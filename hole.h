//---------------------------------------------------------------------------

#ifndef holeH
#define holeH
using namespace std;


class hole{
	private:
		float x,y;
		float rad;

	int id;

	public:
	hole(float x1=0, float y1=0,  float radius1=16.0f)
	{
		x = x1;
		y = y1;
		rad = radius1;
	}
	float getX()
	{
	return x;
    }
	float getY()
	{
		return y;
	}
	float getRad()
	{
		return rad;
	}
	void setX(float xn)
	{
		x = xn;
	}
	void setY(float xn)
	{
		y = xn;
	}
	void setRad(float rn)
	{
		rad = rn;
	}
	void Show(TCanvas *Canvas, TImage* Image);
	~hole(){} ;
};

//---------------------------------------------------------------------------
#endif
