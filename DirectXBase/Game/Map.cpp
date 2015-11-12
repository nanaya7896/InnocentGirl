#include"Map.h"

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
	//���ʈ�i��
	xpanelSky.Render(&D3DXVECTOR3(0, 6, 72), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(12, 6, 72), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(24, 6, 72), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(36, 6, 72), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-12, 6, 72), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-24, 6, 72), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-36, 6, 72), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	//���ʓ�i��
	xpanelSky.Render(&D3DXVECTOR3(0, 18, 72), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(12, 18, 72), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[0].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(24, 18, 72), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(36, 18, 72), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-12, 18, 72), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-24, 18, 72), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-36, 18, 72), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	//���ʎO�i��

	xpanelSky.Render(&D3DXVECTOR3(0, 30, 72), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[0].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(12, 30, 72), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(24, 30, 72), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(36, 30, 72), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-12, 30, 72), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-24, 30, 72), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-36, 30, 72), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	//�w�ʈ�i��
	xpanelSky.Render(&D3DXVECTOR3(0, 6, -60), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(12, 6, -60), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(24, 6, -60), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(36, 6, -60), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-12, 6, -60), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-24, 6, -60), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-36, 6, -60), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	//�w�ʓ�i��
	xpanelSky.Render(&D3DXVECTOR3(0, 18, -60), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(12, 18, -60), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[0].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(24, 18, -60), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(36, 18, -60), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-12, 18, -60), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-24, 18, -60), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-36, 18, -60), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	//�w�ʎO�i��
	xpanelSky.Render(&D3DXVECTOR3(0, 30, -60), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[0].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(12, 30, -60), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(24, 30, -60), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(36, 30, -60), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-12, 30, -60), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-24, 30, -60), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-36, 30, -60), &D3DXVECTOR3(0, 300.029f, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	//�E�ʈ�i��
	xpanelSky.Render(&D3DXVECTOR3(42, 6, 66), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 6, 54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 6, 42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 6, 30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 6, 18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 6, 6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 6, -6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 6, -18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[0].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 6, -30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 6, -42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 6, -54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());

	//�E�ʈ�i��
	xpanelSky.Render(&D3DXVECTOR3(42, 6, 66), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 6, 54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 6, 42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 6, 30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 6, 18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 6, 6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 6, -6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 6, -18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[0].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 6, -30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 6, -42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 6, -54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());

	//�E�ʓ�i��
	xpanelSky.Render(&D3DXVECTOR3(42, 18, 66), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 18, 54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[0].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 18, 42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 18, 30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 18, 18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 18, 6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 18, -6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 18, -18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[0].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 18, -30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 18, -42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 18, -54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());

	//�E�ʎO�i��
	xpanelSky.Render(&D3DXVECTOR3(42, 30, 66), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[0].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 30, 54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 30, 42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 30, 30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 30, 18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 30, 6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 30, -6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 30, -18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[0].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 30, -30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 30, -42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(42, 30, -54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());

	//���ʈ�i��
	xpanelSky.Render(&D3DXVECTOR3(-42, 6, 66), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-42, 6, 54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-42, 6, 42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-42, 6, 30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-42, 6, 18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-42, 6, 6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-42, 6, -6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-42, 6, -18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[0].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-42, 6, -30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-42, 6, -42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-42, 6, -54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());

	//���ʓ�i��
	xpanelSky.Render(&D3DXVECTOR3(-42, 18, 66), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-42, 18, 54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[0].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-42, 18, 42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-42, 18, 30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-42, 18, 18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-42, 18, 6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-42, 18, -6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-42, 18, -18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[0].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-42, 18, -30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-42, 18, -42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-42, 18, -54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());

	//���ʎO�i��
	xpanelSky.Render(&D3DXVECTOR3(-42, 30, 66), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[0].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-42, 30, 54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-42, 30, 42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-42, 30, 30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-42, 30, 18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-42, 30, 6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-42, 30, -6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-42, 30, -18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[0].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-42, 30, -30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-42, 30, -42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-42, 30, -54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());

	//��
	xpanelSky.Render(&D3DXVECTOR3(0, 0, 6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	//�c���H(z�����}12)
	xpanelSky.Render(&D3DXVECTOR3(0, 0, -6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(0, 0, -18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(0, 0, -30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(0, 0, -42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(0, 0, -54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(0, 0, 18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(0, 0, 30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(0, 0, 42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(0, 0, 54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(0, 0, 66), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	//�����H(x�����}12)
	xpanelSky.Render(&D3DXVECTOR3(-12, 0, 6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-24, 0, 6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-36, 0, 6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(12, 0, 6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(24, 0, 6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(36, 0, 6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	//�n��
	//���[�^���[�t��
	//����N�_
	xpanelSky.Render(&D3DXVECTOR3(-12, 0, 18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	//����c���H��
	xpanelSky.Render(&D3DXVECTOR3(-12, 0, 30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-12, 0, 42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-12, 0, 54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	//����c���H����
	xpanelSky.Render(&D3DXVECTOR3(-12, 0, 66), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	//���㉡���H��
	xpanelSky.Render(&D3DXVECTOR3(-24, 0, 18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	//���㉡���H�[
	xpanelSky.Render(&D3DXVECTOR3(-36, 0, 18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	//�������
	//����
	xpanelSky.Render(&D3DXVECTOR3(-24, 0, 18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-24, 0, 30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-24, 0, 42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-24, 0, 54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-24, 0, 66), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	//����
	xpanelSky.Render(&D3DXVECTOR3(-36, 0, 18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-36, 0, 30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-36, 0, 42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-36, 0, 54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-36, 0, 66), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	//�E��N�_
	xpanelSky.Render(&D3DXVECTOR3(12, 0, 18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	//�E��c���H��
	xpanelSky.Render(&D3DXVECTOR3(12, 0, 30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(12, 0, 42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(12, 0, 54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	//�E��c���H����
	xpanelSky.Render(&D3DXVECTOR3(12, 0, 66), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	//�E�㉡���H��
	xpanelSky.Render(&D3DXVECTOR3(24, 0, 18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	//�E�㉡���H�[
	xpanelSky.Render(&D3DXVECTOR3(36, 0, 18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	//�E�����
	//����
	xpanelSky.Render(&D3DXVECTOR3(24, 0, 18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(24, 0, 30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(24, 0, 42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(24, 0, 54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(24, 0, 66), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	//����
	xpanelSky.Render(&D3DXVECTOR3(36, 0, 18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(36, 0, 30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanelSky[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(36, 0, 42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(36, 0, 54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(36, 0, 66), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[0].GetTexture());
	//�����N�_
	xpanelSky.Render(&D3DXVECTOR3(-12, 0, -6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[10].GetTexture());
	//�����c���H��
	xpanelSky.Render(&D3DXVECTOR3(-12, 0, -18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[3].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-12, 0, -30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[3].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-12, 0, -42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[3].GetTexture());
	//�����c���H����
	xpanelSky.Render(&D3DXVECTOR3(-12, 0, -54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[3].GetTexture());
	//���������H��
	xpanelSky.Render(&D3DXVECTOR3(-24, 0, -6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[4].GetTexture());
	//���������H�[
	xpanelSky.Render(&D3DXVECTOR3(-36, 0, -6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[4].GetTexture());
	//��������
	//����
	xpanelSky.Render(&D3DXVECTOR3(-24, 0, -18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[0].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-24, 0, -30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-24, 0, -42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-24, 0, -54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[0].GetTexture());
	//����
	xpanelSky.Render(&D3DXVECTOR3(-36, 0, -18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-36, 0, -30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[0].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-36, 0, -42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(-36, 0, -54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());
	//�E���N�_
	xpanelSky.Render(&D3DXVECTOR3(12, 0, -6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[8].GetTexture());
	//�E���c���H��
	xpanelSky.Render(&D3DXVECTOR3(12, 0, -18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(12, 0, -30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[2].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(12, 0, -42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[2].GetTexture());
	//�E���c���H����
	xpanelSky.Render(&D3DXVECTOR3(12, 0, -54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[2].GetTexture());
	//�E�������H��
	xpanelSky.Render(&D3DXVECTOR3(24, 0, -6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[4].GetTexture());
	//�E�������H�[
	xpanelSky.Render(&D3DXVECTOR3(36, 0, -6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[4].GetTexture());
	//�E������
	//����
	xpanelSky.Render(&D3DXVECTOR3(24, 0, -18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[0].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(24, 0, -30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(24, 0, -42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(24, 0, -54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[0].GetTexture());
	//����
	xpanelSky.Render(&D3DXVECTOR3(36, 0, -18), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(36, 0, -30), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[0].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(36, 0, -42), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());
	xpanelSky.Render(&D3DXVECTOR3(36, 0, -54), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tfloorGround[1].GetTexture());


//	xroof3.Render(&D3DXVECTOR3(-6, 12, 6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), troof3.GetTexture());
	//xroof4.Render(&D3DXVECTOR3(6, 12, 6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), troof4.GetTexture());

	//xpaneln1.Render(&D3DXVECTOR3(6, 6, 12), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanel1.GetTexture());
	//xpaneln2.Render(&D3DXVECTOR3(-6, 6, 12), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanel1.GetTexture());
	//xpanels1.Render(&D3DXVECTOR3(-6, 6, -12), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanel2.GetTexture());
	//xpanels2.Render(&D3DXVECTOR3(6, 6, -12), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanel2.GetTexture());
	//xpanelw1.Render(&D3DXVECTOR3(-12, 6, 6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanel3.GetTexture());
	//xpanelw2.Render(&D3DXVECTOR3(-12, 6, -6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanel3.GetTexture());
	//xpanele1.Render(&D3DXVECTOR3(12, 6, 6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanel4.GetTexture());
	//xpanele2.Render(&D3DXVECTOR3(12, 6, -6), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tpanel4.GetTexture());

	//xhouse.Render(&D3DXVECTOR3(4, 2, 4), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), thouse.GetTexture());
	//xtree.Render(&D3DXVECTOR3(4, 0.8f, -1), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), ttree.GetTexture());
	//xleaf.Render(&D3DXVECTOR3(-4, 3, -4), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tleaf.GetTexture());
	//xball.Render(&D3DXVECTOR3(-4, 8, -4), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), tball.GetTexture());


}