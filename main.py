#!/usr/bin/python
# -*- coding: utf-8 -*-

from PySide import QtCore, QtGui, QtDeclarative
from QtMobility.Sensors import *
from PySide.phonon import Phonon

class Drummer(QtCore.QObject):
    def __init__(self):
        super(Drummer, self).__init__()
        self.medias = {}
        self.samples = {}
        self.outputs = {}
        self.load_samples()

    def load_samples(self):
        for name in ['kick', 'hihat', 'snare', 'crash']:
            self.medias[name] = Phonon.MediaObject(self)
            self.samples[name] = Phonon.MediaSource("samples/%s.wav" % name)
            self.outputs[name] = Phonon.AudioOutput(Phonon.MusicCategory, self)
            Phonon.createPath(self.medias[name], self.outputs[name])

    @QtCore.Slot(str)
    def play(self, name):
        self.medias[name].setCurrentSource(self.samples[name])
        self.medias[name].play()

    @QtCore.Slot()
    def exit(self):
        # Assume success
        QtGui.QApplication.quit()

class RotationFilter(QRotationFilter):
    stamp = 0

    def filter(self, reading):
        diff = ( reading.timestamp() - self.stamp )
        stamp = reading.timestamp()
        print "Rotation: %.2f x" % reading.x(),  " %.2f y" % reading.y(),  " %.2f z" % reading.z(), " (%.2f ms since last, " % (diff / 1000),  "%.2f Hz)" % (1000000.0 / diff)
        return True

class Rotation(QRotationSensor):

    def __init__(self):
        super(Rotation, self).__init__()
        self.addFilter(RotationFilter())
        self.state = "Portrait"

if __name__ == '__main__':
    import sys

    app = QtGui.QApplication(sys.argv)
    app.setApplicationName("Poumtchak")

    view = QtDeclarative.QDeclarativeView()

    rotation = Rotation()
    rotation.start()

    if not rotation.isActive():
        QtCore.qWarning("Rotationsensor didn't start!")
        exit()

    if rotation.property("hasZ"):
        if rotation.property("hasZ"):
            QtCore.qDebug("Sensor hasZ is set")
        else:
            QtCore.qDebug("Sensor hasZ is NOT set")
    else:
        QtCore.qDebug("Sensor hasZ error: no value")

    drummer = Drummer()

    context = view.rootContext()
    context.setContextProperty("drummer", drummer)
    context.setContextProperty("Rotation", "Portrait" )
    context.setContextProperty("screenWidth", 400);
    context.setContextProperty("screenHeight", 100);

    view.setSource(QtCore.QUrl('main.qml'))
    view.setResizeMode(QtDeclarative.QDeclarativeView.SizeRootObjectToView)
    view.showFullScreen()
    #view.show()

    sys.exit(app.exec_())

