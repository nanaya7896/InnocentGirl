#include"MyAllocatehierarchy.h"

//フレームを作成する
HRESULT MyAllocateHierarchy::CreateFrame(LPCTSTR Name, LPD3DXFRAME* ppNewFrame)
{
	HRESULT hr = S_OK;
	MYFRAME *pFrame;
	//新しいフレームアドレス格納用変数を初期化
	*ppNewFrame = NULL;
	//フレーム領域確保
	pFrame = new MYFRAME;
	//領域確保の失敗時の処理
	if (pFrame == NULL)
	{
		return E_OUTOFMEMORY;
	}
	//フレーム名格納用領域確保
	pFrame = new MYFRAME;
	//領域確保の失敗時の処理
	if (pFrame == NULL)
	{
		return E_OUTOFMEMORY;
	}
	//フレーム名格納用領域確保
	pFrame->Name = new TCHAR[lstrlen(Name) + 1];
	if (!pFrame->Name)
	{
		return E_FAIL;
	}
	//strcpy(pFrame->Name,Name);
	//フレーム名格納
	strcpy_s(pFrame->Name, lstrlen(Name) + 1, Name);
	//行列の初期化
	D3DXMatrixIdentity(&pFrame->TransformationMatrix);
	D3DXMatrixIdentity(&pFrame->CombinedTransformationMatrix);
	//追加・オフセット関係初期化
	pFrame->OffsetID = 0xFFFFFFFF;
	D3DXMatrixIdentity(&(pFrame->OffsetMat));
	//新規フレームのメッシュコンテナの初期化
	pFrame->pMeshContainer = NULL;
	//新規フレームの兄弟フレームアドレス格納用変数初期化
	pFrame->pFrameSibling = NULL;
	//新規フレームの子フレームアドレス格納用変数初期化
	pFrame->pFrameFirstChild = NULL;
	//外部の新規フレームアドレス格納用変数に、作成したフレームのアドレスを格納
	*ppNewFrame = pFrame;

	return S_OK;

}

//HRESULT MyAllocateHierarchy::CreateMeshContainer
//メッシュコンテナーの作成する
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
	//ローカル生成用
	MYMESHCONTAINER *pMeshContainer = NULL;
	//メッシュの面の数を格納
	int iFacesAmount;
	//forループで使用
	int iMaterial;
	//一時的にDirectXデバイス取得用
	LPDIRECT3DDEVICE9 pDevice = NULL;
	//一時的なメッシュデータの格納用
	LPD3DXMESH pMesh = NULL;
	//メッシュコンテナ格納用変数初期化
	*ppMeshContainer = NULL;
	//ボーンの数格納用変数初期化
	DWORD dwBoneNum = 0;
	//pMeshに"外部引数の"メッシュアドレスを格納
	pMesh = pMeshData->pMesh;
	//メッシュコンテナ領域の動的確保
	pMeshContainer = new MYMESHCONTAINER;
	//もし領域確保に失敗したら
	if (!pMeshContainer->Name)
	{
		return E_OUTOFMEMORY;
	}
	//メッシュコンテナを初期化
	ZeroMemory(pMeshContainer, sizeof(MYMESHCONTAINER));
	//メッシュコンテナの名前格納用領域を動的確保
	pMeshContainer->Name = new TCHAR[lstrlen(Name) + 1];
	//失敗時の処理
	if (!pMeshContainer->Name)
	{
		return E_FAIL;
	}
	//確保した領域にメッシュコンテナ名を格納
	strcpy_s(pMeshContainer->Name, lstrlen(Name) + 1, Name);
	//DirectXデバイス取得
	pMesh->GetDevice(&pDevice);
	//メッシュの面の数を取得
	iFacesAmount = pMesh->GetNumFaces();
	//- メッシュのマテリアル設定 -//
	//メッシュのマテリアル数を格納(最大で1つ)
	pMeshContainer->NumMaterials = max(1, NumMaterials);
	//メッシュコンテナの、マテリアルデータ格納領域を動的確保
	pMeshContainer->pMaterials = new D3DXMATERIAL[pMeshContainer->NumMaterials];
	//メッシュコンテナの、テクスチャデータ格納領域を動的確保
	pMeshContainer->ppTextures = new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];
	//メッシュコンテナの、面ごとに持つ3つの隣接性情報が格納されたDWORD型のアドレス格納用(ポインタ)変数
	pMeshContainer->pAdjacency = new DWORD[iFacesAmount * 3];
	//領域確保の失敗時の処理
	if ((pMeshContainer->pAdjacency == NULL) || (pMeshContainer->pMaterials == NULL))
	{
		return E_FAIL;
	}
	//外部引数の隣接性情報をメッシュコンテナに格納
	memcpy(pMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * iFacesAmount * 3);
	//テクスチャデータ格納用領域を初期化(memsetを使用して0で中身を埋める)
	memset(pMeshContainer->ppTextures, 0, sizeof(LPDIRECT3DTEXTURE9) * pMeshContainer->NumMaterials);
	//引数のマテリアル数が0じゃない場合
	if (NumMaterials > 0)
	{
		//外部引数のマテリアルデータアドレスをメッシュコンテナに格納
		memcpy(pMeshContainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL) * NumMaterials);
		//マテリアル数分ループさせる
		for (iMaterial = 0; (DWORD)iMaterial < NumMaterials; iMaterial++)
		{
			//テクスチャのファイル名がNULLでなければ(テクスチャデータがあれば)
			if (pMeshContainer->pMaterials[iMaterial].pTextureFilename != NULL)
			{
				//テクスチャのファイルパス保存用変数
				TCHAR strTexturePath[MAX_PATH];
				//テクスチャのファイルパスを保存(再読み込み時に必要)
				strcpy_s(strTexturePath, lstrlen(pMeshContainer->pMaterials[iMaterial].pTextureFilename) + 1, pMeshContainer->pMaterials[iMaterial].pTextureFilename);
				//テクスチャ情報の読み込み
				if (FAILED(D3DXCreateTextureFromFile(pDevice, strTexturePath,
					&pMeshContainer->ppTextures[iMaterial])))
				{
					//失敗時の処理
					//テクスチャファイル名格納用
					CHAR TexMeshPass[255];
					//追記
					//もしなければ、Graphフォルダを調べる
					//注）ファイル名の結合時に、必ず両方にファイル名がある事を確認してから
					//  strcpy_sとstrcat_sを使うようにする(この場合は、上にある 
					//    テクスチャのファイルがあり、さらにそのファイル名の長さが0でなければ の所のif文)。
					//  TexMeshPassに、Xファイルがある場所と同じディレクトリと、テクスチャのファイル名を
					//  結合したものを格納
					// strcpy_s( TexMeshPass, sizeof( TexMeshPass ) , "./../Source/Graph/" );
					strcpy_s(TexMeshPass, sizeof(TexMeshPass), "");
					strcat_s(TexMeshPass, sizeof(TexMeshPass) - strlen(TexMeshPass) - strlen(strTexturePath) - 1, strTexturePath);
					//テクスチャ情報の読み込み
					if (FAILED(D3DXCreateTextureFromFile(pDevice, TexMeshPass,
						&pMeshContainer->ppTextures[iMaterial])))
					{
						pMeshContainer->ppTextures[iMaterial] = NULL;
					}
					//テクスチャのファイルパスをNULLにする
					pMeshContainer->pMaterials[iMaterial].pTextureFilename = NULL;
				}
			}
		}
	}
	else
	{
		//- マテリアルなしの場合 -//
		//テクスチャファイル名をNULLに
		pMeshContainer->pMaterials[0].pTextureFilename = NULL;
		//マテリアルデータ初期化(memsetを使用して中身を0で埋める)
		memset(&pMeshContainer->pMaterials[0].MatD3D, 0, sizeof(D3DMATERIAL9));
		//マテリアルカラーを0.5に設定
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.r = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.g = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.b = 0.5f;
		//スペキュラも0.5に設定(上で設定したマテリアルカラーの0.5の設定をコピー)
		pMeshContainer->pMaterials[0].MatD3D.Specular = pMeshContainer->pMaterials[0].MatD3D.Diffuse;
	}
	//メッシュ情報を格納(今回は通常メッシュと完全に分けているためすべてスキンメッシュ情報となる)
	pMeshContainer->pSkinInfo = pSkinInfo;
	//参照カウンタ
	pSkinInfo->AddRef();
	//ボーンの数を取得
	dwBoneNum = pSkinInfo->GetNumBones();
	//フレーム(ボーン)単位でのワールド行列格納用領域の動的確保
	pMeshContainer->pBoneOffsetMatrices = new D3DXMATRIX[dwBoneNum];
	//ボーンの数だけループさせる
	for (DWORD i = 0; i < dwBoneNum; i++)
	{
		//角フレーム(ボーン)のオフセット行列を取得して格納
		memcpy(&pMeshContainer->pBoneOffsetMatrices[i],
			pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(i), sizeof(D3DMATRIX));
	}
	//- 変換作業 -//
	//メッシュコンテナにオリジナルのpMesh情報を格納
	D3DVERTEXELEMENT9 Decl[MAX_FVF_DECL_SIZE];
	pMesh->GetDeclaration(&Decl[0]);
	pMesh->CloneMesh(pMesh->GetOptions(), &Decl[0], pDevice, &pMeshContainer->pOriMesh);
	//メッシュのタイプを定義
	pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;
	//- 固定パイプライン描画用に変換 -//
	//シェーダで描画する場合は別途変換が必要
	//頂点単位でのブレンドの重みとボーンの組み合わせテーブルを適応した新しいメッシュを返す。
	if (FAILED(pMeshContainer->pSkinInfo->ConvertToBlendedMesh(
		pMeshContainer->pOriMesh, //元のメッシュデータアドレス
		NULL, //オプション(現在は使われていないためNULLでいい)
		pMeshContainer->pAdjacency, //元のメッシュの隣接性情報
		NULL, //出力メッシュの隣接性情報
		NULL, //各面の新しいインデックス値格納用変数のアドレス
		NULL, //角頂点の新しいインデックス値格納用変数のアドレス
		&pMeshContainer->dwWeight, //ボーンの影響の一面当たりの最大数格納用変数のアドレス
		&pMeshContainer->dwBoneNum, //ボーンの組み合わせテーブルに含まれるボーン数格納用変数のアドレス
		&pMeshContainer->pBoneBuffer, //ボーンの組み合わせテーブルへのポインタ
		&pMeshContainer->MeshData.pMesh //出力されるメッシュアドレス格納用変数のアドレス(固定パイプライン用)
		)))
	{
		return E_FAIL;
	}
	//ローカルに生成したメッシュコンテナーを呼び出し側にコピーする
	*ppMeshContainer = pMeshContainer;
	//参照カウンタを増やしたので減らす
	SAFE_RELEASE(pDevice);
	return S_OK;
}
//HRESULT MY_HIERARCHY::DestroyFrame(LPD3DXFRAME pFrameToFree) 
//フレームを破棄する
HRESULT MyAllocateHierarchy::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
	//2銃解放防止
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
//メッシュコンテナーを破棄する
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
			//テクスチャ解放
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