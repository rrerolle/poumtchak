import Qt 4.7

Rectangle {
    id: pad_grid
    width: screenWidth
    height: screenHeight
    anchors.centerIn: parent
    color:"grey"
    state:"LandscapeInverted"

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

    states:  [
        State {
        name: "Landscape"
        PropertyChanges {
            target: pad_grid
            rotation: 0
            width: screenWidth
            height: screenHeight
            x: 0
            y: 0
          }
        },
        State {
          name: "LandscapeInverted"
          PropertyChanges {
            target: pad_grid
            rotation: 180
            width: screenWidth
            height: screenHeight
            x: 0
            y: 0
          }
        },
        State {
          name: "Portrait"
          PropertyChanges {
            target: pad_grid
            rotation: 270
            width: screenHeight
            height: screenWidth
            x: (screenWidth - screenHeight) / 2
            y: -(screenWidth - screenHeight) / 2
          }
        },
        State {
          name: "PortraitInverted"
          PropertyChanges {
            target: pad_grid
            rotation: 90
            width: screenHeight
            height: screenWidth
            x: (screenWidth - screenHeight) / 2
            y: -(screenWidth - screenHeight) / 2
          }
        }
      ]
     
      transitions: [
        Transition {
          from: "*"
          to: "*"
 
          ParallelAnimation {
            RotationAnimation {
              properties: "rotation"
              duration: 250
              direction: RotationAnimation.Shortest
            }
            PropertyAnimation {
              target: pad_grid
              properties: "x,y,width,height"
              duration: 250
            }
          }
        }
      ] 

}
