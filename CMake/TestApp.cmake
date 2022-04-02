file(GLOB PROJECT_SOURCES 
    ${PROJECT_DIR}/src/*.cpp
    ${PROJECT_DIR}/src/Scripts/*.cpp)

# Build as WIN32 application on windows
if(WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${PROJECT_SOURCES})
else()
    add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
endif()

# Compile definitions
if (NOT AE_STATIC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DAE_SHARED)
endif()

target_link_libraries(${PROJECT_NAME} AEngine)

# Post build events
if (WIN32)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PROJECT_DIR}/Assets/
            ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>/Assets/)
elseif(UNIX)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PROJECT_DIR}/Assets/
            ${CMAKE_CURRENT_BINARY_DIR}/Assets/)
endif()
