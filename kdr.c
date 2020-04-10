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
#define gmax _p[0]
#define mbaserate _p[1]
#define i _p[2]
#define g _p[3]
#define m _p[4]
#define h _p[5]
#define cao _p[6]
#define cai _p[7]
#define ica _p[8]
#define ina _p[9]
#define ik _p[10]
#define Dm _p[11]
#define Dh _p[12]
#define _g _p[13]
#define _ion_ina	*_ppvar[0]._pval
#define _ion_dinadv	*_ppvar[1]._pval
#define _ion_ik	*_ppvar[2]._pval
#define _ion_dikdv	*_ppvar[3]._pval
#define _ion_cao	*_ppvar[4]._pval
#define _ion_cai	*_ppvar[5]._pval
#define _ion_ica	*_ppvar[6]._pval
#define _ion_dicadv	*_ppvar[7]._pval
 
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
 static void _hoc_FRT(void);
 static void _hoc_alpha(void);
 static void _hoc_beta(void);
 static void _hoc_ghkca(void);
 static void _hoc_iassign(void);
 static void _hoc_mh(void);
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
 "setdata_kdr", _hoc_setdata,
 "FRT_kdr", _hoc_FRT,
 "alpha_kdr", _hoc_alpha,
 "beta_kdr", _hoc_beta,
 "ghkca_kdr", _hoc_ghkca,
 "iassign_kdr", _hoc_iassign,
 "mh_kdr", _hoc_mh,
 "states_kdr", _hoc_states,
 0, 0
};
#define FRT FRT_kdr
#define alpha alpha_kdr
#define beta beta_kdr
#define ghkca ghkca_kdr
 extern double FRT( double );
 extern double alpha( double , double );
 extern double beta( double , double );
 extern double ghkca( double );
 /* declare global and static user variables */
#define Add Add_kdr
 double Add[2];
#define Inf Inf_kdr
 double Inf[2];
#define Mult Mult_kdr
 double Mult[2];
#define Tau Tau_kdr
 double Tau[2];
#define erev erev_kdr
 double erev = -90;
#define hexp hexp_kdr
 double hexp = 0;
#define hq10 hq10_kdr
 double hq10 = 3;
#define htemp htemp_kdr
 double htemp = 0;
#define hbasetau hbasetau_kdr
 double hbasetau = 0;
#define hvhalf hvhalf_kdr
 double hvhalf = 0;
#define hbaserate hbaserate_kdr
 double hbaserate = 0;
#define hgamma hgamma_kdr
 double hgamma = 0;
#define hvalence hvalence_kdr
 double hvalence = 0;
#define mexp mexp_kdr
 double mexp = 4;
#define mq10 mq10_kdr
 double mq10 = 3;
#define mtemp mtemp_kdr
 double mtemp = 24;
#define mbasetau mbasetau_kdr
 double mbasetau = 1;
#define mvhalf mvhalf_kdr
 double mvhalf = -35;
#define mgamma mgamma_kdr
 double mgamma = 0.7;
#define mvalence mvalence_kdr
 double mvalence = 3;
#define usetable usetable_kdr
 double usetable = 1;
#define vmin vmin_kdr
 double vmin = -100;
#define vmax vmax_kdr
 double vmax = 50;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "usetable_kdr", 0, 1,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "erev_kdr", "mV",
 "vmax_kdr", "mV",
 "vmin_kdr", "mV",
 "gmax_kdr", "umho",
 "i_kdr", "mA/cm^2",
 "g_kdr", "mho/cm^2",
 0,0
};
 static double delta_t = 1;
 static double h0 = 0;
 static double m0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "erev_kdr", &erev_kdr,
 "mvalence_kdr", &mvalence_kdr,
 "mgamma_kdr", &mgamma_kdr,
 "mvhalf_kdr", &mvhalf_kdr,
 "mbasetau_kdr", &mbasetau_kdr,
 "mtemp_kdr", &mtemp_kdr,
 "mq10_kdr", &mq10_kdr,
 "mexp_kdr", &mexp_kdr,
 "hvalence_kdr", &hvalence_kdr,
 "hgamma_kdr", &hgamma_kdr,
 "hbaserate_kdr", &hbaserate_kdr,
 "hvhalf_kdr", &hvhalf_kdr,
 "hbasetau_kdr", &hbasetau_kdr,
 "htemp_kdr", &htemp_kdr,
 "hq10_kdr", &hq10_kdr,
 "hexp_kdr", &hexp_kdr,
 "vmax_kdr", &vmax_kdr,
 "vmin_kdr", &vmin_kdr,
 "usetable_kdr", &usetable_kdr,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 "Inf_kdr", Inf_kdr, 2,
 "Tau_kdr", Tau_kdr, 2,
 "Mult_kdr", Mult_kdr, 2,
 "Add_kdr", Add_kdr, 2,
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
"kdr",
 "gmax_kdr",
 "mbaserate_kdr",
 0,
 "i_kdr",
 "g_kdr",
 0,
 "m_kdr",
 "h_kdr",
 0,
 0};
 static Symbol* _na_sym;
 static Symbol* _k_sym;
 static Symbol* _ca_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 14, _prop);
 	/*initialize range parameters*/
 	gmax = 0.08;
 	mbaserate = 0.1;
 	_prop->param = _p;
 	_prop->param_size = 14;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 8, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_na_sym);
 	_ppvar[0]._pval = &prop_ion->param[3]; /* ina */
 	_ppvar[1]._pval = &prop_ion->param[4]; /* _ion_dinadv */
 prop_ion = need_memb(_k_sym);
 	_ppvar[2]._pval = &prop_ion->param[3]; /* ik */
 	_ppvar[3]._pval = &prop_ion->param[4]; /* _ion_dikdv */
 prop_ion = need_memb(_ca_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[4]._pval = &prop_ion->param[2]; /* cao */
 	_ppvar[5]._pval = &prop_ion->param[1]; /* cai */
 	_ppvar[6]._pval = &prop_ion->param[3]; /* ica */
 	_ppvar[7]._pval = &prop_ion->param[4]; /* _ion_dicadv */
 
}
 static void _initlists();
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*f)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _kdr_reg() {
	int _vectorized = 0;
  _initlists();
 	ion_reg("na", -10000.);
 	ion_reg("k", -10000.);
 	ion_reg("ca", -10000.);
 	_na_sym = hoc_lookup("na_ion");
 	_k_sym = hoc_lookup("k_ion");
 	_ca_sym = hoc_lookup("ca_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 0);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
  hoc_register_dparam_size(_mechtype, 8);
 	hoc_register_cvode(_mechtype, _ode_count, 0, 0, 0);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 kdr /cygdrive/c/Neuron_B/Downto1/kdr.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double FARADAY = 96489.0;
 static double R = 8.31441;
 static double *_t_Add[2];
 static double *_t_Mult[2];
static int _reset;
static char *modelname = "Borg-Graham Channel Model";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int _f_mh(double);
static int iassign();
static int mh(double);
static int states();
 static void _n_mh(double);
 
static int  iassign (  ) {
   i = g * ( v - erev ) ;
   ik = i ;
    return 0; }
 
static void _hoc_iassign(void) {
  double _r;
   _r = 1.;
 iassign (  );
 hoc_retpushx(_r);
}
 
static int  states (  ) {
   mh ( _threadargscomma_ v * 1.0 ) ;
   m = m * Mult [ 0 ] + Add [ 0 ] ;
   h = h * Mult [ 1 ] + Add [ 1 ] ;
   
/*VERBATIM*/
	return 0;
  return 0; }
 
static void _hoc_states(void) {
  double _r;
   _r = 1.;
 states (  );
 hoc_retpushx(_r);
}
 static double _mfac_mh, _tmin_mh;
 static void _check_mh();
 static void _check_mh() {
  static int _maktable=1; int _i, _j, _ix = 0;
  double _xi, _tmax;
  static double _sav_dt;
  static double _sav_hbaserate;
  static double _sav_hbasetau;
  static double _sav_hexp;
  static double _sav_hgamma;
  static double _sav_htemp;
  static double _sav_hvalence;
  static double _sav_hvhalf;
  static double _sav_mbaserate;
  static double _sav_mbasetau;
  static double _sav_mexp;
  static double _sav_mgamma;
  static double _sav_mtemp;
  static double _sav_mvalence;
  static double _sav_mvhalf;
  static double _sav_celsius;
  static double _sav_mq10;
  static double _sav_hq10;
  static double _sav_vmin;
  static double _sav_vmax;
  if (!usetable) {return;}
  if (_sav_dt != dt) { _maktable = 1;}
  if (_sav_hbaserate != hbaserate) { _maktable = 1;}
  if (_sav_hbasetau != hbasetau) { _maktable = 1;}
  if (_sav_hexp != hexp) { _maktable = 1;}
  if (_sav_hgamma != hgamma) { _maktable = 1;}
  if (_sav_htemp != htemp) { _maktable = 1;}
  if (_sav_hvalence != hvalence) { _maktable = 1;}
  if (_sav_hvhalf != hvhalf) { _maktable = 1;}
  if (_sav_mbaserate != mbaserate) { _maktable = 1;}
  if (_sav_mbasetau != mbasetau) { _maktable = 1;}
  if (_sav_mexp != mexp) { _maktable = 1;}
  if (_sav_mgamma != mgamma) { _maktable = 1;}
  if (_sav_mtemp != mtemp) { _maktable = 1;}
  if (_sav_mvalence != mvalence) { _maktable = 1;}
  if (_sav_mvhalf != mvhalf) { _maktable = 1;}
  if (_sav_celsius != celsius) { _maktable = 1;}
  if (_sav_mq10 != mq10) { _maktable = 1;}
  if (_sav_hq10 != hq10) { _maktable = 1;}
  if (_sav_vmin != vmin) { _maktable = 1;}
  if (_sav_vmax != vmax) { _maktable = 1;}
  if (_maktable) { double _x, _dx; _maktable=0;
   _tmin_mh =  vmin ;
   _tmax =  vmax ;
   _dx = (_tmax - _tmin_mh)/200.; _mfac_mh = 1./_dx;
   for (_i=0, _x=_tmin_mh; _i < 201; _x += _dx, _i++) {
    _f_mh(_x);
    for (_j = 0; _j < 2; _j++) { _t_Add[_j][_i] = Add[_j];
}    for (_j = 0; _j < 2; _j++) { _t_Mult[_j][_i] = Mult[_j];
}   }
   _sav_dt = dt;
   _sav_hbaserate = hbaserate;
   _sav_hbasetau = hbasetau;
   _sav_hexp = hexp;
   _sav_hgamma = hgamma;
   _sav_htemp = htemp;
   _sav_hvalence = hvalence;
   _sav_hvhalf = hvhalf;
   _sav_mbaserate = mbaserate;
   _sav_mbasetau = mbasetau;
   _sav_mexp = mexp;
   _sav_mgamma = mgamma;
   _sav_mtemp = mtemp;
   _sav_mvalence = mvalence;
   _sav_mvhalf = mvhalf;
   _sav_celsius = celsius;
   _sav_mq10 = mq10;
   _sav_hq10 = hq10;
   _sav_vmin = vmin;
   _sav_vmax = vmax;
  }
 }

 static int mh(double _lv){ _check_mh();
 _n_mh(_lv);
 return 0;
 }

 static void _n_mh(double _lv){ int _i, _j;
 double _xi, _theta;
 if (!usetable) {
 _f_mh(_lv); return; 
}
 _xi = _mfac_mh * (_lv - _tmin_mh);
 _i = (int) _xi;
 if (_xi <= 0.) {
 for (_j = 0; _j < 2; _j++) { Add[_j] = _t_Add[_j][0];
} for (_j = 0; _j < 2; _j++) { Mult[_j] = _t_Mult[_j][0];
} return; }
 if (_i >= 200) {
 for (_j = 0; _j < 2; _j++) { Add[_j] = _t_Add[_j][200];
} for (_j = 0; _j < 2; _j++) { Mult[_j] = _t_Mult[_j][200];
} return; }
 _theta = _xi - (double)_i;
 for (_j = 0; _j < 2; _j++) {double *_t = _t_Add[_j]; Add[_j] = _t[_i] + _theta*(_t[_i+1] - _t[_i]);}
 for (_j = 0; _j < 2; _j++) {double *_t = _t_Mult[_j]; Mult[_j] = _t[_i] + _theta*(_t[_i+1] - _t[_i]);}
 }

 
static int  _f_mh (  double _lv ) {
   double _la , _lb , _lj , _lmqq10 , _lhqq10 ;
 _lmqq10 = pow( mq10 , ( ( celsius - mtemp ) / 10. ) ) ;
   _lhqq10 = pow( hq10 , ( ( celsius - htemp ) / 10. ) ) ;
   {int  _lj ;for ( _lj = 0 ; _lj <= 1 ; _lj ++ ) {
     _la = alpha ( _threadargscomma_ _lv , ((double) _lj ) ) ;
     _lb = beta ( _threadargscomma_ _lv , ((double) _lj ) ) ;
     Inf [ _lj ] = _la / ( _la + _lb ) ;
     
/*VERBATIM*/
		switch (_lj) {
			case 0:
		/* Make sure Tau is not less than the base Tau */
				if ((Tau[_lj] = 1 / (_la + _lb)) < mbasetau) {
					Tau[_lj] = mbasetau;
				}
				Tau[_lj] = Tau[_lj] / _lmqq10;
				break;
			case 1:
				if ((Tau[_lj] = 1 / (_la + _lb)) < hbasetau) {
					Tau[_lj] = hbasetau;
				}
				Tau[_lj] = Tau[_lj] / _lhqq10;
				if (hexp==0) {
					Tau[_lj] = 1.; }
				break;
		}

 Mult [ _lj ] = exp ( - dt / Tau [ _lj ] ) ;
     Add [ _lj ] = Inf [ _lj ] * ( 1. - exp ( - dt / Tau [ _lj ] ) ) ;
     } }
    return 0; }
 
static void _hoc_mh(void) {
  double _r;
    _r = 1.;
 mh (  *getarg(1) );
 hoc_retpushx(_r);
}
 
double alpha (  double _lv , double _lj ) {
   double _lalpha;
 if ( _lj  == 1.0 ) {
     if ( hexp  == 0.0 ) {
       _lalpha = 1.0 ;
       }
     else {
       _lalpha = hbaserate * exp ( ( _lv - hvhalf ) * hvalence * hgamma * FRT ( _threadargscomma_ htemp ) ) ;
       }
     }
   else {
     _lalpha = mbaserate * exp ( ( _lv - mvhalf ) * mvalence * mgamma * FRT ( _threadargscomma_ mtemp ) ) ;
     }
   
return _lalpha;
 }
 
static void _hoc_alpha(void) {
  double _r;
   _r =  alpha (  *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
double beta (  double _lv , double _lj ) {
   double _lbeta;
 if ( _lj  == 1.0 ) {
     if ( hexp  == 0.0 ) {
       _lbeta = 1.0 ;
       }
     else {
       _lbeta = hbaserate * exp ( ( - _lv + hvhalf ) * hvalence * ( 1.0 - hgamma ) * FRT ( _threadargscomma_ htemp ) ) ;
       }
     }
   else {
     _lbeta = mbaserate * exp ( ( - _lv + mvhalf ) * mvalence * ( 1.0 - mgamma ) * FRT ( _threadargscomma_ mtemp ) ) ;
     }
   
return _lbeta;
 }
 
static void _hoc_beta(void) {
  double _r;
   _r =  beta (  *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
double FRT (  double _ltemperature ) {
   double _lFRT;
 _lFRT = FARADAY * 0.001 / R / ( _ltemperature + 273.15 ) ;
   
return _lFRT;
 }
 
static void _hoc_FRT(void) {
  double _r;
   _r =  FRT (  *getarg(1) );
 hoc_retpushx(_r);
}
 
double ghkca (  double _lv ) {
   double _lghkca;
 double _lnu , _lefun ;
 _lnu = _lv * 2.0 * FRT ( _threadargscomma_ celsius ) ;
   if ( fabs ( _lnu ) < 1.e-6 ) {
     _lefun = 1. - _lnu / 2. ;
     }
   else {
     _lefun = _lnu / ( exp ( _lnu ) - 1. ) ;
     }
   _lghkca = - FARADAY * 2.e-3 * _lefun * ( cao - cai * exp ( _lnu ) ) ;
   
return _lghkca;
 }
 
static void _hoc_ghkca(void) {
  double _r;
   _r =  ghkca (  *getarg(1) );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ hoc_execerror("kdr", "cannot be used with CVODE"); return 0;}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_na_sym, _ppvar, 0, 3);
   nrn_update_ion_pointer(_na_sym, _ppvar, 1, 4);
   nrn_update_ion_pointer(_k_sym, _ppvar, 2, 3);
   nrn_update_ion_pointer(_k_sym, _ppvar, 3, 4);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 4, 2);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 5, 1);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 6, 3);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 7, 4);
 }

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  h = h0;
  m = m0;
 {
   mh ( _threadargscomma_ v ) ;
   if ( usetable  == 0.0 ) {
     m = Inf [ 0 ] ;
     h = Inf [ 1 ] ;
     }
   else {
     m = Add [ 0 ] / ( 1.0 - Mult [ 0 ] ) ;
     h = Add [ 1 ] / ( 1.0 - Mult [ 1 ] ) ;
     }
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
  cao = _ion_cao;
  cai = _ion_cai;
 initmodel();
   }}

static double _nrn_current(double _v){double _current=0.;v=_v;{ {
   double _lhexp_val , _lindex , _lmexp_val ;
 _lhexp_val = 1.0 ;
   _lmexp_val = 1.0 ;
   if ( hexp > 0.0 ) {
     {int  _lindex ;for ( _lindex = 1 ; _lindex <= ((int) hexp ) ; _lindex ++ ) {
       _lhexp_val = h * _lhexp_val ;
       } }
     }
   if ( mexp > 0.0 ) {
     {int  _lindex ;for ( _lindex = 1 ; _lindex <= ((int) mexp ) ; _lindex ++ ) {
       _lmexp_val = m * _lmexp_val ;
       } }
     }
   g = gmax * _lmexp_val * _lhexp_val ;
   iassign ( _threadargs_ ) ;
   }
 _current += ina;
 _current += ik;
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
  cao = _ion_cao;
  cai = _ion_cai;
 _g = _nrn_current(_v + .001);
 	{ double _dica;
 double _dik;
 double _dina;
  _dina = ina;
  _dik = ik;
  _dica = ica;
 _rhs = _nrn_current(_v);
  _ion_dinadv += (_dina - ina)/.001 ;
  _ion_dikdv += (_dik - ik)/.001 ;
  _ion_dicadv += (_dica - ica)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ina += ina ;
  _ion_ik += ik ;
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
  cao = _ion_cao;
  cai = _ion_cai;
 { {
 for (; t < _break; t += dt) {
 error =  states();
 if(error){fprintf(stderr,"at line 162 in file kdr.mod:\n\n"); nrn_complain(_p); abort_run(error);}
 
}}
 t = _save;
 }   }}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
  for (_i=0; _i < 2; _i++) {  _t_Add[_i] = makevector(201*sizeof(double)); }
  for (_i=0; _i < 2; _i++) {  _t_Mult[_i] = makevector(201*sizeof(double)); }
_first = 0;
}
