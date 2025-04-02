import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

import CustomOpenGL 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("TtVideoClip")

    // Popup {
    //     id: popup
    //     // anchors.centerIn: parent
    //     Rectangle {
    //         width: 300
    //         height: 400
    //         anchors.fill: parent
    //     }
    // }
    // Button {
    //     text: "Open"
    //     onClicked: popup.open()
    // }
    // Popup {
    //     id: popup
    //     x: (parent.width - width) / 2
    //     y: (parent.height - height) / 2
    //     width: 300
    //     height: 200
    //     modal: true
    //     focus: true
    //     closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    //     Rectangle {
    //         anchors.fill: parent
    //         color: "lightblue"

    //         Text {
    //             anchors.centerIn: parent
    //             text: "This is a popup"
    //         }

    //         Button {
    //             text: "Close"
    //             anchors.bottom: parent.bottom
    //             anchors.horizontalCenter: parent.horizontalCenter
    //             anchors.bottomMargin: 20
    //             onClicked: popup.close()
    //         }
    //     }
    // }

    // SwipeView {
    //     id: view
    //     anchors.fill: parent

    //     Loader {
    //         active: SwipeView.isCurrentItem || SwipeView.isNextItem
    //                 || SwipeView.isPreviousItem
    //         sourceComponent: Page {
    //             Label {
    //                 text: "第一页"
    //                 anchors.centerIn: parent
    //             }
    //         }
    //     }

    //     Loader {
    //         active: SwipeView.isCurrentItem || SwipeView.isNextItem
    //                 || SwipeView.isPreviousItem
    //         sourceComponent: Page {
    //             Label {
    //                 text: "第二页"
    //                 anchors.centerIn: parent
    //             }
    //         }
    //     }

    //     Loader {
    //         active: SwipeView.isCurrentItem || SwipeView.isNextItem
    //                 || SwipeView.isPreviousItem
    //         sourceComponent: Page {
    //             Label {
    //                 text: "第三页"
    //                 anchors.centerIn: parent
    //             }
    //         }
    //     }
    //     MouseArea {
    //         onPressed: popup.open()
    //     }
    // }

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
        rotationAngle: 0

        Rectangle {
            anchors.fill: parent
            color: "red"
            opacity: 0.5
            border.width: 2
        }

        // 使用显式动画绑定
        RotationAnimation on rotationAngle {
            from: 0
            to: 360
            duration: 3000
            loops: Animation.Infinite
            running: true // 必须手动启动
        }
    }
}
