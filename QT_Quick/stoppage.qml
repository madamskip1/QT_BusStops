import QtQuick 2.0

Component
{
    id: mainView

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
                            text: "ID: " + StopID +". " + StopName + ", kierunek " + StopDir
                        }

                        MouseArea
                        {
                            id: pageMouse
                            anchors.fill: parent
                            onClicked: function()
                            {
                                stack.push(linePage)
                                viewMaster.stopBusClicked(StopID)
                            }
                        }
                    }
                }

            }
        }
    }
}
