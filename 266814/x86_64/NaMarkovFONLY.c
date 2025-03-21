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
 
#define nrn_init _nrn_init__FastNaMark
#define _nrn_initial _nrn_initial__FastNaMark
#define nrn_cur _nrn_cur__FastNaMark
#define _nrn_current _nrn_current__FastNaMark
#define nrn_jacob _nrn_jacob__FastNaMark
#define nrn_state _nrn_state__FastNaMark
#define _net_receive _net_receive__FastNaMark 
#define kin kin__FastNaMark 
#define rates rates__FastNaMark 
 
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
#define shift _p[1]
#define shift_columnindex 1
#define scale _p[2]
#define scale_columnindex 2
#define hshift _p[3]
#define hshift_columnindex 3
#define oinit _p[4]
#define oinit_columnindex 4
#define DISABLE _p[5]
#define DISABLE_columnindex 5
#define BALBI _p[6]
#define BALBI_columnindex 6
#define ina _p[7]
#define ina_columnindex 7
#define gna _p[8]
#define gna_columnindex 8
#define c1 _p[9]
#define c1_columnindex 9
#define c2 _p[10]
#define c2_columnindex 10
#define i1 _p[11]
#define i1_columnindex 11
#define o1 _p[12]
#define o1_columnindex 12
#define c1c2 _p[13]
#define c1c2_columnindex 13
#define c2c1 _p[14]
#define c2c1_columnindex 14
#define i1c1 _p[15]
#define i1c1_columnindex 15
#define c1i1 _p[16]
#define c1i1_columnindex 16
#define o1i1 _p[17]
#define o1i1_columnindex 17
#define i1o1 _p[18]
#define i1o1_columnindex 18
#define o1c2 _p[19]
#define o1c2_columnindex 19
#define c2o1 _p[20]
#define c2o1_columnindex 20
#define c2i1 _p[21]
#define c2i1_columnindex 21
#define i1c2 _p[22]
#define i1c2_columnindex 22
#define Dc1 _p[23]
#define Dc1_columnindex 23
#define Dc2 _p[24]
#define Dc2_columnindex 24
#define Di1 _p[25]
#define Di1_columnindex 25
#define Do1 _p[26]
#define Do1_columnindex 26
#define v _p[27]
#define v_columnindex 27
#define _g _p[28]
#define _g_columnindex 28
#define _ion_ina	*_ppvar[0]._pval
#define _ion_dinadv	*_ppvar[1]._pval
 
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
 static void _hoc_DoubSig(void);
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
 "setdata_FastNaMark", _hoc_setdata,
 "DoubSig_FastNaMark", _hoc_DoubSig,
 "boltz_FastNaMark", _hoc_boltz,
 "rates_FastNaMark", _hoc_rates,
 0, 0
};
#define DoubSig DoubSig_FastNaMark
#define boltz boltz_FastNaMark
 extern double DoubSig( _threadargsprotocomma_ double , double , double , double , double , double , double );
 extern double boltz( _threadargsprotocomma_ double , double , double );
 /* declare global and static user variables */
#define dist dist_FastNaMark
 double dist = 100;
#define ena ena_FastNaMark
 double ena = 50;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "ena_FastNaMark", "mV",
 "ina_FastNaMark", "mA/cm2",
 "gna_FastNaMark", "pS/um2",
 0,0
};
 static double c20 = 0;
 static double c10 = 0;
 static double delta_t = 0.01;
 static double i10 = 0;
 static double o10 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "ena_FastNaMark", &ena_FastNaMark,
 "dist_FastNaMark", &dist_FastNaMark,
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
"FastNaMark",
 "gnabar_FastNaMark",
 "shift_FastNaMark",
 "scale_FastNaMark",
 "hshift_FastNaMark",
 "oinit_FastNaMark",
 "DISABLE_FastNaMark",
 "BALBI_FastNaMark",
 0,
 "ina_FastNaMark",
 "gna_FastNaMark",
 0,
 "c1_FastNaMark",
 "c2_FastNaMark",
 "i1_FastNaMark",
 "o1_FastNaMark",
 0,
 0};
 static Symbol* _na_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 29, _prop);
 	/*initialize range parameters*/
 	gnabar = 0.00055;
 	shift = 0;
 	scale = 1;
 	hshift = 0;
 	oinit = -1;
 	DISABLE = 1;
 	BALBI = 0;
 	_prop->param = _p;
 	_prop->param_size = 29;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 3, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_na_sym);
 	_ppvar[0]._pval = &prop_ion->param[3]; /* ina */
 	_ppvar[1]._pval = &prop_ion->param[4]; /* _ion_dinadv */
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static void _thread_cleanup(Datum*);
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _NaMarkovFONLY_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("na", -10000.);
 	_na_sym = hoc_lookup("na_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 3);
  _extcall_thread = (Datum*)ecalloc(2, sizeof(Datum));
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 0, _thread_cleanup);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 29, 3);
  hoc_register_dparam_semantics(_mechtype, 0, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 FastNaMark /home/workspace/266814/NaMarkovFONLY.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "Markov sodium channel of NaV 1.6  (fast only)";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int rates(_threadargsprotocomma_ double);
 
#define _MATELM1(_row,_col) *(_nrn_thread_getelm(_so, _row + 1, _col + 1))
 
#define _RHS1(_arg) _rhs[_arg+1]
  static int _cvspth1 = 1;
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 extern double *_nrn_thread_getelm(SparseObj*, int, int);
 
#define _MATELM1(_row,_col) *(_nrn_thread_getelm(_so, _row + 1, _col + 1))
 
#define _RHS1(_arg) _rhs[_arg+1]
  
#define _linmat1  1
 static int _spth1 = 0;
 static int _slist1[4], _dlist1[4]; static double *_temp1;
 static int kin();
 
static int kin (void* _so, double* _rhs, double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt)
 {int _reset=0;
 {
   double b_flux, f_flux, _term; int _i;
 {int _i; double _dt1 = 1.0/dt;
for(_i=1;_i<4;_i++){
  	_RHS1(_i) = -_dt1*(_p[_slist1[_i]] - _p[_dlist1[_i]]);
	_MATELM1(_i, _i) = _dt1;
      
} }
 rates ( _threadargscomma_ v ) ;
   /* ~ c1 <-> c2 ( c1c2 , c2c1 )*/
 f_flux =  c1c2 * c1 ;
 b_flux =  c2c1 * c2 ;
 _RHS1( 2) -= (f_flux - b_flux);
 _RHS1( 1) += (f_flux - b_flux);
 
 _term =  c1c2 ;
 _MATELM1( 2 ,2)  += _term;
 _MATELM1( 1 ,2)  -= _term;
 _term =  c2c1 ;
 _MATELM1( 2 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
  /* ~ o1 <-> c2 ( o1c2 , c2o1 )*/
 f_flux =  o1c2 * o1 ;
 b_flux =  c2o1 * c2 ;
 _RHS1( 3) -= (f_flux - b_flux);
 _RHS1( 1) += (f_flux - b_flux);
 
 _term =  o1c2 ;
 _MATELM1( 3 ,3)  += _term;
 _MATELM1( 1 ,3)  -= _term;
 _term =  c2o1 ;
 _MATELM1( 3 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
  /* ~ o1 <-> i1 ( o1i1 , i1o1 )*/
 f_flux =  o1i1 * o1 ;
 b_flux =  i1o1 * i1 ;
 _RHS1( 3) -= (f_flux - b_flux);
 
 _term =  o1i1 ;
 _MATELM1( 3 ,3)  += _term;
 _term =  i1o1 ;
 _MATELM1( 3 ,0)  -= _term;
 /*REACTION*/
  /* ~ i1 <-> c1 ( i1c1 , c1i1 )*/
 f_flux =  i1c1 * i1 ;
 b_flux =  c1i1 * c1 ;
 _RHS1( 2) += (f_flux - b_flux);
 
 _term =  i1c1 ;
 _MATELM1( 2 ,0)  -= _term;
 _term =  c1i1 ;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ i1 <-> c2 ( i1c2 , c2i1 )*/
 f_flux =  i1c2 * i1 ;
 b_flux =  c2i1 * c2 ;
 _RHS1( 1) += (f_flux - b_flux);
 
 _term =  i1c2 ;
 _MATELM1( 1 ,0)  -= _term;
 _term =  c2i1 ;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
   /* c1 + o1 + c2 + i1 = 1.0 */
 _RHS1(0) =  1.0;
 _MATELM1(0, 0) = 1;
 _RHS1(0) -= i1 ;
 _MATELM1(0, 1) = 1;
 _RHS1(0) -= c2 ;
 _MATELM1(0, 3) = 1;
 _RHS1(0) -= o1 ;
 _MATELM1(0, 2) = 1;
 _RHS1(0) -= c1 ;
 /*CONSERVATION*/
   } return _reset;
 }
 
static int  rates ( _threadargsprotocomma_ double _lv ) {
   double _lvm ;
 _lvm = _lv + shift ;
   if ( BALBI < 1.0 + 1e-6  && BALBI > 1.0 - 1e-6 ) {
     c1c2 = scale * DoubSig ( _threadargscomma_ _lvm , 0.0 , 0.0 , 0.0 , 16.0 , - 5.0 , - 10.0 ) ;
     c2c1 = scale * DoubSig ( _threadargscomma_ _lvm , 3.0 , - 35.0 , 10.0 , 16.0 , - 5.0 , - 10.0 ) ;
     c2o1 = scale * DoubSig ( _threadargscomma_ _lvm , 0.0 , 0.0 , 0.0 , 16.0 , - 10.0 , - 10.0 ) ;
     o1c2 = scale * DoubSig ( _threadargscomma_ _lvm , 3.0 , - 40.0 , 10.0 , 16.0 , - 10.0 , - 10.0 ) ;
     o1i1 = DISABLE * scale * DoubSig ( _threadargscomma_ _lvm , 3.0 , - 41.0 + hshift , 12.0 , 16.0 , - 11.0 + hshift , - 12.0 ) ;
     i1o1 = DISABLE * scale * DoubSig ( _threadargscomma_ _lvm , 1.0e-5 , - 42.0 + hshift , 10.0 , 0.0 , 0.0 , 0.0 ) ;
     i1c1 = DISABLE * scale * DoubSig ( _threadargscomma_ _lvm , 0.55 , - 65.0 , 7.0 , 0.0 , 0.0 , 0.0 ) ;
     c1i1 = DISABLE * scale * DoubSig ( _threadargscomma_ _lvm , 0.0 , 0.0 , 0.0 , 0.55 , - 65.0 , - 11.0 ) ;
     }
   else {
     c1c2 = 0.75 * scale * DoubSig ( _threadargscomma_ _lvm , 0.0 , 0.0 , 0.0 , 16.0 , - 8.0 , - 10.0 ) ;
     c2c1 = 0.25 * scale * DoubSig ( _threadargscomma_ _lvm , 2.0 , - 50.0 , 9.0 , 0.0 , - 8.0 , - 10.0 ) ;
     c2o1 = 1.0 * scale * DoubSig ( _threadargscomma_ _lvm , 0.0 , 0.0 , 0.0 , 14.0 , 0.0 , - 6.0 ) ;
     o1c2 = 1.0 * scale * DoubSig ( _threadargscomma_ _lvm , 4.0 , - 48.0 , 9.0 , 0.0 , 0.0 , 0.0 ) ;
     o1i1 = 0.5 * DISABLE * scale * DoubSig ( _threadargscomma_ _lvm , 1.0 , - 42.0 + hshift , 12.0 , 5.0 , 10.0 + hshift , - 12.0 ) ;
     i1o1 = 0.0 ;
     i1c1 = DISABLE * scale * DoubSig ( _threadargscomma_ _lvm , 0.2 , - 65.0 , 10.0 , 0.0 , 0.0 , 0.0 ) ;
     c1i1 = DISABLE * scale * DoubSig ( _threadargscomma_ _lvm , 0.0 , 0.0 , 0.0 , 0.2 , - 65.0 , - 11.0 ) ;
     c2i1 = 0.3 * c1i1 ;
     i1c2 = 0.0 ;
     }
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
 
double DoubSig ( _threadargsprotocomma_ double _lv , double _lbh , double _lvh , double _lkh , double _lbd , double _lvd , double _lkd ) {
   double _lDoubSig;
 double _lboltz1 , _lboltz2 ;
 if ( _lbh > 0.0 ) {
     _lboltz1 = _lbh * boltz ( _threadargscomma_ _lv , _lvh , - _lkh ) ;
     }
   else {
     _lboltz1 = 0.0 ;
     }
   if ( _lbd > 0.0 ) {
     _lboltz2 = _lbd * boltz ( _threadargscomma_ _lv , _lvd , - _lkd ) ;
     }
   else {
     _lboltz2 = 0.0 ;
     }
   _lDoubSig = _lboltz1 + _lboltz2 ;
   
return _lDoubSig;
 }
 
static void _hoc_DoubSig(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  DoubSig ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) , *getarg(3) , *getarg(4) , *getarg(5) , *getarg(6) , *getarg(7) );
 hoc_retpushx(_r);
}
 
/*CVODE ode begin*/
 static int _ode_spec1(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {int _reset=0;{
 double b_flux, f_flux, _term; int _i;
 {int _i; for(_i=0;_i<4;_i++) _p[_dlist1[_i]] = 0.0;}
 rates ( _threadargscomma_ v ) ;
 /* ~ c1 <-> c2 ( c1c2 , c2c1 )*/
 f_flux =  c1c2 * c1 ;
 b_flux =  c2c1 * c2 ;
 Dc1 -= (f_flux - b_flux);
 Dc2 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ o1 <-> c2 ( o1c2 , c2o1 )*/
 f_flux =  o1c2 * o1 ;
 b_flux =  c2o1 * c2 ;
 Do1 -= (f_flux - b_flux);
 Dc2 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ o1 <-> i1 ( o1i1 , i1o1 )*/
 f_flux =  o1i1 * o1 ;
 b_flux =  i1o1 * i1 ;
 Do1 -= (f_flux - b_flux);
 Di1 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ i1 <-> c1 ( i1c1 , c1i1 )*/
 f_flux =  i1c1 * i1 ;
 b_flux =  c1i1 * c1 ;
 Di1 -= (f_flux - b_flux);
 Dc1 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ i1 <-> c2 ( i1c2 , c2i1 )*/
 f_flux =  i1c2 * i1 ;
 b_flux =  c2i1 * c2 ;
 Di1 -= (f_flux - b_flux);
 Dc2 += (f_flux - b_flux);
 
 /*REACTION*/
   /* c1 + o1 + c2 + i1 = 1.0 */
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE matsol*/
 static int _ode_matsol1(void* _so, double* _rhs, double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {int _reset=0;{
 double b_flux, f_flux, _term; int _i;
   b_flux = f_flux = 0.;
 {int _i; double _dt1 = 1.0/dt;
for(_i=0;_i<4;_i++){
  	_RHS1(_i) = _dt1*(_p[_dlist1[_i]]);
	_MATELM1(_i, _i) = _dt1;
      
} }
 rates ( _threadargscomma_ v ) ;
 /* ~ c1 <-> c2 ( c1c2 , c2c1 )*/
 _term =  c1c2 ;
 _MATELM1( 2 ,2)  += _term;
 _MATELM1( 1 ,2)  -= _term;
 _term =  c2c1 ;
 _MATELM1( 2 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
  /* ~ o1 <-> c2 ( o1c2 , c2o1 )*/
 _term =  o1c2 ;
 _MATELM1( 3 ,3)  += _term;
 _MATELM1( 1 ,3)  -= _term;
 _term =  c2o1 ;
 _MATELM1( 3 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
  /* ~ o1 <-> i1 ( o1i1 , i1o1 )*/
 _term =  o1i1 ;
 _MATELM1( 3 ,3)  += _term;
 _MATELM1( 0 ,3)  -= _term;
 _term =  i1o1 ;
 _MATELM1( 3 ,0)  -= _term;
 _MATELM1( 0 ,0)  += _term;
 /*REACTION*/
  /* ~ i1 <-> c1 ( i1c1 , c1i1 )*/
 _term =  i1c1 ;
 _MATELM1( 0 ,0)  += _term;
 _MATELM1( 2 ,0)  -= _term;
 _term =  c1i1 ;
 _MATELM1( 0 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ i1 <-> c2 ( i1c2 , c2i1 )*/
 _term =  i1c2 ;
 _MATELM1( 0 ,0)  += _term;
 _MATELM1( 1 ,0)  -= _term;
 _term =  c2i1 ;
 _MATELM1( 0 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
   /* c1 + o1 + c2 + i1 = 1.0 */
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE end*/
 
static int _ode_count(int _type){ return 4;}
 
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
	for (_i=0; _i < 4; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _cvode_sparse_thread(&_thread[_cvspth1]._pvoid, 4, _dlist1, _p, _ode_matsol1, _ppvar, _thread, _nt);
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
 
static void _thread_cleanup(Datum* _thread) {
   _nrn_destroy_sparseobj_thread(_thread[_spth1]._pvoid);
   _nrn_destroy_sparseobj_thread(_thread[_cvspth1]._pvoid);
 }
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_na_sym, _ppvar, 0, 3);
   nrn_update_ion_pointer(_na_sym, _ppvar, 1, 4);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
  int _i; double _save;{
  c2 = c20;
  c1 = c10;
  i1 = i10;
  o1 = o10;
 {
   rates ( _threadargscomma_ v ) ;
   if ( oinit < 0.0 ) {
      _ss_sparse_thread(&_thread[_spth1]._pvoid, 4, _slist1, _dlist1, _p, &t, dt, kin, _linmat1, _ppvar, _thread, _nt);
     if (secondorder) {
    int _i;
    for (_i = 0; _i < 4; ++_i) {
      _p[_slist1[_i]] += dt*_p[_dlist1[_i]];
    }}
 }
   else {
     c1 = 0.5 - 2e-6 ;
     c2 = 1e-6 ;
     i1 = 0.5 - oinit ;
     o1 = oinit ;
     }
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
   gna = gnabar * o1 ;
   ina = gna * ( v - ena ) ;
   }
 _current += ina;

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
 	{ double _dina;
  _dina = ina;
 _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
  _ion_dinadv += (_dina - ina)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ina += ina ;
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
double _dtsav = dt;
if (secondorder) { dt *= 0.5; }
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
 {  sparse_thread(&_thread[_spth1]._pvoid, 4, _slist1, _dlist1, _p, &t, dt, kin, _linmat1, _ppvar, _thread, _nt);
     if (secondorder) {
    int _i;
    for (_i = 0; _i < 4; ++_i) {
      _p[_slist1[_i]] += dt*_p[_dlist1[_i]];
    }}
 } }}
 dt = _dtsav;
}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = i1_columnindex;  _dlist1[0] = Di1_columnindex;
 _slist1[1] = c2_columnindex;  _dlist1[1] = Dc2_columnindex;
 _slist1[2] = c1_columnindex;  _dlist1[2] = Dc1_columnindex;
 _slist1[3] = o1_columnindex;  _dlist1[3] = Do1_columnindex;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/home/workspace/266814/NaMarkovFONLY.mod";
static const char* nmodl_file_text = 
  "TITLE Markov sodium channel of NaV 1.6  (fast only)\n"
  "\n"
  "COMMENT\n"
  "\n"
  "from Balbi et al 2017, modified by Carol Upchurch and Christopher Knowlton\n"
  "\n"
  "ENDCOMMENT\n"
  "\n"
  "NEURON {\n"
  "       SUFFIX FastNaMark\n"
  "       USEION na WRITE ina\n"
  "       RANGE gnabar, gna,  ina, o1, shift, scale,hshift, oinit,DISABLE,hinit, BALBI\n"
  "       :GLOBAL zhalf\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "	(mV) = (millivolt)\n"
  "	(mA) = (milliamp)\n"
  "	(nA) = (nanoamp)\n"
  "	(pA) = (picoamp)\n"
  "	(S)  = (siemens)\n"
  "	(uS) = (microsiemens)\n"
  "	(nS) = (nanosiemens)\n"
  "	(pS) = (picosiemens)\n"
  "	(um) = (micron)\n"
  "	(molar) = (1/liter)\n"
  "	(mM) = (millimolar)		\n"
  "}\n"
  "\n"
  "CONSTANT {\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "	v (mV)\n"
  "	celsius (degC)\n"
  "	ena = 50 (mV)\n"
  "	gnabar = 550.0e-6\n"
  "	shift = 0\n"
  "	dist = 100\n"
  "	scale = 1\n"
  "	hshift = 0\n"
  "	oinit=-1\n"
  "	DISABLE = 1\n"
  "	BALBI = 0\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	ina (mA/cm2)\n"
  "    gna (pS/um2) \n"
  "    c1c2\n"
  "    c2c1\n"
  "    i1c1\n"
  "    c1i1\n"
  "    o1i1\n"
  "    i1o1 : 0\n"
  "    o1c2\n"
  "    c2o1   \n"
  "    c2i1\n"
  "    i1c2\n"
  "}\n"
  "\n"
  "STATE {\n"
  "	c1   FROM 0 TO 1\n"
  "	c2   FROM 0 TO 1\n"
  "	i1   FROM 0 TO 1\n"
  "	o1   FROM 0 TO 1\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "	rates(v)\n"
  "	if(oinit < 0) { \n"
  "		SOLVE kin\n"
  "		STEADYSTATE sparse\n"
  "	} else {\n"
  "	c1 = 0.5-2e-6\n"
  "	c2 = 1e-6\n"
  "	i1 = 0.5 - oinit\n"
  "	:i2 = 1e-6\n"
  "	o1 = oinit\n"
  "	}\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "	SOLVE kin METHOD sparse\n"
  "    gna = gnabar*o1  \n"
  "	ina = gna * (v - ena)\n"
  "}\n"
  "\n"
  "KINETIC kin {\n"
  "	rates(v)\n"
  "	~ c1 <-> c2 (c1c2,c2c1)\n"
  "	~ o1 <-> c2 (o1c2,c2o1)\n"
  "	~ o1 <-> i1 (o1i1,i1o1)\n"
  "	~ i1 <-> c1 (i1c1,c1i1)	\n"
  "	:~ i1 <-> i2 (i1i2,i2i1)\n"
  "	~ i1 <-> c2 (i1c2,c2i1)\n"
  "\n"
  "	CONSERVE c1 + o1 + c2 + i1 = 1\n"
  "}\n"
  "\n"
  "\n"
  ":DERIVATIVE states {\n"
  ":	rates(v)\n"
  ":	o1 = 1.0 - c1 - c2 - i1 - i2\n"
  ":	c1' = c2c1*c2 + i1c1*i1 - (c1c2+c1i1)*c1:\n"
  ":	c2' = c1c2*c1 + o1c2*o1 - (c2c1+c2o1)*c2\n"
  ":	i2' = i1i2*i1 - i2i1*i2\n"
  ":	i1' = i2i1*i2 + o1i1*o1 + c1i1*c1 - (i1o1 + i1i2 + i1c1)*i1 \n"
  ":}\n"
  "\n"
  "PROCEDURE rates( v (mV) ) {\n"
  "	LOCAL vm\n"
  "	vm = v+shift\n"
  "	\n"
  "	if(BALBI<1+1e-6 && BALBI > 1-1e-6) {\n"
  "\n"
  "	c1c2 = scale*DoubSig(vm,0,0,0,16.0,-5.0,-10.0)\n"
  "	c2c1 = scale*DoubSig(vm,3.0,-35.0,10.0,16.0,-5.0,-10.0) :38\n"
  "\n"
  "	c2o1 = scale*DoubSig(vm,0,0,0,16.0, -10,-10.0)\n"
  "	o1c2 = scale*DoubSig(vm,3.0,-40.0,10.0,16.0,-10,-10.0) : 18\n"
  "\n"
  "	o1i1 = DISABLE*scale*DoubSig(vm,3.0,-41.0+hshift,12.0,16.0, -11.0+hshift,-12.0) : 10 -18\n"
  "	i1o1 = DISABLE*scale*DoubSig(vm,1.0e-5,-42.0+hshift,10.0,0,0,0) : control\n"
  "\n"
  "	i1c1 = DISABLE*scale*DoubSig(vm,0.55,-65.0,7.0,0,0,0)\n"
  "	c1i1 = DISABLE*scale*DoubSig(vm,0,0,0,0.55,-65.0,-11.0)\n"
  "\n"
  "	:i1i2 = dist*scale*DoubSig(vm,0,0,0,2.2e-3,-90.0,-5.0) :1000x : or here :above -50, it accumulates\n"
  "	:i2i1 = scale*DoubSig(vm,1.7e-2,-90.0,15.0,0,0,0) : 100x : add parameter here\n"
  "	\n"
  "	} else {\n"
  "\n"
  "	c1c2 = 0.75*scale*DoubSig(vm,0,0,0,16.0,-8.0,-10.0)\n"
  "	c2c1 = 0.25*scale*DoubSig(vm,2.0,-50.0,9.0,0.0,-8.0,-10.0) :38\n"
  "\n"
  "	c2o1 = 1*scale*DoubSig(vm,0,0,0,14.0, 0,-6.0)\n"
  "	o1c2 = 1*scale*DoubSig(vm,4.0,-48.0,9.0,0,0,0) : 18\n"
  "\n"
  "	o1i1 = 0.5*DISABLE*scale*DoubSig(vm,1.0,-42.0+hshift,12.0,5.0, 10.0+hshift,-12.0) : 10 -18\n"
  "	i1o1 = 0\n"
  "\n"
  "	i1c1 = DISABLE*scale*DoubSig(vm,0.2,-65.0,10.0,0,0,0)\n"
  "	c1i1 = DISABLE*scale*DoubSig(vm,0,0,0,0.2,-65.0,-11.0)\n"
  "	\n"
  "	c2i1 = 0.3*c1i1 : required to match Ding steady state data, not required otherwise.\n"
  "	i1c2 = 0\n"
  "\n"
  "	:i1i2 = 2.0*dist*DoubSig(vm,0,0,0,2.0e-2,-25.0,-5.0) :1000x : or here :above -50, it accumulates\n"
  "	:i2i1 = 2.0*DoubSig(vm,1.8e-3,-50.0,10.0,0,0,0) : 100x : add parameter here 50/5\n"
  "	\n"
  "\n"
  "\n"
  "	\n"
  "	}\n"
  "}\n"
  "\n"
  "FUNCTION boltz(x,y,z) {\n"
  "               LOCAL arg\n"
  "                arg= -(x-y)/z\n"
  "                if (arg > 50) {boltz = 0}\n"
  "				else {if (arg < -50) {boltz = 1}\n"
  "                else {boltz = 1.0/(1.0 + exp(arg))}}\n"
  "}\n"
  "\n"
  "FUNCTION DoubSig(v,bh,vh,kh,bd,vd,kd){\n"
  "	LOCAL boltz1, boltz2\n"
  "	if(bh > 0){\n"
  "		boltz1 = bh*boltz(v,vh,-kh)\n"
  "	} else {\n"
  "	    boltz1 = 0\n"
  "	}\n"
  "	if(bd > 0){\n"
  "		boltz2 = bd*boltz(v,vd,-kd)\n"
  "	} else {\n"
  "	    boltz2 = 0\n"
  "	}\n"
  "	DoubSig = boltz1 + boltz2\n"
  "	\n"
  "}\n"
  ;
#endif
