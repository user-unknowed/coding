import base64

def encode_base64(message):
    # 将字符串转换为bytes
    message_bytes = message.encode('utf-8')
    # 进行base64编码
    base64_bytes = base64.b64encode(message_bytes)
    # 将bytes转换回字符串
    base64_message = base64_bytes.decode('utf-8')
    return base64_message

def decode_base64(base64_message):
    try:
        # 将base64字符串转换为bytes
        base64_bytes = base64_message.encode('utf-8')
        # 进行base64解码
        message_bytes = base64.b64decode(base64_bytes)
        # 将bytes转换回字符串
        message = message_bytes.decode('utf-8')
        return message
    except:
        return "解码失败！请确保输入的是有效的Base64字符串。"

# 测试程序
while True:
    print("\n=== Base64编解码器 ===")
    print("1. 编码")
    print("2. 解码")
    print("3. 退出")
    
    choice = input("请选择操作 (1/2/3): ")
    
    if choice == "1":
        message = input("请输入要编码的文本: ")
        encoded = encode_base64(message)
        print("编码结果:", encoded)
    
    elif choice == "2":
        message = input("请输入要解码的Base64字符串: ")
        decoded = decode_base64(message)
        print("解码结果:", decoded)
    
    elif choice == "3":
        print("谢谢使用！")
        break
    
    else:
        print("无效的选择，请重试。")

