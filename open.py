import os

# 文件路径
file_path = "军训心得.docx"

# 检查文件是否存在
if os.path.exists(file_path):
    # 打开文件
    os.startfile(file_path)
else:
    print(f"文件 {file_path} 不存在，请检查路径。")