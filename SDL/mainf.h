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
	for (int a = 0; a < map_w; a++)
	{
		for (int b = 0; b < map_h; b++)
		{
			for (int i = 0; i < map_opt; i++)
			{
				tip[a][b][i] = 0;
				flt[a][b][i] = random();
			}
			flt[a][b][fl_height] = flt[a][b][fl_height] - 0.5;
			flt[a][b][fl_wat] = flt[a][b][fl_wat] / 2;// -0.5;
			flt[a][b][fl_wat_angle] = M_PI;
			flt[a][b][fl_wat_speed] = 1;
		}
	}
	for (int i = 0; i < cont_num; i++)
	{
		rand_pos(&tmp[0], &tmp[1]);
		tip[tmp[0]][tmp[1]][mp_contient] = i;
		flt[tmp[0]][tmp[1]][fl_mass] = i;
		flt[tmp[0]][tmp[1]][fl_press] = 0;
		flt[tmp[0]][tmp[1]][fl_angle] = random() * M_PI *2;
	}
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
				if (c >= 0 && d >= 0 && c < map_w && d < map_h && rand() % 8 == 0)
				{
					if (tip[a][b][mp_contient] > 0)
					{
						tmp2[1] = dir_force(flt[a][b][fl_angle], w * M_PI / 4) * flt[a][b][fl_speed];
						if (tip[c][d][mp_contient] == 0 && flt[a][b][fl_mass] > 0.5 && tmp2[1] > 0)
						{
							tmp2[0] = reru(flt[a][b][fl_mass] / 2 + tmp2[1]);

							flt[c][d][fl_angle] = flt[a][b][fl_angle];
							flt[c][d][fl_speed] = 1;

							tip[c][d][mp_contient] = tip[a][b][mp_contient];
							flt[c][d][fl_press] = flt[a][b][fl_press];
							flt[a][b][fl_mass] += tmp2[2];
							flt[c][d][fl_mass] -= tmp2[2];
						}
						if (tip[c][d][mp_contient] == tip[a][b][mp_contient] && flt[a][b][fl_mass] * flt[a][b][fl_press] > flt[c][d][fl_mass] * flt[c][d][fl_press] && tmp2[1] > 0)
						{
							tmp2[0] = (flt[a][b][fl_mass] - flt[c][d][fl_mass]) / 4 * (flt[a][b][fl_press] / flt[c][d][fl_press]) + tmp2[1];
							flt[a][b][fl_mass] -= tmp2[2];
							flt[c][d][fl_mass] += tmp2[2];
						}
						if (tip[c][d][mp_contient] != tip[a][b][mp_contient] && flt[a][b][fl_mass] * flt[a][b][fl_press] > flt[c][d][fl_mass] * flt[c][d][fl_press] && tmp2[1] > 0)
						{
							if (flt[a][b][fl_mass] < 0.5)
							{
								tmp2[2] = (flt[a][b][fl_mass] - flt[c][d][fl_mass]) / 4 * (flt[a][b][fl_press] / flt[c][d][fl_press]) + tmp2[1];

								flt[c][d][fl_angle] = flt[a][b][fl_angle];
								flt[c][d][fl_speed] = (flt[a][b][fl_press] / flt[c][d][fl_press]);

								flt[a][b][fl_mass] -= tmp2[2];
								flt[c][d][fl_mass] += tmp2[2];
								tip[c][d][mp_contient] = tip[a][b][mp_contient];
							}
							else
							{
								tmp2[4] = flt[c][d][fl_angle];
								flt[c][d][fl_angle] = (flt[a][b][fl_angle] * flt[a][b][fl_mass] * tmp2[1] + flt[c][d][fl_angle] * flt[c][d][fl_mass]) / (flt[a][b][fl_mass] * tmp2[1] + flt[c][d][fl_mass]);
								flt[c][d][fl_speed] = (flt[a][b][fl_mass] * tmp2[1]) / (flt[c][d][fl_mass]) * dir_force(flt[c][d][fl_angle], tmp2[4]);


								tmp2[2] = ((flt[a][b][fl_mass] - flt[c][d][fl_mass]) * 2 + tmp2[1] * 2);
								flt[a][b][fl_press] -= tmp2[2];
								flt[c][d][fl_press] += tmp2[2];
							}
						}


					}
					if (flt[a][b][fl_wat] > 0)
					{
						tmp2[4] = 0;
						if (flt[a][b][fl_height] + flt[a][b][fl_wat] > flt[c][d][fl_height] + flt[c][d][fl_wat])
						{
							tmp2[4] += ((flt[a][b][fl_height] + flt[a][b][fl_wat] + flt[a][b][fl_moon]) - (flt[c][d][fl_height] + flt[c][d][fl_wat] + flt[a][b][fl_moon])) / 1;
						}

						if (flt[a][b][fl_wat_speed] + tmp2[4] > 0)
						{
							tmp2[2] = dir_force(flt[a][b][fl_wat_angle], w * M_PI / 4);

							tmp2[1] = reru(flt[a][b][fl_wat_speed] * tmp2[2] + tmp2[4]);
							tmp2[3] = tmp2[4] * reru(tmp2[1]);

							flt[c][d][fl_wat] += tmp2[3];
							flt[a][b][fl_wat] -= tmp2[3];

							tmp[0] = fl_height;
							tmp2[1] = 1;
							flt[c][d][tmp[0]] += flt[a][b][tmp[0]] * reru(tmp2[3]) * tmp2[1];
							flt[a][b][tmp[0]] -= flt[a][b][tmp[0]] * reru(tmp2[3]) * tmp2[1];
						}
					}
					break;
				}
			}
			if (flt[a][b][fl_height] > flt[c][d][fl_height] + 0.5)
			{
				tmp2[0] = (flt[a][b][fl_height]) - (flt[c][d][fl_height]);
				tmp2[1] = 0.1;
				tmp2[3] = tmp2[0] * tmp2[1];
				flt[c][d][fl_height] += tmp2[3];
				flt[a][b][fl_height] -= tmp2[3];
			}
			if (flt[a][b][fl_mass] < 1)
			{
				flt[a][b][fl_mass] += 0.001 * random();
			}

			if (flt[a][b][fl_press] != 1.0)
			{
				tmp2[0] = (flt[a][b][fl_press] - 1.0);
				tmp2[1] = random() * 0.01;
				flt[a][b][fl_press] -= tmp2[0] * tmp2[1];
				flt[a][b][fl_height] += tmp2[0] * tmp2[1];
			}

			flt[a][b][fl_sun] = (sin((a + the_time * map_w) / (map_w / 2.0) * M_PI)) * (1 - abs(b - (map_h / 2.0)) / (map_h / 2.0));
			flt[a][b][fl_moon] = abs(sin((a + the_time * map_w) / (map_w / 2.0) * M_PI)) * (1 - abs(b - (map_h / 2.0)) / (map_h / 2.0));

			in_1_1(&flt[a][b][fl_height]);

			flt[a][b][fl_wat_angle] += 0.01;
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
		merge_color(c, mgr_a, mgr_b, 1 - (flt[a][b][fl_height] + 1) * 0.5);

		if (flt[a][b][fl_wat] > 0)
		{
			c[2] = 255;
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