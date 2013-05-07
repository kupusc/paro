cmake_minimum_required (VERSION 2.8)
project (SSW_FML_Workaround)

set(SSW_dir ${OAM_ROOT}/SSW_SupportSoftware)

include_directories(
    ${FML_dir}/src/${RHAPSODY_GENERATED_DIR}
)

# gcc has a link order problem, combined with OAM's strong coupling (this includes FML) this project
# has to be included before FML

add_library(${PROJECT_NAME}
    ${SSW_dir}/src/Logger/src/LoggerPc.cpp
    ${SSW_dir}/src/SSWinit/src/Init.cpp
)