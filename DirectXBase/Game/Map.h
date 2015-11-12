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
	//Texture�̃C���X�^���X����
	Texture tfloor[8];
	Texture tfloorGround[11];
	Texture tpanelSky[4];
	Texture tpanelSun;
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

	//Xfile�̃C���X�^���X����
	X_FILE xfloor;
	X_FILE xpanelSky;
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
	//�R���X�g���N�^
	Map();
	//�f�X�g���N�^
	~Map();
	
	HRESULT LoadBuldings();
	void MapRender();


protected:




};