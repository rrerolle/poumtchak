#include <QtCore/QObject>
#include <QtCore/QHash>

namespace poumtchak {

class Sample : public QObject
{
	Q_OBJECT

public:
	Sample(QString name, int loops);
	int load();
        void release();

public slots:
	void play(int offset);
	void pause();

public:
        QString filename;
        bool done;
        int loops;
        int pos;
        int size;
        bool playing;
        short *data;
};

}

