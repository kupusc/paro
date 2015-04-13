cmake_minimum_required (VERSION 2.8)
project (tdd-boost-turtle-training)

set (TDD_BOOST_TURTLE_TRAINING_VERSION_MAJOR 1)
set (TDD_BOOST_TURTLE_TRAINING_VERSION_MINOR 0)

configure_file (
    ${PROJECT_SOURCE_DIR}/config.h.in
    ${PROJECT_BINARY_DIR}/config.h
)

add_definitions(-include config.h -std=c++11)

set(BUILD_SHARED_LIBS     true              )

find_package( Boost 1.46.1 REQUIRED COMPONENTS unit_test_framework thread program_options system)

include_directories(
    ${PROJECT_BINARY_DIR}
    ${Boost_INCLUDE_DIRS}
    test_framework
    .
)

add_library(   bug-introducer   mutation/bug-introducer.cc  )
add_library(   implementation   implementation/implementation.cc implementation/implementation-other-part.cc)
add_library(   third-party      third-party.cpp    )
add_executable(test-application implementation/implementation-tests.cc)
add_executable(mutation-tester  mutation/tests-tester.cc )

set_target_properties(implementation
    PROPERTIES COMPILE_FLAGS "-fprofile-arcs -ftest-coverage"
	       LINK_FLAGS "-coverage"
)
   
target_link_libraries(test-application implementation third-party -Wl,--no-as-needed ${Boost_LIBRARIES} -Wl,--as-needed bug-introducer pthread)
target_link_libraries(mutation-tester -Wl,--no-as-needed ${Boost_LIBRARIES}               )

get_filename_component(${CMAKE_SOURCE_DIRECTORY}/calculator_tests_path test-application ABSOLUTE)

add_custom_target(mutation-testing
    COMMAND mutation-tester --input ${CMAKE_BINARY_DIR}/test-application --verbose
)

add_custom_target(implementation-testing
    COMMAND test-application
)

add_custom_target(coverage
    COMMAND find . -name \"*.gcda\" | xargs rm -f
    COMMAND find . -name \"*.html\" | xargs rm -f
    COMMAND cmake --build . --target implementation-testing
    COMMAND lcov -c -d . -o coverage.info
    COMMAND lcov --remove coverage.info "*/usr/*" -o coverage.info
    COMMAND lcov --remove coverage.info "*/opt/*" -o coverage.info
    COMMAND lcov --remove coverage.info "*/boost/*" -o coverage.info
    COMMAND lcov --remove coverage.info "bug-introducer.*" -o coverage.info
    COMMAND genhtml --legend coverage.info
)

