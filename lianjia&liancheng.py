result = 0
print('which way would you like?')
print("1.+")
print('2.*')
try:
    choice = int(input())
    if choice == 1:  # 修正为根据用户输入的 choice 判断
        print("start number")
        a = int(input())
        print("end number")
        b = int(input())
        for x in range(a + 1, b):
            result += x
    elif choice == 2:  # 修正为根据用户输入的 choice 判断
        result = 1  # 初始化为 1，因为乘法需要从 1 开始
        print("start number")
        a = int(input())
        print("end number")
        b = int(input())
        for x in range(a + 1, b):
            result *= x
    else:
        print("Invalid choice")
except ValueError:
    print('error: invalid input')
except Exception as e:
    print(f'error: {e}')

print(result)
