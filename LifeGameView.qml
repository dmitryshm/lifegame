import QtQuick 2.0
import QtQuick.Controls 2.3

Item {
    id: element
    width: 329
    height: 410
    property int playGroundSize: 100

    Grid {
        id: playGround
        x: 8
        y: 8
        width: 328
        height: 328
        spacing: 1
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        rows: playGroundSize
        columns: playGroundSize
        Repeater {
            model: playGroundSize*playGroundSize
            Rectangle {
                width: 1.0*playGround.width/playGroundSize - 1 + 1.0*playGround.spacing/playGroundSize
                height: 1.0*playGround.height/playGroundSize - 1 + 1.0*playGround.spacing/playGroundSize
                radius: 0
                border.width: 1
            }
        }
    }
    states: [
        State {
            name: "gameRun"
        },
        State {
            name: "gameResults"
        }
    ]

}









































/*##^## Designer {
    D{i:1;anchors_height:464;anchors_width:624;anchors_x:8;anchors_y:8}
}
 ##^##*/
