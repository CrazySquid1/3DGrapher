/*****************************************************************/
/*                                                               */
/*   CASIO fx-9860G SDK Library                                  */
/*                                                               */
/*   File name : [ProjectName].c                                 */
/*                                                               */
/*   Copyright (c) 2006 CASIO COMPUTER CO., LTD.                 */
/*                                                               */
/*****************************************************************/

extern "C"
{
	#include <fxlib.h>
}

#include "Grapher.h"
#include "Menu.h"


//****************************************************************************
//  AddIn_main (Sample program main function)
//
//  param   :   isAppli   : 1 = This application is launched by MAIN MENU.
//                        : 0 = This application is launched by a strip in eACT application.
//
//              OptionNum : Strip number (0~3)
//                         (This parameter is only used when isAppli parameter is 0.)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
extern "C" int AddIn_main(int isAppli, unsigned short OptionNum)
{
	bool quit = false;
	StateType nextState = mainMenu;
	
	//loops though game states
	while(!quit)
	{
		GameStatus* state;
		
		//load all the current states
		Menu menu(128, 64);
		Grapher Engine3D(128, 64);
		
		if(nextState == mainMenu)
		{
			state = &menu;
		}
		else if (nextState == grapher)
		{
			Vector min(-3,-3,-3);
			Vector max(3, 3, 3);
			unsigned char equationS[] = "X^2-Y^2";
			int yRes = 10;
			int xRes = 10;
			Engine3D.LoadEquation(equationS, min, max, yRes, xRes);
			state = &Engine3D;
		}
		else
		{
			
		}
		
		//repeats game state
		bool mContinue = true;
		while (mContinue == true)
		{
			mContinue = state->Input();

			state->Proccess();

			state->Display();
		}
		
	}
    return 1;
}




//****************************************************************************
//**************                                              ****************
//**************                 Notice!                      ****************
//**************                                              ****************
//**************  Please do not change the following source.  ****************
//**************                                              ****************
//****************************************************************************


#pragma section _BR_Size
unsigned long BR_Size;
#pragma section


#pragma section _TOP

//****************************************************************************
//  InitializeSystem
//
//  param   :   isAppli   : 1 = Application / 0 = eActivity
//              OptionNum : Option Number (only eActivity)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
extern "C" int InitializeSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#pragma section

