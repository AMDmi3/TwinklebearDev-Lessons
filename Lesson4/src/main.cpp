#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include "res_path.h"
#include "cleanup.h"

/*
 * Lesson 4: Handling Events
 */
//Screen attributes
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

/*
 * Draw an SDL_Texture to an SDL_Renderer at position x, y, with some desired
 * width and height
 * @param tex The source texture we want to draw
 * @param rend The renderer we want to draw too
 * @param x The x coordinate to draw too
 * @param y The y coordinate to draw too
 * @param w The width of the texture to draw
 * @param h The height of the texture to draw
 */
void renderTexture(SDL2pp::Texture &tex, SDL2pp::Renderer &ren, int x, int y, int w, int h){
	//Setup the destination rectangle to be at the position we want
	SDL2pp::Rect dst(x, y, w, h);
	ren.Copy(tex, SDL2pp::NullOpt, dst);
}
/*
 * Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
 * the texture's width and height
 * @param tex The source texture we want to draw
 * @param rend The renderer we want to draw too
 * @param x The x coordinate to draw too
 * @param y The y coordinate to draw too
 */
void renderTexture(SDL2pp::Texture &tex, SDL2pp::Renderer &ren, int x, int y){
	int w = tex.GetWidth(), h = tex.GetHeight();
	renderTexture(tex, ren, x, y, w, h);
}

int main(int, char**){
	try {
		//Start up SDL and make sure it went ok
		SDL2pp::SDL sdl(SDL_INIT_VIDEO);
		SDL2pp::SDLImage sdlimage;

		//Setup our window and renderer, this time let's put our window in the center
		//of the screen
		SDL2pp::Window window("Lesson 4", SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		//The texture we'll be using
		const std::string resPath = getResourcePath("Lesson4");
		SDL2pp::Texture image(renderer, resPath + "image.png");

		//Our texture size won't change, so we can get it here
		//instead of constantly allocating/deleting ints in the loop
		int iW = image.GetWidth(), iH = image.GetHeight();
		int x = SCREEN_WIDTH / 2 - iW / 2;
		int y = SCREEN_HEIGHT / 2 - iH / 2;

		//Our event structure
		SDL_Event e;
		//For tracking if we want to quit
		bool quit = false;
		while (!quit){
			//Read any events that occured, for now we'll just quit if any event occurs
			while (SDL_PollEvent(&e)){
				//If user closes the window
				if (e.type == SDL_QUIT){
					quit = true;
				}
				//If user presses any key
				if (e.type == SDL_KEYDOWN){
					quit = true;
				}
				//If user clicks the mouse
				if (e.type == SDL_MOUSEBUTTONDOWN){
					quit = true;
				}
			}
			//Rendering
			renderer.Clear();
			//Draw the image
			renderTexture(image, renderer, x, y);
			//Update the screen
			renderer.Present();
		}
	} catch (SDL2pp::Exception& e) {
		std::cerr << e.GetSDLFunction() << " Error: " << e.GetSDLError() << std::endl;
		return 1;
	}

	return 0;
}
