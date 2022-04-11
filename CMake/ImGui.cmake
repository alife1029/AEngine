project(imgui)
include_directories(${LIB_DIR}/imgui)
file(GLOB IMGUI_SOURCES ${LIB_DIR}/imgui/*.cpp)
add_library(${PROJECT_NAME} SHARED ${IMGUI_SOURCES})
target_compile_definitions(${PROJECT_NAME} PRIVATE -DGLAD_GLAPI_EXPORT -DIMGUI_IMPL_OPENGL_LOADER_GLAD -D_GLFW_BUILD_DLL -DIMGUI_BUILD_DLL)
target_link_libraries(${PROJECT_NAME} ${GLFW_LIB} glad)

list(APPEND AENGINE_LIB_DEPS imgui)
