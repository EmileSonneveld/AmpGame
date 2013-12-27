//---------------------------
// Includes
//---------------------------
#include "Magnet.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap *Magnet::m_BmpSpritePtr= 0;

Magnet::Magnet(DOUBLE2 pos, double power): ObjectBase(pos), 
	m_Rotate(0), m_Power(power), m_Straal(400+rand()%600)//, m_Pos(pos)
{
	if( m_BmpSpritePtr==0 ){
		m_BmpSpritePtr= new Bitmap("recources/Magnet.png");
		m_BmpSpritePtr->SetOpacity(0.9);
	}
	m_SpriteSize.x= m_BmpSpritePtr->GetWidth();
	m_SpriteSize.y= m_BmpSpritePtr->GetHeight();
}

Magnet::Magnet(DOUBLE2 pos): ObjectBase(pos), 
	m_Rotate(0), m_Power(10-rand()%20), m_Straal(400)//, m_Pos(pos)
{
	if( m_BmpSpritePtr==0 ){
		m_BmpSpritePtr= new Bitmap("recources/Magnet.png");
		m_BmpSpritePtr->SetOpacity(0.9);
	}
	m_SpriteSize.x= m_BmpSpritePtr->GetWidth();
	m_SpriteSize.y= m_BmpSpritePtr->GetHeight();
}

Magnet::~Magnet()
{
	// nothing to destroy
}

//---------------------------
// Own methods
//---------------------------

void Magnet::Tick(double deltaTime)
{
	m_Rotate-= deltaTime* m_Power/10;
	//m_ObjectListPtr->Get
	vector<Dynamic*> dynamicPtrVect;
	dynamicPtrVect= m_DynamicListPtr->GetVector();
	for (unsigned int plaats=0; plaats<dynamicPtrVect.size(); ++plaats){
		if( dynamicPtrVect.at(plaats) != 0 ){
		Dynamic * otherPtr= dynamicPtrVect.at(plaats);
		DOUBLE2 deltaVect= otherPtr->GetPos() - m_Pos;
		double length= deltaVect.Length();
		if( length < m_Straal ){
			otherPtr->ApplyForce(deltaVect* ( 1-length/m_Straal )*m_Power  * deltaTime*60 );
		}
		}
	}
}


void Magnet::Paint()
{

	/*RECT2 clip;
	clip.left  = 0;
	clip.top   = 0;
	clip.right = clip.left+  m_SpriteSize.x;
	clip.bottom= clip.top +  m_SpriteSize.y;//*/

	MATRIX3X2 matCenter, matScale, matRotate, matTranslate;
	matCenter.	 SetAsTranslate( -m_SpriteSize/2 );
	matScale.	SetAsScale( (m_Straal) / m_BmpSpritePtr->GetWidth() );
	matRotate.	SetAsRotate(m_Rotate);
	matTranslate.SetAsTranslate( m_Pos );

	GAME_ENGINE->SetTransformMatrix(matCenter * matScale * matRotate * matTranslate * (*m_MatViewPtr));

	GAME_ENGINE->DrawBitmap(m_BmpSpritePtr, 0,0);


	matScale.	SetAsScale( (m_Straal) / m_BmpSpritePtr->GetWidth() *0.8 );
	matRotate.	SetAsRotate( m_Rotate*2 );

	GAME_ENGINE->SetTransformMatrix(matCenter * matScale * matRotate * matTranslate * (*m_MatViewPtr));

	GAME_ENGINE->DrawBitmap(m_BmpSpritePtr, 0,0);

}