cmake_minimum_required(VERSION 3.20)
project(maine-coon-app)
set(CMAKE_CXX_STANDARD 20)

###################################################################
# Local variables
###################################################################
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(PROJECT_SRC_DIR "src")
set(PROJECT_ASSETS_DIR "${CMAKE_CURRENT_LIST_DIR}/assets")

# Libraries

if (ANDROID)
    set(MAINECOON_DIR "${CMAKE_SOURCE_DIR}/../maine-coon")
    set(MAINECOON_LIB_DIR "${CMAKE_BINARY_DIR}/maine-coon")
else()
    set(MAINECOON_DIR "${CMAKE_SOURCE_DIR}/maine-coon")
    set(MAINECOON_LIB_DIR "${CMAKE_BINARY_DIR}/maine-coon")
endif()

macro(append_linker_flags FLAGS)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${FLAGS}")
endmacro()
###################################################################
# Target sources and create executable
###################################################################
file(GLOB_RECURSE PROJECT_SOURCES
        "${PROJECT_SRC_DIR}/*.h"
        "${PROJECT_SRC_DIR}/*.cpp"
        )

list(APPEND PROJECT_SOURCES

        )

# Create executable
if (ANDROID)
    add_library(${PROJECT_NAME} SHARED 
        ${PROJECT_SOURCES}
        )
    include_directories("${MAINECOON_DIR}/vendor/spdlog/include")
    include_directories("${MAINECOON_DIR}/vendor")

    add_subdirectory(
        ../maine-coon
        ./maine-coon
        )
else()
    add_executable(${PROJECT_NAME} "${PROJECT_SOURCES}")
endif()
# Link libraries
target_link_libraries(${PROJECT_NAME}
        maine-coon
        )

include_directories(SYSTEM "src")
include_directories("${MAINECOON_DIR}/src")

# Include directories
target_include_directories(${PROJECT_NAME} PUBLIC
        "${PROJECT_ASSETS_DIR}"
        "${PROJECT_SOURCE_DIR}"
        )

if (EMSCRIPTEN)
	append_linker_flags("-sOFFSCREEN_FRAMEBUFFER=1")
	append_linker_flags("-sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2")
    append_linker_flags("-sUSE_SDL=2")
    append_linker_flags("-FULL_ES3=1")
	append_linker_flags("-lGL")
    append_linker_flags("-sFORCE_FILESYSTEM=1")
	append_linker_flags("-sFETCH=1")
	append_linker_flags("-sASYNCIFY")
	append_linker_flags("-sASSERTIONS=1")

	append_linker_flags("-Oz")
	append_linker_flags("-sMIN_FIREFOX_VERSION=70")
	append_linker_flags("-sMIN_SAFARI_VERSION=130000")
	append_linker_flags("-sMIN_IE_VERSION=0x7FFFFFFF") # Do not support Internet Explorer at all (this is the Emscripten default, shown here for posterity)
	# append_linker_flags("-sMIN_EDGE_VERSION=79") # Require Chromium-based Edge browser
	append_linker_flags("-sMIN_CHROME_VERSION=80")

endif (EMSCRIPTEN)

###################################################################
# Copy executable dependencies to CMake runtime output directory
###################################################################
if (WIN32)
    # Copy library dlls -------------------------------------------
    file(GLOB_RECURSE LIB_DLLS
            "${MAINECOON_LIB_DIR}/*.dll"
            )

    foreach (dll ${LIB_DLLS})
        file(COPY ${dll}
                DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    endforeach (dll)
    # -------------------------------------------------------------
endif ()


if (DEFINED EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    # This line is used to set your executable to build with the emscripten html
    # template so that you can directly open it.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
    target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="/assets/")
    # set(CMAKE_EXECUTABLE_SUFFIX ".wasm")
  # Set the asset path macro in release mode to a relative path that assumes the
  # assets folder is in the same directory as the game executable

endif (DEFINED EMSCRIPTEN)

add_custom_target(copy_assets_sandbox
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_ASSETS_DIR} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
        )

add_dependencies(${PROJECT_NAME} copy_assets_sandbox)
# -----------------------------------------------------------------
