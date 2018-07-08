/****************************************************************************
** Meta object code from reading C++ file 'personal.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../hydrogenMusic/personal.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'personal.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Personal_t {
    QByteArrayData data[19];
    char stringdata0[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Personal_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Personal_t qt_meta_stringdata_Personal = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Personal"
QT_MOC_LITERAL(1, 9, 9), // "IDChanged"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 14), // "songlisChanged"
QT_MOC_LITERAL(4, 35, 8), // "songList"
QT_MOC_LITERAL(5, 44, 14), // "QList<QString>"
QT_MOC_LITERAL(6, 59, 3), // "vec"
QT_MOC_LITERAL(7, 63, 10), // "downloadOk"
QT_MOC_LITERAL(8, 74, 8), // "uploadOk"
QT_MOC_LITERAL(9, 83, 8), // "searchOk"
QT_MOC_LITERAL(10, 92, 10), // "registerOk"
QT_MOC_LITERAL(11, 103, 14), // "registerFailed"
QT_MOC_LITERAL(12, 118, 7), // "loginOk"
QT_MOC_LITERAL(13, 126, 11), // "loginFailed"
QT_MOC_LITERAL(14, 138, 3), // "run"
QT_MOC_LITERAL(15, 142, 11), // "sendMessage"
QT_MOC_LITERAL(16, 154, 1), // "m"
QT_MOC_LITERAL(17, 156, 2), // "ID"
QT_MOC_LITERAL(18, 159, 7) // "songlis"

    },
    "Personal\0IDChanged\0\0songlisChanged\0"
    "songList\0QList<QString>\0vec\0downloadOk\0"
    "uploadOk\0searchOk\0registerOk\0"
    "registerFailed\0loginOk\0loginFailed\0"
    "run\0sendMessage\0m\0ID\0songlis"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Personal[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       2,   92, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    0,   75,    2, 0x06 /* Public */,
       4,    1,   76,    2, 0x06 /* Public */,
       7,    0,   79,    2, 0x06 /* Public */,
       8,    0,   80,    2, 0x06 /* Public */,
       9,    1,   81,    2, 0x06 /* Public */,
      10,    0,   84,    2, 0x06 /* Public */,
      11,    0,   85,    2, 0x06 /* Public */,
      12,    0,   86,    2, 0x06 /* Public */,
      13,    0,   87,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
      14,    0,   88,    2, 0x02 /* Public */,
      15,    1,   89,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   16,

 // properties: name, type, flags
      17, QMetaType::QString, 0x00495103,
      18, 0x80000000 | 5, 0x0049510b,

 // properties: notify_signal_id
       0,
       1,

       0        // eod
};

void Personal::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Personal *_t = static_cast<Personal *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->IDChanged(); break;
        case 1: _t->songlisChanged(); break;
        case 2: _t->songList((*reinterpret_cast< QList<QString>(*)>(_a[1]))); break;
        case 3: _t->downloadOk(); break;
        case 4: _t->uploadOk(); break;
        case 5: _t->searchOk((*reinterpret_cast< QList<QString>(*)>(_a[1]))); break;
        case 6: _t->registerOk(); break;
        case 7: _t->registerFailed(); break;
        case 8: _t->loginOk(); break;
        case 9: _t->loginFailed(); break;
        case 10: _t->run(); break;
        case 11: _t->sendMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QString> >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QString> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (Personal::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Personal::IDChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Personal::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Personal::songlisChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Personal::*_t)(QList<QString> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Personal::songList)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Personal::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Personal::downloadOk)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Personal::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Personal::uploadOk)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (Personal::*_t)(QList<QString> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Personal::searchOk)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (Personal::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Personal::registerOk)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (Personal::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Personal::registerFailed)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (Personal::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Personal::loginOk)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (Personal::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Personal::loginFailed)) {
                *result = 9;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QString> >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        Personal *_t = static_cast<Personal *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->ID(); break;
        case 1: *reinterpret_cast< QList<QString>*>(_v) = _t->songlis(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        Personal *_t = static_cast<Personal *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setID(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setSonglis(*reinterpret_cast< QList<QString>*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject Personal::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Personal.data,
      qt_meta_data_Personal,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Personal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Personal::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Personal.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Personal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Personal::IDChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Personal::songlisChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Personal::songList(QList<QString> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Personal::downloadOk()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Personal::uploadOk()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Personal::searchOk(QList<QString> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Personal::registerOk()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void Personal::registerFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void Personal::loginOk()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void Personal::loginFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
