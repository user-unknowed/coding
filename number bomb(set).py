import random


def play_number_bomb():
    """进行一次猜数字游戏：在1-100中随机选一个数，用集合追踪可能值，并在每次猜测后缩小范围。"""
    a = random.randint(1, 100)
    candidates = set(range(1, 101))

    print('已在 1-100 中生成一个数字，开始猜吧（输入 q 退出本局）')
    while True:
        try:
            s = input('你的猜测: ').strip().lower()
            if s == 'q':
                print('本局退出，正确答案是', a)
                return
            guess = int(s)
            if guess < 1 or guess > 100:
                print('请输入 1 到 100 之间的整数')
                continue

            if guess == a:
                print('恭喜，猜对了！答案是', a)
                return
            elif guess > a:
                # 猜大了，剔除所有 >= guess
                to_remove = {x for x in candidates if x >= guess}
                candidates -= to_remove
                print('猜大了。可能的数字还剩 {} 个'.format(len(candidates)))
            else:
                # 猜小了，剔除所有 <= guess
                to_remove = {x for x in candidates if x <= guess}
                candidates -= to_remove
                print('猜小了。可能的数字还剩 {} 个'.format(len(candidates)))

            # 提示当前候选范围（只在候选数不多时显示全部，否则显示最小/最大）
            if len(candidates) <= 20:
                print('候选：', sorted(candidates))
            else:
                print('候选范围大致在 {} - {}'.format(min(candidates), max(candidates)))

        except ValueError:
            print('输入无效，请输入数字或 q 退出')


def main():
    while True:
        cmd = input("输入 'number' 开始游戏，或输入 'exit' 退出: ").strip().lower()
        if cmd == 'exit':
            print('退出程序')
            break
        elif cmd == 'number':
            play_number_bomb()
            # 游戏结束后询问是否再玩一次
            while True:
                again = input('再来一局吗？(Y/N): ').strip().lower()
                if again == 'y':
                    break
                elif again == 'n':
                    print('退出程序')
                    return
                else:
                    print('请输入 Y 或 N')
        else:
            print("未知指令，请输入 'number' 或 'exit'")


if __name__ == '__main__':
    main()