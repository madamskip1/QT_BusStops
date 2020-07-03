import QtQuick 2.0

Component
{
    id: depPage
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
                        Rectangle
                        {
                            height: parent.height;
                            width: 40
                            color: parent.color;
                            Text
                            {
                                x: 10
                                anchors.verticalCenter: parent.verticalCenter
                                text: StopID
                            }
                        }
                        Rectangle
                        {
                            x: 40
                            height: parent.height;
                            width: 150
                            color: parent.color;
                            Text
                            {
                                x: 10
                                anchors.verticalCenter: parent.verticalCenter
                                text: StopName
                            }
                        }
                        Rectangle
                        {
                            height: parent.height;
                            x: 190
                            width: 150
                            color: parent.color;
                            Text
                            {
                                x: 10
                                anchors.verticalCenter: parent.verticalCenter
                                text: ((StopDir == "") ? "" : " Odjazd za: " + StopDir + " min")
                            }
                        }

                    }
                }

            }
        }
    }
}
