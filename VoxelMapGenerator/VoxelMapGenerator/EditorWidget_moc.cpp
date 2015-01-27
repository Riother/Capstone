/****************************************************************************
** Meta object code from reading C++ file 'EditorWidget.h'
**
** Created: Tue Jan 27 00:32:42 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "EditorWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EditorWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EditorWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      29,   13,   13,   13, 0x05,
      51,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      67,   13,   13,   13, 0x08,
      85,   13,   13,   13, 0x08,
     100,   13,   13,   13, 0x08,
     112,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_EditorWidget[] = {
    "EditorWidget\0\0valueChanged()\0"
    "currentIndexChanged()\0heightChanged()\0"
    "updateSpinboxes()\0updateHeight()\0"
    "keyUpdate()\0updateTexture()\0"
};

void EditorWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        EditorWidget *_t = static_cast<EditorWidget *>(_o);
        switch (_id) {
        case 0: _t->valueChanged(); break;
        case 1: _t->currentIndexChanged(); break;
        case 2: _t->heightChanged(); break;
        case 3: _t->updateSpinboxes(); break;
        case 4: _t->updateHeight(); break;
        case 5: _t->keyUpdate(); break;
        case 6: _t->updateTexture(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData EditorWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject EditorWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_EditorWidget,
      qt_meta_data_EditorWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EditorWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EditorWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EditorWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EditorWidget))
        return static_cast<void*>(const_cast< EditorWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int EditorWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void EditorWidget::valueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void EditorWidget::currentIndexChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void EditorWidget::heightChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
