#ifndef BOX_H
#define BOX_H

#include "SDL/SDL.h"
#include <app\core\math\vector.h>

//TODO: switch from screen space to world space
class BoxCollider
{
public:
	BoxCollider();
	BoxCollider(int x, int y, int width, int height, SDL_Color color);

	void Update(float delta);
	void Move(int x, int y, float time);
	bool Intersects(const BoxCollider& box);
	void Speed(float val);
	float Speed();

	// For debugging/prototyping only
	void Render() const;
	SDL_Color color;

	Vector2 position;
	Vector2 velocity;
	int width;
	int height;
	bool enabled;

private:
	int destx, desty;
	float animTime;
	float totalAnimTime;
	float speed;
};

#endif
