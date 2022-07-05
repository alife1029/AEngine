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
if (WIN32)
    include_directories(${LIB_DIR}/yaml-cpp/include)
    link_directories(${LIB_DIR}/yaml-cpp/lib)
elseif(UNIX)
    find_package(yaml-cpp 0.7.0 REQUIRED)
    list(APPEND AENGINE_LIB_DEPS yaml-cpp)
endif()

# Freetype
if (WIN32)
    include_directories(${LIB_DIR}/freetype/include)
    list(APPEND AENGINE_LIB_DEPS ${LIB_DIR}/freetype/lib/freetype.lib)
elseif(UNIX)
    find_package(freetype 2.10.4 REQUIRED)
    list(APPEND AENGINE_LIB_DEPS freetype)
endif()

# GLAD
include(${CMAKE_SOURCE_DIR}/CMake/Glad.cmake)

# ImGui
include(${CMAKE_SOURCE_DIR}/CMake/ImGui.cmake)
