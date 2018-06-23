#pragma once
#define M_R2 0.70710678118654752440084436210485

inline unsigned int *egw(unsigned int i)
{
	return &(tip[me_x][me_y][i]);
}
inline const unsigned int eg(unsigned int i)
{
	return (tip[me_x][me_y][i]);
}

inline unsigned int *vsw(unsigned int i)
{
	return &(tip[yu_x][yu_y][i]);
}
inline const unsigned int vs(unsigned int i)
{
	return (tip[yu_x][yu_y][i]);
}
inline double *egfw(unsigned int i)
{
	return &(flt[me_x][me_y][i]);
}
inline const double egf(unsigned int i)
{
	return (flt[me_x][me_y][i]);
}

inline double *vsfw(unsigned int i)
{
	return &(flt[yu_x][yu_y][i]);
}
inline const double vsf(unsigned int i)
{
	return (flt[yu_x][yu_y][i]);
}

void all_rand()
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
			flt[a][b][fl_food] = random() * (geo_list[tip[a][b][mp_geo]].food_max) * (0.01);
		}
	}
}

double get_grow_food(double food, int geo)
{
	return food * (-geo_list[geo - 1].food_eff * 0.05 + 4.0 * geo_list[geo - 1].food_eff * abs(the_time - 0.5) * 2);
}


void set_con()
{
	for (int i = 0; i < con_num; i++)
	{
		for (int j = 0; j < 3000; j++)
		{
			rand_pos(&tmp[0], &tmp[1]);
			if (tip[tmp[0]][tmp[1]][mp_geo] == 1 || tip[tmp[0]][tmp[1]][mp_geo] == 2 || tip[tmp[0]][tmp[1]][mp_geo] == 3)
			{
				tip[tmp[0]][tmp[1]][mp_con] = i + 1;
				pop[tmp[0]][tmp[1]][0].id = 1;
				pop[tmp[0]][tmp[1]][0].size = 1024;
				break;
			}
		}
	}
}

void get_conquer()
{
	if (egf(fl_food) > vsf(fl_food) && geo_list[eg(mp_geo)].in_wat == geo_list[vs(mp_geo)].in_wat && rand()%(9 - mw) == 0)
	{
		tmp2[0] = egf(fl_food) - vsf(fl_food);
		tmp2[0] *= 0.01;
		*egfw(fl_food) -= tmp2[0];
		*vsfw(fl_food) += tmp2[0]; 
	}
}
void grow()
{
	if (egf(fl_food) >= 0 && egf(fl_food) <  geo_list[eg(mp_geo)].food_max)
	{
		tmp2[0] = 0.8;
		*egfw(fl_food) += geo_list[eg(mp_geo)].food_eff * eg(mp_sun) * tmp2[0];
		*egfw(fl_food_crease) = egf(fl_food) - egf(fl_last_food);
		*egfw(fl_last_food) = egf(fl_food);
	}
}

void set_border()
{
	if (eg(mp_con) != vs(mp_con))
	{
		*egw(grp_con_border) += 1;
	}
}

void get_geo()
{
	int i;
	FILE* f;
	fopen_s(&f, (currentDir + "\\" + "gfx\\map\\map.bmp").c_str(), "rb");
	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f);
	int width = *(int*)&info[18];
	int height = *(int*)&info[22];
	int size = 3 * width * height;
	unsigned char* data = new unsigned char[size];
	fread(data, sizeof(unsigned char), size, f);
	fclose(f);

	if (map_w != width || map_h != height)
	{
		LOG_W("Map Size Not Same");
		return;
	}

	int a = 0,  b = height;
	for (i = 0; i < size; i += 3)
	{
		if (i / 3 % width == 0)
		{
			b--;
			a = 0;
		}
		for (int j = 0; j <= sizeof geo_list / sizeof geo; j++)
		{
			if (geo_list[j].compare(data[i + 2], data[i + 1], data[i]))
			{
				tip[a][b][mp_geo] = j + 1;
				break;
			}
		}
		a++;
	}
}
void get_sun()
{
	int i;
	FILE* f;
	fopen_s(&f, (currentDir + "\\" + "gfx\\map\\sun.bmp").c_str(), "rb");
	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f);
	int width = *(int*)&info[18];
	int height = *(int*)&info[22];
	int size = 3 * width * height;
	unsigned char* data = new unsigned char[size];
	fread(data, sizeof(unsigned char), size, f);
	fclose(f);

	if (map_w != width || map_h != height)
	{
		LOG_W("Map Size Not Same");
		return;
	}

	int a = 0, b = height;
	for (i = 0; i < size; i += 3)
	{
		if (i / 3 % width == 0)
		{
			b--;
			a = 0;
		}
		for (int j = 0; j <= sizeof geo_list / sizeof geo; j++)
		{
			tip[a][b][mp_sun] = 255 - data[i];
		}
		a++;
	}
}
void set_geo()
{
	tmp[0] = 0;
	geo_list[tmp[0]++].set_color(181, 230, 29); // Flat 
	{
		geo_list[tmp[0]].food_max = 400;
		geo_list[tmp[0]].food_eff = 0.07;
	}
	geo_list[tmp[0]++].set_color(185, 122, 87); // Mountain
	{
		geo_list[tmp[0]].food_max = 200;
		geo_list[tmp[0]].food_eff = 0.05;
	}
	geo_list[tmp[0]++].set_color(0, 162, 232); // River
	{
		geo_list[tmp[0]].food_max = 500;
		geo_list[tmp[0]].food_eff = 0.1;
	}
	geo_list[tmp[0]++].set_color(136, 0, 21); // Alps
	{
		geo_list[tmp[0]].food_max = 50;
	}
	geo_list[tmp[0]++].set_color(153, 217, 234); // Coast
	{
		geo_list[tmp[0]].food_max = 800;
		geo_list[tmp[0]].food_eff = 0.03;
		geo_list[tmp[0]].in_wat = true;
	}
	geo_list[tmp[0]++].set_color(63, 72, 204); // Ocean
	{
		geo_list[tmp[0]].food_max = 1600;
		geo_list[tmp[0]].food_eff = 0.6;
		geo_list[tmp[0]].in_wat = true;
	}
	geo_list[tmp[0]++].set_color(0, 0, 0); // None
	{
		geo_list[tmp[0]].food_max = 1600;
		geo_list[tmp[0]].food_eff = 0.6;
		geo_list[tmp[0]].in_wat = true;
	}


}