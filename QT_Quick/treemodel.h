#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QTimer>
#include "treenode.h"

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    TreeModel(QObject * parent = nullptr);
    ~TreeModel();
    enum TreeRoles
    {
        StopID = Qt::UserRole + 1,
        StopName,
        StopDir
    };

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent (const QModelIndex &index) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;


    QHash<int, QByteArray> roleNames() const override;

    QModelIndex getBus(int id);
    QModelIndex getBusStartingWith(int id);
    QModelIndex addBusStop(const QVector<QVariant>& stop);
    void removeBusStopByID(int id);

    QModelIndex getLine(int stopID, int lineID);
    QModelIndex getLine(QModelIndex stop, int lineID);
    QModelIndex addLine(QModelIndex stop, const QVector<QVariant>& line);
    QModelIndex addLine(int stopID, const QVector<QVariant>& line);
    void removeLine(QModelIndex stop, int id);

    QModelIndex getDeparture(QModelIndex line, QString time);
    QModelIndex addDeparture(QModelIndex line, const QVector<QVariant>& dep);
    void editDeparture(QModelIndex dep, QString newDelay);
    void setProbTime(QModelIndex dep, QString time);
    void removeProbTime(QModelIndex dep);
    void edited();

    void calculateTime();
signals:
    void someEdits();

public slots:
    void timer30();
private:
    TreeNode *root;
    QTimer * timer;
};
#endif // TREEMODEL_H
