#pragma once

const double M_E = std::exp(1.0);

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

void send(double *a, double ao, double a2, double *b, double bo, double b2, double ch)//b2 is change
{
	*a = a2 + (ch / bo * b2);
	*b = b2 - (ch / bo * b2);

	return;
}

double sigm(double d)
{
	return 1 / (1 + pow(M_E, -d));
}

double reru (double d)
{
	if (d >= 1)
	{
		return 1;
	}
	else if (d > 0)
	{
		return d;
	}
	return 0;
}

void hsv_to_rgb(unsigned char *c, double h)
{
	double hh;
	while (h >= 1) { h -= 1; }
	if (h <= 1 / 6.0)
	{
		hh = (h - 0 / 6.0) * 6;
		c[0] = 255;
		c[2] = 0;

		c[1] = 255 * hh;
	}
	else if (h <= 2 / 6.0)
	{
		hh = (h - 1 / 6.0) * 6;
		c[2] = 0;
		c[1] = 255;

		c[0] = 255 * (1 - hh);
	}
	else if (h <= 3 / 6.0)
	{
		hh = (h - 2 / 6.0) * 6;
		c[1] = 255;
		c[0] = 0;

		c[2] = 255 * hh;
	}
	else if (h <= 4 / 6.0)
	{
		hh = (h - 3 / 6.0) * 6;
		c[2] = 255;
		c[0] = 0;

		c[1] = 255 * (1 - hh);
	}
	else if (h <= 5 / 6.0)
	{
		hh = (h - 4 / 6.0) * 6;
		c[2] = 255;
		c[1] = 0;

		c[0] = 255 * hh;
	}
	else
	{
		hh = (h - 5 / 6.0) * 6;
		c[0] = 255;
		c[1] = 0;

		c[2] = 255 * (1 - hh);
	}
}