// *********************************************************//
//				(c) Emile Sonneveld							//
//				emile.sonneveld@howest.be					//
// *********************************************************//

//---------------------------
// Includes
//---------------------------
#include "MasterOfLists.h"
#include "ListsController.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())
//using namespace std;

//---------------------------
// Constructor & Destructor
//---------------------------
Dynamic::Dynamic(DOUBLE2 pos):// m_HitBgPtr(0),
	m_Pos(pos), m_Velocity(), m_Acceleration(),
	m_Mass(10), m_K(5), m_Gravity(15), m_Straal(10+rand()%20), m_OldVelocity()
{
	m_MasterOfListsPtr= MasterOfLists::GetSignleton();
	m_DynamicListPtr= m_MasterOfListsPtr->GetDynamicList();

	m_Cluster= m_DynamicListPtr->GetMaxCluster(); //Cluster Tracking
	m_DynamicListPtr->VerhoogMaxCluster();

	m_Straal= 20;
	m_PosPtr= &m_Pos;
	m_MaxLinks= MAX_LINKS;
	m_TargetLen= 200;
	//m_Bounce= 0.4; // tussen 0.1 en 1 zijn
	
	m_DynamicListPtr->Add( this );
}

Dynamic::~Dynamic() {
	
	unsigned int max= m_LinkList.size();
	for (unsigned int plaats=0; plaats<m_LinkList.size(); ++plaats){
		RemoveLink( 0 );
		//RemoveLink( plaats ); // delete alles dat naar dit object verwijst.
	}
	
	//m_DynamicListPtr->Delete(this);
}


//---------------------------
// Own methods
//---------------------------

void Dynamic::TickSetDistance(double deltaTime){
		
	for( unsigned int b= 0; b<m_LinkList.size(); ++b ){

		Dynamic *bPtr= m_LinkList.at(b);
		
		DOUBLE2 AB= bPtr->m_Pos - m_Pos; // difference vector
		double deltaLength= AB.Length();
		
		double verschil=   deltaLength - m_LinkLen.at(b); //Hooke's Law

		
		// Power
		double power;
		//power= pow( abs(verschil)/2, 1.5 )*10;		if( verschil<0 ) power= -power;
		double k= 50;							power= k * verschil;	// veerconstante;

		this->ApplyForce( AB.Normalized() * power );
		bPtr->ApplyForce( AB.Normalized() *-power );//*/

		// bij te grote impuls gaat de conectie kapot. Dit voorkomt ook dynamics explotions
		if(  abs(deltaLength/m_LinkLen.at(b) - 1)> 1.2){ //power>6000 ||
			RemoveLink(b);
			OutputDebugString("\nImpulsBreak!");
			return;
		}
		

		//this->m_Velocity*=0.9;
		//bPtr->m_Velocity*=0.9;

		/*if( false ){ // niet werkende friction.
			DOUBLE2 velocity1, velocity2;
			velocity1= AB.Normalized() * AB.DotProduct( m_Velocity );
			velocity2= m_Velocity - velocity1;
			velocity1*= 0.8;
			m_Velocity= velocity1 + velocity2;
			
			/*velocity1= AB * AB.DotProduct( bPtr->m_Velocity );
			velocity2= bPtr->m_Velocity - velocity1;
			velocity1*= 0.8;
			bPtr->m_Velocity= velocity1 + velocity2;//*/
		//}
	}

}









void Dynamic::ApplyForce(DOUBLE2 force){
	m_Acceleration+= force/ m_Mass;
}

int Dynamic::CountDynamicsInRadius( double straal )
{
	int num=0;

	vector<Dynamic*> objectPtrVect= m_DynamicListPtr->GetVector();
	for( unsigned int i=0; i< objectPtrVect.size(); ++i){
		if( objectPtrVect.at(i)!=this &&  objectPtrVect.at(i)!=0){
			if( (objectPtrVect.at(i)->m_Pos - m_Pos ).Length() < straal ){
				++num;
			}
		}
	}
	return num;
}

int Dynamic::MakeLinks(double straal)
{
	int num=0;

	vector<Dynamic*> objectPtrVect= m_DynamicListPtr->GetVector();
	for( unsigned int i=0; i< objectPtrVect.size(); ++i){
		if( objectPtrVect.at(i)!=this &&  objectPtrVect.at(i)!=0){
			if( (objectPtrVect.at(i)->m_Pos - m_Pos ).Length() < straal ){
				AddToLinkList( objectPtrVect.at(i) );
				++num;
			}
		}
	}
	return num;

}

void Dynamic::AddToLinkList(Dynamic* otherPtr){
	if( otherPtr == this ) return; // niet met zichzelf linken.
	if( (int)m_LinkList.size()<=m_MaxLinks /*&&  (other->m_LinkList).size()<=other->m_MaxLinks*/ ){

		double len= (*otherPtr->m_PosPtr-*m_PosPtr).Length();

		if( m_Straal + otherPtr->m_Straal > len ) return; // te kleine afstand geeft problemen

		// hier word de link gelegd:
		otherPtr->SetCluster(m_Cluster);
		this->m_LinkList.push_back(otherPtr);
		this->m_LinkLen. push_back( len );
		otherPtr->m_LinkList.push_back(this);
		otherPtr->m_LinkLen.push_back( len );

	}
}


void Dynamic::RemoveLink(int plaats)
{
	Dynamic *plaatsPtr = m_LinkList.at( plaats );

	//int erasePlaatsen[MAX_LINKS];
	//int counter= 0;

	m_LinkList.erase(m_LinkList.begin() + plaats);
	m_LinkLen.erase(  m_LinkLen.begin() + plaats);

	for( unsigned int hisLink= 0; hisLink< plaatsPtr->m_LinkList.size(); ++hisLink ){
		if( plaatsPtr->m_LinkList.at(hisLink) == this ){
			plaatsPtr->m_LinkList.erase(plaatsPtr->m_LinkList.begin() + hisLink);
			plaatsPtr->m_LinkLen.erase( plaatsPtr-> m_LinkLen.begin() + hisLink);
			plaatsPtr->SetCluster( m_DynamicListPtr->GetMaxCluster() );
			m_DynamicListPtr->VerhoogMaxCluster();
			return;
		}
	}

	/*for( int i= 0; i<counter; ++i ){
		plaatsPtr->m_LinkList.erase(plaatsPtr->m_LinkList.begin() + erasePlaatsen[i]);
		plaatsPtr->m_LinkLen.erase( plaatsPtr-> m_LinkLen.begin() + erasePlaatsen[i]);
	}*/

	
}

void Dynamic::SetCluster(int cluster)
{
	if( m_Cluster < cluster ){ // kleinste nummer wint
		m_Cluster= cluster;
		for( unsigned int i=0; i< m_LinkList.size(); ++i){
			m_LinkList.at(i)->SetCluster(m_Cluster);
		}
	}

}

void Dynamic::MoveTo( DOUBLE2 targetPos, double maxLen, double force )
{
	DOUBLE2 deltaVect= m_Pos- targetPos;
	double length= deltaVect.Length();
	if( length < maxLen ){
		this->ApplyForce(deltaVect* ( 1-length/maxLen )*force );
	}
}

void Dynamic::DeleteMe()
{
	m_DynamicListPtr->Delete(this);
}


void Dynamic::PaintDynamic()
{
	//GAME_ENGINE->SetTransformMatrix((*m_MatViewPtr));
	//GAME_ENGINE->FillEllipse(m_Pos, m_Straal, m_Straal);

	GAME_ENGINE->SetColor(255,5,5, 20);
	if( GAME_ENGINE->IsKeyDown('C') )
		GAME_ENGINE->FillEllipse(*m_PosPtr, m_TargetLen, m_TargetLen);

	

	for( unsigned int myLink=0; myLink<m_LinkList.size(); ++myLink ){

		Dynamic *bPtr= m_LinkList.at(myLink);
		
		DOUBLE2 AB= bPtr->m_Pos - m_Pos; // difference vector
		double deltaLength= AB.Length();
		double verschil=   deltaLength - m_LinkLen.at(myLink); 

		double scaler= min(255, max( 0,  abs(verschil)/80 ) );

		GAME_ENGINE->SetColor((int)(scaler*255), 60, m_Cluster);
		GAME_ENGINE->DrawLine(m_Pos, (m_LinkList.at(myLink)->m_Pos+m_Pos)/2, m_Straal/2);


		/*for( unsigned int otherLink=0; otherLink<m_LinkList.at(myLink)->m_LinkList.size(); ++otherLink ){
			for( unsigned int myLink2=0; myLink2<m_LinkList.size(); ++myLink2 ){
				if( m_LinkList.at(otherLink)==m_LinkList.at(myLink2) ){
					POINT tri[3]; // OVERKILL COMPLEX POINT ARRAY!!
					tri[0].x= (long)( *                  this->m_LinkList.at(myLink   )->m_PosPtr ).x ;
					tri[0].y= (long)( *                  this->m_LinkList.at(myLink   )->m_PosPtr ).y ;
					tri[1].x= (long)( * m_LinkList.at(myLink)->m_LinkList.at(otherLink)->m_PosPtr ).x ;
					tri[1].y= (long)( * m_LinkList.at(myLink)->m_LinkList.at(otherLink)->m_PosPtr ).y ;
					tri[2].x= (long)( *                  this->m_LinkList.at(myLink2  )->m_PosPtr ).x ;
					tri[2].y= (long)( *                  this->m_LinkList.at(myLink2  )->m_PosPtr ).y ;
					GAME_ENGINE->DrawPolygon(tri,3,true);
					//GAME_ENGINE->FillPolygon(tri, 2, 1);
				}
			}
		}//*/
	}

	// Cluster Tracking
	/*GAME_ENGINE->SetColor(10, 60, m_Cluster*30);
	GAME_ENGINE->FillEllipse(m_Pos, m_Straal, m_Straal);

	GAME_ENGINE->SetColor(0, 0, 0);
	GAME_ENGINE->DrawString(String("")+m_Cluster, m_Pos);//*/
}


void Dynamic::Move(double deltaTime)
{
	m_Acceleration.y+= m_Gravity * deltaTime*60;
	m_OldVelocity= m_Velocity;
	m_Velocity+= m_Acceleration;
	//*m_PosPtr+=  m_Velocity     * deltaTime;
	m_Acceleration= DOUBLE2();

	RayBounceWrapper(deltaTime); // Kan ook multi-tretherd! Zie GameEngine (concurrency problemen...)
	//RayBounce(deltaTime, &m_Pos,  &m_Velocity);

	//DOUBLE2 pos= *m_PosPtr;
	if( GAME_ENGINE->IsKeyDown('X') ){
		for( unsigned int myLink=0; myLink<m_LinkList.size(); ++myLink ){
			if( rand()%140 < deltaTime*60 )
				RemoveLink(myLink);
		}
	}

	if(  m_Pos.x<0 ) ApplyForce(DOUBLE2(-m_Pos.x*4, 0));

	double xTeVeel=  m_MasterOfListsPtr->GetLevelMaxPos().x - m_Pos.x;
	if( xTeVeel<0 ) ApplyForce(DOUBLE2( xTeVeel*4, 0));

	//xMarge= m_Pos.x - m_LevelMaxPos.x;
	//if(  xMarge>0 ) ApplyForce(DOUBLE2(-xMarge*2, 0));
}

void Dynamic::RayBounceWrapper(double deltaTime)
{
	RayBounce(deltaTime, &m_Pos,  &m_Velocity);
}

void Dynamic::RayBounce(double deltaTime, DOUBLE2 *pos, DOUBLE2 *velocity)
{
	bool canIPaint= false;
	DOUBLE2 moveVector= *velocity * deltaTime; // afstand af te leggen.
	//DOUBLE2 moveVector= ( *m_MousePos - pos ).Normalized() * 1000; // afstand af te leggen.
	double moveVectorLen= moveVector.Length();
	
	
	//HIT hitStructArr[1];
	HIT hitStruct;
	int nrOfHits;
	//int nrOfIterations=0;
	//while( true ){ // als er iets misloopt, dan hapert de game
	for( int nrOfIterations= 0; nrOfIterations<20; ++nrOfIterations){
		//nrOfHits= m_HitBgPtr->Raycast(*pos, moveVector, hitStructArr, 1, -1);
		nrOfHits= m_HitRegionListPtr->Raycast(*pos, moveVector, &hitStruct, m_Straal);

		if( nrOfHits==0 ){
			if( nrOfIterations>=3 )
				OutputDebugString(String("\nnrOfIterations:")+nrOfIterations);
			if( canIPaint ){ GAME_ENGINE->SetColor(0,0,0); GAME_ENGINE->DrawLine(*pos, *pos+  moveVector, 2 ); }
			*pos+=  moveVector;
			*velocity= moveVector.Normalized() * moveVectorLen / deltaTime;
			break; // simpele versie, na of zonder botsingen

		} else if (nrOfHits>0 ){
			
			DOUBLE2 normal= hitStruct.normal;

			// MANIER1
			/*DOUBLE2 restLen= m_MoveVector*( 1-hitStruct[0].time);
			DOUBLE2 projected=  -normal * normal.DotProduct(restLen); 
			m_MoveVector= restLen +2*projected;//*/

			moveVector*= ( 1-hitStruct.time);
			double lenBefore= moveVector.Length();

			// Gebotste velocity berekenen.
			DOUBLE2 vector1= normal * normal.DotProduct( moveVector ); // m_Velocity
			DOUBLE2 vector2= moveVector - vector1;
			vector1*= -0.4; // Bounce factor
			//vector2= vector2.Normalized() * ( moveVector.Length() -vector1.Length() );
			moveVector= vector1 + vector2;

			double lenAfter= moveVector.Length();
			moveVectorLen*= lenAfter/lenBefore;


			if( canIPaint ){ GAME_ENGINE->SetColor(0,0,0, 200); GAME_ENGINE->DrawLine(*pos, hitStruct.point,2 );}

			*pos= hitStruct.point + -normal*0.1;

			if( canIPaint ){
				GAME_ENGINE->SetColor(0,255,0);
				GAME_ENGINE->FillEllipse(*pos, 3,3);

				GAME_ENGINE->DrawLine(*pos, *pos+ normal*20 );
			}

			//m_MoveVector= m_MoveVector.Normalized() * restLenD;

			//*m_PosPtr+= m_MoveVector; // Hij mag hier niet verplaatsen, er kan nog een botsing zijn.
		}
	} //*/ END loop

}


void Dynamic::DrawArrows(){
	GAME_ENGINE->SetColor(5,255,5, 150);
	GAME_ENGINE->DrawLine(m_Pos, m_Pos + m_Acceleration/5, 3); // 
	GAME_ENGINE->SetColor(255,5,5, 150);
	GAME_ENGINE->DrawLine(m_Pos, m_Pos + m_Velocity/5, 5); // altijd (0,0)
	//GAME_ENGINE->DrawLine(*m_PosPtr, *m_PosPtr + ); // 

}


void Dynamic::friction(double deler){
	//ApplyForce( m_K*(-m_Velocity.Normalized()) ); // vrijving constant
	ApplyForce( -m_Velocity.Normalized()* pow(m_Velocity.Norm()/deler, 1.3) ); // vrijving ifv snelhijd
}


void Dynamic::Bounce(Dynamic *oponentPtr)
{
	if( oponentPtr == this ) return; // niet met zichzelf botsen.
	if( oponentPtr->m_Cluster == m_Cluster ) return; // niet in de zelvde cluster botsen

	DOUBLE2 deltaVect= *m_PosPtr - (*oponentPtr->m_PosPtr);
	double sum= oponentPtr->m_Straal + m_Straal;
	double quadraatDing= deltaVect.x * deltaVect.x + deltaVect.y*deltaVect.y ;

	if( sum*sum > quadraatDing){ // collition //pow(deltaVect.x,2)+ pow(deltaVect.y,2)
		
		double deltaVectLen= sqrt( quadraatDing );
		DOUBLE2 normal= ( deltaVect/deltaVectLen ); //.Normalized();

		double deltaX= m_Pos.x - oponentPtr->GetPos().x;
		DOUBLE2 thisVector1= normal * normal.DotProduct( m_Velocity				); // m_Velocity
		DOUBLE2 othrVector1= normal * normal.DotProduct( oponentPtr->m_Velocity	); // m_Velocity

		// Bart U. zijn manier:
		/*//calculate the normalized vector connecting two positions
		DOUBLE2 vNormal = ( m_Pos - oponentPtr->m_Pos ).Normalized();
		//project the velocity vectors onto the vNormal.

		DOUBLE2 projVelocity1 = vNormal.DotProduct(			   m_Velocity)*vNormal;
		DOUBLE2 projVelocity2 = vNormal.DotProduct(oponentPtr->m_Velocity)*vNormal;
		//if the projected velocities are pointing in the same direction:
		if(projVelocity1.DotProduct(projVelocity2)>0){

			//if the first one is moving faster than the second, don't interfere
			//first one is identified by dot with vNormal
			if(vNormal.DotProduct(projVelocity1)>0){
				if(projVelocity1.Length()>projVelocity2.Length())return;
			}else{
				if(projVelocity1.Length()<projVelocity2.Length())return;
			}

		}else{//they are not moving in the same direction

			if(vNormal.DotProduct(projVelocity1)>0)
				return;

		}//*/


		// Mijn geoptimaliseerde chek:  (c) Emile Sonneveld
		if( ( thisVector1.x -othrVector1.x<=0 && deltaX>=0 ) || ( thisVector1.x -othrVector1.x>0 && deltaX<0 ) ){

			// Switch de velocitys
			DOUBLE2 thisVector2= m_Velocity				- thisVector1;
			DOUBLE2 othrVector2= oponentPtr->m_Velocity	- othrVector1;
			
			DOUBLE2 pusch= normal*  pow(deltaVectLen-sum, 2)/2;
			//					  = Original    + Switched   *bounce + uit elkaar duwen
			m_Velocity            = thisVector2 + othrVector1*0.95   - pusch;
			oponentPtr->m_Velocity= othrVector2 + thisVector1*0.95   + pusch ;

			//m_Pos+= normal*0.2;

		}
	}

}

