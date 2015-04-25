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
#include "EditTextState.h"
#include "point.h"
#include "Renderer.h"

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
	//StateType nextState = grapher;
	//StateType currentState = mainMenu;
	
	Renderer gRenderer(127, 63);
	
	//load all the current states
	GameStatus* state;
	
	Menu menu(&gRenderer);
	
	Grapher Engine3D(&gRenderer);
	
	//EditTextState EditText(128, 64);
	
	/*
	Function eq;
			
	uString equationS = "X^2-Y^2";

	eq.SetEquation(equationS);

	eq.SetDrawable(true);

	eq.SetGridRes(10, 10);

	Vector min(-3,-3,-3);
	Vector max(3, 3, 3);

	eq.UpdateGrid(min, max);

	Engine3D.LoadFunction(&eq);
	*/	
	
	state = &menu;
		
	//repeats game state
	bool mContinue = true;
	while (mContinue == true)
	{
		state->Proccess();
		state->Display();
		mContinue = state->Input();


	}
		
	//nextState = state->nextState;
	//currentState = state->state;

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

