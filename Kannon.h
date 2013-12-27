#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include "MasterOfLists.h"
class Player;


//-----------------------------------------------------
// Kannon Class									
//-----------------------------------------------------
class Kannon: public ObjectBase
{
public:
	Kannon(DOUBLE2 pos);	// Constructor
	virtual ~Kannon();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	virtual void Tick(double deltaTime);
	virtual void Paint();

	void SetPlayerPtr(Player * playerPtr){ m_PlayerPtr= playerPtr;}
	
private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	static Bitmap *m_BmpSpritePtr;
	//DOUBLE2 m_Pos;
	//DynamicList *m_DynamicListPtr;

	Player *m_PlayerPtr;

	double m_ShootCounter;

	double m_MaxTargetDistance;
	DOUBLE2 m_SpriteSize;
	double m_Direction;
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Kannon(const Kannon& yRef);									
	Kannon& operator=(const Kannon& yRef);	
};

 
