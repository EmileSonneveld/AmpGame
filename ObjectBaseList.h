#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
//#include "Dynamic.h"
#include <vector>
//#include "Bal.h"
//#include "Player.h"

//-----------------------------------------------------------------
//  Forward Declarations:
//-----------------------------------------------------------------
class ObjectBase;
class ObjectList;


//-----------------------------------------------------
// ObjectBase Class
//-----------------------------------------------------
class ObjectBase
{
public:
	ObjectBase(ObjectList *objectListPtr);//, Bitmap * BmpSpritePtr
	virtual ~ObjectBase();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------

	virtual void Tick(double deltaTime) =0;
	virtual void Paint() =0;

	//virtual DOUBLE2 GetPos(){ return m_Pos; }

	// SETTERS -------------------------------------------------------------------------
	void SetMatViewPtr(MATRIX3X2 *matViewPtr)		{m_MatViewPtr= matViewPtr;			}
	void SetObjectList(ObjectList *objectListPtr)	{m_ObjectListPtr= objectListPtr;	}
	void SetDynamicList(DynamicList * dynamicList)	{m_DynamicList= dynamicList;		}
	//void SetHitBgPtrPtr(HitRegion *hitRegionPtr)	{m_HitBgPtr= hitRegionPtr;			}
	//void SetObjectList(ObjectList * objectListPtr){ m_ObjectListPtr= objectListPtr;	}

	//HitRegion *GetHitRegion(){ return m_HitRegionPtr; }

protected:
	//static Bitmap *m_BmpSpritePtr;
	DOUBLE2 m_Pos; // Ambigu met 
	
	DOUBLE2 m_SpriteSize;
	MATRIX3X2 *m_MatViewPtr;
	ObjectList *m_ObjectListPtr;
	DynamicList *m_DynamicList;

	//HitRegion *m_HitRegionPtr;
	//int m_Team; // 0: onpartijdig, 1: speler, 2:vijand

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	ObjectBase(const ObjectBase& yRef);									
	ObjectBase& operator=(const ObjectBase& yRef);	
};

 



//-----------------------------------------------------
// ObjectList Class									
//-----------------------------------------------------
class ObjectList
{
public:
	ObjectList();				// Constructor
	virtual ~ObjectList();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	int Add( ObjectBase * objectPtr );
	//int Add( Bal * objectPtr );
	//int Add( Player * objectPtr );
	bool Delete( int plaats );
	bool Delete( ObjectBase *objPtr );

	void Tick(double deltaTime);
	void Paint();
	//DOUBLE2 GetPos( int plaats );
	ObjectBase *GetPointer( int plaats ){return m_ObjectPtrVect.at(plaats);}
	//MATRIX3X2 GetMatViewPtr(){return *m_MatViewPtr;}
	

	// SETTERS -------------------------------------------------------------------------
	void SetMatViewPtr(MATRIX3X2 *matViewPtr)		{m_MatViewPtr= matViewPtr;			}
	//void SetObjectList(ObjectList *objectListPtr)	{m_ObjectListPtr= objectListPtr;	}
	//void SetLevelMax(DOUBLE *levelMax)			{m_LevelMaxPos= levelMax;			}


private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	vector<ObjectBase*> m_ObjectPtrVect;

	// voor de inzittende objecten:
	//DOUBLE2 m_LevelMaxPos;
	MATRIX3X2 *m_MatViewPtr;

	// Funcs ------------------------------------------
	bool CheckIfPlaatsExist( int plaats );
	void OutputStatus();

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	ObjectList(const ObjectList& yRef);									
	ObjectList& operator=(const ObjectList& yRef);	
};