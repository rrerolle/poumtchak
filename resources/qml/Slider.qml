 import Qt 4.7

 Item {
     id: slider; width: 100; height: 400

     // value is read/write.
     property real value: 1
     onValueChanged: updatePos();
     property real maximum: 1
     property real minimum: 1
     property int yMax: height - handle.height - 4
     onYMaxChanged: updatePos();
     onMinimumChanged: updatePos();

     function updatePos() {
         if (maximum > minimum) {
             var pos = 2 + (value - minimum) * slider.yMax / (maximum - minimum);
             pos = Math.min(pos, height - handle.height - 2);
             pos = Math.max(pos, 2);
             handle.y = pos;
         } else {
             handle.y = 2;
         }
     }

     Rectangle {
         anchors.fill: parent
         border.color: "white"; border.width: 0; radius: 8
         gradient: Gradient {
             GradientStop { position: 0.0; color: "#66343434" }
             GradientStop { position: 1.0; color: "#66000000" }
         }
     }

     Rectangle {
         id: handle; smooth: true
         x: 2; height: 60; width: slider.width-4; radius: 6
         gradient: Gradient {
             GradientStop { position: 0.0; color: "lightgray" }
             GradientStop { position: 1.0; color: "gray" }
         }

         MouseArea {
             id: mouse
             anchors.fill: parent; drag.target: parent
             drag.axis: Drag.YAxis; drag.minimumY: 2; drag.maximumY: slider.yMax+2
             onPositionChanged: { value = (maximum - minimum) * (handle.y-2) / slider.yMax + minimum; }
         }
     }
 }
