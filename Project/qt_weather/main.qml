import QtQuick 2.2
import QtQuick.Window 2.1

Window {
    id: mainWin
    visible: true
    width: 360
    height: 360
    property string txtIP: ""
    property string txtCity: ""
    property string txtWeather: ""
    property string txtAQI: ""
    property string txtLowTemp: ""
    property string txtHighTemp: ""
    property string txtTemp: ""
    property string txtLevel: ""
    Flickable{
        anchors.fill: parent
        clip: true
        Grid{
            rows: 4
            columns: 4
            rowSpacing: 5
            columnSpacing: 5
            anchors.centerIn: parent
            Text{
                text:"IP地址：" + txtIP
            }
            Text{
                text:"城市：" + txtCity
            }
            Text{
                text:"天气：" + txtWeather
            }
            Text{
                text:"空气质量：" + txtAQI
            }
            Text{
                text:"最低气温：" + txtLowTemp
            }
            Text{
                text:"最高气温：" + txtHighTemp
            }
            Text{
                text:"气温：" + txtTemp
            }
            Text{
                text:"空气质量等级：" + txtLevel
            }
        }
    }
    Component.onCompleted: {
        mainWin.txtIP = WeatherInfo.getIP();
        mainWin.txtCity = WeatherInfo.getIPCity();
        var str = WeatherInfo.getWeatherInfoString();
        var aqis = WeatherInfo.getCityAqi();
        mainWin.txtWeather = str.split("|")[0];
        mainWin.txtTemp = str.split("|")[1];
        mainWin.txtLowTemp = str.split("|")[2];
        mainWin.txtHighTemp = str.split("|")[3];
        mainWin.txtLevel = aqis.split("|")[0];
        mainWin.txtAQI = aqis.split("|")[1];
    }
}

