#include "mainf.h"

int main(int argc, char* args[])
{
	srand(time(NULL));
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
			start();
			SDL_Event e;
			std::thread trd_ui(ui, &e);
			std::thread trd_step(step);

			while (!quit)
			{
				event(&e);
				//step();
				
				//ui(&e);
			}
			trd_ui.join();
			trd_step.join();
			
		}
	}
	close();
	LOG_Stop();
	return 0;
}

void start()
{
	msg.push_back(Message(msg_show, 200,70,"1972년 11월 21일"));
}
void step()
{
	while(!quit)
	{
		map_step();
		T = (++T) % T_max;
		the_time = (the_time + 0.0003);
		if (the_time > 1) { the_time -= 1; }
	}
	//Mix_PlayMusic(gMusic, 0);
}
void draw()
{
	SDL_SetRenderDrawColor(REND, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(REND);


	SDL_Texture* t = NULL;
	SDL_Rect r;

	unsigned char color[4];
	
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
}
void ui(SDL_Event *e)
{
	SDL_Rect r;
	int x, y;
	while(!quit)
	{
		draw();
		if (msg.size() > 0)
		{
			SDL_GetMouseState(&x, &y);
			if (e->type == SDL_MOUSEBUTTONDOWN)
			{
				global[glb_mousesx] = x;
				global[glb_mousesy] = y;
				bool effect = true;
				for (int a = 0; a < msg.size(); a++)
				{
					if (x > msg[a].x && y > msg[a].y && x < msg[a].x + msg[a].w && y < msg[a].y + 20 && effect)
					{
						msg[a].selected = true;
						global[glb_mousebx] = msg[a].x;
						global[glb_mouseby] = msg[a].y;
						effect = false;
						break;
					}
				}
			}
			else if (e->type == SDL_MOUSEMOTION)
			{
				if (msg.size() > 0)
				{
					for (int a = 0; a < msg.size(); a++)
					{
						if (msg[a].selected)
						{
							msg[a].x = x - global[glb_mousesx] + global[glb_mousebx];
							msg[a].y = y - global[glb_mousesy] + global[glb_mouseby];
							break;
						}
					}
				}
			}
			else if (e->type == SDL_MOUSEBUTTONUP)
			{
				for (int a = 0; a < msg.size(); a++)
				{
					msg[a].selected = false;
				}
			}
			global[glb_mousex] = x;
			global[glb_mousey] = y;
			for (int a = 0; a < msg.size(); a++)
			{
				set_rect(&r, msg[a].x, msg[a].y, msg[a].w, msg[a].h);
				SDL_RenderCopy(REND, sprite[8], NULL, &r);

				//SDL_SetRenderDrawColor(REND, 255, 255, 255, 255); 
				//SDL_RenderFillRect(REND, &r);
				set_rect(&r, msg[a].x, msg[a].y, msg[a].w, 20);
				if (msg[a].selected)
				{
					SDL_RenderCopy(REND, sprite[8], NULL, &r);
				}

				SDL_Texture* draw_text = draw_string(msg[a].sub, c_black);
				SDL_QueryTexture(draw_text, NULL, NULL, &r.w, &r.h);
				r.x += (msg[a].w - r.w) / 2;
				SDL_RenderCopy(REND, draw_text, NULL, &r);
				r.x -= (msg[a].w - r.w) / 2;

				r.y = msg[a].y + msg[a].h / 2 - 20;
				draw_text = draw_string("신정우는 오렌지병으로 사망했다.", c_black);
				SDL_QueryTexture(draw_text, NULL, NULL, &r.w, &r.h);
				r.x += (msg[a].w - r.w) / 2;
				SDL_RenderCopy(REND, draw_text, NULL, &r);
				r.x -= (msg[a].w - r.w) / 2;
			}
		}
		SDL_RenderPresent(REND);
	}
	
}


SDL_Texture* draw_string(std::string s, SDL_Color color) {

	SDL_Texture* t = SDL_CreateTextureFromSurface(REND, TTF_RenderUTF8_Solid(def_font, s.c_str(), color));
	
	return t;
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

bool init()
{
	setlocale(LC_ALL, "");
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

	def_font = TTF_OpenFont((currentDir + "\\" + "ttf\\NanumSquareR.ttf").c_str(), 20);

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
				LOG_W("SPRITE_FILE is CORRUPT in " + std::to_string(a) + "\n" + currentDir + "\\" + sprite_file[a] + "\n");
				success = false;
			}
			else
			{
				//SDL_SetColorKey(sprite_surf[2], SDL_TRUE, SDL_MapRGB(sprite_surf[2]->format, 0, 0, 0));
				SDL_SetColorKey(sprite_surf[a], SDL_TRUE, SDL_MapRGB(sprite_surf[a]->format, 0, 0, 0));
				LOG_O(("SPRITE_FILE is LOADED in " + std::to_string(a)));

				sprite[a] = SDL_CreateTextureFromSurface(REND, sprite_surf[a]);
				if (sprite[a] == NULL)
				{
					LOG_W("FAILED MAKE TEXTURE in " + std::to_string(a), SDL_GetError());
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
			LOG_A(("SPRITE_FILE is EMPTY in " + std::to_string(a)));
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

void LOG_A(std::string s)
{
	std::cout << ESCAPE << "[1;33m[Attention]" << ESCAPE << "[1;37m " << s << "\n";
	//std::cout << ESCAPE << "[1;30m" << "Hello!" << "\n";//Black
	//std::cout << ESCAPE << "[1;31m" << "Hello!" << "\n";//Red
	//std::cout << ESCAPE << "[1;32m" << "Hello!" << "\n";//Green
	//std::cout << ESCAPE << "[1;33m" << "Hello!" << "\n";//Yellow
	//std::cout << ESCAPE << "[1;34m" << "Hello!" << "\n";//Blue
	//std::cout << ESCAPE << "[1;35m" << "Hello!" << "\n";//Purple
	//std::cout << ESCAPE << "[1;36m" << "Hello!" << "\n";//SkyBlue
	//std::cout << ESCAPE << "[1;37m" << "Hello!" << "\n";
	//std::cout << ESCAPE << "[1;93m" << "Hello!" << "\n";
}
void LOG_W(std::string s)
{
	std::cout << ESCAPE << "[1;31m[Warning]" << ESCAPE << "[1;37m " << s << "\n";
}
void LOG_H(std::string s)
{
	std::cout << ESCAPE << "[1;34m[Info]" << ESCAPE << "[1;37m " << s << "\n";
}
void LOG_O(std::string s)
{
	std::cout << ESCAPE << "[1;32m[OK]" << ESCAPE << "[1;37m " << s << "\n";
}
void LOG_A(std::string s, std::string s2)
{
	std::cout << ESCAPE << "[1;33m[Info]" << ESCAPE << "[1;37m " << s << " : " << s2 << "\n";
}
void LOG_W(std::string s, std::string s2)
{
	std::cout << ESCAPE << "[1;31m[Warning]" << ESCAPE << "[1;37m " << s << " : " << s2 << "\n";
}
void LOG_H(std::string s, std::string s2)
{
	std::cout << ESCAPE << "[1;34m[Info]" << ESCAPE << "[1;37m " << s << " : " << s2 << "\n";
}
void LOG_O(std::string s, std::string s2)
{
	std::cout << ESCAPE << "[1;33m[OK]" << ESCAPE << "[1;37m " << s << " : " << s2 << "\n";
}
void LOG_Stop()
{
	std::string a;
	std::cout << "Press Any Key to Continue...";
	std::cin.ignore();
	return;
}