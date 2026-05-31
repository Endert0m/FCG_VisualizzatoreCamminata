cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 	0af55ccecd98d4e5a8d1fad7de25ba429d60e863 #refs/tags/1.0.1
)
FetchContent_MakeAvailable(glm)


set(METHODS_PATH "./src/*/methods/*.cpp")


set(VERSION "V3")

file(GLOB_RECURSE METHODS_SRC "${METHODS_PATH}")
add_executable(main${VERSION} ./src/testMain.cpp ${METHODS_SRC} )
target_compile_features(main${VERSION} PRIVATE cxx_std_17)
target_link_libraries(main${VERSION} PRIVATE SFML::Graphics glm)
