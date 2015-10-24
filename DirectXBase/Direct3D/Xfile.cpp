#include"Xfile.h"

X_FILE::X_FILE()
{


}

X_FILE::~X_FILE()
{


}


//X�t�@�C���ǂݍ���
BOOL X_FILE::XfileLoader(LPDIRECT3DDEVICE9 pD3D9,LPCWSTR name)
{

	D3DXLoadMeshFromX(name, D3DXMESH_SYSTEMMEM, pD3D9,
		NULL, NULL, NULL, NULL, &g_pMesh);
	//����X�t�@�C�����Ȃ����
	if (g_pMesh == NULL)
	{
		//false��Ԃ�
		return false;
	}

	return TRUE;

}

BOOL X_FILE::CleanUp()
{

	if (g_pMesh != NULL)
		g_pMesh->Release();

	return TRUE;

}



BOOL X_FILE::SetupMatrices(LPDIRECT3DDEVICE9 pD3D9, HWND hWnd, DWORD lasttime)
{
	// World Matrix.
	//D3DXMatrixRotationX(&matWorld, timeGetTime() / 1000.5f);
	dInput.Init(hWnd);

	dInput.Update();
	//pD3D9->SetTransform(D3DTS_WORLD, &matWorld);
	// �����f���̔z�u
	//D3DXMatrixIdentity(&matWorld);
	// ���f���̊g��k��
	//D3DXMatrixScaling(&matWorld, 1.0f, 1.0f, 1.0f);
	// ���f���̈ړ�
	//	D3DXMatrixTranslation(&matWorld, 20.0f, 0.1f, 0.0f);
	// ���[���h�}�g���b�N�X��DirectX�ɐݒ�
	//g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
	// ���[���h�}�g���b�N�X��DirectX�ɐݒ�
	//g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
	// Camera.
	//�J�����̈ʒu	
	DWORD curtime = timeGetTime();
	looptime = ((float)lasttime - curtime )/ 1000.0f;

	
	if (dInput.KeyUp(DIK_W)==true)
	{
		PlayerVec.z = speed*looptime;
	}
	if (dInput.KeyUp(DIK_S)==true)
	{
		PlayerVec.z = -speed*looptime;
	}
	if (dInput.KeyUp(DIK_A)==true)
	{
		PlayerAngel.y -= anglesp*looptime;
	}
	if (dInput.KeyUp(DIK_D)==true)
	{
		PlayerAngel.y += anglesp*looptime;
	}
	if (PlayerAngel.y < 0)
	{
		PlayerAngel.y += D3DX_PI * 2;
	}
	if (PlayerAngel.y > 360)
	{
		PlayerAngel.y -= D3DX_PI * 2;
	}
	D3DXVECTOR3 PlayerVec2;

	D3DXMatrixRotationY(&matWorld, PlayerAngel.y);
	D3DXVec3TransformCoord(&PlayerVec2, &PlayerVec, &matView);
	PlayerPos += PlayerVec2;
	//���[���h�ϊ��s��
	D3DXMatrixTranslation(&matWorld, PlayerPos.x, PlayerPos.y, PlayerPos.z);
	matProj = matView*matWorld;
	pD3D9->SetTransform(D3DTS_WORLD, &matProj);
	//vEyePt.x = 0.0f;
	//vEyePt.y = 3.0f;
	//vEyePt.z = 0.0f - 15.0f;//���߂�ς���
	//���イ������
	/*vLookatPt.x = 0.0f;
	vLookatPt.y = 0.0f;
	vLookatPt.z = 0.0f;*/

	vUpVec.x = 0.0f;
	vUpVec.y = 1.0f;
	vUpVec.z = 0.0f;

	D3DXVECTOR3 viewvecE(0.0f, 1.0f, -5.0f), viewvecL(0.0f,2.0f,4.0f);
	D3DXVECTOR3 viewvec;
	//�r���[�ϊ�
	D3DXVec3TransformCoord(&viewvec,&viewvecE,&matView);
	vEyePt.x =PlayerPos.x+viewvec.x ;
	vEyePt.y = PlayerPos.y + viewvec.y;
	vEyePt.z = PlayerPos.z + viewvec.z;
	D3DXVec3TransformCoord(&viewvec, &viewvecL, &matView);
	vLookatPt.x = PlayerPos.x+viewvec.x;
	vLookatPt.y = PlayerPos.y + viewvec.y;
	vLookatPt.z = PlayerPos.z + viewvec.z;

	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	pD3D9->SetTransform(D3DTS_VIEW, &matView);

	//�ˌ`�ϊ�
	D3DXMatrixPerspectiveFovLH(&matProj, 3.0f / 4.0f, 1.0f, 0.5f, 100.0f);
	pD3D9->SetTransform(D3DTS_PROJECTION, &matProj);
	Render();
	lasttime = curtime;
	return TRUE;

}
BOOL X_FILE::NatureLight(LPDIRECT3DDEVICE9 pD3D9)
{
	//�����̐ݒ�
	pD3D9->SetRenderState(D3DRS_AMBIENT,0xffffffff);
	D3DXMatrixTranslation(&matWorld,0.0f,0.0f,1.0f);
	D3DXMatrixRotationY(&matView,D3DX_PI);

	pD3D9->SetTransform(D3DTS_WORLD, &matView);

	return TRUE;

}

BOOL X_FILE::Render()
{
	g_pMesh->DrawSubset(0);

	return true;
}


