/****************************************************************************
** Meta object code from reading C++ file 'simpleplayer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../hydrogenMusic/simpleplayer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'simpleplayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SimplePlayer_t {
    QByteArrayData data[11];
    char stringdata0[85];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SimplePlayer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SimplePlayer_t qt_meta_stringdata_SimplePlayer = {
    {
QT_MOC_LITERAL(0, 0, 12), // "SimplePlayer"
QT_MOC_LITERAL(1, 13, 5), // "onEnd"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 7), // "openUrl"
QT_MOC_LITERAL(4, 28, 3), // "add"
QT_MOC_LITERAL(5, 32, 4), // "play"
QT_MOC_LITERAL(6, 37, 5), // "pause"
QT_MOC_LITERAL(7, 43, 10), // "getpositon"
QT_MOC_LITERAL(8, 54, 9), // "getlength"
QT_MOC_LITERAL(9, 64, 11), // "setposition"
QT_MOC_LITERAL(10, 76, 8) // "position"

    },
    "SimplePlayer\0onEnd\0\0openUrl\0add\0play\0"
    "pause\0getpositon\0getlength\0setposition\0"
    "position"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SimplePlayer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
       3,    1,   50,    2, 0x02 /* Public */,
       5,    0,   53,    2, 0x02 /* Public */,
       6,    0,   54,    2, 0x02 /* Public */,
       7,    0,   55,    2, 0x02 /* Public */,
       8,    0,   56,    2, 0x02 /* Public */,
       9,    1,   57,    2, 0x02 /* Public */,

 // slots: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Void, QMetaType::Int,   10,

       0        // eod
};

void SimplePlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SimplePlayer *_t = static_cast<SimplePlayer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onEnd(); break;
        case 1: _t->openUrl((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->play(); break;
        case 3: _t->pause(); break;
        case 4: { float _r = _t->getpositon();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 5: { float _r = _t->getlength();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->setposition((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SimplePlayer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SimplePlayer.data,
      qt_meta_data_SimplePlayer,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SimplePlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SimplePlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SimplePlayer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SimplePlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
