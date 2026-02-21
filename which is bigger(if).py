import random
number = 0
while True:
    try:
        print('which is bigger? y/n')
        if input().lower() == 'n':
            print("exit")
            break
        else:
            a = int(input('number?'))
            number = random.randint(1, 100)
            if a > number:
                print('bigger')
            elif a < number:
                print('smaller')
            else:
                print('equal')
    except ValueError:
        print('error')
        continue

    x = input('try again? y/n')
    if x == 'y':
        continue
    elif x == 'n':
        print("exit")
        break
    else:
        print('error')
        continue