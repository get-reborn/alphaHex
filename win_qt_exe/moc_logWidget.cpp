/****************************************************************************
** Meta object code from reading C++ file 'logWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qt_alphaHex/inc/gui/widget/logWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'logWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WidgetLog_t {
    QByteArrayData data[8];
    char stringdata0[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WidgetLog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WidgetLog_t qt_meta_stringdata_WidgetLog = {
    {
QT_MOC_LITERAL(0, 0, 9), // "WidgetLog"
QT_MOC_LITERAL(1, 10, 18), // "slots_on_updateLog"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 9), // "GameCore*"
QT_MOC_LITERAL(4, 40, 4), // "core"
QT_MOC_LITERAL(5, 45, 17), // "slots_on_clearLog"
QT_MOC_LITERAL(6, 63, 8), // "HexGame*"
QT_MOC_LITERAL(7, 72, 4) // "game"

    },
    "WidgetLog\0slots_on_updateLog\0\0GameCore*\0"
    "core\0slots_on_clearLog\0HexGame*\0game"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WidgetLog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       5,    0,   37,    2, 0x0a /* Public */,
       5,    1,   38,    2, 0x0a /* Public */,
       5,    1,   41,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void WidgetLog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WidgetLog *_t = static_cast<WidgetLog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slots_on_updateLog((*reinterpret_cast< GameCore*(*)>(_a[1]))); break;
        case 1: _t->slots_on_clearLog(); break;
        case 2: _t->slots_on_clearLog((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slots_on_clearLog((*reinterpret_cast< HexGame*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< GameCore* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< HexGame* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WidgetLog::staticMetaObject = {
    { &QTextBrowser::staticMetaObject, qt_meta_stringdata_WidgetLog.data,
      qt_meta_data_WidgetLog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *WidgetLog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WidgetLog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WidgetLog.stringdata0))
        return static_cast<void*>(this);
    return QTextBrowser::qt_metacast(_clname);
}

int WidgetLog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextBrowser::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
