#include "busstopparser.h"
#include <QString>
#include <QRegularExpression>
#include <QTextStream>

BusStopParser::BusStopParser() : QObject()
{
    file = new QFile(filePath);

    watcher.addPath(filePath);
    QObject::connect(&watcher, &QFileSystemWatcher::fileChanged,
                     this, &BusStopParser::FileChanged);
}

BusStopParser::~BusStopParser()
{
    file->close();
    delete file;
}

bool BusStopParser::openFile()
{
    if(!file->open(QIODevice::ReadOnly))
        return false;

    file->reset();
    return true;
}

void BusStopParser::Parse()
{
    if (!openFile())
        return;

    currentSection = Section::STOP;

    QTextStream text(file);
    text.setCodec("UTF-8");

    while (!text.atEnd())
    {
        QString line = text.readLine();
        switch (currentSection)
        {
            case Section::STOP:
                parseStop(line);
                break;
            case Section::LINE:
                parseLine(line);
                break;
            case Section::DEPARTURE:
                parseDeparture(line);
                break;
        }
    }

    file->close();
    adapter->end();
}

void BusStopParser::parseStop(const QString &line)
{
    QRegularExpression regx("PRZYSTANEK:(\\d+);(.+?);(.+?);(\\d+)");
    QRegularExpressionMatch match = regx.match(line);
    if (match.hasMatch())
    {
        // [1] = stopID
        // [2] = stop name
        // [3] = direction
        // [4] = number of Lines

        int stopID = match.captured(1).toInt();

        numberOfLines = match.captured(4).toInt();
        counterLine = 0;
        currentStop = stopID;

        currentSection = Section::LINE;
        adapter->addBus(stopID, match.captured(2), match.captured(3));
    }
}

void BusStopParser::parseLine(const QString &line)
{
    QRegularExpression regx("LINIA:(.+?);(\\d+)");
    QRegularExpressionMatch match = regx.match(line);

    if (match.hasMatch())
    {
        // [1] lineID
        // [2] number of departures

        int lineID = match.captured(1).toInt();

        currentLine = lineID;
        numberOfDeparture = match.captured(2).toInt();
        counterDeparture = 0;
        currentSection = Section::DEPARTURE;

        adapter->addLine(lineID, numberOfDeparture);
    }
}

void BusStopParser::parseDeparture(const QString &line)
{
    QRegularExpression regx("ODJAZD:(.+?);(.+)");
    QRegularExpressionMatch match = regx.match(line);

    if (match.hasMatch())
    {
        // [1] = time
        // [2] = delay

        adapter->addDeprature(match.captured(1), match.captured(2).toInt());
    }

    counterDeparture++;
    if (counterDeparture >= numberOfDeparture)
    {
        counterLine++;
        if (counterLine >= numberOfLines)
            currentSection = Section::STOP;
        else
            currentSection = Section::LINE;
    }
}

void BusStopParser::setAdapter(BusStopAdapter* adap)
{
    adapter = adap;
}


void BusStopParser::FileChanged(const QString& name)
{
    if (name == filePath)
        Parse();
}
