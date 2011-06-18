import Qt 4.7

Rectangle {
    id: pad_grid
    width: screenWidth
    height: screenHeight
    anchors.centerIn: parent
    color:"blue"

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
        Row {
            ExitButton {
                id: exitbtn
                label: "Exit"
            }
        }
    }
}
