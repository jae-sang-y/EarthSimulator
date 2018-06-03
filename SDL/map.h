#pragma once

///////////////////////////
//          MAP          //
///////////////////////////
const unsigned int map_w = 384;
const unsigned int map_h = 216;
const unsigned int map_opt = 16;


unsigned int tip[map_w][map_h][map_opt] = { { { 0 }, }, };
static double flt[map_w][map_h][map_opt] = { { { 0 }, }, };

const int cont_num = 20;
enum { mp_geo, mp_con, mp_contient };
enum {
	fl_food, fl_mat, fl_cst,
	fl_sun, fl_moon,
	fl_height, fl_heat, fl_mass, fl_press, fl_angle, fl_speed,//Solid
	fl_wat, fl_wat_angle, fl_wat_speed, fl_wat_heat, fl_wat_mat, //Water
	fl_gas, fl_gas_angle, fl_gas_heat //Gas
};

///////////////////////////
//      MAP GRAPHICS     //
///////////////////////////

unsigned int mgr = 4;
const unsigned int mgr_size = 5;
unsigned char mgr_a[4];
unsigned char mgr_b[4];
double the_time = 0;

///////////////////////////
//        MAP CACUL      //
///////////////////////////

const int mca_w[8][2] = { { 1,0 },{ 1, -1 },{ 0, -1 },{ -1,-1 },{ -1,0 },{ -1, 1 },{ 0,1 },{ 1,1 } };
int me_x = 0, me_y = 0, yu_x = 0, yu_y = 0;

///////////////////////////
//          TEMP         //
///////////////////////////

int tmp[256];
double tmp2[256];
