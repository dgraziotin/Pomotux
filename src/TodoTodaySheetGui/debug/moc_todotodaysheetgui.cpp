/****************************************************************************
** Meta object code from reading C++ file 'todotodaysheetgui.h'
**
** Created: Wed Apr 29 09:56:37 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../todotodaysheetgui.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'todotodaysheetgui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TodoTodaySheetGui[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x08,
      45,   18,   18,   18, 0x08,
      81,   18,   18,   18, 0x08,
     114,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TodoTodaySheetGui[] = {
    "TodoTodaySheetGui\0\0on_stopActivity_clicked()\0"
    "on_postponeActivityButton_clicked()\0"
    "on_startActivityButton_clicked()\0"
    "on_finishActivityButton_clicked()\0"
};

const QMetaObject TodoTodaySheetGui::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_TodoTodaySheetGui,
      qt_meta_data_TodoTodaySheetGui, 0 }
};

const QMetaObject *TodoTodaySheetGui::metaObject() const
{
    return &staticMetaObject;
}

void *TodoTodaySheetGui::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TodoTodaySheetGui))
        return static_cast<void*>(const_cast< TodoTodaySheetGui*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int TodoTodaySheetGui::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_stopActivity_clicked(); break;
        case 1: on_postponeActivityButton_clicked(); break;
        case 2: on_startActivityButton_clicked(); break;
        case 3: on_finishActivityButton_clicked(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
