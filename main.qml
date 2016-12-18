import QtQuick 2.7
import QtQuick.Window 2.2
import JsonListModel 1.0

Window {
    visible: true
    width: 480
    height: 240
    title: qsTr("東京の天気")

    JsonListModel {
        id: jsonListModel
        query: "forecasts"
        roles: new Array("dateLabel", "telop", "image", "temperature")
    }

    ListView {
        id: listView
        anchors.fill: parent

        model: jsonListModel

        delegate: Rectangle {
            width: parent.width
            height: 72
            border.color: "#FF000000"
            border.width: 1
            radius: 5
            Row {
                anchors.fill: parent
                padding: 2
                Text {
                    width: parent.width / 3
                    height: parent.height
                    font.pixelSize: 24
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: dateLabel
                }
                Column {
                    width: parent.width / 3
                    Image {
                        width: 48
                        height: 48
                        anchors.horizontalCenter: parent.horizontalCenter
                        fillMode: Image.PreserveAspectFit
                        source: image.url
                    }
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.pixelSize: 16
                        horizontalAlignment: Text.AlignHCenter
                        text: telop
                    }
                }
                Column {
                    width: parent.width / 3
                    anchors.verticalCenter: parent.verticalCenter
                    Text {
                        text:  "最高気温 %1℃".arg(temperature.max.celsius)
                    }
                    Text {
                        text: "最低気温 %1℃".arg(temperature.min.celsius)
                    }
                }
            }
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
