//---------------------------
// Includes
//---------------------------
#include "Player.h"
#include "Explosion.h"
#include <iostream>
#include "ListsController.h"


//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())


//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap *Player::m_BmpSpritePtr= 0;

Player::Player(DOUBLE2 pos):Dynamic(pos), m_Health(100)
{
	//m_DynamicList= dynamicList;
	//m_ObjectList= objectList;
	//m_Pos= pos;
	//m_DynamicPtr= new Dynamic(&m_Pos);
	//dynamicList->Add( m_DynamicPtr );

	m_Mass= 20;
	m_Straal= 30;

	if( m_BmpSpritePtr==0 ){
		m_BmpSpritePtr= new Bitmap("./recources/bol.png");
		//m_BmpSpritePtr->SetTransparencyColor(255,0,255);
	}
	m_SpriteSize.x= m_BmpSpritePtr->GetWidth();
	m_SpriteSize.y= m_BmpSpritePtr->GetHeight();

	m_HitRegionPtr= new HitRegion();
	m_HitRegionPtr->CreateFromRect(-m_SpriteSize.x/2, -m_SpriteSize.y/2, m_SpriteSize.x, m_SpriteSize.y);

	m_GasPowerMax= 10;
	m_GasPower= 0;
	m_GasPowerConsumption= 0.03;

}

Player::~Player(){}


//---------------------------
// Own methods
//---------------------------
/*void Player::PassGlobalVars(HitRegion *backgroundHitPtr, DOUBLE2 *mousePos){
	//m_HitBgPtr= backgroundHitPtr;
	//m_DynamicPtr->PassGlobalVars(m_BackgroundHitPtr);
	m_MousePos= mousePos;
}*/

void Player::Tick(double deltaTime){
	m_GasPower= min( m_GasPowerMax, m_GasPower+deltaTime );
	//if( rand()%2<1 )
	//	m_ObjectListPtr->Add( new Explosion( m_Pos ) );

	if( GAME_ENGINE->IsKeyDown('X') ){
		for( unsigned int myLink=0; myLink<m_LinkList.size(); ++myLink ){
			if( rand()%10 < deltaTime*60 )
				RemoveLink(myLink);
		}
	}


	double power= 90 * deltaTime*60;
	DOUBLE2 PointingDir(0,0);
	if( GAME_ENGINE->IsKeyDown(VK_LEFT) || GAME_ENGINE->IsKeyDown('Q') ){PointingDir.x=-1;}
	if( GAME_ENGINE->IsKeyDown(VK_RIGHT)|| GAME_ENGINE->IsKeyDown('D') ){PointingDir.x= 1;}
	if( GAME_ENGINE->IsKeyDown(VK_UP)   || GAME_ENGINE->IsKeyDown('Z') ){PointingDir.y=-1;}
	if( GAME_ENGINE->IsKeyDown(VK_DOWN) || GAME_ENGINE->IsKeyDown('S') ){PointingDir.y= 1;}
	if( GAME_ENGINE->IsKeyDown(VK_SHIFT) ){
		if( m_GasPower>0 ){
			m_GasPower-= m_GasPowerConsumption;
		power*= 5;
		//if( rand()%2<1 )
		for( int i=0; i<1; ++i){
			DOUBLE2 pos(m_Pos.x+rand()%(int)m_Straal-m_Straal, m_Pos.y+rand()%(int)m_Straal-m_Straal );
			new Explosion( pos, -power*PointingDir.Normalized());
			//m_ObjectListPtr->Add( new Explosion( m_Pos, m_ObjectListPtr ) );
		}
		}
	}

	//ApplyForce(PointingDir.Normalized()*power); // hoe zwaarder het object, hoe mer kracht het meestal heeft.
	m_Acceleration+= PointingDir.Normalized()*power;  // dus de velocity is niet afhankelijk vd massa.

	//m_DinamicPtr->Tick( deltaTime );

	// SPACE WARP ------------------------------------------------
	/*if( m_Pos.x<0 ) m_Pos.x= GAME_ENGINE->GetWidth();
	if( m_Pos.x>GAME_ENGINE->GetWidth() ) m_Pos.x= 0;
	if( m_Pos.y<0 ) m_Pos.y= GAME_ENGINE->GetHeight();
	if( m_Pos.y>GAME_ENGINE->GetHeight() ) m_Pos.y= 0;*/

	TickSetDistance(deltaTime);

	friction(100);

	Move( deltaTime );

}

void Player::Paint(){

	GAME_ENGINE->SetTransformMatrix(*m_MatViewPtr);
	PaintDynamic();

	MATRIX3X2 matCenter, matScale, matTranslate;
	matCenter.	 SetAsTranslate( -m_SpriteSize/2 );
	matScale.	SetAsScale( (m_Straal*2) / m_BmpSpritePtr->GetWidth() );
	matTranslate.SetAsTranslate( m_Pos );
	GAME_ENGINE->SetTransformMatrix(matCenter * matScale * matTranslate * (*m_MatViewPtr));
	GAME_ENGINE->DrawBitmap(m_BmpSpritePtr, 0,0);

	//DOUBLE2 velocity;//= m_MousePos-m_Pos;
	//RayTest(0.016, &m_Pos, &velocity);

	//m_DinamicPtr->Tick( 0.016);
	GAME_ENGINE->SetTransformMatrix(MATRIX3X2());
	GAME_ENGINE->SetColor(0,0,0, 200);
	GAME_ENGINE->DrawRect(20, 60, m_GasPowerMax*50, 42);
	GAME_ENGINE->SetColor(233,20,0, 200);
	GAME_ENGINE->FillRect(21, 61, m_GasPower*50, 40);
}
