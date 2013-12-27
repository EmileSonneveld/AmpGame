#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include <vector>
#include <queue>


// Forward declarations! --------------------------------
// Iedere soort heeft zijn eigen list.
class Dynamic;
class DynamicList;

class ObjectBase;
class ObjectList;

class HitRegionStukje;
class HitRegionList;

class MasterOfLists;


//-----------------------------------------------------
// Dynamic Class									
//-----------------------------------------------------
class Dynamic
{
public:
	Dynamic(DOUBLE2 pos);// Constructor
	//Dynamic(DOUBLE2 pos, double mass, double K, double gravity);
	virtual ~Dynamic();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	
	virtual void Tick(double deltaTime)= 0;
	virtual void Paint()=0;

	void ApplyForce(DOUBLE2 force);
	//void Tick(double deltaTime);
	void DrawArrows();
	//void PassGlobalVars(HitRegion *backgroundHitPtr){m_BackgroundHitPtr= backgroundHitPtr;}
	void PaintDynamic();
	void Bounce(Dynamic *oponentPtr);
	DOUBLE2 GetPos(){return m_Pos;}
	
	void MoveTo( DOUBLE2 pos, double maxLen, double foce );

	//vector<Dynamic*> GetLinkList();
	void AddToLinkList(Dynamic* otherPtr);
	int GetCluster(){ return m_Cluster; }

	// Setters --------------------------------------
	void SetMatViewPtr(MATRIX3X2 *matViewPtr)		{m_MatViewPtr= matViewPtr;			}
	//void SetHitBgPtrPtr(HitRegion *hitRegionPtr)	{m_HitBgPtr= hitRegionPtr;			}
	void SetObjectList(ObjectList *objectListPtr)	{m_ObjectListPtr= objectListPtr;	}
	void SetHitRegionList(HitRegionList *hitRegionList){m_HitRegionListPtr= hitRegionList;	}
	void SetPos(DOUBLE2 pos){m_Pos= pos;}

	void RayBounceWrapper(double deltaTime);

	void DeleteMe();

protected:

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	// hij zet zichzelf in deze lijst (zie constructor)
	DynamicList *m_DynamicListPtr;
	MasterOfLists* m_MasterOfListsPtr;

	// Dynamic Vars
	DOUBLE2 m_Pos;
	DOUBLE2 m_Velocity, m_OldVelocity, m_Acceleration;
	DOUBLE2 *m_PosPtr; // idem aan m_Pos, geen zin om te vervangen
	double m_Mass, m_K, m_Gravity, m_Straal; //m_Bounce


	//_________________________________________________________________________
	// World Of Goo Stuff ( links leggen ) 
	static const int MAX_LINKS= 4;
	int m_MaxLinks;
	double m_TargetLen;
	vector<Dynamic*> m_LinkList;
	vector<double> m_LinkLen;
	int m_Cluster;
	void SetCluster(int cluster);
	// Functions
	void TickSetDistance(double deltaTime);
	int CountDynamicsInRadius( double straal );
	int MakeLinks(double straal);
	void RemoveLink(int plaats);


	//_________________________________________________________________________
	// datamember who will be set by the DynamicList
	MATRIX3X2 *m_MatViewPtr;
	//HitRegion *m_HitBgPtr;
	ObjectList *m_ObjectListPtr;
	HitRegionList *m_HitRegionListPtr;

	

	// Methods ----------------------------------------
	void Move(double deltaTime);
	void RayBounce(double deltaTime, DOUBLE2 *pos, DOUBLE2 *velocity);
	void friction(double deler= 100);

private: // vooral bucht.
	
	

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Dynamic(const Dynamic& yRef);									
	Dynamic& operator=(const Dynamic& yRef);	
};




//-----------------------------------------------------
// DynamicList Class									
//-----------------------------------------------------
class DynamicList
{
public:
	DynamicList(DOUBLE2 maxPos);// Constructor
	virtual ~DynamicList();		// Destructor

	//-------------------------------------------------
	// Own methods									
	//-------------------------------------------------
	int Add( Dynamic * objectPtr );
	//int Add( Bal * objectPtr );
	//int Add( Player * objectPtr );
	bool Delete( int plaats );
	bool Delete( Dynamic *objPtr );

	void Tick(double deltaTime);
	void Paint();
	//DOUBLE2 GetPos( int plaats );
	Dynamic *GetPointer( int plaats ){return m_ObjectPtrVect.at(plaats);}
	unsigned int GetVectorSize(){ return m_ObjectPtrVect.size(); }

	int GetMaxCluster(){ return m_MaxCluster;}
	void VerhoogMaxCluster(){ ++m_MaxCluster; }

	// Setters --------------------------------------
	void SetMatViewPtr(MATRIX3X2 *matViewPtr)			{m_MatViewPtr= matViewPtr;			}
	void SetHitBgPtrPtr(HitRegion *hitRegionPtr)		{m_HitBgPtr= hitRegionPtr;			}
	void SetObjectList(ObjectList *objectListPtr)		{m_ObjectListPtr= objectListPtr;	}
	void SetHitRegionList(HitRegionList *hitRegionList)	{m_HitRegionListPtr= hitRegionList;	}

	vector<Dynamic*>	GetVector()	{ return m_ObjectPtrVect;	}
	
private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	//static const int ARR_MAX=100;
	//ObjectBase * m_ObjectPtr[ARR_MAX];
	vector<Dynamic*> m_ObjectPtrVect;

	queue<int> m_DelteBuffer;
	// voor de inzittende objecten:
	DOUBLE2 m_LevelMaxPos;

	MATRIX3X2 *m_MatViewPtr;
	HitRegion *m_HitBgPtr;
	ObjectList *m_ObjectListPtr;
	HitRegionList *m_HitRegionListPtr;

	bool m_Bounce;

	int m_MaxCluster;

	// Funcs ------------------------------------------
	bool CheckIfPlaatsExist( int plaats );
	void OutputStatus();

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	DynamicList(const DynamicList& yRef);									
	DynamicList& operator=(const DynamicList& yRef);	
};




//-----------------------------------------------------
// ObjectBase Class
//-----------------------------------------------------
class ObjectBase
{
public:
	ObjectBase(DOUBLE2 pos);//, Bitmap * BmpSpritePtr
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
	void SetDynamicList(DynamicList * dynamicList)	{m_DynamicListPtr= dynamicList;		}
	//void SetHitBgPtrPtr(HitRegion *hitRegionPtr)	{m_HitBgPtr= hitRegionPtr;			}
	//void SetObjectList(ObjectList * objectListPtr){ m_ObjectListPtr= objectListPtr;	}

	//HitRegion *GetHitRegion(){ return m_HitRegionPtr; }

protected:
	//static Bitmap *m_BmpSpritePtr;
	DOUBLE2 m_Pos; // Ambigu met 
	
	DOUBLE2 m_SpriteSize;
	MATRIX3X2 *m_MatViewPtr;
	ObjectList *m_ObjectListPtr;
	DynamicList *m_DynamicListPtr;

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
	void SetDynamicList( DynamicList *dynamicListPtr ){m_DynamicListPtr= dynamicListPtr;}


private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	vector<ObjectBase*> m_ObjectPtrVect;

	// voor de inzittende objecten:
	//DOUBLE2 m_LevelMaxPos;
	MATRIX3X2 *m_MatViewPtr;
	DynamicList * m_DynamicListPtr;

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








// HITREGIONS ------------------------------------------------------------------------

//-----------------------------------------------------
// HitStukSoort Class
//-----------------------------------------------------

class HitStukSoort // bv een rots in de vorm van een banaan.
{

public:
	HitStukSoort( String stukjesNaam );
	virtual ~HitStukSoort();

	void Paint(DOUBLE2 pos);

	int Raycast( DOUBLE2 pos, DOUBLE2 vector, HIT* hitStructt, double bouncerRadius, DOUBLE2 ghostPos );
	
private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	vector<HitRegion*> m_HitregionsVect;
	vector<int> m_HitRadiusVect;

	Bitmap *m_BmpSpritePtr;

	bool FileExists( String filename );

	// Disabling stuff:
	HitStukSoort(const HitStukSoort& yRef);						
	HitStukSoort& operator=(const HitStukSoort& yRef);	
};


//-----------------------------------------------------
// HitRegionList Class									
//-----------------------------------------------------
class HitRegionList
{
public:
	HitRegionList();				// Constructor
	virtual ~HitRegionList();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	int LaadNieuwStukjeIn( String stukjesNaam );
	
	int PlaatsGhostStuk( DOUBLE2 pos, int hitStukSoortNum );

	void Tick(double deltaTime);
	void Paint();

	//DOUBLE2 GetPos( int plaats );
	//MATRIX3X2 GetMatViewPtr(){return *m_MatViewPtr;}
	
	int Raycast( DOUBLE2 pos, DOUBLE2 vector, HIT* hitStructt, double bouncerRadius );

	// SETTERS -------------------------------------------------------------------------
	void SetMatViewPtr(MATRIX3X2 *matViewPtr)		{m_MatViewPtr= matViewPtr;			}
	//void SetObjectList(ObjectList *objectListPtr)	{m_ObjectListPtr= objectListPtr;	}
	//void SetLevelMax(DOUBLE *levelMax)			{m_LevelMaxPos= levelMax;			}


private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	// de verschillende soorten inladen
	vector<HitStukSoort*> m_InstancesPtrVect;

	// verschillende copies
	// een Ghost is een soort copie can de HitStukSoort op een bepaalde plaats
	vector<DOUBLE2> m_GhostPlaats; 
	vector<int> m_GhostType; 

	// voor de inzittende objecten:
	//DOUBLE2 m_LevelMaxPos;
	MATRIX3X2 *m_MatViewPtr;

	// Funcs ------------------------------------------
	int Add( HitStukSoort * objectPtr );
	bool Delete( int plaats );
	bool Delete( HitStukSoort *objPtr );

	bool CheckIfPlaatsExist( int plaats );
	void OutputStatus();

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	HitRegionList(const HitRegionList& yRef);									
	HitRegionList& operator=(const HitRegionList& yRef);	
};