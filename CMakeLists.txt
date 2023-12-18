cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Add source files
file(GLOB_RECURSE SOURCE_FILES 
	 ./src/*.c
	 ./src/*.cpp
     ./lib/EasyBMP/*.cpp)
	
# Add header files
file(GLOB_RECURSE HEADER_FILES 
	 ./include/*.h
	 ./include/*.hpp
     ./lib/rapidjson-master/include/*.h
     ./lib/rapidjson-master/include/*.hpp
     ./lib/EasyBMP/*.h
     ./lib/EasyBMP/*.hpp)

include_directories(./include
./lib/rapidjson-master/include
./lib/EasyBMP)

add_executable(CMakeSFMLProject ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(CMakeSFMLProject PRIVATE sfml-graphics)
target_compile_features(CMakeSFMLProject PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET CMakeSFMLProject
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:CMakeSFMLProject>
        VERBATIM)
endif()

install(TARGETS CMakeSFMLProject)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E create_symlink 
    ${CMAKE_SOURCE_DIR}/res 
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)
