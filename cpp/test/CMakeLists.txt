find_package(Catch2 3 REQUIRED)

add_executable(tests test_001.cpp)

target_link_libraries(tests PRIVATE base91-cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

include(Catch)
catch_discover_tests(tests)