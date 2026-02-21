import random

while True:
    try:
        print('which is bigger? y/n')
        if input().lower() == 'n':
            print("exit")
            break

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

    while True:
        x = input('try again? y/n')
        if x == 'y':
            break
        elif x == 'n':
            print("exit")
            exit()
        else:
            print('error')