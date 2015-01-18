project(Lesson5)

add_executable(Lesson5 src/main.cpp)
target_link_libraries(Lesson5 ${SDL2PP_LIBRARIES})
install(TARGETS Lesson5 RUNTIME DESTINATION ${BIN_DIR})

