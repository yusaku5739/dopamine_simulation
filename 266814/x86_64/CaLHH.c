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
 
#define nrn_init _nrn_init__calhh
#define _nrn_initial _nrn_initial__calhh
#define nrn_cur _nrn_cur__calhh
#define _nrn_current _nrn_current__calhh
#define nrn_jacob _nrn_jacob__calhh
#define nrn_state _nrn_state__calhh
#define _net_receive _net_receive__calhh 
#define states states__calhh 
 
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
#define gcalbar _p[0]
#define gcalbar_columnindex 0
#define skcoup _p[1]
#define skcoup_columnindex 1
#define mhalf _p[2]
#define mhalf_columnindex 2
#define mslope _p[3]
#define mslope_columnindex 3
#define pf _p[4]
#define pf_columnindex 4
#define ica _p[5]
#define ica_columnindex 5
#define ical _p[6]
#define ical_columnindex 6
#define incal _p[7]
#define incal_columnindex 7
#define dl _p[8]
#define dl_columnindex 8
#define hl _p[9]
#define hl_columnindex 9
#define cai _p[10]
#define cai_columnindex 10
#define Ddl _p[11]
#define Ddl_columnindex 11
#define Dhl _p[12]
#define Dhl_columnindex 12
#define gcal _p[13]
#define gcal_columnindex 13
#define dlinf _p[14]
#define dlinf_columnindex 14
#define hlinf _p[15]
#define hlinf_columnindex 15
#define v _p[16]
#define v_columnindex 16
#define _g _p[17]
#define _g_columnindex 17
#define _ion_cai	*_ppvar[0]._pval
#define _ion_ica	*_ppvar[1]._pval
#define _ion_dicadv	*_ppvar[2]._pval
 
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
 static void _hoc_boltz(void);
 static void _hoc_gaussian(void);
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
 "setdata_calhh", _hoc_setdata,
 "boltz_calhh", _hoc_boltz,
 "gaussian_calhh", _hoc_gaussian,
 0, 0
};
#define boltz boltz_calhh
#define gaussian gaussian_calhh
 extern double boltz( _threadargsprotocomma_ double , double , double );
 extern double gaussian( _threadargsprotocomma_ double , double , double , double , double );
 /* declare global and static user variables */
#define cao cao_calhh
 double cao = 2;
#define eca eca_calhh
 double eca = 120;
#define kml kml_calhh
 double kml = 0.00045;
#define km km_calhh
 double km = 0.0001;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "km_calhh", "mM",
 "kml_calhh", "mM",
 "eca_calhh", "mV",
 "cao_calhh", "mM",
 "gcalbar_calhh", "S/cm2",
 "ica_calhh", "mA/cm2",
 "ical_calhh", "mA/cm2",
 "incal_calhh", "mA/cm2",
 0,0
};
 static double delta_t = 1;
 static double dl0 = 0;
 static double hl0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "km_calhh", &km_calhh,
 "kml_calhh", &kml_calhh,
 "eca_calhh", &eca_calhh,
 "cao_calhh", &cao_calhh,
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
 
static int _ode_count(int);
static void _ode_map(int, double**, double**, double*, Datum*, double*, int);
static void _ode_spec(NrnThread*, _Memb_list*, int);
static void _ode_matsol(NrnThread*, _Memb_list*, int);
 
#define _cvode_ieq _ppvar[3]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"calhh",
 "gcalbar_calhh",
 "skcoup_calhh",
 "mhalf_calhh",
 "mslope_calhh",
 "pf_calhh",
 0,
 "ica_calhh",
 "ical_calhh",
 "incal_calhh",
 0,
 "dl_calhh",
 "hl_calhh",
 0,
 0};
 static Symbol* _ca_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 18, _prop);
 	/*initialize range parameters*/
 	gcalbar = 1.1196e-05;
 	skcoup = 1;
 	mhalf = -30;
 	mslope = 8;
 	pf = 0.6;
 	_prop->param = _p;
 	_prop->param_size = 18;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 4, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_ca_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[0]._pval = &prop_ion->param[1]; /* cai */
 	_ppvar[1]._pval = &prop_ion->param[3]; /* ica */
 	_ppvar[2]._pval = &prop_ion->param[4]; /* _ion_dicadv */
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _CaLHH_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("ca", -10000.);
 	_ca_sym = hoc_lookup("ca_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 18, 4);
  hoc_register_dparam_semantics(_mechtype, 0, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 calhh /home/workspace/266814/CaLHH.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 
#define F _nrnunit_F[_nrnunit_use_legacy_]
static double _nrnunit_F[2] = {0x1.78e555060882cp+16, 96485.3}; /* 96485.3321233100141 */
 
#define R _nrnunit_R[_nrnunit_use_legacy_]
static double _nrnunit_R[2] = {0x1.03d3b37125759p+13, 8314.5}; /* 8314.46261815323851 */
static int _reset;
static char *modelname = "calcium channel (L type) ";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[2], _dlist1[2];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {int _reset = 0; {
   double _ldlinf , _ldhvainf , _lfhvainf , _ldltau , _ldhvatau , _lfhvatau , _lhltau , _lhlinf ;
 _ldlinf = boltz ( _threadargscomma_ v , mhalf , mslope ) ;
   _lhlinf = boltz ( _threadargscomma_ v , - 55.0 , - 2.0 ) ;
   _ldltau = gaussian ( _threadargscomma_ v , 9.0 , 25.0 , 70.0 , 0.30 ) ;
   _lhltau = 100.0 + 100.0 * boltz ( _threadargscomma_ v , - 30.0 , - 5.0 ) ;
   Ddl = ( _ldlinf - dl ) / _ldltau ;
   Dhl = ( _lhlinf - hl ) / _lhltau ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
 double _ldlinf , _ldhvainf , _lfhvainf , _ldltau , _ldhvatau , _lfhvatau , _lhltau , _lhlinf ;
 _ldlinf = boltz ( _threadargscomma_ v , mhalf , mslope ) ;
 _lhlinf = boltz ( _threadargscomma_ v , - 55.0 , - 2.0 ) ;
 _ldltau = gaussian ( _threadargscomma_ v , 9.0 , 25.0 , 70.0 , 0.30 ) ;
 _lhltau = 100.0 + 100.0 * boltz ( _threadargscomma_ v , - 30.0 , - 5.0 ) ;
 Ddl = Ddl  / (1. - dt*( ( ( ( - 1.0 ) ) ) / _ldltau )) ;
 Dhl = Dhl  / (1. - dt*( ( ( ( - 1.0 ) ) ) / _lhltau )) ;
  return 0;
}
 /*END CVODE*/
 static int states (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) { {
   double _ldlinf , _ldhvainf , _lfhvainf , _ldltau , _ldhvatau , _lfhvatau , _lhltau , _lhlinf ;
 _ldlinf = boltz ( _threadargscomma_ v , mhalf , mslope ) ;
   _lhlinf = boltz ( _threadargscomma_ v , - 55.0 , - 2.0 ) ;
   _ldltau = gaussian ( _threadargscomma_ v , 9.0 , 25.0 , 70.0 , 0.30 ) ;
   _lhltau = 100.0 + 100.0 * boltz ( _threadargscomma_ v , - 30.0 , - 5.0 ) ;
    dl = dl + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / _ldltau)))*(- ( ( ( _ldlinf ) ) / _ldltau ) / ( ( ( ( - 1.0 ) ) ) / _ldltau ) - dl) ;
    hl = hl + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / _lhltau)))*(- ( ( ( _lhlinf ) ) / _lhltau ) / ( ( ( ( - 1.0 ) ) ) / _lhltau ) - hl) ;
   }
  return 0;
}
 
double gaussian ( _threadargsprotocomma_ double _lv , double _la , double _lb , double _lc , double _ld ) {
   double _lgaussian;
 double _larg ;
 _larg = _la * exp ( - ( _lc + _lv ) * ( _lv + _lc ) / ( _lb * _lb ) ) + _ld ;
   _lgaussian = _larg ;
   
return _lgaussian;
 }
 
static void _hoc_gaussian(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  gaussian ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) , *getarg(3) , *getarg(4) , *getarg(5) );
 hoc_retpushx(_r);
}
 
double boltz ( _threadargsprotocomma_ double _lx , double _ly , double _lz ) {
   double _lboltz;
 double _larg ;
 _larg = - ( _lx - _ly ) / _lz ;
   if ( _larg > 50.0 ) {
     _lboltz = 0.0 ;
     }
   else {
     if ( _larg < - 50.0 ) {
       _lboltz = 1.0 ;
       }
     else {
       _lboltz = 1.0 / ( 1.0 + exp ( _larg ) ) ;
       }
     }
   
return _lboltz;
 }
 
static void _hoc_boltz(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  boltz ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) , *getarg(3) );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ return 2;}
 
static void _ode_spec(NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  cai = _ion_cai;
     _ode_spec1 (_p, _ppvar, _thread, _nt);
  }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
	double* _p; Datum* _ppvar;
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 2; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _ode_matsol1 (_p, _ppvar, _thread, _nt);
 }
 
static void _ode_matsol(NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  cai = _ion_cai;
 _ode_matsol_instance1(_threadargs_);
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_ca_sym, _ppvar, 0, 1);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 1, 3);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 2, 4);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
  int _i; double _save;{
  dl = dl0;
  hl = hl0;
 {
   dl = boltz ( _threadargscomma_ v , mhalf , 5.0 ) ;
   hl = boltz ( _threadargscomma_ v , - 55.0 , - 2.0 ) ;
   }
 
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
  cai = _ion_cai;
 initmodel(_p, _ppvar, _thread, _nt);
 }
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   gcal = dl * ( 1.0 - pf + pf * hl ) ;
   ical = gcalbar * gcal * ( v - eca ) ;
   incal = ( 1.0 - skcoup ) * ical ;
   ica = ( skcoup ) * ical ;
   }
 _current += incal;
 _current += ica;

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
  cai = _ion_cai;
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ double _dica;
  _dica = ica;
 _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
  _ion_dicadv += (_dica - ica)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ica += ica ;
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
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v=_v;
{
  cai = _ion_cai;
 {   states(_p, _ppvar, _thread, _nt);
  } }}

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = dl_columnindex;  _dlist1[0] = Ddl_columnindex;
 _slist1[1] = hl_columnindex;  _dlist1[1] = Dhl_columnindex;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/home/workspace/266814/CaLHH.mod";
static const char* nmodl_file_text = 
  "TITLE calcium channel (L type) \n"
  " \n"
  "UNITS {\n"
  "       (molar) = (1/liter)\n"
  "       (S)  = (siemens)\n"
  "       (mA) = (milliamp)\n"
  "       (mV) = (millivolt)\n"
  "       (mM) = (millimolar)\n"
  "        F = (faraday)  (coulomb)\n"
  "        R = (mole k)   (mV-coulomb/degC)\n"
  "       \n"
  "}\n"
  " \n"
  "NEURON {\n"
  "        SUFFIX calhh\n"
  "        NONSPECIFIC_CURRENT incal\n"
  "        USEION ca READ cai WRITE ica\n"
  "        RANGE  gcalbar,ica,ical,incal, mhalf, mslope,skcoup, pf\n"
  "}\n"
  " \n"
  "INDEPENDENT {t FROM 0 TO 1 WITH 1 (ms)}\n"
  " \n"
  "PARAMETER {\n"
  "        v (mV)\n"
  "        dt (ms)\n"
  "        cai   (mM)\n"
  "        celsius =  35.0      (degC)\n"
  "        gcalbar =  11.196e-6  (S/cm2)\n"
  "        km = 0.0001   (mM)\n"
  "        kml = 0.00045  (mM)\n"
  "        eca = 120 (mV)\n"
  "        cao = 2.0 (mM)\n"
  "        skcoup = 1.0\n"
  "        mhalf = -30.0\n"
  "        mslope = 8.0\n"
  "        pf = 0.6\n"
  "        \n"
  "}\n"
  " \n"
  "STATE {\n"
  "        dl hl\n"
  "}\n"
  " \n"
  "ASSIGNED {\n"
  "        ica (mA/cm2)\n"
  "        ical (mA/cm2)\n"
  "        incal (mA/cm2)\n"
  "        gcal (S/cm2)\n"
  "        dlinf\n"
  "        hlinf \n"
  " }\n"
  " \n"
  "BREAKPOINT {\n"
  "        SOLVE states METHOD cnexp\n"
  "        gcal = dl*(1.0 - pf + pf*hl)\n"
  "        ical = gcalbar*gcal*(v-eca)\n"
  "        incal = (1-skcoup)*ical\n"
  "        ica  = (skcoup)*ical\n"
  "}\n"
  " \n"
  "UNITSOFF\n"
  " \n"
  "INITIAL {\n"
  "        dl = boltz(v,mhalf,5.0)\n"
  "        hl = boltz(v,-55,-2.0)\n"
  "}\n"
  "\n"
  "DERIVATIVE states {  :Computes state variables m, h, and n \n"
  "LOCAL dlinf,dhvainf,fhvainf,dltau,dhvatau,fhvatau,hltau,hlinf\n"
  "        :dlinf = boltz(v,-39.0,5.0) : sharper dlinf needed for SOPs\n"
  "        dlinf = boltz(v,mhalf,mslope)\n"
  "        hlinf = boltz(v,-55,-2)\n"
  "        dltau = gaussian(v,9.0,25.0,70.0,0.30)\n"
  "        hltau = 100.0 + 100.0*boltz(v,-30,-5.0)\n"
  "        :dltau = 5.0 + 50.0 * boltz(v,-40.0, -5.0)\n"
  "        :dltau = gaussian(v,25.0,10.0,50.0,5.00)\n"
  "        :dltau = 1.0\n"
  "        dl'  = (dlinf-dl)/dltau\n"
  "        hl' = (hlinf-hl)/hltau\n"
  "}\n"
  " \n"
  " \n"
  "FUNCTION gaussian(v,a,b,c,d) {\n"
  "        LOCAL arg\n"
  "        arg= a*exp(-(c+v)*(v+c)/(b*b)) +d\n"
  "        gaussian = arg\n"
  "}\n"
  " \n"
  " \n"
  "FUNCTION boltz(x,y,z) {\n"
  "               LOCAL arg\n"
  "                arg= -(x-y)/z\n"
  "                if (arg > 50) {boltz = 0}\n"
  "                else {if (arg < -50) {boltz = 1}\n"
  "                else {boltz = 1.0/(1.0 + exp(arg))}}\n"
  "}\n"
  "\n"
  " \n"
  "UNITSON\n"
  "\n"
  ;
#endif
