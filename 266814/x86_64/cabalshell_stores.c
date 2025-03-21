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
 
#define nrn_init _nrn_init__cabalstore
#define _nrn_initial _nrn_initial__cabalstore
#define nrn_cur _nrn_cur__cabalstore
#define _nrn_current _nrn_current__cabalstore
#define nrn_jacob _nrn_jacob__cabalstore
#define nrn_state _nrn_state__cabalstore
#define _net_receive _net_receive__cabalstore 
#define factors factors__cabalstore 
#define states states__cabalstore 
 
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
#define fCa _p[0]
#define fCa_columnindex 0
#define cainit _p[1]
#define cainit_columnindex 1
#define icapumpmax _p[2]
#define icapumpmax_columnindex 2
#define km _p[3]
#define km_columnindex 3
#define DCa _p[4]
#define DCa_columnindex 4
#define k1buf _p[5]
#define k1buf_columnindex 5
#define k2buf _p[6]
#define k2buf_columnindex 6
#define TotalBuffer _p[7]
#define TotalBuffer_columnindex 7
#define basal _p[8]
#define basal_columnindex 8
#define shellfrac _p[9]
#define shellfrac_columnindex 9
#define SCALE _p[10]
#define SCALE_columnindex 10
#define tog _p[11]
#define tog_columnindex 11
#define icapump _p[12]
#define icapump_columnindex 12
#define vrat (_p + 13)
#define vrat_columnindex 13
#define cast _p[15]
#define cast_columnindex 15
#define cac _p[16]
#define cac_columnindex 16
#define ca (_p + 17)
#define ca_columnindex 17
#define CaBuffer (_p + 19)
#define CaBuffer_columnindex 19
#define Buffer (_p + 21)
#define Buffer_columnindex 21
#define castore (_p + 23)
#define castore_columnindex 23
#define ica _p[25]
#define ica_columnindex 25
#define Kd _p[26]
#define Kd_columnindex 26
#define B0 _p[27]
#define B0_columnindex 27
#define cai _p[28]
#define cai_columnindex 28
#define Dca (_p + 29)
#define Dca_columnindex 29
#define DCaBuffer (_p + 31)
#define DCaBuffer_columnindex 31
#define DBuffer (_p + 33)
#define DBuffer_columnindex 33
#define Dcastore (_p + 35)
#define Dcastore_columnindex 35
#define v _p[37]
#define v_columnindex 37
#define _g _p[38]
#define _g_columnindex 38
#define _ion_cai	*_ppvar[0]._pval
#define _ion_ica	*_ppvar[1]._pval
#define _style_ca	*((int*)_ppvar[2]._pvoid)
#define ju_p	*_ppvar[3]._pval
#define _p_ju_p	_ppvar[3]._pval
#define jcicr_p	*_ppvar[4]._pval
#define _p_jcicr_p	_ppvar[4]._pval
#define diam	*_ppvar[5]._pval
 
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
 static int hoc_nrnpointerindex =  3;
 static Datum* _extcall_thread;
 static Prop* _extcall_prop;
 /* external NEURON variables */
 extern double celsius;
 /* declaration of user functions */
 static void _hoc_factors(void);
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
 "setdata_cabalstore", _hoc_setdata,
 "factors_cabalstore", _hoc_factors,
 0, 0
};
 #define _zfrat (_thread[2]._pval + 0)
 #define _zdsq _thread[2]._pval[2]
 #define _zdsqvol _thread[2]._pval[3]
 #define _zcasq _thread[2]._pval[4]
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "fCa_cabalstore", "1",
 "cainit_cabalstore", "mM",
 "icapumpmax_cabalstore", "mA/cm2",
 "km_cabalstore", "mM",
 "DCa_cabalstore", "um2/ms",
 "k1buf_cabalstore", "/mM-ms",
 "k2buf_cabalstore", "/ms",
 "TotalBuffer_cabalstore", "mM",
 "basal_cabalstore", "mM",
 "ca_cabalstore", "mM",
 "CaBuffer_cabalstore", "mM",
 "Buffer_cabalstore", "mM",
 "castore_cabalstore", "mM",
 "icapump_cabalstore", "mA/cm2",
 "cast_cabalstore", "mM",
 "cac_cabalstore", "mM",
 0,0
};
 static double Buffer0 = 0;
 static double CaBuffer0 = 0;
 static double castore0 = 0;
 static double ca0 = 0;
 static double delta_t = 0.01;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
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
 
#define _cvode_ieq _ppvar[6]._i
 static void _ode_synonym(int, double**, Datum**);
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"cabalstore",
 "fCa_cabalstore",
 "cainit_cabalstore",
 "icapumpmax_cabalstore",
 "km_cabalstore",
 "DCa_cabalstore",
 "k1buf_cabalstore",
 "k2buf_cabalstore",
 "TotalBuffer_cabalstore",
 "basal_cabalstore",
 "shellfrac_cabalstore",
 "SCALE_cabalstore",
 "tog_cabalstore",
 0,
 "icapump_cabalstore",
 "vrat_cabalstore[2]",
 "cast_cabalstore",
 "cac_cabalstore",
 0,
 "ca_cabalstore[2]",
 "CaBuffer_cabalstore[2]",
 "Buffer_cabalstore[2]",
 "castore_cabalstore[2]",
 0,
 "ju_p_cabalstore",
 "jcicr_p_cabalstore",
 0};
 static Symbol* _morphology_sym;
 static Symbol* _ca_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 39, _prop);
 	/*initialize range parameters*/
 	fCa = 0.05;
 	cainit = 0.0001;
 	icapumpmax = 0.00191;
 	km = 0.0005;
 	DCa = 0.6;
 	k1buf = 100;
 	k2buf = 0.1;
 	TotalBuffer = 0.03;
 	basal = 0;
 	shellfrac = 0.25;
 	SCALE = 1;
 	tog = 1;
 	_prop->param = _p;
 	_prop->param_size = 39;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 7, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_morphology_sym);
 	_ppvar[5]._pval = &prop_ion->param[0]; /* diam */
 prop_ion = need_memb(_ca_sym);
 nrn_check_conc_write(_prop, prop_ion, 1);
 nrn_promote(prop_ion, 3, 0);
 	_ppvar[0]._pval = &prop_ion->param[1]; /* cai */
 	_ppvar[1]._pval = &prop_ion->param[3]; /* ica */
 	_ppvar[2]._pvoid = (void*)(&(prop_ion->dparam[0]._i)); /* iontype for ca */
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 "ca_cabalstore", 1e-10,
 "CaBuffer_cabalstore", 1e-10,
 "Buffer_cabalstore", 1e-10,
 "castore_cabalstore", 1e-10,
 0,0
};
 static void _thread_mem_init(Datum*);
 static void _thread_cleanup(Datum*);
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _cabalshell_stores_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("ca", -10000.);
 	_morphology_sym = hoc_lookup("morphology");
 	_ca_sym = hoc_lookup("ca_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 4);
  _extcall_thread = (Datum*)ecalloc(3, sizeof(Datum));
  _thread_mem_init(_extcall_thread);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 1, _thread_mem_init);
     _nrn_thread_reg(_mechtype, 0, _thread_cleanup);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 39, 7);
  hoc_register_dparam_semantics(_mechtype, 0, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "#ca_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "pointer");
  hoc_register_dparam_semantics(_mechtype, 4, "pointer");
  hoc_register_dparam_semantics(_mechtype, 6, "cvodeieq");
  hoc_register_dparam_semantics(_mechtype, 5, "diam");
 	nrn_writes_conc(_mechtype, 0);
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_synonym(_mechtype, _ode_synonym);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 cabalstore /home/workspace/266814/cabalshell_stores.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 
#define FARADAY _nrnunit_FARADAY[_nrnunit_use_legacy_]
static double _nrnunit_FARADAY[2] = {0x1.78e555060882cp+16, 96485.3}; /* 96485.3321233100141 */
 
#define PI _nrnunit_PI[_nrnunit_use_legacy_]
static double _nrnunit_PI[2] = {0x1.921fb54442d18p+1, 3.14159}; /* 3.14159265358979312 */
 /*Top LOCAL _zfrat [ 2 ] */
 /*Top LOCAL _zdsq , _zdsqvol , _zcasq */
static int _reset;
static char *modelname = "Calcium ion accumulation without diffusion and buffering and calcium induced calcium release";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int factors(_threadargsproto_);
 extern double *_nrn_thread_getelm(SparseObj*, int, int);
 
#define _MATELM1(_row,_col) *(_nrn_thread_getelm(_so, _row + 1, _col + 1))
 
#define _RHS1(_arg) _rhs[_arg+1]
  
#define _linmat1  0
 static int _spth1 = 1;
 static int _cvspth1 = 0;
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[8], _dlist1[8]; static double *_temp1;
 static int states();
 
static int  factors ( _threadargsproto_ ) {
   double _lr , _ldr2 , _lshsq ;
 if ( 2.0 > 1.0 ) {
     _lr = 1.0 / 2.0 ;
     _ldr2 = _lr / ( 2.0 - 1.0 ) / 2.0 ;
     vrat [ 0 ] = 0.0 ;
     _zfrat [ 0 ] = 2.0 * _lr * PI ;
     {int  _li ;for ( _li = 0 ; _li <= 2 - 2 ; _li ++ ) {
       vrat [ _li ] = vrat [ _li ] + PI * ( _lr - _ldr2 / 2.0 ) * 2.0 * _ldr2 ;
       _lr = _lr - _ldr2 ;
       _zfrat [ _li + 1 ] = 2.0 * PI * _lr / ( 2.0 * _ldr2 ) ;
       _lr = _lr - _ldr2 ;
       vrat [ _li + 1 ] = PI * ( _lr + _ldr2 / 2.0 ) * 2.0 * _ldr2 ;
       } }
     }
   else {
     _zfrat [ 0 ] = 1.0 ;
     vrat [ 0 ] = 1.0 ;
     }
   if ( 2.0  == 2.0 ) {
     _zfrat [ 1 ] = PI * ( 1.0 - shellfrac ) ;
     vrat [ 1 ] = 0.25 * PI * ( 1.0 - shellfrac ) * ( 1.0 - shellfrac ) ;
     vrat [ 0 ] = 0.25 * PI - vrat [ 1 ] ;
     }
    return 0; }
 
static void _hoc_factors(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r = 1.;
 factors ( _p, _ppvar, _thread, _nt );
 hoc_retpushx(_r);
}
 
static int states (void* _so, double* _rhs, double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt)
 {int _reset=0;
 {
   double b_flux, f_flux, _term; int _i;
 {int _i; double _dt1 = 1.0/dt;
for(_i=0;_i<8;_i++){
  	_RHS1(_i) = -_dt1*(_p[_slist1[_i]] - _p[_dlist1[_i]]);
	_MATELM1(_i, _i) = _dt1;
      
} 
for (_i=0; _i < 2; _i++) {
  	_RHS1(_i + 0) *= ( diam * diam * vrat [ ((int) _i ) ]) ;
_MATELM1(_i + 0, _i + 0) *= ( diam * diam * vrat [ ((int) _i ) ]);  } 
for (_i=0; _i < 2; _i++) {
  	_RHS1(_i + 2) *= ( diam * diam * vrat [ ((int) _i ) ]) ;
_MATELM1(_i + 2, _i + 2) *= ( diam * diam * vrat [ ((int) _i ) ]);  } 
for (_i=0; _i < 2; _i++) {
  	_RHS1(_i + 4) *= ( diam * diam * vrat [ ((int) _i ) ]) ;
_MATELM1(_i + 4, _i + 4) *= ( diam * diam * vrat [ ((int) _i ) ]);  } 
for (_i=0; _i < 2; _i++) {
  	_RHS1(_i + 6) *= ( diam * diam * vrat [ ((int) _i ) ]) ;
_MATELM1(_i + 6, _i + 6) *= ( diam * diam * vrat [ ((int) _i ) ]);  } }
 /* COMPARTMENT _li , diam * diam * vrat [ ((int) _i ) ] {
     ca CaBuffer Buffer castore }
   */
 icapump = icapumpmax * ( 1.0 / ( 1.0 + km / ca [ 0 ] ) ) ;
   {int  _li ;for ( _li = 0 ; _li <= 2 - 2 ; _li ++ ) {
     /* ~ ca [ _li ] <-> ca [ _li + 1 ] ( DCa * _zfrat [ _li + 1 ] , DCa * _zfrat [ _li + 1 ] )*/
 f_flux =  DCa * _zfrat [ _li + 1 ] * ca [ _li] ;
 b_flux =  DCa * _zfrat [ _li + 1 ] * ca [ _li + 1] ;
 _RHS1( 6 +  _li) -= (f_flux - b_flux);
 _RHS1( 6 +  _li + 1) += (f_flux - b_flux);
 
 _term =  DCa * _zfrat [ _li + 1 ] ;
 _MATELM1( 6 +  _li ,6 +  _li)  += _term;
 _MATELM1( 6 +  _li + 1 ,6 +  _li)  -= _term;
 _term =  DCa * _zfrat [ _li + 1 ] ;
 _MATELM1( 6 +  _li ,6 +  _li + 1)  -= _term;
 _MATELM1( 6 +  _li + 1 ,6 +  _li + 1)  += _term;
 /*REACTION*/
  } }
   _zdsq = diam * diam ;
   {int  _li ;for ( _li = 0 ; _li <= 2 - 1 ; _li ++ ) {
     _zdsqvol = _zdsq * vrat [ _li ] ;
     /* ~ ca [ _li ] + Buffer [ _li ] <-> CaBuffer [ _li ] ( k1buf * _zdsqvol , k2buf * _zdsqvol )*/
 f_flux =  k1buf * _zdsqvol * Buffer [ _li] * ca [ _li] ;
 b_flux =  k2buf * _zdsqvol * CaBuffer [ _li] ;
 _RHS1( 0 +  _li) -= (f_flux - b_flux);
 _RHS1( 6 +  _li) -= (f_flux - b_flux);
 _RHS1( 2 +  _li) += (f_flux - b_flux);
 
 _term =  k1buf * _zdsqvol * ca [ _li] ;
 _MATELM1( 0 +  _li ,0 +  _li)  += _term;
 _MATELM1( 6 +  _li ,0 +  _li)  += _term;
 _MATELM1( 2 +  _li ,0 +  _li)  -= _term;
 _term =  k1buf * _zdsqvol * Buffer [ _li] ;
 _MATELM1( 0 +  _li ,6 +  _li)  += _term;
 _MATELM1( 6 +  _li ,6 +  _li)  += _term;
 _MATELM1( 2 +  _li ,6 +  _li)  -= _term;
 _term =  k2buf * _zdsqvol ;
 _MATELM1( 0 +  _li ,2 +  _li)  -= _term;
 _MATELM1( 6 +  _li ,2 +  _li)  -= _term;
 _MATELM1( 2 +  _li ,2 +  _li)  += _term;
 /*REACTION*/
  } }
   _zdsqvol = _zdsq * vrat [ 1 ] ;
   /* ~ ca [ 2 - 1 ] <-> castore [ 2 - 1 ] ( tog * ju_p * _zdsqvol , tog * jcicr_p * _zdsqvol )*/
 f_flux =  tog * ju_p * _zdsqvol * ca [ 2 - 1] ;
 b_flux =  tog * jcicr_p * _zdsqvol * castore [ 2 - 1] ;
 _RHS1( 6 +  2 - 1) -= (f_flux - b_flux);
 _RHS1( 4 +  2 - 1) += (f_flux - b_flux);
 
 _term =  tog * ju_p * _zdsqvol ;
 _MATELM1( 6 +  2 - 1 ,6 +  2 - 1)  += _term;
 _MATELM1( 4 +  2 - 1 ,6 +  2 - 1)  -= _term;
 _term =  tog * jcicr_p * _zdsqvol ;
 _MATELM1( 6 +  2 - 1 ,4 +  2 - 1)  -= _term;
 _MATELM1( 4 +  2 - 1 ,4 +  2 - 1)  += _term;
 /*REACTION*/
  /* ~ ca [ 0 ] < < ( - SCALE * ( ica + icapump ) * PI * diam * ( 1e4 ) / ( 2.0 * FARADAY ) )*/
 f_flux = b_flux = 0.;
 _RHS1( 6 +  0) += (b_flux =   ( - SCALE * ( ica + icapump ) * PI * diam * ( 1e4 ) / ( 2.0 * FARADAY ) ) );
 /*FLUX*/
  cai = ca [ 0 ] ;
   cac = ca [ 2 - 1 ] ;
   cast = castore [ 2 - 1 ] ;
     } return _reset;
 }
 
/*CVODE ode begin*/
 static int _ode_spec1(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {int _reset=0;{
 double b_flux, f_flux, _term; int _i;
 {int _i; for(_i=0;_i<8;_i++) _p[_dlist1[_i]] = 0.0;}
 /* COMPARTMENT _li , diam * diam * vrat [ ((int) _i ) ] {
   ca CaBuffer Buffer castore }
 */
 icapump = icapumpmax * ( 1.0 / ( 1.0 + km / ca [ 0 ] ) ) ;
 {int  _li ;for ( _li = 0 ; _li <= 2 - 2 ; _li ++ ) {
   /* ~ ca [ _li ] <-> ca [ _li + 1 ] ( DCa * _zfrat [ _li + 1 ] , DCa * _zfrat [ _li + 1 ] )*/
 f_flux =  DCa * _zfrat [ _li + 1 ] * ca [ _li] ;
 b_flux =  DCa * _zfrat [ _li + 1 ] * ca [ _li + 1] ;
 Dca [ _li] -= (f_flux - b_flux);
 Dca [ _li + 1] += (f_flux - b_flux);
 
 /*REACTION*/
  } }
 _zdsq = diam * diam ;
 {int  _li ;for ( _li = 0 ; _li <= 2 - 1 ; _li ++ ) {
   _zdsqvol = _zdsq * vrat [ _li ] ;
   /* ~ ca [ _li ] + Buffer [ _li ] <-> CaBuffer [ _li ] ( k1buf * _zdsqvol , k2buf * _zdsqvol )*/
 f_flux =  k1buf * _zdsqvol * Buffer [ _li] * ca [ _li] ;
 b_flux =  k2buf * _zdsqvol * CaBuffer [ _li] ;
 DBuffer [ _li] -= (f_flux - b_flux);
 Dca [ _li] -= (f_flux - b_flux);
 DCaBuffer [ _li] += (f_flux - b_flux);
 
 /*REACTION*/
  } }
 _zdsqvol = _zdsq * vrat [ 1 ] ;
 /* ~ ca [ 2 - 1 ] <-> castore [ 2 - 1 ] ( tog * ju_p * _zdsqvol , tog * jcicr_p * _zdsqvol )*/
 f_flux =  tog * ju_p * _zdsqvol * ca [ 2 - 1] ;
 b_flux =  tog * jcicr_p * _zdsqvol * castore [ 2 - 1] ;
 Dca [ 2 - 1] -= (f_flux - b_flux);
 Dcastore [ 2 - 1] += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ ca [ 0 ] < < ( - SCALE * ( ica + icapump ) * PI * diam * ( 1e4 ) / ( 2.0 * FARADAY ) )*/
 f_flux = b_flux = 0.;
 Dca [ 0] += (b_flux =   ( - SCALE * ( ica + icapump ) * PI * diam * ( 1e4 ) / ( 2.0 * FARADAY ) ) );
 /*FLUX*/
  cai = ca [ 0 ] ;
 cac = ca [ 2 - 1 ] ;
 cast = castore [ 2 - 1 ] ;
 for (_i=0; _i < 2; _i++) { _p[_dlist1[_i + 0]] /= ( diam * diam * vrat [ ((int) _i ) ]);}
 for (_i=0; _i < 2; _i++) { _p[_dlist1[_i + 2]] /= ( diam * diam * vrat [ ((int) _i ) ]);}
 for (_i=0; _i < 2; _i++) { _p[_dlist1[_i + 4]] /= ( diam * diam * vrat [ ((int) _i ) ]);}
 for (_i=0; _i < 2; _i++) { _p[_dlist1[_i + 6]] /= ( diam * diam * vrat [ ((int) _i ) ]);}
   } return _reset;
 }
 
/*CVODE matsol*/
 static int _ode_matsol1(void* _so, double* _rhs, double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {int _reset=0;{
 double b_flux, f_flux, _term; int _i;
   b_flux = f_flux = 0.;
 {int _i; double _dt1 = 1.0/dt;
for(_i=0;_i<8;_i++){
  	_RHS1(_i) = _dt1*(_p[_dlist1[_i]]);
	_MATELM1(_i, _i) = _dt1;
      
} 
for (_i=0; _i < 2; _i++) {
  	_RHS1(_i + 0) *= ( diam * diam * vrat [ ((int) _i ) ]) ;
_MATELM1(_i + 0, _i + 0) *= ( diam * diam * vrat [ ((int) _i ) ]);  } 
for (_i=0; _i < 2; _i++) {
  	_RHS1(_i + 2) *= ( diam * diam * vrat [ ((int) _i ) ]) ;
_MATELM1(_i + 2, _i + 2) *= ( diam * diam * vrat [ ((int) _i ) ]);  } 
for (_i=0; _i < 2; _i++) {
  	_RHS1(_i + 4) *= ( diam * diam * vrat [ ((int) _i ) ]) ;
_MATELM1(_i + 4, _i + 4) *= ( diam * diam * vrat [ ((int) _i ) ]);  } 
for (_i=0; _i < 2; _i++) {
  	_RHS1(_i + 6) *= ( diam * diam * vrat [ ((int) _i ) ]) ;
_MATELM1(_i + 6, _i + 6) *= ( diam * diam * vrat [ ((int) _i ) ]);  } }
 /* COMPARTMENT _li , diam * diam * vrat [ ((int) _i ) ] {
 ca CaBuffer Buffer castore }
 */
 icapump = icapumpmax * ( 1.0 / ( 1.0 + km / ca [ 0 ] ) ) ;
 {int  _li ;for ( _li = 0 ; _li <= 2 - 2 ; _li ++ ) {
 /* ~ ca [ _li ] <-> ca [ _li + 1 ] ( DCa * _zfrat [ _li + 1 ] , DCa * _zfrat [ _li + 1 ] )*/
 _term =  DCa * _zfrat [ _li + 1 ] ;
 _MATELM1( 6 +  _li ,6 +  _li)  += _term;
 _MATELM1( 6 +  _li + 1 ,6 +  _li)  -= _term;
 _term =  DCa * _zfrat [ _li + 1 ] ;
 _MATELM1( 6 +  _li ,6 +  _li + 1)  -= _term;
 _MATELM1( 6 +  _li + 1 ,6 +  _li + 1)  += _term;
 /*REACTION*/
  } }
 _zdsq = diam * diam ;
 {int  _li ;for ( _li = 0 ; _li <= 2 - 1 ; _li ++ ) {
 _zdsqvol = _zdsq * vrat [ _li ] ;
 /* ~ ca [ _li ] + Buffer [ _li ] <-> CaBuffer [ _li ] ( k1buf * _zdsqvol , k2buf * _zdsqvol )*/
 _term =  k1buf * _zdsqvol * ca [ _li] ;
 _MATELM1( 0 +  _li ,0 +  _li)  += _term;
 _MATELM1( 6 +  _li ,0 +  _li)  += _term;
 _MATELM1( 2 +  _li ,0 +  _li)  -= _term;
 _term =  k1buf * _zdsqvol * Buffer [ _li] ;
 _MATELM1( 0 +  _li ,6 +  _li)  += _term;
 _MATELM1( 6 +  _li ,6 +  _li)  += _term;
 _MATELM1( 2 +  _li ,6 +  _li)  -= _term;
 _term =  k2buf * _zdsqvol ;
 _MATELM1( 0 +  _li ,2 +  _li)  -= _term;
 _MATELM1( 6 +  _li ,2 +  _li)  -= _term;
 _MATELM1( 2 +  _li ,2 +  _li)  += _term;
 /*REACTION*/
  } }
 _zdsqvol = _zdsq * vrat [ 1 ] ;
 /* ~ ca [ 2 - 1 ] <-> castore [ 2 - 1 ] ( tog * ju_p * _zdsqvol , tog * jcicr_p * _zdsqvol )*/
 _term =  tog * ju_p * _zdsqvol ;
 _MATELM1( 6 +  2 - 1 ,6 +  2 - 1)  += _term;
 _MATELM1( 4 +  2 - 1 ,6 +  2 - 1)  -= _term;
 _term =  tog * jcicr_p * _zdsqvol ;
 _MATELM1( 6 +  2 - 1 ,4 +  2 - 1)  -= _term;
 _MATELM1( 4 +  2 - 1 ,4 +  2 - 1)  += _term;
 /*REACTION*/
  /* ~ ca [ 0 ] < < ( - SCALE * ( ica + icapump ) * PI * diam * ( 1e4 ) / ( 2.0 * FARADAY ) )*/
 /*FLUX*/
  cai = ca [ 0 ] ;
 cac = ca [ 2 - 1 ] ;
 cast = castore [ 2 - 1 ] ;
   } return _reset;
 }
 
/*CVODE end*/
 
static int _ode_count(int _type){ return 8;}
 
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
  ica = _ion_ica;
  cai = _ion_cai;
     _ode_spec1 (_p, _ppvar, _thread, _nt);
  _ion_cai = cai;
 }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
	double* _p; Datum* _ppvar;
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 8; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 static void _ode_synonym(int _cnt, double** _pp, Datum** _ppd) { 
	double* _p; Datum* _ppvar;
 	int _i; 
	for (_i=0; _i < _cnt; ++_i) {_p = _pp[_i]; _ppvar = _ppd[_i];
 _ion_cai =  ca [ 0 ] ;
 }}
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _cvode_sparse_thread(&_thread[_cvspth1]._pvoid, 8, _dlist1, _p, _ode_matsol1, _ppvar, _thread, _nt);
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
  ica = _ion_ica;
  cai = _ion_cai;
 _ode_matsol_instance1(_threadargs_);
 }}
 
static void _thread_mem_init(Datum* _thread) {
   _thread[2]._pval = (double*)ecalloc(5, sizeof(double));
 }
 
static void _thread_cleanup(Datum* _thread) {
   _nrn_destroy_sparseobj_thread(_thread[_cvspth1]._pvoid);
   _nrn_destroy_sparseobj_thread(_thread[_spth1]._pvoid);
   free((void*)(_thread[2]._pval));
 }
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_ca_sym, _ppvar, 0, 1);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 1, 3);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
  int _i; double _save;{
 for (_i=0; _i<2; _i++) Buffer[_i] = Buffer0;
 for (_i=0; _i<2; _i++) CaBuffer[_i] = CaBuffer0;
 for (_i=0; _i<2; _i++) castore[_i] = castore0;
 for (_i=0; _i<2; _i++) ca[_i] = ca0;
 {
   factors ( _threadargs_ ) ;
   cai = cainit ;
   Kd = k1buf ;
   B0 = TotalBuffer / ( 1.0 + Kd * cainit ) ;
   {int  _li ;for ( _li = 0 ; _li <= 2 - 1 ; _li ++ ) {
     ca [ _li ] = cai ;
     Buffer [ _li ] = B0 ;
     CaBuffer [ _li ] = TotalBuffer - B0 ;
     castore [ _li ] = 0.2 ;
     } }
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
  ica = _ion_ica;
  cai = _ion_cai;
 initmodel(_p, _ppvar, _thread, _nt);
  _ion_cai = cai;
  nrn_wrote_conc(_ca_sym, (&(_ion_cai)) - 1, _style_ca);
}
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt, double _v){double _current=0.;v=_v;{
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
  cai = _ion_cai;
  ica = _ion_ica;
  cai = _ion_cai;
 {  sparse_thread(&_thread[_spth1]._pvoid, 8, _slist1, _dlist1, _p, &t, dt, states, _linmat1, _ppvar, _thread, _nt);
     if (secondorder) {
    int _i;
    for (_i = 0; _i < 8; ++_i) {
      _p[_slist1[_i]] += dt*_p[_dlist1[_i]];
    }}
 } {
   }
  _ion_cai = cai;
}}
 dt = _dtsav;
}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 for(_i=0;_i<2;_i++){_slist1[0+_i] = Buffer_columnindex + _i;  _dlist1[0+_i] = DBuffer_columnindex + _i;}
 for(_i=0;_i<2;_i++){_slist1[2+_i] = CaBuffer_columnindex + _i;  _dlist1[2+_i] = DCaBuffer_columnindex + _i;}
 for(_i=0;_i<2;_i++){_slist1[4+_i] = castore_columnindex + _i;  _dlist1[4+_i] = Dcastore_columnindex + _i;}
 for(_i=0;_i<2;_i++){_slist1[6+_i] = ca_columnindex + _i;  _dlist1[6+_i] = Dca_columnindex + _i;}
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/home/workspace/266814/cabalshell_stores.mod";
static const char* nmodl_file_text = 
  "TITLE Calcium ion accumulation without diffusion and buffering and calcium induced calcium release\n"
  " \n"
  "                 \n"
  "NEURON {\n"
  "	SUFFIX cabalstore\n"
  "	USEION ca READ cai, ica WRITE cai\n"
  "\n"
  "	THREADSAFE :but we make it so (this SHOULD not be a problem so long as each neuron or compartment is handled by one thread)\n"
  "	RANGE  cainit, fCa , icapump,icapumpmax,km, TotalBuffer, k1buf, k2buf, SCALE, shellfrac, DCa, vrat, frat, basal, cac, cast, tog\n"
  "	POINTER ju_p, jcicr_p\n"
  "}\n"
  "\n"
  "DEFINE Nannuli 2 : thin shell and option\n"
  "\n"
  "UNITS {\n"
  "	(molar) = (1/liter)\n"
  "	(mM) =  (millimolar)\n"
  "	(um) =  (micron)\n"
  "	(mA) =  (milliamp)\n"
  "	FARADAY = (faraday) (coulomb) \n"
  "	PI = (pi) (1)\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "        fCa = 0.05  (1)\n"
  "        cainit = 0.0001 (mM)\n"
  "        dt    (ms)\n"
  "        celsius = 35  (degC)\n"
  "        icapumpmax  = 0.00191  (mA/cm2) : 191\n"
  "        km = 0.000500         (mM)\n"
  "        DCa = 0.6 (um2/ms) : diffusion constant for calcium, set to 0 to remove radial diffusion\n"
  "        k1buf = 100 (/mM-ms) : Yamada et al\n"
  "        k2buf = 0.1 (/ms)\n"
  "        TotalBuffer = 0.03  (mM)\n"
  "        basal = 0 (mM) \n"
  "        shellfrac = 0.25 : fraction of compartment diameter in outer shell\n"
  "        SCALE = 1\n"
  "        tog = 1\n"
  "\n"
  "         }\n"
  "\n"
  "ASSIGNED {\n"
  "  diam  (um)\n"
  "  ica   (mA/cm2)\n"
  "  icapump (mA/cm2)\n"
  "  vrat[Nannuli]\n"
  "  Kd  (/mM)\n"
  "  B0  (mM)\n"
  "  cai (mM)\n"
  "  cast (mM)\n"
  "  cac (mM)\n"
  "  jcicr_p\n"
  "  ju_p\n"
  "}\n"
  "\n"
  "STATE {\n"
  "  ca[Nannuli] (mM) <1e-10>\n"
  "  CaBuffer[Nannuli] (mM) <1e-10>\n"
  "  Buffer[Nannuli] (mM) <1e-10>\n"
  "  castore[Nannuli] (mM) <1e-10>\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "	SOLVE states METHOD sparse\n"
  "}\n"
  "\n"
  "INITIAL{\n"
  "  factors()\n"
  "   \n"
  "  cai=cainit\n"
  "  \n"
  "  Kd = k1buf\n"
  "  B0 = TotalBuffer/(1+Kd*cainit)\n"
  "  \n"
  "  FROM i=0 TO Nannuli-1 {\n"
  "    ca[i] = cai\n"
  "    Buffer[i] = B0\n"
  "    CaBuffer[i] = TotalBuffer - B0\n"
  "    castore[i] = 0.2 : 200 uM\n"
  "  }\n"
  "  :Buffer[0] = 0\n"
  "  :CaBuffer[0] = 0\n"
  "}\n"
  "\n"
  "LOCAL frat[Nannuli]\n"
  "PROCEDURE factors() {\n"
  "  LOCAL r, dr2, shsq\n"
  "  if(Nannuli > 1) {\n"
  "  r = 1/2 : starts at edge (half diam)\n"
  "  dr2 = r/(Nannuli-1)/2 : full thickness of outermost annulus,\n"
  "  : half thickness of all other annuli\n"
  "  vrat[0] = 0\n"
  "  frat[0] = 2*r*PI\n"
  "  FROM i=0 TO Nannuli-2 {\n"
  "    vrat[i] = vrat[i] + PI*(r-dr2/2)*2*dr2 : interior half\n"
  "    r = r - dr2\n"
  "    frat[i+1] = 2*PI*r/(2*dr2) : outer radius of annulus\n"
  "                               : div by distance between centers\n"
  "    r = r - dr2\n"
  "    vrat[i+1] = PI*(r+dr2/2)*2*dr2 : outer half of annulus\n"
  "    }\n"
  "  } else { : for 1 compartment buffering\n"
  "  frat[0] = 1\n"
  "  vrat[0] = 1\n"
  "  }\n"
  "  if(Nannuli == 2){\n"
  "     frat[1] = PI*(1.0-shellfrac)\n"
  "     vrat[1] = 0.25*PI*(1.0-shellfrac)*(1.0-shellfrac)\n"
  "     vrat[0] = 0.25*PI-vrat[1]\n"
  "  \n"
  "  }\n"
  "\n"
  "  }\n"
  " \n"
  "LOCAL dsq, dsqvol, casq\n"
  "\n"
  "\n"
  "\n"
  "KINETIC states {\n"
  "  COMPARTMENT i, diam*diam*vrat[i] {ca CaBuffer Buffer castore}\n"
  "  icapump = icapumpmax*(1/(1 + km/ca[0])) :calcium only exits from outer layer\n"
  "\n"
  "  FROM i = 0 TO Nannuli-2 {\n"
  "    ~ ca[i] <-> ca[i+1] (DCa*frat[i+1], DCa*frat[i+1]) : turn off/on diffusion\n"
  "  }\n"
  "  dsq = diam*diam\n"
  "  FROM i=0 TO Nannuli-1 {\n"
  "    dsqvol = dsq*vrat[i]\n"
  "    ~ca[i] + Buffer[i] <-> CaBuffer[i] (k1buf*dsqvol, k2buf*dsqvol)\n"
  "  }\n"
  "  dsqvol = dsq*vrat[1]\n"
  "  ~ ca[Nannuli-1] <-> castore[Nannuli-1] (tog*ju_p*dsqvol,tog*jcicr_p*dsqvol)\n"
  "  ~ ca[0] << (-SCALE*(ica +icapump)*PI*diam*(1e4)/(2*FARADAY))\n"
  "  \n"
  "  cai = ca[0]\n"
  "  cac = ca[Nannuli-1]\n"
  "  cast = castore[Nannuli-1]\n"
  "}\n"
  ;
#endif
