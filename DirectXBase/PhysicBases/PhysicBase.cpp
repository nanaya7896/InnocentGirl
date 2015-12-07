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

//! 位置や速度を更新
void PhysicBase::update(float dt, bool isResetAccel)
{
	// 位置を算出
	getPos(pos_, dt);

	// 加速度から速度を算出
	vel_ += acc_ * dt;

	// 加速度をリセット
	if (isResetAccel)
		acc_.x = acc_.y = acc_.z = 0.0f;
}

//! 位置を設定
void PhysicBase::setPos(D3DXVECTOR3 &pos)
{
	pos_ = pos;
}

//! 速度を設定
void PhysicBase::setVelocity(D3DXVECTOR3 &vel) 
{
	vel_ = vel;
}

//! 加速度を設定
void PhysicBase::setAccel(D3DXVECTOR3 &acc)
{
	// 速度更新
	acc_ = acc;
}

//! 位置を加算
D3DXVECTOR3& PhysicBase::addPos(D3DXVECTOR3& out, D3DXVECTOR3 &pos)
{
	pos_ += pos;
	out = pos_;
	return out;
}

//! 速度を加算
D3DXVECTOR3& PhysicBase::addVelocity(D3DXVECTOR3& out, D3DXVECTOR3 &vel)
{
	vel_ += vel;
	out = vel_;
	return out;
}

//! 加速度を加算
D3DXVECTOR3& PhysicBase::addAccel(D3DXVECTOR3& out, D3DXVECTOR3 &acc)
{
	acc_ += acc;
	out = acc_;
	return out;
}

//! 指定時刻での位置を取得
D3DXVECTOR3& PhysicBase::getPos(D3DXVECTOR3& out, float dt)
{
	D3DXVECTOR3 next = vel_ * t_ + 0.5f * acc_ * t_ * t_;
	out = pos_ + dt / t_ * next;
	return out;
}

//! 指定時刻での速度を取得
D3DXVECTOR3& PhysicBase::getVelocity(D3DXVECTOR3& out, float dt)
{
	D3DXVECTOR3 next = acc_ * t_;
	out = vel_ + dt / t_ * next;
	return out;
}

//! 現在の位置を取得
D3DXVECTOR3& PhysicBase::getCurPos()
{
	return pos_;
}

//! 現在の速度を取得
D3DXVECTOR3& PhysicBase::getCurVelocity()
{
	return vel_;
}

//! 現在設定されている加速度を取得
D3DXVECTOR3& PhysicBase::getCurAccel() 
{
	return acc_;
}