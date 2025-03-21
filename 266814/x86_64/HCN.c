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
 
#define nrn_init _nrn_init__hcn
#define _nrn_initial _nrn_initial__hcn
#define nrn_cur _nrn_cur__hcn
#define _nrn_current _nrn_current__hcn
#define nrn_jacob _nrn_jacob__hcn
#define nrn_state _nrn_state__hcn
#define _net_receive _net_receive__hcn 
#define rates rates__hcn 
#define states states__hcn 
 
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
#define ghcnbar _p[0]
#define ghcnbar_columnindex 0
#define km _p[1]
#define km_columnindex 1
#define mhalf _p[2]
#define mhalf_columnindex 2
#define aslope _p[3]
#define aslope_columnindex 3
#define bhalf _p[4]
#define bhalf_columnindex 4
#define bslope _p[5]
#define bslope_columnindex 5
#define tau1 _p[6]
#define tau1_columnindex 6
#define tau2 _p[7]
#define tau2_columnindex 7
#define ehcn _p[8]
#define ehcn_columnindex 8
#define scale _p[9]
#define scale_columnindex 9
#define ihcn _p[10]
#define ihcn_columnindex 10
#define ghcn _p[11]
#define ghcn_columnindex 11
#define minf _p[12]
#define minf_columnindex 12
#define mtau _p[13]
#define mtau_columnindex 13
#define m _p[14]
#define m_columnindex 14
#define Dm _p[15]
#define Dm_columnindex 15
#define alpha _p[16]
#define alpha_columnindex 16
#define beta _p[17]
#define beta_columnindex 17
#define v _p[18]
#define v_columnindex 18
#define _g _p[19]
#define _g_columnindex 19
 
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
 static void _hoc_rates(void);
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
 "setdata_hcn", _hoc_setdata,
 "boltz_hcn", _hoc_boltz,
 "gaussian_hcn", _hoc_gaussian,
 "rates_hcn", _hoc_rates,
 0, 0
};
#define boltz boltz_hcn
#define gaussian gaussian_hcn
 extern double boltz( _threadargsprotocomma_ double , double , double );
 extern double gaussian( _threadargsprotocomma_ double , double , double , double , double );
 /* declare global and static user variables */
#define gcahvabar gcahvabar_hcn
 double gcahvabar = 0;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "gcahvabar_hcn", "S/cm2",
 "ghcnbar_hcn", "S/cm2",
 "km_hcn", "mV",
 "mhalf_hcn", "mV",
 "ehcn_hcn", "mV",
 "ihcn_hcn", "mA/cm2",
 "ghcn_hcn", "S/cm2",
 0,0
};
 static double delta_t = 1;
 static double m0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "gcahvabar_hcn", &gcahvabar_hcn,
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
 
#define _cvode_ieq _ppvar[0]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"hcn",
 "ghcnbar_hcn",
 "km_hcn",
 "mhalf_hcn",
 "aslope_hcn",
 "bhalf_hcn",
 "bslope_hcn",
 "tau1_hcn",
 "tau2_hcn",
 "ehcn_hcn",
 "scale_hcn",
 0,
 "ihcn_hcn",
 "ghcn_hcn",
 "minf_hcn",
 "mtau_hcn",
 0,
 "m_hcn",
 0,
 0};
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 20, _prop);
 	/*initialize range parameters*/
 	ghcnbar = 1.1196e-05;
 	km = -5;
 	mhalf = -75;
 	aslope = 10.2;
 	bhalf = -10;
 	bslope = -100;
 	tau1 = 2e-08;
 	tau2 = 0.0076;
 	ehcn = -35;
 	scale = 1;
 	_prop->param = _p;
 	_prop->param_size = 20;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 1, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _HCN_reg() {
	int _vectorized = 1;
  _initlists();
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 20, 1);
  hoc_register_dparam_semantics(_mechtype, 0, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 hcn /home/workspace/266814/HCN.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 
#define F _nrnunit_F[_nrnunit_use_legacy_]
static double _nrnunit_F[2] = {0x1.78e555060882cp+16, 96485.3}; /* 96485.3321233100141 */
 
#define R _nrnunit_R[_nrnunit_use_legacy_]
static double _nrnunit_R[2] = {0x1.03d3b37125759p+13, 8314.5}; /* 8314.46261815323851 */
static int _reset;
static char *modelname = "HCN model from Tarfa Evans and Khaliq 2017";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int rates(_threadargsprotocomma_ double);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[1], _dlist1[1];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {int _reset = 0; {
   rates ( _threadargscomma_ v ) ;
   minf = boltz ( _threadargscomma_ v , mhalf , km ) ;
   mtau = scale / ( alpha + beta ) ;
   Dm = ( minf - m ) / mtau ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
 rates ( _threadargscomma_ v ) ;
 minf = boltz ( _threadargscomma_ v , mhalf , km ) ;
 mtau = scale / ( alpha + beta ) ;
 Dm = Dm  / (1. - dt*( ( ( ( - 1.0 ) ) ) / mtau )) ;
  return 0;
}
 /*END CVODE*/
 static int states (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) { {
   rates ( _threadargscomma_ v ) ;
   minf = boltz ( _threadargscomma_ v , mhalf , km ) ;
   mtau = scale / ( alpha + beta ) ;
    m = m + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / mtau)))*(- ( ( ( minf ) ) / mtau ) / ( ( ( ( - 1.0 ) ) ) / mtau ) - m) ;
   }
  return 0;
}
 
static int  rates ( _threadargsprotocomma_ double _lvx ) {
   alpha = tau1 * exp ( - _lvx / aslope ) ;
   beta = tau2 * boltz ( _threadargscomma_ _lvx , bhalf , - bslope ) ;
    return 0; }
 
static void _hoc_rates(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r = 1.;
 rates ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
double gaussian ( _threadargsprotocomma_ double _lv , double _la , double _lb , double _lc , double _ld ) {
   double _lgaussian;
 double _larg ;
 _larg = _lb * exp ( - 0.5 * ( _lv - _lc ) * ( _lv - _lc ) / ( _ld * _ld ) ) + _la ;
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
 
static int _ode_count(int _type){ return 1;}
 
static void _ode_spec(NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
     _ode_spec1 (_p, _ppvar, _thread, _nt);
 }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
	double* _p; Datum* _ppvar;
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 1; ++_i) {
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
 _ode_matsol_instance1(_threadargs_);
 }}

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
  int _i; double _save;{
  m = m0;
 {
   rates ( _threadargscomma_ v ) ;
   mtau = scale / ( alpha + beta ) ;
   minf = boltz ( _threadargscomma_ v , mhalf , km ) ;
   m = minf ;
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
 initmodel(_p, _ppvar, _thread, _nt);
}
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   ghcn = ghcnbar * m ;
   ihcn = ghcn * ( v - ehcn ) ;
   }
 _current += ihcn;

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
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
 	}
 _g = (_g - _rhs)/.001;
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
 {   states(_p, _ppvar, _thread, _nt);
  }}}

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = m_columnindex;  _dlist1[0] = Dm_columnindex;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/home/workspace/266814/HCN.mod";
static const char* nmodl_file_text = 
  "TITLE HCN model from Tarfa Evans and Khaliq 2017\n"
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
  "        SUFFIX hcn\n"
  "        NONSPECIFIC_CURRENT ihcn\n"
  "        : make this sodium/potassium eventually\n"
  "        RANGE  ghcnbar, ehcn, mhalf,tau1,aslope,tau2,bhalf,bslope,ghcn, minf,mtau,scale,km\n"
  "        :GLOBAL minf : creates a shared lookup table\n"
  "}\n"
  " \n"
  "INDEPENDENT {t FROM 0 TO 1 WITH 1 (ms)}\n"
  " \n"
  "PARAMETER {\n"
  "        v (mV)\n"
  "        dt (ms)\n"
  "        celsius =  35.0      (degC)\n"
  "        gcahvabar =  0.0e-6 (S/cm2)\n"
  "        ghcnbar =  11.196e-6  (S/cm2)\n"
  "        km = -5.0 (mV)\n"
  "        mhalf = -75.0 (mV) : \n"
  "        aslope = 10.2\n"
  "        bhalf = -10\n"
  "        bslope = -100\n"
  "        tau1 = 2.0e-8\n"
  "        tau2 = 7.6e-3\n"
  "        :vtau = -80.0 (mV)\n"
  "        :stau = 11.06 (mV)\n"
  "        ehcn = -35 (mV)\n"
  "        scale = 1.0\n"
  "}\n"
  " \n"
  "STATE {\n"
  "        m\n"
  "}\n"
  " \n"
  "ASSIGNED {\n"
  "        ihcn (mA/cm2)\n"
  "        ghcn (S/cm2)\n"
  "        minf\n"
  "        mtau\n"
  "        alpha\n"
  "        beta\n"
  " }\n"
  " \n"
  "BREAKPOINT {\n"
  "        SOLVE states METHOD cnexp\n"
  "        ghcn = ghcnbar*m\n"
  "        ihcn = ghcn*(v-ehcn)\n"
  "}\n"
  " \n"
  "UNITSOFF\n"
  " \n"
  "INITIAL {\n"
  "      rates(v)\n"
  "      :mtau = gaussian(v,tau1,tau2,vtau,stau)\n"
  "      mtau = scale/(alpha+beta)\n"
  "      minf = boltz(v,mhalf,km)\n"
  "      m= minf\n"
  "}\n"
  "\n"
  "DERIVATIVE states {  :Computes state variables m\n"
  ":LOCAL minf, mtau\n"
  "   rates(v) : calculate alpha, beta\n"
  "   minf = boltz(v,mhalf,km)\n"
  "   :mtau = gaussian(v,tau1,tau2,vtau,stau)\n"
  "   mtau = scale/(alpha+beta)\n"
  "   m' = (minf-m)/mtau\n"
  "   \n"
  "}\n"
  "\n"
  "PROCEDURE rates(vx) {\n"
  "	alpha = tau1*exp(-vx/aslope)\n"
  "	beta = tau2*boltz(vx,bhalf,-bslope)\n"
  "}\n"
  " \n"
  " \n"
  "FUNCTION gaussian(v,a,b,c,d) {\n"
  "        LOCAL arg\n"
  "        arg= b*exp(-0.5*(v-c)*(v-c)/(d*d)) +a\n"
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
