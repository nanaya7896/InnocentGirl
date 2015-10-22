#pragma once

class Vector2
{
	int x;
	int y;

public:

	Vector2()
	{
		x = y = 0;
	}

	void Set(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	int X()const{ return x; }
	int Y()const{ return y; }


	//�ȉ����Z�q�̃I�[�o�[���[�h
	const Vector2 operator +(const Vector2& other)const
	{
		Vector2 temp;
		temp.Set(x + other.X(), y + other.Y());
		return temp;
	}

	const Vector2 operator -(const Vector2& other)const
	{
		Vector2 temp;
		temp.Set(x - other.X(), y - other.Y());
		return temp;
	}

	const Vector2& operator += (const Vector2& other)
	{
		x += other.X();
		y += other.Y();

		return *(this);
	}

	const Vector2& operator -= (const Vector2& other)
	{
		x -= other.X();
		y -= other.Y();

		return *(this);
	}
};
