#include <QVector>
#include <QVariant>
#include <QDebug>
#include "busstopadapter.h"

BusStopAdapter::BusStopAdapter()
{
    first = true;
}

void BusStopAdapter::setModel(TreeModel *_model)
{
    model = _model;
}

void BusStopAdapter::addBus(int id, const QString &name, const QString &direct)
{
    if (!first)
    {

        curStop = model->getBus(id);

        if (curStop.isValid())
            return;

    }
    curStop = model->addBusStop({id, name, direct});
}

void BusStopAdapter::addLine(int id, int departures)
{
    if (!first)
    {

        curLine = model->getLine(curStop, id);

        if (curLine.isValid())
            return;
    }

    curLine = model->addLine(curStop, {"Linia: " + QString::number(id), "Odjazdów: " + QString::number(departures)});
}

void BusStopAdapter::addDeprature(QString time, int delay)
{
    QString stringDelay;

    if (delay < 0)
        stringDelay = "Nie wyruszył";
    else if (delay > 0)
        stringDelay = "Opóźnienie: " + QString::number(delay) + " min";
    else
        stringDelay = "Brak opóźnienia";
    QString str;

    if (!first)
    {
        QModelIndex dep = model->getDeparture(curLine, time);
        dep = model->index(dep.row(), 1, dep.parent());

        if (dep.isValid())
        {
            str = model->data(dep).toString();

            if (str.compare(stringDelay) != 0)
                model->editDeparture(dep, stringDelay);

            return;
        }
    }
    model->addDeparture(curLine, {time, stringDelay});
}

void BusStopAdapter::end()
{
    first = false;
    model->calculateTime();
    model->edited();

}
