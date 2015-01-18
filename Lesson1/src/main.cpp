#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include "res_path.h"

/*
 * Lesson 1: Hello World!
 */
int main(int, char**){
	try {
		//First we need to start up SDL, and make sure it went ok
		SDL2pp::SDL(SDL_INIT_VIDEO);

		//Now create a window with title "Hello World" at 100, 100 on the screen with w:640 h:480 and show it
		SDL2pp::Window win("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);

		//Create a renderer that will draw to the window, -1 specifies that we want to load whichever
		//video driver supports the flags we're passing
		//Flags: SDL_RENDERER_ACCELERATED: We want to use hardware accelerated rendering
		//SDL_RENDERER_PRESENTVSYNC: We want the renderer's present function (update screen) to be
		//synchornized with the monitor's refresh rate
		SDL2pp::Renderer ren(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		//SDL 2.0 now uses textures to draw things but SDL_LoadBMP returns a surface
		//this lets us choose when to upload or remove textures from the GPU
		std::string imagePath = getResourcePath("Lesson1") + "hello.bmp";
		SDL2pp::Surface bmp(imagePath);

		//To use a hardware accelerated texture for rendering we can create one from
		//the surface we loaded
		SDL2pp::Texture tex(ren, bmp);

		//Now lets draw our image
		//First clear the renderer
		ren.Clear();
		//Draw the texture
		ren.Copy(tex, SDL2pp::NullOpt, SDL2pp::NullOpt);
		//Update the screen
		ren.Present();

		//Have the program wait for 2000ms so we get a chance to see the screen
		SDL_Delay(2000);

	} catch (SDL2pp::Exception& e) {
		std::cout << e.GetSDLFunction() << " Error: " << e.GetSDLError() << std::endl;
	}

	return 0;
}

