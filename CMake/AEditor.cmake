file(GLOB PROJECT_SOURCES 
    ${PROJECT_DIR}/src/*.cpp
    ${PROJECT_DIR}/src/Core/*.cpp
    ${PROJECT_DIR}/src/Menus/*.cpp
    ${PROJECT_DIR}/src/Panels/*.cpp
    )

include_directories(${PROJECT_DIR}/src)

# Build as WIN32 application on windows
if(WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${PROJECT_SOURCES} ${AEDITOR_SRC_DEPS})
else()
    add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${AEDITOR_SRC_DEPS})
endif()

target_link_libraries(${PROJECT_NAME} AEngine)

# Post build events
if (WIN32)
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
elseif(UNIX)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PROJECT_DIR}/Fonts/
            ${CMAKE_CURRENT_BINARY_DIR}/Fonts/
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PROJECT_DIR}/Icons/
            ${CMAKE_CURRENT_BINARY_DIR}/Icons/
    COMMAND ${CMAKE_COMMAND} -E copy
            ${PROJECT_DIR}/imgui.ini
            ${CMAKE_CURRENT_BINARY_DIR}/imgui.ini)
endif()
