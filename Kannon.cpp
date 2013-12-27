//---------------------------
// Includes
//---------------------------
#include "Kannon.h"

#include "Player.h"
#include "Bal.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap *Kannon::m_BmpSpritePtr= 0;

Kannon::Kannon(DOUBLE2 pos): ObjectBase(pos), 
	m_Direction(0), m_ShootCounter(0)
{
	if( m_BmpSpritePtr==0 ){
		m_BmpSpritePtr= new Bitmap("recources/Kannon.png");
		//m_BmpSpritePtr->SetOpacity(0.9);
	}
	m_SpriteSize.x= m_BmpSpritePtr->GetWidth();
	m_SpriteSize.y= m_BmpSpritePtr->GetHeight();
	m_MaxTargetDistance= 1800;
};

Kannon::~Kannon()
{
	// nothing to destroy
}


//---------------------------
// Own methods
//---------------------------

void Kannon::Tick(double deltaTime)
{
	m_ShootCounter+= deltaTime;

	DOUBLE2 pointingVect= (m_PlayerPtr->GetPos()-m_Pos);
	double length= pointingVect.Length();

	if( length< m_MaxTargetDistance ){
		m_Direction= - pointingVect.AngleWith( DOUBLE2(0,1) );

		if( m_ShootCounter >= 1 ){
			m_ShootCounter= 0;
			new Bal( m_Pos, 23000*pointingVect/length );

		}
	}
}

void Kannon::Paint()
{
	MATRIX3X2 matCenter, matRotate, matTranslate;
	matCenter.	 SetAsTranslate( -m_SpriteSize/2 );
	//matScale.	SetAsScale( (m_Straal) / m_BmpSpritePtr->GetWidth() );
	matRotate.	SetAsRotate(m_Direction);
	matTranslate.SetAsTranslate( m_Pos );

	GAME_ENGINE->SetTransformMatrix(matCenter * matRotate * matTranslate * (*m_MatViewPtr));

	GAME_ENGINE->DrawBitmap(m_BmpSpritePtr, 0,0);

	GAME_ENGINE->SetTransformMatrix(matCenter * matTranslate * (*m_MatViewPtr));
	GAME_ENGINE->DrawEllipse(0,0, m_MaxTargetDistance, m_MaxTargetDistance);
}