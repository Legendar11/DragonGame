#ifndef SDL_KEYBOARD_H_INCLUDED
#define SDL_KEYBOARD_H_INCLUDED


#include "SDL_Player.h"
#include "SDL_Menu.h"

class SDL_Keyboard
{
private:
	const Uint8 *keyboardState;
	SDL_Player* player;

	void move_UP(SDL_Renderer* render, SDL_Texture* texture, SDL_Rect &destrect, int offset = 5)
	{
		destrect.y -= offset;
		SDL_RenderClear(render);
		SDL_RenderCopy(render, texture, NULL, &destrect);
	}

	void move_DOWN(SDL_Renderer* render, SDL_Texture* texture, SDL_Rect &destrect, int offset = 5)
	{
		destrect.y += offset;
		SDL_RenderClear(render);
		SDL_RenderCopy(render, texture, NULL, &destrect);
	}

	void move_LEFT(SDL_Renderer* render, SDL_Texture* texture, SDL_Rect &destrect, int offset = 5)
	{
		destrect.x -= offset;
		SDL_RenderClear(render);
		SDL_RenderCopy(render, texture, NULL, &destrect);
	}

	void move_RIGHT(SDL_Renderer* render, SDL_Texture* texture, SDL_Rect &destrect, int offset = 5)
	{
		destrect.x += offset;
		SDL_RenderClear(render);
		SDL_RenderCopy(render, texture, NULL, &destrect);
	}

public:
	SDL_Keyboard(SDL_Player* player)
	{
		this->player = player;
		keyboardState = SDL_GetKeyboardState(NULL);
		if(player) this->player->SetMove(PLAYER_MOVE::RIGHT);
	}

	int check_Score()
	{
		if ((keyboardState[SDL_SCANCODE_SPACE]))
		{
			return 1;
		}
		return 0;
	}

	int check_Menu(SDL_Renderer *&ren, std::vector<SDL_Menu*> sdl_menu)
	{
		if ((keyboardState[SDL_SCANCODE_UP]) || (keyboardState[SDL_SCANCODE_W]))
		{
			int index = 0; for (int i = 0; i < sdl_menu.size(); i++)
			{
				if (sdl_menu[i]->isSelected)
				{
					sdl_menu[i]->isSelected = false;
					index = i;
					break;
				}
			}
			if (index == 0)
			{
				sdl_menu[sdl_menu.size() - 1]->isSelected = true;
			}
			else
			{
				sdl_menu[index - 1]->isSelected = true;
			}
		}

		if ((keyboardState[SDL_SCANCODE_DOWN]) || (keyboardState[SDL_SCANCODE_S]))
		{
			int index = 0; for (int i = 0; i < sdl_menu.size(); i++)
			{
				if (sdl_menu[i]->isSelected)
				{
					sdl_menu[i]->isSelected = false;
					index = i;
					break;
				}
			}
			if (index == sdl_menu.size() - 1)
			{
				sdl_menu[0]->isSelected = true;
			}
			else
			{
				sdl_menu[index + 1]->isSelected = true;
			}
		}

		if ((keyboardState[SDL_SCANCODE_RETURN]))
		{
			int index = 0; for (int i = 0; i < sdl_menu.size(); i++)
			{
				if (sdl_menu[i]->isSelected)
				{
					return i;
				}
			}
		}

		return -1;
	}

	void move_CHECK(SDL_Renderer *&ren, SDL_StaticObject* sdl_object)
	{
		if (sdl_object)
		{
			if ((keyboardState[SDL_SCANCODE_UP]) || (keyboardState[SDL_SCANCODE_W]))
			{
				move_UP(ren, sdl_object->creature, sdl_object->rect_face);
				//player_move = SDL_Player::PLAYER_MOVE::UP;
			}

			if ((keyboardState[SDL_SCANCODE_DOWN]) || (keyboardState[SDL_SCANCODE_S]))
			{
				move_DOWN(ren, sdl_object->creature, sdl_object->rect_face);
				//player_move = SDL_Player::PLAYER_MOVE::DOWN;
			}
			if ((keyboardState[SDL_SCANCODE_LEFT]) || (keyboardState[SDL_SCANCODE_A]))
			{
				move_LEFT(ren, sdl_object->creature, sdl_object->rect_face);
				if (player) player->SetMove(PLAYER_MOVE::LEFT);
			}
			if ((keyboardState[SDL_SCANCODE_RIGHT]) || (keyboardState[SDL_SCANCODE_D]))
			{
				move_RIGHT(ren, sdl_object->creature, sdl_object->rect_face);
				if (player) player->SetMove(PLAYER_MOVE::RIGHT);
			}
			if ((keyboardState[SDL_SCANCODE_SPACE]))
			{
				if (player) player->setAttack(true);
			}
		}
	}

	SDL_Player* GetPlayer()
	{
		return player;
	}

};

#endif // SDL_KEYBOARD_H_INCLUDED
