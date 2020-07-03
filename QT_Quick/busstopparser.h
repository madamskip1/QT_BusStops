#ifndef BUSSTOPPARSER_H
#define BUSSTOPPARSER_H

#include <QFile>
#include <QFileSystemWatcher>
#include <QObject>
#include "busstopadapter.h"

enum class Section
{
    STOP,
    LINE,
    DEPARTURE
};

class BusStopParser : public QObject
{
    Q_OBJECT
public:
    BusStopParser();
    ~BusStopParser();

    void setAdapter(BusStopAdapter* adap);
    void Parse();

public slots:
    void FileChanged(const QString &name);

private:
    const QString filePath = "C:/Programowanie/QtQuickEmpty/bus_stop.txt";

    QFile* file;
    QFileSystemWatcher watcher;
    Section currentSection;
    BusStopAdapter * adapter;

    int currentStop;
    int numberOfLines;
    int currentLine;
    int counterLine;
    int numberOfDeparture;
    int counterDeparture;

    void parseStop(const QString &line);
    void parseLine(const QString &line);
    void parseDeparture(const QString &line);

    bool openFile();
};

#endif // BUSSTOPPARSER_H
