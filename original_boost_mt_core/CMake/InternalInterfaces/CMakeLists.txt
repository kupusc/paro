cmake_minimum_required (VERSION 2.8)
project (SUT_InternalInterfaces)

aux_source_directory(${II_dir}/src/${RHAPSODY_GENERATED_DIR} RhapsodySources)

add_library (
    ${PROJECT_NAME} 
    ${RhapsodySources}
)