import QtQuick 2.0
import QtQuick.Controls 2.3

Item {
    id: element
    property alias sliderValue: slider.value

    Text {
        id: element1
        x: 0
        y: 54
        text: "Размер: "
        font.pixelSize: 12
    }

    Text {
        id: element2
        x: 57
        y: 54
        text: slider.value
        font.pixelSize: 12
    }

    Text {
        id: element3
        x: 0
        y: 88
        width: 19
        height: 15
        text: slider.from
        font.pixelSize: 12
    }

    Slider {
        id: slider
        x: 25
        y: 75
        width: 162
        height: 40
        from: 3
        to: 1000
        stepSize: 1
        value: 50
    }

    Text {
        id: element4
        x: 193
        y: 88
        text: slider.to
        font.pixelSize: 12
    }

    Text {
        id: element5
        width: 221
        height: 53
        text: "Выберите размер игрового поля, укажите живые клетки на поле и запустите игру нажатием кнопки."
        wrapMode: Text.WordWrap
        font.pixelSize: 12
    }
    states: [
        State {
            name: "gameRun"

            PropertyChanges {
                target: element5
                visible: false
            }

            PropertyChanges {
                target: element1
                visible: false
            }

            PropertyChanges {
                target: element2
                visible: false
            }

            PropertyChanges {
                target: element3
                visible: false
            }

            PropertyChanges {
                target: slider
                visible: false
            }

            PropertyChanges {
                target: element4
                visible: false
            }
        },
        State {
            name: "gameResults"

            PropertyChanges {
                target: element4
                visible: false
            }

            PropertyChanges {
                target: slider
                visible: false
            }

            PropertyChanges {
                target: element3
                visible: false
            }

            PropertyChanges {
                target: element1
                visible: false
            }

            PropertyChanges {
                target: element2
                visible: false
            }

            PropertyChanges {
                target: element5
                visible: false
            }
        }
    ]

}

























/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
