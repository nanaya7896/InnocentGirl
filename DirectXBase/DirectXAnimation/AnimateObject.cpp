#include"AnimateObject.h"

CSkinMesh::CSkinMesh(){
	//�}�e���A���ύX�t���O
	m_MaterialFlg = FALSE;
	//�}�e���A���f�[�^
	ZeroMemory(&m_Material, sizeof(D3DMATERIAL9));
	//�P�ʍs��
	D3DXMatrixIdentity(&(this->m_World));
	//�A�j���[�V�������ԏ�����
	m_AnimeTime = 0;
	//�A�j���[�V�����X�s�[�h������
	m_AnimSpeed = SKIN_ANIME_SPEED; //�Œ�
	//���݂̃A�j���[�V�����g���b�N������
	m_CurrentTrack = 0;
	//�A�j���[�V�����f�[�^�g���b�N������
	//�L���ɂ���
	m_CurrentTrackDesc.Enable = TRUE;
	//�e���x100%
	m_CurrentTrackDesc.Weight = 1;
	//�J�n�ʒu������
	m_CurrentTrackDesc.Position = 0;
	//���x
	m_CurrentTrackDesc.Speed = 1;
}

VOID CSkinMesh::Release(){
	if (m_pFrameRoot != NULL){
		//�{�[���t���[���֌W���
		FreeAnim(m_pFrameRoot);
		//���̑����(�e�N�X�`���̎Q�ƃf�[�^�Ȃ�)�̉��
		m_cHierarchy.DestroyFrame(m_pFrameRoot);
		m_pFrameRoot = NULL;
	}
	//�A�j���[�V�����R���g���[���[���
	SAFE_RELEASE(m_pAnimController);
	//���ׂẴt���[���Q�ƕϐ��̗v�f���폜
	m_FrameArray.clear();
	//���b�V���R���e�i����̃t���[���Q�ƕϐ��̗v�f���폜
	m_IntoMeshFrameArray.clear();
}

HRESULT CSkinMesh::AllocateBoneMatrix(LPD3DXFRAME pFrameRoot, LPD3DXMESHCONTAINER pMeshContainerBase)
{
	MYFRAME *pFrame = NULL;
	DWORD dwBoneNum = 0;
	//���b�V���R���e�i�̌^���I���W�i���̌^�Ƃ��Ĉ���
	//(���b�V���R���e�i�������ɃI���W�i���̌^�Ƃ��č���Ă���̂Ŗ��͂Ȃ����A
	//��{�_�E���L���X�g�͊댯�Ȃ̂ő��p�͔�����ׂ�)
	MYMESHCONTAINER *pMeshContainer = (MYMESHCONTAINER*)pMeshContainerBase;
	//�X�L�����b�V���łȂ����
	if (pMeshContainer->pSkinInfo == NULL)
	{
		return S_OK;
	}
	//�{�[���̐��擾
	dwBoneNum = pMeshContainer->pSkinInfo->GetNumBones();
	//�e�{�[���̃��[���h�s��i�[�p�̈���m��
	SAFE_DELETE(pMeshContainer->ppBoneMatrix);
	pMeshContainer->ppBoneMatrix = new D3DXMATRIX*[dwBoneNum];
	//�{�[���̐��������[�v
	for (DWORD i = 0; i<dwBoneNum; i++)
	{
		//�q�t���[��(�{�[��)�̃A�h���X����������pFrame�Ɋi�[
		pFrame = (MYFRAME*)D3DXFrameFind(pFrameRoot, pMeshContainer->pSkinInfo->GetBoneName(i));
		//�q�t���[�����Ȃ���Ώ������I������
		if (pFrame == NULL)
		{
			return E_FAIL;
		}
		//�e�{�[���̃��[���h�s��i�[�p�ϐ��ɍŏI�s����i�[
		pMeshContainer->ppBoneMatrix[i] = &pFrame->CombinedTransformationMatrix;
	}
	return S_OK;
}

//HRESULT AllocateAllBoneMatrices( THING* pThing,LPD3DXFRAME pFrame )
//
//�{�[���s��̏�����
HRESULT CSkinMesh::AllocateAllBoneMatrices(LPD3DXFRAME pFrameRoot, LPD3DXFRAME pFrame)
{
	//�K�w�̑���(���������m�ۂ������b�V���R���e�i�̈��T������)
	if (pFrame->pMeshContainer != NULL)
	{
		//�{�[���s��̏���������
		if (FAILED(AllocateBoneMatrix(pFrameRoot, pFrame->pMeshContainer)))
		{
			return E_FAIL;
		}
	}
	//�ċN���f����
	if (pFrame->pFrameSibling != NULL)
	{
		if (FAILED(AllocateAllBoneMatrices(pFrameRoot, pFrame->pFrameSibling)))
		{
			return E_FAIL;
		}
	}
	if (pFrame->pFrameFirstChild != NULL)
	{
		if (FAILED(AllocateAllBoneMatrices(pFrameRoot, pFrame->pFrameFirstChild)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}


//VOID RenderMeshContainer(LPDIRECT3DDEVICE9 pDevice,MYMESHCONTAINER* pMeshContainer, MYFRAME* pFrame)
//�t���[�����̂��ꂼ��̃��b�V���������_�����O����
VOID CSkinMesh::RenderMeshContainer(LPDIRECT3DDEVICE9 pDevice, MYMESHCONTAINER* pMeshContainer, MYFRAME* pFrame)
{
	DWORD i, k;
	DWORD dwBlendMatrixNum;
	DWORD dwPrevBoneID;
	LPD3DXBONECOMBINATION pBoneCombination;
	UINT iMatrixIndex;
	D3DXMATRIX mStack;
	//�X�L�����b�V���̕`��
	if (pMeshContainer->pSkinInfo != NULL)
	{
		//�{�[���e�[�u������o�b�t�@�̐擪�A�h���X���擾
		pBoneCombination = reinterpret_cast<LPD3DXBONECOMBINATION>(pMeshContainer->pBoneBuffer->GetBufferPointer());
		//dwPrevBoneID��UINT_MAX�̒l(0xffffffff)���i�[
		dwPrevBoneID = UINT_MAX;
		//�X�L�j���O�v�Z
		for (i = 0; i < pMeshContainer->dwBoneNum; i++)
		{
			dwBlendMatrixNum = 0;
			//�e�����Ă���s�񐔎擾
			for (k = 0; k< pMeshContainer->dwWeight; k++)
			{
				//UINT_MAX(-1)
				if (pBoneCombination[i].BoneId[k] != UINT_MAX)
				{
					//���݉e�����󂯂Ă���{�[���̐�
					dwBlendMatrixNum = k;
				}
			}
			//�W�I���g���u�����f�B���O���g�p���邽�߂ɍs��̌����w��
			pDevice->SetRenderState(D3DRS_VERTEXBLEND, dwBlendMatrixNum);
			//�e�����Ă���s��̌���
			for (k = 0; k < pMeshContainer->dwWeight; k++)
			{
				//iMatrixIndex��1�x�̌Ăяo���ŕ`��o����e�{�[�������ʂ���l���i�[
				//( ����BoneID�z��̒����̓��b�V���̎�ނɂ���ĈقȂ�
				//( �C���f�b�N�X�Ȃ��ł���΁@=�@���_���Ƃ̏d�� �ł���
				// �C���f�b�N�X����ł���΁@=�@�{�[���s��p���b�g�̃G���g����)
				//���݂̃{�[��(i�Ԗ�)����݂�k�Ԗڂ̃{�[��id
				iMatrixIndex = pBoneCombination[i].BoneId[k];
				//�s��̏�񂪂����
				if (iMatrixIndex != UINT_MAX)
				{
					//mStack�ɃI�t�Z�b�g�s��*�{�[���s����i�[
					mStack = pMeshContainer->pBoneOffsetMatrices[iMatrixIndex] * (*pMeshContainer->ppBoneMatrix[iMatrixIndex]);
					//�s��X�^�b�N�Ɋi�[
					pDevice->SetTransform(D3DTS_WORLDMATRIX(k), &mStack);
				}
			}
			D3DMATERIAL9 TmpMat = pMeshContainer->pMaterials[pBoneCombination[i].AttribId].MatD3D;
			TmpMat.Emissive.a = TmpMat.Diffuse.a = TmpMat.Ambient.a = 1.0f;
			pDevice->SetMaterial(&TmpMat);
			pDevice->SetTexture(0, pMeshContainer->ppTextures[pBoneCombination[i].AttribId]);
			//dwPrevBoneID�ɑ����e�[�u���̎��ʎq���i�[
			dwPrevBoneID = pBoneCombination[i].AttribId;
			//���b�V���̕`��
			pMeshContainer->MeshData.pMesh->DrawSubset(i);
		}
	}
	//�ʏ탁�b�V���̏ꍇ
	else
	{
		MessageBox(NULL, "�X�L�����b�V��X�t�@�C���̕`��Ɏ��s���܂����B", NULL, MB_OK);
		exit(EOF);
	}
}

//
//VOID DrawFrame(LPDIRECT3DDEVICE9 pDevice,LPD3DXFRAME pFrameBase)
//�t���[���������_�����O����B
VOID CSkinMesh::DrawFrame(LPDIRECT3DDEVICE9 pDevice, LPD3DXFRAME pFrameBase)
{
	MYFRAME* pFrame = (MYFRAME*)pFrameBase;
	MYMESHCONTAINER* pMeshContainer = (MYMESHCONTAINER*)pFrame->pMeshContainer;
	while (pMeshContainer != NULL)
	{
		//SHADER_KIND a = GetpShader()->GetShaderKind();
		////�V�F�[�_���g�p���Ă���̂Ȃ��p�̕`��֐��ɔ�΂�
		//if( GetpShader() != NULL && GetpShader()->GetShaderKind() == SHADER_KIND_LAMBERT ){
		// ShaderDraw( pDevice, ControlNum, pMeshContainer, pFrame ); 
		//}else{
		RenderMeshContainer(pDevice, pMeshContainer, pFrame);
		// }
		//���̃��b�V���R���e�i�փA�N�e�B�u���ڂ�
		pMeshContainer = (MYMESHCONTAINER*)pMeshContainer->pNextMeshContainer;
	}
	if (pFrame->pFrameSibling != NULL)
	{
		DrawFrame(pDevice, pFrame->pFrameSibling);
	}
	if (pFrame->pFrameFirstChild != NULL)
	{
		DrawFrame(pDevice, pFrame->pFrameFirstChild);
	}
}

//
//VOID UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix)
//�t���[�����̃��b�V�����Ƀ��[���h�ϊ��s����X�V����
VOID CSkinMesh::UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix)
{
	MYFRAME *pFrame = (MYFRAME*)pFrameBase;
	if (pParentMatrix != NULL)
	{
		//CombinedTransformationMatrix�ɍŏI�s����i�[
		D3DXMatrixMultiply(&pFrame->CombinedTransformationMatrix, &pFrame->TransformationMatrix, pParentMatrix);
	}
	else
	{
		//CombinedTransformationMatrix�ɍŏI�s����i�[
		pFrame->CombinedTransformationMatrix = pFrame->TransformationMatrix;
	}
	if (pFrame->pFrameSibling != NULL)
	{
		UpdateFrameMatrices(pFrame->pFrameSibling, pParentMatrix);
	}
	if (pFrame->pFrameFirstChild != NULL)
	{
		UpdateFrameMatrices(pFrame->pFrameFirstChild, &pFrame->CombinedTransformationMatrix);
	}
}

//�S�Ă̊K�w�t���[�����������
VOID CSkinMesh::FreeAnim(LPD3DXFRAME pFrame)
{
	if (pFrame->pMeshContainer != NULL){
		m_cHierarchy.DestroyMeshContainer(pFrame->pMeshContainer);
		pFrame->pMeshContainer = NULL;
	}
	if (pFrame->pFrameSibling != NULL)
		FreeAnim(pFrame->pFrameSibling);
	if (pFrame->pFrameFirstChild != NULL)
		FreeAnim(pFrame->pFrameFirstChild);
}

HRESULT CSkinMesh::Init(LPDIRECT3DDEVICE9 lpD3DDevice, LPSTR pMeshPass)
{
	CHAR TmpMeshPass[255];
	strcpy_s(TmpMeshPass, sizeof(TmpMeshPass) - 1, pMeshPass);
	// X�t�@�C������A�j���[�V�������b�V����ǂݍ��ݍ쐬����
	if (FAILED(
		D3DXLoadMeshHierarchyFromX(TmpMeshPass, D3DXMESH_MANAGED, lpD3DDevice, &m_cHierarchy,
		NULL,
		&m_pFrameRoot,
		&m_pAnimController)))
	{
		MessageBox(NULL, "X�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", TmpMeshPass, MB_OK);
		return E_FAIL;
	}

	
	//�{�[���s�񏉊���
	AllocateAllBoneMatrices(m_pFrameRoot, m_pFrameRoot);
	//�A�j���[�V�����g���b�N�̎擾
	for (DWORD i = 0; i<m_pAnimController->GetNumAnimationSets(); i++)
	{
		//�A�j���[�V�����擾
		m_pAnimController->GetAnimationSet(i, &(m_pAnimSet[i]));
	}
	//���ׂẴt���[���Q�ƕϐ��̐���
	m_FrameArray.clear();
	m_IntoMeshFrameArray.clear();
	CreateFrameArray(m_pFrameRoot);
	//�t���[���z��ɃI�t�Z�b�g���쐬
	for (DWORD i = 0; i<m_IntoMeshFrameArray.size(); i++)
	{
		MYMESHCONTAINER* pMyMeshContainer = (MYMESHCONTAINER*)m_IntoMeshFrameArray[i]->pMeshContainer;
		while (pMyMeshContainer)
		{
			//�X�L�����
			if (pMyMeshContainer->pSkinInfo)
			{
				DWORD cBones = pMyMeshContainer->pSkinInfo->GetNumBones();
				for (DWORD iBone = 0; iBone<cBones; iBone++){
					//�t���[�������瓯�����O�̃t���[��������
					for (DWORD Idx = 0; Idx<m_FrameArray.size(); Idx++)
					{
						if (strcmp(pMyMeshContainer->pSkinInfo->GetBoneName(iBone), m_FrameArray[Idx]->Name) == 0)
						{
							pMyMeshContainer->BoneFrameArray.push_back(m_FrameArray[Idx]);
							//Offset�s��
							m_FrameArray[Idx]->OffsetMat = *(pMyMeshContainer->pSkinInfo->GetBoneOffsetMatrix(iBone));
							m_FrameArray[Idx]->OffsetID = Idx;
							break;
						}
					}
				}
			}
			//����
			pMyMeshContainer = (MYMESHCONTAINER *)pMyMeshContainer->pNextMeshContainer;
		}
	}
	return S_OK;
}

//���ׂẴt���[���|�C���^�i�[�����֐�
VOID CSkinMesh::CreateFrameArray(LPD3DXFRAME _pFrame){
	if (_pFrame == NULL){ return; }
	//�t���[���A�h���X�i�[
	MYFRAME* pMyFrame = (MYFRAME*)_pFrame;
	m_FrameArray.push_back(pMyFrame);
	//���b�V���R���e�i������ꍇ��IntoMeshFrameArray�ɃA�h���X���i�[
	if (pMyFrame->pMeshContainer != NULL){
		m_IntoMeshFrameArray.push_back(pMyFrame);
	}
	//�q�t���[������
	if (pMyFrame->pFrameFirstChild != NULL){
		CreateFrameArray(pMyFrame->pFrameFirstChild);
	}
	//�Z��t���[������
	if (pMyFrame->pFrameSibling != NULL){
		CreateFrameArray(pMyFrame->pFrameSibling);
	}
}

//- �X�V���� -//
VOID CSkinMesh::Update(D3DXMATRIX _World){
	//�������ςȂ��ɂ��A���؂�ւ��h�~
	static bool PushFlg = false; //�����ł͉��Ńt���O���g�p���邪�A�{���̓����o�ϐ��Ȃǂɂ���
	//�A�j���[�V�����ύX�`�F�b�N
	if ((GetAsyncKeyState(VK_LEFT) & 0x8000) || (GetAsyncKeyState(VK_RIGHT) & 0x8000)){
		if (GetAsyncKeyState(VK_LEFT) & 0x8000){
			if (PushFlg == false){
				int Num = GetAnimTrack() - 1;
				if (Num < 0)Num = 0;
				ChangeAnim(Num);
			}
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000){
			if (PushFlg == false){
				int Num = GetAnimTrack() + 1;
				if ((DWORD)Num > m_pAnimController->GetNumAnimationSets())Num = m_pAnimController->GetNumAnimationSets();
				ChangeAnim(Num);
			}
		}
		PushFlg = true;
	}
	else{
		PushFlg = false;
	}
	//�}�g���b�N�X�s�񔽉f
	m_World = _World;
	//�A�j���[�V�������Ԃ��X�V
	m_AnimeTime++;
}

//�X�L�����b�V���̕`��
VOID CSkinMesh::Draw(LPDIRECT3DDEVICE9 lpD3DDevice){
	//���݂̃A�j���[�V�����ԍ���K��
	m_pAnimController->SetTrackAnimationSet(0, m_pAnimSet[m_CurrentTrack]);
	//0(�Đ�����)�g���b�N����g���b�N�f�X�N���Z�b�g����
	m_pAnimController->SetTrackDesc(0, &(m_CurrentTrackDesc));
	//�A�j���[�V�������ԃf�[�^�̍X�V
	m_pAnimController->AdvanceTime(m_AnimSpeed, NULL);
	//�A�j���[�V�����f�[�^���X�V
	UpdateFrameMatrices(m_pFrameRoot, &m_World);
	//�A�j���[�V�����`��
	DrawFrame(lpD3DDevice, m_pFrameRoot);
	//0(�Đ�����)�g���b�N����X�V�����g���b�N�f�X�N���擾����
	m_pAnimController->GetTrackDesc(0, &m_CurrentTrackDesc);
}

//�I�u�W�F�N�g�̃A�j���[�V�����ύX( �ύX����A�j���[�V�����ԍ� )
VOID CSkinMesh::ChangeAnim(DWORD _NewAnimNum){
	//�V�K�A�j���[�V�����ɕύX
	m_CurrentTrack = _NewAnimNum;
	//�A�j���[�V�����^�C����������
	m_AnimeTime = 0;
	//�A�j���[�V�������ŏ��̈ʒu����Đ�������
	m_pAnimController->GetTrackDesc(0, &m_CurrentTrackDesc);
	m_CurrentTrackDesc.Position = 0;
	m_pAnimController->SetTrackDesc(0, &m_CurrentTrackDesc);
}

//�Ώۂ̃{�[��������
MYFRAME* CSkinMesh::SearchBoneFrame(LPSTR _BoneName, D3DXFRAME* _pFrame){
	MYFRAME* pFrame = (MYFRAME*)_pFrame;
	if (strcmp(pFrame->Name, _BoneName) == 0){
		return pFrame;
	}
	if (_pFrame->pFrameSibling != NULL)
	{
		pFrame = SearchBoneFrame(_BoneName, _pFrame->pFrameSibling);
		if (pFrame != NULL){
			return pFrame;
		}
	}
	if (_pFrame->pFrameFirstChild != NULL)
	{
		pFrame = SearchBoneFrame(_BoneName, _pFrame->pFrameFirstChild);
		if (pFrame != NULL){
			return pFrame;
		}
	}
	return NULL;
}

//�{�[���̃}�g���b�N�X�擾( �{�[���̖��O )
D3DXMATRIX CSkinMesh::GetBoneMatrix(LPSTR _BoneName){
	MYFRAME* pFrame = SearchBoneFrame(_BoneName, m_pFrameRoot);
	//�{�[�����������
	if (pFrame != NULL){
		//�{�[���s���Ԃ�
		return pFrame->CombinedTransformationMatrix;
	}
	//�{�[����������Ȃ����
	else{
		//�P�ʍs���Ԃ�
		D3DXMATRIX TmpMatrix;
		D3DXMatrixIdentity(&TmpMatrix);
		return TmpMatrix;
	}
}

//�{�[���̃}�g���b�N�X�|�C���^�擾( �{�[���̖��O )
D3DXMATRIX* CSkinMesh::GetpBoneMatrix(LPSTR _BoneName){
	/////////////////////////////////////
	//���ӁjRokDeBone�p�ɐݒ�(�Ώۃ{�[���̈��̍s����Ƃ��Ă���)
	MYFRAME* pFrame = SearchBoneFrame(_BoneName, m_pFrameRoot);
	//�{�[�����������
	if (pFrame != NULL){
		return &pFrame->CombinedTransformationMatrix;
	}
	//�{�[����������Ȃ����
	else{
		//NULL��Ԃ�
		return NULL;
	}
}