from neuron import h, gui
import matplotlib.pyplot as plt
import numpy as np
import os
from mpi4py import MPI

VERBOSE=False

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


def create_dopapmie_neuron(model_type, vinit):
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
    
    # dopa細胞クラスのインスタンスを作成
    cell = DopaCell(0, [1, 2], pstable, vinit)
    
    return cell
