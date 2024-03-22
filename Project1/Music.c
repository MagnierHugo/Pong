#include <stdio.h>
#include <SDL.h>
#include <SDL_mixer.h>

#include "HandleSDL.h"
#include "Utility.h"
#include "SDLStruct.h"


// Fonction pour charger le fichier audio
Mix_Chunk* loadSound(char songWAV[20], struct SDL sdlStruct) {
    Mix_Chunk* sound = Mix_LoadWAV(songWAV);

    if (!sound) {
        ErrorHandling("Error while loading audio file", sdlStruct);
    }

    return sound;
}

void PlaySound(char songWAV[20], struct SDL sdlStruct) {

    Mix_Chunk* sound = loadSound(songWAV, sdlStruct);

    Mix_PlayChannel(-1, sound, 0);
}
