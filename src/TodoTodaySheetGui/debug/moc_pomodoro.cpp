/****************************************************************************
** Meta object code from reading C++ file 'pomodoro.hpp'
**
** Created: Wed Apr 29 02:46:12 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gui/pomodoro/pomodoro.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pomodoro.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Pomodoro[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      29,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      46,    9,    9,    9, 0x08,
      58,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Pomodoro[] = {
    "Pomodoro\0\0PomodoroFinished()\0"
    "PomodoroBroken()\0ShowTimer()\0Run()\0"
};

const QMetaObject Pomodoro::staticMetaObject = {
    { &QLCDNumber::staticMetaObject, qt_meta_stringdata_Pomodoro,
      qt_meta_data_Pomodoro, 0 }
};

const QMetaObject *Pomodoro::metaObject() const
{
    return &staticMetaObject;
}

void *Pomodoro::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Pomodoro))
        return static_cast<void*>(const_cast< Pomodoro*>(this));
    return QLCDNumber::qt_metacast(_clname);
}

int Pomodoro::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLCDNumber::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: PomodoroFinished(); break;
        case 1: PomodoroBroken(); break;
        case 2: ShowTimer(); break;
        case 3: Run(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Pomodoro::PomodoroFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Pomodoro::PomodoroBroken()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
