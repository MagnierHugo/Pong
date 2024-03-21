#pragma once

struct InputSummary HandleInput(struct Paddle paddles[2], float deltaTime, bool screenWrapping);
void BeginningCountdown(struct Scene scene, int fromWhat, SDL_Texture* background);
void ResetScene(struct Scene* currentScene, int whoWon);
void DrawScene(struct Scene currentScene, SDL_Texture* background);