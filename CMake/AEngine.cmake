# Collect project sources
file(GLOB PROJECT_SOURCES 
    ${PROJECT_DIR}/src/*.c
    ${PROJECT_DIR}/src/*.cpp
    ${PROJECT_DIR}/src/Application/*.cpp
    ${PROJECT_DIR}/src/Exception/*.cpp
    ${PROJECT_DIR}/src/Graphics/*.cpp
    ${PROJECT_DIR}/src/Input/*.cpp
    ${PROJECT_DIR}/src/Scene/*.cpp
    ${PROJECT_DIR}/src/Scene/Components/*.cpp
    ${PROJECT_DIR}/src/Utils/*.cpp
    )
include_directories(${PROJECT_DIR}/include)

# Architecture predefines
set(ARCHITECTURE_PREDEFINE)
if (TARGET_ARCH STREQUAL x86_64) # 64-bit lib files
    set(ARCHITECTURE_PREDEFINE -DAE_64BIT)
elseif(TARGET_ARCH STREQUAL i386) # 32-bit lib files
    set(ARCHITECTURE_PREDEFINE -DAE_32BIT)
endif()

# Platform-spesific sources
if (WIN32)
    file(GLOB PLATFORM_SOURCES ${PROJECT_DIR}/src/Platform/Windows/*.cpp)
elseif(UNIX)
    file(GLOB PLATFORM_SOURCES ${PROJECT_DIR}/src/Platform/Linux/*.cpp)

    list(APPEND AENGINE_LIB_DEPS ${GTK3_LIBRARIES})
endif()
list(APPEND PROJECT_SOURCES ${PLATFORM_SOURCES})

# Build library
if(AE_STATIC)
    message("-- Engine building as a static library...")
    add_library(${PROJECT_NAME} ${PROJECT_SOURCES} ${AENGINE_SRC_DEPS})

    # AE_STATIC is defined globally because this macro must be defined on client too
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DAE_STATIC)
else()
    message("-- Engine building as a shared library...")
    add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES} ${AENGINE_SRC_DEPS})
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DAE_BUILD_SHARED -DAE_SHARED)
endif()

target_compile_definitions(${PROJECT_NAME} PUBLIC ${ARCHITECTURE_PREDEFINE})
target_compile_definitions(${PROJECT_NAME} PRIVATE -DIMGUI_IMPL_OPENGL_LOADER_GLAD -DGLAD_GLAPI_EXPORT -DGLFW_DLL)
if(UNIX)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -Dpthread)
endif()

target_link_libraries(${PROJECT_NAME} ${AENGINE_LIB_DEPS})



# Post build events
if (WIN32)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PROJECT_DIR}/glsl/
            ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>/glsl/
    
    # Copy glfw.dll
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/Libs/GLFW/lib-vc2022/${TARGET_ARCH}/glfw3.dll
            ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>/

    # Copy freetype.dll
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/Libs/freetype/lib/freetype.dll
            ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>/)
elseif(UNIX)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PROJECT_DIR}/glsl/
            ${CMAKE_CURRENT_BINARY_DIR}/glsl/)
endif()
