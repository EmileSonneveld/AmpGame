//---------------------------
// Includes
//---------------------------
#include "Explosion.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap *Explosion::m_BmpSpritePtr= 0;

Explosion::Explosion(DOUBLE2 pos, DOUBLE2 velocity): ObjectBase(pos), m_AnimationTick(0), m_Velocity(velocity)
{
	m_Pos= pos;

	if( m_BmpSpritePtr==0 ){
		m_BmpSpritePtr= new Bitmap("recources/Explosion.png"); //14 frames
		m_BmpSpritePtr->SetTransparencyColor(255,0,255);
	}
	m_SpriteSize.x= m_BmpSpritePtr->GetWidth()/15; // geew width
	m_SpriteSize.y= m_BmpSpritePtr->GetHeight();
	m_AnimationSpeed= 0.3+ (double)( rand()%100 )/100;
}

Explosion::~Explosion(){}
//---------------------------
// Own methods
//---------------------------

void Explosion::Tick(double deltaTime){
	m_Pos+= m_Velocity * deltaTime;
	m_AnimationTick+= m_AnimationSpeed  * deltaTime*60;
	if( m_AnimationTick>=14 ) m_ObjectListPtr->Delete(this);
}


void Explosion::Paint(){

	if( m_AnimationTick>=14 ) m_AnimationTick= 0;

	MATRIX3X2 matCenter, matScale, matTranslate;
	matCenter.	 SetAsTranslate( -m_SpriteSize/2 );
	//matScale.	SetAsScale( (m_Radius) / m_BmpSpritePtr->GetWidth() );
	matTranslate.SetAsTranslate( m_Pos );
	GAME_ENGINE->SetTransformMatrix(matCenter /* matScale*/ * matTranslate * (*m_MatViewPtr));

	RECT2 clip;
	clip.left  = m_SpriteSize.x*(int)m_AnimationTick;
	clip.top   = 0;
	clip.right = clip.left+  m_SpriteSize.x;
	clip.bottom= clip.top +  m_SpriteSize.y;

	GAME_ENGINE->DrawBitmap(m_BmpSpritePtr, 0,0, clip);

}
