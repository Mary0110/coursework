//---------------------------------------------------------------------------

#pragma hdrstop

#include "borders.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
   void border::Show(TCanvas* Canvas, TImage* Image)
{
	Image->Canvas->Pen->Color=clBlack;
	Image->Canvas->Brush->Color=clCream;

	if(by==ey)
		Image->Canvas->Rectangle(bx, by - width, ex, ey + width);
	else
		Image->Canvas->Rectangle(bx -width , by, ex+width, ey);
	Image->Canvas->Brush->Color=clWhite;
}

float border::getwidth()
{
	return width;
}
float border::getbx()
{
return bx;
}
float border::getby()
{
	return by;
}
float border::getex()
{
  return ex;
}
float border::getey()
{
	return ey;
}
void border::setbx(float xn)
{
	bx = xn;
}
void border::setby(float xn)
{
	by = xn;
}
void border::setex(float xn)
{
  ex = xn;
}
void border::setey(float xn)
{
	ey = xn;
}

