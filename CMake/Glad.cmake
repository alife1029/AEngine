project(glad)
include_directories(${LIB_DIR}/glad/include)
add_library(${PROJECT_NAME} SHARED ${LIB_DIR}/glad/src/glad.c)
target_compile_definitions(${PROJECT_NAME} PRIVATE -DGLAD_GLAPI_EXPORT -DGLAD_GLAPI_EXPORT_BUILD)

list(APPEND AENGINE_LIB_DEPS glad)
