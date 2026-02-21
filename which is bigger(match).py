import random

while True:
    try:
        print('which is bigger? y/n')
        user_input = input().lower()
        match user_input:
            case 'n':
                print("exit")
                break
            case 'y':
                a = int(input('number?'))
                number = random.randint(1, 100)
                match a:
                    case _ if a > number:
                        print('bigger')
                    case _ if a < number:
                        print('smaller')
                    case _:
                        print('equal')
            case _:
                print('error')
                continue

        x = input('try again? y/n').lower()
        match x:
            case 'y':
                continue
            case 'n':
                print("exit")
                break
            case _:
                print('error')
                continue
    except ValueError:
        print('error')
        continue