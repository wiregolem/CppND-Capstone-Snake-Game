#include "SDL.h"
#include "SDL_image.h"

class TextureLoader
{
 public:
	static SDL_Texture* LoadTexture(const char* filename, SDL_Renderer * renderer);
};

