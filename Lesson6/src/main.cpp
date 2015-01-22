#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include "res_path.h"

/*
 * Lesson 6: True Type Fonts with SDL_ttf
 */
//Screen attributes
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

/*
 * Draw an SDL_Texture to an SDL_Renderer at some destination rect
 * taking a clip of the texture if desired
 * @param tex The source texture we want to draw
 * @param rend The renderer we want to draw too
 * @param dst The destination rectangle to render the texture too
 * @param clip The sub-section of the texture to draw (clipping rect)
 *		default of nullptr draws the entire texture
 */
void renderTexture(SDL2pp::Texture &tex, SDL2pp::Renderer &ren, SDL2pp::Rect dst, SDL2pp::Optional<SDL2pp::Rect> clip = SDL2pp::NullOpt){
	ren.Copy(tex, clip, dst);
}
/*
 * Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
 * the texture's width and height and taking a clip of the texture if desired
 * If a clip is passed, the clip's width and height will be used instead of the texture's
 * @param tex The source texture we want to draw
 * @param rend The renderer we want to draw too
 * @param x The x coordinate to draw too
 * @param y The y coordinate to draw too
 * @param clip The sub-section of the texture to draw (clipping rect)
 *		default of nullptr draws the entire texture
 */
void renderTexture(SDL2pp::Texture &tex, SDL2pp::Renderer &ren, int x, int y, SDL2pp::Optional<SDL2pp::Rect> clip = SDL2pp::NullOpt){
	SDL2pp::Rect dst;
	dst.x = x;
	dst.y = y;
	if (clip){
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else {
		dst.w = tex.GetWidth();
		dst.h = tex.GetHeight();
	}
	renderTexture(tex, ren, dst, clip);
}
/*
 * Render the message we want to display to a texture for drawing
 * @param message The message we want to display
 * @param fontFile The font we want to use to render the text
 * @param color The color we want the text to be
 * @param fontSize The size we want the font to be
 * @param renderer The renderer to load the texture in
 * @return An SDL_Texture containing the rendered message, or nullptr if something went wrong
 */
SDL2pp::Texture renderText(const std::string &message, const std::string &fontFile, SDL_Color color,
		int fontSize, SDL2pp::Renderer &renderer)
{
	//Open the font
	SDL2pp::Font font(fontFile, fontSize);
	//We need to first render to a surface as that's what TTF_RenderText returns, then
	//load that surface into a texture
	SDL2pp::Surface surf = font.RenderText_Blended(message, color);
	SDL2pp::Texture texture(renderer, surf);
	return texture;
}

int main(int, char**) try {
	//Start up SDL and make sure it went ok
	SDL2pp::SDL sdl(SDL_INIT_VIDEO);
	//Also need to init SDL_ttf
	SDL2pp::SDLTTF sdlttf;

	//Setup our window and renderer
	SDL2pp::Window window("Lesson 6", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	const std::string resPath = getResourcePath("Lesson6");
	//We'll render the string "TTF fonts are cool!" in white
	//Color is in RGB format
	SDL_Color color = { 255, 255, 255, 255 };
	SDL2pp::Texture image = renderText("TTF fonts are cool!", resPath + "sample.ttf", color, 64, renderer);

	//Get the texture w/h so we can center it in the screen
	int iW = image.GetWidth(), iH = image.GetHeight();
	int x = SCREEN_WIDTH / 2 - iW / 2;
	int y = SCREEN_HEIGHT / 2 - iH / 2;

	SDL_Event e;
	bool quit = false;
	while (!quit){
		//Event Polling
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT){
				quit = true;
			}
			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE){
				quit = true;
			}
		}
		renderer.Clear();
		//We can draw our message as we do any other texture, since it's been
		//rendered to a texture
		renderTexture(image, renderer, x, y);
		renderer.Present();
	}

	return 0;
} catch (SDL2pp::Exception& e) {
	std::cout << e.GetSDLFunction() << " Error: " << e.GetSDLError() << std::endl;
	return 1;
}
