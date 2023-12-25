#ifndef COMMON_FUNCTION_H_  // Tao header card dung chung cho cac lop 
#define COMMON_FUNCTION_H_


#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

const int WIDTH_BACKGROUND = 4800;
const int HEIGHT_BACKGROUND = 600;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
const int NUM_THREATS = 3; 
 


static SDL_Surface *g_screen = NULL;
static SDL_Surface *g_bkground = NULL;
static SDL_Event g_even;

namespace SDLCommonFunc
{
    SDL_Surface* LoadImage(std::string file_path);
    void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
    void CleanUp();
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2 );
}


#endif