#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include "res_path.h"
#include "cleanup.h"

/*
 * Lesson 2: Don't Put Everything in Main
 */
//Screen attributes
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

/*
 * Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
 * the texture's width and height
 * @param tex The source texture we want to draw
 * @param ren The renderer we want to draw too
 * @param x The x coordinate to draw too
 * @param y The y coordinate to draw too
 */
void renderTexture(SDL2pp::Texture &tex, SDL2pp::Renderer &ren, int x, int y){
	//Setup the destination rectangle to be at the position we want
	SDL2pp::Rect dst(x, y, tex.GetWidth(), tex.GetHeight());
	ren.Copy(tex, SDL2pp::NullOpt, dst);
}

int main(int, char**) try {
	//Start up SDL and make sure it went ok
	SDL2pp::SDL sdl(SDL_INIT_VIDEO);

	//Setup our window and renderer
	SDL2pp::Window window("Lesson 2", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//The textures we'll be using
	const std::string resPath = getResourcePath("Lesson2");
	SDL2pp::Texture background(renderer, resPath + "background.bmp");
	SDL2pp::Texture image(renderer, resPath + "image.bmp");

	//Clear the window
	renderer.Clear();

	//Get the width and height from the texture so we know how much to move x,y by
	//to tile it correctly
	int bW = background.GetWidth(), bH = background.GetHeight();

	//We want to tile our background so draw it 4 times
	renderTexture(background, renderer, 0, 0);
	renderTexture(background, renderer, bW, 0);
	renderTexture(background, renderer, 0, bH);
	renderTexture(background, renderer, bW, bH);

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

	return 0;
} catch (SDL2pp::Exception& e) {
	std::cout << e.GetSDLFunction() << " Error: " << e.GetSDLError() << std::endl;
	return 1;
}

