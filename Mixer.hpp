#include <QtCore/QObject>
#include <QtCore/QHash>
#include <portaudio.h>

#include "Sample.hpp"

namespace poumtchak {

class Mixer : public QObject
{
	Q_OBJECT

public:
	Mixer();
        int initialize();
	void load_samples();
	int start();
	int stop();
	int close();
        QHash<QString,Sample *> samples;
        int nframes;

public slots:
        void play(QString name);
        void exit();

private:
        PaStream *stream;
};

}

