
#include"AnimationController.h"



//#pragma comment(lib, "d3d9.lib")
//#ifdef _DEBUG
//#pragma comment(lib, "d3dx9d.lib")
//#else
//#pragma comment(lib, "d3dx9.lib")
//#endif
//#pragma comment(lib,"dxguid.lib")

using namespace std;

/**
ID3DXAnimationControllerを独自バイナリデータとして保存する関数.
@param	filename	出力ファイル名.
@param	ctrl		対象のID3DXAnimationControllerへのポインタ.
@return	LRESULT		エラーコード.
*/
extern LRESULT save(const char *filename, ID3DXAnimationController *ctrl);

/**
ID3DXAnimationControllerを独自バイナリデータからロードする関数.
@param	filename	読み込みファイル名.
@param	rootFrame	メッシュのルートD3DXFRAMEへのポインタ. ID3DXAnimationControllerとの関連付けが行われる.
@param	ctrl		ID3DXAnimationControllerへのポインタへのポインタ. 正常終了すればここにインスタンスが生成される.
@return	LRESULT		エラーコード.
*/
extern int load(const char *filename, const D3DXFRAME *rootFrame, ID3DXAnimationController **ctrl);

/**
D3DXKEY_QUATERNIONの配列から、余分なデータを削除した配列を変える関数.
@param	src	元データ配列.
@return vector<D3DXKEY_QUATERNION>	余分なデータが削除されたデータ配列.
*/
extern vector<D3DXKEY_QUATERNION> CompressKeyQuaternion(const vector<D3DXKEY_QUATERNION> &src);

/**
D3DXKEY_VECTOR3の配列から、余分なデータを削除した配列を変える関数.
@param	src	元データ配列.
@return vector<D3DXKEY_VECTOR3>	余分なデータが削除されたデータ配列.
*/
extern vector<D3DXKEY_VECTOR3> CompressKeyVector3(const vector<D3DXKEY_VECTOR3> &src);





vector<D3DXKEY_QUATERNION> CompressKeyQuaternion(const vector<D3DXKEY_QUATERNION> &src)
{
	//	キーの内容を整頓する関数です.
	//	例えば下記のように(A, Bはそれぞれあるポーズを表しています)
	//	AAAAAAAAAAAABBBB
	//	というようなアニメーションの場合、
	//	A          AB  B
	//	というキーだけあれば問題ありません.
	//	キー情報が無い部分は、アニメーションコントローラーが前後のキーから補間してくれるからです.
	//	データ量をごっそり減らせるので、非常に有効です.

	vector<D3DXKEY_QUATERNION> dest;
	dest.reserve(src.size());

	//	srcが空なら、空を返す.
	if (src.empty())
	{
		return dest;
	}

	//	最初のキーは必ず登録する必要がありますね.
	dest.push_back(src[0]);

	for (UINT i = 1; i < src.size(); ++i)
	{
		D3DXQUATERNION tmp = dest.back().Value - src[i].Value;

		//	差が閾値を超えていたら、ポーズが変わったと判断する.
		//	完全なイコールだともったいないことが多々あるので.
		if (
			(tmp.x < -0.0001f || 0.0001f < tmp.x)
			|| (tmp.y < -0.0001f || 0.0001f < tmp.y)
			|| (tmp.z < -0.0001f || 0.0001f < tmp.z)
			|| (tmp.w < -0.0001f || 0.0001f < tmp.w)
			)
		{
			//	違うキーが見つかった.
			if (dest.back().Time != src[i - 1].Time)
			{
				//	キーが切り替わる直前のキーが、登録済みかどうかを調べます.
				//	これをやらないと、
				//	AAAAAAAAAAAABBBB
				//	↓
				//	A           B
				//	となってしまい、意味が変わってしまいます.
				//	A     x     B   
				//	xの地点のポーズが、本来ならAと同一であるべきなのに、AとBのポーズの中間として補間されてしまいますよね.
				dest.push_back(src[i - 1]);
			}
			dest.push_back(src[i]);
		}
	}
	if (dest.back().Time != src.back().Time)
	{
		//	一番最後のフレームが登録されているかをチェック.
		//	登録されていなければ、登録.
		dest.push_back(src.back());
	}
	return dest;
}

vector<D3DXKEY_VECTOR3> CompressKeyVector3(const vector<D3DXKEY_VECTOR3> &src)
{
	//	キーの内容を整頓する関数です.
	//	例えば下記のように(A, Bはそれぞれあるポーズを表しています)
	//	AAAAAAAAAAAABBBB
	//	というようなアニメーションの場合、
	//	A          AB  B
	//	というキーだけあれば問題ありません.
	//	キー情報が無い部分は、アニメーションコントローラーが前後のキーから補間してくれるからです.
	//	データ量をごっそり減らせるので、非常に有効です.

	vector<D3DXKEY_VECTOR3> dest;
	dest.reserve(src.size());

	//	srcが空なら、空を返す.
	if (src.empty())
	{
		return dest;
	}

	//	最初のキーは必ず登録する必要がありますね.
	dest.push_back(src[0]);

	for (UINT i = 1; i < src.size(); ++i)
	{
		D3DXVECTOR3 tmp = dest.back().Value - src[i].Value;

		//	差が閾値を超えていたら、ポーズが変わったと判断する.
		//	完全なイコールだともったいないことが多々あるので.
		if (
			(tmp.x < -0.0001f || 0.0001f < tmp.x)
			|| (tmp.y < -0.0001f || 0.0001f < tmp.y)
			|| (tmp.z < -0.0001f || 0.0001f < tmp.z)
			)
		{
			//	違うキーが見つかった.
			if (dest.back().Time != src[i - 1].Time)
			{
				//	キーが切り替わる直前のキーが、登録済みかどうかを調べます.
				//	これをやらないと、
				//	AAAAAAAAAAAABBBB
				//	↓
				//	A           B
				//	となってしまい、意味が変わってしまいます.
				//	A     x     B   
				//	xの地点のポーズが、本来ならAと同一であるべきなのに、AとBのポーズの中間として補間されてしまいますよね.
				dest.push_back(src[i - 1]);
			}
			dest.push_back(src[i]);
		}
	}
	if (dest.back().Time != src.back().Time)
	{
		//	一番最後のフレームが登録されているかをチェック.
		//	登録されていなければ、登録.
		dest.push_back(src.back());
	}
	return dest;
}

LRESULT AnimationController::save(const char *filename, ID3DXAnimationController *ctrl)
{
	//	出力ヘルパークラス.
	class Output
	{
		FILE *m_fp;
	public:
		Output(FILE *fp) :m_fp(fp){}

		void writeStr(const char *p)
		{
			fwrite(p, strlen(p) + 1, 1, m_fp);
		}
		void writeInt(int n)
		{
			fwrite(&n, sizeof(n), 1, m_fp);
		}
		void write(void *p, size_t size)
		{
			fwrite(p, size, 1, m_fp);
		}
	};

	FILE *fp;
	if (0 != fopen_s(&fp, filename, "wb"))
	{
		return 1;
	}

	Output out(fp);
	out.writeInt(ctrl->GetMaxNumAnimationOutputs());
	out.writeInt(ctrl->GetMaxNumAnimationSets());
	out.writeInt(ctrl->GetMaxNumTracks());
	out.writeInt(ctrl->GetMaxNumEvents());

	out.writeInt(ctrl->GetNumAnimationSets());
	for (UINT i = 0; i < ctrl->GetNumAnimationSets(); ++i)
	{
		//	アニメーションセットを取得.
		ID3DXAnimationSet *src;
		ctrl->GetAnimationSet(i, &src);

		//	キーフレーム毎の情報が欲しいので、ID3DXKeyframedAnimationSetにキャスト.
		ID3DXKeyframedAnimationSet *key;
		src->QueryInterface(IID_ID3DXAnimationSet, (LPVOID*)&key);
		src->Release();

		out.writeStr(key->GetName());
		out.writeInt(key->GetNumAnimations());
		for (UINT part = 0; part < key->GetNumAnimations(); ++part)
		{
			LPCSTR name;
			key->GetAnimationNameByIndex(part, &name);
			vector<D3DXKEY_QUATERNION> dataR(key->GetNumRotationKeys(part));
			vector<D3DXKEY_VECTOR3> dataS(key->GetNumScaleKeys(part));
			vector<D3DXKEY_VECTOR3> dataT(key->GetNumTranslationKeys(part));

			out.writeStr(name);
			key->GetRotationKeys(part, &dataR[0]);
			key->GetScaleKeys(part, &dataS[0]);
			key->GetTranslationKeys(part, &dataT[0]);

			dataR = CompressKeyQuaternion(dataR);
			dataS = CompressKeyVector3(dataS);
			dataT = CompressKeyVector3(dataT);

			out.writeInt(dataR.size());
			out.write(&dataR[0], sizeof(D3DXKEY_QUATERNION) * dataR.size());

			out.writeInt(dataS.size());
			out.write(&dataS[0], sizeof(D3DXKEY_VECTOR3) * dataS.size());

			out.writeInt(dataT.size());
			out.write(&dataT[0], sizeof(D3DXKEY_VECTOR3) * dataT.size());
		}

		key->Release();
	}
	fclose(fp);
	return 0;
}

int AnimationController::load(const char *filename, const D3DXFRAME *rootFrame, ID3DXAnimationController **ctrl)
{
	//	入力ヘルパークラス.
	//	エラー処理などが無いので、実際はもう少しキッチリ作りましょう.
	class Input
	{
		FILE *m_fp;
	public:
		Input(FILE *fp) :m_fp(fp){}

		int readInt()
		{
			int n;
			fread(&n, sizeof(int), 1, m_fp);
			return n;
		}
		string readStr()
		{
			int n;
			string str;
			while (0 < (n = fgetc(m_fp)))
			{
				str += n;
			}
			return str;
		}
		size_t read(void *p, size_t size)
		{
			return fread(p, 1, size, m_fp);
		}
	};

	FILE *fp;
	if (0 != fopen_s(&fp, filename, "rb"))
	{
		return 1;
	}

	Input in(fp);

	//	面倒くさがらず、一旦変数に読み込み.
	//	in.readInt()を関数の引数として並べると、「引数の実行順番は不定」なのでバグの温床になります.
	UINT outputs = in.readInt();
	UINT sets = in.readInt();
	UINT tracks = in.readInt();
	UINT events = in.readInt();

	if (S_OK != D3DXCreateAnimationController(outputs, sets, tracks, events, ctrl))
	{
		return 2;
	}

	//	全てのパート(ボーン)名を記録する. 最後に更新MATRIXとの関連付けを行うため.
	set<std::string> partNames;

	int animationSetNum = in.readInt();
	for (int i = 0; i < animationSetNum; ++i)
	{
		string animationName = in.readStr();
		int partsNum = in.readInt();

		ID3DXKeyframedAnimationSet *key;

		//	ここの引数は、作るものに合わせて変えましょう. LOOPさせないなど.
		D3DXCreateKeyframedAnimationSet(animationName.c_str(), 4800, D3DXPLAY_LOOP, partsNum, 0, NULL, &key);

		for (int part = 0; part < partsNum; ++part)
		{
			string partName = in.readStr();
			partNames.insert(partName);

			int cntR = in.readInt();
			vector<byte> bufferR(cntR * sizeof(D3DXKEY_QUATERNION));
			D3DXKEY_QUATERNION *pR = (0 < cntR) ? (D3DXKEY_QUATERNION *)&bufferR[0] : NULL;
			in.read(pR, bufferR.size());

			int cntS = in.readInt();
			vector<byte> bufferS(cntS * sizeof(D3DXKEY_VECTOR3));
			D3DXKEY_VECTOR3 *pS = (0 < cntS) ? (D3DXKEY_VECTOR3 *)&bufferS[0] : NULL;
			in.read(pS, bufferS.size());

			int cntT = in.readInt();
			vector<byte> bufferT(cntT * sizeof(D3DXKEY_VECTOR3));
			D3DXKEY_VECTOR3 *pT = (0 < cntT) ? (D3DXKEY_VECTOR3 *)&bufferT[0] : NULL;
			in.read(pT, bufferT.size());

			DWORD index;
			HRESULT hr = key->RegisterAnimationSRTKeys
				(
				partName.c_str(),
				cntS, cntR, cntT,
				pS, pR, pT,
				&index
				);
		}
		(*ctrl)->RegisterAnimationSet(key);
		key->Release();
	}
	fclose(fp);

	//	パート(ボーン)が更新された時、それぞれどのマトリクスを書き換えるかを登録する.
	for (set<string>::const_iterator it = partNames.begin(); it != partNames.end(); ++it)
	{
		const char *name = it->c_str();
		(*ctrl)->RegisterAnimationOutput
			(
			name, (D3DXMATRIX *)&D3DXFrameFind(rootFrame, name)->TransformationMatrix, NULL, NULL, NULL
			);
	}
	return 0;
}
