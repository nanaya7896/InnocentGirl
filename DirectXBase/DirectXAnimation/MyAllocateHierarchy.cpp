#include"MyAllocatehierarchy.h"

//�t���[�����쐬����
HRESULT MyAllocateHierarchy::CreateFrame(LPCTSTR Name, LPD3DXFRAME* ppNewFrame)
{
	HRESULT hr = S_OK;
	MYFRAME *pFrame;
	//�V�����t���[���A�h���X�i�[�p�ϐ���������
	*ppNewFrame = NULL;
	//�t���[���̈�m��
	pFrame = new MYFRAME;
	//�̈�m�ۂ̎��s���̏���
	if (pFrame == NULL)
	{
		return E_OUTOFMEMORY;
	}
	//�t���[�����i�[�p�̈�m��
	pFrame = new MYFRAME;
	//�̈�m�ۂ̎��s���̏���
	if (pFrame == NULL)
	{
		return E_OUTOFMEMORY;
	}
	//�t���[�����i�[�p�̈�m��
	pFrame->Name = new TCHAR[lstrlen(Name) + 1];
	if (!pFrame->Name)
	{
		return E_FAIL;
	}
	//strcpy(pFrame->Name,Name);
	//�t���[�����i�[
	strcpy_s(pFrame->Name, lstrlen(Name) + 1, Name);
	//�s��̏�����
	D3DXMatrixIdentity(&pFrame->TransformationMatrix);
	D3DXMatrixIdentity(&pFrame->CombinedTransformationMatrix);
	//�ǉ��E�I�t�Z�b�g�֌W������
	pFrame->OffsetID = 0xFFFFFFFF;
	D3DXMatrixIdentity(&(pFrame->OffsetMat));
	//�V�K�t���[���̃��b�V���R���e�i�̏�����
	pFrame->pMeshContainer = NULL;
	//�V�K�t���[���̌Z��t���[���A�h���X�i�[�p�ϐ�������
	pFrame->pFrameSibling = NULL;
	//�V�K�t���[���̎q�t���[���A�h���X�i�[�p�ϐ�������
	pFrame->pFrameFirstChild = NULL;
	//�O���̐V�K�t���[���A�h���X�i�[�p�ϐ��ɁA�쐬�����t���[���̃A�h���X���i�[
	*ppNewFrame = pFrame;

	return S_OK;

}

//HRESULT MyAllocateHierarchy::CreateMeshContainer
//���b�V���R���e�i�[�̍쐬����
HRESULT MyAllocateHierarchy::CreateMeshContainer(
	LPCSTR Name,
	CONST D3DXMESHDATA* pMeshData,
	CONST D3DXMATERIAL* pMaterials,
	CONST D3DXEFFECTINSTANCE* pEffectInstances,
	DWORD NumMaterials,
	CONST DWORD *pAdjacency,
	LPD3DXSKININFO pSkinInfo,
	LPD3DXMESHCONTAINER *ppMeshContainer
	)
{
	//HRESULT hr;
	//���[�J�������p
	MYMESHCONTAINER *pMeshContainer = NULL;
	//���b�V���̖ʂ̐����i�[
	int iFacesAmount;
	//for���[�v�Ŏg�p
	int iMaterial;
	//�ꎞ�I��DirectX�f�o�C�X�擾�p
	LPDIRECT3DDEVICE9 pDevice = NULL;
	//�ꎞ�I�ȃ��b�V���f�[�^�̊i�[�p
	LPD3DXMESH pMesh = NULL;
	//���b�V���R���e�i�i�[�p�ϐ�������
	*ppMeshContainer = NULL;
	//�{�[���̐��i�[�p�ϐ�������
	DWORD dwBoneNum = 0;
	//pMesh��"�O��������"���b�V���A�h���X���i�[
	pMesh = pMeshData->pMesh;
	//���b�V���R���e�i�̈�̓��I�m��
	pMeshContainer = new MYMESHCONTAINER;
	//�����̈�m�ۂɎ��s������
	if (!pMeshContainer->Name)
	{
		return E_OUTOFMEMORY;
	}
	//���b�V���R���e�i��������
	ZeroMemory(pMeshContainer, sizeof(MYMESHCONTAINER));
	//���b�V���R���e�i�̖��O�i�[�p�̈�𓮓I�m��
	pMeshContainer->Name = new TCHAR[lstrlen(Name) + 1];
	//���s���̏���
	if (!pMeshContainer->Name)
	{
		return E_FAIL;
	}
	//�m�ۂ����̈�Ƀ��b�V���R���e�i�����i�[
	strcpy_s(pMeshContainer->Name, lstrlen(Name) + 1, Name);
	//DirectX�f�o�C�X�擾
	pMesh->GetDevice(&pDevice);
	//���b�V���̖ʂ̐����擾
	iFacesAmount = pMesh->GetNumFaces();
	//- ���b�V���̃}�e���A���ݒ� -//
	//���b�V���̃}�e���A�������i�[(�ő��1��)
	pMeshContainer->NumMaterials = max(1, NumMaterials);
	//���b�V���R���e�i�́A�}�e���A���f�[�^�i�[�̈�𓮓I�m��
	pMeshContainer->pMaterials = new D3DXMATERIAL[pMeshContainer->NumMaterials];
	//���b�V���R���e�i�́A�e�N�X�`���f�[�^�i�[�̈�𓮓I�m��
	pMeshContainer->ppTextures = new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];
	//���b�V���R���e�i�́A�ʂ��ƂɎ���3�̗אڐ���񂪊i�[���ꂽDWORD�^�̃A�h���X�i�[�p(�|�C���^)�ϐ�
	pMeshContainer->pAdjacency = new DWORD[iFacesAmount * 3];
	//�̈�m�ۂ̎��s���̏���
	if ((pMeshContainer->pAdjacency == NULL) || (pMeshContainer->pMaterials == NULL))
	{
		return E_FAIL;
	}
	//�O�������̗אڐ��������b�V���R���e�i�Ɋi�[
	memcpy(pMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * iFacesAmount * 3);
	//�e�N�X�`���f�[�^�i�[�p�̈��������(memset���g�p����0�Œ��g�𖄂߂�)
	memset(pMeshContainer->ppTextures, 0, sizeof(LPDIRECT3DTEXTURE9) * pMeshContainer->NumMaterials);
	//�����̃}�e���A������0����Ȃ��ꍇ
	if (NumMaterials > 0)
	{
		//�O�������̃}�e���A���f�[�^�A�h���X�����b�V���R���e�i�Ɋi�[
		memcpy(pMeshContainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL) * NumMaterials);
		//�}�e���A���������[�v������
		for (iMaterial = 0; (DWORD)iMaterial < NumMaterials; iMaterial++)
		{
			//�e�N�X�`���̃t�@�C������NULL�łȂ����(�e�N�X�`���f�[�^�������)
			if (pMeshContainer->pMaterials[iMaterial].pTextureFilename != NULL)
			{
				//�e�N�X�`���̃t�@�C���p�X�ۑ��p�ϐ�
				TCHAR strTexturePath[MAX_PATH];
				//�e�N�X�`���̃t�@�C���p�X��ۑ�(�ēǂݍ��ݎ��ɕK�v)
				strcpy_s(strTexturePath, lstrlen(pMeshContainer->pMaterials[iMaterial].pTextureFilename) + 1, pMeshContainer->pMaterials[iMaterial].pTextureFilename);
				//�e�N�X�`�����̓ǂݍ���
				if (FAILED(D3DXCreateTextureFromFile(pDevice, strTexturePath,
					&pMeshContainer->ppTextures[iMaterial])))
				{
					//���s���̏���
					//�e�N�X�`���t�@�C�����i�[�p
					CHAR TexMeshPass[255];
					//�ǋL
					//�����Ȃ���΁AGraph�t�H���_�𒲂ׂ�
					//���j�t�@�C�����̌������ɁA�K�������Ƀt�@�C���������鎖���m�F���Ă���
					//  strcpy_s��strcat_s���g���悤�ɂ���(���̏ꍇ�́A��ɂ��� 
					//    �e�N�X�`���̃t�@�C��������A����ɂ��̃t�@�C�����̒�����0�łȂ���� �̏���if��)�B
					//  TexMeshPass�ɁAX�t�@�C��������ꏊ�Ɠ����f�B���N�g���ƁA�e�N�X�`���̃t�@�C������
					//  �����������̂��i�[
					// strcpy_s( TexMeshPass, sizeof( TexMeshPass ) , "./../Source/Graph/" );
					strcpy_s(TexMeshPass, sizeof(TexMeshPass), "");
					strcat_s(TexMeshPass, sizeof(TexMeshPass) - strlen(TexMeshPass) - strlen(strTexturePath) - 1, strTexturePath);
					//�e�N�X�`�����̓ǂݍ���
					if (FAILED(D3DXCreateTextureFromFile(pDevice, TexMeshPass,
						&pMeshContainer->ppTextures[iMaterial])))
					{
						pMeshContainer->ppTextures[iMaterial] = NULL;
					}
					//�e�N�X�`���̃t�@�C���p�X��NULL�ɂ���
					pMeshContainer->pMaterials[iMaterial].pTextureFilename = NULL;
				}
			}
		}
	}
	else
	{
		//- �}�e���A���Ȃ��̏ꍇ -//
		//�e�N�X�`���t�@�C������NULL��
		pMeshContainer->pMaterials[0].pTextureFilename = NULL;
		//�}�e���A���f�[�^������(memset���g�p���Ē��g��0�Ŗ��߂�)
		memset(&pMeshContainer->pMaterials[0].MatD3D, 0, sizeof(D3DMATERIAL9));
		//�}�e���A���J���[��0.5�ɐݒ�
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.r = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.g = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.b = 0.5f;
		//�X�y�L������0.5�ɐݒ�(��Őݒ肵���}�e���A���J���[��0.5�̐ݒ���R�s�[)
		pMeshContainer->pMaterials[0].MatD3D.Specular = pMeshContainer->pMaterials[0].MatD3D.Diffuse;
	}
	//���b�V�������i�[(����͒ʏ탁�b�V���Ɗ��S�ɕ����Ă��邽�߂��ׂăX�L�����b�V�����ƂȂ�)
	pMeshContainer->pSkinInfo = pSkinInfo;
	//�Q�ƃJ�E���^
	pSkinInfo->AddRef();
	//�{�[���̐����擾
	dwBoneNum = pSkinInfo->GetNumBones();
	//�t���[��(�{�[��)�P�ʂł̃��[���h�s��i�[�p�̈�̓��I�m��
	pMeshContainer->pBoneOffsetMatrices = new D3DXMATRIX[dwBoneNum];
	//�{�[���̐��������[�v������
	for (DWORD i = 0; i < dwBoneNum; i++)
	{
		//�p�t���[��(�{�[��)�̃I�t�Z�b�g�s����擾���Ċi�[
		memcpy(&pMeshContainer->pBoneOffsetMatrices[i],
			pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(i), sizeof(D3DMATRIX));
	}
	//- �ϊ���� -//
	//���b�V���R���e�i�ɃI���W�i����pMesh�����i�[
	D3DVERTEXELEMENT9 Decl[MAX_FVF_DECL_SIZE];
	pMesh->GetDeclaration(&Decl[0]);
	pMesh->CloneMesh(pMesh->GetOptions(), &Decl[0], pDevice, &pMeshContainer->pOriMesh);
	//���b�V���̃^�C�v���`
	pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;
	//- �Œ�p�C�v���C���`��p�ɕϊ� -//
	//�V�F�[�_�ŕ`�悷��ꍇ�͕ʓr�ϊ����K�v
	//���_�P�ʂł̃u�����h�̏d�݂ƃ{�[���̑g�ݍ��킹�e�[�u����K�������V�������b�V����Ԃ��B
	if (FAILED(pMeshContainer->pSkinInfo->ConvertToBlendedMesh(
		pMeshContainer->pOriMesh, //���̃��b�V���f�[�^�A�h���X
		NULL, //�I�v�V����(���݂͎g���Ă��Ȃ�����NULL�ł���)
		pMeshContainer->pAdjacency, //���̃��b�V���̗אڐ����
		NULL, //�o�̓��b�V���̗אڐ����
		NULL, //�e�ʂ̐V�����C���f�b�N�X�l�i�[�p�ϐ��̃A�h���X
		NULL, //�p���_�̐V�����C���f�b�N�X�l�i�[�p�ϐ��̃A�h���X
		&pMeshContainer->dwWeight, //�{�[���̉e���̈�ʓ�����̍ő吔�i�[�p�ϐ��̃A�h���X
		&pMeshContainer->dwBoneNum, //�{�[���̑g�ݍ��킹�e�[�u���Ɋ܂܂��{�[�����i�[�p�ϐ��̃A�h���X
		&pMeshContainer->pBoneBuffer, //�{�[���̑g�ݍ��킹�e�[�u���ւ̃|�C���^
		&pMeshContainer->MeshData.pMesh //�o�͂���郁�b�V���A�h���X�i�[�p�ϐ��̃A�h���X(�Œ�p�C�v���C���p)
		)))
	{
		return E_FAIL;
	}
	//���[�J���ɐ����������b�V���R���e�i�[���Ăяo�����ɃR�s�[����
	*ppMeshContainer = pMeshContainer;
	//�Q�ƃJ�E���^�𑝂₵���̂Ō��炷
	SAFE_RELEASE(pDevice);
	return S_OK;
}
//HRESULT MY_HIERARCHY::DestroyFrame(LPD3DXFRAME pFrameToFree) 
//�t���[����j������
HRESULT MyAllocateHierarchy::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
	//2�e����h�~
	// if (pFrameToFree == NULL)return S_FALSE;
	SAFE_DELETE_ARRAY(pFrameToFree->Name);
	if (pFrameToFree->pFrameFirstChild)
	{
		DestroyFrame(pFrameToFree->pFrameFirstChild);
	}
	if (pFrameToFree->pFrameSibling)
	{
		DestroyFrame(pFrameToFree->pFrameSibling);
	}
	SAFE_DELETE(pFrameToFree);
	return S_OK;
}

//HRESULT MY_HIERARCHY::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase)
//���b�V���R���e�i�[��j������
HRESULT MyAllocateHierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase)
{
	int iMaterial;
	MYMESHCONTAINER *pMeshContainer = (MYMESHCONTAINER*)pMeshContainerBase;
	SAFE_DELETE_ARRAY(pMeshContainer->Name);
	SAFE_RELEASE(pMeshContainer->pSkinInfo);
	SAFE_DELETE_ARRAY(pMeshContainer->pAdjacency);
	SAFE_DELETE_ARRAY(pMeshContainer->pMaterials);
	SAFE_DELETE_ARRAY(pMeshContainer->ppBoneMatrix);
	if (pMeshContainer->ppTextures != NULL)
	{
		for (iMaterial = 0; (DWORD)iMaterial < pMeshContainer->NumMaterials; iMaterial++)
		{
			//�e�N�X�`�����
			SAFE_RELEASE(pMeshContainer->ppTextures[iMaterial]);
		}
	}
	SAFE_DELETE_ARRAY(pMeshContainer->ppTextures);
	SAFE_RELEASE(pMeshContainer->MeshData.pMesh);
	SAFE_RELEASE(pMeshContainer->pOriMesh);
	if (pMeshContainer->pBoneBuffer != NULL)
	{
		SAFE_RELEASE(pMeshContainer->pBoneBuffer);
		SAFE_DELETE_ARRAY(pMeshContainer->pBoneOffsetMatrices);
	}
	SAFE_DELETE(pMeshContainer);
	pMeshContainerBase = NULL;
	return S_OK;
}