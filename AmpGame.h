//-----------------------------------------------------------------
// Game File
// C++ Header - AmpGame.h - version 2012 v2_10
// Copyright Kevin Hoefman - kevin.hoefman@howest.be
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "GameEngine.h"
#include "AbstractGame.h"
#include "Player.h"
#include "ListsController.h"


//-----------------------------------------------------------------
// AmpGame Class
//-----------------------------------------------------------------
class AmpGame : public AbstractGame, public Callable
{
public:				
	//---------------------------
	// Constructor(s)
	//---------------------------
	AmpGame();

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~AmpGame();

	//---------------------------
	// General Methods
	//---------------------------

	void GameInitialize(HINSTANCE hInstance);
	void GameStart();				
	void GameEnd();
	//void GameActivate();
	//void GameDeactivate();
	void MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam);
	void MouseMove(int x, int y, WPARAM wParam);
	//void CheckKeyboard();
	//void KeyPressed(TCHAR cKey);
	void GameTick(double deltaTime);
	void GamePaint(RECT rect);

	//void CallAction(Caller* callerPtr);

	// -------------------------
	// Member functions
	// -------------------------

private:
	// -------------------------
	// Member functions
	// -------------------------
	void DoCameraMovement(double deltaTime, DOUBLE2 playerPos);
	bool FileExists( String filename );

	// -------------------------
	// Datamembers
	// -------------------------
	vector<HitRegion*> m_HitVector;
	vector<int> m_Hitradius;
	Bitmap *m_BmpBGPtr;

	double m_DeltaTime;

	Player *m_PlayerPtr;
	HitRegion *m_BackgroundHitPtr;
	DOUBLE2 m_MousePos, m_LevelMaxPos, m_PosCamera;
	bool m_MouseDown;
	double m_ViewScale;
	MATRIX3X2 m_MatView;

	MasterOfLists * m_MasterOfListsPtr;


	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	AmpGame(const AmpGame& tRef);
	AmpGame& operator=(const AmpGame& tRef);
};
