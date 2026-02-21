---
name: "github-code-submission"
description: "将代码文件提交到GitHub仓库。当用户要求将代码提交到git或GitHub时调用此技能。"
---

# GitHub 代码提交技能

此技能帮助将本地代码文件提交到GitHub远程仓库，支持单文件或多文件批量提交。

## 何时调用

- 用户要求将代码提交到git仓库
- 用户想要将代码推送到GitHub
- 用户需要提交特定文件夹的代码文件
- 用户要求备份代码到远程仓库

## 功能特性

### 1. 自动检测Git仓库状态
- 检查当前目录是否为git仓库
- 识别已配置的远程仓库
- 验证远程仓库连接状态

### 2. 智能文件选择
- 支持单文件提交
- 支持多文件批量提交
- 支持文件夹批量提交
- 自动过滤不需要提交的文件（如.exe、.pyc等）
- 支持自定义文件选择
- 文件格式验证和大小检查
- 并发上传控制

### 3. 多种提交方式
- 使用GitHub MCP工具直接提交
- 使用本地git命令提交
- 支持创建新分支提交
- 支持Pull Request创建

### 4. 错误处理
- 处理空仓库情况
- 处理认证失败
- 处理文件冲突
- 提供清晰的错误提示

## 操作流程

### 步骤1：环境检查

```bash
# 检查git状态
git status

# 检查远程仓库配置
git remote -v

# 查看当前分支
git branch
```

### 步骤2：文件准备

```bash
# 查看文件列表
ls -la

# 查看特定文件夹
ls -la c/

# 查看文件内容
cat README.md
```

### 步骤3：文件读取

读取需要提交的文件内容，确保：
- 文件内容完整
- 编码正确
- 无敏感信息
- 符合项目规范

### 步骤4：GitHub提交

#### 方式A：使用MCP工具（推荐）

```python
# 单文件提交
mcp_GitHub_create_or_update_file(
    owner="username",
    repo="repository",
    path="file/path",
    content="file content",
    message="commit message",
    branch="main"
)

# 多文件批量提交
mcp_GitHub_push_files(
    owner="username",
    repo="repository",
    branch="main",
    files=[
        {"path": "file1", "content": "content1"},
        {"path": "file2", "content": "content2"}
    ],
    message="commit message"
)
```

#### 方式B：使用本地git命令

```bash
# 添加文件到暂存区
git add file1.c file2.cpp

# 提交更改
git commit -m "commit message"

# 推送到远程仓库
git push origin main
```

### 步骤5：验证提交

```bash
# 查看提交历史
git log --oneline

# 查看远程状态
git remote show origin

# 在GitHub上验证
# 访问仓库URL查看文件
```

## 多文件批量上传功能

### 功能特性

1. **多文件选择**
   - 支持用户手动选择多个文件
   - 支持通配符模式选择（如 `*.c`, `*.cpp`）
   - 支持文件夹递归选择
   - 提供文件预览和确认界面

2. **文件验证和大小检查**
   - 自动验证文件格式（文本文件、代码文件）
   - 检查文件大小（单文件不超过100MB）
   - 检测并过滤二进制文件
   - 验证文件编码（UTF-8、GBK等）

3. **批量处理状态反馈**
   - 实时显示上传进度（已完成/总数）
   - 显示每个文件的上传状态
   - 提供详细的错误信息
   - 支持取消操作

4. **并发控制**
   - 支持并发上传多个文件
   - 可配置并发数量（默认3个）
   - 防止过载GitHub API
   - 自动重试失败的文件

5. **错误恢复机制**
   - 自动处理文件冲突
   - 网络错误自动重试（最多3次）
   - 部分失败不影响其他文件
   - 提供失败文件列表和重试选项

### 多文件上传流程

#### 步骤1：文件选择和验证

```python
def select_and_validate_files(file_paths):
    """
    选择并验证多个文件
    返回验证通过的文件列表
    """
    validated_files = []
    
    for file_path in file_paths:
        # 1. 检查文件是否存在
        if not os.path.exists(file_path):
            print(f"❌ 文件不存在: {file_path}")
            continue
        
        # 2. 检查文件大小
        file_size = os.path.getsize(file_path)
        if file_size > 100 * 1024 * 1024:  # 100MB
            print(f"❌ 文件过大: {file_path} ({file_size/1024/1024:.2f}MB)")
            continue
        
        # 3. 验证文件格式
        if not is_text_file(file_path):
            print(f"❌ 不支持的文件格式: {file_path}")
            continue
        
        # 4. 读取文件内容
        try:
            with open(file_path, 'r', encoding='utf-8') as f:
                content = f.read()
            
            # 5. 检查敏感信息
            if contains_sensitive_info(content):
                print(f"⚠️  文件包含敏感信息: {file_path}")
                continue
            
            validated_files.append({
                'path': file_path,
                'content': content,
                'size': file_size
            })
            print(f"✅ 文件验证通过: {file_path}")
            
        except Exception as e:
            print(f"❌ 读取文件失败: {file_path} - {str(e)}")
    
    return validated_files
```

#### 步骤2：并发上传控制

```python
import concurrent.futures
from threading import Lock

class FileUploader:
    def __init__(self, max_concurrent=3):
        self.max_concurrent = max_concurrent
        self.uploaded_count = 0
        self.failed_count = 0
        self.total_count = 0
        self.lock = Lock()
        self.results = []
    
    def upload_file(self, owner, repo, branch, file_info):
        """上传单个文件"""
        try:
            result = mcp_GitHub_create_or_update_file(
                owner=owner,
                repo=repo,
                path=file_info['path'],
                content=file_info['content'],
                message=f"Upload {os.path.basename(file_info['path'])}",
                branch=branch
            )
            
            with self.lock:
                self.uploaded_count += 1
                progress = (self.uploaded_count / self.total_count) * 100
                print(f"✅ [{self.uploaded_count}/{self.total_count}] ({progress:.1f}%) - {file_info['path']}")
            
            return {'success': True, 'file': file_info['path']}
            
        except Exception as e:
            with self.lock:
                self.failed_count += 1
                print(f"❌ 上传失败: {file_info['path']} - {str(e)}")
            
            return {'success': False, 'file': file_info['path'], 'error': str(e)}
    
    def upload_files_concurrently(self, owner, repo, branch, files):
        """并发上传多个文件"""
        self.total_count = len(files)
        print(f"📦 开始上传 {self.total_count} 个文件...")
        
        with concurrent.futures.ThreadPoolExecutor(max_workers=self.max_concurrent) as executor:
            futures = []
            for file_info in files:
                future = executor.submit(
                    self.upload_file,
                    owner, repo, branch, file_info
                )
                futures.append(future)
            
            # 等待所有任务完成
            for future in concurrent.futures.as_completed(futures):
                result = future.result()
                self.results.append(result)
        
        # 输出汇总信息
        print(f"\n📊 上传完成:")
        print(f"   ✅ 成功: {self.uploaded_count} 个")
        print(f"   ❌ 失败: {self.failed_count} 个")
        
        return self.results
```

#### 步骤3：错误恢复和重试机制

```python
def retry_failed_uploads(results, owner, repo, branch, max_retries=3):
    """
    重试失败的文件上传
    """
    failed_files = [r for r in results if not r['success']]
    
    if not failed_files:
        return results
    
    print(f"\n🔄 开始重试 {len(failed_files)} 个失败的文件...")
    
    retry_count = 0
    while retry_count < max_retries and failed_files:
        retry_count += 1
        print(f"📝 第 {retry_count} 次重试...")
        
        new_results = []
        for failed_file in failed_files:
            try:
                result = mcp_GitHub_create_or_update_file(
                    owner=owner,
                    repo=repo,
                    path=failed_file['file'],
                    content=failed_file.get('content'),
                    message=f"Retry upload {os.path.basename(failed_file['file'])}",
                    branch=branch
                )
                new_results.append({'success': True, 'file': failed_file['file']})
                print(f"✅ 重试成功: {failed_file['file']}")
            except Exception as e:
                new_results.append({'success': False, 'file': failed_file['file'], 'error': str(e)})
                print(f"❌ 重试失败: {failed_file['file']} - {str(e)}")
        
        # 更新失败文件列表
        failed_files = [r for r in new_results if not r['success']]
        
        if not failed_files:
            print("✅ 所有文件重试成功！")
            break
    
    return results
```

#### 步骤4：完整的多文件上传示例

```python
def batch_upload_files(file_paths, owner, repo, branch="main"):
    """
    批量上传文件的完整流程
    """
    print("🚀 开始多文件批量上传流程\n")
    
    # 步骤1: 选择和验证文件
    print("📋 步骤1: 文件选择和验证")
    validated_files = select_and_validate_files(file_paths)
    
    if not validated_files:
        print("❌ 没有通过验证的文件")
        return False
    
    # 步骤2: 并发上传
    print(f"\n📤 步骤2: 并发上传文件")
    uploader = FileUploader(max_concurrent=3)
    results = uploader.upload_files_concurrently(
        owner, repo, branch, validated_files
    )
    
    # 步骤3: 错误恢复
    print(f"\n🔄 步骤3: 错误恢复和重试")
    final_results = retry_failed_uploads(results, owner, repo, branch)
    
    # 步骤4: 验证和汇总
    print(f"\n✅ 步骤4: 验证和汇总")
    success_count = sum(1 for r in final_results if r['success'])
    total_count = len(final_results)
    
    print(f"\n📊 最终结果:")
    print(f"   总文件数: {total_count}")
    print(f"   成功上传: {success_count}")
    print(f"   失败上传: {total_count - success_count}")
    
    if success_count == total_count:
        print("\n🎉 所有文件上传成功！")
        return True
    else:
        print(f"\n⚠️  有 {total_count - success_count} 个文件上传失败")
        failed_files = [r['file'] for r in final_results if not r['success']]
        print("失败的文件:")
        for file in failed_files:
            print(f"   - {file}")
        return False
```

### 辅助函数

```python
def is_text_file(file_path):
    """检查是否为文本文件"""
    text_extensions = ['.c', '.cpp', '.h', '.hpp', '.py', '.js', 
                    '.java', '.go', '.rs', '.ts', '.md', 
                    '.txt', '.json', '.yaml', '.yml', '.xml']
    return any(file_path.lower().endswith(ext) for ext in text_extensions)

def contains_sensitive_info(content):
    """检查是否包含敏感信息"""
    sensitive_patterns = [
        r'password\s*=\s*["\'].*["\']',
        r'api[_-]?key\s*=\s*["\'].*["\']',
        r'secret\s*=\s*["\'].*["\']',
        r'token\s*=\s*["\'].*["\']'
    ]
    
    for pattern in sensitive_patterns:
        if re.search(pattern, content, re.IGNORECASE):
            return True
    return False

def format_file_size(size_bytes):
    """格式化文件大小"""
    if size_bytes < 1024:
        return f"{size_bytes} B"
    elif size_bytes < 1024 * 1024:
        return f"{size_bytes / 1024:.2f} KB"
    else:
        return f"{size_bytes / (1024 * 1024):.2f} MB"
```

### 使用示例

#### 示例1：上传多个指定文件

```python
# 用户指定多个文件
file_paths = [
    'c/README.md',
    'c/222.c',
    'c/bfs.c',
    'c/divide_candy.c'
]

batch_upload_files(
    file_paths,
    owner="user-unknowed",
    repo="coding",
    branch="main"
)
```

#### 示例2：上传整个文件夹

```python
# 上传c文件夹的所有.c文件
import glob

file_paths = glob.glob('c/*.c')
file_paths.append('c/README.md')

batch_upload_files(
    file_paths,
    owner="user-unknowed",
    repo="coding",
    branch="main"
)
```

#### 示例3：递归上传文件夹

```python
# 递归上传c文件夹及其子文件夹的所有文件
file_paths = []
for root, dirs, files in os.walk('c'):
    for file in files:
        file_path = os.path.join(root, file)
        if is_text_file(file_path):
            file_paths.append(file_path)

batch_upload_files(
    file_paths,
    owner="user-unknowed",
    repo="coding",
    branch="main"
)
```

### 性能优化

1. **并发控制**
   - 默认并发数：3
   - 可根据网络状况调整（1-10）
   - 避免GitHub API限流

2. **批量提交优化**
   - 对于小文件（<10KB），使用批量提交
   - 对于大文件（>10KB），单独提交
   - 自动分组优化上传效率

3. **进度显示优化**
   - 使用进度条显示
   - 实时更新上传速度
   - 预估剩余时间

4. **内存管理**
   - 流式读取大文件
   - 及时释放已上传文件的内存
   - 防止内存溢出

### 错误处理增强

1. **文件冲突处理**
   ```python
   def handle_file_conflict(file_path, owner, repo, branch):
       """处理文件冲突"""
       try:
           # 获取远程文件SHA
           remote_file = mcp_GitHub_get_file_contents(
               owner=owner, repo=repo, path=file_path, branch=branch
           )
           
           # 询问用户处理方式
           print(f"⚠️  文件冲突: {file_path}")
           choice = input("选择处理方式: [1]覆盖 [2]合并 [3]取消: ")
           
           if choice == '1':
               # 覆盖远程文件
               return force_upload(file_path, owner, repo, branch)
           elif choice == '2':
               # 合并文件
               return merge_files(file_path, remote_file, owner, repo, branch)
           else:
               # 取消上传
               return None
               
       except Exception as e:
           print(f"❌ 处理冲突失败: {str(e)}")
           return None
   ```

2. **网络错误重试**
   ```python
   def upload_with_retry(file_info, owner, repo, branch, max_retries=3):
       """带重试机制的上传"""
       for attempt in range(max_retries):
           try:
               return mcp_GitHub_create_or_update_file(
                   owner=owner, repo=repo, branch=branch,
                   path=file_info['path'], content=file_info['content'],
                   message=f"Upload {os.path.basename(file_info['path'])}"
               )
           except Exception as e:
               if attempt < max_retries - 1:
                   wait_time = 2 ** attempt  # 指数退避
                   print(f"⏳ 网络错误，{wait_time}秒后重试... (尝试 {attempt + 1}/{max_retries})")
                   time.sleep(wait_time)
               else:
                   raise e
   ```

3. **部分失败恢复**
   ```python
   def handle_partial_failure(results, owner, repo, branch):
       """处理部分失败的情况"""
       failed_files = [r for r in results if not r['success']]
       
       if failed_files:
           print(f"\n⚠️  {len(failed_files)} 个文件上传失败")
           print("失败的文件:")
           for file in failed_files:
               print(f"   - {file['file']}: {file.get('error', 'Unknown error')}")
           
           # 提供重试选项
           retry = input("是否重试失败的文件? [y/N]: ")
           if retry.lower() == 'y':
               return retry_failed_uploads(results, owner, repo, branch)
       
       return results
   ```

## 使用示例

### 示例1：提交单个文件

**用户请求**：提交 c/README.md 到GitHub

**执行步骤**：
1. 读取文件内容
2. 使用 `mcp_GitHub_create_or_update_file` 提交
3. 验证提交成功

### 示例2：批量提交文件夹

**用户请求**：提交 c 文件夹的所有代码文件

**执行步骤**：
1. 列出 c 文件夹所有文件
2. 过滤不需要的文件（.exe、.pyc等）
3. 读取所有需要提交的文件内容
4. 使用 `mcp_GitHub_push_files` 批量提交
5. 验证所有文件上传成功

### 示例3：提交到特定分支

**用户请求**：提交代码到 feature/new-feature 分支

**执行步骤**：
1. 检查分支是否存在
2. 如不存在，创建新分支
3. 提交代码到指定分支
4. 可选：创建Pull Request

## 最佳实践

### 文件选择原则

**应该提交的文件**：
- 源代码文件（.c, .cpp, .py, .js等）
- 配置文件（.json, .yaml, .xml等）
- 文档文件（README.md, .md等）
- 构建脚本（Makefile, CMakeLists.txt等）

**不应该提交的文件**：
- 编译产物（.exe, .o, .class等）
- 临时文件（.tmp, .bak等）
- IDE配置（.idea/, .vs/等）
- 敏感信息（.env, 密钥等）

### 提交信息规范

**好的提交信息**：
```
feat: 添加BFS迷宫搜索算法实现

- 实现队列数据结构
- 添加方向数组处理
- 完善注释说明
```

**不好的提交信息**：
```
update file
fix bug
```

### 错误处理策略

1. **空仓库错误**
   - 使用 `mcp_GitHub_create_or_update_file` 创建初始文件
   - 避免使用 `mcp_GitHub_push_files`

2. **认证失败**
   - 检查GitHub token配置
   - 验证仓库访问权限
   - 提供重新认证指导

3. **文件冲突**
   - 拉取最新代码
   - 解决冲突
   - 重新提交

4. **网络问题**
   - 重试提交
   - 检查网络连接
   - 使用备用方式提交

## 测试验证

### 单元测试要点

1. **文件读取测试**
   - 验证文件路径正确
   - 确认文件内容完整
   - 检查编码格式

2. **提交功能测试**
   - 测试单文件提交
   - 测试多文件批量提交
   - 测试不同文件类型

3. **错误处理测试**
   - 模拟空仓库场景
   - 模拟认证失败场景
   - 模拟网络错误场景

4. **验证测试**
   - 确认文件上传成功
   - 验证提交信息正确
   - 检查文件内容一致性

### 多文件上传测试

1. **并发上传测试**
   ```python
   def test_concurrent_upload():
       """测试并发上传功能"""
       print("🧪 测试并发上传功能...")
       
       # 创建测试文件
       test_files = create_test_files(count=10)
       
       # 测试不同并发数
       for concurrent in [1, 3, 5, 10]:
           print(f"\n测试并发数: {concurrent}")
           uploader = FileUploader(max_concurrent=concurrent)
           results = uploader.upload_files_concurrently(
               "test-owner", "test-repo", "main", test_files
           )
           
           # 验证结果
           assert len(results) == len(test_files), "文件数量不匹配"
           success_count = sum(1 for r in results if r['success'])
           assert success_count == len(test_files), f"成功上传数量不正确: {success_count}/{len(test_files)}"
           
           print(f"✅ 并发数 {concurrent} 测试通过")
   ```

2. **文件验证测试**
   ```python
   def test_file_validation():
       """测试文件验证功能"""
       print("🧪 测试文件验证功能...")
       
       # 测试各种文件类型
       test_cases = [
           ('test.c', True, "C源文件"),
           ('test.cpp', True, "C++源文件"),
           ('test.py', True, "Python源文件"),
           ('test.exe', False, "可执行文件"),
           ('test.pdf', False, "PDF文件"),
           ('large_file.txt', False, "超大文件"),
           ('sensitive.txt', False, "包含敏感信息")
       ]
       
       for filename, should_pass, description in test_cases:
           result = validate_file(filename)
           if should_pass and result['valid']:
               print(f"✅ {description} 验证通过")
           elif not should_pass and not result['valid']:
               print(f"✅ {description} 正确拒绝")
           else:
               print(f"❌ {description} 验证失败")
   ```

3. **错误恢复测试**
   ```python
   def test_error_recovery():
       """测试错误恢复机制"""
       print("🧪 测试错误恢复机制...")
       
       # 模拟部分失败场景
       test_files = create_test_files(count=5)
       
       # 模拟第3个文件失败
       original_upload = mock_upload_function(
           test_files, 
           fail_indices=[2]
       )
       
       # 测试重试机制
       results = retry_failed_uploads(
           original_upload, 
           "test-owner", 
           "test-repo", 
           "main"
       )
       
       # 验证重试结果
       success_count = sum(1 for r in results if r['success'])
       assert success_count == len(test_files), f"重试后仍有失败: {success_count}/{len(test_files)}"
       
       print("✅ 错误恢复机制测试通过")
   ```

4. **性能测试**
   ```python
   def test_upload_performance():
       """测试上传性能"""
       print("🧪 测试上传性能...")
       
       file_counts = [1, 5, 10, 20, 50]
       results = []
       
       for count in file_counts:
           test_files = create_test_files(count=count)
           
           start_time = time.time()
           uploader = FileUploader(max_concurrent=3)
           upload_results = uploader.upload_files_concurrently(
               "test-owner", "test-repo", "main", test_files
           )
           end_time = time.time()
           
           duration = end_time - start_time
           throughput = count / duration
           
           results.append({
               'count': count,
               'duration': duration,
               'throughput': throughput
           })
           
           print(f"📊 {count} 个文件: {duration:.2f}秒 ({throughput:.2f} 文件/秒)")
       
       # 分析性能趋势
       print("\n📈 性能分析:")
       for result in results:
           print(f"   {result['count']} 文件: {result['throughput']:.2f} 文件/秒")
   ```

5. **集成测试**
   ```python
   def test_integration():
       """完整流程集成测试"""
       print("🧪 测试完整流程...")
       
       # 测试场景1: 正常多文件上传
       print("\n场景1: 正常多文件上传")
       file_paths = ['test1.c', 'test2.cpp', 'test3.py']
       success = batch_upload_files(
           file_paths, 
           "test-owner", 
           "test-repo", 
           "main"
       )
       assert success, "场景1 失败"
       
       # 测试场景2: 包含无效文件
       print("\n场景2: 包含无效文件")
       file_paths = ['test1.c', 'test.exe', 'test2.cpp']
       success = batch_upload_files(
           file_paths, 
           "test-owner", 
           "test-repo", 
           "main"
       )
       assert success, "场景2 失败"
       
       # 测试场景3: 网络错误恢复
       print("\n场景3: 网络错误恢复")
       file_paths = ['test1.c', 'test2.cpp']
       with mock_network_errors():
           success = batch_upload_files(
               file_paths, 
               "test-owner", 
               "test-repo", 
               "main"
           )
           assert success, "场景3 失败"
       
       print("✅ 集成测试通过")
   ```

### 测试覆盖率

```python
def run_all_tests():
    """运行所有测试"""
    print("🚀 开始运行完整测试套件\n")
    
    tests = [
        ("文件验证测试", test_file_validation),
        ("并发上传测试", test_concurrent_upload),
        ("错误恢复测试", test_error_recovery),
        ("性能测试", test_upload_performance),
        ("集成测试", test_integration)
    ]
    
    passed = 0
    failed = 0
    
    for test_name, test_func in tests:
        try:
            test_func()
            passed += 1
            print(f"✅ {test_name} 通过\n")
        except Exception as e:
            failed += 1
            print(f"❌ {test_name} 失败: {str(e)}\n")
    
    print(f"\n📊 测试总结:")
    print(f"   总测试数: {len(tests)}")
    print(f"   通过: {passed}")
    print(f"   失败: {failed}")
    print(f"   覆盖率: {passed/len(tests)*100:.1f}%")
    
    if failed == 0:
        print("\n🎉 所有测试通过！")
    else:
        print(f"\n⚠️  有 {failed} 个测试失败")
```

## 代码示例

### 完整提交流程示例

```python
# 1. 检查仓库状态
git_status = check_git_status()

# 2. 获取文件列表
files = get_files_in_directory("c/")

# 3. 过滤文件
filtered_files = filter_files(files, exclude=[".exe", ".pyc", ".vs/"])

# 4. 读取文件内容
file_contents = {}
for file in filtered_files:
    file_contents[file] = read_file(file)

# 5. 提交到GitHub
try:
    result = mcp_GitHub_push_files(
        owner="username",
        repo="repository",
        branch="main",
        files=file_contents,
        message="提交代码文件"
    )
    print("提交成功！")
except Exception as e:
    print(f"提交失败: {e}")
    # 尝试备用方案
    fallback_submission(file_contents)
```

### 错误处理示例

```python
def submit_to_github(files, owner, repo, branch="main"):
    try:
        # 尝试批量提交
        result = mcp_GitHub_push_files(
            owner=owner,
            repo=repo,
            branch=branch,
            files=files,
            message="批量提交代码"
        )
        return {"success": True, "data": result}
    except Exception as e:
        if "empty" in str(e).lower():
            # 空仓库，逐个文件提交
            return handle_empty_repo(files, owner, repo, branch)
        elif "auth" in str(e).lower():
            # 认证失败
            return {"success": False, "error": "认证失败，请检查GitHub token"}
        else:
            # 其他错误
            return {"success": False, "error": str(e)}
```

## 注意事项

1. **权限要求**
   - 需要GitHub仓库的写权限
   - 需要配置有效的GitHub token
   - 确保网络连接正常

2. **文件大小限制**
   - 单文件大小不超过100MB
   - 大文件建议使用Git LFS
   - 避免提交二进制文件

3. **分支管理**
   - 推荐使用main分支
   - 重要功能使用feature分支
   - 提交前确认目标分支

4. **提交频率**
   - 小步快跑，频繁提交
   - 每个提交保持单一职责
   - 避免过大的提交

## 常见问题

**Q: 提交失败怎么办？**
A: 检查网络连接、GitHub token配置、仓库权限，然后重试。

**Q: 如何撤销提交？**
A: 使用 `git revert` 或 `git reset` 命令，然后重新推送。

**Q: 支持哪些文件类型？**
A: 支持所有文本文件，包括源代码、配置文件、文档等。

**Q: 可以提交到私有仓库吗？**
A: 可以，但需要相应的访问权限和认证。

## 相关工具

- `mcp_GitHub_create_or_update_file` - 创建或更新单个文件
- `mcp_GitHub_push_files` - 批量提交多个文件
- `mcp_GitHub_create_branch` - 创建新分支
- `mcp_GitHub_create_pull_request` - 创建Pull Request
- `git` 命令行工具 - 本地git操作
