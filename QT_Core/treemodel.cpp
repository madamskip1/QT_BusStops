#include "treemodel.h"
#include <QDebug>
#include <QBrush>
#include <QFont>

TreeModel::TreeModel(QObject * parent) : QAbstractItemModel(parent)
{
    root = new TreeNode({"ID", "Nazwa", "Kierunek"});   // Nagłówki
}

TreeModel::~TreeModel()
{
    delete root;
}

int TreeModel::rowCount(const QModelIndex &parent) const
{    
    if (!parent.isValid())
        return root->childCount();

    TreeNode* parentNode;
    parentNode = static_cast<TreeNode*>(parent.internalPointer());
    return parentNode->childCount();
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeNode*>(parent.internalPointer())->columnCount();


    return root->columnCount();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (hasIndex(row, column, parent))
    {
        TreeNode *parentNode;

        if (parent.isValid())
            parentNode = static_cast<TreeNode*>(parent.internalPointer());
        else
            parentNode = root;

        if (parentNode->child(row))
            return createIndex(row, column, parentNode->child((row)));
    }

    return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();


    TreeNode * parentNode;
    TreeNode * childNode;

    childNode = static_cast<TreeNode*>(index.internalPointer());
    parentNode = childNode->getParent();

    if (parentNode == root)
        return QModelIndex();

    return createIndex(parentNode->row(), 0, parentNode);

}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (role == Qt::DisplayRole)
            return root->data(section);

        else if (role == Qt::FontRole)
            return QFont("Arial", 10, QFont::Bold);
    }

    return QVariant();
}


QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid())
    {
        TreeNode *node = static_cast<TreeNode*>(index.internalPointer());

        if (role == Qt::DisplayRole)
            return node->data(index.column());
    }

    return QVariant();
}







QModelIndex TreeModel::getBus(int id)
{
    int rows = root->childCount();
    if (rows <= 0)
        return QModelIndex();

    for (int i = 0; i < rows; i++)
    {
        if (root->child(i)->data(0) == id)
            return index(i, 0);
    }

    return QModelIndex();
}

QModelIndex TreeModel::getBusStartingWith(int id)
{
    int rows = root->childCount();
    if (rows <= 0)
        return QModelIndex();

    QString string;
    QString stopID = QString::number(id);
    for (int i = 0; i < rows; i++)
    {
        string = root->child(i)->data(0).toString();

        if (string.startsWith(stopID))
            return index(i, 0);
    }

    return QModelIndex();
}

void TreeModel::removeBusStopByID(int id)
{
    QModelIndex index = getBus(id);
    if (!index.isValid())
        return;

    int nodeRow = index.row();

    beginRemoveRows(QModelIndex(), nodeRow, nodeRow);
    root->removeRow(nodeRow);
    endRemoveRows();
}

QModelIndex TreeModel::addBusStop(const QVector<QVariant>& stop)
{
    TreeNode * nodeToAdd = new TreeNode(stop, root);
    beginInsertRows(QModelIndex(), root->childCount()-1, root->childCount());
    root->addChild(nodeToAdd);
    endInsertRows();

    return index(nodeToAdd->row(), 0);
}

QModelIndex TreeModel::getLine(int stopID, int lineID)
{
    QModelIndex index = getBus(stopID);
    return getLine(index, lineID);
}

QModelIndex TreeModel::getLine(QModelIndex stop, int lineID)
{
    TreeNode * busStop = static_cast<TreeNode*>(stop.internalPointer());
    int rows = busStop->childCount();
    if (rows <= 0)
        return QModelIndex();

    QString cur;
    QString id = QString::number(lineID);
    for (int i = 0; i < rows; i++)
    {
        cur = busStop->child(i)->data(0).toString();
        if (cur.contains(id))
            return index(i, 0, stop);
    }

    return QModelIndex();
}

QModelIndex TreeModel::addLine(QModelIndex stop, const QVector<QVariant> &line)
{
    TreeNode * parent = static_cast<TreeNode*>(stop.internalPointer());
    TreeNode * lineToAdd = new TreeNode(line, parent);

    beginInsertRows(index(parent->row(), 0), parent->childCount(), parent->childCount());
    parent->addChild(lineToAdd);
    endInsertRows();

    return index(lineToAdd->row(), 0, stop);
}

void TreeModel::removeLine(QModelIndex stop, int id)
{
    QModelIndex line = getLine(stop, id);
    if (!line.isValid())
        return;

    int nodeRow = line.row();
    beginRemoveRows(index(stop.row(), 0), nodeRow, nodeRow);
    (static_cast<TreeNode*>(stop.internalPointer()))->removeRow(nodeRow);
    endRemoveRows();
}

QModelIndex TreeModel::addDeparture(QModelIndex line, const QVector<QVariant> &dep)
{
    if(!line.isValid())
        return QModelIndex();


    QString depTime = dep.at(0).toString();
    QString lineTime;
    TreeNode * lineNode = static_cast<TreeNode*>(line.internalPointer());
    int rows = lineNode->childCount();

    for (int i = 0; i < rows; i++)
    {
        lineTime = lineNode->child(i)->data(0).toString();
        if (depTime.compare(lineTime) == -1)
        {
            beginInsertRows(index(lineNode->row(), 0, line.parent()), i, i);
            lineNode->addChild(new TreeNode(dep, lineNode), i);
            endInsertRows();

            return index(i, 0, line);
        }
    }

    beginInsertRows(index(lineNode->row(), 0, line.parent()), lineNode->childCount(), lineNode->childCount());
    lineNode->addChild(new TreeNode(dep, lineNode));
    endInsertRows();
}

QModelIndex TreeModel::getDeparture(QModelIndex line, QString time)
{
    if(!line.isValid())
        return QModelIndex();

    TreeNode * lineNode = static_cast<TreeNode*>(line.internalPointer());
    int rows = lineNode->childCount();
    for (int i = 0; i < rows; i++)
    {
        if (time == lineNode->child(i)->data(0).toString())
            return index(i, 0, line);
    }

    return QModelIndex();
}


void TreeModel::editDeparture(QModelIndex dep, QString newDelay)
{
    if (!dep.isValid())
        return;

    TreeNode * node =  static_cast<TreeNode*>(dep.internalPointer());
    node->setData(newDelay, 1);
    emit dataChanged(index(node->row(), 0, dep.parent()), index(node->row(), node->columnCount(), dep.parent()), {Qt::DisplayRole});
}
