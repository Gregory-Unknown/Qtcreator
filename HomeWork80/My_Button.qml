import QtQuick 2.0

BorderImage {
    id: _mybutton

    property alias text: _txt.text
    signal clicked

    source: "qrc:///img/press.png"
    width: _txt.width + 15
    height: _txt.height + 15
    border.left: 5
    border.top: 2
    border.right: 5
    border.bottom: 2

    Text {
        id: _txt
        color: "red"
        anchors.centerIn: parent
    }

    //Действие мыши
    MouseArea{
        anchors.fill: parent
        onClicked: parent.clicked()


        onPressed: {
            parent.source = "qrc:///img/unpress.png"
            parent.clicked = true
        }
        onReleased: {
            parent.source = "qrc:///img/press.png"
            parent.clicked = false
        }
    }
}
