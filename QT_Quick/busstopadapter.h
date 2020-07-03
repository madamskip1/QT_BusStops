#ifndef BUSSTOPADAPTER_H
#define BUSSTOPADAPTER_H

#include <QString>

#include "treemodel.h"
#include "treenode.h"

class BusStopAdapter
{
public:
    BusStopAdapter();

    void setModel(TreeModel* _model);
    void addBus(int id, const QString &name, const QString &direct);
    void addLine(int id, int departures);
    void addDeprature(QString time, int delay);
    void end();

private:
    bool first;
    TreeModel * model;
    QModelIndex curStop;
    QModelIndex curLine;
};

#endif // BUSSTOPADAPTER_H
