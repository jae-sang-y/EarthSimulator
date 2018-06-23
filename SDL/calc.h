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
	c[0] = (unsigned char)(d[0] * (1 - f) + e[0] * f);
	c[1] = (unsigned char)(d[1] * (1 - f) + e[1] * f);
	c[2] = (unsigned char)(d[2] * (1 - f) + e[2] * f);
	c[3] = (unsigned char)(d[3] * (1 - f) + e[3] * f);
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

void hsv_to_rgb(unsigned char *cc, double h)
{
	double hh;
	double c[3] = { 0.0, };
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
	cc[0] = (unsigned char)c[0];
	cc[1] = (unsigned char)c[1];
	cc[2] = (unsigned char)c[2];
	cc[3] = (unsigned char)c[3];
}

double xy2dir(double x, double y)
{
	if (x == 0)
	{
		if (y > 0)
		{
			return M_PI / 2;
		}
		else if (y < 0)
		{
			return M_PI / 2 * 3;
		}
	}
	else if (x < 0)
	{
		return atan(y / x) + M_PI;
	}
	else
	{
		if (y >= 0)
		{
			return atan(y / x);
		}
		else if (y < 0)
		{
			return atan(y / x) + 2 * M_PI;
		}
	}
}

void comb_vv(double *D, double *L, double d1, double l1, double d2, double l2)
{
	double x, y;
	x = l1 * sin(d1) + l2 * sin(d2);
	y = l1 * cos(d1) + l2 * cos(d2);

	*L = sqrt(pow(x,2) + pow(y,2));
	*D = (xy2dir(x, y));
	if (_isnan(*D))
	{
		*D = 0;
	}

	return;
}

const int c2i(const int r, const int g, const int b)
{
	return r * 256 * 256 + g * 256 + b;
}