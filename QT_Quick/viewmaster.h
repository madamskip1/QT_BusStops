#ifndef TESTCLASS_H
#define TESTCLASS_H
#include <QString>
#include <QObject>
#include <QQmlContext>
#include "proxymodel.h"

class ViewMaster : public QObject
{
    Q_OBJECT
public:
    explicit ViewMaster(QObject *parent = nullptr);
    void setProxy(ProxyModel * prox);

public slots:
    void stopBusClicked(QString id);
    void lineClicked(QString lineID);
    void backButtonClicked();
    ProxyModel * getProxy();
    void setCtx(QQmlContext * ctx);
private:
    ProxyModel * proxy;
    TreeModel * model;
    QQmlContext * context;
};

#endif // TESTCLASS_H
