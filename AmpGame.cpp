//-----------------------------------------------------------------
// Game File
// C++ Source - AmpGame.cpp - version 2012 v2_10
// Copyright Kevin Hoefman - kevin.hoefman@howest.be
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "AmpGame.h"

#include <fstream>
//#include <sstream>
using namespace std;

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//-----------------------------------------------------------------
// AmpGame methods																				
//-----------------------------------------------------------------

AmpGame::AmpGame(): m_MatView(), m_ViewScale(2), m_MouseDown(false)//, m_BmpBGPtr(0)
{}

AmpGame::~AmpGame()
{}

void AmpGame::GameInitialize(HINSTANCE hInstance)			
{
	// Set the required values
	AbstractGame::GameInitialize(hInstance);
	GAME_ENGINE->SetTitle("AmpGame");
	GAME_ENGINE->RunGameLoop(true);
	
	// Set the optional values
	GAME_ENGINE->SetWidth(1200);
	GAME_ENGINE->SetHeight(980);
	GAME_ENGINE->SetFrameRate(60);
	GAME_ENGINE->SetTickPaintRatio(2); //  best niet veranderen
	//GAME_ENGINE->SetKeyList(String("QSDZ") + (TCHAR) VK_SPACE);


	GAME_ENGINE->EnableAntiAlias(true);
}

void AmpGame::GameStart()
{
	// ini-files lezen zit in de winAPI
	//UINT value = GetPrivateProfileInt("Section", "Key", DEFAULT_VALUE, "program.ini");
	
	m_LevelMaxPos.x= 50000 ;
	m_LevelMaxPos.y= 160000;

	// __THE LISTS _____________________________________
	m_MasterOfListsPtr = new MasterOfLists(&m_MatView, m_LevelMaxPos);
	//m_MasterOfListsPtr->SetMatViewPtr(   &m_MatView );


	m_PlayerPtr= m_MasterOfListsPtr->GetPlayerPtr();
	//m_MasterOfListsPtr->NewPlayer(DOUBLE2(200, 200));

	double distance= 190;
	for( double radians= 0; radians<2*M_PI; radians+= 2*M_PI/8 ){
		m_MasterOfListsPtr->NewBal(m_PlayerPtr->GetPos()+distance*DOUBLE2(cos(radians), -sin(radians)));
		//Bal *tmpPtr= new Bal(m_PlayerPtr->GetPos()+distance*DOUBLE2(cos(radians), -sin(radians)) , m_DynamicListPtr);
	}
}

void AmpGame::GameEnd()
{
	// __THE LISTS _____________________________________
	delete m_MasterOfListsPtr;
	m_MasterOfListsPtr= 0;

}

//void AmpGame::GameActivate()
//{
//	// Insert the code that needs to be executed when the game window becomes active
//
//	/* Example:
//	GAME_ENGINE->SetSleep(false);
//	*/
//}
//
//void AmpGame::GameDeactivate()
//{
//	// Insert the code that needs to be executed when the game window becomes inactive
//
//	/* Voorbeeld:
//	GAME_ENGINE->SetSleep(true);
//	*/
//}

void AmpGame::MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam)
{
	m_MousePos= DOUBLE2( x, y );
	m_MousePos.x= m_PosCamera.x+ ( x - GAME_ENGINE->GetWidth() /2 )*m_ViewScale;
	m_MousePos.y= m_PosCamera.y+ ( y - GAME_ENGINE->GetHeight()/2 )*m_ViewScale;

	if (isLeft == true && isDown == true)
		m_MouseDown= true;
	if (isLeft == true && isDown == false)
		m_MouseDown= false;
	

	if (isLeft == false && isDown == true) m_MasterOfListsPtr->NewBal( m_MousePos );
		//Bal *tmpPtr= new Bal(m_MousePos, m_DynamicListPtr);
}

void AmpGame::MouseMove(int x, int y, WPARAM wParam){	
	m_MousePos= DOUBLE2( x, y );
	m_MousePos.x= m_PosCamera.x+ ( x - GAME_ENGINE->GetWidth() /2 )*m_ViewScale;
	m_MousePos.y= m_PosCamera.y+ ( y - GAME_ENGINE->GetHeight()/2 )*m_ViewScale;
}

//void AmpGame::CheckKeyboard()
//{	
//	// Here you can check if a key of choice is held down
//	// Is executed once per frame 
//
//	/* Example:
//	if (GAME_ENGINE->IsKeyDown('K')) xIcon -= xSpeed;
//	if (GAME_ENGINE->IsKeyDown('L')) yIcon += xSpeed;
//	if (GAME_ENGINE->IsKeyDown('M')) xIcon += xSpeed;
//	if (GAME_ENGINE->IsKeyDown('O')) yIcon -= ySpeed;
//	*/
//}
//
//void AmpGame::KeyPressed(TCHAR cKey)
//{	
//	// DO NOT FORGET to use SetKeyList() !!
//
//	// Insert the code that needs to be executed when a key of choice is pressed
//	// Is executed as soon as the key is released
//	// You first need to specify the keys that the game engine needs to watch by using the SetKeyList() method
//
//	/* Example:
//	switch (cKey)
//	{
//	case 'K': case VK_LEFT:
//		MoveBlock(DIR_LEFT);
//		break;
//	case 'L': case VK_DOWN:
//		MoveBlock(DIR_DOWN);
//		break;
//	case 'M': case VK_RIGHT:
//		MoveBlock(DIR_RIGHT);
//		break;
//	case 'A': case VK_UP:
//		RotateBlock();
//		break;
//	case VK_ESCAPE:
//	}
//	*/
//}

void AmpGame::GameTick(double deltaTime)
{
	// View Scalen
	if( GAME_ENGINE->IsKeyDown('A') ) m_ViewScale*= 1.02;
	if( GAME_ENGINE->IsKeyDown('E') ) m_ViewScale/= 1.02;

	if( GAME_ENGINE->IsKeyDown(VK_ESCAPE) ) GAME_ENGINE->QuitGame();

	//if( deltaTime >= 0.5 ) DebugBreak();
	deltaTime= min( 0.02, deltaTime);
	m_DeltaTime= deltaTime;

	if( m_MouseDown ){
		vector<Dynamic*> dynamicPtrVect = MasterOfLists::GetDynamicList()->GetVector();
		for( unsigned int plaats=0; plaats<dynamicPtrVect.size(); ++plaats){
			if( dynamicPtrVect.at(plaats) != 0 ){
				dynamicPtrVect.at(plaats)->MoveTo(m_MousePos, 600, -5 );
			}
		}
		//m_PlayerPtr->SetPos( m_MousePos );
	}

	// __THE LISTS _____________________________________
	m_MasterOfListsPtr->Tick(deltaTime); 

	if( m_PlayerPtr->GetPos().y > m_LevelMaxPos.y ){
		int playersClusterSize= 0;
		vector<Dynamic*> dynamicPtrVect = m_MasterOfListsPtr->GetDynamicList()->GetVector();
		for( unsigned int plaats=0; plaats<dynamicPtrVect.size(); ++plaats){
			if( dynamicPtrVect.at(plaats) != 0 ){
				if( dynamicPtrVect.at(plaats)->GetCluster() == m_PlayerPtr->GetCluster() ){
					++playersClusterSize;
				}
			}
		}
		GAME_ENGINE->MessageBox(String("LevelComplete!\nClustersize of the player: ") +playersClusterSize);
		GAME_ENGINE->QuitGame();
	}

	if( GAME_ENGINE->IsKeyDown('N') ) // new Ball
		new Bal(m_MousePos, 0);

	DoCameraMovement(deltaTime, m_PlayerPtr->GetPos());
}

void AmpGame::GamePaint(RECT rect)
{
	GAME_ENGINE->SetTransformMatrix(MATRIX3X2());
	GAME_ENGINE->DrawSolidBackground(222,222,242);
	

	MATRIX3X2 matCenter, matScale, matTranslate;
	matCenter		.SetAsTranslate(-GAME_ENGINE->GetWidth()/2,-GAME_ENGINE->GetHeight()/2);
	matScale		.SetAsScale(m_ViewScale);
	matTranslate	.SetAsTranslate(m_PosCamera);
	m_MatView= (matCenter * matScale * matTranslate).Inverse();

	GAME_ENGINE->SetTransformMatrix(m_MatView);

	GAME_ENGINE->SetColor(100,150,200);
	GAME_ENGINE->FillRect(0,0,m_LevelMaxPos.x, m_LevelMaxPos.y );

	GAME_ENGINE->SetColor(0,0,0);
	GAME_ENGINE->DrawRect(0,0,m_LevelMaxPos.x, m_LevelMaxPos.y );
	

	// __THE LISTS _____________________________________
	m_MasterOfListsPtr->Paint(); 
	

	GAME_ENGINE->SetTransformMatrix(MATRIX3X2());
	GAME_ENGINE->SetColor(0,0,0);
	int fps= (int)( 1/m_DeltaTime );
	GAME_ENGINE->DrawString(String("FPS: ")+ fps , 10, 10);
	
}

//void AmpGame::CallAction(Caller* callerPtr)
//{
//	// Insert the code that needs to be executed when a Caller has to perform an action
//}




void AmpGame::DoCameraMovement(double deltaTime, DOUBLE2 playerPos)
{
	//-- De player blijft in het scherm--//
	int deler=5; // hoe ver van de kant.
	if (m_PosCamera.x< playerPos.x-GAME_ENGINE->GetWidth() /deler *m_ViewScale)
		m_PosCamera.x= playerPos.x-GAME_ENGINE->GetWidth() /deler *m_ViewScale;
	if (m_PosCamera.x> playerPos.x+GAME_ENGINE->GetWidth() /deler *m_ViewScale)
		m_PosCamera.x= playerPos.x+GAME_ENGINE->GetWidth() /deler *m_ViewScale;
	if (m_PosCamera.y< playerPos.y-GAME_ENGINE->GetHeight()/deler *m_ViewScale)
		m_PosCamera.y= playerPos.y-GAME_ENGINE->GetHeight()/deler *m_ViewScale;
	if (m_PosCamera.y> playerPos.y+GAME_ENGINE->GetHeight()/deler *m_ViewScale)
		m_PosCamera.y= playerPos.y+GAME_ENGINE->GetHeight()/deler *m_ViewScale;

	//-- Camera volgt player --//
	//m_PosCamera=playerPos;

	//-- Besturing Camera --//
	/*double camSpeed= 250*deltaTime;
	if(GAME_ENGINE->IsKeyDown('D')) m_PosCamera.x+=camSpeed; // VK_RIGHT	
	if(GAME_ENGINE->IsKeyDown('Q')) m_PosCamera.x-=camSpeed; // VK_LEFT	
	if(GAME_ENGINE->IsKeyDown('S')) m_PosCamera.y+=camSpeed; // VK_DOWN	
	if(GAME_ENGINE->IsKeyDown('Z')) m_PosCamera.y-=camSpeed; // VK_UP		
	//*/

	//-- Binnen de wereld blijven --//
	
	/*if (m_PosCamera.x<					 GAME_ENGINE->GetWidth() /2 *m_ViewScale)
		m_PosCamera.x=					 GAME_ENGINE->GetWidth() /2 *m_ViewScale;
	if (m_PosCamera.x> m_LevelMaxPos.x	-GAME_ENGINE->GetWidth() /2 *m_ViewScale)
		m_PosCamera.x= m_LevelMaxPos.x	-GAME_ENGINE->GetWidth() /2 *m_ViewScale;
	if (m_PosCamera.y<					 GAME_ENGINE->GetHeight()/2 *m_ViewScale)
		m_PosCamera.y=					 GAME_ENGINE->GetHeight()/2 *m_ViewScale;
	if (m_PosCamera.y> m_LevelMaxPos.y	-GAME_ENGINE->GetHeight()/2 *m_ViewScale)
		m_PosCamera.y= m_LevelMaxPos.y	-GAME_ENGINE->GetHeight()/2 *m_ViewScale;//*/

}

bool AmpGame::FileExists( String filename )
{
	ifstream openFile(filename.ToTChar());
	if( openFile ){
		return true;
	}
	return false;
	// openFile zit in de stack en word dus nu gedelete
}