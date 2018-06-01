#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <direct.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>
#include <ctime>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int MAX_SPRITE = 16;
const int MAX_MAP = 1;
const char ESCAPE = 0x1b;
std::string currentDir;
std::string sprite_file[MAX_SPRITE] = {
"a.bmp"
, "b.bmp"
, "gfx\\tile\\grass.bmp"
, "gfx\\tile\\mountain.bmp"
, "gfx\\tile\\high-mountain.bmp"
, "gfx\\tile\\river.bmp"
, "gfx\\tile\\ocean.bmp"
, "gfx\\tile\\sea.bmp"
};
std::string map_file[MAX_MAP] = {
	"gfx\\map\\map.bmp"
};
SDL_Surface* sprite_surf[MAX_SPRITE] = {};
SDL_Texture* sprite[MAX_SPRITE] = {};
SDL_Texture* texture[MAX_SPRITE] = {};
TTF_Font *def_font = NULL;

void step();
void draw();

bool init();
bool loadMedia();
void close();

void map_set();

void LOG_A(std::string);
void LOG_W(std::string);
void LOG_H(std::string);
void LOG_O(std::string);
void LOG_A(std::string, std::string);
void LOG_W(std::string, std::string);
void LOG_H(std::string, std::string);
void LOG_O(std::string, std::string);
void LOG_Stop();

SDL_Window* WNDW = NULL;
SDL_Surface* SURF;
SDL_Renderer* REND;

Mix_Music *gMusic = NULL;

SDL_Texture* draw_string(SDL_Color);
std::string public_string = "";
void set_rect(SDL_Rect*, int, int, int, int);
void set_rect(SDL_Rect*, int, int);
int T = 0;
const int T_max = pow(2 * 3 * 5 * 7 * 11, 5);

///////////////////////////
//         COLOR         //
///////////////////////////

Uint32 color(int, int, int);
SDL_Color c_black = { 0, 0, 0 };
SDL_Color c_white = { 255, 255, 255 };

///////////////////////////
//          MAP          //
///////////////////////////
const unsigned int map_w = 384;
const unsigned int map_h = 216;
const unsigned int map_opt = 16;


unsigned int tip[map_w][map_h][map_opt] = { { { 0 }, }, };
double flt[map_w][map_h][map_opt] = { { { 0 }, }, };

const int cont_num = 20;
enum { mp_geo, mp_con, mp_contient};
enum { fl_food, fl_mat, fl_cst, 
	fl_sun, fl_moon,
	fl_height, fl_heat, fl_mass, fl_press, fl_angle, fl_speed,//Solid
	fl_wat, fl_wat_angle, fl_wat_speed, fl_wat_heat, fl_wat_mat, //Water
	fl_gas, fl_gas_angle, fl_gas_heat //Gas
};

///////////////////////////
//      MAP GRAPHICS     //
///////////////////////////

unsigned int mgr = 4;
const unsigned int mgr_size = 5;
unsigned char mgr_a[4];
unsigned char mgr_b[4];
double the_time = 0;

///////////////////////////
//        MAP CACUL      //
///////////////////////////

const int mca_w[8][2] = { { 1,0 },{ 1, -1 },{ 0, -1 },{ -1,-1 },{ -1,0 },{ -1, 1 },{ 0,1 },{ 1,1 } };

///////////////////////////
//         USER          //
///////////////////////////

bool quit = false;

///////////////////////////
//          TEMP         //
///////////////////////////

int tmp[256];
double tmp2[256];

