CMAKE_MINIMUM_REQUIRED  (VERSION 2.6)
SET                     (CMAKE_BUILD_TYPE Debug)

PROJECT                 (poumtchak C CXX)

SET                     (CMAKE_MODULE_PATH
                            ${CMAKE_MODULE_PATH}
                            ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules
                        )

FIND_PACKAGE            (Qt4 REQUIRED)

SET                     (SAMPLE_RCS resources/resources.qrc)
QT4_ADD_RESOURCES       (SAMPLE_RC_SRCS ${SAMPLE_RCS})

FIND_PACKAGE            (Qt4 4.7.0 COMPONENTS QtCore QtGui QtDeclarative REQUIRED)
SET                     (QT_USE_QTCORE ON)
SET                     (QT_USE_QTGUI ON)
SET                     (QT_USE_QTDECLARATIVE ON)
INCLUDE                 (${QT_USE_FILE})

FIND_PACKAGE            (sndfile REQUIRED)
FIND_PACKAGE            (portaudio REQUIRED)

SET                     (POUMTCHAK_SRC
                            "src/main.cpp"
                            "src/Sample.cpp"
                            "src/Mixer.cpp"
                        )
SET                     (POUMTCHAK_MOC
                            "include/Sample.hpp"
                            "include/Mixer.hpp"
                        )

INCLUDE_DIRECTORIES     ("include")

QT4_WRAP_CPP            (MOC_SRCS ${POUMTCHAK_MOC})

ADD_EXECUTABLE          (poumtchak
                            ${MOC_SRCS}
                            ${POUMTCHAK_SRC}
                            ${SAMPLE_RC_SRCS}
                        )

TARGET_LINK_LIBRARIES   (poumtchak
                            ${QT_LIBRARIES}
                            ${PORTAUDIO_LIBRARIES}
                            ${SNDFILE_LIBRARY}
                        )
