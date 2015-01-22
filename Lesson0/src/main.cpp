#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

/*
 * Lesson 0: Test to make sure SDL is setup properly
 */
int main(int, char**) try {
	SDL2pp::SDL(SDL_INIT_VIDEO);
	return 0;
} catch (SDL2pp::Exception& e) {
	std::cout << e.GetSDLFunction() << " Error: " << e.GetSDLError() << std::endl;
	return 1;
}

