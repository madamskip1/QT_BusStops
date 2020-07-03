import QtQuick 2.9
import QtQuick.Controls 2.1

Rectangle
{
    width: 330
    height: 350
    id: mainWind


    StackView
    {
        initialItem: stopPage
        anchors.fill: parent
        id: stack


        Stoppage
        {
            id: stopPage
        }

        Linepage
        {
            id: linePage
        }



        Deppage
        {
            id: depPage
        }
    }
}
