#ifndef SDL_ANIMATEDOBJECT_H_INCLUDED
#define SDL_ANIMATEDOBJECT_H_INCLUDED


#include "SDL_StaticObject.h"

class SDL_AnimatedObject : public SDL_StaticObject
{
private:
	std::vector<SDL_Texture*> anim_object;
	unsigned counter;

public:
	SDL_AnimatedObject(
		SDL_Renderer* render,
		std::string fileCreature,
		SDL_Rect _rect_face,
		std::string folderAnimated,
		std::string folderPathAgony = "",
		std::string fileDestroyed = "",
		bool _needUpdate = true,
		bool _agony = false,
		bool _destroyed = false,
		double _timeAgony = 5.0,
		double _timeDead = 5.0)
		: SDL_StaticObject(render, fileCreature, _rect_face, folderPathAgony, fileDestroyed,
			_needUpdate, _agony, _destroyed, _timeAgony, _timeDead)
	{
		anim_object = GetTexturesFromFolder(render, folderAnimated);
		counter = rand() % anim_object.size();
	}

	void Paint(SDL_Renderer* render)
	{
		if (destroyed)
		{
			if (timeDead->timeStart < timeDead->timeEnd)
			{
				SDL_RenderCopy(render, creature_destroyed, NULL, &rect_face);
			}
			else
			{
				agony = false;
				destroyed = false;
				needUpdate = false;
			}
			return;
		}

		if (agony)
		{
			timeAgony->timeStart = SDL_GetTicks();

			if (timeAgony->timeStart < timeAgony->timeEnd)
			{
				SDL_Texture*& sdl_Object = creature_agony[counterAgony++ % creature_agony.size()];
				SDL_RenderCopy(render, sdl_Object, NULL, &rect_face);
			}
			else
			{
				agony = false;
				destroyed = true;
			}
			return;
		}

		if (needUpdate)
		{
			SDL_Texture*& sdl_Object = anim_object[counter++ % anim_object.size()];
			SDL_RenderCopy(render, sdl_Object, NULL, &rect_face);
			return;
		}

	}

	bool NeedUpdate()
	{
		return needUpdate;
	}
};


#endif // SDL_ANIMATEDOBJECT_H_INCLUDED
