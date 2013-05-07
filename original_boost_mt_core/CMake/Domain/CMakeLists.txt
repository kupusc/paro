cmake_minimum_required (VERSION 2.8)
project (SUT_${DOMAIN_NAME})

#aux_source_directory(${Domain_dir}/src/targetagnostic/ TargetAgnosticSources)
#note: should be as above but some domains use targetagnostic improperly (e.g. FM)
file(GLOB_RECURSE TargetAgnosticSources ${Domain_dir}/src/targetagnostic/*.cpp)

aux_source_directory(${Domain_dir}/src/ServiceImpl ServiceImplSources)
aux_source_directory(${Domain_dir}/src/static/${STATIC_FSMrX_DIR} StaticTargetSources)
aux_source_directory(${Domain_dir}/src/${RHAPSODY_GENERATED_DIR} RhapsodySources)

# static/ may have subdirectories that are not release specific
file(GLOB_RECURSE StaticSources ${Domain_dir}/src/static/*.cpp)
file(GLOB_RECURSE StaticSourcesAllRel ${Domain_dir}/src/static/FSMr?/*.cpp)
list(REMOVE_ITEM StaticSources StaticSourcesAllRel)

add_library (
    ${PROJECT_NAME} 
    ${TargetAgnosticSources}
    ${StaticSources}
    ${ServiceImplSources}
    ${StaticTargetSources}
    ${RhapsodySources}
)