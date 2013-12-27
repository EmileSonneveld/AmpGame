#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include "MasterOfLists.h"


//-----------------------------------------------------
// Bal Class									
//-----------------------------------------------------
class Bal : public Dynamic// , public ObjectBase
{
public:
	Bal(DOUBLE2 pos, DOUBLE2 force);		// Constructor
	Bal(DOUBLE2 pos, int linksWanted);
	virtual ~Bal();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	virtual void Tick(double deltaTime);
	virtual void Paint();

	

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	//Dynamic *m_DinamicPtr;
	//DynamicList *m_DynamicList;
	//ObjectList *m_ObjectList;
	//DOUBLE2 m_Pos;

	bool m_LinksGelged;
	DOUBLE2 m_SpriteSize;
	static Bitmap *m_BmpSpritePtr;

	HitRegion *m_HitRegionPtr;

	void BitmapStuff();

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Bal(const Bal& yRef);									
	Bal& operator=(const Bal& yRef);	
};

 
