"""
增强版：支持混合输入（十六进制/十进制），并能处理小数（十进制小数或十六进制小数）。

下面对文件中每个函数和关键步骤添加中文注释，说明输入、输出与实现要点，
注释风格尽量详细但不改变原始逻辑或输出行为。
"""

import re
import sys


# split_tokens: 将输入行拆分为 token 列表
# 说明：使用正则匹配三类 token：
#   1) 以 0x 可选前缀的十六进制（可带小数点，例如 0xA.B 或 A.B），
#   2) 含字母 A-F 的十六进制（可带小数点，例如 6E, A.B），
#   3) 普通十进制数或十进制小数（例如 12 或 12.375）。
def split_tokens(s):
	"""用正则提取可能的数字项：支持 0x...、十六进制小数（含 A-F）、或十进制小数。"""
	# pattern 说明：(?i) 忽略大小写，(?:0x)? 可选 0x 前缀，后面允许小数点部分
	pattern = r"(?i)(?:0x)?[0-9a-f]+(?:\.[0-9a-f]+)?|\d+(?:\.\d+)?"
	return re.findall(pattern, s)


# is_hex_token: 判断 token 是否应按十六进制解析
# 规则：token 包含字母 a-f（说明显然为 hex），或以 "0x" 开头也当作 hex
def is_hex_token(tok):
	"""判断 token 是否应被当作十六进制：包含字母 a-f 或以 0x 开头。"""
	return bool(re.search(r"[a-fA-F]", tok)) or tok.lower().startswith('0x')


# hex_str_to_decimal: 把十六进制字符串（可能含小数点）转换为十进制浮点值
# 返回值：(规范化的十六进制文本, 十进制浮点值)
# 例如：'0xA.B' -> ('A.B', 10.6875)
def hex_str_to_decimal(tok):
	"""把十六进制字符串（可能含小数点）转换为十进制浮点数，并返回 (normalized_hex, decimal_value)。"""
	s = tok.lower()
	# 移除可选的 0x 前缀
	if s.startswith('0x'):
		s = s[2:]
	parts = s.split('.')
	int_part = parts[0] if parts[0] != '' else '0'
	frac_part = parts[1] if len(parts) > 1 else ''
	# 整数部分直接用 int(...,16)
	dec_int = int(int_part, 16) if int_part else 0
	# 小数部分按位累加：每位的权重为 1/16^i
	dec_frac = 0.0
	for i, ch in enumerate(frac_part, start=1):
		dec_frac += int(ch, 16) / (16 ** i)
	# 返回规范化十六进制（大写）和计算得到的十进制浮点
	return ((int_part + ('.' + frac_part if frac_part else '')).upper(), dec_int + dec_frac)


# dec_float_to_binary_str: 把十进制浮点数转换为二进制表示（字符串）
# - 支持整数和小数部分
# - frac_bits 控制小数位的精度（默认 20 位），可通过参数调整
def dec_float_to_binary_str(x, frac_bits=20):
	"""把十进制浮点数转换为二进制字符串（带小数部分），保留 frac_bits 位小数。"""
	if x < 0:
		sign = '-'
		x = -x
	else:
		sign = ''
	int_part = int(x)
	frac = x - int_part
	# 整数部分直接用 format
	int_str = format(int_part, 'b')
	if frac == 0:
		return sign + int_str
	bits = []
	# 通过不断乘 2 提取小数位
	for _ in range(frac_bits):
		frac *= 2
		bit = int(frac)
		bits.append(str(bit))
		frac -= bit
		if frac == 0:
			break
	return sign + int_str + '.' + ''.join(bits)


# dec_float_to_hex_str: 把十进制浮点数转换为十六进制字符串（带小数部分）
# - frac_digits 控制小数位长度（默认 10 位）
def dec_float_to_hex_str(x, frac_digits=10):
	"""把十进制浮点数转换为十六进制字符串（带小数部分），保留 frac_digits 位小数。"""
	if x < 0:
		sign = '-'
		x = -x
	else:
		sign = ''
	int_part = int(x)
	frac = x - int_part
	int_str = format(int_part, 'X')
	if frac == 0:
		return sign + int_str
	digits = []
	# 小数部分乘 16 提取每一位
	for _ in range(frac_digits):
		frac *= 16
		d = int(frac)
		digits.append(format(d, 'X'))
		frac -= d
		if frac == 0:
			break
	return sign + int_str + '.' + ''.join(digits)


# handle_tokens: 对拆分出的 token 逐个处理并生成结果记录
# - 对于被识别为十六进制的 token，调用 hex_str_to_decimal -> 得到十进制浮点后转换为二进制字符串
# - 对于十进制 token（可能含小数），直接 float(...) -> 再转换为二进制与十六进制表示
def handle_tokens(tokens):
	"""处理识别出的 token 列表，返回结果记录列表。"""
	results = []
	for tok in tokens:
		if is_hex_token(tok):
			# 解析十六进制（支持小数部分），返回规范化 hex 文本与十进制值
			hx_norm, dec = hex_str_to_decimal(tok)
			# 再把十进制值转为二进制（可能带小数）用于显示
			bstr = dec_float_to_binary_str(dec)
			# 记录格式：(原始 token, 类型 'hex', 规范化 hex, 二进制表示, 十进制值)
			results.append((tok, 'hex', hx_norm, bstr, dec))
		else:
			# 十进制输入（可能带小数），安全转换为 float
			try:
				dec = float(tok)
			except ValueError:
				# 若无法解析，跳过该项
				continue
			bstr = dec_float_to_binary_str(dec)
			hx = dec_float_to_hex_str(dec)
			# 记录格式：(原始 token, 类型 'dec', 十六进制表示, 二进制表示, 十进制值)
			results.append((tok, 'dec', hx, bstr, dec))
	return results


# print_results: 把结果按可读形式打印到标准输出
def print_results(results):
	print('\n结果（原始, 类型, 转换后（HEX/HEX-NORM 或 BIN），十进制）:')
	for orig, typ, rep1, rep2, dec in results:
		if typ == 'hex':
			# rep1 = 规范化十六进制文本，rep2 = 二进制字符串，dec = 十进制浮点
			print(f"{orig} (HEX) -> 二进制: {rep2}  十进制: {dec}")
		else:
			# dec 输入：rep1 = 十六进制表示，rep2 = 二进制字符串
			print(f"{orig} (DEC) -> 二进制: {rep2}  十六进制: {rep1}  十进制: {dec}")


# main: 支持命令行参数或交互式输入
# - 若通过命令行参数传入（python 111111.py 218 6E），则合并参数为一行处理
# - 否则提示用户交互式输入
def main(argv=None):
	if argv is None:
		argv = sys.argv[1:]
	if argv:
		# 通过命令行参数传入，合并为一行
		s = ' '.join(argv)
	else:
		s = input('请输入十六进制或十进制数（支持小数，空格或逗号分隔）：')
	tokens = split_tokens(s)
	if not tokens:
		print('未检测到有效项。')
		return
	results = handle_tokens(tokens)
	print_results(results)


if __name__ == '__main__':
	main()


