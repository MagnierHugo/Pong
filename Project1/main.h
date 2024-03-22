#pragma once

struct InputSummary HandleInput(struct Paddle paddles[2], float deltaTime, bool screenWrapping);
void BeginningCountdown(struct GameState state, int fromWhat);
void ResetScene(struct Scene* currentScene, int whoWon);
void DrawScene(struct GameState state);