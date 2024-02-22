add_library(${LIGHT_YEARS_ENGINE_TARGET_NAME} STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/application.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/application.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/core.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/core.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/world.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/world.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/actor.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/actor.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/include/entrypoint.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/entrypoint.cpp
)

target_include_directories(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC sfml-graphics)
target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC sfml-window)
target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC sfml-system)
target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC sfml-audio)

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
