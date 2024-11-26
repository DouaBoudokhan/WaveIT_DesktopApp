/****************************************************************************
** Meta object code from reading C++ file 'openweathermapforecast.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../users/openweathermapforecast.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'openweathermapforecast.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_OpenWeatherMapForecast_t {
    QByteArrayData data[9];
    char stringdata0[116];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OpenWeatherMapForecast_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OpenWeatherMapForecast_t qt_meta_stringdata_OpenWeatherMapForecast = {
    {
QT_MOC_LITERAL(0, 0, 22), // "OpenWeatherMapForecast"
QT_MOC_LITERAL(1, 23, 16), // "forecastsUpdated"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 4), // "data"
QT_MOC_LITERAL(4, 46, 13), // "errorOccurred"
QT_MOC_LITERAL(5, 60, 11), // "errorString"
QT_MOC_LITERAL(6, 72, 22), // "onNetworkReplyFinished"
QT_MOC_LITERAL(7, 95, 14), // "QNetworkReply*"
QT_MOC_LITERAL(8, 110, 5) // "reply"

    },
    "OpenWeatherMapForecast\0forecastsUpdated\0"
    "\0data\0errorOccurred\0errorString\0"
    "onNetworkReplyFinished\0QNetworkReply*\0"
    "reply"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OpenWeatherMapForecast[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    1,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   35,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QJsonArray,    3,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void OpenWeatherMapForecast::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OpenWeatherMapForecast *_t = static_cast<OpenWeatherMapForecast *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->forecastsUpdated((*reinterpret_cast< QJsonArray(*)>(_a[1]))); break;
        case 1: _t->errorOccurred((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->onNetworkReplyFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (OpenWeatherMapForecast::*_t)(QJsonArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OpenWeatherMapForecast::forecastsUpdated)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (OpenWeatherMapForecast::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OpenWeatherMapForecast::errorOccurred)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject OpenWeatherMapForecast::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_OpenWeatherMapForecast.data,
      qt_meta_data_OpenWeatherMapForecast,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *OpenWeatherMapForecast::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OpenWeatherMapForecast::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_OpenWeatherMapForecast.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int OpenWeatherMapForecast::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void OpenWeatherMapForecast::forecastsUpdated(QJsonArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void OpenWeatherMapForecast::errorOccurred(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
