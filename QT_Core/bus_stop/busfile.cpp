#include <QDebug>
#include "busfile.h"

BusFile::BusFile() : QObject()
{
    watcher.addPath("C:/Programowanie/PainQT/bus_stop");
    QObject::connect(&watcher, &QFileSystemWatcher::directoryChanged,
                     this, &BusFile::DirChanged);
    qDebug() << "COS";
}

BusFile::~BusFile()
{
}

void BusFile::DirChanged()
{
    qDebug() << "DUPA";
}
