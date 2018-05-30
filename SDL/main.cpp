#include "mainf.h"

int main(int argc, char* args[])
{
	system("color 01");
	LOG_H("Hello");
	if (!init())
	{
		LOG_W("System Initialize Failed");
	}
	else
	{
		if (!loadMedia())
		{
			LOG_W("System Load Failed");
		}
		else
		{
			//SDL_Delay(20000);
			SDL_Event e;
			while (!quit)
			{
				event(&e);
				step();
				draw();
			}
		}
	}

	close();

	LOG_Stop();

	return 0;
}

void step()
{
	map_step();
	T = (++T) % T_max;
	//Mix_PlayMusic(gMusic, 0);
}
void draw()
{
	SDL_SetRenderDrawColor(REND, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(REND);


	SDL_Texture* t = NULL;
	SDL_Rect r;
	set_rect(&r, 0, 0, 100, 100);

	//SDL_RenderCopy(REND, sprite[2], NULL, NULL);

	//public_string = "Fuck you";
	unsigned char color[4];
	//t = draw_string(c_black);
	//SDL_RenderCopy(REND, t, NULL, &r);
	for (int a = 0; a < map_w; a++)
	{
		for (int b = 0; b < map_h; b++)
		{
			set_rect(&r, mgr_size * a, mgr_size * b, mgr_size, mgr_size);

			map_color(color, a, b);
			in0_255(&color[0]);
			in0_255(&color[1]);
			in0_255(&color[2]);
			in0_255(&color[3]);
			SDL_SetRenderDrawColor(REND, color[0], color[1], color[2], color[3]);

			SDL_RenderFillRect(REND, &r);
			//SDL_RenderCopy(REND, sprite[2], NULL, &r);
		}
	}
	/*if (Say == 0)
	{
		SDL_RenderCopy(REND, sprite[0], NULL, &r);
	}
	else
	{
		SDL_RenderCopy(REND, sprite[1], NULL, &r);
	}*/
	SDL_RenderPresent(REND);

}

void set_rect(SDL_Rect *r, int x, int y, int w, int h)
{
	r->x = x;
	r->y = y;
	r->w = w;
	r->h = h;
}
void set_rect(SDL_Rect *r, int x, int y)
{
	r->x = x;
	r->y = y;
}
SDL_Texture* draw_string(SDL_Color fg)
{
	TTF_Font* ft = def_font;
	SDL_Surface* textSurface = TTF_RenderText_Solid(def_font, "Fuck", fg);
	if (textSurface == NULL)
	{
		LOG_W("Failed Draw String : ", TTF_GetError());
	}
	static SDL_Texture *temp_texture = SDL_CreateTextureFromSurface(REND, textSurface);
	SDL_FreeSurface(textSurface);
	//ft = NULL;
	return temp_texture;
}

bool init()
{
	char curDir[1000];
	_getcwd(curDir, 1000);
	currentDir = curDir;
	LOG_H("This Programm run in ", currentDir);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		LOG_W("SDL_INIT Failed : ", SDL_GetError());
		return false;
	}
	WNDW = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (WNDW == NULL)
	{
		LOG_W("WIN_INIT Failed : ", SDL_GetError());
		return false;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG_W("MIX_INIT Failed : ", Mix_GetError());
		return false;
	}
	SURF = SDL_GetWindowSurface(WNDW);
	REND = SDL_CreateRenderer(WNDW, -1, SDL_RENDERER_ACCELERATED);
	if (REND == NULL)
	{
		LOG_W("RND_INIT Failed : ", SDL_GetError());
		return false;
	}
	/*if (!(IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG))
	{
		LOG_W("IMG_INIT Failed : ", IMG_GetError());
		return false;
	}*/
	if (TTF_Init() == -1)
	{
		LOG_W("TTF_INIT Failed : ", TTF_GetError());
		return false;
	}
	return true;
}
bool loadMedia()
{
	bool success = true;

	def_font = TTF_OpenFont((currentDir + "\\" + "ttf\\consola.ttf").c_str(), 28);

	gMusic = Mix_LoadMUS((currentDir + "\\" + "music\\test.wav").c_str());
	if (gMusic == NULL)
	{
		LOG_W("MUSIC_FILE is CORRUPT in " + currentDir + "music\\test.wav");
	}

	for (int a = 0; a < sizeof sprite_file / sizeof sprite_file[0]; a++)
	{
		if (sprite_file[a] != "")
		{
			sprite_surf[a] = IMG_Load((currentDir + "\\" + sprite_file[a]).c_str());
			if (sprite_surf[a] == NULL)
			{
				LOG_W("SPRITE_FILE is CORRUPT in " + to_string(a) + "\n" + currentDir + "\\" + sprite_file[a] + "\n");
				success = false;
			}
			else
			{
				//SDL_SetColorKey(sprite_surf[2], SDL_TRUE, SDL_MapRGB(sprite_surf[2]->format, 0, 0, 0));
				SDL_SetColorKey(sprite_surf[a], SDL_TRUE, SDL_MapRGB(sprite_surf[a]->format, 0, 0, 0));
				LOG_O(("SPRITE_FILE is LOADED in " + to_string(a)));

				sprite[a] = SDL_CreateTextureFromSurface(REND, sprite_surf[a]);
				if (sprite[a] == NULL)
				{
					LOG_W("FAILED MAKE TEXTURE in " + to_string(a), SDL_GetError());
					success = false;
				}
				else
				{
					SDL_FreeSurface(sprite_surf[a]);
				}
			}
		}
		else
		{
			LOG_A(("SPRITE_FILE is EMPTY in " + to_string(a)));
		}
	}
	map_set();


	return success;
}
void close()
{
	TTF_CloseFont(def_font);
	def_font = NULL;

	Mix_FreeMusic(gMusic);


	for (int a = 0; a < MAX_SPRITE; a++)
	{
		if (sprite[a] != NULL)
		{
			SDL_DestroyTexture(sprite[a]);
			sprite[a] = NULL;
		}
		if (texture[a] != NULL)
		{
			SDL_DestroyTexture(texture[a]);
			texture[a] = NULL;
		}
	}

	SDL_DestroyRenderer(REND);
	SDL_DestroyWindow(WNDW);
	REND = NULL;
	WNDW = NULL;
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

Uint32 color(int r, int g, int b)
{
	return r * 65536 + g * 256 + b;
}

void LOG_A(string s)
{
	cout << ESCAPE << "[1;33m[Attention]" << ESCAPE << "[1;37m " << s << "\n";
	//cout << ESCAPE << "[1;30m" << "Hello!" << "\n";//Black
	//cout << ESCAPE << "[1;31m" << "Hello!" << "\n";//Red
	//cout << ESCAPE << "[1;32m" << "Hello!" << "\n";//Green
	//cout << ESCAPE << "[1;33m" << "Hello!" << "\n";//Yellow
	//cout << ESCAPE << "[1;34m" << "Hello!" << "\n";//Blue
	//cout << ESCAPE << "[1;35m" << "Hello!" << "\n";//Purple
	//cout << ESCAPE << "[1;36m" << "Hello!" << "\n";//SkyBlue
	//cout << ESCAPE << "[1;37m" << "Hello!" << "\n";
	//cout << ESCAPE << "[1;93m" << "Hello!" << "\n";
}
void LOG_W(string s)
{
	cout << ESCAPE << "[1;31m[Warning]" << ESCAPE << "[1;37m " << s << "\n";
}
void LOG_H(string s)
{
	cout << ESCAPE << "[1;34m[Info]" << ESCAPE << "[1;37m " << s << "\n";
}
void LOG_O(string s)
{
	cout << ESCAPE << "[1;32m[OK]" << ESCAPE << "[1;37m " << s << "\n";
}
void LOG_A(string s, string s2)
{
	cout << ESCAPE << "[1;33m[Info]" << ESCAPE << "[1;37m " << s << " : " << s2 << "\n";
}
void LOG_W(string s, string s2)
{
	cout << ESCAPE << "[1;31m[Warning]" << ESCAPE << "[1;37m " << s << " : " << s2 << "\n";
}
void LOG_H(string s, string s2)
{
	cout << ESCAPE << "[1;34m[Info]" << ESCAPE << "[1;37m " << s << " : " << s2 << "\n";
}
void LOG_O(string s, string s2)
{
	cout << ESCAPE << "[1;33m[OK]" << ESCAPE << "[1;37m " << s << " : " << s2 << "\n";
}
void LOG_Stop()
{
	string a;
	cout << "Press Any Key to Continue...";
	getchar();
	return;
}