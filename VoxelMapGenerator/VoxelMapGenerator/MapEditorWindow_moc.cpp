/****************************************************************************
** Meta object code from reading C++ file 'MapEditorWindow.h'
**
** Created: Tue Feb 3 21:59:14 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MapEditorWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MapEditorWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MapEditorWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      29,   16,   16,   16, 0x08,
      42,   16,   16,   16, 0x08,
      56,   16,   16,   16, 0x08,
      68,   16,   16,   16, 0x08,
      78,   16,   16,   16, 0x08,
      88,   16,   16,   16, 0x08,
     107,   16,   16,   16, 0x08,
     121,   16,   16,   16, 0x08,
     134,   16,   16,   16, 0x08,
     149,   16,   16,   16, 0x08,
     164,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MapEditorWindow[] = {
    "MapEditorWindow\0\0triggered()\0newProject()\0"
    "openProject()\0saveMapAs()\0saveMap()\0"
    "loadMap()\0loadMapFromImage()\0loadTexture()\0"
    "updateLoop()\0updateColors()\0updateHeight()\0"
    "updateTexture()\0"
};

void MapEditorWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MapEditorWindow *_t = static_cast<MapEditorWindow *>(_o);
        switch (_id) {
        case 0: _t->triggered(); break;
        case 1: _t->newProject(); break;
        case 2: _t->openProject(); break;
        case 3: _t->saveMapAs(); break;
        case 4: _t->saveMap(); break;
        case 5: _t->loadMap(); break;
        case 6: _t->loadMapFromImage(); break;
        case 7: _t->loadTexture(); break;
        case 8: _t->updateLoop(); break;
        case 9: _t->updateColors(); break;
        case 10: _t->updateHeight(); break;
        case 11: _t->updateTexture(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MapEditorWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MapEditorWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MapEditorWindow,
      qt_meta_data_MapEditorWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MapEditorWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MapEditorWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MapEditorWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MapEditorWindow))
        return static_cast<void*>(const_cast< MapEditorWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MapEditorWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void MapEditorWindow::triggered()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
