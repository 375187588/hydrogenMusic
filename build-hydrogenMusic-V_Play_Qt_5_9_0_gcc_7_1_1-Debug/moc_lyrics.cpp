/****************************************************************************
** Meta object code from reading C++ file 'lyrics.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../hydrogenMusic/lyrics.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lyrics.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Lyric_t {
    QByteArrayData data[20];
    char stringdata0[212];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Lyric_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Lyric_t qt_meta_stringdata_Lyric = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Lyric"
QT_MOC_LITERAL(1, 6, 14), // "lheaderChanged"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 19), // "lyricContentChanged"
QT_MOC_LITERAL(4, 42, 16), // "startTimeChanged"
QT_MOC_LITERAL(5, 59, 15), // "lAddressChanged"
QT_MOC_LITERAL(6, 75, 2), // "ok"
QT_MOC_LITERAL(7, 78, 9), // "readLyric"
QT_MOC_LITERAL(8, 88, 4), // "addr"
QT_MOC_LITERAL(9, 93, 17), // "changeStringToInt"
QT_MOC_LITERAL(10, 111, 11), // "std::string"
QT_MOC_LITERAL(11, 123, 8), // "str_time"
QT_MOC_LITERAL(12, 132, 6), // "header"
QT_MOC_LITERAL(13, 139, 14), // "QList<QString>"
QT_MOC_LITERAL(14, 154, 7), // "lineNum"
QT_MOC_LITERAL(15, 162, 7), // "lheader"
QT_MOC_LITERAL(16, 170, 12), // "lyricContent"
QT_MOC_LITERAL(17, 183, 7), // "endTime"
QT_MOC_LITERAL(18, 191, 10), // "QList<int>"
QT_MOC_LITERAL(19, 202, 9) // "startTime"

    },
    "Lyric\0lheaderChanged\0\0lyricContentChanged\0"
    "startTimeChanged\0lAddressChanged\0ok\0"
    "readLyric\0addr\0changeStringToInt\0"
    "std::string\0str_time\0header\0QList<QString>\0"
    "lineNum\0lheader\0lyricContent\0endTime\0"
    "QList<int>\0startTime"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Lyric[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       6,   60, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,
       4,    0,   51,    2, 0x06 /* Public */,
       5,    0,   52,    2, 0x06 /* Public */,
       6,    0,   53,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       7,    1,   54,    2, 0x02 /* Public */,
       9,    1,   57,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Int, 0x80000000 | 10,   11,

 // properties: name, type, flags
      12, 0x80000000 | 13, 0x00095009,
      14, QMetaType::Int, 0x00095001,
      15, 0x80000000 | 13, 0x0049500b,
      16, 0x80000000 | 13, 0x0049500b,
      17, 0x80000000 | 18, 0x00095009,
      19, 0x80000000 | 18, 0x0049500b,

 // properties: notify_signal_id
       0,
       0,
       0,
       1,
       0,
       2,

       0        // eod
};

void Lyric::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Lyric *_t = static_cast<Lyric *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->lheaderChanged(); break;
        case 1: _t->lyricContentChanged(); break;
        case 2: _t->startTimeChanged(); break;
        case 3: _t->lAddressChanged(); break;
        case 4: _t->ok(); break;
        case 5: _t->readLyric((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: { int _r = _t->changeStringToInt((*reinterpret_cast< std::string(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Lyric::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Lyric::lheaderChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Lyric::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Lyric::lyricContentChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Lyric::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Lyric::startTimeChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Lyric::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Lyric::lAddressChanged)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Lyric::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Lyric::ok)) {
                *result = 4;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
        case 2:
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QString> >(); break;
        case 5:
        case 4:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<int> >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        Lyric *_t = static_cast<Lyric *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QList<QString>*>(_v) = _t->header(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->lineNum(); break;
        case 2: *reinterpret_cast< QList<QString>*>(_v) = _t->lheader(); break;
        case 3: *reinterpret_cast< QList<QString>*>(_v) = _t->lyricContent(); break;
        case 4: *reinterpret_cast< QList<int>*>(_v) = _t->endTime(); break;
        case 5: *reinterpret_cast< QList<int>*>(_v) = _t->startTime(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        Lyric *_t = static_cast<Lyric *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 2: _t->setlheader(*reinterpret_cast< QList<QString>*>(_v)); break;
        case 3: _t->setlyricContent(*reinterpret_cast< QList<QString>*>(_v)); break;
        case 5: _t->setstartTime(*reinterpret_cast< QList<int>*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject Lyric::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Lyric.data,
      qt_meta_data_Lyric,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Lyric::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Lyric::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Lyric.stringdata0))
        return static_cast<void*>(const_cast< Lyric*>(this));
    return QObject::qt_metacast(_clname);
}

int Lyric::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 6;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Lyric::lheaderChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Lyric::lyricContentChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Lyric::startTimeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Lyric::lAddressChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Lyric::ok()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
