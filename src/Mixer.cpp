#include <QtCore/QStringList>
#include <QtGui/QApplication>
#include <sndfile.h>

#include "Mixer.hpp"
using namespace poumtchak;

#define error_check(err) \
    do {\
        if (err) { \
            fprintf(stderr, "line %d ", __LINE__); \
            fprintf(stderr, "error number: %d\n", err); \
            fprintf(stderr, "\n\t%s\n\n", Pa_GetErrorText(err)); \
            return err; \
        } \
    } while (0)


static int
output_callback(const void *input,
          void *output,
          unsigned long frames_per_buffer,
          const PaStreamCallbackTimeInfo *time_info,
          PaStreamCallbackFlags flags,
          void *data)
{
    short *output_buffer = (short *)output;
    Mixer *mixer = (Mixer *)data;
    (void) data;
    (void) input;
    (void) time_info;
    (void) flags;
    unsigned int i;
    for (i = 0; i < frames_per_buffer*2; i++) {
        int outval = 0;
        QHash<QString, Sample*>::const_iterator j = mixer->samples.constBegin();
        while (j != mixer->samples.constEnd()) {
            Sample *sample = (Sample *)j.value();
            if (sample->pos >= sample->size) {   
                if (sample->loops != 0) {
                    sample->pos = 0; 
                    sample->loops = sample->loops == -1 ? -1:sample->loops-1;
                }
                else {
                    sample->playing = false;
                }
            }
            if (sample->playing)
                outval += sample->data[sample->pos++];
            j++;
        }
        if (outval > 32767)
            outval = 32767;
        else if (outval < -32767)
            outval = -32767;
        *output_buffer++ = outval;
        mixer->nframes++;
    }
    return 0;
}

Mixer::Mixer()
{
}

int Mixer::initialize()
{
    PaStreamParameters out_param;
    PaError err;
    SNDFILE *file;
    SF_INFO sfinfo;

    err = Pa_Initialize();
    error_check(err);

    out_param.device = Pa_GetDefaultOutputDevice();
    if (out_param.device == paNoDevice) {
        fprintf(stderr, "Haven't found an audio device!\n");
        return -1;
    }

    out_param.channelCount = 2;
    out_param.sampleFormat = paInt16;
    out_param.suggestedLatency = Pa_GetDeviceInfo(out_param.device)->defaultLowOutputLatency;
    out_param.hostApiSpecificStreamInfo = NULL;

    err = Pa_OpenStream(
        &stream,
        NULL,
        &out_param,
        44100,
        paFramesPerBufferUnspecified,
        paClipOff,
        output_callback,
        this);
    error_check(err);
}

int Mixer::start()
{
    PaError err;
    nframes = 0;
    err = Pa_StartStream(stream);
    error_check(err);
}

int Mixer::stop()
{
    PaError err;
    err = Pa_StopStream(stream);
    error_check(err);
}

int Mixer::close()
{
    PaError err;
    err = Pa_CloseStream(stream);
    error_check(err);
}

void Mixer::play(QString name)
{
    Sample *sample;
    int offset;
    bool playing = false;
    QHash<QString, Sample*>::const_iterator i = samples.constBegin();
    while (i != samples.constEnd()) {
        sample = (Sample *)i.value();
        if (sample->playing && sample->loops!=0) {
            playing = true;
            break;
        }
        i++;
    }
    sample = samples[name];
    if (playing) {
        offset = nframes % sample->size;
    }
    else {
        nframes = 0;
        offset = 0;
    }
    if (sample->loops && sample->playing)
        sample->pause();
    else
        sample->play(offset);
}

void Mixer::load_samples()
{
    QStringList sample_names;
    Sample *sample;

    sample_names << "crash" << "hihat" << "kick" << "snare";
    for(int i = 0; i < sample_names.size(); i++)
    {
        sample = new Sample(sample_names.at(i), 0);
        samples.insert(sample_names.at(i), sample);
    }
    QStringList loop_names;
    loop_names << "drums" << "bass" << "guitar1" << "guitar2";
    for(int i = 0; i < loop_names.size(); i++)
    {
        sample = new Sample(loop_names.at(i), -1);
        samples.insert(loop_names.at(i), sample);
    }
}

void Mixer::exit()
{
    printf("Stopping Pa\n");
    stop();
    QHash<QString, Sample*>::const_iterator i = samples.constBegin();
    while (i != samples.constEnd()) {
        Sample *sample = (Sample *)i.value();
        sample->release();
        printf("Released %s\n", i.key().toAscii().constData());
        i++;
    }
    printf("Closing Pa\n");
    close();
    printf("Terminating Pa\n");
    Pa_Terminate();
    printf("Quiting\n");
    qApp->quit();
}
