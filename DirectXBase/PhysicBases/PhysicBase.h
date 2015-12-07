#pragma once
#include"../Global.h"


//物理的に位置を動かすクラス
class PhysicBase
{
public:
	PhysicBase(float unitTime = 1 / 60.f);
	~PhysicBase();

	//! 更新
	virtual void update(float dt, bool isResetAccel = true);

	//! 位置を設定
	virtual void setPos(D3DXVECTOR3 &pos);

	//! 速度を設定
	virtual void setVelocity(D3DXVECTOR3 &vel);

	//! 加速度を設定
	virtual void setAccel(D3DXVECTOR3 &acc);

	//! 位置を加算
	D3DXVECTOR3& addPos(D3DXVECTOR3& out, D3DXVECTOR3 &pos);

	//! 速度を加算
	D3DXVECTOR3& addVelocity(D3DXVECTOR3& out, D3DXVECTOR3 &vel);

	//! 加速度を加算
	D3DXVECTOR3& addAccel(D3DXVECTOR3& out, D3DXVECTOR3 &acc);

	//! 指定時刻での位置を取得
	virtual D3DXVECTOR3& getPos(D3DXVECTOR3& out, float dt);

	//! 指定時刻での速度を取得
	virtual D3DXVECTOR3& getVelocity(D3DXVECTOR3& out, float dt);

	//! 現在の位置を取得
	D3DXVECTOR3& getCurPos();

	//! 現在の速度を取得
	D3DXVECTOR3& getCurVelocity();

	//! 現在設定されている加速度を取得
	D3DXVECTOR3& getCurAccel();

protected:
	float		t_;		//!< 差分時間
	D3DXVECTOR3 pos_;	//!< 位置
	D3DXVECTOR3 vel_;	//!< 速度
	D3DXVECTOR3 acc_;	//!< 加速度













};