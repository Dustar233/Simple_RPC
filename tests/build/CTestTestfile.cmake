# CMake generated Testfile for 
# Source directory: /home/dustar/Code/Simple_RPC/tests
# Build directory: /home/dustar/Code/Simple_RPC/tests/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(transport_test "/home/dustar/Code/Simple_RPC/tests/build/transport_tests")
set_tests_properties(transport_test PROPERTIES  _BACKTRACE_TRIPLES "/home/dustar/Code/Simple_RPC/tests/CMakeLists.txt;42;add_test;/home/dustar/Code/Simple_RPC/tests/CMakeLists.txt;0;")
add_test(client_test "/home/dustar/Code/Simple_RPC/tests/build/client_tests")
set_tests_properties(client_test PROPERTIES  _BACKTRACE_TRIPLES "/home/dustar/Code/Simple_RPC/tests/CMakeLists.txt;43;add_test;/home/dustar/Code/Simple_RPC/tests/CMakeLists.txt;0;")
add_test(server_test "/home/dustar/Code/Simple_RPC/tests/build/server_tests")
set_tests_properties(server_test PROPERTIES  _BACKTRACE_TRIPLES "/home/dustar/Code/Simple_RPC/tests/CMakeLists.txt;44;add_test;/home/dustar/Code/Simple_RPC/tests/CMakeLists.txt;0;")
subdirs("_deps/googletest-build")
