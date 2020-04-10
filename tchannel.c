/* Created by Language version: 6.2.0 */
/* NOT VECTORIZED */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "scoplib_ansi.h"
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
 
#define _threadargscomma_ /**/
#define _threadargs_ /**/
 
#define _threadargsprotocomma_ /**/
#define _threadargsproto_ /**/
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 static double *_p; static Datum *_ppvar;
 
#define t nrn_threads->_t
#define dt nrn_threads->_dt
#define pbar _p[0]
#define pcabar _p[1]
#define vshift _p[2]
#define qt _p[3]
#define GHKo _p[4]
#define GHKa _p[5]
#define GHKb _p[6]
#define GHKc _p[7]
#define itt _p[8]
#define itmax _p[9]
#define it _p[10]
#define tt_inf _p[11]
#define u_inf _p[12]
#define tau_tt _p[13]
#define tau_u _p[14]
#define tt_exp _p[15]
#define u_exp _p[16]
#define tt _p[17]
#define u _p[18]
#define cai _p[19]
#define cao _p[20]
#define Dtt _p[21]
#define Du _p[22]
#define ica _p[23]
#define _g _p[24]
#define _ion_ica	*_ppvar[0]._pval
#define _ion_cai	*_ppvar[1]._pval
#define _ion_cao	*_ppvar[2]._pval
#define _ion_dicadv	*_ppvar[3]._pval
 
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
 /* external NEURON variables */
 extern double celsius;
 /* declaration of user functions */
 static void _hoc_evaluate_fct(void);
 static void _hoc_efun(void);
 static void _hoc_ghk(void);
 static void _hoc_states(void);
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _p = _prop->param; _ppvar = _prop->dparam;
 }
 static void _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range(int);
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 hoc_retpushx(1.);
}
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 "setdata_tchannel", _hoc_setdata,
 "evaluate_fct_tchannel", _hoc_evaluate_fct,
 "efun_tchannel", _hoc_efun,
 "ghk_tchannel", _hoc_ghk,
 "states_tchannel", _hoc_states,
 0, 0
};
#define efun efun_tchannel
#define ghk ghk_tchannel
 extern double efun( double );
 extern double ghk( double , double , double );
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "pcabar_tchannel", 0, 1e+09,
 "pbar_tchannel", 0, 1e+09,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "pbar_tchannel", "cm/s",
 "pcabar_tchannel", "cm/s",
 "vshift_tchannel", "mV",
 "itt_tchannel", "nA/cm2",
 "itmax_tchannel", "nA/cm2",
 "it_tchannel", "nA/cm2",
 0,0
};
 static double delta_t = 1;
 static double tt0 = 0;
 static double u0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(_NrnThread*, _Memb_list*, int);
static void nrn_state(_NrnThread*, _Memb_list*, int);
 static void nrn_cur(_NrnThread*, _Memb_list*, int);
static void  nrn_jacob(_NrnThread*, _Memb_list*, int);
 
static int _ode_count(int);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "6.2.0",
"tchannel",
 "pbar_tchannel",
 "pcabar_tchannel",
 "vshift_tchannel",
 "qt_tchannel",
 "GHKo_tchannel",
 "GHKa_tchannel",
 "GHKb_tchannel",
 "GHKc_tchannel",
 0,
 "itt_tchannel",
 "itmax_tchannel",
 "it_tchannel",
 "tt_inf_tchannel",
 "u_inf_tchannel",
 "tau_tt_tchannel",
 "tau_u_tchannel",
 "tt_exp_tchannel",
 "u_exp_tchannel",
 0,
 "tt_tchannel",
 "u_tchannel",
 0,
 0};
 static Symbol* _ca_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 25, _prop);
 	/*initialize range parameters*/
 	pbar = 1.7e-05;
 	pcabar = 0.0002;
 	vshift = 0;
 	qt = 1;
 	GHKo = 0;
 	GHKa = 0;
 	GHKb = 0;
 	GHKc = 0;
 	_prop->param = _p;
 	_prop->param_size = 25;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 4, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_ca_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[0]._pval = &prop_ion->param[3]; /* ica */
 	_ppvar[1]._pval = &prop_ion->param[1]; /* cai */
 	_ppvar[2]._pval = &prop_ion->param[2]; /* cao */
 	_ppvar[3]._pval = &prop_ion->param[4]; /* _ion_dicadv */
 
}
 static void _initlists();
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*f)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _tchannel_reg() {
	int _vectorized = 0;
  _initlists();
 	ion_reg("ca", -10000.);
 	_ca_sym = hoc_lookup("ca_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 0);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
  hoc_register_dparam_size(_mechtype, 4);
 	hoc_register_cvode(_mechtype, _ode_count, 0, 0, 0);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 tchannel /cygdrive/c/Neuron_B/Downto1/tchannel.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double FARADAY = 96485.3;
 static double R = 8.31342;
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int evaluate_fct(double);
static int states();
 
double ghk (  double _lv , double _lci , double _lco ) {
   double _lghk;
 double _lz , _leci , _leco ;
 _lz = 1e-3 * 2.0 * FARADAY * _lv / ( R * ( celsius + 273.18 ) ) ;
   _leco = _lco * efun ( _threadargscomma_ _lz ) ;
   _leci = _lci * efun ( _threadargscomma_ - _lz ) ;
   _lghk = ( .001 ) * 2.0 * FARADAY * ( _leci - _leco ) ;
   
return _lghk;
 }
 
static void _hoc_ghk(void) {
  double _r;
   _r =  ghk (  *getarg(1) , *getarg(2) , *getarg(3) );
 hoc_retpushx(_r);
}
 
double efun (  double _lz ) {
   double _lefun;
 if ( fabs ( _lz ) < 1e-4 ) {
     _lefun = 1.0 - _lz / 2.0 ;
     }
   else {
     _lefun = _lz / ( exp ( _lz ) - 1.0 ) ;
     }
   
return _lefun;
 }
 
static void _hoc_efun(void) {
  double _r;
   _r =  efun (  *getarg(1) );
 hoc_retpushx(_r);
}
 
static int  states (  ) {
   evaluate_fct ( _threadargscomma_ v ) ;
   tt = tt + tt_exp * ( tt_inf - tt ) ;
   u = u + u_exp * ( u_inf - u ) ;
   
/*VERBATIM*/
return 0;
  return 0; }
 
static void _hoc_states(void) {
  double _r;
   _r = 1.;
 states (  );
 hoc_retpushx(_r);
}
 
static int  evaluate_fct (  double _lv ) {
   double _la , _lb , _ly , _ld ;
 qt = pow( 2.9 , ( ( celsius - 18.0 ) / 10.0 ) ) ;
   vshift = ( 15.0 - cao ) * ( - .757575 ) ;
   tt_inf = pow( ( 1.0 / ( 1.0 + exp ( ( ( - 56.4 + vshift ) - ( _lv ) ) / 13.2 ) ) ) , 3.0 ) ;
   if ( _lv < - 60.0 + vshift ) {
     tau_tt = ( 44.2 + .8014 + pow( .0049 , 2.0 ) + ( ( 9.7 * ( pow( 10.0 , - 6.0 ) ) ) * pow( ( _lv + vshift ) , 3.0 ) ) ) * ( 1.0 / qt ) ;
     }
   else {
     tau_tt = ( .5187 + .01550 + pow( .0013 , 2.0 ) + ( ( - .4064 * pow( 10.0 , - 6.0 ) ) * pow( ( _lv + vshift ) , 3.0 ) ) ) * ( 1.0 / qt ) ;
     }
   u_inf = 1.0 / ( 1.0 + exp ( ( ( - 68.2 + vshift ) - ( _lv ) ) / - 7.63 ) ) ;
   if ( _lv <= - 55.0 + vshift ) {
     tau_u = ( ( 33.08 + ( 346.6 - 33.08 ) / ( 1.0 + exp ( ( - 82.2 - ( _lv + vshift ) ) / - 3.362 ) ) ) ) * ( 1.0 / qt ) ;
     }
   else {
     tau_u = ( ( ( .01149 * exp ( - .1348 * ( _lv - vshift ) ) ) + ( 31.42 * exp ( - .0007572 * ( _lv - vshift ) ) ) + ( - 13.38 ) ) ) * ( 1.0 / qt ) ;
     }
   tt_exp = 1.0 - exp ( - dt / tau_tt ) ;
   u_exp = 1.0 - exp ( - dt / tau_u ) ;
    return 0; }
 
static void _hoc_evaluate_fct(void) {
  double _r;
   _r = 1.;
 evaluate_fct (  *getarg(1) );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ hoc_execerror("tchannel", "cannot be used with CVODE"); return 0;}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_ca_sym, _ppvar, 0, 3);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 1, 1);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 2, 2);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 3, 4);
 }

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  tt = tt0;
  u = u0;
 {
   tt = .0003 ;
   u = .9 ;
   }
  _sav_indep = t; t = _save;

}
}

static void nrn_init(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
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
  ica = _ion_ica;
  cai = _ion_cai;
  cao = _ion_cao;
 initmodel();
 }}

static double _nrn_current(double _v){double _current=0.;v=_v;{ {
   itt = ( tt * tt * tt * u * pbar * ghk ( _threadargscomma_ v , cai , cao ) ) ;
   itmax = ( pbar * ghk ( _threadargscomma_ v , cai , cao ) ) / pow( 10.0 , 6.0 ) ;
   ica = itt ;
   }
 _current += ica;

} return _current;
}

static void nrn_cur(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
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
  ica = _ion_ica;
  cai = _ion_cai;
  cao = _ion_cao;
 _g = _nrn_current(_v + .001);
 	{ double _dica;
  _dica = ica;
 _rhs = _nrn_current(_v);
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
 
}}

static void nrn_jacob(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
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
 
}}

static void nrn_state(_NrnThread* _nt, _Memb_list* _ml, int _type){
 double _break, _save;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
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
 _break = t + .5*dt; _save = t;
 v=_v;
{
  ica = _ion_ica;
  cai = _ion_cai;
  cao = _ion_cao;
 { {
 for (; t < _break; t += dt) {
 error =  states();
 if(error){fprintf(stderr,"at line 74 in file tchannel.mod:\n     \n"); nrn_complain(_p); abort_run(error);}
 
}}
 t = _save;
 } }}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
_first = 0;
}
