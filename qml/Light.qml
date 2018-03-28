import QtQuick 2.0

Item {
    property alias text: txt.text
    property int index
    height: 50

    Text {
        id: txt
        text: text
    }
}
