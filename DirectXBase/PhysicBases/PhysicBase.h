#pragma once
#include"../Global.h"


//�����I�Ɉʒu�𓮂����N���X
class PhysicBase
{
public:
	PhysicBase(float unitTime = 1 / 60.f);
	~PhysicBase();

	//! �X�V
	virtual void update(float dt, bool isResetAccel = true);

	//! �ʒu��ݒ�
	virtual void setPos(D3DXVECTOR3 &pos);

	//! ���x��ݒ�
	virtual void setVelocity(D3DXVECTOR3 &vel);

	//! �����x��ݒ�
	virtual void setAccel(D3DXVECTOR3 &acc);

	//! �ʒu�����Z
	D3DXVECTOR3& addPos(D3DXVECTOR3& out, D3DXVECTOR3 &pos);

	//! ���x�����Z
	D3DXVECTOR3& addVelocity(D3DXVECTOR3& out, D3DXVECTOR3 &vel);

	//! �����x�����Z
	D3DXVECTOR3& addAccel(D3DXVECTOR3& out, D3DXVECTOR3 &acc);

	//! �w�莞���ł̈ʒu���擾
	virtual D3DXVECTOR3& getPos(D3DXVECTOR3& out, float dt);

	//! �w�莞���ł̑��x���擾
	virtual D3DXVECTOR3& getVelocity(D3DXVECTOR3& out, float dt);

	//! ���݂̈ʒu���擾
	D3DXVECTOR3& getCurPos();

	//! ���݂̑��x���擾
	D3DXVECTOR3& getCurVelocity();

	//! ���ݐݒ肳��Ă�������x���擾
	D3DXVECTOR3& getCurAccel();

protected:
	float		t_;		//!< ��������
	D3DXVECTOR3 pos_;	//!< �ʒu
	D3DXVECTOR3 vel_;	//!< ���x
	D3DXVECTOR3 acc_;	//!< �����x













};