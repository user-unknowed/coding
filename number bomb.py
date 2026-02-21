import random

while True:
    print('number/exit?')
    user_input = input().lower()
    if user_input == 'exit':
        print("quit")
        break
    elif user_input == 'number':
        while True:
            print('input number')
            a = random.randint(1, 100)  # 生成1到100之间的整数
            while True:
                try:
                    number = int(input())
                    if a == number:
                        print('equal')
                        print('a:', a)
                        print('try again?  Y/N')
                        retry_input = input().lower()
                        if retry_input == "n":
                            print("quit")
                            break
                        elif retry_input == "y":
                            break
                    elif a < number:
                        print('a is less than number')
                    else:
                        print('a is greater than number')
                except ValueError:
                    print('error')
            if retry_input == "n":
                break
        continue