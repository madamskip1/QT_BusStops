#ifndef TESTPROXY_H
#define TESTPROXY_H
#include <QAbstractItemModel>
#include <QObject>

#include "treemodel.h"

class ProxyModel : public QAbstractItemModel
{

public:
    ProxyModel();
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent (const QModelIndex &index) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;


    QHash<int, QByteArray> roleNames() const override;

    void setModel(TreeModel* mod);
    TreeModel * getModel();
    void setParent(QModelIndex index);
    QModelIndex getParent();

public slots:
    void edited();
private:
    QModelIndex curParent;
    TreeModel * model;

};

#endif // TESTPROXY_H
