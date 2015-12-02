#include"Map.h"

BoundingBox Map::buildingsbox[8];

//�R���X�g���N�^
Map::Map()
{

	LoadBuldings();
}
//
Map::~Map()
{

}


HRESULT Map::LoadBuldings()
{
	ttfloor.Load(_T("texture/mapo.png"));
		//�r���̃e�N�X�`��
		tBuil[0].Load(_T("texture/buil-tex.jpg"));
		tBuil[1].Load(_T("texture/buil2-tex.jpg"));
		tBuil[2].Load(_T("texture/buil3-tex.jpg"));

		//��
		tpanelSky[0].Load(_T("texture/sora.png"));
		tpanelSky[1].Load(_T("texture/sora2.png"));
		tpanelSky[2].Load(_T("texture/sora3.png"));
		tSky.Load(_T("texture/sky-texture.png"));
		//���z
		tpanelSun.Load(_T("texture/taiyo.png"));

		//����X�t�@�C��
		xfloor.XfileLoader(L"xfile/maponigo.X");
		//���xfile
		xpanelSky.XfileLoader(L"xfile/panele1.x");
		xSky.XfileLoader(L"xfile/sky.X");
		//�r����X�t�@�C��
		xBuil[0].XfileLoader(L"xfile/building.X");
		xBuil[1].XfileLoader(L"xfile/building2.X");
		xBuil[2].XfileLoader(L"xfile/building3.X");
		
	return S_OK;
}

void Map::MapRender()
{
	//���`��
xfloor.Render(&D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f - (D3DX_PI / 2), 0.0f, 0.0f), &D3DXVECTOR3(0.2f, 0.2f, 0.2f), ttfloor.GetTexture());
	//�Ǎ��
	//����
		for (float wally = 6.0f; wally < 31.0f; wally += 12.0f)
		{
			for (float wallx = -36.0f; wallx < 37.0f; wallx += 12.0f)
			{
				xpanelSky.Render(&D3DXVECTOR3(wallx, wally, 72), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
			}
		}
	//�w��
	for (float wally = 6.0f; wally < 31.0f; wally += 12.0f)
	{
		for (float wallx = -36.0f; wallx < 37.0f; wallx += 12.0f)
		{
			xpanelSky.Render(&D3DXVECTOR3(wallx, wally, -60.0f), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());

		}
	}

	//�E��
	for (float wally = 6.0f; wally < 31.0f; wally += 12.0f)
	{
		for (float wallz = -54.0f; wallz < 67.0f; wallz += 12.0f)
		{
			xpanelSky.Render(&D3DXVECTOR3(42, wally, wallz), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
		}
	}

	//����
	for (float wally = 6.0f; wally < 31.0f; wally += 12.0f)
	{
		for (float wallz = -54.0f; wallz < 67.0f; wallz += 12.0f)
		{
			xpanelSky.Render(&D3DXVECTOR3(-42, wally, wallz), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
		}
	}
	i = 0;
	xSky.Render(&D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tSky.GetTexture());
	
	//�r���̕`��
	
	//�D�F�̃r��
	xBuil[0].Render(&D3DXVECTOR3(30.0f, 0.1f, -50.0f), &D3DXVECTOR3(4.69999790f, 0, 0), &D3DXVECTOR3(0.1f, 0.1f, 0.2f), tBuil[0].GetTexture());
	numv[0] = xBuil[0].g_pMesh->GetNumVertices();
	stride[0] = D3DXGetFVFVertexSize(xBuil[0].g_pMesh->GetFVF());
	hr[0] = xBuil[0].g_pMesh->GetVertexBuffer(&pvb9);
	if (FAILED(hr))
	{
		return;
	}
	hr[0] = pvb9->Lock(0, 0, (VOID**)&pvertices, 0);	//���_�o�b�t�@�����b�N
	if (FAILED(hr))
	{
		return;
	}
	hr[0] = D3DXComputeBoundingBox((D3DXVECTOR3*)pvertices, numv[0], stride[0], &lminv, &lmaxv);
	if (FAILED(hr))
	{
		return;
	}
	buildingsbox[0].minv = D3DXVECTOR3(30.0f, 0.1f, -50.0f) - D3DXVECTOR3(3.0f,3.0f,3.0f);
	buildingsbox[0].maxv = D3DXVECTOR3(30.0f, 0.1f, -50.0f) + D3DXVECTOR3(3.0f, 3.0f, 3.0f);
	pvb9->Unlock();
	


	xBuil[0].Render(&D3DXVECTOR3(30.0f, 0.1f, 36.0f), &D3DXVECTOR3(4.69999790f, 0, 0), &D3DXVECTOR3(0.1f, 0.1f, 0.2f), tBuil[0].GetTexture());
	numv[1] = xBuil[0].g_pMesh->GetNumVertices();
	stride[1] = D3DXGetFVFVertexSize(xBuil[0].g_pMesh->GetFVF());
	hr[1] = xBuil[0].g_pMesh->GetVertexBuffer(&pvb9);
	if (FAILED(hr))
	{
		return;
	}
	hr[1] = pvb9->Lock(0, 0, (VOID**)&pvertices, 0);	//���_�o�b�t�@�����b�N
	if (FAILED(hr))
	{
		return;
	}
	hr[1] = D3DXComputeBoundingBox((D3DXVECTOR3*)pvertices, numv[1], stride[1], &lminv, &lmaxv);
	if (FAILED(hr))
	{
		return;
	}
	buildingsbox[1].minv = D3DXVECTOR3(30.0f, 0.1f, 36.0f) - D3DXVECTOR3(3.0f, 3.0f, 3.0f);
	buildingsbox[1].maxv = D3DXVECTOR3(30.0f, 0.1f, 36.0f) + D3DXVECTOR3(3.0f, 3.0f, 3.0f);
	pvb9->Unlock();

	xBuil[0].Render(&D3DXVECTOR3(-30.0f, 0.1f, -24.0f), &D3DXVECTOR3(4.69999790f, 0, 0), &D3DXVECTOR3(0.1f, 0.1f, 0.1f), tBuil[0].GetTexture());
	numv[2] = xBuil[0].g_pMesh->GetNumVertices();
	stride[2] = D3DXGetFVFVertexSize(xBuil[0].g_pMesh->GetFVF());
	hr[2] = xBuil[0].g_pMesh->GetVertexBuffer(&pvb9);
	if (FAILED(hr))
	{
		return;
	}
	hr[2] = pvb9->Lock(0, 0, (VOID**)&pvertices, 0);	//���_�o�b�t�@�����b�N
	if (FAILED(hr))
	{
		return;
	}
	hr[2] = D3DXComputeBoundingBox((D3DXVECTOR3*)pvertices, numv[2], stride[2], &lminv, &lmaxv);
	if (FAILED(hr))
	{
		return;
	}
	buildingsbox[2].minv = D3DXVECTOR3(-30.0f, 0.1f, -24.0f) - D3DXVECTOR3(3.0f, 3.0f, 3.0f);
	buildingsbox[2].maxv = D3DXVECTOR3(-30.0f, 0.1f, -24.0f) + D3DXVECTOR3(3.0f, 3.0f, 3.0f);
	pvb9->Unlock();
	//�N���[���F�̃r��
	xBuil[1].Render(&D3DXVECTOR3(12.0f, 0.1f, -24.0f), &D3DXVECTOR3(-1.60000026f, 0, -7.89999485f), &D3DXVECTOR3(0.1f, 0.1f, 0.1f), tBuil[1].GetTexture());
	numv[3] = xBuil[1].g_pMesh->GetNumVertices();
	stride[3] = D3DXGetFVFVertexSize(xBuil[1].g_pMesh->GetFVF());
	hr[3] = xBuil[1].g_pMesh->GetVertexBuffer(&pvb9);
	if (FAILED(hr))
	{
		return;
	}
	hr[3] = pvb9->Lock(0, 0, (VOID**)&pvertices, 0);	//���_�o�b�t�@�����b�N
	if (FAILED(hr))
	{
		return;
	}
	hr[3] = D3DXComputeBoundingBox((D3DXVECTOR3*)pvertices, numv[111], stride[111], &lminv, &lmaxv);
	if (FAILED(hr))
	{
		return;
	}
	buildingsbox[3].minv = D3DXVECTOR3(12.0f, 0.1f, -24.0f) - D3DXVECTOR3(4.0f, 3.0f, 5.0f);
	buildingsbox[3].maxv = D3DXVECTOR3(12.0f, 0.1f, -24.0f) + D3DXVECTOR3(4.0f, 3.0f, 5.0f);
	pvb9->Unlock();

	xBuil[1].Render(&D3DXVECTOR3(-30.0f, 0.1f, 12.0f), &D3DXVECTOR3(-1.60000026f, 0, -7.89999485f), &D3DXVECTOR3(0.1f, 0.1f, 0.2f), tBuil[1].GetTexture());
	numv[4] = xBuil[1].g_pMesh->GetNumVertices();
	stride[4] = D3DXGetFVFVertexSize(xBuil[1].g_pMesh->GetFVF());
	hr[4] = xBuil[1].g_pMesh->GetVertexBuffer(&pvb9);
	if (FAILED(hr))
	{
		return;
	}
	hr[4] = pvb9->Lock(0, 0, (VOID**)&pvertices, 0);	//���_�o�b�t�@�����b�N
	if (FAILED(hr))
	{
		return;
	}
	hr[4] = D3DXComputeBoundingBox((D3DXVECTOR3*)pvertices, numv[4], stride[4], &lminv, &lmaxv);
	if (FAILED(hr))
	{
		return;
	}
	buildingsbox[4].minv = D3DXVECTOR3(-30.0f, 0.1f, 12.0f) - D3DXVECTOR3(4.0f, 3.0f, 5.0f);
	buildingsbox[4].maxv = D3DXVECTOR3(-30.0f, 0.1f, 12.0f) + D3DXVECTOR3(4.0f, 3.0f, 5.0f);
	pvb9->Unlock();
	//�ԓ��F�̃r��
	xBuil[2].Render(&D3DXVECTOR3(12.0f, 0.1f, 36.0f), &D3DXVECTOR3(-1.60000026f, 0, -4.69999790f), &D3DXVECTOR3(0.1f, 0.1f, 0.2f), tBuil[2].GetTexture());
	numv[5] = xBuil[2].g_pMesh->GetNumVertices();
	stride[5] = D3DXGetFVFVertexSize(xBuil[2].g_pMesh->GetFVF());
	hr[5] = xBuil[2].g_pMesh->GetVertexBuffer(&pvb9);
	if (FAILED(hr))
	{
		return;
	}
	hr[5] = pvb9->Lock(0, 0, (VOID**)&pvertices, 0);	//���_�o�b�t�@�����b�N
	if (FAILED(hr))
	{
		return;
	}
	hr[5] = D3DXComputeBoundingBox((D3DXVECTOR3*)pvertices, numv[113], stride[113], &lminv, &lmaxv);
	if (FAILED(hr))
	{
		return;
	}
	buildingsbox[5].minv = D3DXVECTOR3(12.0f, 0.1f, 36.0f) - D3DXVECTOR3(4.0f, 3.0f, 4.0f);
	buildingsbox[5].maxv = D3DXVECTOR3(12.0f, 0.1f, 36.0f) + D3DXVECTOR3(4.0f, 3.0f, 4.0f);
	pvb9->Unlock();

	xBuil[2].Render(&D3DXVECTOR3(-12.0f, 0.1f, 24.0f), &D3DXVECTOR3(-1.60000026f, 0, -4.69999790f), &D3DXVECTOR3(0.1f, 0.1f, 0.1f), tBuil[2].GetTexture());
	numv[6] = xBuil[2].g_pMesh->GetNumVertices();
	stride[6] = D3DXGetFVFVertexSize(xBuil[2].g_pMesh->GetFVF());
	hr[6] = xBuil[2].g_pMesh->GetVertexBuffer(&pvb9);
	if (FAILED(hr))
	{
		return;
	}
	hr[6] = pvb9->Lock(0, 0, (VOID**)&pvertices, 0);	//���_�o�b�t�@�����b�N
	if (FAILED(hr))
	{
		return;
	}
	hr[6] = D3DXComputeBoundingBox((D3DXVECTOR3*)pvertices, numv[114], stride[114], &lminv, &lmaxv);
	if (FAILED(hr))
	{
		return;
	}
	buildingsbox[6].minv = D3DXVECTOR3(-12.0f, 0.1f, 24.0f) - D3DXVECTOR3(4.0f, 3.0f, 4.0f);
	buildingsbox[6].maxv = D3DXVECTOR3(-12.0f, 0.1f, 24.0f) + D3DXVECTOR3(4.0f, 3.0f, 4.0f);
	pvb9->Unlock();
}


BOOL Map::HitTikei(D3DXVECTOR3 *pmina, D3DXVECTOR3 *pmaxa)
{
	if (pmina->x < -40 || pmina->x >40)
	{
		return TRUE;
	}
	if (pmina->z < -59 || pmina->z >70)
	{
		return TRUE;
	}

	for (int i = 0; i < 7; i++)
	{
		D3DXVECTOR3 *pminb, *pmaxb;
		pminb = &buildingsbox[i].minv;
		pmaxb = &buildingsbox[i].maxv;

		if ((pmina->x < pmaxb->x) && (pmaxa->x > pminb->x) && (pmina->y <pmaxb->y) && (pmaxa->y > pminb->y) && (pmina->z < pmaxb->z) && (pmaxa->z > pminb->z))
		{
			return TRUE;
		}
	}
	return FALSE;

}

BOOL Map::HitETikei(D3DXVECTOR3 *emina, D3DXVECTOR3 *emaxa)
{
	if (emina->x < -40 || emina->x >40)
	{
		return TRUE;
	}
	if (emina->z < -59 || emina->z >70)
	{
		return TRUE;
	}
	for (int i = 0; i < 7; i++)
	{
		D3DXVECTOR3 *eminb, *emaxb;
		eminb = &buildingsbox[i].minv;
		emaxb = &buildingsbox[i].maxv;

		if ((emina->x < emaxb->x) && (emaxa->x > eminb->x) && (emina->y <emaxb->y) && (emaxa->y > eminb->y) && (emina->z < emaxb->z) && (emaxa->z > eminb->z))
		{
			return TRUE;
		}
	}
	return FALSE;




}