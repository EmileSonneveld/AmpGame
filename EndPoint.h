#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include "MasterOfLists.h"
#include "ListsController.h"

//-----------------------------------------------------
// EndPoint Class									
//-----------------------------------------------------
class EndPoint: public ObjectBase
{
public:
	EndPoint(DOUBLE2 pos);	// Constructor
	virtual ~EndPoint();	// Destructor

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

	MasterOfLists *m_MasterOfListsPtr;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	EndPoint(const EndPoint& yRef);									
	EndPoint& operator=(const EndPoint& yRef);	
};

 
