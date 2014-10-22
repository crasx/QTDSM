import QtQuick 2.0

Rectangle {
    width: 100
    height: 100

    Grid {
        id: grid1
        x: 0
        y: 0
        width: 1024
        height: 786
    }

    Row {
        id: row1
        x: 0
        y: 751
        width: 1024
        height: 35
    }

    TextEdit {
        id: ipInput
        x: 51
        y: 759
        width: 174
        height: 20
        text: qsTr("")
        font.pixelSize: 12
    }

    Text {
        id: text1
        x: 34
        y: 762
        text: qsTr("IP")
        font.pixelSize: 12
    }

    Text {
        id: text2
        x: 271
        y: 762
        text: qsTr("Port")
        font.pixelSize: 12

        TextEdit {
            id: textEdit1
            x: 24
            y: -3
            width: 80
            height: 20
            text: qsTr("")
            font.pixelSize: 12
        }
    }
}
