add_executable(pdr_test pdr_test.cc)

target_link_libraries(pdr_test
    gtest
    gtest_main
    libabc
)

gtest_discover_tests(pdr_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
