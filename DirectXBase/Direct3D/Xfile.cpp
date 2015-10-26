#include"Xfile.h"

X_FILE::X_FILE()
{

}

X_FILE::X_FILE(LPCWSTR FileName)
{
	XfileLoader(FileName);
}

X_FILE::~X_FILE()
{
	if (g_pMesh != NULL)
	{
		g_pMesh->Release();
	}
	
	pD3DXMatrlBuffer->Release();
}


//Xファイル読み込み
BOOL X_FILE::XfileLoader(LPCWSTR name)
{

	D3DXLoadMeshFromX(name, D3DXMESH_SYSTEMMEM,pDevice3D,
		NULL, &pD3DXMatrlBuffer, NULL, &MaterialNum, &g_pMesh);
	//もしXファイルがなければ
	if (g_pMesh == NULL)
	{
		MessageBox(NULL,_T("メッシュがないよ！"),_T("Mesh.exe"),MB_OK);
		//falseを返す
		return FALSE;
	}
	
	return TRUE;

}
void X_FILE::CleanUp()
{
	

}

BOOL X_FILE::SetupMatrices(LPDIRECT3DDEVICE9 pD3D9,DWORD lasttime)
{
	
	dInput.Init();
	
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

	return TRUE;

}

void X_FILE::Render(D3DXVECTOR3 *pos, D3DXVECTOR3 *rota, D3DXVECTOR3 *scale, LPDIRECT3DTEXTURE9 pTex9)
{
	D3DXMATRIX *m_World = new D3DXMATRIX();
	D3DXMATRIX *m_temp=new D3DXMATRIX();
	
	D3DXMatrixIdentity(m_World);
	D3DXMatrixIdentity(m_temp);
	
	//拡大の処理
	D3DXMatrixScaling(m_temp, scale->x, scale->y, scale->z);
	*m_World *= *m_temp;
	//モデルの座標変換(ヨー、ピッチ、ロールを指定して行列を作成)
	D3DXMatrixRotationYawPitchRoll(m_temp, rota->y, rota->x, rota->z);
	*m_World *= *m_temp;
	//モデル移動の処理
	D3DXMatrixTranslation(m_temp, pos->x, pos->y, pos->z);
	*m_World *= *m_temp;

	pDevice3D->SetTransform(D3DTS_WORLD,m_World);

	

	D3DXMATERIAL *d3dxMaterials = (D3DXMATERIAL *)pD3DXMatrlBuffer->GetBufferPointer();
	pDevice3D->SetTexture(0, pTex9);
		for (DWORD i = 0; i < MaterialNum; i++)
	{
		pDevice3D->SetMaterial(&d3dxMaterials[i].MatD3D);
		
		g_pMesh->DrawSubset(i);
	}
	
		
	delete m_temp;
	delete m_World;

	}