project(Lesson2)
add_executable(Lesson2 src/main.cpp)
target_link_libraries(Lesson2 ${SDL2PP_LIBRARIES})
install(TARGETS Lesson2 RUNTIME DESTINATION ${BIN_DIR})

