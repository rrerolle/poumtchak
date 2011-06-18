import Qt 4.7
//import Qt.labs.gestures 1.0

Rectangle {
    id: pad

    property string label
    property color onHoverColor: "lightsteelblue"
    property color borderColor: "transparent"
    property color buttonColor: "lightblue"
    property real labelSize: 14

    radius: 10
    smooth: true
    border { width: 2; color: borderColor }
    width: (pad_grid.width / 6) - 10
    height: pad.width

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
        onEntered: parent.border.color = onHoverColor
        onExited:  parent.border.color = borderColor
        onClicked: drummer.play(label)
    }
//    GestureArea { 
//        id: buttonTapArea
//        anchors.fill: parent
//        onTap: drummer.play(label)
//    }

    color: buttonMouseArea.pressed ? Qt.darker(buttonColor, 1.5) : buttonColor
    Behavior on color { ColorAnimation{ duration: 55 } }

    scale: buttonMouseArea.pressed ? 1.1 : 1.00
    Behavior on scale { NumberAnimation{ duration: 55 } }

    gradient: Gradient {
        GradientStop { position: 0.0; color: "darkgrey" }
        GradientStop { position: 1.0; color: "black" }
    }
}
