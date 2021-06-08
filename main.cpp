//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "ball.h"
#include "position.h"
#include "main.h"
#include "borders.h"
#include "hole.h"
#include <algorithm>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
using namespace std;

int i = 0, count = 0, caught = 0;  float cueX, cueY;
TForm4 *Form4;
vector<balls> vecBall;
vector<border> vecLines;
balls *pSelectedBall = nullptr;
vector<hole>vecHoles;

void addBall(TCanvas* Canvas, TImage* Image,float x1, float y1, float radius1)
{
	int id = vecBall.size();
	balls b(x1, y1, radius1, id);
	vecBall.push_back(b);
	b.Show(Canvas, Image);
}
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm4::FormCreate(TObject *Sender)
{
		float ballrad = 14.0f;

		addBall(Canvas,Image1, 590, 230, ballrad);
		addBall(Canvas,Image1, 623,263, ballrad);
		addBall(Canvas,Image1, 623,197, ballrad);
		addBall(Canvas,Image1, 656,230, ballrad);
		addBall(Canvas,Image1, 656,296, ballrad);
		addBall(Canvas,Image1, 656,164, ballrad);
		addBall(Canvas,Image1, 689,263, ballrad);
		addBall(Canvas,Image1, 689,197, ballrad);
		addBall(Canvas,Image1, 689,326, ballrad);
		addBall(Canvas,Image1, 689,130, ballrad);
		addBall(Canvas,Image1, 722,230, ballrad);
		addBall(Canvas,Image1, 722,296, ballrad);
		addBall(Canvas,Image1, 722,164, ballrad);
		addBall(Canvas,Image1, 722,100, ballrad);
		addBall(Canvas,Image1, 722,360, ballrad);
		addBall(Canvas,Image1, 380,230, ballrad);

		float r = 40.0f;
		float l = 328.0f;
		float w = 14.0f;
		float hx1 = 40.0f;
		float hx2 = hx1 + 2*r + l;
		float hx3 = hx2 + 2*r + l;
		float hy1 = 40.0f;
		float hy2 = hy1 + 2*r+ l;

		vecLines.push_back({ hx1 + r, hy1, hx2- r, hy1, w });
		vecLines.push_back({ hx2 + r , hy1, hx3-r, hy1, w });
		vecLines.push_back({hx3 , hy1 +r, hx3, hy2-r, w});
		vecLines.push_back({ hx2 + r , hx2, hx3 - r , hx2, w});
		vecLines.push_back({ hx1+r, hx2, hx2-r, hx2, w });
		vecLines.push_back({ hx1, hy1+r, hx1, hy2-r, w});

		vecHoles.push_back({ hx1, hy1, r});
		vecHoles.push_back({ hx2, hy1, r });
		vecHoles.push_back({ hx3, hy1, r });
		vecHoles.push_back({ hx1, hy2, r});
		vecHoles.push_back({ hx2, hy2, r});
		vecHoles.push_back({ hx3, hy2, r });

		for(auto border:vecLines)
			border.Show(Canvas,Image1);

		for(auto hole:vecHoles)
			hole.Show(Canvas,Image1);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Image1MouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	if(Shift.Contains(ssLeft))
	{
			if (pSelectedBall != nullptr)
			{
				 pSelectedBall->Hide(Canvas,Image1);

				 Image1->Canvas->FillRect(Image1->Canvas->ClipRect);

				 cueX = pSelectedBall->getX();
				 cueY = pSelectedBall->getY();
				 Image1->Canvas->MoveTo(cueX, cueY);

				 Image1->Canvas->Pen->Color=clBlue;
				 Image1->Canvas->LineTo(X,Y);

				//pSelectedBall->Show(Canvas,Image1);

				for(auto border:vecLines)
					border.Show(Canvas,Image1);
				for(auto ball: vecBall)
					ball.Show(Canvas,Image1);
				for(auto ball: vecHoles)
					ball.Show(Canvas,Image1);
			 }
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
			pSelectedBall = nullptr;
			for (balls &b : vecBall)
			{
				if (IsPointInCircle(b.getX(), b.getY(), b.getRad(),X, Y))
				{
					pSelectedBall = &b;
					break;
				}
			}
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	Image1->Canvas->MoveTo(cueX, cueY);
	Image1->Canvas->Pen->Color=clWhite;
	Image1->Canvas->LineTo(X,Y);

	if(pSelectedBall)
	{
		pSelectedBall->setVx(5.0f * ((pSelectedBall->getX()) - (float)X));
		pSelectedBall->setVy(5.0f * ((pSelectedBall->getX()) - (float)Y));
		Timer1->Enabled=true;
	}
	pSelectedBall = nullptr;
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Timer1Timer(TObject *Sender)
{
		i++;int count = 0;
		vector<pair<balls*, balls*>> vecCollidingPairs;
		vector<balls*> vecFakeBalls;

		for(auto &ball : vecBall)
			ball.Hide(Canvas,Image1);

		for (auto &ball : vecBall)
		{
			ball.setAx(-ball.getVx() * 0.8f);
			ball.setAy(-ball.getVy()* 0.8f);

			ball.setVx(ball.getVx()+ ball.getAx() * i * Timer1->Interval/1000) ;
			ball.setVy(ball.getVy() + ball.getAy() * i * Timer1->Interval/1000);
			ball.setX(ball.getX()+ ball.getVx() * i * Timer1->Interval/1000) ;
			ball.setY(ball.getY() + ball.getVy() * i * Timer1->Interval/1000);

			if (ball.getX() < 0) ball.setX(ball.getX() + (float)Image1->Width);
			if (ball.getX() >= Image1->Width) ball.setX(ball.getX() - (float)Image1->Width);
			if (ball.getY() < 0) ball.setY(ball.getY() + (float)Image1->Height);
			if (ball.getY() >= Image1->Height) ball.setY(ball.getY() - (float)Image1->Height);

			if (ball.getVx()*ball.getVx()+ ball.getVy()*ball.getVy() < 0.01f)
			{
				count ++;
				if(count == vecBall.size())
				{
					Timer1->Enabled=false;
					i = 0;
				}
				ball.setVx(0);
				ball.setVy(0);
			}

		}

		for (auto &ball : vecBall)
		{
			// Against borders
			for (auto &border : vecLines)
			{
				float fLineX1 = border.getex() - border.getbx();
				float fLineY1 = border.getey() - border.getby();

				float fLineX2 = ball.getX() - border.getbx();
				float fLineY2 = ball.getY() - border.getby();

				float fEdgeLength = fLineX1 * fLineX1 + fLineY1 * fLineY1;

				float t = max(0.0f, min(fEdgeLength, (fLineX1 * fLineX2 + fLineY1 * fLineY2))) / fEdgeLength;

				float fClosestPointX = border.getbx() + t * fLineX1;
				float fClosestPointY = border.getby() + t * fLineY1;

				float fDistance = sqrtf((ball.getX() - fClosestPointX)*(ball.getX() - fClosestPointX) + (ball.getY() - fClosestPointY)*(ball.getY() - fClosestPointY));


				if (fDistance <= (ball.getRad() + border.getwidth()) )
				{
					balls *fakeball = new balls();
					fakeball->setRad( border.getwidth());
					fakeball->setMass(ball.getMass() * 0.8f);
					fakeball->setX(fClosestPointX);
					fakeball->setY(fClosestPointY);
					fakeball->setVx(-ball.getVx());
					fakeball->setVy(-ball.getVy());

					vecFakeBalls.push_back(fakeball);

					vecCollidingPairs.push_back({ &ball, fakeball });

					float fOverlap = 1.0f * (fDistance - ball.getRad() - fakeball->getRad());

					ball.setX( ball.getX() - (fOverlap * (ball.getX() - fakeball->getX()) / fDistance));
					ball.setY(ball.getY()- (fOverlap * (ball.getY() - fakeball->getY()) / fDistance));
				}
			}
		}

		for (auto &ball : vecBall)
		{
			for (auto &target : vecBall)
			{
				if (ball.getid() != target.getid())
				{
					if (DoCirclesOverlap(ball.getX(), ball.getY(), ball.getRad(), target.getX(), target.getY(), target.getRad())   )
					{
						vecCollidingPairs.push_back({ &ball, &target });

						float fDistance = sqrt((ball.getX() - target.getX())*(ball.getX() - target.getX()) + (ball.getY() - target.getY())*(ball.getY() - target.getY()));

						float fOverlap = 0.5f * (fDistance - ball.getRad() - target.getRad());

						ball.setX(ball.getX() - fOverlap * (ball.getX() - target.getX()) / fDistance);
						ball.setY(ball.getY() - fOverlap * (ball.getY() - target.getY()) / fDistance);

						target.setX(target.getX() + fOverlap * (ball.getX() - target.getX() )/ fDistance);
						target.setY(target.getY() + fOverlap * (ball.getY() - target.getY() )/ fDistance);
					}
				}
			}
		}
		for(auto &ball : vecBall)
		{
			for(auto hole:vecHoles)
			{
				if(Caught(ball.getX(), ball.getY(), ball.getRad(), hole.getX(), hole.getY(), hole.getRad()))
				{
					ball.Hide(Canvas,Image1);
					caught++;
					ball.setVx(0.0f); ball.setAx(0.0f);
					ball.setVy(0.0f); ball.setAy(0.0f);
					ball.Move(Canvas,Image1,980.0f, 25.0f+ball.getRad()* 2 *(float)caught + (float)caught);
				}
				hole.Show(Canvas,Image1);
				for(auto border:vecLines)
					border.Show(Canvas, Image1);
			}
		}

		// Now work out dynamic collisions
		for (auto c : vecCollidingPairs)
		{
			balls *b1 = c.first;
			balls *b2 = c.second;

			// Distance between balls
			float fDistance = sqrtf((b1->getX() - b2->getX())*(b1->getX() - b2->getX()) + (b1->getY() - b2->getY())*(b1->getY() - b2->getY()));

			// Normal
			float nx = (b2->getX() - b1->getX()) / fDistance;
			float ny = (b2->getY() - b1->getY()) / fDistance;

			// Tangent
			float tx = -ny;
			float ty = nx;

			// Dot Product Tangent
			float dpTan1 = b1->getVx() * tx + b1->getVy()* ty;
			float dpTan2 = b2->getVx() * tx + b2->getVy() * ty;

			// Dot Product Normal
			float dpNorm1 = b1->getVx() * nx + b1->getVy() * ny;
			float dpNorm2 = b2->getVx() * nx + b2->getVy() * ny;

			// Conservation of momentum
			float m1 = (dpNorm1 * (b1->getMass() - b2->getMass()) + 2.0f * b2->getMass() * dpNorm2) / (b1->getMass() + b2->getMass());
			float m2 = (dpNorm2 * (b2->getMass() - b1->getMass()) + 2.0f * b1->getMass() * dpNorm1) / (b1->getMass() + b2->getMass());

			b1->setVx( tx * dpTan1 + nx * m1);
			b1->setVy( ty * dpTan1 + ny * m1);
			b2->setVx(tx * dpTan2 + nx * m2);
			b2->setVy(ty * dpTan2 + ny * m2);
		}

			vecCollidingPairs.clear();

			for (auto &b : vecFakeBalls)
				delete b;
			vecFakeBalls.clear();

			for(auto &ball : vecBall)
				ball.Show(Canvas,Image1);

}
//---------------------------------------------------------------------------

