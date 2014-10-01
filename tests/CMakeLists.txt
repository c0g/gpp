include_directories(${GTEST_INCLUDE_DIRS})
set(test_sources
    TestParameters.cpp
    TestKernel.cpp
)
add_executable(tests ${test_sources})
target_link_libraries(tests
        ${GTEST_LIBS_DIR}/libgtest.a
        ${GTEST_LIBS_DIR}/libgtest_main.a
        pthread
    )
