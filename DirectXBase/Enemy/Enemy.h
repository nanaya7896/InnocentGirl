#pragma once
#include"../Global.h"
#include"../Direct3D/direct3d.h"
#include"../Direct3D/Xfile.h"
#include"../Direct3D/texture.h"

class Enemy : public Direct3D
{
private:


public:
	//�R���X�g���N�^
	Enemy();
	//���z���f�X�g���N�^
	virtual ~Enemy();

	void Update();

	void Draw();

	void Load();

protected:





};