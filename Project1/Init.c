#include <SDL.h>

#include "SDLStruct.h"
#include "HandleSDL.h"
#include "Ball.h"
#include "Constants.h"
#include "Paddle.h"
#include "Particle.h"
#include "textures.h"
#include "Scene.h"

static struct Paddle* InitPaddles(struct SDL sdlStruct)
{
    SDL_Window* window = sdlStruct.window;
    SDL_Renderer* renderer = sdlStruct.renderer;

    struct Paddle* paddles = malloc(2 * sizeof(struct Paddle));

    if (paddles == NULL) {
        ErrorHandling("Memory allocation for the paddles failed", sdlStruct);
    }

    paddles[0] = (struct Paddle){
        PADDLE_OFFSET_FROM_WALL,
        SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2,
        PADDLE_WIDTH,
        PADDLE_HEIGHT,
        PADDLE_SPEED,
        CreateTexture(sdlStruct, "Image\\Pad1.png")
    };
    paddles[1] = (struct Paddle){
        SCREEN_WIDTH - PADDLE_OFFSET_FROM_WALL - PADDLE_WIDTH,
        SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2,
        PADDLE_WIDTH,
        PADDLE_HEIGHT,
        PADDLE_SPEED,
        CreateTexture(sdlStruct, "Image\\Pad2.png")
    };

    return paddles;
}

static struct Ball* InitBalls(struct SDL sdlStruct)
{
    SDL_Window* window = sdlStruct.window;
    SDL_Renderer* renderer = sdlStruct.renderer;

    struct Ball* balls = malloc(MAX_BALL_AMOUNT * sizeof(struct Ball));

    if (balls == NULL) {
        ErrorHandling("Memory allocation for the balls failed", sdlStruct);
    }

    srand(time(NULL));
    for (int i = 0; i < MAX_BALL_AMOUNT; i++)
    {
        balls[i] = (struct Ball){
                SCREEN_WIDTH / 2 - BALL_SIZE / 2, // x pos
                SCREEN_HEIGHT / 2 - BALL_SIZE / 2, // y pos
                BALL_SIZE, // size
                RdmInt(-1, 1, true), // dir x
                RdmInt(-1, 1, true), // dir y
                BALL_INITIAL_SPEED, // speed
                CreateTexture(sdlStruct, "Image\\ball.png"),
                i == 0 // only the first ball shoud be active
        };
    }

    return balls;
}

struct Scene InitScene()
{
    struct SDL sdl = StartSDL();

    struct Paddle* paddles = InitPaddles(sdl);

    struct Ball* balls = InitBalls(sdl);

    struct Particle* particles = InitParticles(sdl);

    return (struct Scene) { balls, paddles, sdl , particles };
}