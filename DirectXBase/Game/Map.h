#pragma once
#include"../Global.h"
#include"../Direct3D/Xfile.h"
#include"../Direct3D/texture.h"

struct Building
{
	BOOL xname;
	BOOL texturename;
};

const int MAXBUILDING = 25;

class Map
{
private:
	//Textureのインスタンス生成
	Texture tfloor1;
	Texture tfloor2;
	Texture tfloor3;
	Texture tfloor4;
	Texture troof1;
	Texture troof2;
	Texture troof3;
	Texture troof4;
	Texture tpanel1;
	Texture tpanel2;
	Texture tpanel3;
	Texture tpanel4;
	Texture tball;
	Texture tleaf;
	Texture ttree;
	Texture thouse;

	//Xfileのインスタンス生成
	X_FILE xfloor1;
	X_FILE xfloor2;
	X_FILE xfloor3;
	X_FILE xfloor4;
	X_FILE xroof1;
	X_FILE xroof2;
	X_FILE xroof3;
	X_FILE xroof4;
	X_FILE xpaneln1;
	X_FILE xpaneln2;
	X_FILE xpanels1;
	X_FILE xpanels2;
	X_FILE xpanelw1;
	X_FILE xpanelw2;
	X_FILE xpanele1;
	X_FILE xpanele2;
	X_FILE xhouse;
	X_FILE xball;
	X_FILE xtree;
	X_FILE xleaf;

public:
	//コンストラクタ
	Map();
	//デストラクタ
	~Map();
	
	HRESULT LoadBuldings();
	void MapRender();


protected:




};