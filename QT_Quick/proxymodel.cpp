#include "proxymodel.h"
#include "treenode.h"
#include <QDebug>

ProxyModel::ProxyModel()
{
    curParent = QModelIndex();
}

void ProxyModel::setModel(TreeModel *mod)
{
    model = mod;
    QObject::connect(model, &TreeModel::someEdits,
                     this, &ProxyModel::edited);
}

void ProxyModel::setParent(QModelIndex index)
{
    beginResetModel();
    curParent = index;
    endResetModel();
}

QModelIndex ProxyModel::getParent()
{
    return curParent;
}

void ProxyModel::edited()
{
    beginResetModel();
    endResetModel();
}

TreeModel * ProxyModel::getModel()
{
    return model;
}

int ProxyModel::rowCount(const QModelIndex &parent) const
{
    return model->rowCount(curParent);
}

int ProxyModel::columnCount(const QModelIndex &parent) const
{
    return model->columnCount(curParent);
}

QModelIndex ProxyModel::index(int row, int column, const QModelIndex &parent) const
{
    return model->index(row, column, curParent);
}

QModelIndex ProxyModel::parent(const QModelIndex &index) const
{
    return model->parent(index);
}

Qt::ItemFlags ProxyModel::flags(const QModelIndex &index) const
{
    return model->flags(index);
}

QVariant ProxyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return model->headerData(section, orientation, role);
}

QVariant ProxyModel::data(const QModelIndex &index, int role) const
{
    return model->data(index, role);
}

QHash<int, QByteArray> ProxyModel::roleNames() const
{
    return model->roleNames();
}
