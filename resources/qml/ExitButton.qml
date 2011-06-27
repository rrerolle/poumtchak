import Qt 4.7

Rectangle {
    id: exitbutton

    property string label
    property color borderColor: "transparent"
    property color buttonColor: "lightblue"
    property real labelSize: 10

    radius: 10
    smooth: true
    border { width: 2; color: borderColor }
    width: parent.width / 6
    height: parent.height / 15

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
        onClicked: mixer.exit()
    }

    gradient: Gradient {
        GradientStop { position: 0.0; color: "darkgrey" }
        GradientStop { position: 1.0; color: "black" }
    }
}
