/****************************************************************************
** Meta object code from reading C++ file 'insertnewactivity.h'
**
** Created: Wed Apr 29 09:56:39 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ActivityInventorySheetGui/insertnewactivity.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'insertnewactivity.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_InsertNewActivity[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x08,
      43,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_InsertNewActivity[] = {
    "InsertNewActivity\0\0on_buttonBox_rejected()\0"
    "on_buttonBox_accepted()\0"
};

const QMetaObject InsertNewActivity::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_InsertNewActivity,
      qt_meta_data_InsertNewActivity, 0 }
};

const QMetaObject *InsertNewActivity::metaObject() const
{
    return &staticMetaObject;
}

void *InsertNewActivity::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InsertNewActivity))
        return static_cast<void*>(const_cast< InsertNewActivity*>(this));
    return QDialog::qt_metacast(_clname);
}

int InsertNewActivity::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_buttonBox_rejected(); break;
        case 1: on_buttonBox_accepted(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
