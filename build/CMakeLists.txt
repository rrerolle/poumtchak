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

MESSAGE ( "Libraries... ${QT_LIBRARIES}" )

### ------------- MOC --------------
QT4_WRAP_CPP ( MOC_SRCS ../Drummer.hpp )

ADD_EXECUTABLE ( PoumTchak ${MOC_SRCS} ../main.cpp ../Drummer.cpp )

TARGET_LINK_LIBRARIES ( PoumTchak ${QT_LIBRARIES} "C:/Qt/2010.05/qt/lib/libQtDeclaratived4.a" )
