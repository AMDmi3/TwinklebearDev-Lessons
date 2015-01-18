project(Lesson6)

add_executable(Lesson6 src/main.cpp)
target_link_libraries(Lesson6 ${SDL2PP_LIBRARIES})
install(TARGETS Lesson6 RUNTIME DESTINATION ${BIN_DIR})

