cmake_minimum_required (VERSION 2.8)
project (tdd-boost-turtle-training)

set (TDD_BOOST_TURTLE_TRAINING_VERSION_MAJOR 1)
set (TDD_BOOST_TURTLE_TRAINING_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
    ${PROJECT_SOURCE_DIR}/config.h.in
    ${PROJECT_BINARY_DIR}/config.h
)

add_definitions(-include config.h)

set(BUILD_SHARED_LIBS true)
set(Boost_NO_SYSTEM_PATHS true)
set(BOOST_ROOT /work/boost_1.46.1)

find_package( Boost 1.46.1 COMPONENTS unit_test_framework thread program_options)

include_directories(
    ${PROJECT_BINARY_DIR}
    ${Boost_INCLUDE_DIRS}
    original_boost_mt_core/test_framework
    .
)

add_executable(boost-playground boost-playground.cc)
add_library(calculator calculator.cc)
add_library(bogus-calculator bogus-calculator.cc)
add_executable(calculator-tests calculator-tests.cc)
add_executable(tests-tester tests-tester.cc)

set_target_properties(bogus-calculator 
    PROPERTIES COMPILE_FLAGS "-fprofile-arcs -ftest-coverage"
	       LINK_FLAGS "-coverage"
)
   
target_link_libraries(boost-playground ${Boost_LIBRARIES})
target_link_libraries(calculator-tests bogus-calculator ${Boost_LIBRARIES})
target_link_libraries(tests-tester ${Boost_LIBRARIES})

get_filename_component(calculator_tests_path calculator-tests ABSOLUTE)

add_custom_target(test
    COMMAND tests-tester --input ${CMAKE_BINARY_DIR}/calculator-tests --verbose
    DEPEND  clean_coverage
    COMMENT "Running all executables"
)

add_custom_target(run
    COMMAND calculator-tests
    DEPEND clean_coverage
)

add_custom_target(coverage
    COMMAND lcov -c -d . -o coverage.info
    COMMAND lcov --remove coverage.info "*/usr/*" -o coverage.info
    COMMAND lcov --remove coverage.info "*/opt/*" -o coverage.info
    COMMAND lcov --remove coverage.info "*/boost/*" -o coverage.info
    COMMAND lcov --remove coverage.info "bug-introducer.hpp" -o coverage.info
    COMMAND genhtml --legend coverage.info
)

add_custom_target(clean_coverage
    COMMAND find . -name *.gcda | xargs rm -f
)
