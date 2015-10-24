#include"Xfile.h"

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



BOOL X_FILE::SetupMatrices(LPDIRECT3DDEVICE9 pD3D9)
{



	// World Matrix.
	//D3DXMatrixRotationX(&matWorld, timeGetTime() / 1000.5f);
	D3DXMatrixRotationY(&matWorld, 100.5f);
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
	vEyePt.z = 0.0f - 5.0f;//遠近を変える
	//ちゅうしせん
	vLookatPt.x = 0.0f;
	vLookatPt.y = 0.0f;
	vLookatPt.z = 0.0f;

	vUpVec.x = 0.0f;
	vUpVec.y = 1.0f;
	vUpVec.z = 0.0f;
	//ビュー変換
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	pD3D9->SetTransform(D3DTS_VIEW, &matView);

	//射形変換
	D3DXMatrixPerspectiveFovLH(&matProj, 3.0f / 4.0f, 1.0f, 0.5f, 100.0f);
	pD3D9->SetTransform(D3DTS_PROJECTION, &matProj);
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

