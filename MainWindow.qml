import Qt 4.7

Rectangle {
    id: mainwindow

    Column {
        spacing: 20
        anchors.centerIn: parent
        Row {
            spacing: 20
            Pad {
                id: pad1x1
                label: "kick"
            }
            Pad {
                id: pad1x2
                label: "hihat"
            }
            Pad {
                id: pad1x3
                label: "snare"
            }
            Pad {
                id: pad1x4
                label: "crash"
            }
        }
        Row {
            spacing: 20
            Loop {
                id: loop1x1
                label: "kick"
            }
            Loop {
                id: loop1x2
                label: "hihat"
            }
            Loop {
                id: loop1x3
                label: "snare"
            }
            Loop {
                id: loop1x4
                label: "crash"
            }
        }
    }
    ExitButton {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 40
        id: exitbtn
        label: "Exit"
    }
    Slider {
        id: volume_slider
        transform: Rotation {
            origin.x: 0
            origin.y: 0
            angle: 0
        }
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 10
        anchors.bottomMargin: 10
    }
}
