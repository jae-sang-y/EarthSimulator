#pragma once
#include "main.h"
#include "calc.h"
#include "map_con.h"

void event(SDL_Event *e)
{
	while (SDL_PollEvent(e) != 0)
	{
		switch (e->type)
		{
		case SDL_QUIT: {
			quit = true;
		}break;
		case SDL_KEYDOWN: {
			switch (e->key.keysym.sym)
			{
			case SDLK_ESCAPE: {
				quit = true;
			}break;
			case SDLK_0: {
				mgr = 0;
			}break;
			case SDLK_1: {
				mgr = 1;
			}break;
			case SDLK_2: {
				mgr = 2;
			}break;
			case SDLK_3: {
				mgr = 3;
			}break;
			case SDLK_4: {
				mgr = 4;
			}break;
			case SDLK_5: {
				mgr = 5;
			}break;
			case SDLK_6: {
				mgr = 6;
			}break;
			case SDLK_7: {
				mgr = 7;
			}break;
			case SDLK_8: {
				mgr = 8;
			}break;
			case SDLK_9: {
				mgr = 9;
			}break;
			}
		}break;
		}
	}
}


void map_set()
{
	all_rand();
	int length;
	char *array;

	std::ifstream stream;
	stream.open((currentDir + "\\" + "gfx\\map\\map.bmp").c_str(), std::ios_base::binary);
	if (!stream.bad()) {
		length = stream.rdbuf()->pubseekoff(0, std::ios_base::end);
		array = new char[length];
		stream.rdbuf()->pubseekoff(0, std::ios_base::beg);
		stream.read(array, length);
		for (int a = 0; a < length; a++)
		{
			std::cout << array[a] << " " << a << " \n";
		}
		stream.close();
	}
}
void run_ab(int a, int b)
{
}
void run_abcd(int a, int b)
{
	static int c, d;
	for (int w = 0; w < 8; w++)
	{
		mw = w;
		//c = (a + mca_w[w][0] + map_w) % map_w;
		c = a + mca_w[w][0];
		d = b + mca_w[w][1];
		if (c >= 0 && d >= 0 && c < map_w && d < map_h)
		{
			yu_x = c;
			yu_y = d;
		}
	}
}

void map_step()
{

	for (int a = 0; a < map_w; a++)
	{
		me_x = a;
		for (int b = 0; b < map_h; b++)
		{
			me_y = b;
			run_ab(a, b);
		}
	}
	for (int a = 0; a < map_w; a++)
	{
		me_x = a;
		for (int b = 0; b < map_h; b++)
		{
			me_y = b;
			run_abcd(a, b);
		}
		for (int b = map_h - 1; b >= 0; b--)
		{
			me_y = b;
			run_abcd(a, b);
		}
	}
	for (int a = map_w -1; a >= 0; a--)
	{
		me_x = a;
		for (int b = 0; b < map_h; b++)
		{
			me_y = b;
			run_abcd(a, b);
		}
		for (int b = map_h - 1; b >= 0; b--)
		{
			me_y = b;
			run_abcd(a, b);
		}
	}
}

void map_color(unsigned char *c, int a ,int b)
{
	c[3] = 255;
	if (mgr == 0)
	{
		c[0] = 0;
		c[2] = 255;
		c[1] = 0;
	}
	else if (mgr == 2)
	{
		c[0] = 0;
		c[1] = 255 * flt[a][b][fl_food];
		c[2] = 0;
	}
	else if (mgr == 3)
	{
		c[0] = 255 - 127 * flt[a][b][fl_mat] - 64;
		c[1] = c[0];
		c[2] = c[0];
	}
	else
	{
		c[0] = 255;
		c[1] = 0;
		c[2] = 255;
	}
}