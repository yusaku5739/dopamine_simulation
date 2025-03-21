from neuron import h, gui
import matplotlib.pyplot as plt
import numpy as np
import os
from mpi4py import MPI

VERBOSE=True

# HOCファイルを読み込む
h.load_file("nrngui.hoc")
h.load_file("template_simple.hoc")

class DopaCell:
    """
    ドーパミンニューロンモデルクラス - 論文のdopaクラスに相当
    """
    def __init__(self, i=0, args=[1, 2], parms=None, vinit=-50):
        h.pop_section()  # セクションスタックのオーバーフロー防止
        
        # パラメータの設定
        self.p1 = args[0]
        self.p2 = args[1]
        self.internal = parms.copy() if parms else {}
        
        # SIMPLE細胞テンプレートから細胞を作成
        self.nrn = h.SIMPLE()
        self.dt = 0.05  # 20kHz
        
        # 追加パラメータの設定
        if len(args) > 3:
            if args[2] in self.internal:
                exec(f"self.internal['{args[2]}'] = {args[3]}")
            if args[2] == 'gnmda':
                for s in self.nrn.all:
                    s.insert('nmda')
                    s.gnmdabar_nmda = self.internal['gnmda']
                    s.cMg_nmda = self.internal['cmg']
                    s.cafrac_nmda = parms['cafrac']
        
        # init_cell_depblockからの初期化
        from def_init_cell_depblock import init
        init(self.nrn, self.internal)
        
        # スパイク検出のためのNetCon
        self.srec = h.Vector()  # スパイク時間
        self.ntc = h.NetCon(self.nrn.soma(0.5)._ref_v, None, sec=self.nrn.soma)
        self.ntc.threshold = -20
        self.ntc.record(self.srec)

        self.da = h.Vector()
        self.da_release = h.DopamineRelease(self.nrn.soma(0.5))
        self.da_ntc = h.NetCon(self.nrn.soma(0.5)._ref_v, self.da_release, -20, 0, 1)
        self.da.record(self.da_release._ref_DA)
        
        # 細胞の追加プロパティの設定
        print(parms["size"])
        for s in self.nrn.somatic:
            s.L = parms['size']
            s.dist_NaMark = parms['slow']
            s.v = vinit
            s.cai = 1e-9
            s.hshift_NaMark = self.internal['na_hshift']
            s.nslope_hhb = self.internal['nslope']
            s.nshift_hhb = self.internal['nshift']
            
            # その他のチャネルパラメータの設定
            if h.ismembrane('kca', sec=s):
                s.tausk_kca = 5
                s.km_kca *= 1.0
                
            if h.ismembrane('calhh', sec=s):
                s.gcalbar_calhh *= 1
                s.mhalf_calhh = -30
                s.mslope_calhh = 5.0
                s.pf_calhh = 0.6
                
            if h.ismembrane('canchan'):
                s.gcanbar_canchan = 50e-6

            if h.ismembrane("hcn", sec=s):
                s.scale_hcn = 3.0
                s.mhalf_hcn = -75.0
                
            if h.ismembrane('cabalstore', sec=s):
                for seg in s:
                    seg.TotalBuffer_cabalstore = 0.03
                    seg.SCALE_cabalstore = 1.0
                    seg.shellfrac_cabalstore = min(0.1/seg.diam, 1.0)
                    seg.tog_cabalstore = 1
                    seg.DCa_cabalstore = self.internal['dca']
                
            if h.ismembrane('nmda'):
                s.cafrac_nmda = parms['cafrac']
                s.cMg_nmda = parms['cmg']
        
        # 表面積計算
        self.areas = []
        for s in self.nrn.all:
            if s.nseg > 1:
                locarea = 0
                for seg in s:
                    locarea += h.area(seg.x, sec=s)
            else:
                locarea = h.area(0.5, sec=s)
            self.areas.append(locarea)

    def __del__(self):
        if VERBOSE:
            print('killing', self.__class__.__name__)
        else:
            pass


def create_model(model_type, vinit):
    """
    論文のドーパミンニューロンモデルを作成する
    Parameters:
        model_type: "atypical" または "conventional"
    Returns:
        cell: NEURON細胞モデル
    """
    # パラメータディクショナリをインポート
    from def_paramsdict import get_params
    pstable = get_params(0 if model_type=="atypical" else 1)
    
    # パラメータセットを変更
    """if model_type == "conventional":
        # 論文のTable 1に従ってパラメータを設定
        pstable["gH"] = 50 # μS/cm2
        pstable['taukv4'] = 25  # ms
        pstable['gKdr'] = 2500 # μS/cm2 
        pstable['gNaV'] = 30  # mS/cm2
        pstable['gSK'] = 100  # μS/cm2
        pstable['CI1-I2'] = 2.5  # s-1
        pstable['size'] = 1000  # μm
    else:  # atypical
        pstable["gH"] = 0 # μS/cm2
        pstable['taukv4'] = 150  # ms
        pstable['gKdr'] = 1250  # μS/cm2
        pstable['gNaV'] = 15  # mS/cm2
        pstable['gSK'] = 20  # μS/cm2
        pstable['CI1-I2'] = 0.67  # s-1
        pstable['size'] = 500  # μm"""
    
    # dopa細胞クラスのインスタンスを作成
    cell = DopaCell(0, [1, 2], pstable, vinit)
    
    return cell, pstable


def run_simulation(cell, params, simulation_type="depolarization_block", duration=10000):
    """
    指定されたシミュレーションを実行
    Parameters:
        cell: dopamine細胞モデル
        params: パラメータディクショナリ
        simulation_type: "pacemaking", "current_step", "ramp", "depolarization_block"
                         または "bifurcation_analysis"
        duration: シミュレーション時間（ms）
    Returns:
        time: 時間ベクトル
        voltage: 電圧ベクトル
        other_data: その他のデータ
    """
    # 記録するベクトルを設定
    t_vec = h.Vector()
    v_vec = h.Vector()
    t_vec.record(h._ref_t)
    v_vec.record(cell.nrn.soma(0.5)._ref_v)
    
    # シミュレーションの種類に基づいて刺激を設定
    stim = None
    
    if simulation_type == "pacemaking":
        # 何もしない - 自発的発火
        pass
        
    elif simulation_type == "current_step":
        # 電流ステップ刺激 - 論文の図7と同様
        stim = h.IClamp(cell.nrn.soma(0.5))
        stim.delay = 1000  # ms
        stim.dur = 2000  # ms
        
        if params.get('CI1-I2', 0) > 50:  # conventional
            stim.amp = 0.075  # nA、75 pA
        else:  # atypical
            stim.amp = 0.075  # nA、75 pA
            
    cv = h.CVode()
    h.finitialize()
    cv.active(1)  # 可変ステップを使用
    
    if simulation_type == "bifurcation_analysis":
        # 長時間のシミュレーションで定常状態に達するようにする
        h.continuerun(10000)  # 10秒間のシミュレーション
    else:
        while h.t < duration:
            h.fadvance()
    
    # 結果を返す
    other_data = {
        'stim': stim,
    }
    
    return np.array(t_vec), np.array(v_vec), np.array(cell.srec), np.array(cell.da), other_data

def plot_results(time, voltage, spike, da, other_data, title="Simulation Results", plot_type="standard"):
    """
    結果をプロット
    Parameters:
        time: 時間ベクトル
        voltage: 電圧ベクトル
        other_data: その他のデータ
        title: プロットのタイトル
        plot_type: "standard", "na_states", "bifurcation", "phase_plane"
    """

    fig, ax = plt.subplots(3, 1, figsize=(18, 8), sharex=True)
    
    # 電圧プロット
    ax[0].plot(time, voltage, 'k', linewidth=1.5)
    ax[0].set_ylabel('Membrane Potential (mV)')
    ax[0].set_title(title)

    print(spike)

    #ax[1].plot(time, spike)
    #ax[1].set_ylabel("spike")
    #ax[1].set_title("spike")

    ax[2].plot(time, da)
    ax[2].set_ylabel("DA concentration (uM)")
    ax[2].set_title("DA concentration")
    
    plt.tight_layout()
    plt.savefig(f"result_{title}.png")


def main():
    """
    論文の主要な図を再現する
    """
    # 1. 自発発火の比較（論文のFig 6A1, B1）
    atypical_cell, atypical_params = create_model("atypical", -50)
    t, v, s, d, data = run_simulation(atypical_cell, atypical_params, "pacemaking", 2000)
    plot_results(t, v, s, d, data, "Atypical Cell - Spontaneous Pacemaking")
    
    """# 2. 相平面プロット（論文のFig 6A3, B3）
    plot_results(t, v, data, "Conventional Cell - Phase Plane", "phase_plane")
    
    # 3. 分岐解析（論文のFig 4C）
    atypical_bifurcation = perform_bifurcation_analysis("atypical")
    plot_results(None, None, atypical_bifurcation, "Atypical Cell", "bifurcation")
    
    conv_bifurcation = perform_bifurcation_analysis("conventional")
    plot_results(None, None, conv_bifurcation, "Conventional Cell", "bifurcation")
    
    # 4. 三角波電流に対する応答（論文の図2, 図6）
    t, v, data = run_simulation(atypical_cell, atypical_params, "ramp", 8000)
    plot_results(t, v, data, "Atypical Cell - Response to Triangular Current Ramp")
    
    t, v, data = run_simulation(conv_cell, conv_params, "ramp", 8000)
    plot_results(t, v, data, "Conventional Cell - Response to Triangular Current Ramp")
    
    # 5. 脱分極ブロックとNaチャンネル状態（論文の図7）
    t, v, data = run_simulation(atypical_cell, atypical_params, "depolarization_block", 3000)
    plot_results(t, v, data, "Atypical Cell - Depolarization Block", "na_states")
    
    t, v, data = run_simulation(conv_cell, conv_params, "depolarization_block", 3000)
    plot_results(t, v, data, "Conventional Cell - Depolarization Block", "na_states")"""


if __name__ == "__main__":
    main()