import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import SavingTask 1.0


Window {
    id: _window
    visible: true
    width: 600
    height: 600
    title: qsTr("Task Manager")

    Saving {
        id: _saving
    }

    Rectangle {
        id: _rectangle1
        width: _column.width
        height: _column.height
        color: "green"

        Column {
            id: _column
            padding: 20
            spacing: 10

            TextField {
                id: _id
                text: "ID " + cppObject.cppMethod()
                readOnly: true
            }

            TextField {
                id: _name
                placeholderText: qsTr("Name")
            }

            TextField {
                id: _date
                placeholderText: qsTr("dd.mm.yyyy")
                validator: RegExpValidator{regExp: /^(?:(?:31(\/|-|\.)(?:0?[13578]|1[02]))\1|(?:(?:29|30)(\/|-|\.)(?:0?[1,3-9]|1[0-2])\2))(?:(?:1[6-9]|[2-9]\d)?\d{2})$|^(?:29(\/|-|\.)0?2\3(?:(?:(?:1[6-9]|[2-9]\d)?(?:0[48]|[2468][048]|[13579][26])|(?:(?:16|[2468][048]|[3579][26])00))))$|^(?:0?[1-9]|1\d|2[0-8])(\/|-|\.)(?:(?:0?[1-9])|(?:1[0-2]))\4(?:(?:1[6-9]|[2-9]\d)?\d{2})$/}
            }

            SpinBox {
                id: _spinbox
                width: _date.width
                from: 0
                to: 10
            }

            MessageDialog {
                id: _messageDialog
                title: "Error!"
                text: "Fill in all the fields!"
            }

            My_Button {
                id: _button
                text: qsTr("Save and exit")
                width: _date.width
                height: _date.width


                onClicked: {
                       if (_name.text !== "" && _date.text !== "") {
                           _saving.saveTask(_id.text, _name.text, _date.text, _spinbox.value)
                           _name.clear()
                           _date.clear()
                           _spinbox.value
                           _label.visible = false
                           Qt.quit()
                       }  else _messageDialog.visible = true
                }
            }
        }
    }
}
