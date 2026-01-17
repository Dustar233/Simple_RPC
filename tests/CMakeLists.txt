
cmake_minimum_required(VERSION 3.10)
project(Simple_RPC_Tests)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加 Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# 对于 Windows: 防止覆盖父项目的编译器/链接器设置
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 包含项目头文件
include_directories(${CMAKE_SOURCE_DIR}/../include)

# 添加被测试的源文件
add_library(simple_rpc_lib STATIC
    ../src/transport/TCP_socket.cpp
)

# 添加测试可执行文件
add_executable(transport_tests transport/TCP_socket_test.cpp)
target_link_libraries(transport_tests gtest_main simple_rpc_lib)

add_executable(client_tests client/rpc_client_test.cpp)
target_link_libraries(client_tests gtest_main simple_rpc_lib)

add_executable(server_tests server/rpc_server_test.cpp)
target_link_libraries(server_tests gtest_main simple_rpc_lib)

# 启用测试
enable_testing()

# 添加测试
add_test(NAME transport_test COMMAND transport_tests)
add_test(NAME client_test COMMAND client_tests)
add_test(NAME server_test COMMAND server_tests)
