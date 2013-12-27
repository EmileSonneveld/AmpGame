//---------------------------
// Includes
//---------------------------
#include "ListsController.h"

#include "Kannon.h"


//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

DynamicList *Global_DynamicListPtr= 0; // Test voor multi-treatherd game

//-----------------------------------------------------------------
// Static Variable Initialization
//-----------------------------------------------------------------
MATRIX3X2	  * MasterOfLists::m_MatViewPtr		 = 0;
ObjectList    * MasterOfLists::m_ObjectListPtr   = 0;
DynamicList	  * MasterOfLists::m_DynamicListPtr  = 0;
HitRegionList * MasterOfLists::m_HitRegionListPtr= 0;

MasterOfLists * MasterOfLists::m_MasterOfListsPtr= 0;


//---------------------------
// Constructor & Destructor
//---------------------------
MasterOfLists::MasterOfLists(MATRIX3X2 *matViewPtr, DOUBLE2 levelMaxPos): 
	m_LevelMaxPos(levelMaxPos)
{
	m_MatViewPtr= matViewPtr;
	m_MasterOfListsPtr= this;

	// ObjectList -----------------------------------------------
	m_ObjectListPtr= new ObjectList();
	m_ObjectListPtr->SetMatViewPtr(	m_MatViewPtr			);
	//m_ObjectListPtr->SetObjectList(	m_ObjectListPtr		);
	//m_ObjectListPtr->SetHitRegionList(	m_HitRegionListPtr	);
	m_ObjectListPtr->SetDynamicList( m_DynamicListPtr );


	m_HitRegionListPtr= new HitRegionList();
	m_HitRegionListPtr->SetMatViewPtr(	m_MatViewPtr			);
	


	m_DynamicListPtr= new DynamicList(	m_LevelMaxPos		);
	m_DynamicListPtr->SetMatViewPtr(	m_MatViewPtr			);
	m_DynamicListPtr->SetObjectList(	m_ObjectListPtr		);
	m_DynamicListPtr->SetHitRegionList(	m_HitRegionListPtr	);

	Global_DynamicListPtr= m_DynamicListPtr;

	//m_ObjectListPtr->SetHitRegionList(	m_HitRegionListPtr	);
	m_ObjectListPtr->SetDynamicList( m_DynamicListPtr );

	PlaceInstances();

}

MasterOfLists::~MasterOfLists()
{
	delete m_DynamicListPtr  ; // <- deze kan nog objecten aanmaken
	delete m_ObjectListPtr   ;
	delete m_HitRegionListPtr;
}


//---------------------------
// Own methods
//---------------------------




void MasterOfLists::Tick(double deltaTime)
{
	m_ObjectListPtr   ->Tick( deltaTime );
	m_DynamicListPtr  ->Tick( deltaTime );
	m_HitRegionListPtr->Tick( deltaTime );

	//Global_DynamicListPtr->Tick( deltaTime );


	if( rand()%80 <=1 ){
		new Bal(DOUBLE2(rand()%(int)m_LevelMaxPos.x,-5000), 0);
	}


	
}

void MasterOfLists::Paint()
{
	GAME_ENGINE->SetTransformMatrix( *m_MatViewPtr );

	m_HitRegionListPtr->Paint();
	m_ObjectListPtr   ->Paint();
	m_DynamicListPtr  ->Paint();
}



void MasterOfLists::PlaceInstances()
{
	int soort = m_HitRegionListPtr->LaadNieuwStukjeIn("Stukje_1_"); // SimpleLevel_
	m_HitRegionListPtr->LaadNieuwStukjeIn("Stukje_2_");

	m_HitRegionListPtr->PlaatsGhostStuk( DOUBLE2(50,10), 0 ); // Start stukje

	int max= 0;
	for( int i= 0; i<50000; ++i){
		max= max( rand(), max);
	}
	OutputDebugString( String("max") + max );

	//				    (       Volume arena    )    /   ( volume stukje )
	double ratio= ( m_LevelMaxPos.x * m_LevelMaxPos.y ) / (1700 * 1000 ) /2;
	DOUBLE2 tmpPos;

	for( int i=0; i<40; ++i ){ // i<ratio rand() gaat tot 32000
		tmpPos.x= rand()%( (int)(m_LevelMaxPos.x ) ); // 50000 
		tmpPos.y= rand()%( (int)(m_LevelMaxPos.y ) ); // 160000
		m_HitRegionListPtr->PlaatsGhostStuk( tmpPos, rand()%2); // rand()%2
	}
	
	m_PlayerPtr= new Player(DOUBLE2(300, 200)); // he adds itself to the list

	for( int i=0; i<5; ++i ){
		Kannon *KannonPtr= new Kannon( DOUBLE2(rand()%(int)m_LevelMaxPos.x, rand()%(int)m_LevelMaxPos.y) );
		KannonPtr->SetPlayerPtr(m_PlayerPtr);

	}



	const int shifter= 199;
	int yy= -300;
	for( int xx=0; xx<m_LevelMaxPos.x; xx+= shifter){
		new Bal(DOUBLE2(xx,yy), DOUBLE2());
	}
	/*yy-= shifter;
	for( int xx=shifter/2; xx<m_LevelMaxPos.x; xx+= shifter){
		new Bal(DOUBLE2(xx,yy), DOUBLE2());
	}*/

	

	/*double distance= 190;
	for( double radians= 0; radians<2*M_PI; radians+= 2*M_PI/8 ){
		Bal *tmpPtr= new Bal(playerPos+distance*DOUBLE2(cos(radians), -sin(radians)) , m_DynamicListPtr);
	}*/

	Magnet *tmpMagnetPtr= new Magnet(m_LevelMaxPos/2, -9 );
	//tmpMagnetPtr->SetDynamicListPtr(m_DynamicListPtr);

	tmpMagnetPtr= new Magnet(m_LevelMaxPos*0.9, 5 );
	//tmpMagnetPtr->SetDynamicListPtr(m_DynamicListPtr);


}