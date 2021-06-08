//---------------------------------------------------------------------------

#pragma hdrstop

#include "hole.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
	 void hole::Show(TCanvas* Canvas, TImage* Image)
{
	Image->Canvas->Pen->Color=clBlack;
	Image->Canvas->Brush->Color=clBlack;
	Image->Canvas->Ellipse(x - rad, y - rad, x + rad, y + rad);
	Image->Canvas->Brush->Color=clWhite;
}
