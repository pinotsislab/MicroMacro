#include <stdio.h>
#include "hocdec.h"
#define IMPORT extern __declspec(dllimport)
IMPORT int nrnmpi_myid, nrn_nobanner_;

extern void _ar_reg();
extern void _ca_reg();
extern void _cad_reg();
extern void _cat_reg();
extern void _catp_reg();
extern void _dipole_reg();
extern void _dpresyn_reg();
extern void _gnetstim_reg();
extern void _h_reg();
extern void _kca_reg();
extern void _kdr_reg();
extern void _km_reg();
extern void _na_reg();
extern void _pp_dipole_reg();
extern void _precall_reg();
extern void _seed_reg();
extern void _tchannel_reg();

modl_reg(){
	//nrn_mswindll_stdio(stdin, stdout, stderr);
    if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
	fprintf(stderr, "Additional mechanisms from files\n");

fprintf(stderr," ar.mod");
fprintf(stderr," ca.mod");
fprintf(stderr," cad.mod");
fprintf(stderr," cat.mod");
fprintf(stderr," catp.mod");
fprintf(stderr," dipole.mod");
fprintf(stderr," dpresyn.mod");
fprintf(stderr," gnetstim.mod");
fprintf(stderr," h.mod");
fprintf(stderr," kca.mod");
fprintf(stderr," kdr.mod");
fprintf(stderr," km.mod");
fprintf(stderr," na.mod");
fprintf(stderr," pp_dipole.mod");
fprintf(stderr," precall.mod");
fprintf(stderr," seed.mod");
fprintf(stderr," tchannel.mod");
fprintf(stderr, "\n");
    }
_ar_reg();
_ca_reg();
_cad_reg();
_cat_reg();
_catp_reg();
_dipole_reg();
_dpresyn_reg();
_gnetstim_reg();
_h_reg();
_kca_reg();
_kdr_reg();
_km_reg();
_na_reg();
_pp_dipole_reg();
_precall_reg();
_seed_reg();
_tchannel_reg();
}
