import Qt 4.7

Rectangle {
    id: pad_grid
    width: screenWidth
    height: screenHeight
    anchors.centerIn: parent
    color:"grey"

    Column {
        spacing: 10
        anchors.centerIn: parent
        Row {
            spacing: 10
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
    }
    ExitButton {
        id: exit_button
        label: "Quit"
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Slider {
        id: volume_slider
        transform: Rotation { 
            origin.x: 25
            origin.y: 25
            angle: 0
        } 
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.bottomMargin: 10
    } 

}
