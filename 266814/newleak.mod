TITLE Leak current including GABA_A receptor current
 

UNITS {
        (pA) = (picoamp)
        (molar) = (1/liter)
	(mV) =	(millivolt)
        (S)  =  (siemens)
	(mA) =	(milliamp)
	(mM) =	(millimolar)
         F = (faraday) (coulomb)
         R = (mole k)  (mV-coulomb/degC)
}


INDEPENDENT {v FROM -100 TO 50 WITH 50 (mV)}

NEURON {
	SUFFIX leak
        NONSPECIFIC_CURRENT iampa
	USEION ca WRITE ica
	USEION na READ nai,ena  WRITE ina
	USEION k  WRITE ik
	USEION cl WRITE icl VALENCE 1
	RANGE  gcabar,ileak,ina,ica,ik,gnabar,gkbar,nai,ggabaa, iampa
 
}

PARAMETER {
        dt      (ms)
        ena     (mV)
        nai     (mM)
        celsius = 35      (degC)
        gkbar   = 5.5e-6 (S/cm2)
        gnabar  = 2.375e-6  (S/cm2)
        gcabar  = 0.136e-6  (S/cm2)
        ggabaa  = 0.0e-6  (S/cm2)
        gampa = 0.0e-6 (S/cm2)
        eampa = 0 (mV)
        eca =   120 (mV)
        ecl =  -70  (mV)
        ek  =  -90.0 (mV)
        nao =   145 (mM)
        
}

ASSIGNED { 
           ica	  (mA/cm2)
           ina	  (mA/cm2)
           ik	  (mA/cm2)
           icl	  (mA/cm2)
           iampa  (mA/cm2)
           ileak  (mA/cm2)
}


BREAKPOINT {
        ena = 50
	ica = gcabar*(v-eca)
	ina = gnabar*(v-ena)
	icl = ggabaa*(v-ecl)
	ik = gkbar*(v-ek)
        iampa = gampa*(v-eampa)
        ileak= ica + ina + ik + icl + iampa
}
