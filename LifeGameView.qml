import QtQuick 2.0
import QtQuick.Controls 2.3
import com.dmitryshm.CustomImageEditor 1.0

Item {
    id: element
    property int playGroundSize: 10

    CustomImageEditor {
        id: customImageEditor
    }
    onPlayGroundSizeChanged: customImageEditor.initImage(playGroundSize)

    ShaderEffect {
        id: playGround
        property vector3d params: Qt.vector3d(playGroundSize + 0.1, 0.1, 0.5)
        property variant imagePattern: customImageEditor.image
        anchors.fill: parent
        fragmentShader: "
            varying vec2 qt_TexCoord0;
            uniform vec3 params;
            void main()
            {
              vec2 grid = fract(qt_TexCoord0.xy*params.x);
              gl_FragColor.rgb = vec3(smoothstep(params.y,params.z,grid.x)*smoothstep(params.y,params.z,grid.y));
              gl_FragColor.a = 1.0;
            }"
    }

    Image {
        id: cellsPattern
        width: playGroundSize
        height: playGroundSize
        enabled: false
        smooth: false
        visible: false
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
