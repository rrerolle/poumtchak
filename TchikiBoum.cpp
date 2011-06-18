/*
 * 	Copyright (c) 2010-2011, Romuald CARI
 *	All rights reserved.
 *
 *	Redistribution and use in source and binary forms, with or without
 *	modification, are permitted provided that the following conditions are met:
 *		* Redistributions of source code must retain the above copyright
 *		  notice, this list of conditions and the following disclaimer.
 *		* Redistributions in binary form must reproduce the above copyright
 *		  notice, this list of conditions and the following disclaimer in the
 *		  documentation and/or other materials provided with the distribution.
 *		* Neither the name of the <organization> nor the
 *		  names of its contributors may be used to endorse or promote products
 *		  derived from this software without specific prior written permission.
 *
 *	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *	DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 *	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "TchikiBoum.hpp"
using namespace poumtchak;

#include <QtCore/QMutexLocker>

#include "SDL.h"

TchikiBoum::TchikiBoum()
: 	_referenceLoopBytesPassed(0),
 	_referenceLoopCounter(0),
 	_referenceLoopMultiplier(2),
 	_referenceLoopChannel(-1)
{
	if( SDL_Init(SDL_INIT_AUDIO) != 0 )
	{
		qFatal("Failed to initialize SDL with audio.");
		return;
	}
	qDebug("Initialized SDL audio.");

	if( Mix_Init(0) != 0 )
	{
		qFatal("Failed to initialize SDL_mixer.");
		return;
	}
	qDebug("Initialized SDL_mixer");

	if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != 0 )
	{
		qFatal("Failed to open audio device for 44.1KHz 16bit Stereo.");
		return;
	}
	qDebug("Initialized audio device for 44.1KHz 16bit Stereo.");

	setChannelsNumber(64);

	Mix_SetPostMix(DummyEffect, this);
}

TchikiBoum::~TchikiBoum()
{
	clearLoops();
	clearSamples();

	qDebug("Cleaning up SDL_mixer and SDL.");
	Mix_Quit();
	SDL_Quit();
}

int TchikiBoum::addSample(const QString& path)
{
	Mix_Chunk* sample = Mix_LoadWAV(qPrintable(path));

	if(!sample)
		qWarning("Can't load sample: %s", qPrintable(path));

	_samples.append(sample);

	return _samples.size() - 1;
}

void TchikiBoum::clearSamples()
{
	for(int i = 0; i < _samples.size(); i++)
	{
		Mix_FreeChunk( _samples.at(i) );
	}
	_samples.clear();
}

int TchikiBoum::addLoop(const QString& path)
{
	Mix_Chunk* loop = Mix_LoadWAV(qPrintable(path));

	if(!loop)
	{
		qWarning("Can't load loop: %s / %s", qPrintable(path), Mix_GetError());
		return -1;
	}

	_loops.append(loop);
	_loopsChannels.append(-2);

	return _loops.size() - 1;
}

void TchikiBoum::setLoopVolume(int loop, int volume)
{
	int channel = _loopsChannels.at(loop);
	if(channel == -2)
	{
		qWarning("Loop #%d is not playing, cannot set volume !", loop);
		return;
	}

	Mix_Volume(channel, volume);
}

void TchikiBoum::clearLoops()
{
	for(int i = 0; i < _loops.size(); i++)
	{
		Mix_FreeChunk( _loops.at(i) );
	}
	_loops.clear();
	_loopsChannels.clear();
}

void TchikiBoum::setChannelsNumber(int channelsNb)
{
	Mix_AllocateChannels(channelsNb);
}

void TchikiBoum::setReferenceLoop(int loop)
{
	_referenceLoopChunk = _loops.at(loop);
	Mix_HaltChannel(_referenceLoopChannel);
	_referenceLoopChannel = Mix_PlayChannel(_referenceLoopChannel, _referenceLoopChunk, -1); // Loop forever...
	qDebug("Starting reference loop %d @ channel %d", loop, _referenceLoopChannel);
	if(_referenceLoopChannel == -1)
	{
		 qWarning("Reference loop error: %s", Mix_GetError());
		 return;
	}
	// Mute the channel !
	Mix_Volume(_referenceLoopChannel, 0);
	//Mix_RegisterEffect(_referenceLoopChannel, DummyEffect, NULL, this);
}

void TchikiBoum::setReferenceLoopMultiplier(int factor)
{
	_referenceLoopMultiplier = factor;
}

void TchikiBoum::playSample(int id)
{
	Mix_PlayChannel(-1, _samples.value(id), 0);
}

void TchikiBoum::playLoop(int loop)
{
	Mix_Chunk* chunk = _loops.at(loop);
	int channel = Mix_PlayChannel(-1, chunk, -1); // Loop till the end !
	if(channel == -1)
	{
		 qDebug("Mix_PlayChannel: %s / Chunk: %p", Mix_GetError(), chunk);
		 return;
	}
	Mix_Pause(channel);
	qDebug("Starting %d @ channel %d", loop, channel);
	_loopsChannels.replace(loop, channel);

	//_loopsToStart.append(channel);
}

void TchikiBoum::stopLoop(int id)
{
	_loopsToStop.append(id);
}

void TchikiBoum::processLoops()
{
	qDebug("Loop Stuff to do !");

	// Stop loops...
	while(!_loopsToStop.isEmpty())
	{
		int loop = _loopsToStop.takeLast();
		qDebug("Stopping %d", loop);
		int channel = _loopsChannels.at(loop);
		_loopsChannels.replace(loop, -2);
		Mix_HaltChannel(channel);
	}

	// Start all paused loops...
	Mix_Pause(-1); // Pause all for synchro...
	Mix_Resume(-1);

	qDebug("Done with loops !");
}

void TchikiBoum::checkReferenceLoop(int len)
{
	_referenceLoopBytesPassed += len;

	if(_referenceLoopBytesPassed >= _referenceLoopChunk->alen)
	{
		_referenceLoopBytesPassed = _referenceLoopChunk->alen - _referenceLoopBytesPassed;
		_referenceLoopCounter++;
		qDebug("Sub-tick #%d",	_referenceLoopCounter);
	}

	if(_referenceLoopCounter == _referenceLoopMultiplier)
	{
		// Reset counter
		_referenceLoopCounter = 0;

		// Start the samples, stop the others in the main loop...
		//_Instance->_processLoopsFlag = true;
		processLoops();

		// Signal !
		emit referenceTick();
	}
}

void TchikiBoum::DummyEffect(void *udata, unsigned char *stream, int len)
{
	TchikiBoum* instance = reinterpret_cast<TchikiBoum*>(udata);

	//Q_ASSERT(chan == instance->_referenceLoopChannel);

	instance->checkReferenceLoop(len);
}
