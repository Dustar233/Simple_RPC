
#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include <string>
#include "simple_rpc/server/rpc_server.h"

using namespace s_rpc;

class RPC_serverTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 在每个测试前执行
    }

    void TearDown() override {
        // 在每个测试后执行
    }
};

// 测试 RPC_server 构造函数
TEST_F(RPC_serverTest, Constructor) {
    RPC_server server(8080);
    // 构造函数应该正确初始化 port
}

// 测试 register_method 功能
TEST_F(RPC_serverTest, RegisterMethod) {
    RPC_server server(8081);

    // 注册一个简单的方法
    server.register_method("echo", [](const std::string& args) -> std::string {
        return args;
    });

    // 注册一个复杂的方法
    server.register_method("add", [](const std::string& args) -> std::string {
        // 假设 args 格式为 {"a":1,"b":2}
        // 实际实现需要解析 JSON
        return "3";
    });

    // 注册多个方法
    server.register_method("method1", [](const std::string& args) -> std::string {
        return "result1";
    });

    server.register_method("method2", [](const std::string& args) -> std::string {
        return "result2";
    });
}

// 测试注册相同名称的方法
TEST_F(RPC_serverTest, RegisterDuplicateMethod) {
    RPC_server server(8082);

    server.register_method("test", [](const std::string& args) -> std::string {
        return "first";
    });

    // 注册同名方法应该覆盖前一个
    server.register_method("test", [](const std::string& args) -> std::string {
        return "second";
    });
}

// 测试注册空名称的方法
TEST_F(RPC_serverTest, RegisterEmptyMethodName) {
    RPC_server server(8083);

    // 注册空名称方法的行为取决于实现
    server.register_method("", [](const std::string& args) -> std::string {
        return "result";
    });
}

// 测试方法处理空参数
TEST_F(RPC_serverTest, MethodWithEmptyArgs) {
    RPC_server server(8084);

    server.register_method("empty_args", [](const std::string& args) -> std::string {
        EXPECT_TRUE(args.empty());
        return "handled_empty_args";
    });
}

// 测试方法处理特殊字符
TEST_F(RPC_serverTest, MethodWithSpecialChars) {
    RPC_server server(8085);

    server.register_method("special_chars", [](const std::string& args) -> std::string {
        // 验证特殊字符是否正确传递
        return args;
    });
}

// 测试方法返回空字符串
TEST_F(RPC_serverTest, MethodReturningEmptyString) {
    RPC_server server(8086);

    server.register_method("empty_return", [](const std::string& args) -> std::string {
        return "";
    });
}

// 测试方法返回大数据
TEST_F(RPC_serverTest, MethodReturningLargeData) {
    RPC_server server(8087);

    server.register_method("large_return", [](const std::string& args) -> std::string {
        return std::string(1024, 'A'); // 返回 1KB 数据
    });
}

// 测试方法抛出异常
TEST_F(RPC_serverTest, MethodThrowingException) {
    RPC_server server(8088);

    server.register_method("throwing", [](const std::string& args) -> std::string {
        throw std::runtime_error("Test exception");
        return "unreachable";
    });
}

// 测试多线程环境下的方法注册
TEST_F(RPC_serverTest, ConcurrentRegister) {
    RPC_server server(8089);

    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([&server, i]() {
            std::string method_name = "method_" + std::to_string(i);
            server.register_method(method_name, [i](const std::string& args) -> std::string {
                return std::to_string(i);
            });
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }
}

// 测试服务器运行（需要单独的线程）
TEST_F(RPC_serverTest, ServerRun) {
    RPC_server server(8090);

    // 注册测试方法
    server.register_method("test", [](const std::string& args) -> std::string {
        return "test_result";
    });

    // 在另一个线程中启动服务器
    std::thread server_thread([&server]() {
        server.run();
    });

    // 给服务器时间启动
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // 在实际测试中，这里应该创建客户端并调用方法
    // 然后验证结果

    // 清理：服务器线程可能需要特殊处理来停止
    // server_thread.detach(); // 或使用其他机制停止服务器
}

// 测试多个服务器实例
TEST_F(RPC_serverTest, MultipleServers) {
    RPC_server server1(8091);
    RPC_server server2(8092);

    server1.register_method("method1", [](const std::string& args) -> std::string {
        return "server1";
    });

    server2.register_method("method2", [](const std::string& args) -> std::string {
        return "server2";
    });
}

// 测试方法链式调用
TEST_F(RPC_serverTest, ChainedMethodCalls) {
    RPC_server server(8093);

    server.register_method("step1", [](const std::string& args) -> std::string {
        return "step1_result";
    });

    server.register_method("step2", [](const std::string& args) -> std::string {
        return "step2_result";
    });

    server.register_method("step3", [](const std::string& args) -> std::string {
        return "step3_result";
    });
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
