//---------------------------
// Includes
//---------------------------
#include "ShootBal.h"

#include "Bal.h"
//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap *ShootBal::m_BmpSpritePtr= 0;

ShootBal::ShootBal(DOUBLE2 pos): Dynamic(pos)
{
	if( m_BmpSpritePtr==0 ){
		m_BmpSpritePtr= new Bitmap("./recources/ShootBal.png");
	}

	m_SpriteSize.x= m_BmpSpritePtr->GetWidth();
	m_SpriteSize.y= m_BmpSpritePtr->GetHeight();

}

ShootBal::~ShootBal()
{
	// nothing to destroy
}

//---------------------------
// Own methods
//---------------------------

void ShootBal::Tick(double deltaTime)
{
	m_ShootCounter+= deltaTime;

	/*DOUBLE2 pointingVect= (m_PlayerPtr->GetPos()-m_Pos);
	double length= pointingVect.Length();

	if( length< 800 ){
		m_Direction= - pointingVect.AngleWith( DOUBLE2(0,1) );

		if( m_ShootCounter >= 1 ){
			m_ShootCounter= 0;
			new Bal( m_Pos, m_DynamicListPtr, 50000*pointingVect/length );

		}
	}*/
}

void ShootBal::Paint()
{
	MATRIX3X2 matCenter, matTranslate;
	matCenter.	 SetAsTranslate( -m_SpriteSize/2 );
	//matScale.	SetAsScale( (m_Straal*2) / m_BmpSpritePtr->GetWidth() );
	matTranslate.SetAsTranslate( m_Pos );

	GAME_ENGINE->SetTransformMatrix(matCenter * matTranslate * (*m_MatViewPtr));

	GAME_ENGINE->DrawBitmap(m_BmpSpritePtr, 0,0);

}