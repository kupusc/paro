cmake_minimum_required (VERSION 2.8)
project (example)

find_package( Boost COMPONENTS unit_test_framework thread )

include_directories(
    ${Boost_INCLUDE_DIRS}
    .
)

add_executable(boost-playground boost-playground.cc)

target_link_libraries(boost-playground 
    ${Boost_LIBRARIES}
)

add_custom_target(run
    COMMAND boost-playground
    COMMENT "Running all executables"
)