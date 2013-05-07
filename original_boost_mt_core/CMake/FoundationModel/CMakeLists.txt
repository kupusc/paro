cmake_minimum_required (VERSION 2.8)
project (SUT_FoundationModel)

aux_source_directory(${FML_dir}/src/targetagnostic/ TargetAgnosticSources)
aux_source_directory(${FML_dir}/src/static/ StaticSources)
aux_source_directory(${FML_dir}/src/static/${STATIC_FSMrX_DIR} StaticTargetSources)
aux_source_directory(${FML_dir}/src/${RHAPSODY_GENERATED_DIR} RhapsodySources)

#disgusting workarounds
list(REMOVE_ITEM RhapsodySources ${FML_dir}/src/${RHAPSODY_GENERATED_DIR}/FORE_Global_Pkg.cpp)
list(REMOVE_ITEM RhapsodySources ${FML_dir}/src/${RHAPSODY_GENERATED_DIR}/DBLogger.cpp)
list(REMOVE_ITEM RhapsodySources ${FML_dir}/src/${RHAPSODY_GENERATED_DIR}/Registry.cpp)

add_library (
    ${PROJECT_NAME} 
    ${TargetAgnosticSources}
    ${StaticSources}
    ${StaticTargetSources}
    ${RhapsodySources}
)