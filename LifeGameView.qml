import QtQuick 2.0
import com.dmitryshm 1.0

Item {
    id: element
    property int playGroundSize: 10

    CustomImageEditor {
        id: customImageEditor
        onImageChanged: {
            playGround.imagePattern.source = ""
            playGround.imagePattern.source = "image://customprovider/updatedImage"
        }
        patternSize: playGroundSize
    }

    MoveMaker {
        id: moveMaker
        x: 0
        y: 0
        width: 100 //playGroundSize
        height: 100 //playGroundSize
        patternSize: playGroundSize
        //visible: false
        z: 1
    }

    Timer {
        id: moveTimer
        interval: 1000
        running: false
        repeat: true
        onTriggered: moveMaker.move()
    }

    Timer {
        id: setupTimer
        interval: 100
        running: true
        repeat: true
        onTriggered: moveMaker.update()
    }

    ShaderEffect {
        id: playGround
        property vector2d fieldSize: Qt.vector2d(mouseArea.width, mouseArea.height)
        property vector3d gridParams: Qt.vector3d(playGroundSize + 0.1, 0.1, 0.3)
        property variant imagePattern: Image {
            cache: false
            source: "image://customprovider/image"
        }
        anchors.fill: parent
        fragmentShader: "
            varying vec2 qt_TexCoord0;
            uniform vec2 fieldSize;
            uniform vec3 gridParams;
            uniform sampler2D imagePattern;
            void main()
            {
                vec4 patternColor = texture2D(imagePattern, qt_TexCoord0);
                vec2 grid = fract(qt_TexCoord0.xy*gridParams.x);
                vec3 gridColor = vec3(smoothstep(gridParams.y,gridParams.z,grid.x)*smoothstep(gridParams.y,gridParams.z,grid.y));
                gl_FragColor.rgb = gridColor*patternColor.rgb + gridColor/5.0;
                gl_FragColor.a = 1.0;
            }"
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }

    Connections {
        target: mouseArea
        onClicked: customImageEditor.setupImagePixel(playGroundSize*mouseArea.mouseX/mouseArea.width, playGroundSize*mouseArea.mouseY/mouseArea.height)
    }

    states: [
        State {
            name: "gameRun"
            PropertyChanges {
                target: mouseArea
                enabled: false
            }
            PropertyChanges {
                target: playGround
                imagePattern: moveMaker
            }
            PropertyChanges {
                target: setupTimer
                running: false
            }
            PropertyChanges {
                target: moveTimer
                running: true
            }
        },
        State {
            name: "gameResults"
        }
    ]

}































































































/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
