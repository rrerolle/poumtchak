import Qt 4.7

Rectangle {
    id: loop

    property string label
    property color borderColor: "lightblue"
    property color borderColorOn: "green"
    property color borderColorChanging: "orange"
    property color buttonColor: "lightblue"
    property real labelSize: 14

    radius: (((mainwindow.width / 6) - 20) > (mainwindow.height / 4)) ? (mainwindow.height / 4) : ((mainwindow.width / 6) - 20)
    smooth: true
    border { width: 10; color: borderColor }
    width: loop.radius
    height: loop.radius
    state: "OFF"

    Text {
        id: buttonLabel
        anchors.centerIn: parent
        text: label
        color: "#DCDCCC"
        font.pointSize: labelSize
    }

    signal buttonClick()

    MouseArea {
        id: buttonMouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
             if(loop.state == "OFF"){
                 loop.state = "PUTTING_ON"
             }
             else if (loop.state == "PUTTING_ON"){
                 loop.state = "ON"
             }
             else if (loop.state == "ON"){
                 loop.state = "PUTTING_OFF"
             }
             else if (loop.state == "PUTTING_OFF"){
                 loop.state = "OFF"
             }
             drummer.play(label)
        }
    }

    color: buttonMouseArea.pressed ? Qt.darker(buttonColor, 1.5) : buttonColor
    Behavior on color { ColorAnimation{ duration: 55 } }

    gradient: Gradient {
        GradientStop { position: 0.0; color: "darkgrey" }
        GradientStop { position: 1.0; color: "black" }
    }

    states:[
        State {
            name: "ON"
            PropertyChanges { target: loop; border.color: borderColorOn; }
        },
        State {
            name: "OFF"
            PropertyChanges { target: loop; border.color: borderColor; }
        },
        State {
            name: "PUTTING_ON"
            PropertyChanges { target: loop; border.color: borderColorChanging; }
        },
        State {
            name: "PUTTING_OFF"
            PropertyChanges { target: loop; border.color: borderColorChanging; }
        }
    ]
}
