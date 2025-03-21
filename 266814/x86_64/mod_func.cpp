#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;
#if defined(__cplusplus)
extern "C" {
#endif

extern void _CaLHH_reg(void);
extern void _CaN_reg(void);
extern void _HCN_reg(void);
extern void _NaMarkov_reg(void);
extern void _NaMarkovFONLY_reg(void);
extern void _blockhh3_reg(void);
extern void _cabalshell_stores_reg(void);
extern void _cicr_reg(void);
extern void _dopamine_release_reg(void);
extern void _nabalan_reg(void);
extern void _newkca_reg(void);
extern void _newleak_reg(void);
extern void _nmda_reg(void);
extern void _nmdasyn_reg(void);
extern void _typem_reg(void);

void modl_reg() {
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");
    fprintf(stderr, " \"CaLHH.mod\"");
    fprintf(stderr, " \"CaN.mod\"");
    fprintf(stderr, " \"HCN.mod\"");
    fprintf(stderr, " \"NaMarkov.mod\"");
    fprintf(stderr, " \"NaMarkovFONLY.mod\"");
    fprintf(stderr, " \"blockhh3.mod\"");
    fprintf(stderr, " \"cabalshell_stores.mod\"");
    fprintf(stderr, " \"cicr.mod\"");
    fprintf(stderr, " \"dopamine_release.mod\"");
    fprintf(stderr, " \"nabalan.mod\"");
    fprintf(stderr, " \"newkca.mod\"");
    fprintf(stderr, " \"newleak.mod\"");
    fprintf(stderr, " \"nmda.mod\"");
    fprintf(stderr, " \"nmdasyn.mod\"");
    fprintf(stderr, " \"typem.mod\"");
    fprintf(stderr, "\n");
  }
  _CaLHH_reg();
  _CaN_reg();
  _HCN_reg();
  _NaMarkov_reg();
  _NaMarkovFONLY_reg();
  _blockhh3_reg();
  _cabalshell_stores_reg();
  _cicr_reg();
  _dopamine_release_reg();
  _nabalan_reg();
  _newkca_reg();
  _newleak_reg();
  _nmda_reg();
  _nmdasyn_reg();
  _typem_reg();
}

#if defined(__cplusplus)
}
#endif
