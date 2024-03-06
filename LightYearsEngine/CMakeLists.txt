add_library(${LIGHT_YEARS_ENGINE_TARGET_NAME} STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/application.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/application.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/core.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/core.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/world.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/world.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/actor.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/actor.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/object.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/object.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/physics.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/physics.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/asset_manager.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/asset_manager.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/math_util.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/math_util.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/include/entrypoint.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/entrypoint.cpp
)

target_include_directories(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

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

target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC sfml-graphics)
target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC sfml-window)
target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC sfml-system)
target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC sfml-audio)

set(BOX2D_LIB_NAME Box2D)
set(BOX2D_LIB_REPO https://github.com/erincatto/box2d)

FetchContent_Declare(
  ${BOX2D_LIB_NAME}
  GIT_REPOSITORY ${BOX2D_LIB_REPO}
  GIT_TAG v2.4.1
  GIT_SHALLOW FALSE
)

FetchContent_MakeAvailable(${BOX2D_LIB_NAME})

target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC box2d)

#function(CopyLibToTarget LIB_NAME TARGET_NAME)
#  add_custom_target(
#    ${LIGHT_YEARS_GAME_TARGET_NAME}
#    POST_BUILD
#    COMMAND
#    ${CMAKE_COMMAND} -E copy_if_different
#    $<TARGET_FILE:sfml-graphics>
#    $<TARGET_FILE_DIR:${LIGHT_YEARS_GAME_TARGET_NAME}
#    ${CMAKE_COMMAND} -E copy_if_different
#    $<TARGET_FILE:sfml-window>
#    $<TARGET_FILE_DIR:${LIGHT_YEARS_GAME_TARGET_NAME}
#    ${CMAKE_COMMAND} -E copy_if_different
#    $<TARGET_FILE:sfml-system>
#    $<TARGET_FILE_DIR:${LIGHT_YEARS_GAME_TARGET_NAME}
#    ${CMAKE_COMMAND} -E copy_if_different
#    $<TARGET_FILE:sfml-audio>
#    $<TARGET_FILE_DIR:${LIGHT_YEARS_GAME_TARGET_NAME}
#  )
#endfunction()
