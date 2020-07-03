#include "treenode.h"
#include <QDebug>

TreeNode::TreeNode(const QVector<QVariant> &dat, TreeNode* _parent) :  _parent(_parent), _data(dat)
{

}

TreeNode::~TreeNode()
{
    qDeleteAll(_children);
}

TreeNode* TreeNode::getParent()
{
    return _parent;
}

TreeNode* TreeNode::child(const int& row)
{
    if (row < 0 || row >= _children.size())
        return nullptr;

    return _children.at(row);
}

int TreeNode::childCount() const
{
    return _children.size();
}

void TreeNode::addChild(TreeNode *node, int pos)
{
    if (pos == -1)
        _children.append(node);
    else
        _children.insert(pos, node);
}

int TreeNode::row() const
{
    if (_parent)
        return _parent->_children.indexOf(const_cast<TreeNode*>(this));
    return 0;
}

int TreeNode::columnCount() const
{
    return _data.size();
}

void TreeNode::addData(QVariant dat)
{
    _data.append(dat);
}

void TreeNode::setData(QVector<QVariant> dat)
{

}

void TreeNode::setData(QVariant dat, int index)
{
    _data.insert(index, dat);
}

QVariant TreeNode::data(int index)
{
    if (index < 0 || index >= _data.size())
        return QVariant();
    return _data[index];
}

void TreeNode::removeRow(int index)
{
    _children.removeAt(index);
}

void TreeNode::removeColumn(int index)
{
    if (_data.size() > index)
        _data.removeAt(index);
}

