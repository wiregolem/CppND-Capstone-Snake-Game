#include "SDL.h"
#include "SDL_Image.h"

class TextureLoader
{
 public:
	static SDL_Texture* LoadTexture(const char* filename, SDLRenderer * renderer);
}
