#pragma once
#pragma warning(disable:4244)
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
#include <thread>
#pragma execution_character_set("utf-8")

#include "map.h"

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
, "gfx\\gui\\white_paper.bmp"
};
std::string map_file[MAX_MAP] = {
	"gfx\\map\\map.bmp"
};
SDL_Surface* sprite_surf[MAX_SPRITE] = {};
SDL_Texture* sprite[MAX_SPRITE] = {};
SDL_Texture* texture[MAX_SPRITE] = {};
TTF_Font *def_font = NULL;

void start();
void step();
void draw();
void ui(SDL_Event*);

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

SDL_Texture* draw_string(std::string, SDL_Color);
void set_rect(SDL_Rect*, int, int, int, int);
void set_rect(SDL_Rect*, int, int);
int T = 0;
const int T_max = (int)pow(2 * 3 * 5 * 7 * 11, 5);
int global[100];
enum {
	glb_mousex,
	glb_mousey,
	glb_mousesx,
	glb_mousesy,
	glb_mousebx,
	glb_mouseby,
	glb_mouseps
};

///////////////////////////
//         COLOR         //
///////////////////////////

Uint32 color(int, int, int);
SDL_Color c_black = { 0, 0, 0 };
SDL_Color c_white = { 255, 255, 255 };

///////////////////////////
//         USER          //
///////////////////////////

bool quit = false;

enum {
	msg_show
};
class Message {
public:
	unsigned int id = 0;
	unsigned int x = 0;
	unsigned int y = 0;
	unsigned int w = 400;
	unsigned int h = 300;
	bool selected = false;
	Message(unsigned i, unsigned int a_x, unsigned int a_y, std::string s){
		id = i;
		x = a_x;
		y = a_y;
		sub = s;
	}
	std::string sub = "";

};

std::vector<Message> msg;