add_executable(tictactoe_tests tictactoe_tests.cpp)
target_link_libraries(tictactoe_tests PRIVATE tictactoe_lib GTest::gtest_main)

# Включаем систему тестирования
enable_testing()

# Автоматически обнаруживает все тесты Google Test
include(GoogleTest)
gtest_discover_tests(tictactoe_tests)

# Альтернатива (если не работает gtest_discover_tests):
# add_test(NAME tictactoe_tests COMMAND tictactoe_tests)