TITLE Dopamine release and uptake mechanism

NEURON {
    POINT_PROCESS DopamineRelease
    RANGE DA_max, Vmax, Km    : Parameters for release and uptake
    RANGE DA                  : Dopamine concentration
    RANGE release_trigger     : Spike detection threshold
}

UNITS {
    (uM)    = (micro)    : micromolar
}

PARAMETER {
    DA_max = 0.1 (uM)        : Maximum amount of DA released per spike
    Vmax = 0.004 (uM/ms)     : Maximum rate of uptake
    Km = 0.2 (uM)           : Affinity of transporter
    release_trigger = 0 (mV) : Threshold for detecting spikes
}

STATE {
    DA (uM)  : Dopamine concentration
}

INITIAL {
    DA = 0   : Initial dopamine concentration
}

BREAKPOINT {
    SOLVE state METHOD cnexp
}

DERIVATIVE state {
    : Uptake term (Michaelis-Menten kinetics)
    DA' = -Vmax * DA / (Km + DA)
}

NET_RECEIVE (weight) {
    if (flag == 0) {  : Spike detected
        : Release term (instantaneous release of DA_max)
        DA = DA + DA_max
    }
}