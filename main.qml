import Qt 4.7

Rectangle {
    id: pad_grid
    width: 370; height:100
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
}
