#include "weathersourcer.h"
#include <QDebug>

WeatherSourcer::WeatherSourcer(QObject *parent) : QObject(parent)
{

}
void WeatherSourcer::Get(const QString websource)
{
    manager = new QNetworkAccessManager(this);//实例化QNetworkAccessManager
    QEventLoop loop;
    connect(manager,SIGNAL(finished(QNetworkReply*)),&loop,SLOT(quit()));//连接信号槽
    QNetworkReply * reply = manager->get(QNetworkRequest(QUrl(websource)));//发送get请求
    loop.exec();//开启事件循环.会阻塞 后面的代码会无法执行 除非能够循环结束
    QTextCodec * codec = QTextCodec::codecForName("utf-8");//转换字符编码
    QString readString = codec->toUnicode(reply->readAll());//读取所有的二进制的字符串 并且转换为unicode字符编码
    qDebug() << readString;
    if(mode == true)
        jsonObj = QJsonDocument::fromJson(readString.toLocal8Bit()).object();
    else
        gettedString = readString;
    reply->deleteLater();//删除对象
}
QString WeatherSourcer::getIP()
{
    mode = false;//启动模式二
    Get("http://twisterfate.byethost11.com/getip.php");//发送get请求
    qDebug() << gettedString;
    return gettedString;
}
QString WeatherSourcer::getIPCity()
{
    mode = true;//启动模式一
    if(!gettedString.isEmpty())//判断ip字符串是否为不空
    {
        Get("http://apistore.baidu.com/microservice/iplookup?ip=" + gettedString);//发送get请求给百度api
        QString::compare(jsonObj.value("errMsg").toString(),"success") == 0 ? //判断是否获取数据成功
                    city = jsonObj.value("retData").toObject().value("city").toString() :
                    city = QString::null;
    }
    qDebug() << city;
    return city;//返回城市名
}
QString WeatherSourcer::getWeatherInfoString()
{
    mode = true;//启动模式一
    QString weatherString;//天气字符串
    if(!city.isEmpty())//判断城市字符串是否为不空
    {
        Get("http://apistore.baidu.com/microservice/weather?cityname=" + city);//发送get请求给百度api
        if(QString::compare(jsonObj.value("errMsg").toString(),"success") == 0)//如果成功获取
        {
            QJsonObject obj = jsonObj.value("retData").toObject();
            weatherString = obj.value("weather").toString() + "|" + obj.value("temp").toString() + "|" + obj.value("l_tmp").toString() + "|" + obj.value("h_tmp").toString();
        }
        else
            weatherString = QString::null;
    }
    qDebug() << weatherString;
    return weatherString;
}
QString WeatherSourcer::getCityAqi()
{
    mode = true;//启动模式一
    QString aqistring;
    if(!city.isEmpty())
    {
        Get("http://apistore.baidu.com/microservice/aqi?city=" + city);
        if(QString::compare(jsonObj.value("retMsg").toString(),"success") == 0)//判断是否获取数据成功
        {
            QJsonObject obj = jsonObj.value("retData").toObject();
            aqistring = obj.value("level").toString() + "|" + QString::number(obj.value("aqi").toInt());
        }
        else
            aqistring = QString::null;
    }
    qDebug() << aqistring;
    return aqistring;
}
WeatherSourcer::~WeatherSourcer()
{

}

