/****************************************************************************
** Meta object code from reading C++ file 'Parametres.h'
**
** Created: Sat May 7 10:36:20 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Parametres.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Parametres.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Parametres[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      30,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   12,   11,   11, 0x0a,
      56,   45,   11,   11, 0x0a,
      91,   75,   11,   11, 0x0a,
     128,  116,   11,   11, 0x0a,
     162,  149,   11,   11, 0x0a,
     203,  191,   11,   11, 0x0a,
     237,  224,   11,   11, 0x0a,
     278,  266,   11,   11, 0x0a,
     312,  299,   11,   11, 0x0a,
     351,  341,   11,   11, 0x0a,
     381,  373,   11,   11, 0x0a,
     417,  406,   11,   11, 0x0a,
     454,  440,   11,   11, 0x0a,
     492,  477,   11,   11, 0x0a,
     537,  523,   11,   11, 0x0a,
     572,  560,   11,   11, 0x0a,
     604,  592,   11,   11, 0x0a,
     638,  624,   11,   11, 0x0a,
     673,  661,   11,   11, 0x0a,
     705,  693,   11,   11, 0x0a,
     738,  725,   11,   11, 0x0a,
     775,  762,   11,   11, 0x0a,
     799,   11,   11,   11, 0x0a,
     824,  812,   11,   11, 0x0a,
     859,  847,   11,   11, 0x0a,
     891,  880,   11,   11, 0x0a,
     923,  913,   11,   11, 0x0a,
     951,  941,   11,   11, 0x0a,
     982,  969,   11,   11, 0x0a,
    1011, 1003,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Parametres[] = {
    "Parametres\0\0render_done\0set_renderdone(bool)\0"
    "pix_grille\0set_pixgrille(int)\0"
    "material_active\0set_materialactive(bool)\0"
    "BRDF_active\0set_BRDFactive(bool)\0"
    "BRDFCheckBox\0set_BRDFcheckbox(QCheckBox*)\0"
    "diff_active\0set_diffactive(bool)\0"
    "diffCheckBox\0set_diffcheckbox(QCheckBox*)\0"
    "spec_active\0set_specactive(bool)\0"
    "specCheckBox\0set_speccheckbox(QCheckBox*)\0"
    "brillance\0set_brillance(double)\0ambiant\0"
    "set_ambiantLight(double)\0saturation\0"
    "set_saturation(double)\0ombres_active\0"
    "set_ombresactive(bool)\0ombresCheckBox\0"
    "set_ombrescheckbox(QCheckBox*)\0"
    "ombres_douces\0set_ombresdouces(bool)\0"
    "ombres_numr\0set_ombresnumr(int)\0"
    "ombres_numa\0set_ombresnuma(int)\0"
    "ambocc_active\0set_amboccactive(bool)\0"
    "ambocc_numr\0set_amboccnumr(int)\0"
    "ambocc_numa\0set_amboccnuma(int)\0"
    "ambocc_theta\0set_ambocctheta(double)\0"
    "ambocc_rayon\0set_amboccrayon(double)\0"
    "set_kddone()\0kd_propdeep\0"
    "set_kdpropdeep(double)\0path_active\0"
    "set_pathactive(bool)\0path_theta\0"
    "set_paththeta(double)\0path_numr\0"
    "set_pathnumr(int)\0path_numa\0"
    "set_pathnuma(int)\0path_maxdeep\0"
    "set_pathmaxdeep(int)\0epsilon\0"
    "set_epsilon(float)\0"
};

const QMetaObject Parametres::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Parametres,
      qt_meta_data_Parametres, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Parametres::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Parametres::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Parametres::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Parametres))
        return static_cast<void*>(const_cast< Parametres*>(this));
    return QObject::qt_metacast(_clname);
}

int Parametres::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: set_renderdone((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: set_pixgrille((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: set_materialactive((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: set_BRDFactive((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: set_BRDFcheckbox((*reinterpret_cast< QCheckBox*(*)>(_a[1]))); break;
        case 5: set_diffactive((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: set_diffcheckbox((*reinterpret_cast< QCheckBox*(*)>(_a[1]))); break;
        case 7: set_specactive((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: set_speccheckbox((*reinterpret_cast< QCheckBox*(*)>(_a[1]))); break;
        case 9: set_brillance((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: set_ambiantLight((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: set_saturation((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: set_ombresactive((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: set_ombrescheckbox((*reinterpret_cast< QCheckBox*(*)>(_a[1]))); break;
        case 14: set_ombresdouces((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: set_ombresnumr((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: set_ombresnuma((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: set_amboccactive((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: set_amboccnumr((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: set_amboccnuma((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: set_ambocctheta((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 21: set_amboccrayon((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 22: set_kddone(); break;
        case 23: set_kdpropdeep((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 24: set_pathactive((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 25: set_paththeta((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 26: set_pathnumr((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: set_pathnuma((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 28: set_pathmaxdeep((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: set_epsilon((*reinterpret_cast< float(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 30;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
