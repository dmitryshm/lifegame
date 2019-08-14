import QtQuick 2.0
import QtQuick.Controls 2.3
import com.dmitryshm.CustomImageEditor 1.0

Item {
    id: element
    property int playGroundSize: 10

    CustomImageEditor {
        id: customImageEditor
        onImageChanged: {
            playGround.update();
        }
    }
    onPlayGroundSizeChanged: customImageEditor.initImage(playGroundSize)
    Component.onCompleted: customImageEditor.initImage(playGroundSize)

    ShaderEffect {
        id: playGround
        property vector2d fieldSize: Qt.vector2d(mouseArea.width, mouseArea.height)
        property vector3d gridParams: Qt.vector3d(playGroundSize + 0.1, 0.1, 0.5)
        property variant imagePattern: ShaderEffectSource {
            sourceItem: customImageEditor.image
            hideSource: true
        }
        anchors.fill: parent
        fragmentShader: "
            varying vec2 qt_TexCoord0;
            uniform vec2 fieldSize;
            uniform vec3 gridParams;
            uniform sampler2D imagePattern;
            void main()
            {
                vec2 patternCoord = vec2(gridParams.x*qt_TexCoord0.x/fieldSize.x, gridParams.x*qt_TexCoord0.y/fieldSize.y);
                vec4 patternColor = texture2D(imagePattern, patternCoord);
                vec2 grid = fract(qt_TexCoord0.xy*gridParams.x);
                vec3 gridColor = vec3(smoothstep(gridParams.y,gridParams.z,grid.x)*smoothstep(gridParams.y,gridParams.z,grid.y));
                gl_FragColor.rgb = vec3(gridColor.r*(1.0 - patternColor.r), gridColor.g*(1.0 - patternColor.g), gridColor.b*(1.0 - patternColor.b));
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
