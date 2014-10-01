include_directories(${gtest_SOURCE_DIR}/include)
set(test_sources
    TestParameters.cpp
    TestKernel.cpp
)
add_executable(tests ${test_sources})
target_link_libraries(tests gtest_main)