#ifndef WEATHERSOURCER_H
#define WEATHERSOURCER_H

#include <QObject>
#include <QtNetwork>
#include <QJsonDocument>
class WeatherSourcer : public QObject
{
    Q_OBJECT
public:
    explicit WeatherSourcer(QObject *parent = 0);
    ~WeatherSourcer();

    QNetworkAccessManager * manager;
    QJsonObject jsonObj;
    QString gettedString,city;//IP字符串,城市名
public slots:
    void Get(const QString websource);
    QString getIP();
    QString getWeatherInfoString();
    QString getCityAqi();
    QString getIPCity();
private:
    bool mode = false;//启动模式一
};

#endif // WEATHERSOURCER_H
