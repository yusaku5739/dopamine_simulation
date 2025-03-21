/* Created by Language version: 7.7.0 */
/* VECTORIZED */
#define NRN_VECTORIZED 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mech_api.h"
#undef PI
#define nil 0
#include "md1redef.h"
#include "section.h"
#include "nrniv_mf.h"
#include "md2redef.h"
 
#if METHOD3
extern int _method3;
#endif

#if !NRNGPU
#undef exp
#define exp hoc_Exp
extern double hoc_Exp(double);
#endif
 
#define nrn_init _nrn_init__leak
#define _nrn_initial _nrn_initial__leak
#define nrn_cur _nrn_cur__leak
#define _nrn_current _nrn_current__leak
#define nrn_jacob _nrn_jacob__leak
#define nrn_state _nrn_state__leak
#define _net_receive _net_receive__leak 
 
#define _threadargscomma_ _p, _ppvar, _thread, _nt,
#define _threadargsprotocomma_ double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt,
#define _threadargs_ _p, _ppvar, _thread, _nt
#define _threadargsproto_ double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 /* Thread safe. No static _p or _ppvar. */
 
#define t _nt->_t
#define dt _nt->_dt
#define gkbar _p[0]
#define gkbar_columnindex 0
#define gnabar _p[1]
#define gnabar_columnindex 1
#define gcabar _p[2]
#define gcabar_columnindex 2
#define ggabaa _p[3]
#define ggabaa_columnindex 3
#define ica _p[4]
#define ica_columnindex 4
#define ina _p[5]
#define ina_columnindex 5
#define ik _p[6]
#define ik_columnindex 6
#define iampa _p[7]
#define iampa_columnindex 7
#define ileak _p[8]
#define ileak_columnindex 8
#define ena _p[9]
#define ena_columnindex 9
#define nai _p[10]
#define nai_columnindex 10
#define icl _p[11]
#define icl_columnindex 11
#define v _p[12]
#define v_columnindex 12
#define _g _p[13]
#define _g_columnindex 13
#define _ion_ica	*_ppvar[0]._pval
#define _ion_dicadv	*_ppvar[1]._pval
#define _ion_nai	*_ppvar[2]._pval
#define _ion_ena	*_ppvar[3]._pval
#define _ion_ina	*_ppvar[4]._pval
#define _ion_dinadv	*_ppvar[5]._pval
#define _ion_ik	*_ppvar[6]._pval
#define _ion_dikdv	*_ppvar[7]._pval
#define _ion_icl	*_ppvar[8]._pval
#define _ion_dicldv	*_ppvar[9]._pval
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 
#if defined(__cplusplus)
extern "C" {
#endif
 static int hoc_nrnpointerindex =  -1;
 static Datum* _extcall_thread;
 static Prop* _extcall_prop;
 /* external NEURON variables */
 extern double celsius;
 /* declaration of user functions */
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 
#define NMODL_TEXT 1
#if NMODL_TEXT
static const char* nmodl_file_text;
static const char* nmodl_filename;
extern void hoc_reg_nmodl_text(int, const char*);
extern void hoc_reg_nmodl_filename(int, const char*);
#endif

 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _extcall_prop = _prop;
 }
 static void _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range(int);
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 hoc_retpushx(1.);
}
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 "setdata_leak", _hoc_setdata,
 0, 0
};
 /* declare global and static user variables */
#define ek ek_leak
 double ek = -90;
#define ecl ecl_leak
 double ecl = -70;
#define eca eca_leak
 double eca = 120;
#define eampa eampa_leak
 double eampa = 0;
#define gampa gampa_leak
 double gampa = 0;
#define nao nao_leak
 double nao = 145;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "gampa_leak", "S/cm2",
 "eampa_leak", "mV",
 "eca_leak", "mV",
 "ecl_leak", "mV",
 "ek_leak", "mV",
 "nao_leak", "mM",
 "gkbar_leak", "S/cm2",
 "gnabar_leak", "S/cm2",
 "gcabar_leak", "S/cm2",
 "ggabaa_leak", "S/cm2",
 "ica_leak", "mA/cm2",
 "ina_leak", "mA/cm2",
 "ik_leak", "mA/cm2",
 "iampa_leak", "mA/cm2",
 "ileak_leak", "mA/cm2",
 0,0
};
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "gampa_leak", &gampa_leak,
 "eampa_leak", &eampa_leak,
 "eca_leak", &eca_leak,
 "ecl_leak", &ecl_leak,
 "ek_leak", &ek_leak,
 "nao_leak", &nao_leak,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(NrnThread*, _Memb_list*, int);
static void nrn_state(NrnThread*, _Memb_list*, int);
 static void nrn_cur(NrnThread*, _Memb_list*, int);
static void  nrn_jacob(NrnThread*, _Memb_list*, int);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"leak",
 "gkbar_leak",
 "gnabar_leak",
 "gcabar_leak",
 "ggabaa_leak",
 0,
 "ica_leak",
 "ina_leak",
 "ik_leak",
 "iampa_leak",
 "ileak_leak",
 0,
 0,
 0};
 static Symbol* _ca_sym;
 static Symbol* _na_sym;
 static Symbol* _k_sym;
 static Symbol* _cl_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 14, _prop);
 	/*initialize range parameters*/
 	gkbar = 5.5e-06;
 	gnabar = 2.375e-06;
 	gcabar = 1.36e-07;
 	ggabaa = 0;
 	_prop->param = _p;
 	_prop->param_size = 14;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 10, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_ca_sym);
 	_ppvar[0]._pval = &prop_ion->param[3]; /* ica */
 	_ppvar[1]._pval = &prop_ion->param[4]; /* _ion_dicadv */
 prop_ion = need_memb(_na_sym);
 nrn_promote(prop_ion, 1, 1);
 	_ppvar[2]._pval = &prop_ion->param[1]; /* nai */
 	_ppvar[3]._pval = &prop_ion->param[0]; /* ena */
 	_ppvar[4]._pval = &prop_ion->param[3]; /* ina */
 	_ppvar[5]._pval = &prop_ion->param[4]; /* _ion_dinadv */
 prop_ion = need_memb(_k_sym);
 	_ppvar[6]._pval = &prop_ion->param[3]; /* ik */
 	_ppvar[7]._pval = &prop_ion->param[4]; /* _ion_dikdv */
 prop_ion = need_memb(_cl_sym);
 	_ppvar[8]._pval = &prop_ion->param[3]; /* icl */
 	_ppvar[9]._pval = &prop_ion->param[4]; /* _ion_dicldv */
 
}
 static void _initlists();
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _newleak_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("ca", -10000.);
 	ion_reg("na", -10000.);
 	ion_reg("k", -10000.);
 	ion_reg("cl", 1.0);
 	_ca_sym = hoc_lookup("ca_ion");
 	_na_sym = hoc_lookup("na_ion");
 	_k_sym = hoc_lookup("k_ion");
 	_cl_sym = hoc_lookup("cl_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 14, 10);
  hoc_register_dparam_semantics(_mechtype, 0, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 4, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 5, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 6, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 7, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 8, "cl_ion");
  hoc_register_dparam_semantics(_mechtype, 9, "cl_ion");
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 leak /home/workspace/266814/newleak.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 
#define F _nrnunit_F[_nrnunit_use_legacy_]
static double _nrnunit_F[2] = {0x1.78e555060882cp+16, 96485.3}; /* 96485.3321233100141 */
 
#define R _nrnunit_R[_nrnunit_use_legacy_]
static double _nrnunit_R[2] = {0x1.03d3b37125759p+13, 8314.5}; /* 8314.46261815323851 */
static int _reset;
static char *modelname = "Leak current including GABA_A receptor current";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_ca_sym, _ppvar, 0, 3);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 1, 4);
   nrn_update_ion_pointer(_na_sym, _ppvar, 2, 1);
   nrn_update_ion_pointer(_na_sym, _ppvar, 3, 0);
   nrn_update_ion_pointer(_na_sym, _ppvar, 4, 3);
   nrn_update_ion_pointer(_na_sym, _ppvar, 5, 4);
   nrn_update_ion_pointer(_k_sym, _ppvar, 6, 3);
   nrn_update_ion_pointer(_k_sym, _ppvar, 7, 4);
   nrn_update_ion_pointer(_cl_sym, _ppvar, 8, 3);
   nrn_update_ion_pointer(_cl_sym, _ppvar, 9, 4);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
  int _i; double _save;{

}
}

static void nrn_init(NrnThread* _nt, _Memb_list* _ml, int _type){
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v = _v;
  nai = _ion_nai;
  ena = _ion_ena;
 initmodel(_p, _ppvar, _thread, _nt);
    }
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   ena = 50.0 ;
   ica = gcabar * ( v - eca ) ;
   ina = gnabar * ( v - ena ) ;
   icl = ggabaa * ( v - ecl ) ;
   ik = gkbar * ( v - ek ) ;
   iampa = gampa * ( v - eampa ) ;
   ileak = ica + ina + ik + icl + iampa ;
   }
 _current += iampa;
 _current += ica;
 _current += ina;
 _current += ik;
 _current += icl;

} return _current;
}

static void nrn_cur(NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
  nai = _ion_nai;
  ena = _ion_ena;
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ double _dicl;
 double _dik;
 double _dina;
 double _dica;
  _dica = ica;
  _dina = ina;
  _dik = ik;
  _dicl = icl;
 _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
  _ion_dicadv += (_dica - ica)/.001 ;
  _ion_dinadv += (_dina - ina)/.001 ;
  _ion_dikdv += (_dik - ik)/.001 ;
  _ion_dicldv += (_dicl - icl)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ica += ica ;
  _ion_ina += ina ;
  _ion_ik += ik ;
  _ion_icl += icl ;
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
  }
 
}
 
}

static void nrn_jacob(NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml];
#if CACHEVEC
  if (use_cachevec) {
	VEC_D(_ni[_iml]) += _g;
  }else
#endif
  {
     _nd = _ml->_nodelist[_iml];
	NODED(_nd) += _g;
  }
 
}
 
}

static void nrn_state(NrnThread* _nt, _Memb_list* _ml, int _type) {

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/home/workspace/266814/newleak.mod";
static const char* nmodl_file_text = 
  "TITLE Leak current including GABA_A receptor current\n"
  " \n"
  "\n"
  "UNITS {\n"
  "        (pA) = (picoamp)\n"
  "        (molar) = (1/liter)\n"
  "	(mV) =	(millivolt)\n"
  "        (S)  =  (siemens)\n"
  "	(mA) =	(milliamp)\n"
  "	(mM) =	(millimolar)\n"
  "         F = (faraday) (coulomb)\n"
  "         R = (mole k)  (mV-coulomb/degC)\n"
  "}\n"
  "\n"
  "\n"
  "INDEPENDENT {v FROM -100 TO 50 WITH 50 (mV)}\n"
  "\n"
  "NEURON {\n"
  "	SUFFIX leak\n"
  "        NONSPECIFIC_CURRENT iampa\n"
  "	USEION ca WRITE ica\n"
  "	USEION na READ nai,ena  WRITE ina\n"
  "	USEION k  WRITE ik\n"
  "	USEION cl WRITE icl VALENCE 1\n"
  "	RANGE  gcabar,ileak,ina,ica,ik,gnabar,gkbar,nai,ggabaa, iampa\n"
  " \n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "        dt      (ms)\n"
  "        ena     (mV)\n"
  "        nai     (mM)\n"
  "        celsius = 35      (degC)\n"
  "        gkbar   = 5.5e-6 (S/cm2)\n"
  "        gnabar  = 2.375e-6  (S/cm2)\n"
  "        gcabar  = 0.136e-6  (S/cm2)\n"
  "        ggabaa  = 0.0e-6  (S/cm2)\n"
  "        gampa = 0.0e-6 (S/cm2)\n"
  "        eampa = 0 (mV)\n"
  "        eca =   120 (mV)\n"
  "        ecl =  -70  (mV)\n"
  "        ek  =  -90.0 (mV)\n"
  "        nao =   145 (mM)\n"
  "        \n"
  "}\n"
  "\n"
  "ASSIGNED { \n"
  "           ica	  (mA/cm2)\n"
  "           ina	  (mA/cm2)\n"
  "           ik	  (mA/cm2)\n"
  "           icl	  (mA/cm2)\n"
  "           iampa  (mA/cm2)\n"
  "           ileak  (mA/cm2)\n"
  "}\n"
  "\n"
  "\n"
  "BREAKPOINT {\n"
  "        ena = 50\n"
  "	ica = gcabar*(v-eca)\n"
  "	ina = gnabar*(v-ena)\n"
  "	icl = ggabaa*(v-ecl)\n"
  "	ik = gkbar*(v-ek)\n"
  "        iampa = gampa*(v-eampa)\n"
  "        ileak= ica + ina + ik + icl + iampa\n"
  "}\n"
  ;
#endif
