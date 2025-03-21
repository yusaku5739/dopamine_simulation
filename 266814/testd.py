from neuron import h
import numpy as np

# セクションとメカニズムの作成
soma = h.Section(name='soma')
soma.insert('hh')  # Hodgkin-Huxleyチャネルを挿入
soma.L = 20        # 長さ
soma.diam = 20     # 直径

# ドーパミン放出メカニズムの挿入
da_release = h.DopamineRelease(soma(0.5))

# NetStimの作成（テスト用の人工的なスパイク生成）
stim = h.NetStim()
stim.number = 100    # スパイク数
stim.start = 100    # 開始時刻 (ms)
stim.interval = 100 # スパイク間隔 (ms)
stim.noise = 0     # 決定論的なスパイクタイミング

# NetConの設定
# 第1引数: ソース（スパイク源）
# 第2引数: ターゲット（ドーパミン放出メカニズム）
# 第3引数: 閾値
# 第4引数: 遅延
# 第5引数: 重み
nc = h.NetCon(stim, da_release, 0, 0, 1)

# 記録用のベクター設定
t_vec = h.Vector()
da_vec = h.Vector()
t_vec.record(h._ref_t)
da_vec.record(da_release._ref_DA)

cv = h.CVode()
h.finitialize()
cv.active(1)  # 可変ステップを使用

while h.t < 10000:
    h.fadvance()

# 結果の取得
time = np.array(t_vec)
da = np.array(da_vec)

import matplotlib.pyplot as plt
plt.plot(time, da)
plt.savefig("test_dopa.png")