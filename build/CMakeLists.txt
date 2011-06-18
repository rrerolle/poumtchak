CMAKE_MINIMUM_REQUIRED ( VERSION 2.6 )

PROJECT ( PoumTchak C CXX )

# -- Qt 4.7.0 minimum --
FIND_PACKAGE ( Qt4 4.7.0 COMPONENTS QtCore QtGui QtDeclarative Phonon REQUIRED )
# -- Configure Qt for PantinStudio --
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
	"C:/Qt/2010.05/qt/lib/libQtDeclaratived4.a"
	"C:/Qt/2010.05/qt/lib/libQtMultimediad4.a"
	${SDL_LIBRARY} ${SDLMIXER_LIBRARY}
)
