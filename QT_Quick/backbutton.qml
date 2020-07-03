import QtQuick 2.9
import QtQuick.Controls 2.1

Rectangle
{
    id: backButton
    width: parent.width;

    height:80
    Button
    {
        width: 200
        height: 50
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        Text {

            text: qsTr("Wróć")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }

        background: Rectangle
        {
            id: buttonBg
            border.width: 2
            border.color: "#000"
            radius: 20
            color: "#e3e2de"
        }

        MouseArea
        {
            anchors.fill: parent
            id: buttonWrocMouse
            hoverEnabled: true
            onEntered: buttonBg.color = "#bfbebb"
            onExited: buttonBg.color = "#e3e2de"
            onClicked:
            {
                stack.pop();
                viewMaster.backButtonClicked();
            }
        }
    }
}
