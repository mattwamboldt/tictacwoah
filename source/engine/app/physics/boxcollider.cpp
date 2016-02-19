#include "boxcollider.h"
#include <app\application.h>

BoxCollider::BoxCollider() : width(0), height(0), enabled(true)
{
	color.a = color.r = color.g = color.b = 255;
}

BoxCollider::BoxCollider(int x, int y, int width, int height, SDL_Color color)
	: position((float)x, (float)y), width(width), height(height), color(color)
{}

void BoxCollider::Update(float delta)
{
	if (totalAnimTime > 0.0f)
	{
		animTime += delta;
		if (animTime >= totalAnimTime)
		{
			totalAnimTime = 0.0f;
			position.x = (float)destx;
			position.y = (float)desty;
		}
		else
		{
			position.x += (destx - position.x) * (animTime / totalAnimTime);
			position.y += (desty - position.y) * (animTime / totalAnimTime);
		}
	}

	position.x += (velocity.x * delta);
	position.y += (velocity.y * delta);
}

void BoxCollider::Render() const
{
	SDL_Renderer* renderer = gApp->Renderer();
	SDL_Rect fillRect = { (int)(position.x), (int)(position.y), width, height };
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &fillRect);
}

void BoxCollider::Move(int x, int y, float time)
{
	destx = x;
	desty = y;
	animTime = 0.0f;
	totalAnimTime = time;
}

bool BoxCollider::Intersects(const BoxCollider& box)
{
	return !(position.x > box.position.x + box.width
		|| position.x + width < box.position.x
		|| position.y > box.position.y + box.height
		|| position.y + height < box.position.y);
}

void BoxCollider::Speed(float val)
{
	speed = val;
	velocity = velocity.Normalize() * speed;
}

float BoxCollider::Speed()
{
	return speed;
}