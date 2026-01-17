
# Simple_RPC 单元测试指南

## 概述

本目录包含 Simple_RPC 项目的所有单元测试。测试使用 Google Test 框架编写，覆盖了以下模块：

- **transport**: TCP socket 通信测试
- **client**: RPC 客户端测试
- **server**: RPC 服务器测试

## 目录结构

```
tests/
├── CMakeLists.txt           # CMake 构建配置
├── README.md               # 本文档
├── transport/
│   └── TCP_socket_test.cpp # transport 模块测试
├── client/
│   └── rpc_client_test.cpp # client 模块测试
└── server/
    └── rpc_server_test.cpp # server 模块测试
```

## 依赖项

- CMake 3.10 或更高版本
- C++11 或更高版本
- Google Test 1.12.1（会自动下载）

## 构建和运行测试

### 1. 创建构建目录

```bash
cd tests
mkdir build
cd build
```

### 2. 配置 CMake

```bash
cmake ..
```

这将自动下载 Google Test 框架（如果尚未下载）。

### 3. 编译测试

```bash
make
```

### 4. 运行所有测试

```bash
ctest
```

或者运行单个测试套件：

```bash
# 运行 transport 测试
./transport_tests

# 运行 client 测试
./client_tests

# 运行 server 测试
./server_tests
```

## 测试说明

### Transport 模块测试 (TCP_socket_test.cpp)

测试 TCP socket 的基本功能，包括：

- 构造和析构
- 服务器监听 (TCP_listen)
- 客户端连接 (TCP_connect)
- 连接接受 (TCP_accept)
- 数据发送和接收 (send_data/receive_data)
- 错误处理（无效连接、无效主机等）
- 大数据传输
- 多次连接

### Client 模块测试 (rpc_client_test.cpp)

测试 RPC 客户端功能，包括：

- 客户端构造
- 方法调用 (call)
- 空参数调用
- 带参数调用
- 大数据参数
- 特殊字符和 Unicode 参数
- 多次调用
- 不同主机的连接

**注意**: 部分 client 测试需要运行中的 RPC 服务器才能完整执行。

### Server 模块测试 (rpc_server_test.cpp)

测试 RPC 服务器功能，包括：

- 服务器构造
- 方法注册 (register_method)
- 重复方法注册
- 空参数处理
- 特殊字符处理
- 空返回值
- 大数据返回
- 异常处理
- 并发注册
- 服务器运行
- 多服务器实例

**注意**: 部分服务器测试可能需要特殊的设置或模拟环境。

## 测试覆盖率

当前测试覆盖了以下方面：

- 基本功能测试
- 边界条件测试
- 错误处理测试
- 并发测试（部分）

## 注意事项

1. **端口冲突**: 某些测试使用固定端口号。确保这些端口在测试运行时未被其他程序占用。

2. **服务器依赖**: client 和 server 的某些测试需要相互配合才能完整运行。建议先启动服务器，再运行客户端测试。

3. **超时设置**: 测试中使用了一些 sleep 来等待服务器启动或连接建立。如果测试环境较慢，可能需要调整这些超时值。

4. **网络环境**: 测试假设本地网络环境正常。如果网络配置有问题，某些测试可能会失败。

## 添加新测试

要添加新的测试：

1. 在相应的模块目录下创建新的测试文件
2. 在 `CMakeLists.txt` 中添加新的测试可执行文件
3. 使用 Google Test 的断言宏（EXPECT_EQ, ASSERT_TRUE 等）
4. 遵循现有的测试命名约定

## 故障排除

### 测试失败

如果测试失败，检查：

1. 端口是否被占用
2. 防火墙是否阻止连接
3. 网络环境是否正常
4. 所有依赖项是否正确安装

### 编译错误

如果遇到编译错误，检查：

1. CMake 版本是否符合要求
2. C++ 标准是否设置为 C++11 或更高
3. 头文件路径是否正确

## 贡献

欢迎贡献新的测试用例或改进现有测试。在提交 PR 前，请确保：

1. 所有测试通过
2. 新测试有清晰的文档说明
3. 测试命名遵循约定
4. 测试覆盖了新的功能或边界条件

## 许可证

本测试套件遵循与主项目相同的许可证。
