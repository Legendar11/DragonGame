#ifndef SDL_GAME_H_INCLUDED
#define SDL_GAME_H_INCLUDED

#include "SDL_EventObject.h"
#include "SDL_Player.h"
#include "SDL_AnimatedObject.h"
#include "SDL_Keyboard.h"
#include "SDL_Menu.h"
#include <fstream>

class SDL_Game
{
private:
	SDL_DisplayMode displayMode;
	SDL_Window* win;
	SDL_Renderer* ren;
	SDL_Keyboard* keyboard;

	SDL_StaticObject* background;
	SDL_Player* player;

	std::vector<SDL_EventObject*> event_objects;
	std::vector<SDL_StaticObject*> static_objects;
	std::vector<SDL_AnimatedObject*> anim_objects;
	std::vector<SDL_Menu*> menu_objects;

	Uint32 start;
	int FPS;
	int score;
	int time;
	int GameState;

	void SDL_FPS()
	{
		if (1000.0 / FPS > SDL_GetTicks() - start) {
			SDL_Delay(1000.0 / FPS - (SDL_GetTicks() - start));
		}
	}

	void WriteScore(std::string text, int x, int y)
	{
		SDL_Color clr; // Тип для цвета. 4 числа — R, G, B и A, соответственно.
		clr.r = 0;
		clr.g = 0;  // Зададим параметры цвета
		clr.b = 0;
		TTF_Font * fnt = TTF_OpenFont("BOD_BLAR.ttf", 50); // Загружаем шрифт по заданному адресу размером sz
		SDL_Rect dest;
		dest.x = x;
		dest.y = y;

		SDL_Surface * TextSurface = TTF_RenderText_Blended(fnt, text.c_str(), clr); // Переносим на поверхность текст с заданным шрифтом и цветом

		SDL_Rect src = { 0, 0, TextSurface->w, TextSurface->h };
		SDL_Rect dst = { x, y, TextSurface->w, TextSurface->h };
		SDL_RenderCopy(ren, SDL_CreateTextureFromSurface(ren, TextSurface), &src, &dst);
	}

	void AddRandomHouse()
	{
		int key = rand() % 4;

		switch (key)
		{
		case 0: this->AddEventObject(
			PATH_TO_EXE + "Live\\StaticObject\\HouseWhite\\HouseWhite.png",
			PATH_TO_EXE + "Live\\StaticObject\\Rabbit\\",
			5,
			2,
			DEFAULT_HOUSE_WIDTH, DEFAULT_HOUSE_HEIGHT,
			-1, -1,
			PATH_TO_EXE + "Live\\AnimatedObjects\\RabbitAgony\\",
			PATH_TO_EXE + "Dead\\House\\House.png"
		); break;

		case 1: this->AddEventObject(
			PATH_TO_EXE + "Live\\StaticObject\\Citadel\\Citadel.png",
			PATH_TO_EXE + "Live\\StaticObject\\Arbalet\\",
			5,
			4,
			DEFAULT_HOUSE_WIDTH, DEFAULT_HOUSE_HEIGHT, -1, -1,
			PATH_TO_EXE + "Live\\AnimatedObjects\\CitadelAgony\\",
			PATH_TO_EXE + "Dead\\House\\House.png"
		); break;

		case 2: this->AddEventObject(
			PATH_TO_EXE + "Live\\StaticObject\\HouseHobbit\\HouseHobbit.png",
			PATH_TO_EXE + "Live\\StaticObject\\Rabbit\\",
			5,
			2,
			DEFAULT_HOUSE_WIDTH, DEFAULT_HOUSE_HEIGHT, -1, -1,
			PATH_TO_EXE + "Live\\AnimatedObjects\\RabbitAgony\\",
			PATH_TO_EXE + "Dead\\House\\House.png"
		); break;

		case 3: this->AddEventObject(
			PATH_TO_EXE + "Live\\StaticObject\\Polestar\\Polestar.png",
			PATH_TO_EXE + "Live\\StaticObject\\Rabbit\\",
			5,
			5,
			DEFAULT_HOUSE_WIDTH, DEFAULT_HOUSE_HEIGHT, -1, -1,
			PATH_TO_EXE + "Live\\AnimatedObjects\\RabbitAgony\\",
			PATH_TO_EXE + "Dead\\House\\House.png"
		); break;

		default:break;
		}
	}

	void AddEventObjects()
	{
		for (int i = 0; i < STANDART_COUNT_HOUSES; i++)
		{
			AddRandomHouse();
		}
	}

	void AddAnimtedObject()
	{
		for (int i = 0; i < STANDART_COUNT_FLAMES; i++)
		{
			this->AddAnimatedObject(
				PATH_TO_EXE + "Live\\AnimatedObjects\\SpiritFlame\\image_part_001.png",
				PATH_TO_EXE + "Live\\AnimatedObjects\\SpiritFlame\\",
				FIRE_WIDTH, FIRE_HEIGHT, -1, -1);
		}
	}

	void AddMenu()
	{
		this->AddMenu(
			PATH_TO_EXE + "Menu\\Start\\Normal.png",
			PATH_TO_EXE + "Menu\\Start\\OnHover.png",
			MENU_WIDTH, MENU_HEIGHT, MENU_STARTX, MENU_STARTY
		);

		this->AddMenu(
			PATH_TO_EXE + "Menu\\Scores\\Normal.png",
			PATH_TO_EXE + "Menu\\Scores\\OnHover.png",
			MENU_WIDTH, MENU_HEIGHT, MENU_STARTX, MENU_STARTY + MENU_HEIGHT + 40
		);

		this->AddMenu(
			PATH_TO_EXE + "Menu\\Exit\\Normal.png",
			PATH_TO_EXE + "Menu\\Exit\\OnHover.png",
			MENU_WIDTH, MENU_HEIGHT, MENU_STARTX, MENU_STARTY + MENU_HEIGHT * 2 + 40
		);
	}

public:
	SDL_Game(std::string NameWindow = "GameWindow", int _FPS = 30) : FPS(_FPS), score(0), time(60 * 10)
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		SDL_GetDesktopDisplayMode(0, &displayMode);
		win = SDL_CreateWindow(NameWindow.c_str(), 0, 0, displayMode.w, displayMode.h, SDL_WINDOW_SHOWN);
		ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		TTF_Init();
		GameState = 0;
	}

	~SDL_Game()
	{
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
	}

	bool CheckOnAttack(SDL_StaticObject* sdl_object) const
	{
		if (player->getAttack())
		{
			if (player->GetMove() == PLAYER_MOVE::RIGHT)
			{
				if (sdl_object->rect_face.x >= player->GetAttackBoom().x
					&& (sdl_object->rect_face.x + sdl_object->rect_face.w) <= (player->GetAttackBoom().x + player->GetAttackBoom().w)
					&& sdl_object->rect_face.y >= player->GetAttackBoom().y
					&& (sdl_object->rect_face.y + sdl_object->rect_face.h) <= (player->GetAttackBoom().y + player->GetAttackBoom().h))
				{
					return true;
				}
			}

			if (player->GetMove() == PLAYER_MOVE::LEFT)
			{
				if (sdl_object->rect_face.x >= player->GetAttackBoom().x
					&& (sdl_object->rect_face.x + sdl_object->rect_face.w) <= (player->GetAttackBoom().x + player->GetAttackBoom().w)
					&& sdl_object->rect_face.y >= player->GetAttackBoom().y
					&& (sdl_object->rect_face.y + sdl_object->rect_face.h) <= (player->GetAttackBoom().y + player->GetAttackBoom().h))
				{
					return true;
				}
			}
		}
		return false;
	}

	void Render()
	{
		start = SDL_GetTicks();

		SDL_RenderClear(ren);

		if (GameState == 0)
		{
			AddBackground(PATH_TO_EXE + "Background\\background.bmp");

			menu_objects.clear(); AddMenu();

			menu_objects[0]->isSelected = true;

			keyboard = new SDL_Keyboard(player = NULL);

			GameState = 1;
		}

		if (GameState == 1)
		{
			SDL_RenderCopy(ren, background->creature, NULL, &background->rect_face);

			for (SDL_Menu*& SDL_ObjectGame : menu_objects)
			{
				SDL_ObjectGame->Paint(ren);
			}
		}

		if (GameState == 2)
		{
			time--;

			SDL_RenderCopy(ren, background->creature, NULL, &background->rect_face);

			for (SDL_StaticObject*& SDL_ObjectGame : static_objects)
			{
				if (SDL_ObjectGame->needUpdate)
				{
					SDL_ObjectGame->Paint(ren);
				}
			}

			for (SDL_EventObject*& SDL_ObjectGame : event_objects)
			{
				if (SDL_ObjectGame->needUpdate)
				{
					SDL_ObjectGame->Paint(ren);

					if (CheckOnAttack(SDL_ObjectGame))
					{
						if (SDL_ObjectGame->destroyed == false
							&& SDL_ObjectGame->agony == false
							&& SDL_ObjectGame->Event)
						{
							SDL_ObjectGame->agony = true;
							score += 5;
						}
						else
						{
							if (SDL_ObjectGame->destroyed == false
								&& SDL_ObjectGame->agony == false)
							{
								SDL_ObjectGame->destroyed = true;
								score += 1;
							}
						}
					}
				}
			}

			for (SDL_AnimatedObject*& SDL_ObjectGame : anim_objects)
			{
				if (SDL_ObjectGame->NeedUpdate())
				{
					SDL_ObjectGame->Paint(ren);
				}
			}

			player = keyboard->GetPlayer();

			player->Paint(ren);

			WriteScore("Your Score = " + std::to_string(score)
				+ "   Time = " + std::to_string(time), 0, 0);

			if (time < 0)
			{
				keyboard = new SDL_Keyboard(NULL);
				GameState = 4;
			}
		}

		if (GameState == 3)
		{
			SDL_RenderCopy(ren, background->creature, NULL, &background->rect_face);
			std::ifstream file_scores("scores.txt");
			int* scores = new int[10];

			for (int i = 0; i < 10; i++)
			{
				file_scores >> scores[i];
			}
			file_scores.close();

			for (int i = 0; i < 10; i++)
			{
				WriteScore("# " + std::to_string(i + 1) + ": Score = " + std::to_string(scores[i]), MENU_STARTX, (i + 1) * 50);
			}

			if (score != 0)
			{
				GameState = 4;
			}
		}

		if (GameState == 4)
		{
			std::cout << 1;
			std::ifstream file_scores("scores.txt");
			int* scores = new int[10];

			for (int i = 0; i < 10; i++)
			{
				file_scores >> scores[i];
			}
			file_scores.close();

			for (int i = 0; i < 10; i++)
			{
				if (score > scores[i])
				{
					for (int j = 10 - 1; j > i; j--)
					{
						scores[j] = scores[j - 1];
					}

					scores[i] = score;
					break;
				}
			}

			std::ofstream file_out("scores.txt");
			for (int i = 0; i < 10; i++)
			{
				file_out << scores[i] << std::endl;
			}
			file_out.close();

			WriteScore("YOUR Score = " + std::to_string(score), MENU_STARTX, 600);

			score = 0;
			GameState = 3;
		}

		SDL_RenderPresent(ren);

		SDL_FPS();
	}

	void AddAnimatedObject(SDL_AnimatedObject*& sdl_anim)
	{
		anim_objects.push_back(sdl_anim);
	}

	void AddPlayer(
		std::string fileCreature,
		std::string folderMoverUp,
		std::string folderMoverRight,
		std::string folderMoverDown,
		std::string folderMoverLeft,
		std::string folderFireAnimateLeft,
		std::string folderFireAnimateRight,
		std::string folderFireAttack,
		int width, int height,
		int x = 0, int y = 0,
		bool needUpdate = true
	)
	{
		player = new SDL_Player(
			ren,
			fileCreature,
			folderMoverUp, folderMoverRight, folderMoverDown, folderMoverLeft,
			folderFireAnimateLeft, folderFireAnimateRight,
			folderFireAttack,
			SDL_Rect{ x == -1 ? rand() % displayMode.w : x, y == -1 ? rand() % displayMode.h : y, width, height }
		);

		keyboard = new SDL_Keyboard(player);
	}

	void AddBackground(std::string filePath)
	{
		background = new SDL_StaticObject(
			ren,
			filePath,
			SDL_Rect{ 0, 0, displayMode.w, displayMode.h }
		);
	}

	void AddMenu(
		std::string fileNormal,
		std::string fileOnHover,
		int width, int height,
		int x, int y)
	{
		menu_objects.push_back(new SDL_Menu(
			ren,
			fileNormal,
			fileOnHover,
			SDL_Rect{ x, y, width, height }
		));
	}

	void AddStaticObject(
		std::string filePath,
		int width, int height,
		int x = 0, int y = 0,
		std::string filePathAgony = "",
		bool needUpdate = true)
	{
		static_objects.push_back(
			new SDL_StaticObject(
				ren,
				filePath,
				SDL_Rect{ x == -1 ? rand() % displayMode.w : x, y == -1 ? rand() % displayMode.h : y, width, height },
				filePathAgony
			)
		);
	}

	void AddEventObject(
		std::string filePath,
		std::string folderEvent,
		double period,
		int chanceEvent,
		int width, int height,
		int x = 0, int y = 0,
		std::string folderPathAgony = "",
		std::string filePathDestroyed = "",
		bool needUpdate = true)
	{
		event_objects.push_back(
			new SDL_EventObject(
				ren,
				filePath,
				folderEvent,
				period,
				chanceEvent,
				SDL_Rect{ x == -1 ? rand() % displayMode.w : x, y == -1 ? rand() % displayMode.h : y, width, height },
				folderPathAgony,
				filePathDestroyed
			)
		);
	}

	void AddAnimatedObject(std::string filePath,
		std::string folderAnimated,
		int width, int height,
		int x = 0, int y = 0, bool needUpdate = true)
	{
		anim_objects.push_back(
			new SDL_AnimatedObject(
				ren,
				filePath,
				SDL_Rect{ x == -1 ? rand() % displayMode.w : x, y == -1 ? rand() % displayMode.h : y, width, height },
				folderAnimated
			)
		);
	}

	void CheckEventKeyboard()
	{
		if (GameState == 1)
		{
			int key = keyboard->check_Menu(ren, menu_objects);
			if (key != -1)
			{
				if (key == 0)
				{
					AddPlayer(PATH_TO_EXE + "player.png", "",
						PATH_TO_EXE + "Live\\Player\\MoveRight\\",
						"",
						PATH_TO_EXE + "Live\\Player\\MoveLeft\\",
						PATH_TO_EXE + "Live\\Player\\FireAttackLeft\\",
						PATH_TO_EXE + "Live\\Player\\FireAttackRight\\",
						PATH_TO_EXE + "Live\\Player\\Boom\\",
						PLAYER_WIDTH, PLAYER_HEIGHT, -1, -1);

					AddEventObjects();

					AddAnimtedObject();

					GameState = 2;
				}

				if (key == 1) GameState = 3;
				if (key == 2) exit(0);
			}
		}

		if (GameState == 2)
		{
			keyboard->move_CHECK(ren, player);
		}

		if (GameState == 3)
		{
			if (keyboard->check_Score())
			{
				GameState = 1;
			}
		}
	}
};

#endif // SDL_GAME_H_INCLUDED
