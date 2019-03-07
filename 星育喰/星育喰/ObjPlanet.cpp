//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjPlanet.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjPlanet::CObjPlanet(float x, float y)
{
	//�쐬���ɓn���ꂽ�l���A���W�̏����l�ɑ��
	m_px = x;
	m_py = y;
}

//�C�j�V�����C�Y
void CObjPlanet::Init()
{
	m_size = 100;
	m_cnt = 0;
}

//�A�N�V����
void CObjPlanet::Action()
{
	m_cnt += 0.07f;
	m_px += 0.02f;
}

//�h���[
void CObjPlanet::Draw()
{
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	RECT_F src;
	RECT_F dst;
	//�؂���ʒu
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =100.0f;
	src.m_bottom=100.0f;
	//�\���ʒu
	dst.m_top   = m_py - m_cnt;
	dst.m_left  = m_px - m_cnt;
	dst.m_right = m_px + m_cnt + m_size;
	dst.m_bottom= m_py + m_cnt + m_size;

	//0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
	Draw::Draw(1, &src, &dst, c, 0.0f);
}
