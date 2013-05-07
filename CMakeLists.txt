cmake_minimum_required (VERSION 2.8)
project (example)

set(BUILD_SHARED_LIBS true)

find_package( Boost COMPONENTS unit_test_framework thread program_options)

include_directories(
    ${Boost_INCLUDE_DIRS}
    .
)

add_executable(boost-playground boost-playground.cc)
add_library(calculator calculator.cc)
add_library(bogus-calculator bogus-calculator.cc)
add_executable(calculator-tests calculator-tests.cc)

target_link_libraries(boost-playground ${Boost_LIBRARIES})
target_link_libraries(calculator-tests bogus-calculator ${Boost_LIBRARIES})

add_custom_target(run
    COMMAND calculator-tests
    COMMAND boost-playground
    COMMENT "Running all executables"
)