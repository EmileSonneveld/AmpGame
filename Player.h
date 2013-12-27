#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include "MasterOfLists.h"

//-----------------------------------------------------
// Player Class										   
//-----------------------------------------------------
class Player:  public Dynamic
{
public:
	Player(DOUBLE2 pos);	// Constructor
	virtual ~Player();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	void Tick(double deltaTime);
	void Paint();
	void PassGlobalVars(HitRegion *backgroundHitPtr, DOUBLE2 *mousePos);
	

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	
	//MATRIX3X2 *m_MatViewPtr;
	//HitRegion *m_HitRegionPtr;

	DOUBLE2 m_SpriteSize;
	static Bitmap *m_BmpSpritePtr;

	DOUBLE2 *m_MousePos;
	
	//Dynamic *m_DynamicPtr;
	//HitRegion *m_BackgroundHitPtr;
	HitRegion *m_HitRegionPtr;

	double m_Health;

	//GasPower ---------------------------
	double m_GasPower;
	double m_GasPowerMax;
	double m_GasPowerConsumption;

	//DynamicList *m_DynamicList;
	//ObjectList *m_ObjectList;

	//void RayTest(double deltaTime, DOUBLE2 *pos, DOUBLE2 *velocity);
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Player(const Player& yRef);									
	Player& operator=(const Player& yRef);	
};

 
