
#include"Xfile.h"

//コンストラクタ
X_FILE::X_FILE(LPDIRECT3DDEVICE9 dev, LPCSTR model)
{
	LPD3DXBUFFER pD3DXMtrlBuffer;

	pMesh = NULL;
	pMat = NULL;
	pTex = NULL;
	dwNum = 0L;

	if (FAILED(D3DXLoadMeshFromX((LPCWSTR)model, D3DXMESH_SYSTEMMEM, dev, NULL,
		&pD3DXMtrlBuffer, NULL, &dwNum, &pMesh)))
	{
		MessageBox(NULL, _T("Could not find x file"), _T("LoadMeshFromX"), MB_OK);
		return;
	}
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	pMat = new D3DMATERIAL9[dwNum];
	if (pMat == NULL)     return;
	pTex = new LPDIRECT3DTEXTURE9[dwNum];
	if (pTex == NULL)     return;
	for (DWORD i = 0; i<dwNum; i++)
	{
		pMat[i] = d3dxMaterials[i].MatD3D;
		pTex[i] = NULL;
		if (d3dxMaterials[i].pTextureFilename != NULL &&
			lstrlen((LPCWSTR)d3dxMaterials[i].pTextureFilename)>0)
		{
			if (FAILED(D3DXCreateTextureFromFile(dev,
				(LPCWSTR)d3dxMaterials[i].pTextureFilename, &pTex[i])))
				MessageBox(NULL, _T("Could not find texture map"), _T("X File Object"), MB_OK);
		}
	}
	pD3DXMtrlBuffer->Release();

	// 法線ベクトルが設定されていないときの処理
	if (!((pMesh)->GetFVF() & D3DFVF_NORMAL))
	{
		ID3DXMesh* pTempMesh;
		(pMesh)->CloneMeshFVF((pMesh)->GetOptions(), (pMesh)->GetFVF() | D3DFVF_NORMAL, dev, &pTempMesh);
		D3DXComputeNormals(pTempMesh, NULL);
		SAFE_RELEASE(pMesh);
		(pMesh) = pTempMesh;
	}
}

//★デストラクタ
X_FILE::~X_FILE()
{
	SAFE_DELETE(pMat);
	if (pTex)
	{
		for (DWORD i = 0; i<dwNum; i++)   SAFE_RELEASE(pTex[i]);
		SAFE_DELETE(pTex);
	}
	SAFE_RELEASE(pMesh);
}

void X_FILE::SetupMatrices(LPDIRECT3DDEVICE9 pD3D9)
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixRotationY(&matWorld, timeGetTime() / 1000.0f);
	pD3D9->SetTransform(D3DTS_WORLD, &matWorld);
	D3DXVECTOR3 vEyePt(0.0f, 3.0f, -5.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	pD3D9->SetTransform(D3DTS_VIEW, &matView);
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	pD3D9->SetTransform(D3DTS_PROJECTION, &matProj);
}



// モデルを描画
void X_FILE::Render()
{
	if (pMesh)
	{
		for (DWORD i = 0; i<dwNum; i++)
		{
			pDEV->SetMaterial(&pMat[i]);
			pDEV->SetTexture(0, pTex[i]);
			pMesh->DrawSubset(i);
		}
	}
}