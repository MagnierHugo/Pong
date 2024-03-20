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

    // Création de la texture à partir de l'image
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image); // Libération de la surface, la texture contient maintenant l'image

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