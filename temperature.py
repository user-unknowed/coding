import random

# 重复生成并打印 4 次在 36.0 到 36.9 之间的随机小数
for _ in range(4):
    a = random.uniform(36.0, 36.9)
    # 格式化为保留两位小数的字符串输出
    print(f"{a:.2f}")
    