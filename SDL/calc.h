#pragma once

void rand_pos(int* x, int* y)
{
	*x = rand() % map_w;
	*y = rand() % map_h;
	return;
}

double random()
{
	return rand() / 32767.0;
}

void in0_1(double *p)
{
	if (*p < 0) { *p = 0; }
	else if (*p > 1) { *p = 1; }
}
void in_1_1(double *p)
{
	if (*p < -1) { *p = 1; }
	else if (*p > 1) { *p = 1; }
}
void in0_255(unsigned char *p)
{
	if (*p < 0) { *p = 0; }
	else if (*p > 255) { *p = 255; }
}

void merge_color(unsigned char *c, unsigned char *d, unsigned char *e, double f)
{
	in0_1(&f);
	c[0] = d[0] * (1 - f) + e[0] * f;
	c[1] = d[1] * (1 - f) + e[1] * f;
	c[2] = d[2] * (1 - f) + e[2] * f;
	c[3] = d[3] * (1 - f) + e[3] * f;
}
void set_color(unsigned char *c, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	c[0] = r;
	c[1] = g;
	c[2] = b;
	c[3] = a;
}

double dir_force(double a, double b)
{
	if (abs(a - b) < (M_PI / 2))
	{
		return ((1 - (abs(a - b) / (M_PI / 2)))) / 2;
	}
	else if (abs(a - b) > (M_PI / 2 * 3))
	{
		return ((1 - ((2 * M_PI - abs(a - b)) / (M_PI / 2)))) / 2;
	}
	return 0;
}