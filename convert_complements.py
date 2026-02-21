#!/usr/bin/env python3
"""
convert_complements.py

将一组十进制整数转换为原码（sign-magnitude）、反码（ones' complement）和补码（two's complement），并以表格形式显示。

用法示例:
  python convert_complements.py 5 -3 127 -128 --width 8

默认宽度为 8 位。对于超出指定位宽表示范围的数，将标记为 OVERFLOW。
"""
from __future__ import annotations
import argparse
from typing import List
from typing import Tuple
import os
import subprocess
import time


def sign_magnitude(n: int, width: int) -> str:
    max_mag = (1 << (width - 1)) - 1
    if abs(n) > max_mag:
        return "OVERFLOW"
    sign = '0' if n >= 0 else '1'
    mag = format(abs(n), 'b').zfill(width - 1)
    return sign + mag


def ones_complement(n: int, width: int) -> str:
    # positive: same as sign-magnitude with leading 0
    # negative: bitwise NOT of positive representation in width bits
    max_mag = (1 << (width - 1)) - 1
    if abs(n) > max_mag:
        return "OVERFLOW"
    pos = '0' + format(abs(n), 'b').zfill(width - 1)
    if n >= 0:
        return pos
    # invert all bits
    return ''.join('1' if b == '0' else '0' for b in pos)
def twos_complement(n: int, width: int) -> str:
    min_val = -(1 << (width - 1))
    max_val = (1 << (width - 1)) - 1
    if n < min_val or n > max_val:
        return "OVERFLOW"
    # standard two's complement representation
    masked = n & ((1 << width) - 1)
    return format(masked, 'b').zfill(width)


def pretty_table(rows: List[List[str]], headers: List[str]) -> str:
    # Compute column widths
    cols = len(headers)
    widths = [len(h) for h in headers]
    for r in rows:
        for i, cell in enumerate(r):
            widths[i] = max(widths[i], len(cell))

    sep = '+'.join('-' * (w + 2) for w in widths)
    sep = '+' + sep + '+'

    def row_to_line(row: List[str]) -> str:
        parts = [f" {row[i].ljust(widths[i])} " for i in range(len(row))]
        return '|' + '|'.join(parts) + '|'

    lines = [sep, row_to_line(headers), sep]
    for r in rows:
        lines.append(row_to_line(r))
    lines.append(sep)
    return '\n'.join(lines)


def format_decimal(n: int) -> str:
    return str(n)


def detect_twos_overflow(a: int, b: int, result: int, width: int) -> bool:
    """Detect overflow for two's complement addition: occurs when a and b have same sign
    but result has different sign (considering width bits)."""
    min_val = -(1 << (width - 1))
    max_val = (1 << (width - 1)) - 1
    # range overflow
    if result < min_val or result > max_val:
        return True
    # sign overflow
    # Only matters if both operands are within range
    try:
        sa = 1 if a < 0 else 0
        sb = 1 if b < 0 else 0
        sr = 1 if result < 0 else 0
        return (sa == sb) and (sr != sa)
    except Exception:
        return False


def perform_addition(a: int, b: int, width: int) -> Tuple[int, dict]:
    """Perform addition and return (result, info_dict) where info_dict contains
    representations and overflow flags."""
    res = a + b
    info = {}
    info['a'] = {
        'dec': format_decimal(a),
        'sign': '0' if a >= 0 else '1',
        'sm': sign_magnitude(a, width),
        'oc': ones_complement(a, width),
        'tc': twos_complement(a, width),
    }
    info['b'] = {
        'dec': format_decimal(b),
        'sign': '0' if b >= 0 else '1',
        'sm': sign_magnitude(b, width),
        'oc': ones_complement(b, width),
        'tc': twos_complement(b, width),
    }
    info['result'] = {
        'dec': format_decimal(res),
        'sign': '0' if res >= 0 else '1',
        'sm': sign_magnitude(res, width),
        'oc': ones_complement(res, width),
        'tc': twos_complement(res, width),
    }

    # detect overflow conditions
    max_mag = (1 << (width - 1)) - 1
    min_tc = -(1 << (width - 1))
    max_tc = (1 << (width - 1)) - 1
    info['overflow'] = {
        'sign_magnitude_overflow': abs(res) > max_mag,
        'twos_range_overflow': not (min_tc <= res <= max_tc),
        'twos_addition_overflow': detect_twos_overflow(a, b, res, width),
    }
    return res, info


def main() -> None:
    parser = argparse.ArgumentParser(description='Convert decimals to sign-magnitude, ones and twos complement and show a table')
    # accept raw strings so floats won't cause argparse to fail; we'll handle parsing below
    parser.add_argument('numbers', nargs='*', type=str, help='decimal integers to convert (non-integers will be marked NOT_INT)')
    parser.add_argument('-w', '--width', type=int, default=8, help='bit width (default: 8)')
    parser.add_argument('--verify-exe', type=str, default=None, help='路径到验证程序（例如: C:\\Users\\You\\Desktop\\验证补码.exe）。脚本会尝试把每个整数传入该可执行文件以获取其验证输出。')
    parser.add_argument('--verify-timeout', type=float, default=5.0, help='与验证程序交互的超时时间（秒）')
    parser.add_argument('--example', action='store_true', help='show example list')
    parser.add_argument('--add', nargs=2, metavar=('A','B'), help='Perform A + B and show conversions and overflow (provide two integers)')
    args = parser.parse_args()

    if args.example or not args.numbers:
        nums_raw = ["119", "-119", "86", "-126", "-67", "-88", "91", "-17", "-69", "110"]
        # if user passed numbers, prefer those
        if args.numbers:
            nums_raw = args.numbers
    else:
        nums_raw = args.numbers

    width = args.width

    # Helper functions to try verifying with external exe
    def verify_with_exe_cmd(exe_path: str, input_str: str, timeout: float) -> Tuple[bool, str]:
        try:
            completed = subprocess.run([exe_path, input_str], capture_output=True, text=True, timeout=timeout)
            out = (completed.stdout or completed.stderr or '').strip()
            return (completed.returncode == 0, out if out else f"RETURNCODE={completed.returncode}")
        except Exception as e:
            return (False, f"cmd-invoke-failed: {e}")

    def verify_with_exe_gui(exe_path: str, input_str: str, timeout: float) -> Tuple[bool, str]:
        try:
            from pywinauto import Application, keyboard
        except Exception as e:
            return (False, f"pywinauto-not-available: {e}")
        try:
            app = Application(backend='uia').start(exe_path)
            time.sleep(0.5)
            dlg = app.top_window()
            dlg.set_focus()
            keyboard.send_keys(str(input_str), pause=0.02)
            keyboard.send_keys('{ENTER}')
            time.sleep(min(0.5, timeout))
            try:
                texts = dlg.texts()
                out = '\n'.join(t for t in texts if t and t.strip())
            except Exception:
                out = 'gui-invoke-succeeded (could not read control texts)'
            return (True, out)
        except Exception as e:
            return (False, f"gui-invoke-failed: {e}")

    exe_path_arg = args.verify_exe

    # If --add provided, perform addition and display conversions and overflow info
    if args.add:
        a_s, b_s = args.add
        try:
            a = int(a_s)
            b = int(b_s)
        except Exception:
            print('ERROR: --add requires two integers')
            return
        res, info = perform_addition(a, b, width)
        headers = ['Decimal', 'Sign', 'Sign-Magnitude', "One's Complement", "Two's Complement"]
        rows = [
            [info['a']['dec'], info['a']['sign'], info['a']['sm'], info['a']['oc'], info['a']['tc']],
            [info['b']['dec'], info['b']['sign'], info['b']['sm'], info['b']['oc'], info['b']['tc']],
            [info['result']['dec'], info['result']['sign'], info['result']['sm'], info['result']['oc'], info['result']['tc']],
        ]
        print(f"Addition: {a} + {b} = {res} (width={width})\n")
        print(pretty_table(rows, headers))
        ov = info['overflow']
        if ov['sign_magnitude_overflow']:
            print('\nERROR: sign-magnitude magnitude overflow: result magnitude exceeds representable range for width')
        if ov['twos_range_overflow']:
            print('\nERROR: two\'s-complement range overflow: result outside [{}, {}]'.format(-(1 << (width-1)), (1 << (width-1)) - 1))
        if ov['twos_addition_overflow'] and not ov['twos_range_overflow']:
            print('\nWARNING: two\'s-complement addition overflow detected (sign change)')
        return

    headers = ['Decimal', 'Sign', 'Sign-Magnitude', "One's Complement", "Two's Complement"]
    if exe_path_arg:
        headers.append('Verify')

    rows = []
    for s in nums_raw:
        # try to parse integer; if not integer (e.g. float), mark as NOT_INT
        try:
            n = int(s)
            sm = sign_magnitude(n, width)
            oc = ones_complement(n, width)
            tc = twos_complement(n, width)
            sign_bit = '0' if n >= 0 else '1'
            row = [format_decimal(n), sign_bit, sm, oc, tc]

            if exe_path_arg:
                exe_path = os.path.expanduser(exe_path_arg)
                if not os.path.isabs(exe_path):
                    exe_path = os.path.abspath(exe_path)

                ok, out = verify_with_exe_cmd(exe_path, str(n), args.verify_timeout)
                method = 'cmd'
                if not ok:
                    ok2, out2 = verify_with_exe_gui(exe_path, str(n), args.verify_timeout)
                    if ok2:
                        ok = True
                        out = out2
                        method = 'gui'
                    else:
                        out = out + ' | ' + out2

                snippet = out.replace('\n', ' ').strip()
                if len(snippet) > 60:
                    snippet = snippet[:57] + '...'
                row.append(f"[{method}] {snippet}")

            rows.append(row)
        except Exception:
            # not an integer (float or invalid) -> display as-is and mark NOT_INT
            rows.append([s, 'N/A', 'NOT_INT', 'NOT_INT', 'NOT_INT'] + ([''] if exe_path_arg else []))

    print(f"Bit width: {width} bits\n")
    print(pretty_table(rows, headers))


if __name__ == '__main__':
    main()
