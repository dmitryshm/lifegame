import QtQuick 2.0
import QtQuick.Controls 2.3

Item {
    id: element
    width: 329
    height: 410

    Grid {
        id: playGround
        anchors.fill: parent
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
