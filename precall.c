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
#define num _p[0]
#define nsyn _p[1]
#define link _p[2]
#define spk _p[3]
#define spk_internal _p[4]
#define maxsyn _p[5]
#define _g _p[6]
#define _nd_area  *_ppvar[0]._pval
 
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
 /* declaration of user functions */
 static double _hoc_code();
 static double _hoc_check();
 static double _hoc_clean();
 static double _hoc_delay();
 static double _hoc_newspike();
 static double _hoc_pp();
 static double _hoc_prq();
 static double _hoc_post();
 static double _hoc_pre();
 static double _hoc_preinit();
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 extern Prop* nrn_point_prop_;
 static int _pointtype;
 static void* _hoc_create_pnt(_ho) Object* _ho; { void* create_point_process();
 return create_point_process(_pointtype, _ho);
}
 static void _hoc_destroy_pnt();
 static double _hoc_loc_pnt(_vptr) void* _vptr; {double loc_point_process();
 return loc_point_process(_pointtype, _vptr);
}
 static double _hoc_has_loc(_vptr) void* _vptr; {double has_loc_point();
 return has_loc_point(_vptr);
}
 static double _hoc_get_loc_pnt(_vptr)void* _vptr; {
 double get_loc_point_process(); return (get_loc_point_process(_vptr));
}
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _p = _prop->param; _ppvar = _prop->dparam;
 }
 static void _hoc_setdata(void* _vptr) { Prop* _prop;
 _prop = ((Point_process*)_vptr)->_prop;
   _setdata(_prop);
 }
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 0,0
};
 static Member_func _member_func[] = {
 "loc", _hoc_loc_pnt,
 "has_loc", _hoc_has_loc,
 "get_loc", _hoc_get_loc_pnt,
 "code", _hoc_code,
 "check", _hoc_check,
 "clean", _hoc_clean,
 "delay", _hoc_delay,
 "newspike", _hoc_newspike,
 "pp", _hoc_pp,
 "prq", _hoc_prq,
 "post", _hoc_post,
 "pre", _hoc_pre,
 "preinit", _hoc_preinit,
 0, 0
};
#define code code_PRESYN
#define check check_PRESYN
#define delay delay_PRESYN
#define post post_PRESYN
#define pre pre_PRESYN
 extern double code( );
 extern double check( );
 extern double delay( );
 extern double post( );
 extern double pre( );
 /* declare global and static user variables */
#define thresh thresh_PRESYN
 double thresh = -20;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 0,0
};
 static double delta_t = 1;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "thresh_PRESYN", &thresh_PRESYN,
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
 static void _hoc_destroy_pnt(_vptr) void* _vptr; {
   destroy_point_process(_vptr);
}
 
static int _ode_count(int);
 static void _destructor(Prop*);
 static void _constructor(Prop*);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "6.2.0",
"PRESYN",
 "num",
 "nsyn",
 "link",
 0,
 "spk",
 "spk_internal",
 "maxsyn",
 0,
 0,
 0};
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
  if (nrn_point_prop_) {
	_prop->_alloc_seq = nrn_point_prop_->_alloc_seq;
	_p = nrn_point_prop_->param;
	_ppvar = nrn_point_prop_->dparam;
 }else{
 	_p = nrn_prop_data_alloc(_mechtype, 7, _prop);
 	/*initialize range parameters*/
 	num = -1;
 	nsyn = 0;
 	link = 0;
  }
 	_prop->param = _p;
 	_prop->param_size = 7;
  if (!nrn_point_prop_) {
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 2, _prop);
  }
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 if (!nrn_point_prop_) {_constructor(_prop);}
 
}
 static void _initlists();
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*f)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _precall_reg() {
	int _vectorized = 0;
  _initlists();
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init,
	 hoc_nrnpointerindex, 0,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func);
 	register_destructor(_destructor);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
  hoc_register_dparam_size(_mechtype, 2);
 	hoc_register_cvode(_mechtype, _ode_count, 0, 0, 0);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 PRESYN /cygdrive/c/Neuron_B/Downto1/precall.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int clean();
static int newspike();
static int pp();
static int prq(double);
static int preinit();
 
/*VERBATIM*/

#define PSTCAST ((SynS *)((unsigned long) lpst))
#define QUECAST ((QueU *)((unsigned long) queu))
#define PRECAST ((PreL *)((unsigned long) link))
#define QPRCAST ((QptR *)((unsigned long) qptr))

#define PREINC  50.  /* size increment for growing the presyn array */
#define POSTINC 5.   /* size increment for growing the postsyn array */

typedef struct QueU { /* postsynaptic queue */
  double time;  /* records spike time + delay */
  short index;  /* records index of associated SynS struct */
} QueU;

/* holds all the info for accessing the queu and its tail */
typedef struct QptR {
  struct QueU *qq;     /* will point to the queu */
  double *nspk; /* will point to newspk */
  double *head; /* will point to begsyn */
  double *qln;  /* points to qlen */
  double dead;  /* Cdur + Deadtime */
  double qterm;  /* the last time put on this queue */
  int cpost;  /* user code for info about postsyn cell */
} QptR;

typedef struct SynS { /* postsynaptic structure */
  /* this stuff used presynaptically */
  short index;  /* index of this item */
  double del;   /* param: individualized delay set by user */
  double spkt;  /* state: time when next spike can begin */
  struct QptR *qpt;   /* indirection to get at the queu */

  /* for allowing mult spikes to add up */
  short chainlen;
  short chainptr;

  /* user codes */
  int ucode;  /* user code for user convenience, an arbitrary index */
  /* this stuff used postsynaptically */
  double pgm;   /* percent of gmax - set by user */
  double Rcurr; /* holds current value of R (release status), internal */
  double last;  /* time last syn will end, internal */
  int *pcpre;   /* pointer to access the presyn code */
  struct SynS **back;  /* pointer to presyn pointer to this entry */
} SynS;

/* holds all the info for accessing presyn list */
typedef struct PreL {
  struct SynS **plst;        /* will point to post for postsyn nrn*/
  double *nnpre;     /* number of pointers currently there */
  double *mxpre;     /* number permitted before realloc required */
  double link2;       /* a copy of the link information to confirm correct hook up */
  int cpre;   /* user code for info about presyn cell */
} PreL;

 
static int  preinit (  ) {
    return 0; }
 
static double _hoc_preinit(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
 _r = 1.;
 preinit (  );
 return(_r);
}
 
static int  newspike (  ) {
   
/*VERBATIM*/
{ 
  int ii, jj, nspk, qend, head, ind, swapi;
  double time, swapt;
  SynS *psyn;		/* pointer to the presynaptic structure */
  QptR *qpr;
  QueU *qp;		/* pointer to the head position in postsyn queu */

  for (ii=0; ii<nsyn;ii++) { 

    /* psyn is the pointer back to the postsyn info array (struct SynS) */
    if ((psyn = PRECAST->plst[ii])==(SynS *)NULL ||     /* skip empties */
	(t < psyn->spkt && psyn->chainlen == 1)) {   /* skip if still on last one */
      continue; }
    /* are we chaining synapses? : this means that we will treat additional spks as */
    /* if they were coming from another synapse */
    if (psyn->chainlen > 1) {
      psyn->chainptr++;  /* augment the pointer */
      if (psyn->chainptr >= psyn->chainlen) { /* have run out of room */
	if (t < psyn->spkt) {  /* can't reset yet so just drop this spk */
	  continue;
	} else {               /* the whole chain is completely done so can reset */
	  psyn->chainptr = 0; }
      }
      ind = psyn->index + psyn->chainptr; /* add index of next one on chain */
    } else {
      ind = psyn->index;
    }

    /* qpr = the post-syn queu pointer */
    qpr = psyn->qpt;  
    /* qp = pointer to postsyn queu */
    qp = qpr->qq;
    nspk = (int)(*(qpr->nspk));
    time = t + psyn->del;
    psyn->spkt = t + qpr->dead; /* when it will all end */

    /* basic queu code taken from queu.inc (viz.) but now must make sure */
    /* that we don't go backwards in time (different delays) */
    /* should have been cleared if we are to write here */
    if (qp[nspk].time != 1e20) { //  -- REMOVED THIS ERROR!!
      printf("WARNING: QUEUE ANOMALY: %x %g %g ",qpr->qq,*(qpr->nspk),*(qpr->qln));
      // hoc_execerror("Error: queue full.\n",0);
    }
    if (qpr->qterm < time) {	/* queu marching forward in time: AOK */
	/* push the two queu items: a time and an index */
	(qp[nspk]).time = time; /* delay */
	(qp[nspk]).index = ind; /* tell postsyn which presyn spiked */
	qpr->qterm = time;	/* keep track of largest time put on */
    } else {			/* move backward to insert in right place */
	/* actually a heap rather than a queue since maintains order */
	qend = (int)(*(qpr->qln)) - 1; /* max ind for queu */
	head = (int)(*(qpr->head)) - 1; /* one in front of the head */
	if (head == -1) { head = qend; } /* wrap around */
	/* search backward */
	for (jj=((nspk==0)?qend:nspk-1);
	     time < qp[jj].time && jj != head;
	     jj=((jj==0)?qend:jj-1)); /* skip over from end */
	if (jj==nspk) { 
	  printf("%g %d %d ",qpr->qterm,ii,jj);
	  hoc_execerror("ERROR: newspike search failed.\n",0); }
	/* move things forward */
	for (jj=((jj==qend)?0:jj+1); /* start one up */
	     jj != nspk;	/* till back where we were */
	     jj=((jj==qend)?0:jj+1)) {
	  swapt = qp[jj].time;	/* store temporarily */
	  swapi = qp[jj].index;
	  qp[jj].time = time;	/* put in the new one */
	  qp[jj].index = ind;
	  time = swapt;		/* swap them */
	  ind = swapi;
	}
	qp[jj].time = time;
	qp[jj].index = ind;
      }

      /* move the tail forward and reset if reached the end */
      (*(qpr->nspk))++;
      if ((*(qpr->nspk)) == *(qpr->qln)) { (*(qpr->nspk)) = 0.; 
        printf("Cycling around for %x\n",qpr->qq);}

  }
  }
  return 0; }
 
static double _hoc_newspike(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
 _r = 1.;
 newspike (  );
 return(_r);
}
 
static int  clean (  ) {
   
/*VERBATIM*/
{ 
    int ii,jj,newn;
    SynS** pl;
    pl = PRECAST->plst;

    for(ii=0,jj=0,newn=nsyn; ii<nsyn; ii++,jj++) {
      while (pl[ii] == (SynS *)NULL && ii<nsyn) {
	ii++; newn--; 
      }
      if (ii != jj && ii<nsyn) {
	pl[jj] = pl[ii];
	pl[jj]->back = &(pl[jj]);
      }
    }
    nsyn = newn;
  }
  return 0; }
 
static double _hoc_clean(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
 _r = 1.;
 clean (  );
 return(_r);
}
 
double check (  ) {
   double _lcheck;
 
/*VERBATIM*/
{ 
    int ii;
    for (ii=0,_lcheck=0; ii<nsyn && _lcheck!=-1.; ii++) {
      if (PRECAST->plst[ii] != (SynS *)NULL) {
	_lcheck++;  /* count the active pointers */
	if ((&(PRECAST->plst[ii])) != (PRECAST->plst[ii]->back)) {
	  printf("****************************************************************\n");
	  printf("ERROR:: %2d: Index:%3d,C%09d,Pr%09d,Po%09d, Delay:%6g (%x->%x->%x)\n",
		 ii,
		 PRECAST->plst[(int)ii]->index,
		 PRECAST->plst[(int)ii]->ucode,
		 PRECAST->cpre,
		 PRECAST->plst[(int)ii]->qpt->cpost,
		 PRECAST->plst[(int)ii]->del,
		 &(PRECAST->plst[(int)ii]),
		 PRECAST->plst[(int)ii],
		 (PRECAST->plst[(int)ii]->back));
	  printf("****************************************************************\n");
	  _lcheck = -1.0;
	}
      }
    } 
  }
 
return _lcheck;
 }
 
static double _hoc_check(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
 _r =  check (  );
 return(_r);
}
 
double code (  ) {
   double _lcode;
 
/*VERBATIM*/
{ int ii;
    if (ifarg(1)) {
      ii = (int)*getarg(1);
      if (ii < 0) { ii = nsyn+ii; }
      if (ii >= nsyn || ii < 0) {hoc_execerror("array index out of bounds", 0);}
      _lcode = ((PRECAST->plst[ii] == (SynS *)NULL)?-2:PRECAST->plst[ii]->ucode);
    } else {
      for (ii=0;ii<nsyn;ii++) {
	if (PRECAST->plst[ii] == (SynS *)NULL) {
	  printf("%d EMPTY.\n",ii);
	} else { 
	  printf("%d,%09d  ",ii,PRECAST->plst[ii]->ucode);
        }
      }
      _lcode = 1.0;
    }
  } 
 
return _lcode;
 }
 
static double _hoc_code(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
 _r =  code (  );
 return(_r);
}
 
double delay (  ) {
   double _ldelay;
 
/*VERBATIM*/
{ int ii;
    if (ifarg(1)) {
      ii = (int)*getarg(1);
      if (ii < 0) { ii = nsyn+ii; }
      if (ii >= nsyn || ii < 0) {hoc_execerror("array index out of bounds", 0);}
      _ldelay = ((PRECAST->plst[ii] == (SynS *)NULL)?-2:PRECAST->plst[ii]->del);
    } else {
      for (ii=0;ii<nsyn;ii++) {
	if (PRECAST->plst[ii] == (SynS *)NULL) {
	  printf("%d EMPTY.\n",ii);
	} else { 
	  printf("%d,%g  ",ii,PRECAST->plst[ii]->del);
        }
      }
      _ldelay = 1.0;
    }
  } 
 
return _ldelay;
 }
 
static double _hoc_delay(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
 _r =  delay (  );
 return(_r);
}
 
double pre (  ) {
   double _lpre;
 
/*VERBATIM*/
{
    if (ifarg(2)) { PRECAST->cpre = (int)*getarg(2); }
    _lpre = PRECAST->cpre;
  } 
 
return _lpre;
 }
 
static double _hoc_pre(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
 _r =  pre (  );
 return(_r);
}
 
double post (  ) {
   double _lpost;
 
/*VERBATIM*/
{ int xx,ii;
    xx = -2;
    if (ifarg(1)) { xx = (int)*getarg(1); }
    if (xx >= 0) {
      if (xx >= nsyn) {hoc_execerror("array index out of bounds", 0);}
      _lpost = ((PRECAST->plst[xx] == (SynS *)NULL)?-2:PRECAST->plst[xx]->qpt->cpost);
    } else {
      for (ii=0;ii<nsyn;ii++) {
	if (PRECAST->plst[ii] == (SynS *)NULL) {
	  printf("%2d EMPTY.\n",ii);
	} else { 
	  printf("%1d (%1d) Del:%-4g Cd:%09d Pre:%09d Post:%09d\n",
		 ii,
		 PRECAST->plst[ii]->index,
		 PRECAST->plst[ii]->del,
		 PRECAST->plst[ii]->ucode,
		 PRECAST->cpre,
		 PRECAST->plst[ii]->qpt->cpost);
	  if (xx == -1 || (&(PRECAST->plst[ii])) != (PRECAST->plst[ii]->back)) {
	    printf("\t\t%s: %x -> %x\n",
		   (((&(PRECAST->plst[ii]))==(PRECAST->plst[ii]->back))?
		    "OK":"POINTER MISMATCH"),
		   &(PRECAST->plst[ii]),
		   PRECAST->plst[ii]);
	  }
	}
      }
      _lpost = 1.0;
    }
  } 
 
return _lpost;
 }
 
static double _hoc_post(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
 _r =  post (  );
 return(_r);
}
 
static int  prq (  double _lx ) {
   
/*VERBATIM*/
{ int ii;
    SynS *psyn;		
    QptR *qpr;
    psyn = PRECAST->plst[(int)_lx];
    qpr = psyn->qpt;  
    printf("%x %g %g\n",qpr->qq,*(qpr->nspk),*(qpr->qln));
    for (ii=0;ii<*(qpr->qln);ii++) {
      printf("%8g%8d\n",
	     ((qpr->qq)[ii]).time,
	     ((qpr->qq)[ii]).index);
   }
  } 
  return 0; }
 
static double _hoc_prq(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
 _r = 1.;
 prq (  *getarg(1) );
 return(_r);
}
 
static int  pp (  ) {
   if ( v > thresh ) {
     if ( spk_internal  == 0.0 ) {
       newspike ( _threadargs_ ) ;
       spk_internal = 1.0 ;
       spk = 1.0 ;
       
/*VERBATIM*/
      { extern double hoc_call_func();
      char func[8] = "precall";
      Symbol* s = hoc_lookup(func);
      if (s && num>=0) {
        hoc_pushx(num);
        hoc_call_func(s, 1);
      }
      }
 }
     }
   else {
     spk_internal = 0.0 ;
     spk = 0.0 ;
     }
    return 0; }
 
static double _hoc_pp(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
 _r = 1.;
 pp (  );
 return(_r);
}
 
static int _ode_count(int _type){ hoc_execerror("PRESYN", "cannot be used with CVODE"); return 0;}
 
static void _constructor(Prop* _prop) {
	_p = _prop->param; _ppvar = _prop->dparam;
{
 {
   
/*VERBATIM*/
{
    /* link allows postsyn cell to manipulate presyn list */
    link = (double)((unsigned long)hoc_Ecalloc(1, sizeof(PreL))); hoc_malchk();
    PRECAST->link2  = link;  /* this can be queried to protect against error */
    PRECAST->nnpre = &nsyn;
    PRECAST->mxpre = &maxsyn;
    nsyn = 0.;
    maxsyn = 0.;
    if (ifarg(2)) { 
      PRECAST->cpre = (int)*getarg(2);
    } else { PRECAST->cpre = -1; }
 } 
 }
 
}
}
 
static void _destructor(Prop* _prop) {
	_p = _prop->param; _ppvar = _prop->dparam;
{
 {
   
/*VERBATIM*/
{ 
      nsyn = maxsyn = 0;
      free(PRECAST);
      link = 0;
  }
 }
 
}
}

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
 {
   spk = 0.0 ;
   spk_internal = 0.0 ;
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
 initmodel();
}}

static double _nrn_current(double _v){double _current=0.;v=_v;{
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
 { {
 for (; t < _break; t += dt) {
 error =  pp();
 if(error){fprintf(stderr,"at line 34 in file precall.mod:\n  SOLVE pp\n"); nrn_complain(_p); abort_run(error);}
 
}}
 t = _save;
 } {
   }
}}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
_first = 0;
}
