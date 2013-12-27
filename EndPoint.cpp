//---------------------------
// Includes
//---------------------------
#include "EndPoint.h"
#include "ListsController.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap *EndPoint::m_BmpSpritePtr= 0;

EndPoint::EndPoint(DOUBLE2 pos): ObjectBase(pos)
{
	if( m_BmpSpritePtr==0 ){
		m_BmpSpritePtr= new Bitmap("./recources/EndPoint.png");
	}

	m_SpriteSize.x= m_BmpSpritePtr->GetWidth();
	m_SpriteSize.y= m_BmpSpritePtr->GetHeight();

	m_MasterOfListsPtr=  MasterOfLists::GetSignleton()->GetSignleton();
	if( m_MasterOfListsPtr == 0 ) DebugBreak();
}

EndPoint::~EndPoint()
{
	// nothing to destroy
}

//---------------------------
// Own methods
//---------------------------

void EndPoint::Tick(double deltaTime)
{
	DOUBLE2 playerPos= MasterOfLists::GetSignleton()->GetPlayerPos();
	DOUBLE2 deltaVect= playerPos - m_Pos;
	if( playerPos.DoubleLength() < pow(m_SpriteSize.x/2, 2) ){

		/*int playersClusterSize= 0;
		vector<Dynamic*> dynamicPtrVect = m_MasterOfListsPtr->GetDynamicList()->GetVector();
		for( unsigned int plaats=0; plaats<dynamicPtrVect.size(); ++plaats){
			if( dynamicPtrVect.at(plaats) != 0 ){
				if( dynamicPtrVect.at(plaats)->GetCluster() == m_PlayerPtr->GetCluster() ){
					++playersClusterSize;
				}
			}
		}
		GAME_ENGINE->MessageBox(String("LevelComplete!\nClustersize of the player: ") +playersClusterSize);*/
		GAME_ENGINE->QuitGame();

	}
}

void EndPoint::Paint()
{
	MATRIX3X2 matCenter, matTranslate;
	matCenter.	 SetAsTranslate( -m_SpriteSize/2 );
	//matScale.	SetAsScale( (m_Straal*2) / m_BmpSpritePtr->GetWidth() );
	matTranslate.SetAsTranslate( m_Pos );

	GAME_ENGINE->SetTransformMatrix(matCenter * matTranslate * (*m_MatViewPtr));

	GAME_ENGINE->DrawBitmap(m_BmpSpritePtr, 0,0);

}