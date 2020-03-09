#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED


#include "Headers.h"

const int STANDART_COUNT_HOUSES = 70;
const int STANDART_COUNT_FLAMES = 50;

const int FIRE_WIDTH = 70, FIRE_HEIGHT = 100;
const int PLAYER_WIDTH = 200, PLAYER_HEIGHT = 150;

const int MENU_WIDTH = 500, MENU_HEIGHT = 200;
const int MENU_STARTX = 430, MENU_STARTY = 50;

const int DEFAULT_HOUSE_WIDTH = 70, DEFAULT_HOUSE_HEIGHT = 100;


const std::string PATH_TO_EXE = "";

std::vector<SDL_Texture*> GetTexturesFromFolder(SDL_Renderer* render, std::string pathFolder)
{
	std::vector<SDL_Texture*> result;
	std::string searchPath = pathFolder + "*.png";

	WIN32_FIND_DATA FindFileData;
	HANDLE hf;

	hf = FindFirstFile(searchPath.c_str(), &FindFileData);

	if (hf != INVALID_HANDLE_VALUE)
	{
		do
		{
			std::string str = pathFolder + "\\" + FindFileData.cFileName;

			SDL_Texture* g = IMG_LoadTexture(render, str.c_str());

			result.push_back(g);
		} while (FindNextFile(hf, &FindFileData) != 0);
		FindClose(hf);
	}

	return result;
}

double GetCurTime()
{
	return (double)clock() / CLK_TCK;
}

#endif // TOOLS_H_INCLUDED
