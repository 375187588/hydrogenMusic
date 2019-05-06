/****************************************************************************
** Meta object code from reading C++ file 'personalinfo.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../hydrogenMusic/personalinfo.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'personalinfo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PersonalInfo_t {
    QByteArrayData data[8];
    char stringdata0[87];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PersonalInfo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PersonalInfo_t qt_meta_stringdata_PersonalInfo = {
    {
QT_MOC_LITERAL(0, 0, 12), // "PersonalInfo"
QT_MOC_LITERAL(1, 13, 2), // "ID"
QT_MOC_LITERAL(2, 16, 4), // "ilik"
QT_MOC_LITERAL(3, 21, 22), // "QQmlListProperty<Song>"
QT_MOC_LITERAL(4, 44, 7), // "downloa"
QT_MOC_LITERAL(5, 52, 9), // "tempSheet"
QT_MOC_LITERAL(6, 62, 9), // "songSheet"
QT_MOC_LITERAL(7, 72, 14) // "QList<QString>"

    },
    "PersonalInfo\0ID\0ilik\0QQmlListProperty<Song>\0"
    "downloa\0tempSheet\0songSheet\0QList<QString>"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PersonalInfo[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       5,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QString, 0x00095001,
       2, 0x80000000 | 3, 0x00095409,
       4, 0x80000000 | 3, 0x00095409,
       5, 0x80000000 | 3, 0x00095409,
       6, 0x80000000 | 7, 0x00095409,

       0        // eod
};

void PersonalInfo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QString> >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        PersonalInfo *_t = static_cast<PersonalInfo *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->ID(); break;
        case 1: *reinterpret_cast< QQmlListProperty<Song>*>(_v) = _t->ilik(); break;
        case 2: *reinterpret_cast< QQmlListProperty<Song>*>(_v) = _t->downloa(); break;
        case 3: *reinterpret_cast< QQmlListProperty<Song>*>(_v) = _t->tempSheet(); break;
        case 4: *reinterpret_cast< QList<QString>*>(_v) = _t->songSheet(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_o);
}

QT_INIT_METAOBJECT const QMetaObject PersonalInfo::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PersonalInfo.data,
      qt_meta_data_PersonalInfo,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PersonalInfo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PersonalInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PersonalInfo.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PersonalInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
   if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
