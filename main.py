#!/usr/bin/python
# -*- coding: utf-8 -*-

from PySide import QtCore, QtGui, QtDeclarative
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
        QtGui.QApplication.quit()

if __name__ == '__main__':
    import sys

    app = QtGui.QApplication(sys.argv)
    app.setApplicationName("Poumtchak")

    view = QtDeclarative.QDeclarativeView()


    drummer = Drummer()

    context = view.rootContext()
    context.setContextProperty("drummer", drummer)
    context.setContextProperty("screenWidth", 800);
    context.setContextProperty("screenHeight", 600);

    view.setSource(QtCore.QUrl('main.qml'))
    view.setResizeMode(QtDeclarative.QDeclarativeView.SizeRootObjectToView)
#    view.showFullScreen()
    view.show()

    sys.exit(app.exec_())

