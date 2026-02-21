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
                    match number:
                        case _ if a == number:
                            print('equal')
                            print('a:', a)
                            print('try again?  Y/N')
                            retry_input = input().lower()
                            match retry_input:
                                case "n":
                                    print("quit")
                                    break
                                case "y":
                                    break
                        case _ if a < number:
                            print('a is less than number')
                        case _:
                            print('a is greater than number')
                except ValueError:
                    print('error')
            if retry_input == "n":
                break
        continue