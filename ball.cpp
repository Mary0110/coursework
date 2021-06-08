//---------------------------------------------------------------------------

#pragma hdrstop

#include "ball.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

void balls::Show(TCanvas* Canvas, TImage* Image)
{
	Image->Canvas->Pen->Color=clGreen;
	Image->Canvas->Brush->Color=clRed;
	Image->Canvas->Ellipse(x - rad, y - rad, x + rad, y + rad);
    Image->Canvas->Brush->Color=clWhite;
}
void balls::Hide(TCanvas *Canvas, TImage* Image)
{
  Image->Canvas->Pen->Color=clWhite;
  Image->Canvas->Ellipse(x - rad, y - rad, x + rad, y + rad);
  Image->Canvas->Pen->Color=clBlue;
}
void balls::Move(TCanvas *Canvas,TImage* Image, float xn, float yn)
{
  Hide(Canvas, Image);
  x = xn;
  y = yn;
  Show(Canvas, Image);
}
 float balls::getX()
{
	return x;
}
float balls::getMass()
{
	return mass;
}
void balls::setMass(float m)
{
	mass = m;
}
float balls::getid()
{
	return id;
}
float balls::getY()
{
	return y;
}
float balls::getVx()
{
  return vx;
}
float balls::getVy()
{
	return vy;
}
float balls::getAx()
{
	return ax;
}
float balls::getAy()
{
	return ay;
}
float balls::getRad()
{
	return rad;
}
void balls::setX(float xn)
{
	x = xn;
}
void balls::setY(float xn)
{
	y = xn;
}
void balls::setVx(float xn)
{
  vx = xn;
}
void balls::setVy(float xn)
{
	vy = xn;
}
void balls::setAx(float xn)
{
	ax =xn;
}
void balls::setAy(float xn)
{
	ay = xn;
}
void balls::setRad(float rn)
{
	rad = rn;
}
void balls::setId(float rn)
{
	id = rn;
}
