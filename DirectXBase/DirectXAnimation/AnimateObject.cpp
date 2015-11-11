#include"AnimateObject.h"

CSkinMesh::CSkinMesh(){
	//マテリアル変更フラグ
	m_MaterialFlg = FALSE;
	//マテリアルデータ
	ZeroMemory(&m_Material, sizeof(D3DMATERIAL9));
	//単位行列化
	D3DXMatrixIdentity(&(this->m_World));
	//アニメーション時間初期化
	m_AnimeTime = 0;
	//アニメーションスピード初期化
	m_AnimSpeed = SKIN_ANIME_SPEED; //固定
	//現在のアニメーショントラック初期化
	m_CurrentTrack = 0;
	//アニメーションデータトラック初期化
	//有効にする
	m_CurrentTrackDesc.Enable = TRUE;
	//影響度100%
	m_CurrentTrackDesc.Weight = 1;
	//開始位置初期化
	m_CurrentTrackDesc.Position = 0;
	//速度
	m_CurrentTrackDesc.Speed = 1;
}

VOID CSkinMesh::Release(){
	if (m_pFrameRoot != NULL){
		//ボーンフレーム関係解放
		FreeAnim(m_pFrameRoot);
		//その他情報(テクスチャの参照データなど)の解放
		m_cHierarchy.DestroyFrame(m_pFrameRoot);
		m_pFrameRoot = NULL;
	}
	//アニメーションコントローラー解放
	SAFE_RELEASE(m_pAnimController);
	//すべてのフレーム参照変数の要素を削除
	m_FrameArray.clear();
	//メッシュコンテナありのフレーム参照変数の要素を削除
	m_IntoMeshFrameArray.clear();
}

HRESULT CSkinMesh::AllocateBoneMatrix(LPD3DXFRAME pFrameRoot, LPD3DXMESHCONTAINER pMeshContainerBase)
{
	MYFRAME *pFrame = NULL;
	DWORD dwBoneNum = 0;
	//メッシュコンテナの型をオリジナルの型として扱う
	//(メッシュコンテナ生成時にオリジナルの型として作っているので問題はないが、
	//基本ダウンキャストは危険なので多用は避けるべき)
	MYMESHCONTAINER *pMeshContainer = (MYMESHCONTAINER*)pMeshContainerBase;
	//スキンメッシュでなければ
	if (pMeshContainer->pSkinInfo == NULL)
	{
		return S_OK;
	}
	//ボーンの数取得
	dwBoneNum = pMeshContainer->pSkinInfo->GetNumBones();
	//各ボーンのワールド行列格納用領域を確保
	SAFE_DELETE(pMeshContainer->ppBoneMatrix);
	pMeshContainer->ppBoneMatrix = new D3DXMATRIX*[dwBoneNum];
	//ボーンの数だけループ
	for (DWORD i = 0; i<dwBoneNum; i++)
	{
		//子フレーム(ボーン)のアドレスを検索してpFrameに格納
		pFrame = (MYFRAME*)D3DXFrameFind(pFrameRoot, pMeshContainer->pSkinInfo->GetBoneName(i));
		//子フレームがなければ処理を終了する
		if (pFrame == NULL)
		{
			return E_FAIL;
		}
		//各ボーンのワールド行列格納用変数に最終行列を格納
		pMeshContainer->ppBoneMatrix[i] = &pFrame->CombinedTransformationMatrix;
	}
	return S_OK;
}

//HRESULT AllocateAllBoneMatrices( THING* pThing,LPD3DXFRAME pFrame )
//
//ボーン行列の初期化
HRESULT CSkinMesh::AllocateAllBoneMatrices(LPD3DXFRAME pFrameRoot, LPD3DXFRAME pFrame)
{
	//階層の走査(メモリを確保したメッシュコンテナ領域を探す処理)
	if (pFrame->pMeshContainer != NULL)
	{
		//ボーン行列の初期化処理
		if (FAILED(AllocateBoneMatrix(pFrameRoot, pFrame->pMeshContainer)))
		{
			return E_FAIL;
		}
	}
	//再起判断処理
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
//フレーム内のそれぞれのメッシュをレンダリングする
VOID CSkinMesh::RenderMeshContainer(LPDIRECT3DDEVICE9 pDevice, MYMESHCONTAINER* pMeshContainer, MYFRAME* pFrame)
{
	DWORD i, k;
	DWORD dwBlendMatrixNum;
	DWORD dwPrevBoneID;
	LPD3DXBONECOMBINATION pBoneCombination;
	UINT iMatrixIndex;
	D3DXMATRIX mStack;
	//スキンメッシュの描画
	if (pMeshContainer->pSkinInfo != NULL)
	{
		//ボーンテーブルからバッファの先頭アドレスを取得
		pBoneCombination = reinterpret_cast<LPD3DXBONECOMBINATION>(pMeshContainer->pBoneBuffer->GetBufferPointer());
		//dwPrevBoneIDにUINT_MAXの値(0xffffffff)を格納
		dwPrevBoneID = UINT_MAX;
		//スキニング計算
		for (i = 0; i < pMeshContainer->dwBoneNum; i++)
		{
			dwBlendMatrixNum = 0;
			//影響している行列数取得
			for (k = 0; k< pMeshContainer->dwWeight; k++)
			{
				//UINT_MAX(-1)
				if (pBoneCombination[i].BoneId[k] != UINT_MAX)
				{
					//現在影響を受けているボーンの数
					dwBlendMatrixNum = k;
				}
			}
			//ジオメトリブレンディングを使用するために行列の個数を指定
			pDevice->SetRenderState(D3DRS_VERTEXBLEND, dwBlendMatrixNum);
			//影響している行列の検索
			for (k = 0; k < pMeshContainer->dwWeight; k++)
			{
				//iMatrixIndexに1度の呼び出しで描画出来る各ボーンを識別する値を格納
				//( このBoneID配列の長さはメッシュの種類によって異なる
				//( インデックスなしであれば　=　頂点ごとの重み であり
				// インデックスありであれば　=　ボーン行列パレットのエントリ数)
				//現在のボーン(i番目)からみてk番目のボーンid
				iMatrixIndex = pBoneCombination[i].BoneId[k];
				//行列の情報があれば
				if (iMatrixIndex != UINT_MAX)
				{
					//mStackにオフセット行列*ボーン行列を格納
					mStack = pMeshContainer->pBoneOffsetMatrices[iMatrixIndex] * (*pMeshContainer->ppBoneMatrix[iMatrixIndex]);
					//行列スタックに格納
					pDevice->SetTransform(D3DTS_WORLDMATRIX(k), &mStack);
				}
			}
			D3DMATERIAL9 TmpMat = pMeshContainer->pMaterials[pBoneCombination[i].AttribId].MatD3D;
			TmpMat.Emissive.a = TmpMat.Diffuse.a = TmpMat.Ambient.a = 1.0f;
			pDevice->SetMaterial(&TmpMat);
			pDevice->SetTexture(0, pMeshContainer->ppTextures[pBoneCombination[i].AttribId]);
			//dwPrevBoneIDに属性テーブルの識別子を格納
			dwPrevBoneID = pBoneCombination[i].AttribId;
			//メッシュの描画
			pMeshContainer->MeshData.pMesh->DrawSubset(i);
		}
	}
	//通常メッシュの場合
	else
	{
		MessageBox(NULL, "スキンメッシュXファイルの描画に失敗しました。", NULL, MB_OK);
		exit(EOF);
	}
}

//
//VOID DrawFrame(LPDIRECT3DDEVICE9 pDevice,LPD3DXFRAME pFrameBase)
//フレームをレンダリングする。
VOID CSkinMesh::DrawFrame(LPDIRECT3DDEVICE9 pDevice, LPD3DXFRAME pFrameBase)
{
	MYFRAME* pFrame = (MYFRAME*)pFrameBase;
	MYMESHCONTAINER* pMeshContainer = (MYMESHCONTAINER*)pFrame->pMeshContainer;
	while (pMeshContainer != NULL)
	{
		//SHADER_KIND a = GetpShader()->GetShaderKind();
		////シェーダを使用しているのなら専用の描画関数に飛ばす
		//if( GetpShader() != NULL && GetpShader()->GetShaderKind() == SHADER_KIND_LAMBERT ){
		// ShaderDraw( pDevice, ControlNum, pMeshContainer, pFrame ); 
		//}else{
		RenderMeshContainer(pDevice, pMeshContainer, pFrame);
		// }
		//次のメッシュコンテナへアクティブを移す
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
//フレーム内のメッシュ毎にワールド変換行列を更新する
VOID CSkinMesh::UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix)
{
	MYFRAME *pFrame = (MYFRAME*)pFrameBase;
	if (pParentMatrix != NULL)
	{
		//CombinedTransformationMatrixに最終行列を格納
		D3DXMatrixMultiply(&pFrame->CombinedTransformationMatrix, &pFrame->TransformationMatrix, pParentMatrix);
	}
	else
	{
		//CombinedTransformationMatrixに最終行列を格納
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

//全ての階層フレームを解放する
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
	// Xファイルからアニメーションメッシュを読み込み作成する
	if (FAILED(
		D3DXLoadMeshHierarchyFromX(TmpMeshPass, D3DXMESH_MANAGED, lpD3DDevice, &m_cHierarchy,
		NULL,
		&m_pFrameRoot,
		&m_pAnimController)))
	{
		MessageBox(NULL, "Xファイルの読み込みに失敗しました", TmpMeshPass, MB_OK);
		return E_FAIL;
	}

	
	//ボーン行列初期化
	AllocateAllBoneMatrices(m_pFrameRoot, m_pFrameRoot);
	//アニメーショントラックの取得
	for (DWORD i = 0; i<m_pAnimController->GetNumAnimationSets(); i++)
	{
		//アニメーション取得
		m_pAnimController->GetAnimationSet(i, &(m_pAnimSet[i]));
	}
	//すべてのフレーム参照変数の生成
	m_FrameArray.clear();
	m_IntoMeshFrameArray.clear();
	CreateFrameArray(m_pFrameRoot);
	//フレーム配列にオフセット情報作成
	for (DWORD i = 0; i<m_IntoMeshFrameArray.size(); i++)
	{
		MYMESHCONTAINER* pMyMeshContainer = (MYMESHCONTAINER*)m_IntoMeshFrameArray[i]->pMeshContainer;
		while (pMyMeshContainer)
		{
			//スキン情報
			if (pMyMeshContainer->pSkinInfo)
			{
				DWORD cBones = pMyMeshContainer->pSkinInfo->GetNumBones();
				for (DWORD iBone = 0; iBone<cBones; iBone++){
					//フレーム内から同じ名前のフレームを検索
					for (DWORD Idx = 0; Idx<m_FrameArray.size(); Idx++)
					{
						if (strcmp(pMyMeshContainer->pSkinInfo->GetBoneName(iBone), m_FrameArray[Idx]->Name) == 0)
						{
							pMyMeshContainer->BoneFrameArray.push_back(m_FrameArray[Idx]);
							//Offset行列
							m_FrameArray[Idx]->OffsetMat = *(pMyMeshContainer->pSkinInfo->GetBoneOffsetMatrix(iBone));
							m_FrameArray[Idx]->OffsetID = Idx;
							break;
						}
					}
				}
			}
			//次へ
			pMyMeshContainer = (MYMESHCONTAINER *)pMyMeshContainer->pNextMeshContainer;
		}
	}
	return S_OK;
}

//すべてのフレームポインタ格納処理関数
VOID CSkinMesh::CreateFrameArray(LPD3DXFRAME _pFrame){
	if (_pFrame == NULL){ return; }
	//フレームアドレス格納
	MYFRAME* pMyFrame = (MYFRAME*)_pFrame;
	m_FrameArray.push_back(pMyFrame);
	//メッシュコンテナがある場合はIntoMeshFrameArrayにアドレスを格納
	if (pMyFrame->pMeshContainer != NULL){
		m_IntoMeshFrameArray.push_back(pMyFrame);
	}
	//子フレーム検索
	if (pMyFrame->pFrameFirstChild != NULL){
		CreateFrameArray(pMyFrame->pFrameFirstChild);
	}
	//兄弟フレーム検索
	if (pMyFrame->pFrameSibling != NULL){
		CreateFrameArray(pMyFrame->pFrameSibling);
	}
}

//- 更新処理 -//
VOID CSkinMesh::Update(D3DXMATRIX _World){
	//押しっぱなしによる連続切り替え防止
	static bool PushFlg = false; //ここでは仮でフラグを使用するが、本来はメンバ変数などにする
	//アニメーション変更チェック
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
	//マトリックス行列反映
	m_World = _World;
	//アニメーション時間を更新
	m_AnimeTime++;
}

//スキンメッシュの描画
VOID CSkinMesh::Draw(LPDIRECT3DDEVICE9 lpD3DDevice){
	//現在のアニメーション番号を適応
	m_pAnimController->SetTrackAnimationSet(0, m_pAnimSet[m_CurrentTrack]);
	//0(再生中の)トラックからトラックデスクをセットする
	m_pAnimController->SetTrackDesc(0, &(m_CurrentTrackDesc));
	//アニメーション時間データの更新
	m_pAnimController->AdvanceTime(m_AnimSpeed, NULL);
	//アニメーションデータを更新
	UpdateFrameMatrices(m_pFrameRoot, &m_World);
	//アニメーション描画
	DrawFrame(lpD3DDevice, m_pFrameRoot);
	//0(再生中の)トラックから更新したトラックデスクを取得する
	m_pAnimController->GetTrackDesc(0, &m_CurrentTrackDesc);
}

//オブジェクトのアニメーション変更( 変更するアニメーション番号 )
VOID CSkinMesh::ChangeAnim(DWORD _NewAnimNum){
	//新規アニメーションに変更
	m_CurrentTrack = _NewAnimNum;
	//アニメーションタイムを初期化
	m_AnimeTime = 0;
	//アニメーションを最初の位置から再生させる
	m_pAnimController->GetTrackDesc(0, &m_CurrentTrackDesc);
	m_CurrentTrackDesc.Position = 0;
	m_pAnimController->SetTrackDesc(0, &m_CurrentTrackDesc);
}

//対象のボーンを検索
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

//ボーンのマトリックス取得( ボーンの名前 )
D3DXMATRIX CSkinMesh::GetBoneMatrix(LPSTR _BoneName){
	MYFRAME* pFrame = SearchBoneFrame(_BoneName, m_pFrameRoot);
	//ボーンが見つかれば
	if (pFrame != NULL){
		//ボーン行列を返す
		return pFrame->CombinedTransformationMatrix;
	}
	//ボーンが見つからなければ
	else{
		//単位行列を返す
		D3DXMATRIX TmpMatrix;
		D3DXMatrixIdentity(&TmpMatrix);
		return TmpMatrix;
	}
}

//ボーンのマトリックスポインタ取得( ボーンの名前 )
D3DXMATRIX* CSkinMesh::GetpBoneMatrix(LPSTR _BoneName){
	/////////////////////////////////////
	//注意）RokDeBone用に設定(対象ボーンの一つ先の行列をとってくる)
	MYFRAME* pFrame = SearchBoneFrame(_BoneName, m_pFrameRoot);
	//ボーンが見つかれば
	if (pFrame != NULL){
		return &pFrame->CombinedTransformationMatrix;
	}
	//ボーンが見つからなければ
	else{
		//NULLを返す
		return NULL;
	}
}