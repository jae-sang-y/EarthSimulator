#pragma once

inline double *egw(int i)
{
	return &(flt[me_x][me_y][i]);
}
inline double eg(int i)
{
	return (flt[me_x][me_y][i]);
}

inline double *vsw(int i)
{
	return &(flt[yu_x][yu_y][i]);
}
inline double vs(int i)
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
			flt[a][b][fl_height] = flt[a][b][fl_height] - 0.5;
			flt[a][b][fl_wat] = flt[a][b][fl_wat] / 2;// -0.5;
			flt[a][b][fl_wat_angle] = M_PI / 4;
			flt[a][b][fl_wat_force] = random() / 10;
		}
	}
}
void stair_height()
{
	for (int a = 0; a < map_w; a++)
	{
		for (int b = 0; b < map_h; b++)
		{
			flt[a][b][fl_height] = (10 * a / (map_w - 1)) / 10.0;// +sin(b) / 10;
			flt[a][b][fl_wat] = 0;
			flt[a][b][fl_wat_angle] = 0;
			flt[a][b][fl_wat_force] = 0;
		}
		if (a > 170 && a < 180)
		{
			for (int b = 80; b < map_h - 80; b++)
			{
				flt[a][b][fl_wat] = 1;
				flt[a][b][fl_wat_angle] = 0;
				flt[a][b][fl_wat_force] = 0;
			}
		}
	}
}

inline void water_go()
{
	tmp2[0] = 0.01;
	if (eg(fl_wat) + eg(fl_height) > vs(fl_wat) + vs(fl_height))
	{
		tmp2[1] = (eg(fl_wat) + eg(fl_height)) - (vs(fl_wat) + vs(fl_height));
		tmp2[0] * tmp2[1];
		comb_vv(egw(fl_wat_angle), egw(fl_wat_force), eg(fl_wat_angle), eg(fl_wat_force), mw * M_PI / 4, tmp2[0]);
	}
}

inline void water_flow()
{
	if (eg(fl_wat_force) > 0)
	{
		tmp2[1] = 0.9;
		tmp2[0] = dir_force(eg(fl_wat_angle), mw * M_PI / 4) * eg(fl_wat_force) * 0.1 * random();
		tmp2[0] = reru(tmp2[0] / eg(fl_wat)) * eg(fl_wat);

		comb_vv(vsw(fl_wat_angle), vsw(fl_wat_force), vs(fl_wat_angle), vs(fl_wat_force), eg(fl_wat_angle), eg(fl_wat_force) * tmp2[0] / eg(fl_wat) * tmp2[1]);
		comb_vv(egw(fl_wat_angle), egw(fl_wat_force), eg(fl_wat_angle), eg(fl_wat_force), eg(fl_wat_angle), -eg(fl_wat_force) * tmp2[0] / eg(fl_wat));

		*vsw(fl_wat) += tmp2[0];
		*egw(fl_wat) -= tmp2[0];
	}
}


void gnd_flow()
{
	if (eg(fl_wat) > 0 && eg(fl_wat_force) > 0)
	{
		tmp2[0] = dir_force(eg(fl_wat_angle), mw * M_PI / 4) * eg(fl_wat_force);
		tmp2[0] = reru(tmp2[0] / eg(fl_wat)) * eg(fl_wat);

		comb_vv(vsw(fl_wat_angle), vsw(fl_wat_force), vs(fl_wat_angle), vs(fl_wat_force), eg(fl_wat_angle), eg(fl_wat_force) * tmp2[0] / eg(fl_wat));
		comb_vv(egw(fl_wat_angle), egw(fl_wat_force), eg(fl_wat_angle), eg(fl_wat_force), eg(fl_wat_angle), -eg(fl_wat_force) * tmp2[0] / eg(fl_wat));

		*vsw(fl_wat) += tmp2[0];
		*egw(fl_wat) -= tmp2[0];
	}
}