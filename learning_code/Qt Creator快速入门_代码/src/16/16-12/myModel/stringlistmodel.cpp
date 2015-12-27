#include "stringlistmodel.h"
#include <QMimeData>

int StringListModel::rowCount(const QModelIndex &parent) const
{
    return stringList.count();
}

QVariant StringListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= stringList.size())
        return QVariant();

    // ���Qt::EditRole���ж�
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return stringList.at(index.row());
    else
        return QVariant();
}

QVariant StringListModel::headerData(int section, Qt::Orientation orientation,
                                     int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QString("Column %1").arg(section);
    else
        return QString("Row %1").arg(section);
}

// ������ʵ�ֱ༭������ӵ���������

// ������16-12�н������޸ģ���֧���ϷŲ���
Qt::ItemFlags StringListModel::flags(const QModelIndex &index) const
{
    // �����������Ч����ôֻ֧�ַ������
    if (!index.isValid())
        return Qt::ItemIsEnabled | Qt::ItemIsDropEnabled;

    // �����������Ч����ô��֧����ק������Ҳ֧�ַ������
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable
            | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}

bool StringListModel::setData(const QModelIndex &index,
                              const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {

        stringList.replace(index.row(), value.toString());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

// �����ǲ����ɾ�����õ�����������

bool StringListModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    beginInsertRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        stringList.insert(position, "");
    }

    endInsertRows();
    return true;
}

bool StringListModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        stringList.removeAt(position);
    }

    endRemoveRows();
    return true;
}

// ���º���������16-12����ӣ�����ʵ���ϷŹ���

// ����֧�ַ��붯��
Qt::DropActions StringListModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

// �������ϷŲ����е�������Ŀ�����ݵı�������
QStringList StringListModel::mimeTypes() const
{
    QStringList types;
    // "application/vnd.text.list"���Զ�������ͣ��ں���ĺ�����Ҫ����һ��
    types << "application/vnd.text.list";
    return types;
}

// ���Ϸŵ����ݷ���QMimeData��
QMimeData * StringListModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    foreach (const QModelIndex &index, indexes) {
        if (index.isValid()) {
            QString text = data(index, Qt::DisplayRole).toString();
            stream << text;
        }
    }
    // �����ݷ���QMimeData��
    mimeData->setData("application/vnd.text.list", encodedData);
    return mimeData;
}

// ���Ϸŵ����ݷ���ģ����
bool StringListModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    // ������붯����Qt::IgnoreAction����ô����true
    if (action == Qt::IgnoreAction)
        return true;
    // ������ݵĸ�ʽ����ָ���ĸ�ʽ����ô����false
    if (!data->hasFormat("application/vnd.text.list"))
        return false;
    // ��Ϊ�������б�ֻ��һ�У������д���0ʱ����false
    if (column > 0)
        return false;
    // ���ÿ�ʼ�������
    int beginRow;
    if (row != -1)
        beginRow = row;
    else if (parent.isValid())
        beginRow = parent.row();
    else
        beginRow = rowCount(QModelIndex());

    // �����ݴ�QMimeData�ж�ȡ������Ȼ����뵽ģ����
    QByteArray encodedData = data->data("application/vnd.text.list");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);
    QStringList newItems;
    int rows = 0;
    while (!stream.atEnd()) {
        QString text;
        stream >> text;
        newItems << text;
        ++rows;
    }
    insertRows(beginRow, rows, QModelIndex());
    foreach (const QString &text, newItems) {
        QModelIndex idx = index(beginRow, 0, QModelIndex());
        setData(idx, text);
        beginRow++;
    }

    return true;
}
