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


//X�t�@�C���ǂݍ���
BOOL X_FILE::XfileLoader(LPCWSTR name)
{

	D3DXLoadMeshFromX(name, D3DXMESH_SYSTEMMEM,pDevice3D,
		NULL, &pD3DXMatrlBuffer, NULL, &MaterialNum, &g_pMesh);
	//����X�t�@�C�����Ȃ����
	if (g_pMesh == NULL)
	{
		MessageBox(NULL,_T("���b�V�����Ȃ���I"),_T("Mesh.exe"),MB_OK);
		//false��Ԃ�
		return FALSE;
	}
	
	return TRUE;

}
void X_FILE::CleanUp()
{
	

}

void X_FILE::Render(D3DXVECTOR3 *pos, D3DXVECTOR3 *rota, D3DXVECTOR3 *scale, LPDIRECT3DTEXTURE9 pTex9)
{
	D3DXMATRIX *m_World = new D3DXMATRIX();
	D3DXMATRIX *m_temp=new D3DXMATRIX();
	
	D3DXMatrixIdentity(m_World);
	D3DXMatrixIdentity(m_temp);
	
	//�g��̏���
	D3DXMatrixScaling(m_temp, scale->x, scale->y, scale->z);
	*m_World *= *m_temp;
	//���f���̍��W�ϊ�(���[�A�s�b�`�A���[�����w�肵�čs����쐬)
	D3DXMatrixRotationYawPitchRoll(m_temp, rota->y, rota->x, rota->z);
	*m_World *= *m_temp;
	//���f���ړ��̏���
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