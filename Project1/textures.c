#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#include "HandleSDL.h"
#include "Scene.h"
#include "GameState.h"
#include "Paddle.h"
#include "Ball.h"
#include "Constants.h"
#include "scoreUI.h"


SDL_Texture* CreateTexture(struct SDL sdlStruct, char* path) 
{
    // Chargement de l'image
    SDL_Surface* image = IMG_Load(path);
    if (!image) {
        ErrorHandling("Failed to load image", sdlStruct);
    }

    // Création de la texture à partir de l'image
    SDL_Texture* texture = SDL_CreateTextureFromSurface(
        sdlStruct.renderer, image
    );

    SDL_FreeSurface(image); // Libération de la surface, la texture contient maintenant l'image

    if (!texture) {
        ErrorHandling("Failed to create texture", sdlStruct);
    }

    return texture;
}

void DestroyTextures(struct GameState state) 
{
    SDL_DestroyTexture(state.background);
    
    struct Paddle* paddles = state.scene.Paddles;
    struct Ball* balls = state.scene.Balls;

    for (int paddleIndex = 0; paddleIndex < 2; paddleIndex++)
    {
        SDL_DestroyTexture(paddles[paddleIndex].texture);
    }

    for (int ballIndex = 0; ballIndex < MAX_BALL_AMOUNT; ballIndex++)
    {
        SDL_DestroyTexture(balls[ballIndex].texture);
    }
}