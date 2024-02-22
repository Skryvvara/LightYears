add_executable(${LIGHT_YEARS_GAME_TARGET_NAME}
  ${CMAKE_CURRENT_SOURCE_DIR}/include/game_framework/game_application.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/game_framework/game_application.cpp
)

target_include_directories(${LIGHT_YEARS_GAME_TARGET_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${LIGHT_YEARS_GAME_TARGET_NAME} PUBLIC ${LIGHT_YEARS_ENGINE_TARGET_NAME})

#function(copy_lib_dir_to_target LIB_DIR_NAME TARGET_NAME)
#  add_custom_target(${TARGET_NAME}
#    POST_BUILD
#    COMMAND
#    ${CMAKE_COMMAND} -E copy_if_different
#    $<TARGET_FILE_DIR:${LIB_DIR_NAME}>
#    $<TARGET_FILE_DIR:${TARGET_NAME}>
#  )
#endfunction()
#
#copy_lib_dir_to_target(${LIGHT_YEARS_ENGINE_TARGET_NAME} ${LIGHT_YEARS_GAME_TARGET_NAME})
