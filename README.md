# convert_complements.py

脚本说明：

- 将一组十进制整数转换为指定位宽下的原码（sign-magnitude）、反码（ones' complement）和补码（two's complement）。
- 默认为 8 位；可通过 `-w/--width` 指定其他位宽。

使用示例：

```
python convert_complements.py 5 -3 127 -128 --width 8
python convert_complements.py --example         # 显示示例输入的表格
```

注意事项：

- 当数值超出在指定位宽下可表示的范围时，表中显示 `OVERFLOW`。

验证可执行程序：

- 脚本增加了 `--verify-exe <path>` 参数，允许你指定一个可执行文件（例如桌面上的 `验证补码.exe`），脚本会尝试把每个整数传给该程序并把返回/读取到的内容显示在表格的 `Verify` 列中。
- 调用策略：首先尝试命令行方式（以参数传入）；如果失败且安装了 `pywinauto`，脚本会回退到基于 GUI 的自动化（启动程序、发送键盘输入并尝试读取窗口文本）。
- 如果要使用 GUI 自动化，需要先安装 `pywinauto`：

```powershell
pip install pywinauto
```

示例：

```powershell
python .\convert_complements.py 119 -119 86 -126 -67 -88 91 -17 -69 110 --width 8 --verify-exe "C:\Users\你\Desktop\验证补码.exe"
```

注意：GUI 自动化对目标程序窗口结构敏感；如果脚本无法读取窗口文本，脚本仍会把程序窗口显示出来，供你手动查看。
