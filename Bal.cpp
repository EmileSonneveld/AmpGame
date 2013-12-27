//---------------------------
// Includes
//---------------------------
#include "Bal.h"
#include "Explosion.h"


//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap *Bal::m_BmpSpritePtr= 0;

Bal::Bal(DOUBLE2 pos, DOUBLE2 force): Dynamic(pos), m_LinksGelged(false)
{
	ApplyForce(force);
	BitmapStuff();
	m_Straal+= 5-rand()%10;
}

Bal::Bal(DOUBLE2 pos, int linksWanted): Dynamic(pos), m_LinksGelged(false)
{
	BitmapStuff();
	m_Straal+= 5-rand()%10;
	if( linksWanted ==0 ) m_LinksGelged= true;
}


Bal::~Bal(){
	
}

//---------------------------
// Own methods
//---------------------------

void Bal::BitmapStuff(){
	if( m_BmpSpritePtr==0 ){
		m_BmpSpritePtr= new Bitmap("./recources/player.png");
		//m_BmpSpritePtr->SetTransparencyColor(255,0,255);
	}
	m_SpriteSize.x= m_BmpSpritePtr->GetWidth();
	m_SpriteSize.y= m_BmpSpritePtr->GetHeight();
}

void Bal::Tick(double deltaTime){

	TickSetDistance(deltaTime);

	friction(100);

	Move( deltaTime );

	if( !m_LinksGelged ){
		if( CountDynamicsInRadius(m_TargetLen*1.3) >= 3){
			MakeLinks(m_TargetLen*1.3);
			m_LinksGelged = true;
		}
		if( CountDynamicsInRadius(m_TargetLen) >= 2){
			MakeLinks(m_TargetLen);
			m_LinksGelged = true;
		}
		if( MakeLinks(m_TargetLen/2) >0 )
			m_LinksGelged = true;
	}


	//m_DinamicPtr->Tick(deltaTime);

	// Impuls destruction -------------------------
	if( (m_OldVelocity- m_Velocity).Length()> 1800 ){
		new Explosion(m_Pos, m_Velocity*(-0.5));
		//m_DynamicListPtr->Delete(this);
	}
}

void Bal::Paint(){
	GAME_ENGINE->SetTransformMatrix(*m_MatViewPtr);
	PaintDynamic();

	MATRIX3X2 matCenter, matScale, matTranslate;
	matCenter.	 SetAsTranslate( -m_SpriteSize/2 );
	matScale.	SetAsScale( (m_Straal*2) / m_BmpSpritePtr->GetWidth() );
	matTranslate.SetAsTranslate( m_Pos );
	
	GAME_ENGINE->SetTransformMatrix(matCenter * matScale * matTranslate * (*m_MatViewPtr));
	
	GAME_ENGINE->DrawBitmap(m_BmpSpritePtr, 0,0);
	
}
