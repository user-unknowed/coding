# 使用 for 循环遍历从 -50 到 50 的所有整数
for a in range(-50, 51):
    # 计算函数值 b = a^2 + 2a + 1
    b = a**2 + 2*a + 1

    # 打印 a 和 b 的值
    print(f"a = {a}, b = {b}")