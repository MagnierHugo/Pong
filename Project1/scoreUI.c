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
    printf("%d : %d\n", scoreGauche, scoreDroite);
    switch (scoreGauche)
    {
        case 1:
            SDL_RenderCopy(
                scene.SDL.renderer,
                //scene.images[scoreGauche - 1].texture,
                CreateTexture(scene.SDL, "Image\\1.png"),
                NULL, &destRectGauche
            ); break;

            //CreateTexture(sdlStruct, "Image\\1.png")
        case 2:
            SDL_RenderCopy(
                scene.SDL.renderer,
                //scene.images[scoreGauche - 1].texture,
                CreateTexture(scene.SDL, "Image\\2.png"),
                NULL, &destRectGauche
            ); break;
        case 3:
            SDL_RenderCopy(
                scene.SDL.renderer,
                //scene.images[scoreGauche - 1].texture,
                CreateTexture(scene.SDL, "Image\\3.png"),
                NULL, &destRectGauche
            ); break;
        case 4:
            SDL_RenderCopy(
                scene.SDL.renderer,
                //scene.images[scoreGauche - 1].texture,
                CreateTexture(scene.SDL, "Image\\4.png"),
                NULL, &destRectGauche
            ); break;
        case 5:
            SDL_RenderCopy(
                scene.SDL.renderer,
                //scene.images[scoreGauche - 1].texture,
                CreateTexture(scene.SDL, "Image\\5.png"),
                NULL, &destRectGauche
            ); break;
        default:
            break;
    }
   //     SDL_RenderCopy(
   //         scene.SDL.renderer, 
			//scene.images[scoreGauche - 1].texture,
   //        /* CreateTexture(
   //             scene.SDL,
   //             "Image\\definetelyNotAMinecraftSprite.png"
   //         ),*/
   //         NULL, &destRectGauche
   //     );
    
    switch (scoreDroite)
    {
        case 1:
            SDL_RenderCopy(
                scene.SDL.renderer,
                //scene.images[scoreGauche - 1].texture,
                CreateTexture(scene.SDL, "Image\\1.png"),
                NULL, &destRectDroite
            ); break;
            //CreateTexture(sdlStruct, "Image\\1.png")
        case 2:
            SDL_RenderCopy(
                scene.SDL.renderer,
                //scene.images[scoreGauche - 1].texture,
                CreateTexture(scene.SDL, "Image\\2.png"),
                NULL, &destRectDroite
            ); break;
        case 3:
            SDL_RenderCopy(
                scene.SDL.renderer,
                //scene.images[scoreGauche - 1].texture,
                CreateTexture(scene.SDL, "Image\\3.png"),
                NULL, &destRectDroite
            ); break;
        case 4:
            SDL_RenderCopy(
                scene.SDL.renderer,
                //scene.images[scoreGauche - 1].texture,
                CreateTexture(scene.SDL, "Image\\4.png"),
                NULL, &destRectDroite
            ); break;
        case 5:
            SDL_RenderCopy(
                scene.SDL.renderer,
                //scene.images[scoreGauche - 1].texture,
                CreateTexture(scene.SDL, "Image\\5.png"),
                NULL, &destRectDroite
            ); break;
        default:
            break;
    }
        /*SDL_RenderCopy(
            scene.SDL.renderer, 
            scene.images[scoreDroite - 1].texture, 
            NULL, &destRectDroite
        );*/
}
