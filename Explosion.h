#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include "MasterOfLists.h"

//-----------------------------------------------------
// Explosion Class									
//-----------------------------------------------------
class Explosion: public ObjectBase
{
public:
	Explosion(DOUBLE2 pos, DOUBLE2 velocity);		// Constructor
	virtual ~Explosion();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	virtual void Tick(double deltaTime);
	virtual void Paint();

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	static Bitmap *m_BmpSpritePtr;
	//DOUBLE2 m_Pos;
	DOUBLE2 m_Velocity;
	double m_AnimationTick;
	double m_AnimationSpeed;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Explosion(const Explosion& yRef);									
	Explosion& operator=(const Explosion& yRef);	
};

 
