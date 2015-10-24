#include"Xfile.h"

X_FILE::X_FILE()
{


}

X_FILE::~X_FILE()
{


}


//Xファイル読み込み
BOOL X_FILE::XfileLoader(LPDIRECT3DDEVICE9 pD3D9,LPCWSTR name)
{

	D3DXLoadMeshFromX(name, D3DXMESH_SYSTEMMEM, pD3D9,
		NULL, NULL, NULL, NULL, &g_pMesh);
	//もしXファイルがなければ
	if (g_pMesh == NULL)
	{
		//falseを返す
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
	// ◆モデルの配置
	//D3DXMatrixIdentity(&matWorld);
	// モデルの拡大縮小
	//D3DXMatrixScaling(&matWorld, 1.0f, 1.0f, 1.0f);
	// モデルの移動
	//	D3DXMatrixTranslation(&matWorld, 20.0f, 0.1f, 0.0f);
	// ワールドマトリックスをDirectXに設定
	//g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
	// ワールドマトリックスをDirectXに設定
	//g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
	// Camera.
	//カメラの位置	
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
	//ワールド変換行列
	D3DXMatrixTranslation(&matWorld, PlayerPos.x, PlayerPos.y, PlayerPos.z);
	matProj = matView*matWorld;
	pD3D9->SetTransform(D3DTS_WORLD, &matProj);
	//vEyePt.x = 0.0f;
	//vEyePt.y = 3.0f;
	//vEyePt.z = 0.0f - 15.0f;//遠近を変える
	//ちゅうしせん
	/*vLookatPt.x = 0.0f;
	vLookatPt.y = 0.0f;
	vLookatPt.z = 0.0f;*/

	vUpVec.x = 0.0f;
	vUpVec.y = 1.0f;
	vUpVec.z = 0.0f;

	D3DXVECTOR3 viewvecE(0.0f, 1.0f, -5.0f), viewvecL(0.0f,2.0f,4.0f);
	D3DXVECTOR3 viewvec;
	//ビュー変換
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

	//射形変換
	D3DXMatrixPerspectiveFovLH(&matProj, 3.0f / 4.0f, 1.0f, 0.5f, 100.0f);
	pD3D9->SetTransform(D3DTS_PROJECTION, &matProj);
	Render();
	lasttime = curtime;
	return TRUE;

}
BOOL X_FILE::NatureLight(LPDIRECT3DDEVICE9 pD3D9)
{
	//環境光の設定
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


