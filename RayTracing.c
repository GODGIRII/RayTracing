#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600
#define RAY_COUNT 1000
#define RAY_STEP 1
#define LIGHT_RADIUS 5
#define OBSTACLE_RADIUS 100

typedef struct {
    float x, y, radius;
} Circle;

typedef struct {
    float x, y, angle;
} Ray;

void drawCircle(SDL_Surface* surface, Circle circle, Uint32 color) {
    Uint32* pixels = (Uint32*)surface->pixels;
    for (int x = circle.x - circle.radius; x <= circle.x + circle.radius; x++) {
        for (int y = circle.y - circle.radius; y <= circle.y + circle.radius; y++) {
            float dx = x - circle.x;
            float dy = y - circle.y;
            if (dx * dx + dy * dy <= circle.radius * circle.radius) {
                if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
                    pixels[y * surface->w + x] = color;
            }
        }
    }
}

int rayHitsCircle(float x, float y, Circle c) {
    float dx = x - c.x;
    float dy = y - c.y;
    return (dx * dx + dy * dy <= c.radius * c.radius);
}

void drawRay(SDL_Surface* surface, Ray ray, Circle blocker, Uint32 color) {
    Uint32* pixels = (Uint32*)surface->pixels;
    float x = ray.x;
    float y = ray.y;

    while (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        if (rayHitsCircle(x, y, blocker))
            break;

        pixels[(int)y * surface->w + (int)x] = color;
        x += cos(ray.angle) * RAY_STEP;
        y += sin(ray.angle) * RAY_STEP;
    }
}

void drawScene(SDL_Surface* surface, Circle light, Circle obstacle) {
    SDL_FillRect(surface, NULL, 0x000000); // Clear screen

    // Draw rays
    for (int i = 0; i < RAY_COUNT; i++) {
        float angle = i * (2 * M_PI / RAY_COUNT);
        Ray ray = {light.x, light.y, angle};
        drawRay(surface, ray, obstacle, 0xffd43bff); // yellow rays
    }

    // Draw light and obstacle
    drawCircle(surface, obstacle, 0xffffffff);
    drawCircle(surface, light, 0xffffffff);
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL init failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Raytracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Surface* surface = SDL_GetWindowSurface(window);

    Circle obstacle = {WIDTH * 0.35, HEIGHT * 0.5, OBSTACLE_RADIUS};
    Circle light = {WIDTH * 0.75, HEIGHT * 0.5, LIGHT_RADIUS};

    SDL_Event event;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = 0;
            if (event.type == SDL_MOUSEMOTION) {
                light.x = event.motion.x;
                light.y = event.motion.y;
            }
        }

        drawScene(surface, light, obstacle);
        SDL_UpdateWindowSurface(window);
        SDL_Delay(16); // ~60 FPS
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

