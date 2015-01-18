project(Lesson3)

add_executable(Lesson3 src/main.cpp)
target_link_libraries(Lesson3 ${SDL2PP_LIBRARIES})
install(TARGETS Lesson3 RUNTIME DESTINATION ${BIN_DIR})

