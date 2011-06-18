import Qt 4.7

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
    width: 80; height: 80

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
        onClicked: tchikboum.playLoop(label)
    }

    color: buttonMouseArea.pressed ? Qt.darker(buttonColor, 1.5) : buttonColor
    Behavior on color { ColorAnimation{ duration: 55 } }

    scale: buttonMouseArea.pressed ? 1.1 : 1.00
    Behavior on scale { NumberAnimation{ duration: 55 } }

    gradient: Gradient {
        GradientStop { position: 0.0; color: "darkgrey" }
        GradientStop { position: 1.0; color: "black" }
    }
}
