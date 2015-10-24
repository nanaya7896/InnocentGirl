#include"Xfile.h"

X_FILE::X_FILE()
{
	

}

X_FILE::~X_FILE()
{
	if (g_pMesh != NULL)
		g_pMesh->Release();

}


//Xファイル読み込み
BOOL X_FILE::XfileLoader(LPDIRECT3DDEVICE9 pD3D9,LPCWSTR name)
{

	D3DXLoadMeshFromX(name, D3DXMESH_SYSTEMMEM, pD3D9,
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
	if (g_pMaterial != NULL)
	{
		delete[] g_pMaterial;
	}

	if (g_pTexture)
	{
		for (DWORD i = 0; i < MaterialNum; i++)
		{
			if (g_pTexture[i])
			{
				g_pTexture[i]->Release();
			}

		}
		delete[] g_pTexture;
	}

}

BOOL X_FILE::MaterialRead(LPDIRECT3DDEVICE9 pD3D9)
{
	
	d3dxMaterials = (D3DXMATERIAL*)pD3DXMatrlBuffer->GetBufferPointer();
	g_pMaterial = new D3DMATERIAL9[MaterialNum];
	if (g_pMaterial == NULL)
	{
		return E_OUTOFMEMORY;
	}
	g_pTexture = new LPDIRECT3DTEXTURE9[MaterialNum];
	if (g_pTexture == NULL)
	{
		return E_OUTOFMEMORY;
	}

	for (DWORD i = 0; i < MaterialNum; i++)
	{

		//Copy the Material
		g_pMaterial[i] = d3dxMaterials[i].MatD3D;
		//Set the ambient color for the material
		g_pMaterial[i].Ambient = g_pMaterial[i].Diffuse;

		g_pTexture[i] = NULL;
		if(d3dxMaterials[i].pTextureFilename !=NULL && lstrlen((LPCWSTR)d3dxMaterials[i].pTextureFilename))
		{
		//Create The Texture
			if (FAILED(D3DXCreateTextureFromFileA(pD3D9, d3dxMaterials[i].pTextureFilename, &g_pTexture[i])))
			{
				
					const TCHAR* strPrefix = TEXT("..\\");
						TCHAR strTexture[MAX_PATH];
						StringCchCopy(strTexture,MAX_PATH,strPrefix);
						StringCchCat(strTexture,MAX_PATH,(STRSAFE_LPCWSTR)d3dxMaterials[i].pTextureFilename);

				if (FAILED(D3DXCreateTextureFromFile(pD3D9, strTexture, &g_pTexture[i])))
				{
					MessageBox(NULL, _T("テクスチャマップはないよ！"), _T("Meshes.exe"), MB_OK);
				}
			}
		}
	}

	pD3DXMatrlBuffer->Release();

	return TRUE;
}





BOOL X_FILE::SetupMatrices(LPDIRECT3DDEVICE9 pD3D9, HWND hWnd, DWORD lasttime)
{
	
	dInput.Init(hWnd);

	dInput.Update();
	
	
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
	// ◆モデルの配置
	//D3DXMatrixIdentity(&matWorld);
	// モデルの拡大縮小
	

	vUpVec.x = 0.0f;
	vUpVec.y = 1.0f;
	vUpVec.z = 0.0f;

	D3DXVECTOR3 viewvecE(0.0f, 1.0f, -75.0f), viewvecL(0.0f,2.0f,4.0f);
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
	D3DXMatrixScaling(&matWorld, 0.3f, 0.3f, 0.3f);
	pD3D9->SetTransform(D3DTS_WORLD, &matWorld);
	// World Matrix.
	D3DXMatrixRotationX(&matWorld, timeGetTime() / 1000.5f);
	pD3D9->SetTransform(D3DTS_WORLD, &matWorld);
	lasttime = curtime;
	return TRUE;

}
BOOL X_FILE::NatureLight(LPDIRECT3DDEVICE9 pD3D9)
{
	//環境光の設定

	/*mat9.Diffuse.r = mat9.Ambient.r = 1.0f;
	mat9.Diffuse.g = mat9.Ambient.g = 1.0f;
	mat9.Diffuse.b = mat9.Ambient.b = 0.0f;
	mat9.Diffuse.a = mat9.Ambient.a = 1.0f;
	pD3D9->SetMaterial(&mat9);
	ZeroMemory(&light,sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	vecDir = D3DXVECTOR3(cosf(timeGetTime() / 350.f), 1.0f, sinf(timeGetTime() / 350.f));
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);
	light.Range = 1000.0f;
	pD3D9->SetLight(0, &light);
	pD3D9->LightEnable(0, TRUE);
	pD3D9->SetRenderState(D3DRS_LIGHTING,FALSE);
*/
	pD3D9->SetRenderState(D3DRS_AMBIENT,D3DCOLOR_ARGB(0,96,96,96));
	D3DXMatrixTranslation(&matWorld,0.0f,0.0f,1.0f);
	D3DXMatrixRotationY(&matView,D3DX_PI);

	pD3D9->SetTransform(D3DTS_WORLD, &matView);

	return TRUE;

}

BOOL X_FILE::Render(LPDIRECT3DDEVICE9 pD3D9)
{
	for (DWORD i = 0; i < MaterialNum; i++)
	{
		pD3D9->SetMaterial(&g_pMaterial[i]);
		pD3D9->SetTexture(0,g_pTexture[i]);
		g_pMesh->DrawSubset(i);
	}
	return true;
}


