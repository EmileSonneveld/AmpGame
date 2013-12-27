#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include "MasterOfLists.h"

//-----------------------------------------------------
// ShootBal Class									
//-----------------------------------------------------
class ShootBal: public Dynamic
{
public:
	ShootBal(DOUBLE2 pos);	// Constructor
	virtual ~ShootBal();	// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	virtual void Tick(double deltaTime);
	virtual void Paint();

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	DOUBLE2 m_SpriteSize;
	static Bitmap *m_BmpSpritePtr;


	double m_ShootCounter;


	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	ShootBal(const ShootBal& yRef);									
	ShootBal& operator=(const ShootBal& yRef);	
};

 
