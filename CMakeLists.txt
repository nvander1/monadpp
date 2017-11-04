cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(PROJECT_NAME_STR monadpp)
set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)
project(${PROJECT_NAME_STR} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(maybe Maybe.cpp)
add_executable(${PROJECT_TEST_NAME} TestMonad.cpp)
target_compile_features(${PROJECT_TEST_NAME} PRIVATE cxx_constexpr cxx_variadic_templates cxx_std_17 cxx_user_literals)

if(CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(${PROJECT_TEST_NAME}
        PUBLIC
        -Wall -Wextra -Werror -pedantic -Winline -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-declarations -Wmissing-include-dirs -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror
        )
endif()

enable_testing()
find_package(GTest REQUIRED)
target_link_libraries(${PROJECT_TEST_NAME} PRIVATE GTest::GTest GTest::Main)
add_test(TestMonad ${PROJECT_TEST_NAME})
