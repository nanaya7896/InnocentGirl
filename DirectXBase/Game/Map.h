#pragma once
#include"../Global.h"
#include"../Direct3D/Xfile.h"
#include"../Direct3D/texture.h"

const int MAXBUILDING = 4;

class Map
{
private:




public:

	Texture tfloor1;
	Texture tfloor2;
	Texture tfloor3;
	Texture tfloor4;
	X_FILE xfloor1;
	X_FILE xfloor2;
	X_FILE xfloor3;
	X_FILE xfloor4;
	HRESULT LoadBuldings();
	void MapRender();


protected:




};