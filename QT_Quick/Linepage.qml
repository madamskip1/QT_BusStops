import QtQuick 2.0

Component
{
    Rectangle
    {
        width: mainWind.width
        height: mainWind.height
        Backbutton {}

        Rectangle
        {
            y: 80
            width: parent.width
            height: parent.height - 80
            color: "#edf7fa"
            ListView {
                id: lineListView
                width: parent.width
                height: parent.height
                model: myModel


                delegate: Component
                {
                    Rectangle
                    {
                        width: parent.width
                        height: 25
                        color: index % 2 == 0 ? "#c3ecf7" : "#2da2c2"
                        Text{
                            x: 10
                            anchors.verticalCenter: parent.verticalCenter
                            text: StopID +" " + StopName
                        }

                        MouseArea
                        {
                            anchors.fill: parent
                            onClicked: function()
                            {
                                stack.push(depPage)
                                viewMaster.lineClicked(StopID)
                            }
                        }
                    }
                }

            }
        }
    }
}
