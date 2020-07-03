#ifndef TREENODE_H
#define TREENODE_H

#include <QVector>
#include <QVariant>

class TreeNode
{
public:
    explicit TreeNode(const QVector<QVariant> &dat, TreeNode* _parent = nullptr);
    ~TreeNode();
    TreeNode *getParent();
    TreeNode *child(const int& row);
    void addChild(TreeNode* node, int pos = -1);
    int childCount() const;
    int columnCount() const;
    void addData(QVariant dat);
    void setData(QVector<QVariant> dat);
    void setData(QVariant dat, int index);
    QVariant data(int index);
    void removeRow(int index);
    void removeColumn(int index);
    int row() const;

private:
    TreeNode *_parent;
    QVector<TreeNode*> _children;
    QVector<QVariant> _data;
};

#endif // TREENODE_H
