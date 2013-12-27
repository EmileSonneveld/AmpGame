//---------------------------
// Includes
//---------------------------
#include "MasterOfLists.h"
#include <fstream>

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())


//---------------------------//---------------------------//---------------------------
// Constructor & Destructor			HitStukSoort
//---------------------------//---------------------------//---------------------------

bool HitStukSoort::FileExists( String filename )
{
	ifstream openFile(filename.ToTChar());
	if( openFile ){
		return true;
	}
	return false;
	// openFile zit in de stack en word dus nu gedelete
}

HitStukSoort::HitStukSoort( String stukjesNaam )
{
	 //stukjesNaam ex: "SimpleLevel_"
	m_BmpSpritePtr= new Bitmap(String("recources/")+stukjesNaam+"Sprite.png");


	for( int i=0; i<100; ++i){ // laat alle hetregions.
		String fileName= String("recources/")+stukjesNaam + i +".svg";
		if( FileExists( fileName ) )
		{
			HitRegion *tmpHitPtr= new HitRegion();
			tmpHitPtr->CreateFromFile( fileName );
			m_HitregionsVect.push_back( tmpHitPtr );
			m_HitRadiusVect.push_back(i);
		}
	}
}

HitStukSoort::~HitStukSoort()
{
	//delete
}

void HitStukSoort::Paint(DOUBLE2 pos)
{
	GAME_ENGINE->DrawBitmap(m_BmpSpritePtr, pos);
}

int HitStukSoort::Raycast( DOUBLE2 pos, DOUBLE2 vector, HIT *hitStruct, double bouncerRadius, DOUBLE2 ghostPos )
{
	// beetje optimaliseren: (nog niet correct, maar goed genoeg)
	if( pos.y>ghostPos.y+m_BmpSpritePtr->GetHeight()|| pos.y<ghostPos.y ) return 0;
	if( pos.x>ghostPos.x+m_BmpSpritePtr->GetWidth() || pos.x<ghostPos.x ) return 0;
	int chosenNum=0; // er is sowiso een hitregion met deze radius

	for( unsigned int i= 0; i<m_HitRadiusVect.size(); ++i){
		if( m_HitRadiusVect.at(i)<=bouncerRadius ){
			chosenNum= i;
		}
	}

	m_HitregionsVect.at(chosenNum)->SetPos( ghostPos );
	return m_HitregionsVect.at(chosenNum)->Raycast(pos, vector, hitStruct, 1, -1);
}







//---------------------------//---------------------------//---------------------------
// Constructor & Destructor			HitRegionList
//---------------------------//---------------------------//---------------------------
HitRegionList::HitRegionList(): m_MatViewPtr(0)
{
}

HitRegionList::~HitRegionList()
{
	for( unsigned int plaats=0; plaats<m_InstancesPtrVect.size(); ++plaats ){
		if( CheckIfPlaatsExist(plaats) ){
			delete m_InstancesPtrVect.at(plaats);
			m_InstancesPtrVect.at(plaats)= 0;
		}
	}
	OutputStatus();
}

//---------------------------//---------------------------
// Own methods
//---------------------------//---------------------------

int HitRegionList::Raycast( DOUBLE2 pos, DOUBLE2 vector, HIT* hitStruct, double bouncerRadius )
{
	static const int arrSize= 10;
	HIT hitStructArr[arrSize]; // er kunnen max 10 effectieve regions gechekt worden
	int nrOfHits= 0;
	for( unsigned int i= 0; i<m_GhostPlaats.size(); ++i){
		if( 0 != m_InstancesPtrVect.at(m_GhostType.at(i))->Raycast(pos, vector, &hitStructArr[nrOfHits], bouncerRadius, m_GhostPlaats.at(i)) ){
			
			++nrOfHits;
			if( nrOfHits >= arrSize ) break;
		}
	}

	double minHitTime= 2; // veel te groot
	HIT choesenHit;
	for( int i= 0; i<nrOfHits; ++i){
		if( hitStructArr[i].time < minHitTime ){
			choesenHit= hitStructArr[i];
			minHitTime= choesenHit.time;
		}
	}

	*hitStruct = choesenHit;

	return nrOfHits;
}


/*
int HitRegionList::Raycast( DOUBLE2 pos, DOUBLE2 vector, HIT* hitStruct, int bouncerRadius ){

	HIT hitsVect[5];

	HIT hitStruct[1];

	int nrOfHits= 0;

	for (int i=0; i<(int)m_InstancesPtrVect.size(); ++i){ // UNDER HAVY CONSTRUCTION!!
		
		nrOfHits += ( 0 < m_InstancesPtrVect.at(i)->Raycast(pos, vector, &hitStruct, 1, -1) );

	}
	
	return nrOfHits;
}*/

int HitRegionList::LaadNieuwStukjeIn( String stukjesNaam){ //ex: "SimpleLevel_"

	return Add( new HitStukSoort( stukjesNaam ) );

}

int HitRegionList::PlaatsGhostStuk( DOUBLE2 pos, int hitStukSoortNum ){
	m_GhostPlaats.push_back(pos); 
	m_GhostType.push_back(hitStukSoortNum); 
	return 0;
}





void HitRegionList::Tick(double deltaTime)
{
	/*for (unsigned int plaats=0; plaats<m_InstancesPtrVect.size(); ++plaats){
		if( CheckIfPlaatsExist(plaats) )
			m_InstancesPtrVect.at(plaats)->Tick(deltaTime); 
	}*/
}

void HitRegionList::Paint()
{
	GAME_ENGINE->SetTransformMatrix( *m_MatViewPtr );
	for (unsigned int plaats=0; plaats<m_GhostPlaats.size(); ++plaats){
		
			m_InstancesPtrVect.at(m_GhostType.at(plaats))->Paint(m_GhostPlaats.at(plaats));
	}
}



// List manager ---------------------------------

int HitRegionList::Add( HitStukSoort * objectPtr )
{
	//objectPtr->SetMatViewPtr(m_MatViewPtr);
	//objectPtr->SetObjectList(this);

	for (int i=0; i<(int)m_InstancesPtrVect.size(); ++i){
		if ( m_InstancesPtrVect.at(i)== 0){
			m_InstancesPtrVect.at(i)= objectPtr;
			return i;
		}
	}
	m_InstancesPtrVect.push_back(objectPtr);
	return m_InstancesPtrVect.size()-1;
	return false;
}

bool HitRegionList::Delete( int plaats )
{
	if( CheckIfPlaatsExist(plaats) ){
		delete m_InstancesPtrVect.at(plaats);
		m_InstancesPtrVect.at(plaats)= 0;
		return true;
	}
	return false;
}

bool HitRegionList::Delete( HitStukSoort *objPtr )
{
	for (unsigned int plaats=0; plaats<m_InstancesPtrVect.size(); ++plaats){
		if( m_InstancesPtrVect.at(plaats)== objPtr )
			return Delete(plaats);
	}
	return false;
}

bool HitRegionList::CheckIfPlaatsExist( int plaats )
{
	if( plaats>=0 || plaats<(int)m_InstancesPtrVect.size()-1 ){
		if( m_InstancesPtrVect.at(plaats)!=0 ){
			return true;  // --- alles OK hier! ---
		}else{
			return false; //"Plaats is niet ingevuld
		}
	}else{
		GAME_ENGINE->MessageBox( String("plaats is niet in de list\n plaats= "+ plaats) );
	}

	return false;
}

void HitRegionList::OutputStatus(){
	String output=String("\nsize: ")+ m_InstancesPtrVect.size();//+ " capa "+ m_InstancesPtrVect.capacity()+ " Objs";
	OutputDebugString(output);
}