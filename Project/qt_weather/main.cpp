#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <weathersourcer.h>
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("WeatherInfo",new WeatherSourcer);//注册c++类给qml
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
