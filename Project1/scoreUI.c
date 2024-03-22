#include <SDL.h>
#include <stdbool.h>
#include <SDL_image.h>

#include "Scene.h"
#include "Constants.h"
#include "textures.h"


struct Score InitScore(struct SDL sdlStruct)
{
    struct Score images = {
        CreateTexture(sdlStruct, Le1),
        CreateTexture(sdlStruct, Le2),
        CreateTexture(sdlStruct, Le3),
        CreateTexture(sdlStruct, Le4),
        CreateTexture(sdlStruct, Le5),
    };
    return images;
}

void AfficherScore(struct Scene scene, int scoreGauche, int scoreDroite)
{
    SDL_Rect destRectGauche = { PADDLE_OFFSET_FROM_WALL, 25, 60, 55 }; // Position pour le score gauche
    SDL_Rect destRectDroite = { SCREEN_WIDTH - PADDLE_OFFSET_FROM_WALL - 50, 25, 60, 55 }; // Position pour le score droit
    
    // Affichage du score du joueur gauche
    if (scoreGauche == 1) {
        SDL_RenderCopy(scene.SDL.renderer, scene.images.img1, NULL, &destRectGauche);
    }
    else if (scoreGauche == 2) {
        SDL_RenderCopy(scene.SDL.renderer, scene.images.img2, NULL, &destRectGauche);
    }
    else if (scoreGauche == 3) {
        SDL_RenderCopy(scene.SDL.renderer, scene.images.img3, NULL, &destRectGauche);
    }
    else if (scoreGauche == 4) {
        SDL_RenderCopy(scene.SDL.renderer, scene.images.img4, NULL, &destRectGauche);
    }
    else if (scoreGauche == 5) {
        SDL_RenderCopy(scene.SDL.renderer, scene.images.img5, NULL, &destRectGauche);
    }

    // Affichage du score du joueur droit
    if (scoreDroite == 1) {
        SDL_RenderCopy(scene.SDL.renderer, scene.images.img1, NULL, &destRectDroite);
    }
    else if (scoreDroite == 2) {
        SDL_RenderCopy(scene.SDL.renderer, scene.images.img2, NULL, &destRectDroite);
    }
    else if (scoreDroite == 3) {
        SDL_RenderCopy(scene.SDL.renderer, scene.images.img3, NULL, &destRectDroite);
    }
    else if (scoreDroite == 4) {
        SDL_RenderCopy(scene.SDL.renderer, scene.images.img4, NULL, &destRectDroite);
    }
    else if (scoreDroite == 5) {
        SDL_RenderCopy(scene.SDL.renderer, scene.images.img5, NULL, &destRectDroite);
    }

}
