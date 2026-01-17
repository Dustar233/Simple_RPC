
#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include <string>
#include "simple_rpc/transport/TCP_socket.h"

using namespace s_rpc::transport;

class TCP_socketTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 在每个测试前执行
    }

    void TearDown() override {
        // 在每个测试后执行
    }
};

// 测试 TCP_socket 构造和析构
TEST_F(TCP_socketTest, ConstructorDestructor) {
    TCP_socket socket;
    // 构造函数应该创建一个有效的 socket
    // 析构函数应该正确关闭 socket
}

// 测试 TCP_listen 功能
TEST_F(TCP_socketTest, TCPListen) {
    TCP_socket server_socket;
    bool result = server_socket.TCP_listen(8080);
    EXPECT_TRUE(result) << "TCP_listen should return true for valid port";
}

// 测试 TCP_connect 功能
TEST_F(TCP_socketTest, TCPConnect) {
    // 先启动一个服务器
    TCP_socket server_socket;
    ASSERT_TRUE(server_socket.TCP_listen(8081)) << "Failed to start server";

    // 给服务器一点时间启动
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // 客户端连接
    TCP_socket client_socket;
    bool result = client_socket.TCP_connect("127.0.0.1", 8081);
    EXPECT_TRUE(result) << "TCP_connect should succeed when server is listening";
}

// 测试无效的 TCP_connect
TEST_F(TCP_socketTest, TCPConnectInvalid) {
    TCP_socket client_socket;
    bool result = client_socket.TCP_connect("127.0.0.1", 9999);
    EXPECT_FALSE(result) << "TCP_connect should fail when no server is listening";
}

// 测试无效的主机地址
TEST_F(TCP_socketTest, TCPConnectInvalidHost) {
    TCP_socket client_socket;
    bool result = client_socket.TCP_connect("invalid.host.address", 8080);
    EXPECT_FALSE(result) << "TCP_connect should fail for invalid host address";
}

// 测试 TCP_accept 功能
TEST_F(TCP_socketTest, TCPAccept) {
    TCP_socket server_socket;
    ASSERT_TRUE(server_socket.TCP_listen(8082)) << "Failed to start server";

    // 在另一个线程中启动客户端连接
    std::thread client_thread([]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        TCP_socket client_socket;
        client_socket.TCP_connect("127.0.0.1", 8082);
    });

    // 服务器接受连接
    bool result = server_socket.TCP_accept();
    EXPECT_TRUE(result) << "TCP_accept should succeed when client connects";

    client_thread.join();
}

// 测试 send_data 和 receive_data 功能
TEST_F(TCP_socketTest, SendAndReceiveData) {
    const std::string test_message = "Hello, RPC!";

    // 启动服务器
    TCP_socket server_socket;
    ASSERT_TRUE(server_socket.TCP_listen(8083)) << "Failed to start server";

    // 在另一个线程中启动客户端
    std::thread client_thread([test_message]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        TCP_socket client_socket;
        ASSERT_TRUE(client_socket.TCP_connect("127.0.0.1", 8083)) << "Client failed to connect";

        // 发送数据
        bool send_result = client_socket.send_data(test_message);
        EXPECT_TRUE(send_result) << "send_data should return true on success";
    });

    // 服务器接受连接并接收数据
    ASSERT_TRUE(server_socket.TCP_accept()) << "Server failed to accept connection";

    // 等待数据到达
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::string received = server_socket.receive_data();
    EXPECT_FALSE(received.empty()) << "receive_data should return non-empty string";

    client_thread.join();
}

// 测试空数据发送
TEST_F(TCP_socketTest, SendEmptyData) {
    TCP_socket client_socket;
    ASSERT_TRUE(client_socket.TCP_connect("127.0.0.1", 8080)) << "Client failed to connect";

    bool result = client_socket.send_data("");
    EXPECT_TRUE(result) << "send_data should handle empty string";
}

// 测试大数据发送
TEST_F(TCP_socketTest, SendLargeData) {
    std::string large_data(1024, 'A'); // 1KB 数据

    // 启动服务器
    TCP_socket server_socket;
    ASSERT_TRUE(server_socket.TCP_listen(8084)) << "Failed to start server";

    // 在另一个线程中启动客户端
    std::thread client_thread([large_data]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        TCP_socket client_socket;
        ASSERT_TRUE(client_socket.TCP_connect("127.0.0.1", 8084)) << "Client failed to connect";

        bool send_result = client_socket.send_data(large_data);
        EXPECT_TRUE(send_result) << "send_data should handle large data";
    });

    // 服务器接受连接并接收数据
    ASSERT_TRUE(server_socket.TCP_accept()) << "Server failed to accept connection";

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::string received = server_socket.receive_data();
    EXPECT_FALSE(received.empty()) << "receive_data should return non-empty string for large data";

    client_thread.join();
}

// 测试多次连接
TEST_F(TCP_socketTest, MultipleConnections) {
    TCP_socket server_socket;
    ASSERT_TRUE(server_socket.TCP_listen(8085)) << "Failed to start server";

    const int num_connections = 3;
    std::vector<std::thread> client_threads;

    for (int i = 0; i < num_connections; ++i) {
        client_threads.emplace_back([i]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(100 * (i + 1)));
            TCP_socket client_socket;
            client_socket.TCP_connect("127.0.0.1", 8085);
        });
    }

    for (int i = 0; i < num_connections; ++i) {
        EXPECT_TRUE(server_socket.TCP_accept()) << "Server should accept connection " << i;
    }

    for (auto& thread : client_threads) {
        thread.join();
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
