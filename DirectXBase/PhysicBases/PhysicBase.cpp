#include"PhysicBase.h"

PhysicBase::PhysicBase(float unitTime) : t_(unitTime)
{
	memset(&pos_, 0, sizeof(D3DXVECTOR3));
	memset(&vel_, 0, sizeof(D3DXVECTOR3));
	memset(&acc_, 0, sizeof(D3DXVECTOR3));
}

PhysicBase::~PhysicBase() 
{

}

//! �ʒu�⑬�x���X�V
void PhysicBase::update(float dt, bool isResetAccel)
{
	// �ʒu���Z�o
	getPos(pos_, dt);

	// �����x���瑬�x���Z�o
	vel_ += acc_ * dt;

	// �����x�����Z�b�g
	if (isResetAccel)
		acc_.x = acc_.y = acc_.z = 0.0f;
}

//! �ʒu��ݒ�
void PhysicBase::setPos(D3DXVECTOR3 &pos)
{
	pos_ = pos;
}

//! ���x��ݒ�
void PhysicBase::setVelocity(D3DXVECTOR3 &vel) 
{
	vel_ = vel;
}

//! �����x��ݒ�
void PhysicBase::setAccel(D3DXVECTOR3 &acc)
{
	// ���x�X�V
	acc_ = acc;
}

//! �ʒu�����Z
D3DXVECTOR3& PhysicBase::addPos(D3DXVECTOR3& out, D3DXVECTOR3 &pos)
{
	pos_ += pos;
	out = pos_;
	return out;
}

//! ���x�����Z
D3DXVECTOR3& PhysicBase::addVelocity(D3DXVECTOR3& out, D3DXVECTOR3 &vel)
{
	vel_ += vel;
	out = vel_;
	return out;
}

//! �����x�����Z
D3DXVECTOR3& PhysicBase::addAccel(D3DXVECTOR3& out, D3DXVECTOR3 &acc)
{
	acc_ += acc;
	out = acc_;
	return out;
}

//! �w�莞���ł̈ʒu���擾
D3DXVECTOR3& PhysicBase::getPos(D3DXVECTOR3& out, float dt)
{
	D3DXVECTOR3 next = vel_ * t_ + 0.5f * acc_ * t_ * t_;
	out = pos_ + dt / t_ * next;
	return out;
}

//! �w�莞���ł̑��x���擾
D3DXVECTOR3& PhysicBase::getVelocity(D3DXVECTOR3& out, float dt)
{
	D3DXVECTOR3 next = acc_ * t_;
	out = vel_ + dt / t_ * next;
	return out;
}

//! ���݂̈ʒu���擾
D3DXVECTOR3& PhysicBase::getCurPos()
{
	return pos_;
}

//! ���݂̑��x���擾
D3DXVECTOR3& PhysicBase::getCurVelocity()
{
	return vel_;
}

//! ���ݐݒ肳��Ă�������x���擾
D3DXVECTOR3& PhysicBase::getCurAccel() 
{
	return acc_;
}