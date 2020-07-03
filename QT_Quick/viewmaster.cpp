#include "viewmaster.h"
#include <QDebug>

ViewMaster::ViewMaster(QObject *parent) : QObject(parent)
{

}

void ViewMaster::stopBusClicked(QString id)
{
    QModelIndex bus = model->getBus(id.toInt());
    proxy->setParent(bus);
}

void ViewMaster::lineClicked(QString lineID)
{
    lineID = lineID.remove(0, 7);
    QModelIndex line = model->getLine(proxy->getParent(), lineID.toInt());
    proxy->setParent(line);
}

void ViewMaster::backButtonClicked()
{
    proxy->setParent(proxy->getParent().parent());
}

void ViewMaster::setProxy(ProxyModel * prox)
{
    proxy = prox;
    model = proxy->getModel();
}

ProxyModel * ViewMaster::getProxy()
{
    return proxy;
}

void ViewMaster::setCtx(QQmlContext *ctx)
{
    context = ctx;
}
