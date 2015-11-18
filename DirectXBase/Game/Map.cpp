#include"Map.h"

BoundingBox Map::buildingsbox[150];

//�R���X�g���N�^
Map::Map()
{
	
}
//
Map::~Map()
{

}


HRESULT Map::LoadBuldings()
{
		//�c��
		tfloor[0].Load(_T("texture/douro.png"));
		tfloor[1].Load(_T("texture/douro2.png"));
		tfloor[2].Load(_T("texture/douro3.png"));
		//����
		tfloor[3].Load(_T("texture/douro4.png"));
		tfloor[4].Load(_T("texture/douro5.png"));
		tfloor[5].Load(_T("texture/douro6.png"));
		//���[�^���[
		tfloor[6].Load(_T("texture/douro7.png"));
		//�����K�̒n��
		tfloorGround[0].Load(_T("texture/yuka.png"));
		tfloorGround[1].Load(_T("texture/yuka2.png"));
		tfloorGround[2].Load(_T("texture/yuka3.png"));
		tfloorGround[3].Load(_T("texture/yuka4.png"));
		tfloorGround[4].Load(_T("texture/yuka5.png"));
		tfloorGround[5].Load(_T("texture/yuka6.png"));
		tfloorGround[6].Load(_T("texture/yuka7.png"));
		tfloorGround[7].Load(_T("texture/yuka8.png"));
		tfloorGround[8].Load(_T("texture/yuka9.png"));
		tfloorGround[9].Load(_T("texture/yuka10.png"));
		tfloorGround[10].Load(_T("texture/yuka11.png"));
		//�r���̃e�N�X�`��
		tBuil[0].Load(_T("texture/buil-tex.jpg"));
		tBuil[1].Load(_T("texture/buil2-tex.jpg"));
		tBuil[2].Load(_T("texture/buil3-tex.jpg"));

		//��
		tpanelSky[0].Load(_T("texture/sora.png"));
		tpanelSky[1].Load(_T("texture/sora2.png"));
		tpanelSky[2].Load(_T("texture/sora3.png"));
		//���z
		tpanelSun.Load(_T("texture/taiyo.png"));

		//����X�t�@�C��
		xfloor.XfileLoader(L"xfile/floor1.x");
		//���xfile
		xpanelSky.XfileLoader(L"xfile/panele1.x");
		//�r����X�t�@�C��
		xBuil[0].XfileLoader(L"xfile/building.X");
		xBuil[1].XfileLoader(L"xfile/building2.X");
		xBuil[2].XfileLoader(L"xfile/building3.X");
		
	return S_OK;
}

void Map::MapRender()
{
	//���[�^���[
	xfloor.Render(&D3DXVECTOR3(0,0,6), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(1,1,1),tfloor[6].GetTexture());
	//�c���H(z�����}12)
	xfloor.Render(&D3DXVECTOR3(0, 0, -6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloor[1].GetTexture());
	xfloor.Render(&D3DXVECTOR3(0, 0, -18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloor[2].GetTexture());
	xfloor.Render(&D3DXVECTOR3(0, 0, -30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloor[0].GetTexture());
	xfloor.Render(&D3DXVECTOR3(0, 0, -42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloor[2].GetTexture());
	xfloor.Render(&D3DXVECTOR3(0, 0, -54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloor[1].GetTexture());
	xfloor.Render(&D3DXVECTOR3(0, 0, 18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloor[0].GetTexture());
	xfloor.Render(&D3DXVECTOR3(0, 0, 30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloor[1].GetTexture());
	xfloor.Render(&D3DXVECTOR3(0, 0, 42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloor[1].GetTexture());
	xfloor.Render(&D3DXVECTOR3(0, 0, 54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloor[1].GetTexture());
	xfloor.Render(&D3DXVECTOR3(0, 0, 66), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloor[1].GetTexture());
	//�����H(x�����}12)
	xfloor.Render(&D3DXVECTOR3(-12, 0, 6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloor[3].GetTexture());
	xfloor.Render(&D3DXVECTOR3(-24, 0, 6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloor[4].GetTexture());
	xfloor.Render(&D3DXVECTOR3(-36, 0, 6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloor[5].GetTexture());
	xfloor.Render(&D3DXVECTOR3(12, 0, 6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloor[3].GetTexture());
	xfloor.Render(&D3DXVECTOR3(24, 0, 6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloor[4].GetTexture());
	xfloor.Render(&D3DXVECTOR3(36, 0, 6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloor[5].GetTexture());
	//�n��
	//���[�^���[�t��
	//����N�_
	xfloor.Render(&D3DXVECTOR3(-12, 0, 18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[7].GetTexture());
	//����c���H��
	xfloor.Render(&D3DXVECTOR3(-12, 0, 30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[3].GetTexture());
	xfloor.Render(&D3DXVECTOR3(-12, 0, 42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[3].GetTexture());
	xfloor.Render(&D3DXVECTOR3(-12, 0, 54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[3].GetTexture());
	//����c���H����
	xfloor.Render(&D3DXVECTOR3(-12, 0, 66), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[3].GetTexture());
	//���㉡���H��
	xfloor.Render(&D3DXVECTOR3(-24, 0, 18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[5].GetTexture());
	//���㉡���H�[
	xfloor.Render(&D3DXVECTOR3(-36, 0, 18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[5].GetTexture());
	//�������
	//����
	xfloor.Render(&D3DXVECTOR3(-24, 0, 18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[0].GetTexture());
	xfloor.Render(&D3DXVECTOR3(-24, 0, 30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());
	xfloor.Render(&D3DXVECTOR3(-24, 0, 42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());
	xfloor.Render(&D3DXVECTOR3(-24, 0, 54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[0].GetTexture());
	xfloor.Render(&D3DXVECTOR3(-24, 0, 66), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[0].GetTexture());
	//����
	xfloor.Render(&D3DXVECTOR3(-36, 0, 18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());
	xfloor.Render(&D3DXVECTOR3(-36, 0, 30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[0].GetTexture());
	xfloor.Render(&D3DXVECTOR3(-36, 0, 42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());
	xfloor.Render(&D3DXVECTOR3(-36, 0, 54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());
	xfloor.Render(&D3DXVECTOR3(-36, 0, 66), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[0].GetTexture());
	//�E��N�_
	xfloor.Render(&D3DXVECTOR3(12, 0, 18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[9].GetTexture());
	//�E��c���H��
	xfloor.Render(&D3DXVECTOR3(12, 0, 30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[2].GetTexture());
	xfloor.Render(&D3DXVECTOR3(12, 0, 42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[2].GetTexture());
	xfloor.Render(&D3DXVECTOR3(12, 0, 54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[2].GetTexture());
	//�E��c���H����
	xfloor.Render(&D3DXVECTOR3(12, 0, 66), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[2].GetTexture());
	//�E�㉡���H��
	xfloor.Render(&D3DXVECTOR3(24, 0, 18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[5].GetTexture());
	//�E�㉡���H�[
	xfloor.Render(&D3DXVECTOR3(36, 0, 18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[5].GetTexture());
	//�E�����
	//����
	xfloor.Render(&D3DXVECTOR3(24, 0, 18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[0].GetTexture());
	xfloor.Render(&D3DXVECTOR3(24, 0, 30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());
	xfloor.Render(&D3DXVECTOR3(24, 0, 42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());
	xfloor.Render(&D3DXVECTOR3(24, 0, 54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[0].GetTexture());
	xfloor.Render(&D3DXVECTOR3(24, 0, 66), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[0].GetTexture());
	//����
	xfloor.Render(&D3DXVECTOR3(36, 0, 18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());
	xfloor.Render(&D3DXVECTOR3(36, 0,30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[0].GetTexture());
	xfloor.Render(&D3DXVECTOR3(36, 0, 42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());
	xfloor.Render(&D3DXVECTOR3(36, 0, 54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());
	xfloor.Render(&D3DXVECTOR3(36, 0, 66), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[0].GetTexture());
	//�����N�_
	xfloor.Render(&D3DXVECTOR3(-12, 0, -6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[10].GetTexture());
	//�����c���H��
	xfloor.Render(&D3DXVECTOR3(-12, 0, -18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[3].GetTexture());
	xfloor.Render(&D3DXVECTOR3(-12, 0, -30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[3].GetTexture());
	xfloor.Render(&D3DXVECTOR3(-12, 0, -42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[3].GetTexture());
	//�����c���H����
	xfloor.Render(&D3DXVECTOR3(-12, 0, -54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[3].GetTexture());
	//���������H��
	xfloor.Render(&D3DXVECTOR3(-24, 0, -6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[4].GetTexture());
	//���������H�[
	xfloor.Render(&D3DXVECTOR3(-36, 0, -6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[4].GetTexture());
	//��������
	//����
	xfloor.Render(&D3DXVECTOR3(-24, 0, -18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[0].GetTexture());
	xfloor.Render(&D3DXVECTOR3(-24, 0, -30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());
	xfloor.Render(&D3DXVECTOR3(-24, 0, -42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());
	xfloor.Render(&D3DXVECTOR3(-24, 0, -54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[0].GetTexture());
	//����
	xfloor.Render(&D3DXVECTOR3(-36, 0, -18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());
	xfloor.Render(&D3DXVECTOR3(-36, 0, -30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[0].GetTexture());
	xfloor.Render(&D3DXVECTOR3(-36, 0, -42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());
	xfloor.Render(&D3DXVECTOR3(-36, 0, -54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());
	//�E���N�_
	xfloor.Render(&D3DXVECTOR3(12, 0, -6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[8].GetTexture());
	//�E���c���H��
	xfloor.Render(&D3DXVECTOR3(12, 0, -18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[2].GetTexture());
	xfloor.Render(&D3DXVECTOR3(12, 0, -30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[2].GetTexture());
	xfloor.Render(&D3DXVECTOR3(12, 0, -42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[2].GetTexture());
	//�E���c���H����
	xfloor.Render(&D3DXVECTOR3(12, 0, -54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[2].GetTexture());
	//�E�������H��
	xfloor.Render(&D3DXVECTOR3(24, 0, -6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[4].GetTexture());
	//�E�������H�[
	xfloor.Render(&D3DXVECTOR3(36, 0, -6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[4].GetTexture());
	//�E������
	//����
	xfloor.Render(&D3DXVECTOR3(24, 0, -18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[0].GetTexture());
	xfloor.Render(&D3DXVECTOR3(24, 0, -30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());
	xfloor.Render(&D3DXVECTOR3(24, 0, -42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());
	xfloor.Render(&D3DXVECTOR3(24, 0, -54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[0].GetTexture());
	//����
	xfloor.Render(&D3DXVECTOR3(36, 0, -18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());
	xfloor.Render(&D3DXVECTOR3(36, 0, -30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[0].GetTexture());
	xfloor.Render(&D3DXVECTOR3(36, 0, -42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());
	xfloor.Render(&D3DXVECTOR3(36, 0, -54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());

	//�Ǎ��
	//����
		for (float wally = 6.0f; wally < 31.0f; wally += 12.0f)
		{
			for (float wallx = -36.0f; wallx < 37.0f; wallx += 12.0f)
			{
				xpanelSky.Render(&D3DXVECTOR3(wallx, wally, 72), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[0].GetTexture());
				
				numv[i] = xpanelSky.g_pMesh->GetNumVertices();
				stride[i] = D3DXGetFVFVertexSize(xpanelSky.g_pMesh->GetFVF());
				hr[i] = xpanelSky.g_pMesh->GetVertexBuffer(&pvb9);
				if (FAILED(hr))
				{
					return;
				}
				hr[i] = pvb9->Lock(0, 0, (VOID**)&pvertices, 0);	//���_�o�b�t�@�����b�N
				if (FAILED(hr))
				{
					return;
				}
				hr[i] = D3DXComputeBoundingBox((D3DXVECTOR3*)pvertices, numv[i], stride[i], &lminv, &lmaxv);
				if (FAILED(hr))
				{
					return;
				}
				buildingsbox[i].minv = D3DXVECTOR3(wallx, wally, 72) - D3DXVECTOR3(6.0f, 6.0f, 3.0f);
				buildingsbox[i].maxv = D3DXVECTOR3(wallx, wally, 72) + D3DXVECTOR3(6.0f, 6.0f, 3.0f);
				pvb9->Unlock();
				i++;
			}
		}
		
	
	//�w��
	for (float wally = 6.0f; wally < 31.0f; wally += 12.0f)
	{
		for (float wallx = -36.0f; wallx < 37.0f; wallx += 12.0f)
		{
			xpanelSky.Render(&D3DXVECTOR3(wallx, wally, -60.0f), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[0].GetTexture());
			numv[i] = xpanelSky.g_pMesh->GetNumVertices();
			stride[i] = D3DXGetFVFVertexSize(xpanelSky.g_pMesh->GetFVF());
			hr[i] = xpanelSky.g_pMesh->GetVertexBuffer(&pvb9);
			if (FAILED(hr))
			{
				return;
			}
			hr[i] = pvb9->Lock(0, 0, (VOID**)&pvertices, 0);	//���_�o�b�t�@�����b�N
			if (FAILED(hr))
			{
				return;
			}
			hr[i] = D3DXComputeBoundingBox((D3DXVECTOR3*)pvertices, numv[i], stride[i], &lminv, &lmaxv);
			if (FAILED(hr))
			{
				return;
			}
			buildingsbox[i].minv = D3DXVECTOR3(wallx, wally, -60.0f) - D3DXVECTOR3(6.0f, 6.0f, 3.0f);
			buildingsbox[i].maxv = D3DXVECTOR3(wallx, wally, -60.0f) + D3DXVECTOR3(6.0f, 6.0f, 3.0f);
			pvb9->Unlock();
			i++;
		}
	}

	//�E��
	for (float wally = 6.0f; wally < 31.0f; wally += 12.0f)
	{
		for (float wallz = -54.0f; wallz < 67.0f; wallz += 12.0f)
		{
			xpanelSky.Render(&D3DXVECTOR3(42, wally, wallz), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[0].GetTexture());
			numv[i] = xpanelSky.g_pMesh->GetNumVertices();
			stride[i] = D3DXGetFVFVertexSize(xpanelSky.g_pMesh->GetFVF());
			hr[i] = xpanelSky.g_pMesh->GetVertexBuffer(&pvb9);
			if (FAILED(hr))
			{
				return;
			}
			hr[i] = pvb9->Lock(0, 0, (VOID**)&pvertices, 0);	//���_�o�b�t�@�����b�N
			if (FAILED(hr))
			{
				return;
			}
			hr[i] = D3DXComputeBoundingBox((D3DXVECTOR3*)pvertices, numv[i], stride[i], &lminv, &lmaxv);
			if (FAILED(hr))
			{
				return;
			}
			buildingsbox[i].minv = D3DXVECTOR3(42.0f, wally, wallz) - D3DXVECTOR3(4.0f, 3.0f, 4.0f);
			buildingsbox[i].maxv = D3DXVECTOR3(42.0f, wally, wallz) + D3DXVECTOR3(4.0f, 3.0f, 4.0f);
			pvb9->Unlock();
			i++;
		}
	}

	//����
	for (float wally = 6.0f; wally < 31.0f; wally += 12.0f)
	{
		for (float wallz = -54.0f; wallz < 67.0f; wallz += 12.0f)
		{
			xpanelSky.Render(&D3DXVECTOR3(-42, wally, wallz), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[0].GetTexture());
			numv[i] = xpanelSky.g_pMesh->GetNumVertices();
			stride[i] = D3DXGetFVFVertexSize(xpanelSky.g_pMesh->GetFVF());
			hr[i] = xpanelSky.g_pMesh->GetVertexBuffer(&pvb9);
			if (FAILED(hr))
			{
				return;
			}
			hr[i] = pvb9->Lock(0, 0, (VOID**)&pvertices, 0);	//���_�o�b�t�@�����b�N
			if (FAILED(hr))
			{
				return;
			}
			hr[i] = D3DXComputeBoundingBox((D3DXVECTOR3*)pvertices, numv[i], stride[i], &lminv, &lmaxv);
			if (FAILED(hr))
			{
				return;
			}
			buildingsbox[i].minv = D3DXVECTOR3(-42.0f, wally, wallz) - D3DXVECTOR3(4.0f, 6.0f, 6.0f);
			buildingsbox[i].maxv = D3DXVECTOR3(-42.0f, wally, wallz) + D3DXVECTOR3(4.0f, 6.0f, 6.0f);
			pvb9->Unlock();
			i++;
		}
	}
	i = 0;

	//��
	for (float skyx = -36; skyx < 37.0f; skyx += 12)
	{
		for (float skyz = -54; skyz < 67; skyz += 12)
		{
			xpanelSky.Render(&D3DXVECTOR3(skyx, 35.0f, skyz), &D3DXVECTOR3(0, 0, 1.56999886f), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
		}
	}
	
	//�r���̕`��
	
	//�D�F�̃r��
	xBuil[0].Render(&D3DXVECTOR3(30.0f, 0.1f, -50.0f), &D3DXVECTOR3(4.69999790f, 0, 0), &D3DXVECTOR3(0.1f, 0.1f, 0.2f), tBuil[0].GetTexture());
	numv[108] = xBuil[0].g_pMesh->GetNumVertices();
	stride[108] = D3DXGetFVFVertexSize(xBuil[0].g_pMesh->GetFVF());
	hr[108] = xBuil[0].g_pMesh->GetVertexBuffer(&pvb9);
	if (FAILED(hr))
	{
		return;
	}
	hr[108] = pvb9->Lock(0, 0, (VOID**)&pvertices, 0);	//���_�o�b�t�@�����b�N
	if (FAILED(hr))
	{
		return;
	}
	hr[108] = D3DXComputeBoundingBox((D3DXVECTOR3*)pvertices, numv[108], stride[108], &lminv, &lmaxv);
	if (FAILED(hr))
	{
		return;
	}
	buildingsbox[108].minv = D3DXVECTOR3(30.0f, 0.1f, -50.0f) - D3DXVECTOR3(3.0f,3.0f,3.0f);
	buildingsbox[108].maxv = D3DXVECTOR3(30.0f, 0.1f, -50.0f) + D3DXVECTOR3(3.0f, 3.0f, 3.0f);
	pvb9->Unlock();
	


	xBuil[0].Render(&D3DXVECTOR3(30.0f, 0.1f, 36.0f), &D3DXVECTOR3(4.69999790f, 0, 0), &D3DXVECTOR3(0.1f, 0.1f, 0.2f), tBuil[0].GetTexture());
	numv[109] = xBuil[0].g_pMesh->GetNumVertices();
	stride[109] = D3DXGetFVFVertexSize(xBuil[0].g_pMesh->GetFVF());
	hr[109] = xBuil[0].g_pMesh->GetVertexBuffer(&pvb9);
	if (FAILED(hr))
	{
		return;
	}
	hr[109] = pvb9->Lock(0, 0, (VOID**)&pvertices, 0);	//���_�o�b�t�@�����b�N
	if (FAILED(hr))
	{
		return;
	}
	hr[109] = D3DXComputeBoundingBox((D3DXVECTOR3*)pvertices, numv[109], stride[109], &lminv, &lmaxv);
	if (FAILED(hr))
	{
		return;
	}
	buildingsbox[109].minv = D3DXVECTOR3(30.0f, 0.1f, 36.0f) - D3DXVECTOR3(3.0f, 3.0f, 3.0f);
	buildingsbox[109].maxv = D3DXVECTOR3(30.0f, 0.1f, 36.0f) + D3DXVECTOR3(3.0f, 3.0f, 3.0f);
	pvb9->Unlock();

	xBuil[0].Render(&D3DXVECTOR3(-30.0f, 0.1f, -24.0f), &D3DXVECTOR3(4.69999790f, 0, 0), &D3DXVECTOR3(0.1f, 0.1f, 0.1f), tBuil[0].GetTexture());
	numv[110] = xBuil[0].g_pMesh->GetNumVertices();
	stride[110] = D3DXGetFVFVertexSize(xBuil[0].g_pMesh->GetFVF());
	hr[110] = xBuil[0].g_pMesh->GetVertexBuffer(&pvb9);
	if (FAILED(hr))
	{
		return;
	}
	hr[110] = pvb9->Lock(0, 0, (VOID**)&pvertices, 0);	//���_�o�b�t�@�����b�N
	if (FAILED(hr))
	{
		return;
	}
	hr[110] = D3DXComputeBoundingBox((D3DXVECTOR3*)pvertices, numv[110], stride[110], &lminv, &lmaxv);
	if (FAILED(hr))
	{
		return;
	}
	buildingsbox[110].minv = D3DXVECTOR3(-30.0f, 0.1f, -24.0f) - D3DXVECTOR3(3.0f, 3.0f, 3.0f);
	buildingsbox[110].maxv = D3DXVECTOR3(-30.0f, 0.1f, -24.0f) + D3DXVECTOR3(3.0f, 3.0f, 3.0f);
	pvb9->Unlock();
	//�N���[���F�̃r��
	xBuil[1].Render(&D3DXVECTOR3(12.0f, 0.1f, -24.0f), &D3DXVECTOR3(-1.60000026f, 0, -7.89999485f), &D3DXVECTOR3(0.1f, 0.1f, 0.1f), tBuil[1].GetTexture());
	numv[111] = xBuil[1].g_pMesh->GetNumVertices();
	stride[111] = D3DXGetFVFVertexSize(xBuil[1].g_pMesh->GetFVF());
	hr[111] = xBuil[1].g_pMesh->GetVertexBuffer(&pvb9);
	if (FAILED(hr))
	{
		return;
	}
	hr[111] = pvb9->Lock(0, 0, (VOID**)&pvertices, 0);	//���_�o�b�t�@�����b�N
	if (FAILED(hr))
	{
		return;
	}
	hr[111] = D3DXComputeBoundingBox((D3DXVECTOR3*)pvertices, numv[111], stride[111], &lminv, &lmaxv);
	if (FAILED(hr))
	{
		return;
	}
	buildingsbox[111].minv = D3DXVECTOR3(12.0f, 0.1f, -24.0f) - D3DXVECTOR3(3.0f, 3.0f, 3.0f);
	buildingsbox[111].maxv = D3DXVECTOR3(12.0f, 0.1f, -24.0f) + D3DXVECTOR3(3.0f, 3.0f, 3.0f);
	pvb9->Unlock();

	xBuil[1].Render(&D3DXVECTOR3(-30.0f, 0.1f, 12.0f), &D3DXVECTOR3(-1.60000026f, 0, -7.89999485f), &D3DXVECTOR3(0.1f, 0.1f, 0.2f), tBuil[1].GetTexture());
	numv[112] = xBuil[1].g_pMesh->GetNumVertices();
	stride[112] = D3DXGetFVFVertexSize(xBuil[1].g_pMesh->GetFVF());
	hr[112] = xBuil[1].g_pMesh->GetVertexBuffer(&pvb9);
	if (FAILED(hr))
	{
		return;
	}
	hr[112] = pvb9->Lock(0, 0, (VOID**)&pvertices, 0);	//���_�o�b�t�@�����b�N
	if (FAILED(hr))
	{
		return;
	}
	hr[112] = D3DXComputeBoundingBox((D3DXVECTOR3*)pvertices, numv[112], stride[112], &lminv, &lmaxv);
	if (FAILED(hr))
	{
		return;
	}
	buildingsbox[112].minv = D3DXVECTOR3(-30.0f, 0.1f, 12.0f) - D3DXVECTOR3(3.0f, 3.0f, 3.0f);
	buildingsbox[112].maxv = D3DXVECTOR3(-30.0f, 0.1f, 12.0f) + D3DXVECTOR3(3.0f, 3.0f, 3.0f);
	pvb9->Unlock();
	//�ԓ��F�̃r��
	xBuil[2].Render(&D3DXVECTOR3(12.0f, 0.1f, 36.0f), &D3DXVECTOR3(-1.60000026f, 0, -4.69999790f), &D3DXVECTOR3(0.1f, 0.1f, 0.2f), tBuil[2].GetTexture());
	numv[113] = xBuil[2].g_pMesh->GetNumVertices();
	stride[113] = D3DXGetFVFVertexSize(xBuil[2].g_pMesh->GetFVF());
	hr[113] = xBuil[2].g_pMesh->GetVertexBuffer(&pvb9);
	if (FAILED(hr))
	{
		return;
	}
	hr[113] = pvb9->Lock(0, 0, (VOID**)&pvertices, 0);	//���_�o�b�t�@�����b�N
	if (FAILED(hr))
	{
		return;
	}
	hr[113] = D3DXComputeBoundingBox((D3DXVECTOR3*)pvertices, numv[113], stride[113], &lminv, &lmaxv);
	if (FAILED(hr))
	{
		return;
	}
	buildingsbox[113].minv = D3DXVECTOR3(12.0f, 0.1f, 36.0f) - D3DXVECTOR3(3.0f, 3.0f, 4.0f);
	buildingsbox[113].maxv = D3DXVECTOR3(12.0f, 0.1f, 36.0f) + D3DXVECTOR3(3.0f, 3.0f, 4.0f);
	pvb9->Unlock();

	xBuil[2].Render(&D3DXVECTOR3(-12.0f, 0.1f, 24.0f), &D3DXVECTOR3(-1.60000026f, 0, -4.69999790f), &D3DXVECTOR3(0.1f, 0.1f, 0.1f), tBuil[2].GetTexture());
	numv[114] = xBuil[2].g_pMesh->GetNumVertices();
	stride[114] = D3DXGetFVFVertexSize(xBuil[2].g_pMesh->GetFVF());
	hr[114] = xBuil[2].g_pMesh->GetVertexBuffer(&pvb9);
	if (FAILED(hr))
	{
		return;
	}
	hr[114] = pvb9->Lock(0, 0, (VOID**)&pvertices, 0);	//���_�o�b�t�@�����b�N
	if (FAILED(hr))
	{
		return;
	}
	hr[114] = D3DXComputeBoundingBox((D3DXVECTOR3*)pvertices, numv[114], stride[114], &lminv, &lmaxv);
	if (FAILED(hr))
	{
		return;
	}
	buildingsbox[114].minv = D3DXVECTOR3(-12.0f, 0.1f, 24.0f) - D3DXVECTOR3(4.0f, 3.0f, 4.0f);
	buildingsbox[114].maxv = D3DXVECTOR3(-12.0f, 0.1f, 24.0f) + D3DXVECTOR3(4.0f, 3.0f, 4.0f);
	pvb9->Unlock();

	
	
	/*for (int i = 0; i < 3; i++)
	{
		numv[1 + i] = xBuil[i].g_pMesh->GetNumVertices();
		stride[1 + i] = xBuil[i].g_pMesh->GetFVF();
		hr[1 + i] = xBuil[i].g_pMesh->GetVertexBuffer(&pvb9);
		if (FAILED(hr))
		{
			return;
		}
		hr[1 + i] = pvb9->Lock(0, 0, (VOID**)&pvertices, 0);
		if (FAILED(hr))
		{
			return;
		}
		hr[1 + i] = D3DXComputeBoundingBox((D3DXVECTOR3*)pvertices, numv[0], stride[0], &lminv, &lmaxv);
		if (FAILED(hr))
		{
			return;
		}
		buildingsbox[1 + i].minv = xBuil[i].pos + lminv;
		buildingsbox[1 + i].maxv = xBuil[i].pos + lmaxv;
		pvb9->Unlock();
	}*/
}


BOOL Map::HitTikei(D3DXVECTOR3 *pmina, D3DXVECTOR3 *pmaxa)
{
	for (int i = 0; i < 115; i++)
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