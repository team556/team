//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define INI_BLACK_STAR_EFFECT_SIZE (1400.0f) //�����̏����T�C�Y

//�C�j�V�����C�Y
void CObjBefore_Fight_Effect::Init()
{
	m_black_star_effect_size = INI_BLACK_STAR_EFFECT_SIZE;
}

//�A�N�V����
void CObjBefore_Fight_Effect::Action()
{
	//���퓬�O���o(����)�̏���
	if (m_black_star_effect_size <= 0.0f)
	{
		//���̉摜�������Ȃ��Ȃ�����A
		//ObjFight�́u�퓬�J�n�J�E���g�v�𓮍삳����
		CObjFight* fight = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
		fight->SetStart_Count();

		this->SetStatus(false);		//�������I�����̂ł��̃I�u�W�F�N�g���폜����
	}
	else if (m_black_star_effect_size > 0.0f)
	{
		//��ʑS�̂����̉摜�ŕ��������ꂽ��ԂŎn�܂�B
		//���̉摜�����X�ɏk�����Ă����A��ʒ����ւƎ����A
		//�ŏI�I�Ɍ����Ȃ��Ȃ�B
		m_black_star_effect_size -= 20.0f;
	}
}

//�h���[
void CObjBefore_Fight_Effect::Draw()
{
	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	//�퓬�O���o�摜�p(�����Ȃ�)
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu


	//���퓬�O���o(����)�\��
	//�����S�ɏk������ƕ`���\���ʒu�̐ݒ��A��\����ԂɂȂ�B
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 256.0f;
	src.m_bottom = 256.0f;

	dst.m_top = 350.0f - m_black_star_effect_size;
	dst.m_left = 600.0f - m_black_star_effect_size;
	dst.m_right = 600.0f + m_black_star_effect_size;
	dst.m_bottom = 350.0f + m_black_star_effect_size;
	Draw::Draw(18, &src, &dst, d, 0.0f);
}
