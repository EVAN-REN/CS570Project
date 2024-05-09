import matplotlib.pyplot as plt

# 示例数据
x = [16, 64, 128, 256, 384, 512, 768, 1024, 1280, 1536, 2048, 2560, 3072, 3584, 3968]
t_basic = [0.029, 0.147, 0.494, 1.88, 4.53, 7.46, 17.136, 33.365, 47.452, 68.674, 123.388, 183.984, 277.988, 374.073, 460.02]
t_efficient = [0.061, 0.307, 1.243, 4.047, 8.091, 17.5, 35.308, 57.397, 86.615, 146.817, 239.469, 376.662, 568, 739.85, 867.602]
m_basic = [2952, 2952, 2952, 2952, 3156, 3100, 3388, 3884, 4444, 5132, 7028, 9508, 12044, 15408, 18412]
m_efficient = [2900, 2900, 2900, 2900, 2900, 2900, 2900, 2900, 2900, 2900, 2900, 2900, 2900, 2900, 2900]

plt.plot(x, t_basic, label='basic function')
plt.plot(x, t_efficient, label='efficient function')

# plt.plot(x, m_basic, label='basic function')
# plt.plot(x, m_efficient, label='efficient function')

plt.title('CPU time vs problem size')
plt.xlabel('Problem Size(m + n)')
plt.ylabel('CPU Time(milliseconds)')

# plt.title('Memory usage vs problem size')
# plt.xlabel('Problem Size(m + n)')
# plt.ylabel('Memory usage(KB)')

# 添加图例
plt.legend()

# 显示图形
plt.show()
