import Qt 4.7

Rectangle {
    id: pad_grid
    width: 400; height:100
    anchors.fill: parent;
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
        Row {
            Slider {
                id: slide1
                transform: Rotation { origin.x: 25; origin.y: 25; angle: 0} //0 for horizontal slider, 90 for vertical one
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
