#pragma once

struct InputSummary HandleInput(struct Paddle paddles[2], float deltaTime, bool screenWrapping);
void PreGame(struct Scene scene, int fromWhat, SDL_Texture* backgroundTexture);
void ResetScene(struct Scene* currentScene, int whoWon);
void DrawScene(struct Scene currentScene, SDL_Texture* background);