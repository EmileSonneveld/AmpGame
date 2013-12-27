//---------------------------
// Includes
//---------------------------
#include "MasterOfLists.h"
#include "ListsController.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//Bitmap * ObjectBase::m_BmpSpritePtr= 0;

//---------------------------
// Constructor & Destructor		ObjectBase
//---------------------------
ObjectBase::ObjectBase(DOUBLE2 pos):
	m_SpriteSize(), m_Pos(pos),	m_MatViewPtr(0)
{
	m_ObjectListPtr= MasterOfLists::GetObjectList();
	m_ObjectListPtr->Add(this);
	//m_ObjectListPtr->Add(this); // add zichzelf in de list.
}

ObjectBase::~ObjectBase(){
	//m_ObjectListPtr->Delete(this);
	//if( m_HitRegionPtr!=0 ) delete m_HitRegionPtr;}
}

//---------------------------
// Own methods
//---------------------------

/*void ObjectBase::Paint() // deze functie kan de gepersonaliseerde m_BmpSpritePtr niet gebruiken!
{ 
	GAME_ENGINE->SetTransformMatrix( *m_MatViewPtr );
	int frame= 0;
	RECT2 clip;
	clip.left   = frame * m_SpriteSize.x;
	clip.top    = 0;
	clip.right  = clip.left +m_SpriteSize.x;
	clip.bottom = clip.top  +m_SpriteSize.y;
	GAME_ENGINE->DrawBitmap(m_BmpSpritePtr, m_Pos, clip);
}//*/


//---------------------------
// Constructor & Destructor		ObjectList
//---------------------------
ObjectList::ObjectList(): m_MatViewPtr(0)
{}

ObjectList::~ObjectList()
{
	for( unsigned int plaats=0; plaats<m_ObjectPtrVect.size(); ++plaats ){
		if( CheckIfPlaatsExist(plaats) ){
			delete m_ObjectPtrVect.at(plaats);
			m_ObjectPtrVect.at(plaats)= 0;
		}
	}
	OutputStatus();
}

//---------------------------
// Own methods
//---------------------------

/*int ObjectList::Add( Bal* objectPtr ){

	ObjectBase * objectBasePtr= objectPtr;
	Add( objectBasePtr );
}
int ObjectList::Add( Player* objectPtr ){

	ObjectBase * objectBasePtr= objectPtr;
	Add( objectBasePtr );
}*/

int ObjectList::Add( ObjectBase * objectPtr )
{
	objectPtr->SetMatViewPtr(m_MatViewPtr);
	//objectPtr->SetObjectList(this);
	objectPtr->SetDynamicList( m_DynamicListPtr );
	for (int i=0; i<(int)m_ObjectPtrVect.size(); ++i){
		if ( m_ObjectPtrVect.at(i)== 0){
			m_ObjectPtrVect.at(i)= objectPtr;
			return i;
		}
	}
	m_ObjectPtrVect.push_back(objectPtr);
	return m_ObjectPtrVect.size()-1;
	//GAME_ENGINE->MessageBox("List is Full, can't add another object!");
	return false;
}

bool ObjectList::Delete( int plaats )
{
	if( CheckIfPlaatsExist(plaats) ){
		delete m_ObjectPtrVect.at(plaats);
		m_ObjectPtrVect.at(plaats)= 0;
		return true;
	}
	return false;
}

bool ObjectList::Delete( ObjectBase *objPtr )
{
	for (unsigned int plaats=0; plaats<m_ObjectPtrVect.size(); ++plaats){
		if( m_ObjectPtrVect.at(plaats)== objPtr )
			return Delete(plaats);
	}
	return false;
}

void ObjectList::Tick(double deltaTime)
{
	for (unsigned int plaats=0; plaats<m_ObjectPtrVect.size(); ++plaats){
		if( CheckIfPlaatsExist(plaats) )
			m_ObjectPtrVect.at(plaats)->Tick(deltaTime); 
	}
}

void ObjectList::Paint()
{
	for (unsigned int plaats=0; plaats<m_ObjectPtrVect.size(); ++plaats){
		if( CheckIfPlaatsExist(plaats) )
			m_ObjectPtrVect[plaats]->Paint();
	}
}

bool ObjectList::CheckIfPlaatsExist( int plaats )
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

void ObjectList::OutputStatus(){
	String output=String("\nsize: ")+ m_ObjectPtrVect.size();//+ " capa "+ m_ObjectPtrVect.capacity()+ " Objs";
	OutputDebugString(output);
	/*if( m_ObjectCount>ARR_MAX ){// geen nut met vector
	OutputDebugString("\nFOUT!");
	GAME_ENGINE->MessageBox(output);
	}*/
}