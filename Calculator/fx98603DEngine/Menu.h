#ifndef MENU_H
#define MENU_H

#include "GameStatus.h"
#include "Function.h"
#include "uString.h"
#include "Triangle.h"
#include "Point.h"
#include "ButtonUI.h"

extern "C"
{
#if _MSC_VER == 1200
	#include <fxlib.h>
#endif
	#include <stdio.h>
}


class Menu : public GameStatus
{	
	Function func[6];
	//funcSelector is the function the selector is over
	int funcSelector;
	
	//store buttions
	ButtonUI selectBut;
	ButtonUI drawBut;

	void PrintTitle();
	void PrintFunctions();
	void PrintUI();
	
public:
	//constructor
	Menu(Renderer* origRenderer);
	bool Input();
	bool Proccess();
	void Display();
	
	//for editText state
	//---
	uString& CurrentString();
	int GetFuncNum();
	bool SetCurrentFunction(const uString& text);
	//===

	//for grapher
	//---
	Function* GetFunctions();
	//===
	~Menu();

};

#endif