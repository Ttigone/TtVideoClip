import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

import CustomOpenGL 1.0

// ApplicationWindow {
Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("TtVideoClip")

    // ColumnLayout {
    //     anchors.centerIn: parent
    //     spacing: 10
    //     Button {
    //         text: qsTr("Check State")
    //         onClicked: {
    //             result.text = "My Name is Kambiz!";
    //             console.log("Hello, Kambiz!")
    //         }
    //     }
    //     Text {
    //         id: result
    //     }
    // }
    // 使用我们注册的OpenGL组件
    OpenGLCube {
        id: cube
        width: 400
        height: 400
        anchors.centerIn: parent

        // 使用属性动画
        SequentialAnimation on rotationAngle {
            NumberAnimation {
                from: 0
                to: 360
                duration: 3000
            }
            loops: Animation.Infinite
        }
    }
}
