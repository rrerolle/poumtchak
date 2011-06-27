#include <QtCore/QObject>
#include <QtCore/QStringList>
#include <sndfile.h>
#include <stdlib.h>

#include "Sample.hpp"


using namespace poumtchak;

Sample::Sample(QString name, int nloops)
{
    filename = "samples/" + name + ".wav";
    loops = nloops;
    playing = false;
    load();
}

int Sample::load()
{
    SF_INFO fileinfo;
    SNDFILE *sndfile;
    unsigned int i;
    unsigned int nread;


    sndfile = sf_open(filename, SFM_READ, &fileinfo);

    if (!sndfile)
        return -1;

    pos = 0;
    size = fileinfo.frames*2;
    data = (short *)malloc(size*sizeof(short));

    if (!data) {
        sf_close(sndfile);
        printf("Not enough memory!\n");
        return -1;
    }
    for (i = 0; i < size; i+=nread) {
        nread = sf_read_short(sndfile, data+i, 4096);
    }

    sf_close(sndfile);
    printf("Loaded %s\n", filename.toAscii().constData());
    return 0;
}

void Sample::play(int offset)
{
    if (loops != 0) {
        pos = offset;
    }
    else {
        pos = 0;
    }
    playing = true;
}

void Sample::pause()
{
    playing = false;
}

void Sample::release()
{
    if (data != NULL) {
        free(data);
        data = NULL;
    }
}

