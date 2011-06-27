CMAKE_MINIMUM_REQUIRED ( VERSION 2.6 )
set(CMAKE_BUILD_TYPE Debug)


PROJECT ( PoumTchak C CXX )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/)

set(QTMOBILITY_MKSPEC_VERSION "11")

find_package(Qt4 REQUIRED)
find_package(QtMobility)


if (QT_MOBILITY_FOUND)
  message(STATUS "Found QtMobility ${QT_MOBILITY_VERSION}")
endif()

if (QT_MOBILITY_FOUND)
    include_directories(${QT_MOBILITY_INCLUDE_DIR})
    link_directories(${QT_MOBILITY_LIBRARY_DIR})
endif()

if (QT_MOBILITY_MULTIMEDIAKIT_FOUND)
    include_directories(${QT_MOBILITY_MULTIMEDIAKIT_INCLUDE_DIR})
    link_directories(${QT_MOBILITY_MULTIMEDIAKIT_LIBRARY})
endif()

 # and finally an resource file
  SET( SAMPLE_RCS
       ../resources.qrc
  )
  # by default only QtCore and QtGui modules are enabled
  # other modules must be enabled like this:
  SET( QT_USE_QT3SUPPORT TRUE )   
  SET( QT_USE_QTXML TRUE )
  # this command finds Qt4 libraries and sets all required variables
  # note that it's Qt4, not QT4 or qt4
  # add some useful macros and variables
  # (QT_USE_FILE is a variable defined by FIND_PACKAGE( Qt4 ) that contains a path to CMake script)
  # this command will generate rules that will run rcc on all files from SAMPLE_RCS
  # in result SAMPLE_RC_SRCS variable will contain paths to files produced by rcc
  QT4_ADD_RESOURCES( SAMPLE_RC_SRCS ${SAMPLE_RCS} )

  SET( SAMPLE_UIS
    Pad.qml 
    ExitButton.qml 
    Loop.qml 
    Slider.qml 
    screen.qml 
    Sound.qml 
    MainWindow.qml 
    arrow.png
  )
# -- Qt 4.7.0 minimum --
FIND_PACKAGE ( Qt4 4.7.0 COMPONENTS QtCore QtGui QtDeclarative REQUIRED )
SET ( QT_USE_QTCORE ON )
SET ( QT_USE_QTGUI ON )
SET ( QT_USE_QTDECLARATIVE ON )
INCLUDE ( ${QT_USE_FILE} )

FIND_PACKAGE ( sndfile )
FIND_PACKAGE ( portaudio )

### ------------- MOC --------------
QT4_WRAP_CPP ( MOC_SRCS ../Sample.hpp ../Mixer.hpp )

ADD_EXECUTABLE ( PoumTchak ${MOC_SRCS} ../main.cpp ../Sample.cpp ../Mixer.cpp ${SAMPLE_RC_SRCS})

TARGET_LINK_LIBRARIES ( 
	PoumTchak
	${QT_LIBRARIES}
    ${QT_MOBILITY_MULTIMEDIAKIT_LIBRARY}
    ${PORTAUDIO_LIBRARIES}
    ${SNDFILE_LIBRARY}
)
