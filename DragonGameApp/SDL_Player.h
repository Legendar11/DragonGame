#ifndef SDL_PLAYER_H_INCLUDED
#define SDL_PLAYER_H_INCLUDED


#include "SDL_AnimatedObject.h"

enum class PLAYER_MOVE { UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3, STOP = 4};

class SDL_Player : public SDL_StaticObject
{
private:
	std::vector<SDL_Texture*> move_right;
	std::vector<SDL_Texture*> move_left;

	std::vector<SDL_Texture*> attack_right;
	std::vector<SDL_Texture*> attack_left;

	SDL_AnimatedObject* attack_boom;

	unsigned counter;
	unsigned counterAttack;
	unsigned counterBoom;
	bool isAttack;


public:
	SDL_Player(
		SDL_Renderer* render,
		std::string fileCreature,
		std::string folderMoverUp,
		std::string folderMoverRight,
		std::string folderMoverDown,
		std::string folderMoverLeft,
		std::string folderFireAnimateLeft,
		std::string folderFireAnimateRight,
		std::string folderFireAttack,
		SDL_Rect _rect_face,
		bool _needUpdate = true
	) : SDL_StaticObject(render, fileCreature, _rect_face),
		counter(0), isAttack(false), counterBoom(0)
	{
		move_right = GetTexturesFromFolder(render, folderMoverRight);
		move_left = GetTexturesFromFolder(render, folderMoverLeft);

		attack_right = GetTexturesFromFolder(render, folderFireAnimateRight);
		attack_left = GetTexturesFromFolder(render, folderFireAnimateLeft);

		attack_boom = new SDL_AnimatedObject(render, "", _rect_face, folderFireAttack);

		move = PLAYER_MOVE::RIGHT;
	}

	void SetMove(PLAYER_MOVE move)
	{
		this->move = move;
	}

	PLAYER_MOVE GetMove()
	{
		return move;
	}
	bool getAttack()
	{
		return isAttack;
	}

	void setAttack(bool isAttack)
	{
		this->isAttack = isAttack;
	}

	SDL_Rect GetAttackBoom()
	{
		return attack_boom->rect_face;
	}

	void Paint(SDL_Renderer* render)
	{
		if (isAttack)
		{
			if (move == PLAYER_MOVE::LEFT)
			{
				SDL_RenderCopy(render, attack_left[counterAttack++ % attack_left.size()], NULL, &rect_face);

				if (counter >= attack_left.size() - 1) isAttack = false;
			}

			if (move == PLAYER_MOVE::RIGHT)
			{
				SDL_RenderCopy(render, attack_right[counterAttack++ % attack_right.size()], NULL, &rect_face);

				if (counter >= attack_right.size() - 1) isAttack = false;
			}
			attack_boom->Paint(render);

			return;
		}

		switch (move)
		{
		case PLAYER_MOVE::UP:
			break;

		case PLAYER_MOVE::RIGHT:
			attack_boom->rect_face.x = rect_face.x + 150;
			SDL_RenderCopy(render, move_right[counter++ % move_right.size()], NULL, &rect_face);
			break;

		case PLAYER_MOVE::DOWN:
			break;

		case PLAYER_MOVE::LEFT:
			attack_boom->rect_face.x = rect_face.x - 150;
			SDL_RenderCopy(render, move_left[counter++ % move_left.size()], NULL, &rect_face);
			break;
		}

		attack_boom->rect_face.y = rect_face.y;
	}

private:
	PLAYER_MOVE move;
};

#endif // SDL_PLAYER_H_INCLUDED
