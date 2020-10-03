#include "TextureLoader.h"
#include "SDL_image.h"

SDL_Texture* TextureLoader::LoadTexture(const char* filename, SDL_Renderer* renderer)
{
 /*Load image from file as an SDL Surface*/
 SDL_Surface* temporary = IMG_Load(filename);

 /*Convert surface into a texture to be rendered*/
 SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temporary);

 /*Free unnecessary surface resource*/
 SDL_FreeSurface(temporary);

 /*return texture pointer for use*/
 return texture;
}
