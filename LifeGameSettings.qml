import QtQuick 2.0
import QtQuick.Controls 2.3

Item {
    id: element
    property alias sliderValue: slider.value
    property alias sliderMovesScale: speedSlider.value
    property int moveNo: 0

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
        value: 10
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

    Text {
        id: element6
        x: 65
        y: 5
        width: 24
        height: 10
        visible: false
        font.pixelSize: 12
        text: "задержка хода"
    }

    Slider {
        id: speedSlider
        x: 26
        y: 21
        width: 162
        stepSize: 1
        from: 1
        to: 1000
        visible: false
        value: 1000
    }

    Text {
        id: element7
        x: 27
        y: 67
        text: "минимальная"
        visible: false
        font.pixelSize: 12
    }

    Text {
        id: element10
        x: 57
        y: 88
        text: "номер хода:"
        visible: false
        font.pixelSize: 12
    }

    Text {
        id: element11
        x: 136
        y: 88
        text: moveNo
        visible: false
        font.pixelSize: 12
    }

    Text {
        id: element8
        text: "1 c"
        visible: false
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
                enabled: false
                visible: false
            }

            PropertyChanges {
                target: element4
                visible: false
            }

            PropertyChanges {
                target: element6
                visible: true
            }

            PropertyChanges {
                target: speedSlider
                visible: true
            }

            PropertyChanges {
                target: element7
                visible: true
            }

            PropertyChanges {
                target: element11
                visible: true
            }

            PropertyChanges {
                target: element10
                visible: true
            }

            PropertyChanges {
                target: element8
                x: 161
                y: 67
                visible: true
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
                enabled: false
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
                x: 13
                y: 35
                text: "Игра завершилась из-за потвора ситуации на поле."
                visible: true
            }

            PropertyChanges {
                target: element10
                x: 18
                text: "последний ход:"
                visible: true
            }

            PropertyChanges {
                target: element11
                visible: true
            }
        }
    ]

}













































/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
