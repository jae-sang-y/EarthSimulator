#pragma once
#include "main.h"
#include "calc.h"

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
			}
		}break;
		}
	}
}


void map_set()
{
	for (int a = 0; a < map_w; a++)
	{
		for (int b = 0; b < map_h; b++)
		{
			for (int i = 0; i < map_opt; i++)
			{
				tip[a][b][i] = 0;
				flt[a][b][i] = random();
			}
			flt[a][b][fl_height] = flt[a][b][fl_height] * 2 - 1;
			flt[a][b][fl_wat] = (flt[a][b][fl_wat] - 0.65) / 2;
			flt[a][b][fl_wat_angle] = M_PI;
		}
	}
	rand_pos(&tmp[0], &tmp[1]);
	tip[tmp[0]][tmp[1]][mp_con] = 1;
	rand_pos(&tmp[0], &tmp[1]);
	tip[tmp[0]][tmp[1]][mp_con] = 2;
	rand_pos(&tmp[0], &tmp[1]);
	tip[tmp[0]][tmp[1]][mp_con] = 3;
	rand_pos(&tmp[0], &tmp[1]);
	tip[tmp[0]][tmp[1]][mp_con] = 4;
	/*fstream input((currentDir + "\\" + map_file[0]).c_str(), ios::binary | ios::in | ios::ate);

	ifstream::pos_type fileSize;

	char* content;

	if (input.is_open())
	{
	fileSize = input.tellg();

	}
	input.close();*/

}
void map_step()
{
	int c, d;

	for (int a = 0; a < map_w; a++)
	{
		for (int b = 0; b < map_h; b++)
		{
			for (int w = 0; w < 8; w++)
			{
				c = (a + mca_w[w][0] + map_w) % map_w;
				d = b + mca_w[w][1];
				if (c >= 0 && d >= 0 && c < map_w && d < map_h)
				{
					if (tip[a][b][mp_con] > 0)
					{
						if (tip[c][d][mp_con] == 0 && tip[a][b][mp_del] == 0)
						{
							tip[c][d][mp_con] = tip[a][b][mp_con];
							tip[c][d][mp_del] = 10 + rand() % 10;
						}
					}
					if (pow(flt[a][b][fl_height] - flt[c][d][fl_height], 2) >= 0.5)
					{
						flt[a][b][fl_height] = (flt[a][b][fl_height] * 3 + flt[c][d][fl_height] * 1) / 4;
						flt[c][d][fl_height] = (flt[a][b][fl_height] * 1 + flt[c][d][fl_height] * 3) / 4;
						flt[a][b][fl_wat] = (flt[a][b][fl_wat] * 3 + flt[c][d][fl_wat] * 1) / 4;
						flt[c][d][fl_wat] = (flt[a][b][fl_wat] * 1 + flt[c][d][fl_wat] * 3) / 4;
					}
					
					if (flt[a][b][fl_wat] > 0)
					{
						tmp2[0] = flt[a][b][fl_wat_angle];
						tmp2[1] = w * M_PI / 4;
						tmp2[2] = 0;
						if (abs(tmp2[0] - tmp2[1]) < (M_PI / 2))
						{
							tmp2[2] = ((1 - (abs(tmp2[0] - tmp2[1]) / (M_PI / 2)))) / 2;
						}
						else if (abs(tmp2[0] - tmp2[1]) > (M_PI / 2 * 3))
						{
							tmp2[2] = ((1 - ((2 * M_PI - abs(tmp2[0] - tmp2[1])) / (M_PI / 2)))) / 2;
						}
						tmp2[0] = flt[a][b][fl_wat];// *tanh(flt[a][b][fl_height] / flt[c][d][fl_height]);
						tmp2[1] = 1;

						flt[c][d][fl_wat] += tmp2[0] * tmp2[1] * tmp2[2];
						flt[a][b][fl_wat] -= tmp2[0] * tmp2[1] * tmp2[2];

						tmp2[3] = ((flt[a][b][fl_height] + flt[a][b][fl_wat]) - (flt[c][d][fl_height] + flt[c][d][fl_wat])) / 2;
						tmp2[0] = tmp2[0] * tmp2[1] * tmp2[2];
						flt[c][d][fl_height] += tmp2[0] * tmp2[3];
						flt[a][b][fl_height] -= tmp2[0] * tmp2[3];

					}

					/*
					if (false && flt[a][b][fl_height] + flt[a][b][fl_wat] > flt[c][d][fl_height] + flt[c][d][fl_wat] && flt[a][b][fl_wat] > 0)
					{
						tmp2[1] = ((flt[a][b][fl_height] + flt[a][b][fl_wat]) - (flt[c][d][fl_height] + flt[c][d][fl_wat])) / 2;
						tmp2[0] = 0.2;
						flt[c][d][fl_wat] += tmp2[0] * tmp2[1];
						flt[a][b][fl_wat] -= tmp2[0] * tmp2[1];
						tmp2[1] = ((flt[a][b][fl_height] + flt[a][b][fl_wat]) - (flt[c][d][fl_height] + flt[c][d][fl_wat])) / 2;
						tmp2[0] = 0.2;
						flt[c][d][fl_height] += tmp2[0] * tmp2[1];
						flt[a][b][fl_height] -= tmp2[0] * tmp2[1];
					}*/
				}
			}
			in_1_1(&flt[a][b][fl_height]);
			flt[a][b][fl_wat_angle] = (flt[a][b][fl_wat_angle] + 0.2);
			while (flt[a][b][fl_wat_angle] > M_PI * 2)
			{
				flt[a][b][fl_wat_angle] -= M_PI * 2;
			}
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
		set_color(mgr_a, 255, 255, 255, 255);
		set_color(mgr_b, 0, 0, 0, 255);

		if (flt[a][b][fl_wat] >= 1)
		{
			set_color(mgr_a, 0, 0, 255, 255);
		}
		else if (flt[a][b][fl_wat] > 0)
		{
			set_color(mgr_a, 0, 0, 255, 255);
			merge_color(mgr_b, mgr_a, mgr_b, 1 - flt[a][b][fl_wat]);
		}
		merge_color(c, mgr_a, mgr_b, 1 - (flt[a][b][fl_height] + 1) * 0.5);

		//ÃÊ ->³ë ->°¥ ->º¸ ->Èò 
		//.00->.25->.50->.75->1.00
	}
	else
	{
		c[0] = 255;
		c[1] = 0;
		c[2] = 255;
	}
}