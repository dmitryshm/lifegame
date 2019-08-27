import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3

Window {
    id: window
    width: 700
    height: 500
    visible: true
    title: "игра \"Жизнь\""
    minimumWidth: 700
    minimumHeight: 500

    LifeGameView {
        id: gameView
        playGroundSize: lifeGameSettings.sliderValue
        moveInterval: lifeGameSettings.sliderMovesScale
        anchors.right: rulesView.left
        anchors.rightMargin: 13
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 9
        anchors.top: parent.top
        anchors.topMargin: 20
        onMoved: ++lifeGameSettings.moveNo
        onNoMoreMoves: lifeGameSettings.state = "gameResults"
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
            text: "Правила\n\nИмеется замкнутая зацикленная поверхность, разделённая на клетки, как слева. Клетки могут быть в двух состояниях: в живом или в мёртвом. В начале игры игроку предлагается наделить выбранные клетки жизнью и запустить последовательность ходов. Для каждой живой клетки: на следующий ход она жива тогда и только тогда, когда рядом с ней живы 2 или 3 клетки. Для каждой мёртвой клетки: на следующий ход оживает, если рядом с ней 3 живые клетки. Последовательность ходов и игра заканчивается, если на поверхности не осталось ни одной живой клетки, либо последовательность ходов стала периодической по состоянию клеток на очередной ход."
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
            y: 30
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 46
            anchors.top: parent.top
            anchors.topMargin: 290
        }

        Button {
            id: exitButton
            x: 148
            width: 131
            height: 40
            text: "Выход"
            anchors.top: parent.top
            anchors.topMargin: 430
            anchors.right: parent.right
            anchors.rightMargin: 0
        }

        Button {
            id: runButton
            x: 0
            y: 387
            width: 129
            height: 40
            text: "Запуск"
            anchors.top: parent.top
            anchors.topMargin: 430
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
