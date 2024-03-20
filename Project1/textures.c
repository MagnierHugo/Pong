#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#include "HandleSDL.h"

SDL_Texture* CreateTexture(SDL_Window* window, SDL_Renderer* renderer, char* path) {

    // Chargement de l'image
    SDL_Surface* image = IMG_Load(path);
    if (!image) {
        ErrorHandling("Failed to load image", true, window);
    }

    // Cr�ation de la texture � partir de l'image
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image); // Lib�ration de la surface, la texture contient maintenant l'image

    if (!texture) {
        ErrorHandling("Failed to create texture", true, window);
    }

    return texture;
}

void DestroyTextures(SDL_Texture* texture[]) {

    for (int textureIndex = 0; textureIndex < sizeof(texture); textureIndex++)
    {
        SDL_DestroyTexture(texture[textureIndex]);
    }
}