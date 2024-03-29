cmake_minimum_required(VERSION 3.5)
project(main)

set(CMAKE_CXX_STANDARD 11)

file(GLOB shaders "${PROJECT_SOURCE_DIR}/shaders/*")

set(SOURCE_FILES
    common.h
    glad.c
    main.cpp
    ShaderProgram.h
    ShaderProgram.cpp
    buffer.h
    texture.h)

set(ADDITIONAL_INCLUDE_DIRS
        dependencies/include/GLAD
	dependencies/include/glm
    dependencies/include/stb_image)
set(ADDITIONAL_LIBRARY_DIRS
        dependencies/lib)   
set(ADDITIONAL_RUNTIME_LIBRARY_DIRS
        dependencies/bin)   

set (CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS_DEBUG}")

if(WIN32)
  set(ADDITIONAL_INCLUDE_DIRS 
        ${ADDITIONAL_INCLUDE_DIRS}
        dependencies/include)
  link_directories(${ADDITIONAL_LIBRARY_DIRS})
else()
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")
	find_package(glfw3 REQUIRED)
endif()

include_directories(${ADDITIONAL_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)

add_executable(main ${SOURCE_FILES} ${shaders})

target_include_directories(main PRIVATE ${OPENGL_INCLUDE_DIR})

foreach(shader ${shaders})
    get_filename_component(outputFileName ${shader} NAME)
    configure_file(${shader} ${PROJECT_BINARY_DIR}/${outputFileName} COPYONLY)
endforeach()

if(WIN32)
  add_custom_command(TARGET main POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/dependencies/bin" $<TARGET_FILE_DIR:main>)
  #set(CMAKE_MSVCIDE_RUN_PATH ${ADDITIONAL_RUNTIME_LIBRARY_DIRS})
  target_compile_options(main PRIVATE)
  target_link_libraries(main LINK_PUBLIC ${OPENGL_gl_LIBRARY} glfw3dll)
elseif(APPLE)
  target_compile_options(main PRIVATE -Wnarrowing)
  target_link_libraries(main LINK_PUBLIC ${OPENGL_gl_LIBRARY} glfw dl)
else()
  target_compile_options(main PRIVATE -Wnarrowing)
  target_link_libraries(main LINK_PUBLIC ${OPENGL_gl_LIBRARY} glfw rt dl)
endif()

