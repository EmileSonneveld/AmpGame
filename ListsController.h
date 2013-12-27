#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include "MasterOfLists.h"

#include "Bal.h"
#include "Player.h"
#include "Magnet.h"
#include "Explosion.h"

//-----------------------------------------------------
// MasterOfLists Class			is Singleton, maar nit zo evil
//-----------------------------------------------------
class MasterOfLists
{
public:
	MasterOfLists(MATRIX3X2 *matViewPtr, DOUBLE2 levelMaxPos);			// Constructor
	virtual ~MasterOfLists();	// Destructor

	void Tick(double deltaTime);
	void Paint();

	Bal       *NewBal       ( DOUBLE2 pos ) { return new Bal   (pos, DOUBLE2() ); }
	Player    *NewPlayer    ( DOUBLE2 pos ) { 
		m_PlayerPtr= new Player   (pos);
		return m_PlayerPtr; }
	Magnet    *NewMagnet    ( DOUBLE2 pos ) { return new Magnet   (pos); }
	Explosion *NewExplosion ( DOUBLE2 pos ) { return new Explosion(pos, DOUBLE2()); }

	/*void *Add( Bal       )
	void *Add( Player    )
	void *Add( Magnet    )
	void *Add( Explosion )*/


	// __ GETTERs ___________________________________________________________
	static MATRIX3X2	  GetMatView      (){ return *m_MatViewPtr	   ; }
	static ObjectList    *GetObjectList   (){ return m_ObjectListPtr   ; }
	static DynamicList   *GetDynamicList  (){ return m_DynamicListPtr  ; }
	static HitRegionList *GetHitRegionList(){ return m_HitRegionListPtr; }
			Player		 *GetPlayerPtr    (){ return m_PlayerPtr	   ; }
			DOUBLE2 GetPlayerPos(){ return m_PlayerPtr->GetPos(); }
			DOUBLE2 GetMousePos(){ return *m_MousePosPtr; }
			DOUBLE2 GetLevelMaxPos(){ return m_LevelMaxPos; }

	static MasterOfLists* GetSignleton(){
				//if( m_MasterOfListsPtr==0){ DebugBreak();} //<- vreemde shit als ge hier geraakt
					//m_MasterOfListsPtr= new MasterOfLists();
				return m_MasterOfListsPtr;
			}
	
	// __ SETTERs ___________________________________________________________
	void SetMatViewPtr(MATRIX3X2 *matViewPtr)		{m_MatViewPtr= matViewPtr;	}
	void SetMousePosPtr( DOUBLE2 *mousePosPtr) {m_MousePosPtr= mousePosPtr; }

private: 

	DOUBLE2 m_LevelMaxPos;
	
	Player *m_PlayerPtr;
	DOUBLE2 *m_MousePosPtr;

	MATRIX3X2 m_MatView;
	static MATRIX3X2 *m_MatViewPtr;

	static ObjectList    * m_ObjectListPtr   ;
	static DynamicList	 * m_DynamicListPtr  ;
	static HitRegionList * m_HitRegionListPtr;

	static MasterOfLists *m_MasterOfListsPtr;


	void PlaceInstances();

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	MasterOfLists(const MasterOfLists& yRef);									
	MasterOfLists& operator=(const MasterOfLists& yRef);	
};
