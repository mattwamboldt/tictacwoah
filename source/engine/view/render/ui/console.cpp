#include "console.h"

void Console::Init(TTF_Font* font, int width, int height, int x, int y)
{
	this->width = width;
	this->height = height;
	enabled = true;
	output.Init("", font, x, y);
	output.SetWrap(width);
	input.Init("", font, x, y + (height - TTF_FontHeight(font)));
	backing.width = width;
	backing.height = height;
	backing.x = x;
	backing.y = y;
	backing.color = { 0, 0, 0 };
}

void Console::Render()
{
	if (enabled)
	{
		backing.Render();
		output.Render();
		input.Render();
	}
}

void Console::HandleInput(SDL_KeyboardEvent key, bool isPress)
{
	if (enabled && isPress)
	{
		if (key.keysym.scancode == SDL_SCANCODE_RETURN || key.keysym.scancode == SDL_SCANCODE_RETURN)
		{
			handler->InputEntered(inputString);
			inputString.clear();
			input.SetText(inputString.c_str());
		}
		else if (key.keysym.scancode == SDL_SCANCODE_BACKSPACE && inputString.length() > 0)
		{
			inputString.erase(inputString.length() - 1);
			input.SetText(inputString.c_str());
		}
	}
}

void Console::WriteLine(string text)
{
	outputString += text;
	outputString += "\n";
	output.SetText(outputString.c_str());

	while (output.Height() > height - input.LineHeight())
	{
		outputString.erase(0, outputString.find("\n") + 1);
		output.SetText(outputString.c_str());
	}
}

void Console::HandleText(SDL_TextInputEvent textEvent)
{
	if (enabled)
	{
		if (textEvent.text)
		{
			inputString.append(textEvent.text);
			input.SetText(inputString.c_str());
		}
	}
}
