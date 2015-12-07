
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
ID3DXAnimationController��Ǝ��o�C�i���f�[�^�Ƃ��ĕۑ�����֐�.
@param	filename	�o�̓t�@�C����.
@param	ctrl		�Ώۂ�ID3DXAnimationController�ւ̃|�C���^.
@return	LRESULT		�G���[�R�[�h.
*/
extern LRESULT save(const char *filename, ID3DXAnimationController *ctrl);

/**
ID3DXAnimationController��Ǝ��o�C�i���f�[�^���烍�[�h����֐�.
@param	filename	�ǂݍ��݃t�@�C����.
@param	rootFrame	���b�V���̃��[�gD3DXFRAME�ւ̃|�C���^. ID3DXAnimationController�Ƃ̊֘A�t�����s����.
@param	ctrl		ID3DXAnimationController�ւ̃|�C���^�ւ̃|�C���^. ����I������΂����ɃC���X�^���X�����������.
@return	LRESULT		�G���[�R�[�h.
*/
extern int load(const char *filename, const D3DXFRAME *rootFrame, ID3DXAnimationController **ctrl);

/**
D3DXKEY_QUATERNION�̔z�񂩂�A�]���ȃf�[�^���폜�����z���ς���֐�.
@param	src	���f�[�^�z��.
@return vector<D3DXKEY_QUATERNION>	�]���ȃf�[�^���폜���ꂽ�f�[�^�z��.
*/
extern vector<D3DXKEY_QUATERNION> CompressKeyQuaternion(const vector<D3DXKEY_QUATERNION> &src);

/**
D3DXKEY_VECTOR3�̔z�񂩂�A�]���ȃf�[�^���폜�����z���ς���֐�.
@param	src	���f�[�^�z��.
@return vector<D3DXKEY_VECTOR3>	�]���ȃf�[�^���폜���ꂽ�f�[�^�z��.
*/
extern vector<D3DXKEY_VECTOR3> CompressKeyVector3(const vector<D3DXKEY_VECTOR3> &src);





vector<D3DXKEY_QUATERNION> CompressKeyQuaternion(const vector<D3DXKEY_QUATERNION> &src)
{
	//	�L�[�̓��e�𐮓ڂ���֐��ł�.
	//	�Ⴆ�Ή��L�̂悤��(A, B�͂��ꂼ�ꂠ��|�[�Y��\���Ă��܂�)
	//	AAAAAAAAAAAABBBB
	//	�Ƃ����悤�ȃA�j���[�V�����̏ꍇ�A
	//	A          AB  B
	//	�Ƃ����L�[��������Ζ�肠��܂���.
	//	�L�[��񂪖��������́A�A�j���[�V�����R���g���[���[���O��̃L�[�����Ԃ��Ă���邩��ł�.
	//	�f�[�^�ʂ��������茸�点��̂ŁA���ɗL���ł�.

	vector<D3DXKEY_QUATERNION> dest;
	dest.reserve(src.size());

	//	src����Ȃ�A���Ԃ�.
	if (src.empty())
	{
		return dest;
	}

	//	�ŏ��̃L�[�͕K���o�^����K�v������܂���.
	dest.push_back(src[0]);

	for (UINT i = 1; i < src.size(); ++i)
	{
		D3DXQUATERNION tmp = dest.back().Value - src[i].Value;

		//	����臒l�𒴂��Ă�����A�|�[�Y���ς�����Ɣ��f����.
		//	���S�ȃC�R�[�����Ƃ��������Ȃ����Ƃ����X����̂�.
		if (
			(tmp.x < -0.0001f || 0.0001f < tmp.x)
			|| (tmp.y < -0.0001f || 0.0001f < tmp.y)
			|| (tmp.z < -0.0001f || 0.0001f < tmp.z)
			|| (tmp.w < -0.0001f || 0.0001f < tmp.w)
			)
		{
			//	�Ⴄ�L�[����������.
			if (dest.back().Time != src[i - 1].Time)
			{
				//	�L�[���؂�ւ�钼�O�̃L�[���A�o�^�ς݂��ǂ����𒲂ׂ܂�.
				//	��������Ȃ��ƁA
				//	AAAAAAAAAAAABBBB
				//	��
				//	A           B
				//	�ƂȂ��Ă��܂��A�Ӗ����ς���Ă��܂��܂�.
				//	A     x     B   
				//	x�̒n�_�̃|�[�Y���A�{���Ȃ�A�Ɠ���ł���ׂ��Ȃ̂ɁAA��B�̃|�[�Y�̒��ԂƂ��ĕ�Ԃ���Ă��܂��܂����.
				dest.push_back(src[i - 1]);
			}
			dest.push_back(src[i]);
		}
	}
	if (dest.back().Time != src.back().Time)
	{
		//	��ԍŌ�̃t���[�����o�^����Ă��邩���`�F�b�N.
		//	�o�^����Ă��Ȃ���΁A�o�^.
		dest.push_back(src.back());
	}
	return dest;
}

vector<D3DXKEY_VECTOR3> CompressKeyVector3(const vector<D3DXKEY_VECTOR3> &src)
{
	//	�L�[�̓��e�𐮓ڂ���֐��ł�.
	//	�Ⴆ�Ή��L�̂悤��(A, B�͂��ꂼ�ꂠ��|�[�Y��\���Ă��܂�)
	//	AAAAAAAAAAAABBBB
	//	�Ƃ����悤�ȃA�j���[�V�����̏ꍇ�A
	//	A          AB  B
	//	�Ƃ����L�[��������Ζ�肠��܂���.
	//	�L�[��񂪖��������́A�A�j���[�V�����R���g���[���[���O��̃L�[�����Ԃ��Ă���邩��ł�.
	//	�f�[�^�ʂ��������茸�点��̂ŁA���ɗL���ł�.

	vector<D3DXKEY_VECTOR3> dest;
	dest.reserve(src.size());

	//	src����Ȃ�A���Ԃ�.
	if (src.empty())
	{
		return dest;
	}

	//	�ŏ��̃L�[�͕K���o�^����K�v������܂���.
	dest.push_back(src[0]);

	for (UINT i = 1; i < src.size(); ++i)
	{
		D3DXVECTOR3 tmp = dest.back().Value - src[i].Value;

		//	����臒l�𒴂��Ă�����A�|�[�Y���ς�����Ɣ��f����.
		//	���S�ȃC�R�[�����Ƃ��������Ȃ����Ƃ����X����̂�.
		if (
			(tmp.x < -0.0001f || 0.0001f < tmp.x)
			|| (tmp.y < -0.0001f || 0.0001f < tmp.y)
			|| (tmp.z < -0.0001f || 0.0001f < tmp.z)
			)
		{
			//	�Ⴄ�L�[����������.
			if (dest.back().Time != src[i - 1].Time)
			{
				//	�L�[���؂�ւ�钼�O�̃L�[���A�o�^�ς݂��ǂ����𒲂ׂ܂�.
				//	��������Ȃ��ƁA
				//	AAAAAAAAAAAABBBB
				//	��
				//	A           B
				//	�ƂȂ��Ă��܂��A�Ӗ����ς���Ă��܂��܂�.
				//	A     x     B   
				//	x�̒n�_�̃|�[�Y���A�{���Ȃ�A�Ɠ���ł���ׂ��Ȃ̂ɁAA��B�̃|�[�Y�̒��ԂƂ��ĕ�Ԃ���Ă��܂��܂����.
				dest.push_back(src[i - 1]);
			}
			dest.push_back(src[i]);
		}
	}
	if (dest.back().Time != src.back().Time)
	{
		//	��ԍŌ�̃t���[�����o�^����Ă��邩���`�F�b�N.
		//	�o�^����Ă��Ȃ���΁A�o�^.
		dest.push_back(src.back());
	}
	return dest;
}

LRESULT AnimationController::save(const char *filename, ID3DXAnimationController *ctrl)
{
	//	�o�̓w���p�[�N���X.
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
		//	�A�j���[�V�����Z�b�g���擾.
		ID3DXAnimationSet *src;
		ctrl->GetAnimationSet(i, &src);

		//	�L�[�t���[�����̏�񂪗~�����̂ŁAID3DXKeyframedAnimationSet�ɃL���X�g.
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
	//	���̓w���p�[�N���X.
	//	�G���[�����Ȃǂ������̂ŁA���ۂ͂��������L�b�`�����܂��傤.
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

	//	�ʓ|�������炸�A��U�ϐ��ɓǂݍ���.
	//	in.readInt()���֐��̈����Ƃ��ĕ��ׂ�ƁA�u�����̎��s���Ԃ͕s��v�Ȃ̂Ńo�O�̉����ɂȂ�܂�.
	UINT outputs = in.readInt();
	UINT sets = in.readInt();
	UINT tracks = in.readInt();
	UINT events = in.readInt();

	if (S_OK != D3DXCreateAnimationController(outputs, sets, tracks, events, ctrl))
	{
		return 2;
	}

	//	�S�Ẵp�[�g(�{�[��)�����L�^����. �Ō�ɍX�VMATRIX�Ƃ̊֘A�t�����s������.
	set<std::string> partNames;

	int animationSetNum = in.readInt();
	for (int i = 0; i < animationSetNum; ++i)
	{
		string animationName = in.readStr();
		int partsNum = in.readInt();

		ID3DXKeyframedAnimationSet *key;

		//	�����̈����́A�����̂ɍ��킹�ĕς��܂��傤. LOOP�����Ȃ��Ȃ�.
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

	//	�p�[�g(�{�[��)���X�V���ꂽ���A���ꂼ��ǂ̃}�g���N�X�����������邩��o�^����.
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
