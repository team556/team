//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameHead.h"
#include "ObjHuman.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjHuman::Init()
{

}

//�A�N�V����
void CObjHuman::Action()
{

}

//�h���[
void CObjHuman::Draw()
{

	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	RECT_F src;
	RECT_F dst;

	src.m_top   = 0.0f;
	src.m_left  = 0.0f;
	src.m_right =32.0f;
	src.m_bottom=32.0f;

	dst.m_top   = 0.0f;
	dst.m_left  = 0.0f;
	dst.m_right =32.0f;
	dst.m_bottom=32.0f;
}