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

#include <QtCore/QBuffer>
#include <QtCore/QFile>

#include <QtMultimedia/QAudioOutput>

#include <SDL_mixer.h>

void test()
{
	Mix_Chunk* loop = Mix_LoadWAV("samples/DRUMLOOP001_TECH_125_X_SC4.wav");

	QAudioFormat format;
	 // Set up the format, eg.
	 format.setFrequency(44100);
	 format.setChannels(2);
	 format.setSampleSize(16);
	 format.setCodec("audio/pcm");
	 format.setByteOrder(QAudioFormat::LittleEndian);
	 format.setSampleType(QAudioFormat::SignedInt);

	 QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
	if (!info.isFormatSupported(format)) {
		qWarning("raw audio format not supported by backend, cannot play audio.");
		return;
	}

	QAudioOutput* output = new QAudioOutput(format);
	QBuffer* buffer = new QBuffer();
	buffer->setData((char*)(loop->abuf), loop->alen);
	buffer->open(QBuffer::ReadOnly);

	QFile* file = new QFile("samples/DRUMLOOP001_TECH_125_X_SC4.wav");
	file->open(QFile::ReadOnly);

	qDebug("File %lld / %lld", file->size(), buffer->size());

	output->start(buffer);
	qDebug("Error code: %d", (int)output->error());
}
