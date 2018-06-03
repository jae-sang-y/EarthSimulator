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
	stair_height();
}
void map_step()
{
	int c, d;

	for (int a = 0; a < map_w; a++)
	{
		me_x = a;
		for (int b = 0; b < map_h; b++)
		{
			me_y = b;
			for (int w = 0; w < 8; w++)
			{
				//c = (a + mca_w[w][0] + map_w) % map_w;
				c = a + mca_w[w][0];
				d = b + mca_w[w][1];
				if (c >= 0 && d >= 0 && c < map_w && d < map_h)
				{
					yu_x = c;
					yu_y = d;
					water_flow();
				}
			}
			flt[a][b][fl_sun] = (sin((a + the_time * map_w) / (map_w / 2.0) * M_PI)) * (1 - abs(b - (map_h / 2.0)) / (map_h / 2.0));
			flt[a][b][fl_moon] = abs(sin((a + the_time * map_w) / (map_w / 2.0) * M_PI)) * (1 - abs(b - (map_h / 2.0)) / (map_h / 2.0));
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
	else if (mgr == 1)
	{
		c[0] = 0;
		c[1] = 0;
		c[2] = 255 * flt[a][b][fl_wat];
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
	else if (mgr == 4)
	{
		set_color(mgr_a, 0, 0, 0, 255);
		set_color(mgr_b, 255, 255, 255, 255);
		merge_color(c, mgr_a, mgr_b, flt[a][b][fl_height]);

		if (flt[a][b][fl_wat] > 0)
		{
			c[2] = 255;
			if (flt[a][b][fl_wat] < 0.1)
			{
				c[1] = 255;
			}
		}

		//ÃÊ ->³ë ->°¥ ->º¸ ->Èò 
		//.00->.25->.50->.75->1.00
	}
	else if (mgr == 5)
	{
		set_color(mgr_a, 255, 255, 255, 255);
		set_color(mgr_b, 0, 0, 0, 255);
		merge_color(c, mgr_a, mgr_b, 1 - (flt[a][b][fl_height] + 1) * 0.5);
	}
	else if (mgr == 6)
	{
		set_color(mgr_a, 255, 255, 255, 255);
		set_color(mgr_b, 0, 255, 0, 255);
		merge_color(c, mgr_a, mgr_b, flt[a][b][fl_gas]);
	}
	else if (mgr == 7)
	{
		set_color(mgr_a, 255, 255, 255, 255);
		set_color(mgr_b, 0, 0, 255, 255);
		merge_color(c, mgr_a, mgr_b, flt[a][b][fl_moon]);
	}
	else if (mgr == 8)
	{
		set_color(c,0,0,0,255);
		if (tip[a][b][mp_contient] > 0)
		{
			set_color(mgr_a, 255, 255, 255, 255);
			hsv_to_rgb(mgr_b, (1.0 / cont_num) * tip[a][b][mp_contient]);
			merge_color(c, mgr_a, mgr_b, flt[a][b][fl_mass]);
		}

	}
	else
	{
		c[0] = 255;
		c[1] = 0;
		c[2] = 255;
	}
}