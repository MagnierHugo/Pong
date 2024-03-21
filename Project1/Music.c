#include <stdio.h>
#include <SDL.h>
#include <SDL_mixer.h>


// Fonction pour initialiser SDL
int initSDL() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }
    return 0;
}

// Fonction pour initialiser SDL Mixer
int initSDL_Mixer() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Erreur lors de l'initialisation de SDL Mixer : %s\n", Mix_GetError());
        SDL_Quit();
        return 1;
    }
    return 0;
}

// Fonction pour charger le fichier audio
Mix_Chunk* loadSound() {
    Mix_Chunk* sound = Mix_LoadWAV("Sound\\DANCING.wav");
    if (!sound) {
        printf("Erreur lors du chargement du fichier audio : %s\n", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return NULL;
    }
    return sound;
}

int dance() {

    if (dance() != 0) {
        printf("Une erreur est survenue lors de la lecture de la musique.\n");
        return 1;
    }

    if (initSDL() != 0)
        return 1;

    if (initSDL_Mixer() != 0)
        return 1;

    Mix_Chunk* sound = loadSound();
    if (!sound)
        return 1;

    Mix_PlayChannel(-1, sound, 0);

    while (Mix_Playing(-1) != 0) {
        SDL_Delay(100);
    }


    Mix_FreeChunk(sound);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}
