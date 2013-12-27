#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include "MasterOfLists.h"


//-----------------------------------------------------
// Magnet Class									
//-----------------------------------------------------
class Magnet: public ObjectBase
{
public:
	Magnet(DOUBLE2 pos, double power);	// Constructor
	Magnet(DOUBLE2 pos);	// Constructor
	virtual ~Magnet();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	virtual void Tick(double deltaTime);
	virtual void Paint();
	//void SetDynamicListPtr(DynamicList *dynamicListPtr){ m_DynamicListPtr= dynamicListPtr; }

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	static Bitmap *m_BmpSpritePtr;
	//DOUBLE2 m_Pos;
	//DynamicList *m_DynamicListPtr;

	double m_Rotate;
	double m_Power;
	double m_Straal;
	
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Magnet(const Magnet& yRef);									
	Magnet& operator=(const Magnet& yRef);	
};

 
