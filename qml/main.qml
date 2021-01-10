import QtQuick 2.9
import QtQuick.Controls 2.2
import com.hue.HueAPI 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Huelify")

    ListModel {
        id: fakeModel
    }

    Button {
        id: sync
        width: parent.width
        text: "sync"
        onClicked: HueAPI.sync()
    }

    ScrollView {
        anchors.top: sync.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        ListView {
            width: parent.width
            model: HueAPI.model.rowCount() ? HueAPI.model : fakeModel
            delegate: Light {
                index: index
                text: name
                lightBrightness: brightness / 255
                lightOn: isOn
            }
        }
    }
}
