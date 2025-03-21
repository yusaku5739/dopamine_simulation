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
 
#define nrn_init _nrn_init__hhb
#define _nrn_initial _nrn_initial__hhb
#define nrn_cur _nrn_cur__hhb
#define _nrn_current _nrn_current__hhb
#define nrn_jacob _nrn_jacob__hhb
#define nrn_state _nrn_state__hhb
#define _net_receive _net_receive__hhb 
#define rates rates__hhb 
#define states states__hhb 
 
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
#define gnabar _p[0]
#define gnabar_columnindex 0
#define gkhhbar _p[1]
#define gkhhbar_columnindex 1
#define gkabar _p[2]
#define gkabar_columnindex 2
#define shift _p[3]
#define shift_columnindex 3
#define sshift _p[4]
#define sshift_columnindex 4
#define hshift _p[5]
#define hshift_columnindex 5
#define ashift _p[6]
#define ashift_columnindex 6
#define nshift _p[7]
#define nshift_columnindex 7
#define nslope _p[8]
#define nslope_columnindex 8
#define bkcor _p[9]
#define bkcor_columnindex 9
#define deptog _p[10]
#define deptog_columnindex 10
#define vhblock _p[11]
#define vhblock_columnindex 11
#define taukv4 _p[12]
#define taukv4_columnindex 12
#define asshift _p[13]
#define asshift_columnindex 13
#define fptog _p[14]
#define fptog_columnindex 14
#define qfix _p[15]
#define qfix_columnindex 15
#define nspeed _p[16]
#define nspeed_columnindex 16
#define ina _p[17]
#define ina_columnindex 17
#define ik _p[18]
#define ik_columnindex 18
#define ika _p[19]
#define ika_columnindex 19
#define ikhh _p[20]
#define ikhh_columnindex 20
#define ena _p[21]
#define ena_columnindex 21
#define minf _p[22]
#define minf_columnindex 22
#define hinf _p[23]
#define hinf_columnindex 23
#define ninf _p[24]
#define ninf_columnindex 24
#define qinf _p[25]
#define qinf_columnindex 25
#define pinf _p[26]
#define pinf_columnindex 26
#define hsinf _p[27]
#define hsinf_columnindex 27
#define mtau _p[28]
#define mtau_columnindex 28
#define htau _p[29]
#define htau_columnindex 29
#define hstau _p[30]
#define hstau_columnindex 30
#define qtau _p[31]
#define qtau_columnindex 31
#define ptau _p[32]
#define ptau_columnindex 32
#define ntau _p[33]
#define ntau_columnindex 33
#define gk _p[34]
#define gk_columnindex 34
#define gka _p[35]
#define gka_columnindex 35
#define n _p[36]
#define n_columnindex 36
#define p _p[37]
#define p_columnindex 37
#define q _p[38]
#define q_columnindex 38
#define Dn _p[39]
#define Dn_columnindex 39
#define Dp _p[40]
#define Dp_columnindex 40
#define Dq _p[41]
#define Dq_columnindex 41
#define v _p[42]
#define v_columnindex 42
#define _g _p[43]
#define _g_columnindex 43
#define _ion_ik	*_ppvar[0]._pval
#define _ion_dikdv	*_ppvar[1]._pval
 
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
 "setdata_hhb", _hoc_setdata,
 "boltz_hhb", _hoc_boltz,
 "rates_hhb", _hoc_rates,
 0, 0
};
#define boltz boltz_hhb
 extern double boltz( _threadargsprotocomma_ double , double , double );
 /* declare global and static user variables */
#define ek ek_hhb
 double ek = -90;
#define nao nao_hhb
 double nao = 145;
#define nai nai_hhb
 double nai = 0;
#define qs qs_hhb
 double qs = 10;
#define qv qv_hhb
 double qv = 66;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "nai_hhb", "mM",
 "ek_hhb", "mV",
 "nao_hhb", "mM",
 "qv_hhb", "mV",
 "qs_hhb", "1",
 "gnabar_hhb", "S/cm2",
 "gkhhbar_hhb", "S/cm2",
 "gkabar_hhb", "S/cm2",
 "shift_hhb", "mV",
 "sshift_hhb", "mV",
 "hshift_hhb", "mV",
 "ashift_hhb", "mV",
 "nshift_hhb", "mV",
 "bkcor_hhb", "ms",
 "deptog_hhb", "1",
 "vhblock_hhb", "mV",
 "ina_hhb", "mA/cm2",
 "ik_hhb", "mA/cm2",
 "ika_hhb", "mA/cm2",
 "ikhh_hhb", "mA/cm2",
 "ena_hhb", "mV",
 0,0
};
 static double delta_t = 1;
 static double n0 = 0;
 static double p0 = 0;
 static double q0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "nai_hhb", &nai_hhb,
 "ek_hhb", &ek_hhb,
 "nao_hhb", &nao_hhb,
 "qv_hhb", &qv_hhb,
 "qs_hhb", &qs_hhb,
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
 
#define _cvode_ieq _ppvar[2]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"hhb",
 "gnabar_hhb",
 "gkhhbar_hhb",
 "gkabar_hhb",
 "shift_hhb",
 "sshift_hhb",
 "hshift_hhb",
 "ashift_hhb",
 "nshift_hhb",
 "nslope_hhb",
 "bkcor_hhb",
 "deptog_hhb",
 "vhblock_hhb",
 "taukv4_hhb",
 "asshift_hhb",
 "fptog_hhb",
 "qfix_hhb",
 "nspeed_hhb",
 0,
 "ina_hhb",
 "ik_hhb",
 "ika_hhb",
 "ikhh_hhb",
 "ena_hhb",
 "minf_hhb",
 "hinf_hhb",
 "ninf_hhb",
 "qinf_hhb",
 "pinf_hhb",
 "hsinf_hhb",
 "mtau_hhb",
 "htau_hhb",
 "hstau_hhb",
 "qtau_hhb",
 "ptau_hhb",
 "ntau_hhb",
 "gk_hhb",
 "gka_hhb",
 0,
 "n_hhb",
 "p_hhb",
 "q_hhb",
 0,
 0};
 static Symbol* _k_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 44, _prop);
 	/*initialize range parameters*/
 	gnabar = 0.00055;
 	gkhhbar = 0.000665;
 	gkabar = 0.000266;
 	shift = 0;
 	sshift = 0;
 	hshift = 0;
 	ashift = 0;
 	nshift = 0;
 	nslope = 12;
 	bkcor = 0;
 	deptog = 1;
 	vhblock = -54;
 	taukv4 = 1;
 	asshift = 0;
 	fptog = 0;
 	qfix = 0;
 	nspeed = 2;
 	_prop->param = _p;
 	_prop->param_size = 44;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 3, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_k_sym);
 	_ppvar[0]._pval = &prop_ion->param[3]; /* ik */
 	_ppvar[1]._pval = &prop_ion->param[4]; /* _ion_dikdv */
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 "n_hhb", 0.0001,
 "p_hhb", 0.0001,
 "q_hhb", 0.0001,
 0,0
};
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _blockhh3_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("k", -10000.);
 	_k_sym = hoc_lookup("k_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 44, 3);
  hoc_register_dparam_semantics(_mechtype, 0, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 hhb /home/workspace/266814/blockhh3.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 
#define F _nrnunit_F[_nrnunit_use_legacy_]
static double _nrnunit_F[2] = {0x1.78e555060882cp+16, 96485.3}; /* 96485.3321233100141 */
 
#define R _nrnunit_R[_nrnunit_use_legacy_]
static double _nrnunit_R[2] = {0x1.03d3b37125759p+13, 8314.5}; /* 8314.46261815323851 */
static int _reset;
static char *modelname = "squid sodium, potassium delayed rectifier, and potassium A channels";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int rates(_threadargsprotocomma_ double);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[3], _dlist1[3];
 static int states(_threadargsproto_);
 
static int  rates ( _threadargsprotocomma_ double _lvf ) {
   double _lahf , _lbhf , _lahs , _lbhs , _lam , _lbm ;
 minf = boltz ( _threadargscomma_ _lvf , - 30.0 - shift , 9.7 - sshift ) ;
   if ( v > - 54.0 - hshift ) {
     hinf = boltz ( _threadargscomma_ _lvf , - 54.0 - hshift , - 10.7 ) ;
     }
   else {
     hinf = 0.5 ;
     }
   hsinf = boltz ( _threadargscomma_ _lvf , vhblock , - 1.57 ) ;
   ninf = boltz ( _threadargscomma_ _lvf , - 20.0 , nslope ) ;
   pinf = boltz ( _threadargscomma_ _lvf , - 35.0 , 7.0 ) ;
   qinf = boltz ( _threadargscomma_ _lvf , - 61.0 + ashift , - 4.5 + asshift ) ;
   pinf = pow ( pinf , 1.0 / 3.0 ) ;
   if ( - 19.565 - 0.5 * _lvf > 1e-3  || - 19.565 - 0.5 * _lvf < - 1e-3 ) {
     _lam = - ( 15.65 + 0.4 * _lvf ) / ( exp ( - 19.5625 - 0.5 * _lvf ) - 1.0 ) ;
     }
   else {
     _lam = 0.8 ;
     }
   _lbm = 3.0 * exp ( - 7.5e-3 * _lvf ) ;
   mtau = 0.01 + 1.0 / ( _lam + _lbm ) ;
   _lahf = 5.0e-4 * exp ( - 6.3e-2 * _lvf ) ;
   _lbhf = 9.75 * exp ( 0.134 * _lvf ) ;
   htau = 0.4 + 1.0 / ( _lahf + _lbhf ) ;
   _lahs = 1.3e-2 * exp ( 8.5e-4 * _lvf ) ;
   _lbhs = 13.165 * exp ( 0.14556 * _lvf ) ;
   hstau = 20.0 + 180.0 * boltz ( _threadargscomma_ _lvf , 0.0 , - 1.0 ) ;
   if ( v > - 40.0 - nshift ) {
     ntau = 1.0 + 5.0 * exp ( - ( log ( 1.0 + 0.05 * ( _lvf + 40.0 + nshift ) ) / 0.05 * log ( 1.0 + 0.05 * ( _lvf + 40.0 + nshift ) ) / 0.05 ) / 300.0 ) ;
     }
   else {
     ntau = nspeed + ( 6.0 - nspeed ) * exp ( - ( ( _lvf + 40.0 + nshift ) ) * ( ( _lvf + 40.0 + nshift ) ) / 8.0 ) ;
     }
   ntau = 1.0 * ntau ;
   ptau = 0.1 * ( 1.029 + 4.83 * boltz ( _threadargscomma_ _lvf , - 56.7 , - 6.22 ) ) ;
   qtau = taukv4 * 250.0 ;
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
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {int _reset = 0; {
   rates ( _threadargscomma_ v ) ;
   Dn = 1.0 * ( ninf - n ) / ntau ;
   Dp = ( pinf - p ) / ptau ;
   Dq = ( qinf - q ) / qtau ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
 rates ( _threadargscomma_ v ) ;
 Dn = Dn  / (1. - dt*( ( ( 1.0 )*( ( ( - 1.0 ) ) ) ) / ntau )) ;
 Dp = Dp  / (1. - dt*( ( ( ( - 1.0 ) ) ) / ptau )) ;
 Dq = Dq  / (1. - dt*( ( ( ( - 1.0 ) ) ) / qtau )) ;
  return 0;
}
 /*END CVODE*/
 static int states (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) { {
   rates ( _threadargscomma_ v ) ;
    n = n + (1. - exp(dt*(( ( 1.0 )*( ( ( - 1.0 ) ) ) ) / ntau)))*(- ( ( ( 1.0 )*( ( ninf ) ) ) / ntau ) / ( ( ( 1.0 )*( ( ( - 1.0 ) ) ) ) / ntau ) - n) ;
    p = p + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / ptau)))*(- ( ( ( pinf ) ) / ptau ) / ( ( ( ( - 1.0 ) ) ) / ptau ) - p) ;
    q = q + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / qtau)))*(- ( ( ( qinf ) ) / qtau ) / ( ( ( ( - 1.0 ) ) ) / qtau ) - q) ;
   }
  return 0;
}
 
double boltz ( _threadargsprotocomma_ double _lx , double _ly , double _lz ) {
   double _lboltz;
 _lboltz = 1.0 / ( 1.0 + exp ( - ( _lx - _ly ) / _lz ) ) ;
   
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
 
static int _ode_count(int _type){ return 3;}
 
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
	for (_i=0; _i < 3; ++_i) {
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
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_k_sym, _ppvar, 0, 3);
   nrn_update_ion_pointer(_k_sym, _ppvar, 1, 4);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
  int _i; double _save;{
  n = n0;
  p = p0;
  q = q0;
 {
   rates ( _threadargscomma_ v ) ;
   n = ninf ;
   p = pinf ;
   q = qinf ;
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
   ena = 50.0 ;
   gk = n * n * n ;
   if ( fptog ) {
     gka = p * p * p * qfix ;
     }
   else {
     gka = p * p * p * q ;
     }
   ikhh = gkhhbar * gk * ( v - ek ) ;
   ika = gkabar * gka * ( v - ek ) ;
   ik = ika + ikhh ;
   }
 _current += ik;

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
 	{ double _dik;
  _dik = ik;
 _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
  _ion_dikdv += (_dik - ik)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ik += ik ;
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
  } }}

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = n_columnindex;  _dlist1[0] = Dn_columnindex;
 _slist1[1] = p_columnindex;  _dlist1[1] = Dp_columnindex;
 _slist1[2] = q_columnindex;  _dlist1[2] = Dq_columnindex;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/home/workspace/266814/blockhh3.mod";
static const char* nmodl_file_text = 
  "\n"
  "TITLE  squid sodium, potassium delayed rectifier, and potassium A channels\n"
  ": Anna's version adding some shift values\n"
  ": Kv4 from Tarfa et al 2017\n"
  ": sodium from Yu et al 2014\n"
  " \n"
  "UNITS {\n"
  "        (molar) = (1/liter)\n"
  "        (S) = (siemens)\n"
  "        (mA) = (milliamp)\n"
  "        (mV) = (millivolt)\n"
  "         F = (faraday) (coulomb)\n"
  "         R = (mole k) (mV-coulomb/degC)\n"
  "        (mM) =  (millimolar)\n"
  "}\n"
  " \n"
  "NEURON {\n"
  "        SUFFIX hhb\n"
  "        :USEION na READ nai WRITE ina\n"
  "        USEION k WRITE ik\n"
  "        RANGE  nspeed, sshift, shift,gnabar,gkhhbar,gkabar,ina,ikhh,ika,ik,ena,gk,gna,gka,nshift,bkcor, ashift, hshift, nslope, deptog, vhblock, taukv4,asshift,fptog, qfix, minf,hinf,qinf,pinf,ninf,hsinf,htau,mtau,ntau,hstau, qtau,ptau\n"
  "        :GLOBAL minf,hinf,ninf\n"
  "}\n"
  " \n"
  "INDEPENDENT {t FROM 0 TO 1 WITH 1 (ms)}\n"
  " \n"
  "PARAMETER {\n"
  "        v   (mV)\n"
  "        dt  (ms)\n"
  "	nai (mM)\n"
  "	celsius = 35.0 (degC)\n"
  "        gnabar  = 550.0e-6 (S/cm2)\n"
  "        gkhhbar = 665.0e-6 (S/cm2)\n"
  "        gkabar  = 266.0e-6  (S/cm2) :kv4 conductance should be ~80% of gkhh\n"
  "        ek  = -90.0  (mV)\n"
  "        nao =  145  (mM)\n"
  "        qv = 66.0 (mV)\n"
  "        qs = 10.0  (1)\n"
  "        shift=0 (mV)\n"
  "        sshift=0 (mV)\n"
  "        hshift = 0 (mV)\n"
  "        ashift = 0.0 (mV)\n"
  "        nshift = 0 (mV)\n"
  "        nslope = 12\n"
  "        bkcor = 0.0 (ms)\n"
  "        deptog = 1 (1)\n"
  "        vhblock = -54.0 (mV)\n"
  "        taukv4 = 1.0\n"
  "        asshift = 0\n"
  "        fptog = 0\n"
  "        qfix = 0\n"
  "        nspeed = 2\n"
  " 	\n"
  "}\n"
  " \n"
  "STATE {\n"
  "         n <1e-4> p <1e-4> q <1e-4>\n"
  "}\n"
  " \n"
  "ASSIGNED {\n"
  "        ina (mA/cm2)\n"
  "        ik (mA/cm2)\n"
  "        ika (mA/cm2)\n"
  "        ikhh (mA/cm2)\n"
  "        ena (mV)\n"
  "	minf hinf ninf qinf pinf hsinf\n"
  "	mtau htau hstau qtau ptau ntau\n"
  "	:gna \n"
  "	gk \n"
  "	gka\n"
  "}\n"
  " \n"
  "BREAKPOINT {\n"
  "        SOLVE states METHOD cnexp\n"
  "	:nai = 0.81 : only for pump\n"
  "    :    ena = R*(celsius+273.15)/F*log(nao/nai)\n"
  "    ena = 50\n"
  "	: ena=77.0\n"
  "  	gk = n*n*n\n"
  "	:gna = m*m*m*h*(deptog*hs+(1-deptog))\n"
  "	if(fptog){\n"
  "	  gka = p*p*p*qfix\n"
  "	} else {\n"
  "	  gka = p*p*p*q : single activation state\n"
  "	}\n"
  "    :ina = gnabar*gna*(v - ena)\n"
  "    ikhh = gkhhbar*gk*(v - ek)      \n"
  "    ika = gkabar*gka*(v - ek)      \n"
  "    ik = ika + ikhh\n"
  "\n"
  "}\n"
  " \n"
  "UNITSOFF\n"
  " \n"
  "\n"
  "\n"
  ": a-type modified to model from Latorre 2012\n"
  ": this model features better inactivation kinetics\n"
  "PROCEDURE rates(vf){\n"
  "LOCAL ahf, bhf, ahs, bhs, am, bm\n"
  "        minf = boltz(vf,-30.0-shift,9.7-sshift) :from tucker et al 2012\n"
  "        if(v > -54.0-hshift){\n"
  "          hinf = boltz(vf,-54.0-hshift,-10.7) : this is why the first spike is so large, h is 1 going into first spike\n"
  "        } else {\n"
  "          hinf = 0.5\n"
  "        }\n"
  "        hsinf = boltz(vf,vhblock,-1.57)\n"
  "        :hsinf = boltz(vf,vhblock,-10.0)\n"
  "        \n"
  "        \n"
  "\n"
  "        ninf = boltz(vf,-20,nslope)\n"
  "\n"
  "        \n"
  "        \n"
  "        :pinf = boltz(vf,-35.0,8.4)\n"
  "        pinf = boltz(vf,-35.0,7.0) :activation, with n=4, this makes p4inf at -37 mV (28 originally)\n"
  "        qinf = boltz(vf,-61.0+ashift,-4.5+asshift) : inactivation\n"
  "        pinf = pow(pinf,1.0/3.0)\n"
  "        \n"
  "        if (-19.565-0.5*vf > 1e-3 || -19.565-0.5*vf < -1e-3){\n"
  "          am = -(15.65 + 0.4*vf)/(exp(-19.5625-0.5*vf) - 1.0)\n"
  "        } else {\n"
  "          am = 0.8\n"
  "        }\n"
  "        bm = 3*exp(-7.5e-3*vf)\n"
  "       \n"
  "        mtau =0.01 + 1.0/(am+bm)\n"
  "        \n"
  "        \n"
  "        \n"
  "        ahf = 5.0e-4*exp(-6.3e-2*vf)\n"
  "        bhf = 9.75*exp(0.134*vf)\n"
  "        htau = 0.4 + 1.0/(ahf+bhf)\n"
  "        ahs = 1.3e-2*exp(8.5e-4*vf)\n"
  "        bhs = 13.165*exp(0.14556*vf)\n"
  "        \n"
  "        hstau = 20.0 +180.0*boltz(vf, 0,-1.0) :time spent above 0 increases middle number\n"
  "										: shorter first number increases the rate at which each spike reduces gNa\n"
  "										: longer 2nd nmber increases the amount of time between spikes required to not accumulate inactivation\n"
  "\n"
  "        if (v > -40-nshift){\n"
  "          ntau = 1 + 5.0*exp(-(log(1.0+0.05*(vf+40+nshift))/0.05*log(1.0+0.05*(vf+40+nshift))/0.05)/300) : peak tau at -40 mV, tau ~5ms at 0\n"
  "        } else {\n"
  "          :ntau = 2.0 + 8.0*exp(-((vf+40+nshift))*((vf+40+nshift))/18.0) : peak tau at -40 mV, tau ~5ms at 0 :5 5 9\n"
  "          ntau = nspeed +(6-nspeed)*exp(-((vf+40+nshift))*((vf+40+nshift))/8.0) : peak tau at -40 mV, tau ~5ms at 0 :5 5 9\n"
  "          :ntau = 10.0\n"
  "        }\n"
  "        ntau =1.0*ntau\n"
  "        ptau = 0.1*(1.029 + 4.83*boltz(vf,-56.7,-6.22))\n"
  "        qtau = taukv4*250.0:(58.6+117.57*boltz(vf,-68.5,-5.95)) : faster may be needed for pacing \n"
  "\n"
  "\n"
  "}\n"
  "INITIAL {\n"
  "        rates(v)\n"
  "        :m = minf\n"
  "        :h = hinf\n"
  "        n = ninf\n"
  "        p = pinf\n"
  "        q = qinf\n"
  "        :hs = hsinf\n"
  "}\n"
  "\n"
  "DERIVATIVE states {  :Computes state variables m, h, and n \n"
  "        rates(v)\n"
  "\n"
  "        :m' = 1.0*(minf-m)/mtau\n"
  "        :h' = 1.0*(hinf-h)/htau\n"
  "        :hs' =1.0*(hsinf - hs)/hstau\n"
  "        n' = 1.0*(ninf-n)/ntau\n"
  "        p' = (pinf-p)/ptau\n"
  "        q' = (qinf-q)/qtau\n"
  "}\n"
  " \n"
  " \n"
  " \n"
  "FUNCTION boltz(x,y,z) {\n"
  "                boltz = 1/(1 + exp(-(x - y)/z))\n"
  "}\n"
  " \n"
  "UNITSON\n"
  "\n"
  ;
#endif
