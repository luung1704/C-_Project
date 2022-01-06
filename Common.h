#ifndef COMMON_H
#define COMMON_H
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <vector>
static SDL_Window* window = NULL;
static SDL_Renderer* screen = NULL;
static SDL_Event event;
const int SCREEN_WIDTH=1280;
const int SCREEN_HEIGHT=640;
const int SCREEN_BPP=32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0xff;
const int SPEED = 8;
#define BLANK_TILE 0
#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10
typedef struct Input{
    int left;
    int right;
    int up;
    int down;
    int jump;
    int attack;
};
typedef struct Map{
    int start_x;
    int start_y;
    int max_x;
    int max_y;
    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name;
};
#endif // COMMON_H
