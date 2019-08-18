import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3

Window {
    id: window
    height: 440
    visible: true
    title: "игра \"Жизнь\""
    minimumWidth: 640
    minimumHeight: 440

    LifeGameView {
        id: gameView
        playGroundSize: lifeGameSettings.sliderValue
        anchors.right: rulesView.left
        anchors.rightMargin: 13
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 9
        anchors.top: parent.top
        anchors.topMargin: 20
    }

    Item {
        id: rulesView
        x: 351
        width: 279
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 10

        Text {
            id: rulesText
            text: "Правила\n\nИмеется замкнутая зацикленная поверхность, разделённая на клетки, как слева. Клетки могут быть в двух состояниях: в живом или в мёртвом. В начале игры игроку предлагается наделить выбранные клетки жизнью и запустить последовательность ходов. Для каждой клетки: на следующий ход она жива тогда и только тогда, когда рядом с ней живы 2 или 3 клетки. Последовательность ходов и игра заканчивается, если на поверхности не осталось ни одной живой клетки, либо последовательность ходов стала периодической по состоянию клеток на очередной ход."
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 205
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            wrapMode: Text.WordWrap
            font.pixelSize: 12
        }

        LifeGameSettings {
            id: lifeGameSettings
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 46
            anchors.top: parent.top
            anchors.topMargin: 251
        }

        Button {
            id: exitButton
            x: 148
            width: 131
            height: 40
            text: "Выход"
            anchors.top: parent.top
            anchors.topMargin: 370
            anchors.right: parent.right
            anchors.rightMargin: 0
        }

        Button {
            id: runButton
            x: 0
            width: 129
            height: 40
            text: "Запуск"
            anchors.top: parent.top
            anchors.topMargin: 370
            anchors.left: parent.left
            anchors.leftMargin: 0
        }
    }

    Connections {
        target: exitButton
        onClicked: Qt.quit()
    }

    Connections {
        target: runButton
        onClicked: {
            runButton.enabled = false
            lifeGameSettings.state = "gameRun"
            gameView.state = "gameRun"
        }
    }
}



















































/*##^## Designer {
    D{i:5;anchors_y:370}D{i:6;anchors_y:410}
}
 ##^##*/
