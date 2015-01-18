#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include "res_path.h"
#include "cleanup.h"

/*
 * Lesson 3: SDL Extension Libraries
 */
//Screen attributes
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
//We'll be scaling our tiles to be 40x40
const int TILE_SIZE = 40;

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

		//Setup our window and renderer
		SDL2pp::Window window("Lesson 3", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		//The textures we'll be using
		const std::string resPath = getResourcePath("Lesson3");
		SDL2pp::Texture background(renderer, resPath + "background.png");
		SDL2pp::Texture image(renderer, resPath + "image.png");

		//Clear the window
		renderer.Clear();

		//Determine how many tiles we'll need to fill the screen
		int xTiles = SCREEN_WIDTH / TILE_SIZE;
		int yTiles = SCREEN_HEIGHT / TILE_SIZE;

		//Draw the tiles by calculating their positions
		for (int i = 0; i < xTiles * yTiles; ++i){
			int x = i % xTiles;
			int y = i / xTiles;
			renderTexture(background, renderer, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
		}

		//Draw our image in the center of the window
		//We need the foreground image's width to properly compute the position
		//of it's top left corner so that the image will be centered
		int iW = image.GetWidth(), iH = image.GetHeight();
		int x = SCREEN_WIDTH / 2 - iW / 2;
		int y = SCREEN_HEIGHT / 2 - iH / 2;
		renderTexture(image, renderer, x, y);

		//Update the screen
		renderer.Present();
		SDL_Delay(2000);
	} catch (SDL2pp::Exception& e) {
		std::cerr << e.GetSDLFunction() << " Error: " << e.GetSDLError() << std::endl;
		return 1;
	}

	return 0;
}
