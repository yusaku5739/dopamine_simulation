from neuron import h, gui
import matplotlib.pyplot as plt
import numpy as np
import os
from mpi4py import MPI
from tqdm import tqdm

from dopamine_neuron import create_dopapmie_neuron

# HOCファイルを読み込む
h.load_file("nrngui.hoc")


if __name__=="__main__":

    n = 100
    neuron_types = ["conventional", "atypical"]
    rng = np.random.default_rng(seed=42)

    cells = [create_dopapmie_neuron(neuron_types[i%2], vinit=rng.uniform(-80, -30)) for i in range(n)]
    #cells = [create_dopapmie_neuron(neuron_types[i%2], vinit=-50) for i in range(n)]

    stims = []
    for i in range(n):
        if i<n//2:
            stims.append(h.IClamp(cells[i].nrn.soma(0.5)))
            stims[-1].delay = 4000  # ms
            stims[-1].dur = 2000  # ms
            stims[-1].amp = -0.1

    t_vec = h.Vector()
    t_vec.record(h._ref_t)

    h.dt = 0.1
    duration = 10000

    cv = h.CVode()
    h.finitialize()
    cv.active(1)  # 可変ステップを使用
    
    with tqdm(total=duration) as pbar:
        while h.t < duration:
            h.fadvance()
            pbar.update(1)

    spikes = []
    total_da = np.zeros((len(t_vec)))
    for i in range(n):
        spike = cells[i].srec.as_numpy()
        spikes.append(spike)
        total_da += cells[i].da.as_numpy()
    
    fig, ax = plt.subplots(2, 1, figsize=(12, 12))
    
    ax[0].eventplot(spikes, colors=[[1.0, 0, 0]])
    ax[1].plot(t_vec, total_da)
    plt.savefig(f"{__file__}.png")
    