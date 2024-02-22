cmake_minimum_required(VERSION 3.28.3)

project(LightYears
  VERSION 1.0.0
  LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(LIGHT_YEARS_ENGINE_TARGET_NAME LightYearsEngine)
set(LIGHT_YEARS_GAME_TARGET_NAME LightYearsGame)

include(FetchContent)

set(SFML_LIB_NAME SFML)
set(SFML_LIB_REPO https://github.com/SFML/SFML)

FetchContent_Declare(
  ${SFML_LIB_NAME}
  GIT_REPOSITORY ${SFML_LIB_REPO}
  GIT_TAG 2.5.1
  GIT_SHALLOW FALSE
)

FetchContent_MakeAvailable(${SFML_LIB_NAME})

add_subdirectory(LightYearsEngine)
add_subdirectory(LightYearsGame)
