add_executable(tictactoe_tests tictactoe_tests.cpp)
target_link_libraries(tictactoe_tests PRIVATE tictactoe_lib GTest::gtest_main)

enable_testing()

include(GoogleTest)
gtest_discover_tests(tictactoe_tests)