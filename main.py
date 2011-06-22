#!/usr/bin/python
# -*- coding: utf-8 -*-

from PySide import QtCore, QtGui, QtDeclarative
import swmixer


class Drummer(QtCore.QObject):
    def __init__(self):
        super(Drummer, self).__init__()
        self.medias = {}
        self.samples = {}
        self.outputs = {}
        self.load_samples()

    def load_samples(self):
        swmixer.init(samplerate=44100, chunksize=128, stereo=True)
        for name in ['kick_16', 'hihat_16', 'snare_16', 'crash_16']:
            self.medias[name] = swmixer.Sound("samples/%s.wav" % name)
        swmixer.start()
        timer = QtCore.QTimer(self)
        self.connect(timer, QtCore.SIGNAL("tick()"), self.tick)
        timer.start(10)

    @QtCore.Slot(str)
    def play(self, name):
        self.medias[name].play()

    @QtCore.Slot()
    def exit(self):
        QtGui.QApplication.quit()

    @QtCore.Slot()
    def tick(self):
        swmixer.tick()

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

