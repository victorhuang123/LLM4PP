from openai import OpenAI

def test_openai_key(api_key):
    # 初始化OpenAI客户端
    client = OpenAI(api_key=api_key)

    try:
        # 发送一个简单的提示
        response = client.chat.completions.create(
            model="gpt-4o-mini",  # 使用gpt-4o-mini模型
            messages=[
                {"role": "user", "content": "Say 'Hello, World!'"}
            ],
            max_tokens=5  # 最大生成的令牌数
        )

        # 检查是否成功返回响应
        if response and response.choices:
            print("API密钥有效！")
            print("响应内容:", response.choices[0].message.content.strip())
        else:
            print("API密钥无效或未返回有效响应。")

    except Exception as e:
        # 捕获并打印错误信息
        print("API调用失败，错误信息:", str(e))


# 替换为你的OpenAI API密钥
api_key = "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"

# 测试API密钥
test_openai_key(api_key)