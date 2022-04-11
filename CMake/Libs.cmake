# Variables for use later
set(AENGINE_LIB_DEPS)
set(AENGINE_SRC_DEPS)

# GLFW
include_directories(${LIB_DIR}/GLFW/include)
if (WIN32)
    set(GLFW_LIB ${LIB_DIR}/GLFW/lib-vc2022/${TARGET_ARCH}/glfw3dll.lib)
    list(APPEND AENGINE_LIB_DEPS ${GLFW_LIB})
elseif (UNIX)
    find_package(glfw3 3.3.4 REQUIRED)
    set(GLFW_LIB glfw)
    list(APPEND AENGINE_LIB_DEPS ${GLFW_LIB})
endif()

# dirent Windows implementation
if (WIN32)
    include_directories(${LIB_DIR}/dirent)
endif()

# STB
include_directories(${LIB_DIR}/stb/include)
list(APPEND AENGINE_SRC_DEPS ${LIB_DIR}/stb/src/stb_image.c)

# GLM
include_directories(${LIB_DIR}/glm)

# YAML-CPP
include_directories(${LIB_DIR}/yaml-cpp/include)
if (WIN32)
    link_directories(${LIB_DIR}/yaml-cpp/lib)
endif()

# Freetype
include_directories(${LIB_DIR}/freetype/include)
if (WIN32)
    #link_directories(${LIB_DIR}/freetype/lib/freetype.lib)
    list(APPEND AENGINE_LIB_DEPS ${LIB_DIR}/freetype/lib/freetype.lib)
endif()

# GLAD
include(${CMAKE_SOURCE_DIR}/CMake/Glad.cmake)

# ImGui
include(${CMAKE_SOURCE_DIR}/CMake/ImGui.cmake)
