#pragma once
#include"../Global.h"


class AnimationController
{
public:
	LRESULT save(const char *filename, ID3DXAnimationController *ctrl);
	int load(const char *filename, const D3DXFRAME *rootFrame, ID3DXAnimationController **ctrl);

private:



};