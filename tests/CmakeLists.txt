project(Test)
include(CTest)
enable_testing()
include_directories(../include)
aux_source_directory(. SRC)
# 将我们写的tests编译成可执行文件
add_executable(${PROJECT_NAME} ${SRC})
 add_dependencies(${PROJECT_NAME} LxSocket)

find_package(GTest CONFIG REQUIRED)
# target_link_libraries( ${PROJECT_NAME} PRIVATE GTest::gtest GTest::gtest_main GTest::gmock  GTest::gmock_main)
 target_link_libraries( ${PROJECT_NAME} PRIVATE GTest::gmock_main GTest::gtest GTest::gtest_main GTest::gmock  )
target_link_libraries(${PROJECT_NAME} PUBLIC LxSocket)
# target_include_directories(${PROJECT_NAME} PUBLIC "../LibMyJson")

add_test(multiply_gtests ${PROJECT_NAME})
