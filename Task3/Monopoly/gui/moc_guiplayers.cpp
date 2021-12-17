#ifdef USE_QT_LIB
/****************************************************************************
** Meta object code from reading C++ file 'guiplayers.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "guiplayers.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'guiplayers.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CRightClickEnabler[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_CRightClickEnabler[] = {
    "CRightClickEnabler\0\0rightClick()\0"
};

void CRightClickEnabler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CRightClickEnabler *_t = static_cast<CRightClickEnabler *>(_o);
        switch (_id) {
        case 0: _t->rightClick(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CRightClickEnabler::staticMetaObjectExtraData = {
    0,  qt_static_metacall
};

const QMetaObject CRightClickEnabler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CRightClickEnabler,
      qt_meta_data_CRightClickEnabler, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CRightClickEnabler::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CRightClickEnabler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CRightClickEnabler::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CRightClickEnabler))
        return static_cast<void*>(const_cast< CRightClickEnabler*>(this));
    return QObject::qt_metacast(_clname);
}

int CRightClickEnabler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void CRightClickEnabler::rightClick()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_GUIPlayers[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      24,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GUIPlayers[] = {
    "GUIPlayers\0\0showSpace()\0upgradeSpace()\0"
};

void GUIPlayers::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GUIPlayers *_t = static_cast<GUIPlayers *>(_o);
        switch (_id) {
        case 0: _t->showSpace(); break;
        case 1: _t->upgradeSpace(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData GUIPlayers::staticMetaObjectExtraData = {
    0,  qt_static_metacall
};

const QMetaObject GUIPlayers::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_GUIPlayers,
      qt_meta_data_GUIPlayers, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GUIPlayers::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GUIPlayers::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GUIPlayers::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GUIPlayers))
        return static_cast<void*>(const_cast< GUIPlayers*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int GUIPlayers::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

#endif
