#ifdef USE_QT_LIB
/****************************************************************************
** Meta object code from reading C++ file 'bottomBar.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "bottomBar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bottomBar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSpinBoxWithoutTextEdit[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_QSpinBoxWithoutTextEdit[] = {
    "QSpinBoxWithoutTextEdit\0"
};

void QSpinBoxWithoutTextEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QSpinBoxWithoutTextEdit::staticMetaObjectExtraData = {
    0,  qt_static_metacall
};

const QMetaObject QSpinBoxWithoutTextEdit::staticMetaObject = {
    { &QSpinBox::staticMetaObject, qt_meta_stringdata_QSpinBoxWithoutTextEdit,
      qt_meta_data_QSpinBoxWithoutTextEdit, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSpinBoxWithoutTextEdit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSpinBoxWithoutTextEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSpinBoxWithoutTextEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSpinBoxWithoutTextEdit))
        return static_cast<void*>(const_cast< QSpinBoxWithoutTextEdit*>(this));
    return QSpinBox::qt_metacast(_clname);
}

int QSpinBoxWithoutTextEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSpinBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_BottomBar[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      22,   10,   10,   10, 0x08,
      33,   10,   10,   10, 0x08,
      43,   10,   10,   10, 0x08,
      67,   10,   10,   10, 0x08,
      91,   10,   10,   10, 0x08,
     121,   10,   10,   10, 0x08,
     144,   10,   10,   10, 0x08,
     154,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_BottomBar[] = {
    "BottomBar\0\0rollDice()\0purchase()\0"
    "endTurn()\0rollDiceWithAnimation()\0"
    "purchaseWithAnimation()\0"
    "purchaseWithAnimationHelper()\0"
    "endTurnWithAnimation()\0exitApp()\0"
    "changeComputerSpeed()\0"
};

void BottomBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BottomBar *_t = static_cast<BottomBar *>(_o);
        switch (_id) {
        case 0: _t->rollDice(); break;
        case 1: _t->purchase(); break;
        case 2: _t->endTurn(); break;
        case 3: _t->rollDiceWithAnimation(); break;
        case 4: _t->purchaseWithAnimation(); break;
        case 5: _t->purchaseWithAnimationHelper(); break;
        case 6: _t->endTurnWithAnimation(); break;
        case 7: _t->exitApp(); break;
        case 8: _t->changeComputerSpeed(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData BottomBar::staticMetaObjectExtraData = {
    0,  qt_static_metacall
};

const QMetaObject BottomBar::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_BottomBar,
      qt_meta_data_BottomBar, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BottomBar::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BottomBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BottomBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BottomBar))
        return static_cast<void*>(const_cast< BottomBar*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int BottomBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

#endif
