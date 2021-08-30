# Variables for use later
set(AENGINE_LIB_DEPS)
set(AENGINE_SRC_DEPS)

# GLFW
include_directories(${LIB_DIR}/GLFW/include)
if (WIN32)
    if (TARGET_ARCH STREQUAL x86_64) # 64-bit lib files
        list(APPEND AENGINE_LIB_DEPS ${LIB_DIR}/GLFW/lib-vc2019/glfw3-x64.lib)
    elseif(TARGET_ARCH STREQUAL i386) # 32-bit lib files
        list(APPEND AENGINE_LIB_DEPS ${LIB_DIR}/GLFW/lib-vc2019/glfw3-x86.lib)
    endif()
elseif (UNIX)
    find_package(glfw3 3.3.4 REQUIRED)
    list(APPEND AENGINE_LIB_DEPS glfw)
endif()

# dirent Windows implementation
if (WIN32)
    include_directories(${LIB_DIR}/dirent)
endif()

# GLAD
include_directories(${LIB_DIR}/glad/include)
list(APPEND AENGINE_SRC_DEPS ${LIB_DIR}/glad/src/glad.c)

# STB
include_directories(${LIB_DIR}/stb/include)
list(APPEND AENGINE_SRC_DEPS ${LIB_DIR}/stb/src/stb_image.c)

# GLM
include_directories(${LIB_DIR}/glm)

# ImGui
include_directories(${LIB_DIR}/imgui)
file(GLOB IMGUI_SOURCES ${LIB_DIR}/imgui/*.cpp)
list(APPEND AENGINE_SRC_DEPS ${IMGUI_SOURCES})
