#pragma once

///////////////////////////
//          MAP          //
///////////////////////////
const unsigned int map_w = 384;
const unsigned int map_h = 216;
const unsigned int map_opt = 16;


unsigned int tip[map_w][map_h][map_opt] = { { { 0 }, }, };
double flt[map_w][map_h][map_opt] = { { { 0 }, }, };

const int con_num = 16;
enum { mp_con,
	mp_geo, mp_sun,
	grp_con_border,
	con_carray_food
};
enum {
	fl_food, fl_last_food, fl_food_crease,
	fl_mat, fl_cst, fl_move
};

///////////////////////////
//      MAP GRAPHICS     //
///////////////////////////

unsigned int mgr = 3;
const unsigned int mgr_size = 5;
unsigned char mgr_a[4];
unsigned char mgr_b[4];
double the_time = 0;

///////////////////////////
//        MAP CACUL      //
///////////////////////////

const int mca_w[8][2] = { { 1,0 },{ 1, -1 },{ 0, -1 },{ -1,-1 },{ -1,0 },{ -1, 1 },{ 0,1 },{ 1,1 } };
int me_x = 0, me_y = 0, yu_x = 0, yu_y = 0, mw = 0;

///////////////////////////
//          TEMP         //
///////////////////////////

int tmp[256];
double tmp2[256];

///////////////////////////
//           GEO         //
///////////////////////////

class geo {
public:
	unsigned char color[3] = {0,};
	void set_color(int r, int g, int b);
	void set_ant_color(unsigned char *c);
	bool compare(int r, int g, int b);
	double food_eff = 0;
	double food_max = 0;
	double move_eff = 0;
	double bild_eff = 0;
	bool in_wat = false;
};
void geo::set_color(int r, int g, int b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
}
void geo::set_ant_color(unsigned char *c)
{
	for (int a = 0; a < 3; a++)
	{
		c[a] = color[a];
	}
}
bool geo::compare(int r, int g, int b)
{
	if (r == color[0] && g == color[1] && b == color[2])
	{
		return true;
	}
	return false;
}

geo geo_list[6];

class con {

};

con con_list[con_num];

class POP {
public:
	unsigned int id = 0;
	unsigned int size = 0;

};

POP pop[map_w][map_h][25];