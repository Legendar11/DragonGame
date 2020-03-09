#ifndef SDL_EVENTOBJECT_H_INCLUDED
#define SDL_EVENTOBJECT_H_INCLUDED


#include "SDL_StaticObject.h"

struct SDL_EventObject : public SDL_StaticObject
{
	std::vector<SDL_Texture*> creature_Event;
	int counterEvent;
	int chanceEvent;
	bool Event;
	TimeStruct* timeEvent;

	SDL_EventObject(
		SDL_Renderer* render,
		std::string fileCreature,
		std::string folderEvent,
		double _periodEvent,
		int _chanceEvent,
		SDL_Rect _rect_face,
		std::string folderPathAgony = "",
		std::string fileDestroyed = "",
		bool _needUpdate = true,
		bool _agony = false,
		bool _destroyed = false,
		double _timeAgony = 5.0,
		double _timeDead = 5.0
	)
		: SDL_StaticObject(render, fileCreature, _rect_face, folderPathAgony, fileDestroyed,
			_needUpdate, _agony, _destroyed, _timeAgony, _timeDead),
		Event(false), chanceEvent(_chanceEvent), counterEvent(0)
	{
		creature_Event = GetTexturesFromFolder(render, folderEvent);

		timeEvent = new TimeStruct(1000 * _periodEvent, 1000 * 2 * _periodEvent, 1000 * _periodEvent);
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

	~SDL_EventObject()
	{
		SDL_DestroyTexture(creature);
	}

	void GenerateEvent()
	{
		if (!Event)
		{
			timeEvent->timeStart = SDL_GetTicks();
			if (timeEvent->timeStart >= timeEvent->timeEnd)
			{
				timeEvent->timeStart = SDL_GetTicks();
				timeEvent->timeEnd = timeEvent->timeEnd + timeEvent->Iter;

				if(rand() % chanceEvent) Event = true;
			}
			//std::cout << timeEvent->timeStart << "    " << timeEvent->timeEnd << std::endl;
		}
		else if (Event)
		{
			timeEvent->timeStart = SDL_GetTicks();
			if (timeEvent->timeStart >= timeEvent->timeEnd)
			{
				timeEvent->timeStart = SDL_GetTicks();
				timeEvent->timeEnd = timeEvent->timeEnd + timeEvent->Iter;

				Event = false;
			}
			//std::cout << timeEvent->timeStart << "    " << timeEvent->timeEnd << std::endl;
		}
	}

	virtual void Paint(SDL_Renderer* render)
	{
		GenerateEvent();

		if (destroyed)
		{
			timeDead->timeStart = SDL_GetTicks();
			timeDead->timeEnd += SDL_GetTicks();

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
			timeAgony->timeEnd += SDL_GetTicks();

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
			SDL_RenderCopy(render, creature, NULL, &rect_face);
			if (Event)
			{
				SDL_Texture*& sdl_Object = creature_Event[counterEvent++ % creature_Event.size()];
				SDL_RenderCopy(render, sdl_Object, NULL, &rect_face);
			}
			return;
		}
	}
};


#endif // SDL_EVENTOBJECT_H_INCLUDED
