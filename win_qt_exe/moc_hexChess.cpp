/****************************************************************************
** Meta object code from reading C++ file 'hexChess.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qt_alphaHex/inc/game/hexChess.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hexChess.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HexGame_t {
    QByteArrayData data[14];
    char stringdata0[157];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HexGame_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HexGame_t qt_meta_stringdata_HexGame = {
    {
QT_MOC_LITERAL(0, 0, 7), // "HexGame"
QT_MOC_LITERAL(1, 8, 17), // "signals_on_aiMove"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 18), // "signals_on_newGame"
QT_MOC_LITERAL(4, 46, 8), // "HexGame*"
QT_MOC_LITERAL(5, 55, 4), // "game"
QT_MOC_LITERAL(6, 60, 18), // "slots_on_renewGame"
QT_MOC_LITERAL(7, 79, 4), // "size"
QT_MOC_LITERAL(8, 84, 4), // "time"
QT_MOC_LITERAL(9, 89, 9), // "redPolicy"
QT_MOC_LITERAL(10, 99, 10), // "bluePolicy"
QT_MOC_LITERAL(11, 110, 19), // "slots_on_policyMove"
QT_MOC_LITERAL(12, 130, 18), // "slots_on_humanMove"
QT_MOC_LITERAL(13, 149, 7) // "moveNum"

    },
    "HexGame\0signals_on_aiMove\0\0"
    "signals_on_newGame\0HexGame*\0game\0"
    "slots_on_renewGame\0size\0time\0redPolicy\0"
    "bluePolicy\0slots_on_policyMove\0"
    "slots_on_humanMove\0moveNum"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HexGame[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    1,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    4,   43,    2, 0x0a /* Public */,
      11,    0,   52,    2, 0x0a /* Public */,
      12,    1,   53,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    7,    8,    9,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   13,

       0        // eod
};

void HexGame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HexGame *_t = static_cast<HexGame *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signals_on_aiMove(); break;
        case 1: _t->signals_on_newGame((*reinterpret_cast< HexGame*(*)>(_a[1]))); break;
        case 2: _t->slots_on_renewGame((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 3: _t->slots_on_policyMove(); break;
        case 4: _t->slots_on_humanMove((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< HexGame* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (HexGame::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HexGame::signals_on_aiMove)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (HexGame::*)(HexGame * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HexGame::signals_on_newGame)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject HexGame::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_HexGame.data,
      qt_meta_data_HexGame,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *HexGame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HexGame::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HexGame.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int HexGame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void HexGame::signals_on_aiMove()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void HexGame::signals_on_newGame(HexGame * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
