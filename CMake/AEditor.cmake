file(GLOB PROJECT_SOURCES 
    ${PROJECT_DIR}/src/*.cpp
    )

include_directories(${PROJECT_DIR}/src)

add_executable(${PROJECT_NAME} WIN32 ${PROJECT_SOURCES} ${AEDITOR_SRC_DEPS})

# Compile definitions
if (NOT AE_STATIC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DAE_SHARED)
endif()

target_link_libraries(${PROJECT_NAME} AEngine)

# Post build events
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PROJECT_DIR}/Fonts/
            ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>/Fonts/
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PROJECT_DIR}/Icons/
            ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>/Icons/
    COMMAND ${CMAKE_COMMAND} -E copy
            ${PROJECT_DIR}/imgui.ini
            ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>/imgui.ini)
