#include "widget.h"
#include "ui_widget.h"

#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>


/*
VHD 格式
http://zhangyu.blog.51cto.com/197148/1095637/

VHD也用于xen虚拟化，目前也是xen上虚拟磁盘的默认标准。
VHD结构有2种实现方式：固定方式和动态方式。 

固定方式就是用真实大小的文件模拟同样大小的一个虚拟磁盘。当然，额外的，一定要加上一些对
本文件的总的描述(在文件尾部)，否则系统无法知道就是固定磁盘还是动态磁盘。
动态磁盘是按稀疏方式，用文件做容器，来表述一个可能大得多的虚拟磁盘，如果某个区域没写数据，
就可能不在文件中真正分配空间。另外，差异磁盘(快照)也基于动态磁盘的方式存储。
本文用"$VHD文件"的说法表示VHD文件本身，而用"$虚拟磁盘"的说法表示 VHD文件描述的
虚拟磁盘寻址空间。

固定方式在文件的最后512字节加上描述，文件一开始和物理磁盘的扇区一一对应。
最后添加的512字节描述结构如下:(扇区是以512字节为单位)
固定方式VHD结构 HD Footer (hd_ftr)

      | 0 1 2 3         | 4 5 6 7           | 8 9 A B       | C D E F
------+-----------------+-------------------+---------------+-------------------
0x0   | MAGIC:conectix                      | features      | (major, minor)
------+-------------------------------------+---------------+-------------------
0x10  | data_offset                         | Creation time | Creator application
------+-----------------+-------------------+---------------+-------------------
0x20  | Creatoe version | Creator host OS   | Size at creation (bytes)
------+-----------------+-------------------+---------------+-------------------
0x30  | Current size of disk (bytes)        | Disk geometry | Disk type
------+-----------------+-------------------+---------------+-------------------
0x40  | checksum        | UUID -
------+-----------------+-------------------------------------------------------
0x50  | - UUID          |
------+-----------------+
0x60  |
0x70  |     保留空间(直到扇区结束)
....
------+-------------------------------------------------------------------------

xen种源码表述是这样的:

struct hd_ftr {
    char        cookie[8];      // Identifies original creator of the disk
    u32         features;       // Feature Support -- see below
    u32         ff_version;     // (major,minor) version of disk file
    u64         data_offset;    // Abs. offset from SOF to next structure
    u32         timestamp;      // Creation time.  secs since 1/1/2000GMT
    char        crtr_app[4];    // Creator application
    u32         crtr_ver;       // Creator version (major,minor)
    u32         crtr_os;        // Creator host OS
    u64         orig_size;      // Size at creation (bytes)
    u64         curr_size;      // Current size of disk (bytes)
    u32         geometry;       // Disk geometry
    u32         type;           // Disk type
    u32         checksum;       // 1's comp sum of this struct
    vhd_uuid_t  uuid;           // Unique disk ID, used for naming parents
    char        saved;          // one-bit -- is this disk/VM in a saved state?
    char        hidden;         // tapdisk-specific field: is this vdi hidden?
    char        reserved[426];  // padding
};

结构解释:

cookie：
    识别标志，为"conectix"，用于判断VHD是否有效

features：
    取值如下。
#define HD_NO_FEATURES      0x00000000
#define HD_TEMPORARY        0x00000001  // disk can be deleted on shutdown
#define HD_RESERVED         0x00000002  // NOTE: must always be set

ff_version：
    VHD版本，用处不大，用于结构判断，似乎更多的会用到crtr_ver。

data_offset：
    描述中指下一个结构的起始绝对字节位置，如果是动态磁盘，这表明了dd_hdr（稍后会提到）的
    物理字节位置。如果是固定磁盘，似乎总是0xFFFFFFFF。

timestamp:
    VHD的创建时间，指2000年1月1日00:00:00起始的秒值。和HFS对时间的描述方式一致，也就是
    说此处数值加上0xB492F400 (即2000/01/01 00:00:00)，即是标准的HFS时间方法对本值的解释。

crtr_app：
    见代码注释

crtr_ver：
    创建版本。根据版本号可实施对应的方法。似乎目前只有当创建版本号为0x00000001时，
    对于bitmap的操作会有不同(具体细节请参考xen源码)。

crtr_os：
    见代码注释

orig_size ：
    创建时$虚拟磁盘大小，再强调一下，这个大小指虚拟出来的磁盘的可用寻址空间。
    如果是固定格式的VHD，这个大小等于$VHD文件的大小减去1扇区(尾部 hd_ftr)。

curr_size：
    或许是用于vhd在线扩容后的最后大小表述，没仔细研究过。同样指$虚拟磁盘的大小，
    即虚拟出来的磁盘的可用寻址空间，如果没有扩容，和orig_size相同。

geometry：
    VHD的C/H/S结构参数，兼容一些老的应用(其实估计不会用到了)。如下表示
#define GEOM_GET_CYLS(_g)  (((_g) >> 16) & 0xffff)
#define GEOM_GET_HEADS(_g) (((_g) >> 8)  & 0xff)
#define GEOM_GET_SPT(_g)   ((_g) & 0xff)

type：
    非常重要的，表示这个VHD的类型。如下表示
#define HD_TYPE_NONE       0
#define HD_TYPE_FIXED      2  // fixed-allocation disk
#define HD_TYPE_DYNAMIC    3  // dynamic disk
#define HD_TYPE_DIFF       4  // differencing disk

    如果是差异磁盘，在dd_hdr中会描述父设备的设备号，但结构与动态磁盘相同

checksum：
    整个扇区所有字节(当然一开始不包括checksum本身)相加得到32位数，再按位取反。

uuid：
    用于VHD识别号，如果是有差异磁盘，这个ID非常重要，决定了VHD间的主从关系。

saved：
    动态中使用，见代码注释

hidden：
    见代码注释

reserved：
    保留空间，总是为0

上述结构中最重要的变量为VHD类型、大小、checksum。

--------------------------------------------------------------------------------
--------------------------------------------------------------------------------

磁盘容量  = 磁头数 × 磁道（柱面）数 × 每道扇区数 × 每扇区字节数
硬盘有数个盘片，每盘片两个面，每个面一个磁头
硬盘以前是512字节一个扇区，现在新硬盘都是4K一个扇区，
这里还是以512字节为单位
Cylinder柱面数表示硬盘每面盘面上有几条磁道，编号是从0开始，最大为1023，表示有1024个磁道。
Head磁头数表示磁盘共有几个磁头，也就是几面盘面，编号从0开始，最大为255，表示有256个磁头。
Sector/Track扇区数表示每条磁道上有几个扇区，编号从1开始，最大为63，表示63个扇区，
每个扇区为512字节，他是磁盘的最小存储单位。
1024个柱面 x 63个扇区 x 256个磁头 x 512byte = 8455716864byte（即8.4G）

每个磁道通常划分为 63 个扇区
VHD文件一开始的512字节对应物理硬盘的0面0道1扇区，第二个512字节对应0面0道2扇区，
一直对应到0面0道n扇区，n为每磁道的扇区数。
然后紧接着是1面0道1扇区，1面0道2扇区

LBA = C * 磁头总数 * 每道扇区数 + H * 每道扇区数 + (S - 1)
C: 磁道，H: 磁头，S: 扇区号

C: 963, H: 16, S: 17
134217728 bytes --> 总字节数 不等于 下面所算的 存储容量，为什么?
存储容量 = 16 * 963 * 17 * 512

VHD容量为 128 MB，即 134217728 bytes
再加上 VHD 最后的 512字节标识，整个文件大小为 134218240 bytes
VHD容量为 134217728 bytes，按 512 字节一个扇区划分，共可划分
134217728 / 512 = 262144 个扇区
然后我们用CHS计算总扇区数
16 * 963 * 17 = 261936 个扇区，为什么会和上面的不同，少了 208 个扇区
(这 208 个扇区应该就是 附加扇区，可以用 DiskGenius 看一下自己的硬盘，
至于有什么用，不清楚
因为现在的硬盘全部都是LBA寻址了，那个附加空间的意思只是总扇区数-(C*H*S)后的
剩余而已。 对于存储（分区，PV）来说，只需要关心总扇区数。
也就是说只要知道硬盘的总容量，然后直接求扇区的总数量，用LBA来寻址即可，
如果用CHS的话，C最多只有1024, H最多是255，S最多是63, 约为8.4G容量
)


16个磁头（即16个面，8个盘片），963个磁道，17个扇区
硬盘写法:

0面0道1扇区, 0面0道2扇区, ... , 0面0道17扇区,
1面0道1扇区, 1面0道2扇区, ... , 1面0道17扇区,
...
15面0道1扇区, 15面0道2扇区, ... , 15面0道17扇区,

0面1道1扇区, 0面1道2扇区, ... , 0面1道17扇区,
...
15面1道1扇区, 15面1道2扇区, ... , 15面1道17扇区,

0面2道1扇区, 0面2道2扇区, ... , 0面2道17扇区,
...
15面2道1扇区, 15面2道2扇区, ... , 15面2道17扇区,

...
...

0面962道1扇区, 0面962道2扇区, ... , 0面962道17扇区,
...
15面962道1扇区, 15面962道2扇区, ... , 15面962道17扇区,
完.
注意，磁头和磁道是从0开始，扇区是从1开始

LBA = C * 磁头总数 * 每道扇区数 + H * 每道扇区数 + (S - 1)
C: 磁道，H: 磁头，S: 扇区号
0面0道1扇区 = 0 * 16 * 17 + 0 * 17 + (1 - 1) = 0
0面0道17扇区 = 0 + 0 + (17 - 1) = 16
1面0道1扇区 = 0 + 1 * 17 + (1 - 1) = 17
15面0道1扇区 = 0 + 15 * 17 + (1 - 1) =
15面962道17扇区 = 962 * 16 * 17 + 15 * 17 + (17 - 1) = 261935


*/


struct hd_ftr {
    uchar       cookie[8];          // Identifies original creator of the disk
    uchar       features[4];        // Feature Support -- see below
    uchar       ff_version[4];      // (major,minor) version of disk file
    uchar       data_offset[8];     // Abs. offset from SOF to next structure
    uchar       timestamp[4];       // Creation time.  secs since 1/1/2000GMT
    uchar       crtr_app[4];        // Creator application
    uchar       crtr_ver[4];        // Creator version (major,minor)
    uchar       crtr_os[4];         // Creator host OS
    uchar       orig_size[8];       // Size at creation (bytes)
    uchar       curr_size[8];       // Current size of disk (bytes)
    uchar       geometry[4];        // Disk geometry
    uchar       type[4];            // Disk type
    uchar       checksum[4];        // 1's comp sum of this struct
    uchar       uuid[16];           // Unique disk ID, used for naming parents
};

// features
#define HD_NO_FEATURES      0x00000000
#define HD_TEMPORARY        0x00000001  // disk can be deleted on shutdown
#define HD_RESERVED         0x00000002  // NOTE: must always be set

// type
#define HD_TYPE_NONE       0
#define HD_TYPE_FIXED      2  // fixed-allocation disk
#define HD_TYPE_DYNAMIC    3  // dynamic disk
#define HD_TYPE_DIFF       4  // differencing disk

// C/H/S --> 柱面/磁头/扇区
#define GEOM_GET_CYLS(_g)  (((_g) >> 16) & 0xffff)
#define GEOM_GET_HEADS(_g) (((_g) >> 8)  & 0xff)
#define GEOM_GET_SPT(_g)   ((_g) & 0xff)


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->diskInfoPlainTextEdit->setReadOnly(true);
    ui->binFileLineEdit->setReadOnly(true);

    isVdiskFileOpen = false;
    isDataFileOpen = false;
}

Widget::~Widget()
{
    if (isVdiskFileOpen)
        vdiskFile->close();

    if (isDataFileOpen)
        dataFile->close();

    delete ui;
}

/*
 * 选择要打开虚拟磁盘文件的路径
 */
void Widget::on_openDiskPushButton_clicked()
{
    QString filePath;
    filePath = QFileDialog::getOpenFileName(this, tr("Open Virtual Disk File"),
                                            "", "VHD File (*.vhd)");
    openVirtualDiskFile(filePath);
}

/*
 * 尝试打开虚拟磁盘文件，并读取最后一个扇区(512字节)里最有用的数据
 */
void Widget::openVirtualDiskFile(QString filePath)
{
    if (filePath.isEmpty()) {
        //QMessageBox::warning(this, tr("File Error"),
        //                     tr("File Path is Empty"), QMessageBox::Ok);
        return;
    }

    if (isVdiskFileOpen)
        vdiskFile->close();

    QString fileName;
    vdiskFile = new QFile(filePath);
    QFileInfo vdiskFileInfo(filePath);
    unsigned int vdiskFileSize;

    fileName = vdiskFileInfo.fileName();
    vdiskFileSize = vdiskFileInfo.size();

    /* Try to open */
    if (!vdiskFile->open(QIODevice::ReadWrite)) {
        QMessageBox::warning(this, tr("Open Virtual Disk File Error"),
                             tr("Can't Open Virtual Disk File: %1\n"
                                "Reason: %2").arg(fileName).
                             arg(vdiskFile->errorString()),
                             QMessageBox::Ok);
        return;
    }
    isVdiskFileOpen = true;
    ui->diskInfoPlainTextEdit->clear();

    /* Read the last sector (512 bytes) */
    int lastSectorIndex = vdiskFileSize - 512;
    //qDebug() << lastSectorIndex;
    vdiskFile->seek(lastSectorIndex);

    struct hd_ftr vdiskFormat;
    vdiskFile->read((char *) &vdiskFormat, sizeof(struct hd_ftr));



    QString cookie;
    QString features;
    int majorVersion, minorVersion;
    QString dataOffset;
    QString createApp;
    QString createOS;
    int createSize;
    int currentSize;
    QString diskType;
    QString uuid;
    uint geometry;

    int i;

    // cookie
    for (i = 0; i < (int) sizeof(vdiskFormat.cookie); ++i)
        cookie.append(vdiskFormat.cookie[i]);
    qDebug() << cookie;

    if (cookie != "conectix") {
        QMessageBox::warning(this, "File Error",
                             "Please Open a Correct Virtual Disk File (.VHD)",
                             QMessageBox::Ok);
        return;
    }
    ui->diskInfoPlainTextEdit->appendPlainText("File Path: " + filePath);
    ui->diskInfoPlainTextEdit->appendPlainText("Cookie: " + cookie);


    // features
    switch (vdiskFormat.features[3]) {
    case 0:
        features = "No Features";
        break;
    case 1:
        features = "Temporary";
        break;
    case 2:
        features = "Reserved";
        break;
    default:
        features = "None";
        break;
    }
    qDebug() << features;
    ui->diskInfoPlainTextEdit->appendPlainText("Features: " + features);

    // version
    majorVersion = (vdiskFormat.ff_version[0] << 8) + vdiskFormat.ff_version[1];
    minorVersion = (vdiskFormat.ff_version[2] << 8) + vdiskFormat.ff_version[3];
    qDebug() << majorVersion << minorVersion;
    ui->diskInfoPlainTextEdit->
            appendPlainText(QString("Major Version: %1 , Minor Version: %2").
                            arg(majorVersion).arg(minorVersion));

    // data offset
    QByteArray offsetByte;
    for (i = 0; i < (int) sizeof(vdiskFormat.data_offset); ++i) {
        offsetByte.append(vdiskFormat.data_offset[i]);
        dataOffset.append(offsetByte.toHex().toUpper() + " ");
        offsetByte.clear();
    }
    ui->diskInfoPlainTextEdit->appendPlainText("Data Offset: " + dataOffset);

    // creation time
    int time = 0;
    for (i = 0; i < (int) sizeof(vdiskFormat.timestamp); ++i) {
        time = (time << 8) + vdiskFormat.timestamp[i];
    }
    qDebug() << time;

    // GMT 时间
    QDate date(2000, 1, 1);
    QDateTime createTime(date);
    createTime = createTime.addSecs(time);
    qDebug() << createTime.toString("yyyy-MM-dd hh:mm:ss");
    ui->diskInfoPlainTextEdit->appendPlainText(QString("Creat Time : %1 GMT").
                                               arg(createTime.toString("yyyy-MM-dd hh:mm:ss")));

    // Create application
    for (i = 0; i < (int) sizeof(vdiskFormat.crtr_app); ++i)
        createApp.append(vdiskFormat.crtr_app[i]);
    ui->diskInfoPlainTextEdit->appendPlainText(QString("Create Application: %1").
                                               arg(createApp));

    // Create version
    majorVersion = (vdiskFormat.crtr_ver[0] << 8) + vdiskFormat.crtr_ver[1];
    minorVersion = (vdiskFormat.crtr_ver[2] << 8) + vdiskFormat.crtr_ver[3];
    ui->diskInfoPlainTextEdit->
            appendPlainText(QString("Create Version: Major Version(%1) , "
                                    "Minor Version(%2)").arg(majorVersion).
                            arg(minorVersion));

    // Create OS
    for (i = 0; i < (int) sizeof(vdiskFormat.crtr_os); ++i)
        createOS.append(vdiskFormat.crtr_os[i]);
    ui->diskInfoPlainTextEdit->appendPlainText(QString("Create OS: %1").
                                               arg(createOS));

    // creation size
    createSize = 0;
    for (i = 0; i < (int) sizeof(vdiskFormat.orig_size); ++i)
        createSize = (createSize << 8) + vdiskFormat.orig_size[i];
    ui->diskInfoPlainTextEdit->appendPlainText(QString("Creation Size: %1 bytes").
                                               arg(createSize));

    // current size
    currentSize = 0;
    for (i = 0; i < (int) sizeof(vdiskFormat.curr_size); ++i)
        currentSize = (currentSize << 8) + vdiskFormat.curr_size[i];

    ui->diskInfoPlainTextEdit->appendPlainText(QString("Current Size: %1 bytes").
                                               arg(currentSize));


    // geometry
    geometry = 0;
    for (i = 0; i < (int) sizeof(vdiskFormat.geometry); ++i)
        geometry = (geometry << 8) + vdiskFormat.geometry[i];
    int cycles = GEOM_GET_CYLS(geometry);
    int heads = GEOM_GET_HEADS(geometry);
    int sectors = GEOM_GET_SPT(geometry);
    qDebug() << "geometry: " << geometry;
    qDebug() << heads << cycles << sectors;
    ui->diskInfoPlainTextEdit->
            appendPlainText(QString("Have %1 heads, %2 cycles, %3 sectors").
                            arg(heads).arg(cycles).arg(sectors));


    // disk type
    switch (vdiskFormat.type[3]) {
    case 0:
        diskType = "None";
        break;
    case 2:
        diskType = "Fixed-allocation Disk";
        break;
    case 3:
        diskType = "Dynamic Disk";
        break;
    case 4:
        diskType = "Differencing Disk";
        break;
    default:
        diskType = "Error";
        break;
    }
    ui->diskInfoPlainTextEdit->appendPlainText("Disk Type: " + diskType);

    // UUID
    for (i = 0; i < (int) sizeof(vdiskFormat.uuid); ++i) {
        offsetByte.append(vdiskFormat.uuid[i]);
        uuid.append(offsetByte.toHex().toUpper());
        offsetByte.clear();
    }
    ui->diskInfoPlainTextEdit->appendPlainText("UUID: " + uuid);

    // 设置LBA扇区号范围
    totalSectors = heads * cycles * sectors;
    ui->sectorLabel->setText(QString("0 ~ %1").arg(totalSectors - 1));
}

void Widget::openDataFile(QString filePath)
{
    if (filePath.isEmpty())
        return;

    if (isDataFileOpen)
        dataFile->close();

    QString fileName;
    dataFile = new QFile(filePath);
    QFileInfo dataFileInfo(filePath);
    unsigned int dataFileSize;

    fileName = dataFileInfo.fileName();
    dataFileSize = dataFileInfo.size();

    /* Try to open */
    if (!dataFile->open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Open Data File Error"),
                             tr("Can't Open Data File: %1\n"
                                "Reason: %2").arg(fileName).
                             arg(dataFile->errorString()),
                             QMessageBox::Ok);
        return;
    }
    isDataFileOpen = true;
    ui->binFileLineEdit->clear();

    ui->binFileLineEdit->setText(filePath);

    // read data;
    binaryData.clear();

}

void Widget::on_binFilePushButton_clicked()
{
    QString filePath;
    filePath = QFileDialog::getOpenFileName(this, tr("Open Data File"));
    openDataFile(filePath);
}

void Widget::on_writeDiskPushButton_clicked()
{
    if (ui->sectorLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, tr("Write Error"),
                             tr("Please enter start sector number"),
                             QMessageBox::Ok);
        return;
    }

    unsigned int startSector = ui->sectorLineEdit->text().toUInt();

    // 检查扇区数是否正确
    if (!(startSector >= 0 && startSector < totalSectors)) {
        QMessageBox::warning(this, tr("Sector Error"),
                             tr("Please enter a correct start sector number"),
                             QMessageBox::Ok);
        return;
    }

    // 指针指到该扇区的起始位
    vdiskFile->seek(startSector * 512);

    int res, i;
    binaryData = dataFile->readAll();

    res = vdiskFile->write(binaryData);
    qDebug() << "write " << res << " bytes";

    if (res != -1)
        QMessageBox::information(this, tr("Write file success"),
                                 tr("Write file success!"));

    return;

    // 下面逻辑有问题
    // 如果数据大小不是512的整数倍，还要填充数据
    int size = binaryData.size();
    qDebug() << "size = " << size;


    int offset = 512 - (size - (size / 512) * 512);
    for (i = 0; i < offset; ++i)
        binaryData.append((char) 0x0);

    res = vdiskFile->write(binaryData);

    qDebug() << "write " << res << " bytes";
    if (res != -1)
        QMessageBox::information(this, tr("Write file success"),
                                 tr("Write file success!"));
}
