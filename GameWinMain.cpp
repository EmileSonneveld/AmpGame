//-----------------------------------------------------------------
// Game Engine WinMain Function
// C++ Source - GameWinMain.cpp - version 2012 v2_10
// Copyright Kevin Hoefman, Bart Uyttenhove, Peter Verswyvelen
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "GameWinMain.h"
#include "GameEngine.h"

#include "AmpGame.h"	
//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

#define GAME_ENGINE (GameEngine::GetSingleton())


//-----------------------------------------------------------------
// Windows Functions
//-----------------------------------------------------------------
int _tmain()
{
       WinMain(GetModuleHandle(0), 0, 0, SW_SHOW);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	if (GAME_ENGINE == NULL) return FALSE; // create the game engine and exit if it fails

	GAME_ENGINE->SetGame(new AmpGame());	// any class that implements AbstractGame
	
	return GAME_ENGINE->Run(hInstance, iCmdShow); // run the game engine and return the result
}
