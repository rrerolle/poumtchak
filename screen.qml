import Qt 4.7

Rectangle{
    id: screen
    width: screenWidth
    height: screenHeight
    anchors.centerIn: parent
    color: "grey"

    property int partition: height/3

     MainWindow{
         id: mainwindow
         height: partition*3
         width: parent.width
         color:  screen.color
     }

     Sound{
         id:sound
         anchors.bottom:parent.bottom
         color: "darkgrey"
         height: 0
         width:parent.width
     }

     Rectangle{
          id:drawer
          height:15
          width: screen.width
          state: "DRAWER_CLOSED"
          y: partition*3 - drawer.height
          color: "black"

          Image{
              id: arrowIcon
              source: "qrc:/arrow.png"
              anchors.horizontalCenter: parent.horizontalCenter
          }

          gradient: Gradient {
              GradientStop { position: 0.0; color: "darkgrey" }
              GradientStop { position: 1.0; color: "black" }
          }

          MouseArea{
              id: drawerMouseArea
              anchors.fill:parent
              onClicked:{
                  if (drawer.state == "DRAWER_CLOSED"){
                      drawer.state = "DRAWER_OPEN"
                  }
                  else if (drawer.state == "DRAWER_OPEN"){
                      drawer.state = "DRAWER_CLOSED"
                  }
              }
          }

          states:[
               State {
                   name: "DRAWER_CLOSED"
                   PropertyChanges { target: mainwindow; height: partition*3 }
                   PropertyChanges { target: sound; height: 0 }
                   PropertyChanges { target: drawer; y: (partition*3 - drawer.height) }
                   PropertyChanges { target: arrowIcon; rotation: 180 }
               },
               State {
                   name: "DRAWER_OPEN"
                   PropertyChanges { target: mainwindow; height: partition*2; }
                   PropertyChanges { target: sound; y: (partition*2 + drawer.height); height: partition }
                   PropertyChanges { target: drawer; y: partition*2 }
                   PropertyChanges { target: arrowIcon; rotation: 0 }
               }
           ]
      }
 }
