import QtQuick 2.9
import QtQuick.Controls 1.4

TreeView
{
    width: 501
    height: 400
    model: myModel

    TableViewColumn
    {
        title: "ID"
        role: "StopID"
        width: 100
    }
    TableViewColumn
    {
        title: "Przystanek"
        role: "StopName"
        width: 200
    }
}
