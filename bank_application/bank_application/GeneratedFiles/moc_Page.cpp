/****************************************************************************
** Meta object code from reading C++ file 'Page.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Page.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Page.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Page_t {
    QByteArrayData data[15];
    char stringdata0[162];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Page_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Page_t qt_meta_stringdata_Page = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Page"
QT_MOC_LITERAL(1, 5, 4), // "hide"
QT_MOC_LITERAL(2, 10, 0), // ""
QT_MOC_LITERAL(3, 11, 6), // "logout"
QT_MOC_LITERAL(4, 18, 10), // "creditPage"
QT_MOC_LITERAL(5, 29, 13), // "transHistPage"
QT_MOC_LITERAL(6, 43, 8), // "settPage"
QT_MOC_LITERAL(7, 52, 12), // "setCloseAble"
QT_MOC_LITERAL(8, 65, 3), // "par"
QT_MOC_LITERAL(9, 69, 8), // "showPage"
QT_MOC_LITERAL(10, 78, 9), // "setHidden"
QT_MOC_LITERAL(11, 88, 10), // "emitSignal"
QT_MOC_LITERAL(12, 99, 35), // "wait_for_the_thread_and_emit_..."
QT_MOC_LITERAL(13, 135, 14), // "Thread_signals"
QT_MOC_LITERAL(14, 150, 11) // "signal2emit"

    },
    "Page\0hide\0\0logout\0creditPage\0transHistPage\0"
    "settPage\0setCloseAble\0par\0showPage\0"
    "setHidden\0emitSignal\0"
    "wait_for_the_thread_and_emit_signal\0"
    "Thread_signals\0signal2emit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Page[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    0,   71,    2, 0x06 /* Public */,
       5,    0,   72,    2, 0x06 /* Public */,
       6,    0,   73,    2, 0x06 /* Public */,
       7,    1,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   77,    2, 0x0a /* Public */,
      10,    1,   78,    2, 0x0a /* Public */,
      10,    0,   81,    2, 0x2a /* Public | MethodCloned */,
      12,    1,   82,    2, 0x09 /* Protected */,
      12,    0,   85,    2, 0x29 /* Protected | MethodCloned */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void,

       0        // eod
};

void Page::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Page *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->hide(); break;
        case 1: _t->logout(); break;
        case 2: _t->creditPage(); break;
        case 3: _t->transHistPage(); break;
        case 4: _t->settPage(); break;
        case 5: _t->setCloseAble((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->showPage(); break;
        case 7: _t->setHidden((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->setHidden(); break;
        case 9: _t->wait_for_the_thread_and_emit_signal((*reinterpret_cast< Thread_signals(*)>(_a[1]))); break;
        case 10: _t->wait_for_the_thread_and_emit_signal(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Page::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Page::hide)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Page::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Page::logout)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Page::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Page::creditPage)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Page::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Page::transHistPage)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Page::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Page::settPage)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Page::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Page::setCloseAble)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Page::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Page.data,
    qt_meta_data_Page,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Page::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Page::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Page.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Page::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void Page::hide()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Page::logout()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Page::creditPage()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Page::transHistPage()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Page::settPage()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Page::setCloseAble(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
