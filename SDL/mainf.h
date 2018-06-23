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
	set_geo();
	get_geo();
	get_sun();
	set_con();
}
void run_ab(int a, int b)
{
	grow();
	tip[a][b][grp_con_border] = 0;
}
void run_ab_end(int a, int b)
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
			get_conquer();
		}
	}
}
void run_abcd_once(int a, int b)
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
			set_border();
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
			run_abcd_once(a, b);
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
	for (int a = 0; a < map_w; a++)
	{
		me_x = a;
		for (int b = 0; b < map_h; b++)
		{
			me_y = b;
			run_ab_end(a, b);
		}
	}
}

void map_color(unsigned char *c, int a ,int b)
{
	c[3] = 255;
	if (mgr == 0)
	{
		set_color(c, 255, 0, 255, 255);
		if (tip[a][b][mp_geo] > 0)
		{
			geo_list[tip[a][b][mp_geo] - 1].set_ant_color(c);
		}
	}
	else if (mgr == 1)
	{
		set_color(c, 255, 0, 255, 255);
		if (tip[a][b][mp_geo] > 0)
		{
			geo_list[tip[a][b][mp_geo] - 1].set_ant_color(c);
		}
		if (tip[a][b][mp_con] > 0)
		{
			hsv_to_rgb(mgr_a, tip[a][b][mp_con] * 1.0 / (con_num));
			set_color(c, 0, 0, 0, 255);
			merge_color(c, mgr_a, c, tip[a][b][grp_con_border] / 8.0 / 2 + 0.25);
			if (geo_list[tip[a][b][mp_geo] - 1].bild_eff == 0)
			{
				geo_list[tip[a][b][mp_geo] - 1].set_ant_color(c);
				merge_color(c, mgr_a, c, 0.8);
				if (tip[a][b][grp_con_border] > 1 && tip[a][b][grp_con_border] <= 5)
				{
					merge_color(c, mgr_a, c, 0.5);
					set_color(c, 0, 0, 0, 255);
					merge_color(c, mgr_a, c, 0.5);
				}
			}
			else if (tip[a][b][grp_con_border] == 0)
			{
				c[0] = mgr_a[0];
				c[1] = mgr_a[1];
				c[2] = mgr_a[2];
			}
		}
	}
	else if (mgr == 2)
	{
		set_color(c, tip[a][b][mp_sun], tip[a][b][mp_sun], tip[a][b][mp_sun], 255);
	}
	else if (mgr == 3)
	{
		c[1] = 255 * reru(flt[a][b][fl_food] / 1000.0);
		c[2] = 0;
		c[0] = 0;
		if (flt[a][b][fl_food] == 0) { set_color(c,255,255,255,255); }
	}
	else if (mgr == 4)
	{
		c[0] = 255 - 127 * flt[a][b][fl_mat] - 64;
		c[1] = c[0];
		c[2] = c[0];
	}
	else if (mgr == 5)
	{
		c[0] = 255 ;
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