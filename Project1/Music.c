#include <stdio.h>
#include <SDL.h>
#include <SDL_mixer.h>

#include "HandleSDL.h"


// Fonction pour initialiser SDL
int initSDL_Audio() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Erreur initialisation de SDL : %s\n", SDL_GetError());
        return -1;
    }
    return 0;
}

// Fonction pour initialiser SDL Mixer
int initSDL_Mixer() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Erreur initialisation de SDL Mixer : %s\n", Mix_GetError());
        SDL_Quit();
        return -1;
    }
    return 0;
}

// Fonction pour charger le fichier audio
Mix_Chunk* loadSound(char songWAV[20]) {
    Mix_Chunk* sound = Mix_LoadWAV(songWAV);
    if (!sound) {
        printf("Erreur lors du chargement du fichier audio : %s\n", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return NULL;
    }
    return sound;
}

int dance(char songWAV[20]) {

    if (initSDL_Audio() != 0)
        return -1;

    if (initSDL_Mixer() != 0)
        return -1;

    Mix_Chunk* sound = loadSound(songWAV);
    if (!sound)
        return -1;

    Mix_PlayChannel(-1, sound, 0);

    return 0;
}
