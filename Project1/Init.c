#include <SDL.h>

#include "SDLStruct.h"
#include "HandleSDL.h"
#include "Ball.h"
#include "Constants.h"
#include "Paddle.h"
#include "Particle.h"
#include "textures.h"
#include "Scene.h"
#include "scoreUI.h"

static struct Paddle* InitPaddles(struct SDL sdlStruct)
{
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

static struct Particle* InitParticles(struct SDL sdlStruct)
{
    struct Particle* particles = malloc(
        MAX_PARTICLE_AMOUNT * sizeof(struct Particle)
    );

    if (particles == NULL) {
        ErrorHandling(
            "The memory allocation for the particles failed",
            sdlStruct
        );
    }

    for (int i = 0; i < MAX_PARTICLE_AMOUNT; i++)
    {
        particles[i] = (struct Particle){ 0, 0, 0, 0, 0, false };
    }

    return particles;
}

static struct Score* InitScore(struct SDL sdlStruct)
{
    struct Score* images = malloc(5 * sizeof(struct Score));

    if (images == NULL) {
        ErrorHandling(
            "The memory allocation for the images failed",
            sdlStruct
        );
    }

    images[0] = (struct Score){ CreateTexture(sdlStruct, "Image\\1.png") };
    images[1] = (struct Score){ CreateTexture(sdlStruct, "Image\\2.png") };
    images[2] = (struct Score){ CreateTexture(sdlStruct, "Image\\3.png") };
    images[3] = (struct Score){ CreateTexture(sdlStruct, "Image\\4.png") };
    images[4] = (struct Score){ CreateTexture(sdlStruct, "Image\\5.png") };
    
    printf("this happened");
    /*char* paths[5] = {
        "Image\\1.png", "Image\\2.png", "Image\\3.png",
        "Image\\4.png", "Image\\5.png"
    };

    for (int i = 0; i < 5; i++)
    {
        images[i] = (struct Score){ CreateTexture(sdlStruct, paths[i])};
    }*/

    return images;
}

struct Scene InitScene()
{
    struct SDL sdl = StartSDL();

    struct Paddle* paddles = InitPaddles(sdl);

    struct Ball* balls = InitBalls(sdl);

    struct Particle* particles = InitParticles(sdl);

    struct Score* images = InitScore(sdl);

    struct Obstacle* obstacles = malloc(
        MAX_OBSTACLE_AMOUNT * sizeof(struct Obstacle)
    );

    int nbr_obstacles = 0;

    struct Scene scene = (struct Scene){ balls, paddles, sdl , 
        particles, images, obstacles, nbr_obstacles };

    return scene;
}