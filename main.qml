import QtQuick 2.7
import QtQuick.Window 2.2
import JsonListModel 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    JsonListModel {
        id: jsonListModel
        role: "forecasts"
        jrole: new Array("dateLabel", "telop")
    }

    ListView {
        id: listView
        anchors.fill: parent

        model: jsonListModel

        delegate: Text {
            width: parent.width
            height: 30

            text: "%1: %2".arg(dateLabel).arg(telop)
        }
    }

    function getWeather() {
        var xhr = new XMLHttpRequest();
        xhr.open("GET", "http://weather.livedoor.com/forecast/webservice/json/v1?city=%1".arg("130010"), true);
        xhr.onreadystatechange = function() {
            if (xhr.readyState === 4) {
                switch (xhr.status) {
                case 200:
                    jsonListModel.jsonText = xhr.responseText;
                    break;
                default:
                    console.debug("Something wrong to get the Weather data.");
                    break;
                }
            }
        }
        xhr.send();
    }

    Component.onCompleted: getWeather()
}
