project(Lesson4)

add_executable(Lesson4 src/main.cpp)
target_link_libraries(Lesson4 ${SDL2PP_LIBRARIES})
install(TARGETS Lesson4 RUNTIME DESTINATION ${BIN_DIR})

