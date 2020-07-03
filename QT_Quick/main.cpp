#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include <qqml.h>
#include <qqmlcontext.h>
#include <QtQuick/qquickitem.h>
#include <QtQuick/qquickview.h>
#include <QDebug>
#include "treemodel.h"
#include "busstopadapter.h"
#include "busstopparser.h"
#include "viewmaster.h"
#include "proxymodel.h"



int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);


    TreeModel * model = new TreeModel();
    BusStopAdapter * adapter = new BusStopAdapter();
    adapter->setModel(model);
    BusStopParser * parser = new BusStopParser();
    parser->setAdapter(adapter);
    parser->Parse();

    ProxyModel * prox = new ProxyModel();
    prox->setModel(model);

    ViewMaster viewMaster;
    viewMaster.setProxy(prox);


    // stackView
    QQuickView stackView;
    stackView.setTitle("Rozkład autobusowy");
    stackView.setResizeMode(QQuickView::SizeRootObjectToView);
    QQmlContext * context = stackView.rootContext();
    context->setContextProperty("myModel", prox);
    context->setContextProperty("viewMaster", &viewMaster);
    stackView.setSource(QUrl("qrc:/main.qml"));
    stackView.show();


    // Tree view
    QQuickView viewTree;
    viewTree.setTitle("Rozkład autobusowy");
    viewTree.setResizeMode(QQuickView::SizeRootObjectToView);
    QQmlContext * contextTree = viewTree.rootContext();
    contextTree->setContextProperty("myModel", model);
    contextTree->setContextProperty("viewMaster", &viewMaster);
    viewTree.setSource(QUrl("qrc:/tree.qml"));
    viewTree.show();

    return app.exec();
}
