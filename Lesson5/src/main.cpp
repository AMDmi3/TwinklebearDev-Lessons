#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include "res_path.h"
#include "cleanup.h"

/*
 * Lesson 5: Clipping Sprite Sheets
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

int main(int, char**){
	try {
		//Start up SDL and make sure it went ok
		SDL2pp::SDL sdl(SDL_INIT_VIDEO);
		SDL2pp::SDLImage sdlimage;

		//Setup our window and renderer
		SDL2pp::Window window("Lesson 5", SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		const std::string resPath = getResourcePath("Lesson5");
		SDL2pp::Texture image(renderer, resPath + "image.png");

		//iW and iH are the clip width and height
		//We'll be drawing only clips so get a center position for the w/h of a clip
		int iW = 100, iH = 100;
		int x = SCREEN_WIDTH / 2 - iW / 2;
		int y = SCREEN_HEIGHT / 2 - iH / 2;

		//Setup the clips for our image
		SDL2pp::Rect clips[4];
		//Since our clips our uniform in size we can generate a list of their
		//positions using some math (the specifics of this are covered in the lesson)
		for (int i = 0; i < 4; ++i){
			clips[i].x = i / 2 * iW;
			clips[i].y = i % 2 * iH;
			clips[i].w = iW;
			clips[i].h = iH;
		}
		//Specify a default clip to start with
		int useClip = 0;

		SDL_Event e;
		bool quit = false;
		while (!quit){
			//Event Polling
			while (SDL_PollEvent(&e)){
				if (e.type == SDL_QUIT){
					quit = true;
				}
				//Use number input to select which clip should be drawn
				if (e.type == SDL_KEYDOWN){
					switch (e.key.keysym.sym){
						case SDLK_1:
							useClip = 0;
							break;
						case SDLK_2:
							useClip = 1;
							break;
						case SDLK_3:
							useClip = 2;
							break;
						case SDLK_4:
							useClip = 3;
							break;
						case SDLK_ESCAPE:
							quit = true;
							break;
						default:
							break;
					}
				}
			}
			//Rendering
			renderer.Clear();
			//Draw the image
			renderTexture(image, renderer, x, y, clips[useClip]);
			//Update the screen
			renderer.Present();
		}
	} catch (SDL2pp::Exception& e) {
		std::cerr << e.GetSDLFunction() << " Error: " << e.GetSDLError() << std::endl;
		return 1;
	}

	return 0;
}
