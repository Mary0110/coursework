//---------------------------------------------------------------------------
#ifndef ballH
#define ballH
//---------------------------------------------------------------------------

#include <vcl.h>
#include <vector>
using namespace std;


class balls{
	private:
	float x,y;
	float vx, vy;
	float ax, ay;
	float rad;
	float mass = 10.0f;

	int id;

	public:
	balls(float x1 = 0, float y1 = 0, float radius1=14.0f, int id1 = 0)
	{
		x = x1;
		y = y1;
		vx = 0; vy = 0; ax = 0; ay = 0;
		rad = radius1;
		id = id1;
	}

	float getMass();
	void setMass(float m);
	float getid();
	float getX();
	float getY();
	float getVx();
	float getVy();
	float getAx();
	float getAy();
	float getRad();
	void setX(float xn);
	void setY(float xn);
	void setVx(float xn);
	void setVy(float xn);
	void setAx(float xn);
	void setAy(float xn);
	void setRad(float rn);
	void setId(float rn);
	void Show(TCanvas *Canvas, TImage* Image);
	void Hide(TCanvas *Canvas, TImage* Image);
	void Move(TCanvas *Canvas, TImage* Image, float xn, float yn);
	~balls(){} ;
};


#endif

