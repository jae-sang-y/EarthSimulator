#pragma once
#define M_R2 0.70710678118654752440084436210485

inline double *egw(int i)
{
	return &(flt[me_x][me_y][i]);
}
inline const double eg(int i)
{
	return (flt[me_x][me_y][i]);
}

inline double *vsw(int i)
{
	return &(flt[yu_x][yu_y][i]);
}
inline const double vs(int i)
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
		}
	}
}
