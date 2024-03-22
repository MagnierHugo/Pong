#include <SDL.h>
#include <stdbool.h>
#include <SDL_image.h>

#include "Scene.h"
#include "Constants.h"
#include "textures.h"

void RenderScore(struct Scene scene, SDL_Rect* dest, SDL_Texture* texture) {
    SDL_RenderCopy(
        scene.SDL.renderer,
        texture,
        NULL, dest
    );
}

void AfficherScoreSingle(struct Scene scene, int score, SDL_Rect dest) {
    switch (score)
    {
    case 1:
        RenderScore(scene, &dest,
            CreateTexture(scene.SDL, "Image\\1.png"));
        break;

    case 2:
        RenderScore(scene, &dest,
            CreateTexture(scene.SDL, "Image\\2.png"));
        break;
    case 3:
        RenderScore(scene, &dest,
            CreateTexture(scene.SDL, "Image\\3.png"));
        break;
    case 4:
        RenderScore(scene, &dest,
            CreateTexture(scene.SDL, "Image\\4.png"));
        break;
    case 5:
        RenderScore(scene, &dest,
            CreateTexture(scene.SDL, "Image\\5.png"));
        break;
    default:
        break;
    }
}

void AfficherScore(struct Scene scene, int scoreGauche, int scoreDroite)
{
    SDL_Rect destRectGauche = { 
        PADDLE_OFFSET_FROM_WALL, 25, 60, 55 
    }; // Position pour le score gauche
    AfficherScoreSingle(scene, scoreGauche, destRectGauche);
    
    SDL_Rect destRectDroite = {
        SCREEN_WIDTH - PADDLE_OFFSET_FROM_WALL - 50, 25, 60, 55
    }; // Position pour le score droit
    AfficherScoreSingle(scene, scoreDroite, destRectDroite);
}