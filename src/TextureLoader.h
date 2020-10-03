#include <SDL>

class TextureLoader
{
 public:
	static SDL_Texture* LoadTexture(const char* filename, SDLRenderer * renderer);
}
