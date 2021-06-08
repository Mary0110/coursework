//---------------------------------------------------------------------------

#ifndef bordersH
#define bordersH
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

#include <vcl.h>
#include <vector>
using namespace std;


class border
{
	private:
		float bx,by;
		float ex, ey;
		int width;

	public:
	border(float bx1, float by1,  float ex1, float ey1, float id1)
	{
		bx = bx1;
		by = by1;
		ex = ex1;
		ey = ey1;

		width = id1;
	}

	float getwidth();
	float getbx();
	float getby();
	float getex();
	float getey();
	void setbx(float xn);
	void setby(float xn);
	void setex(float xn);
	void setey(float xn);
	void Show(TCanvas *Canvas, TImage* Image);
	~border(){} ;
};

#endif

