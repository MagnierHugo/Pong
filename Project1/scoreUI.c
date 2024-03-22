#include <SDL.h>
#include <stdbool.h>
#include <SDL_image.h>

#include "Scene.h"
#include "Constants.h"
#include "textures.h"


void AfficherScore(struct Scene scene, int scoreGauche, int scoreDroite)
{
    SDL_Rect destRectGauche = { 
        PADDLE_OFFSET_FROM_WALL, 25, 60, 55 
    }; // Position pour le score gauche

    SDL_Rect destRectDroite = { 
        SCREEN_WIDTH - PADDLE_OFFSET_FROM_WALL - 50, 25, 60, 55 
    }; // Position pour le score droit
    
    if (scoreGauche != 0)
    {
        SDL_RenderCopy(
            scene.SDL.renderer, 
            scene.images[scoreGauche - 1].texture, 
            NULL, &destRectGauche
        );
    }

    if (scoreDroite != 0)
    {
        SDL_RenderCopy(
            scene.SDL.renderer, 
            scene.images[scoreDroite - 1].texture, 
            NULL, &destRectDroite
        );
    }
}
