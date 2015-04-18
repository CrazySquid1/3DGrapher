#ifndef GRAPHICS_H
#define GRAPHICS_H




#if _MSC_VER == 1800
	#include <SDL.h>
#endif

#include "Mesh.h"

class Renderer
{
	friend class Triangle; //so triangle objects can use draw line
public:

	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;

#if _MSC_VER == 1800
	SDL_Window * gWindow;
	SDL_Renderer * gRenderer;
#endif


	//constructor
	Renderer(const int& width, const int& height);
	
#if _MSC_VER == 1800
	bool SetColour(const Uint8& r, const Uint8& g, const Uint8& b, const Uint8& a);
#endif

	void DrawLine(const int& x1, const int& y1, const int& x2, const int& y2) const;
	
	void PrintTextMini(const int& x, const int& y, unsigned char* s, const int& drawType) const;
	
	void PrintTextXY(const int& x, const int& y, unsigned char* s, const int& drawType) const;
	
	void DrawBox(const int& x1, const int& y1, const int& x2, const int& y2, bool inverted) const;
	
	void ClearScreen() const;
	
	void UpdateScreen() const;

	~Renderer();
};

#endif //GRAPHICS_H