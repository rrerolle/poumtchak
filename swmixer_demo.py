#!/usr/bin/python
# -*- coding: utf-8 -*-

import swmixer
import time

SAMPLERATE = 48000
CHUNKSIZE = 2048
STEREO = True

class Track(object):
    def __init__(self, name):
        self.sound = swmixer.Sound("samples/%s.wav" % name)
        self.length = self.sound.get_length()
        self.active = False

    def play(self, volume=1.0, offset=0, fadein=0, envelope=None, loops=0):
        self.channel = self.sound.play(volume, offset, fadein, envelope, loops)
        self.active = True

    def get_position(self):
        return self.channel.get_position()

    def pause(self):
        self.active = False
        return self.channel.pause()

    def unpause(self):
        self.active = True
        return self.channel.unpause()

    def is_done(self):
        return self.get_position() + 2*CHUNKSIZE > self.length

swmixer.init(samplerate=48000, chunksize=2048, stereo=True)

tracks = {}

for track_name in [
    'track_drums',
    'track_bass',
    'track_guitar1',
    'track_guitar2',
]:
    tracks[track_name] = Track(track_name)

tracks['track_drums'].play(loops=-1)

try:
    while True:
        tick = swmixer.tick()
        if tracks['track_drums'].is_done():
            if not tracks['track_bass'].active:
                tracks['track_bass'].play(loops=-1)
            elif not tracks['track_guitar1'].active:
                tracks['track_guitar1'].play(loops=-1)
            elif not tracks['track_guitar2'].active:
                tracks['track_guitar2'].play(loops=-1)
        time.sleep(0.001)
except KeyboardInterrupt:
    pass
