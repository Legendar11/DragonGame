#ifndef SDL_STATICOBJECT_H_INCLUDED
#define SDL_STATICOBJECT_H_INCLUDED

#include "Tools.h"
#include "TimeStruct.h"

struct SDL_StaticObject
{
	SDL_Texture* creature;
	std::vector<SDL_Texture*> creature_agony;
	SDL_Texture* creature_destroyed;
	SDL_Rect rect_face;
	bool needUpdate;
	bool agony;
	unsigned counterAgony;
	bool destroyed;

	TimeStruct* timeAgony;
	TimeStruct* timeDead;

	SDL_StaticObject(
		SDL_Renderer* render,
		std::string fileCreature,
		SDL_Rect _rect_face,
		std::string folderPathAgony = "",
		std::string fileDestroyed = "",
		bool _needUpdate = true,
		bool _agony = false,
		bool _destroyed = false,
		double _timeAgony = 5.0,
		double _timeDead = 5.0
	)
		: creature(IMG_LoadTexture(render, fileCreature.c_str())),
		rect_face(_rect_face),
		creature_destroyed(fileDestroyed == "" ? creature : IMG_LoadTexture(render, fileDestroyed.c_str())),
		needUpdate(_needUpdate), destroyed(_destroyed), agony(_agony), counterAgony(0)
	{
		timeAgony = new TimeStruct(0, 1000 * _timeAgony);
		timeDead = new TimeStruct(0, 1000 * _timeDead);

		if (folderPathAgony == "")
		{
			creature_agony.push_back(creature);
		}
		else
		{
			creature_agony = GetTexturesFromFolder(render, folderPathAgony);
		}
	}

	~SDL_StaticObject()
	{
		SDL_DestroyTexture(creature);
	}

	virtual void Paint(SDL_Renderer* render)
	{
		if (destroyed)
		{
			SDL_RenderCopy(render, creature_destroyed, NULL, &rect_face);
			return;
		}

		if (agony)
		{
			SDL_Texture*& sdl_Object = creature_agony[counterAgony++ % creature_agony.size()];
			SDL_RenderCopy(render, sdl_Object, NULL, &rect_face);
			return;
		}

		if (needUpdate)
		{
			SDL_RenderCopy(render, creature, NULL, &rect_face);
			return;
		}
	}
};

#endif // SDL_STATICOBJECT_H_INCLUDED
