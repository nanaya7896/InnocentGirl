#include"Xfile.h"


BOOL X_FILE::XfileLoader(LPDIRECT3DDEVICE9 pD3D9,LPCWSTR name)
{

	D3DXLoadMeshFromX(name, D3DXMESH_SYSTEMMEM, pD3D9,
		NULL, NULL, NULL, NULL, &g_pMesh);
	return TRUE;

}



BOOL X_FILE::SetupMatrices(LPDIRECT3DDEVICE9 pD3D9)
{

	D3DXMATRIXA16 matWorld, matView, matProj;
	D3DXVECTOR3 vEyePt, vLookatPt, vUpVec;

	// World Matrix.
	D3DXMatrixRotationY(&matWorld, 100.5f);//timeGetTime() /
	pD3D9->SetTransform(D3DTS_WORLD, &matWorld);
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
	vEyePt.x = 0.0f;
	vEyePt.y = 3.0f;
	vEyePt.z = 0.0f - 50.0f;//遠近を変える
	//ちゅうしせん
	vLookatPt.x = 0.0f;
	vLookatPt.y = 0.0f;
	vLookatPt.z = 0.0f;

	vUpVec.x = 0.0f;
	vUpVec.y = 1.0f;
	vUpVec.z = 0.0f;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	pD3D9->SetTransform(D3DTS_VIEW, &matView);

	// Projection Matrix.
	D3DXMatrixPerspectiveFovLH(&matProj, 3.0f / 4.0f, 1.0f, 0.5f, 100.0f);
	pD3D9->SetTransform(D3DTS_PROJECTION, &matProj);
	return TRUE;

}

BOOL X_FILE::Render()
{
	g_pMesh->DrawSubset(0);

	return true;
}