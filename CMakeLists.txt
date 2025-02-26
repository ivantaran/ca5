cmake_minimum_required(VERSION 3.7.2)

project(ca5 VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_CXX_CLANG_TIDY
# clang-tidy;-header-filter=.*;
# -checks=*,-llvmlibc-restrict-system-libc-headers,-fuchsia-default-arguments,-cppcoreguidelines-avoid-magic-numbers,-readability-magic-numbers,-llvm-header-guard;)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 REQUIRED COMPONENTS Core)
find_package(Qt5 REQUIRED COMPONENTS Gui)
find_package(Qt5 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOUIC_SEARCH_PATHS "src/ui")

file(GLOB SOURCES
    "src/*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

add_executable(test1 tests/test1.cpp src/myreader.cpp)
target_include_directories(test1 PRIVATE src)
enable_testing()
add_test(test1 test1 ${PROJECT_SOURCE_DIR}/tests/data.csv)
