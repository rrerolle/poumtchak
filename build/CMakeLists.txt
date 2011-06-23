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




# -- Qt 4.7.0 minimum --
FIND_PACKAGE ( Qt4 4.7.0 COMPONENTS QtCore QtGui QtDeclarative Phonon REQUIRED )
SET ( QT_USE_QTCORE ON )
SET ( QT_USE_QTGUI ON )
SET ( QT_USE_QTDECLARATIVE ON )
SET ( QT_USE_PHONON ON )
INCLUDE ( ${QT_USE_FILE} )

FIND_PACKAGE ( SDL 1.2 )
FIND_PACKAGE ( SDL_mixer 1.2 )




INCLUDE_DIRECTORIES( ${SDL_INCLUDE_DIR} ${SDLMIXER_INCLUDE_DIR} )

### ------------- MOC --------------
QT4_WRAP_CPP ( MOC_SRCS ../Drummer.hpp ../ITchikiBoum.hpp )

ADD_EXECUTABLE ( PoumTchak ${MOC_SRCS} ../main.cpp ../Drummer.cpp ../TchikiBoum.cpp ../test.cpp )

TARGET_LINK_LIBRARIES ( 
	PoumTchak
	${QT_LIBRARIES}
	${SDL_LIBRARY} ${SDLMIXER_LIBRARY}
    ${QT_MOBILITY_MULTIMEDIAKIT_LIBRARY}
)
