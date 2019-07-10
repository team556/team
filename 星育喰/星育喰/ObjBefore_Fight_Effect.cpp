//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
//���������oIN �� OUT �Ȃ̂��ŏ����ʒu���ς��
//IN�Ȃ� 0.0f,OUT�Ȃ� 1500.0f�B
#define INI_BLACK_STAR_EFFECT_SIZE (m_In_Out_Check == true ? 0.0f : 1500.0f) //�����̏����T�C�Y

//�C�j�V�����C�Y
void CObjBefore_Fight_Effect::Init()
{
	m_black_star_effect_size = INI_BLACK_STAR_EFFECT_SIZE;
}

//�A�N�V����
void CObjBefore_Fight_Effect::Action()
{
	//���퓬�O���o(����)IN�̏���
	if (m_In_Out_Check == true)
	{
		if (m_black_star_effect_size >= 1500.0f)
		{
			//���摜����ʑS�̂𕢂���������A
			//ObjPreparation�́um_black_star_effect_f�v��ON�ɂ���B
			CObjPreparation* preparation = (CObjPreparation*)Objs::GetObj(OBJ_PREPARATION);
			preparation->SetEffectF();
		}
		else if (m_black_star_effect_size < 1500.0f)
		{
			//��ʒ������N�_�Ƃ��āA���̉摜�����X�Ɋg��
			//���̂܂܉�ʑS�̂𕢂������B
			m_black_star_effect_size += 20.0f;
		}
	}

	//���퓬�O���o(����)OUT�̏���
	else
	{
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
