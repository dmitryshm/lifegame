import QtQuick 2.0
import QtQuick.Controls 2.3

Item {
    id: element
    property int playGroundSize: 10

    ShaderEffect {
        id: playGround
        property vector3d params: Qt.vector3d(playGroundSize + 0.1, 0.1, 0.5)
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
    D{i:0;autoSize:true;height:480;width:640}D{i:1;anchors_height:328;anchors_width:328;anchors_x:8;anchors_y:8}
}
 ##^##*/
