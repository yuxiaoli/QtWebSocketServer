import QtQuick 2.0

Rectangle {
    id: qrect
    x: obj.x
    y: obj.y
    width: 100
    height: 100
    color: "red"

    Text {
        anchors.centerIn: parent
        text: "Hello, World!"
    }
}
