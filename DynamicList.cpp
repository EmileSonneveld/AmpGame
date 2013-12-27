// Includes -------------------------------------------------------
#include "MasterOfLists.h"


// Defines -------------------------------------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())


// Constructor & Destructor ---------------------------------------
DynamicList::DynamicList(DOUBLE2 maxPos): m_LevelMaxPos(maxPos), m_Bounce(true), m_MaxCluster(0)
{
}

DynamicList::~DynamicList()
{
	for (int i=0; i<(int)m_ObjectPtrVect.size(); ++i){  Delete(i); }
	OutputStatus();
}


// Methodes ----------------------------------------------------------
int DynamicList::Add( Dynamic * objectPtr )
{
	objectPtr->SetMatViewPtr(		m_MatViewPtr		);
	//objectPtr->SetHitBgPtrPtr(		m_HitBgPtr			);
	objectPtr->SetObjectList(		m_ObjectListPtr		);
	objectPtr->SetHitRegionList(	m_HitRegionListPtr	);


	for (int i=0; i<(int)m_ObjectPtrVect.size(); ++i){
		if ( m_ObjectPtrVect.at(i)== 0){
			m_ObjectPtrVect.at(i)= objectPtr;
			return i;
		}
	}
	m_ObjectPtrVect.push_back(objectPtr);
	return m_ObjectPtrVect.size()-1;
	OutputStatus();
	return false;
}

bool DynamicList::Delete( int plaats )
{
	if( CheckIfPlaatsExist(plaats) ){
		
		m_DelteBuffer.push(plaats); // zal worden gedeleet op een vijlig moment
		//m_ObjectPtrVect.erase(m_ObjectPtrVect.begin()+plaats); // safer, but slower
		//m_ObjectPtrVect.at(plaats)= 0;
		return true;
	}
	return false;
}

bool DynamicList::Delete( Dynamic *objPtr )
{
	for (unsigned int plaats=0; plaats<m_ObjectPtrVect.size(); ++plaats){
		if( CheckIfPlaatsExist(plaats) ){
			if( m_ObjectPtrVect.at(plaats) == objPtr )
				return Delete(plaats);
		}
	}
	return false;
}

void DynamicList::Tick(double deltaTime)
{
	for (int plaats=0; plaats<(int)m_ObjectPtrVect.size(); ++plaats){ // Tick
		if( CheckIfPlaatsExist(plaats) ){
			
			m_ObjectPtrVect.at(plaats)->Tick(deltaTime);

		}
	}
	for( unsigned int i= 0; i<m_DelteBuffer.size(); ++i){
		delete m_ObjectPtrVect.at( m_DelteBuffer.front() );
		m_ObjectPtrVect.erase( m_ObjectPtrVect.begin()+m_DelteBuffer.front() );
		m_DelteBuffer.pop();
	}

	if( GAME_ENGINE->IsKeyDown('B') ) m_Bounce= !m_Bounce;

	if( m_Bounce ){
		for (unsigned int plaats=0;          plaats<m_ObjectPtrVect.size(); ++plaats){  if( CheckIfPlaatsExist(plaats) ){
		for (unsigned int plaatsB=plaats+1; plaatsB<m_ObjectPtrVect.size(); ++plaatsB){ if( CheckIfPlaatsExist(plaatsB)){
			if( plaats!= plaatsB ){

				m_ObjectPtrVect.at(plaats)->Bounce( m_ObjectPtrVect.at(plaatsB) ); // hier word er gebotst!
			}
		}}
		}}
	}
}

void DynamicList::Paint()
{
	for (int plaats=0; plaats<(int)m_ObjectPtrVect.size(); ++plaats){
		if( CheckIfPlaatsExist(plaats) )
			m_ObjectPtrVect[plaats]->Paint();
	}
}

bool DynamicList::CheckIfPlaatsExist( int plaats )
{
	if( plaats>=0 || plaats<(int)m_ObjectPtrVect.size()-1 ){
		if( m_ObjectPtrVect.at(plaats)!=0 ){
			return true;  // --- alles OK hier! ---
		}else{
			return false; //"Plaats is niet ingevuld
		}
	}else{
		GAME_ENGINE->MessageBox( String("plaats is niet in de list\n plaats= "+ plaats) );
	}

	return false;
}

void DynamicList::OutputStatus(){
	String output=String("\nsize: ")+ m_ObjectPtrVect.size();//+ " capa "+ m_ObjectPtrVect.capacity()+ " Objs";
	OutputDebugString(output);
	/*if( m_ObjectCount>ARR_MAX ){// geen nut met vector
	OutputDebugString("\nFOUT!");
	GAME_ENGINE->MessageBox(output);
	}*/
}