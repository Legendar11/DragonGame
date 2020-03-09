#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED


#include "SDL_StaticObject.h"

struct SDL_Menu
{
	SDL_Texture* Normal;
	SDL_Texture* OnHover;
	SDL_Rect rect_face;
	bool isSelected;

	SDL_Menu(
		SDL_Renderer* render,
		std::string fileNormal,
		std::string fileOnHover,
		SDL_Rect _rect_face
	)
		: Normal(IMG_LoadTexture(render, fileNormal.c_str())),
		OnHover(IMG_LoadTexture(render, fileOnHover.c_str())),
		rect_face(_rect_face), isSelected(false)
	{

	}

	~SDL_Menu()
	{
		SDL_DestroyTexture(Normal);
		SDL_DestroyTexture(OnHover);
	}

	virtual void Paint(SDL_Renderer* render)
	{
		if (isSelected == false)
		{
			SDL_RenderCopy(render, Normal, NULL, &rect_face);
		}
		else
		{
			SDL_RenderCopy(render, OnHover, NULL, &rect_face);
		}
	}
};


#endif // MENU_H_INCLUDED
