/****************************************************************************
** Meta object code from reading C++ file 'guiactivityinventorysheet.h'
**
** Created: Wed Apr 29 09:56:40 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ActivityInventorySheetGui/guiactivityinventorysheet.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'guiactivityinventorysheet.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GuiActivityInventorySheet[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      27,   26,   26,   26, 0x08,
      58,   26,   26,   26, 0x08,
      97,   92,   26,   26, 0x08,
     135,   26,   26,   26, 0x08,
     169,   26,   26,   26, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GuiActivityInventorySheet[] = {
    "GuiActivityInventorySheet\0\0"
    "on_insertInTTSButton_clicked()\0"
    "on_modifyActivityButton_clicked()\0"
    "item\0on_ais_itemClicked(QTableWidgetItem*)\0"
    "on_deleteActivityButton_clicked()\0"
    "on_newActivityButton_clicked()\0"
};

const QMetaObject GuiActivityInventorySheet::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_GuiActivityInventorySheet,
      qt_meta_data_GuiActivityInventorySheet, 0 }
};

const QMetaObject *GuiActivityInventorySheet::metaObject() const
{
    return &staticMetaObject;
}

void *GuiActivityInventorySheet::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GuiActivityInventorySheet))
        return static_cast<void*>(const_cast< GuiActivityInventorySheet*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int GuiActivityInventorySheet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_insertInTTSButton_clicked(); break;
        case 1: on_modifyActivityButton_clicked(); break;
        case 2: on_ais_itemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 3: on_deleteActivityButton_clicked(); break;
        case 4: on_newActivityButton_clicked(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
