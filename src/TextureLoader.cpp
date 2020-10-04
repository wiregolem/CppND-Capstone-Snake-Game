#include "TextureLoader.h"

SDL_Texture* TextureLoader::LoadTexture(const char* filename, SDL_Renderer * renderer)
{
 /*Load image from file as an SDL Surface*/
 SDL_Surface* temporary = IMG_Load(filename);
 if (temporary == NULL) {
   std::cerr << "Failed to load image\n";
   std::cerr << " SDL_Error: "<<  SDL_GetError() << "\n";
 }
 /*Convert surface into a texture to be rendered*/
 SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temporary);
 if (texture == NULL) {
   std::cerr << "Create texture from surface failed " << SDL_GetError() << "\n";
 }

 /*Free unnecessary surface resource*/
 SDL_FreeSurface(temporary);

 /*return texture pointer for use*/
 return texture;
}


