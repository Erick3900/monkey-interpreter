cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
    monkey-interpreter
    VERSION 0.0.1
    DESCRIPTION "Monkey lang interpreter created by following 'The Interpreter Book' by Thorsten Ball"
    LANGUAGES CXX
)

set(PROJECT_AUTHOR "Erick Saúl")
set(PROJECT_AUTHOR_GITHUB "@Erick3900")

add_subdirectory(configured_files)

find_package(fmt CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(docopt CONFIG REQUIRED)
find_package(range-v3 CONFIG REQUIRED)
find_package(tl-expected CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES "src/monkey/**.cpp")
file(GLOB_RECURSE TESTS "tests/**.cpp")

add_library(
    ${PROJECT_NAME} STATIC
        ${SOURCES}
)

target_link_libraries(
    ${PROJECT_NAME} PUBLIC
        fmt::fmt
        tl::expected
        docopt::docopt
        range-v3::range-v3
)

target_include_directories(
    ${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/monkey
        ${CMAKE_CURRENT_SOURCE_DIR}/include/common
        ${CMAKE_BINARY_DIR}/configured_files/include
)


file(GLOB_RECURSE INTERPRETER_SOURCES "src/interpreter/**.cpp")

add_executable(
    "monkey"
        main.cpp
        ${INTERPRETER_SOURCES}
)

target_link_libraries(
    "monkey" PRIVATE
        ${PROJECT_NAME}
)

target_include_directories(
    "monkey" PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/common
        ${CMAKE_CURRENT_SOURCE_DIR}/include/interpreter
)

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
        OUTPUT_NAME "monkey"
)


enable_testing()

foreach(FILE IN LISTS TESTS)
    cmake_path(GET FILE PARENT_PATH PARENT)
    cmake_path(GET PARENT STEM PARENT_STEM)
    cmake_path(GET FILE STEM FILE_STEM)

    if (${PARENT_STEM} MATCHES "tests")
        set(TestName ${FILE_STEM})
    else()
        set(TestName "${PARENT_STEM}.${FILE_STEM}")
    endif()

    add_executable(
        ${TestName}_test
            ${FILE}
    )

    target_include_directories(
        ${TestName}_test PRIVATE
            tests/include
    )

    target_link_libraries(
        ${TestName}_test PRIVATE
            GTest::gtest
            ${PROJECT_NAME}
    )

    add_test(${TestName} ${TestName}_test)
endforeach()
