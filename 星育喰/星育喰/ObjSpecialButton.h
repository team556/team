#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "ObjFight.h"	//���N���X�Ƃ��Ē�`���邽�ߓǂݍ���
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�X�y�V�����Z�{�^��
class CObjSpecialButton :public CObjFight //CObjFight���p������
{
public:
	CObjSpecialButton(float x, float y, float h, float w);
	~CObjSpecialButton() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[

	bool GetEnemy_Used_Special() { return m_is_used_special[1]; }//�G���X�y�V�����Z���g�p�������ǂ�����Ԃ�
	int  GetSpecial_equip() { return m_enemy_special_equipment; }//�G���������̃X�y�V�����Z��Ԃ�
	bool GetInvocating(int Planet_id) { return m_is_invocating[Planet_id]; }//[�v���C���[ or �G]�����݃X�y�V�����Z�������ł��邩��Ԃ�
	void SetBuff_count(int Planet_id) { m_count[Planet_id] += 1; }//�|�b�g�̎ˏo�񐔃J�E���g�p[�X�y�V�����Z:�Z���̎m�C���A�b�v�p]
	void SetSpecial_Equip(int equip) { m_enemy_special_equipment = equip; }//�G�̔�������X�y�V�����Z�����߂�p
	void SetSpecial_Start() { m_enemy_special_button = true; }	//�G�̃X�y�V�����Z�𔭓�������p
private:
	void Special_staging_message(int Planet_id, int Special_equip);	//�X�y�V�����Z�������o���b�Z�[�W�ݒ�֐�
	void Special_process(int Planet_id, int Opponent_id, int Special_equip);			//�X�y�V�����Z�����֐�(�X�y�V�����Z�������o�A�X�y�V�����Z���ʂ̏��������s��)

	float m_x;		//�X�y�V�����Z�{�^���̍��WX
	float m_y;		//�X�y�V�����Z�{�^���̍��WY
	float m_h;		//�X�y�V�����Z�{�^����height(����)
	float m_w;		//�X�y�V�����Z�{�^����width(��)
	float m_a;		//�X�y�V�����Z�{�^����alpha(���ߓx)

	float m_mou_x;		//�}�E�X�̈ʒuX
	float m_mou_y;		//�}�E�X�̈ʒuY
	bool  m_mou_r;		//�}�E�X�v�b�V���m�F(�E�N���b�N)
	bool  m_mou_l;		//�}�E�X�v�b�V���m�F(���N���b�N)

	wchar_t m_staging_message[2][15];	//�X�y�V�����Z�������o�t�H���g�p([�t�H���g�s��][�����f�[�^�i�[�\��])
	float m_staging_font_color;			//�X�y�V�����Z�������o�t�H���g�J���[�ύX�p

	//���z�񐔎��̈Ӗ��͈ȉ��̒ʂ�
	//0:�v���C���[�f���@1:�G�f��
	int m_count[2];				//�X�y�V�����Z���ʎ��ԁA���ʉ񐔁A�������o���ԊǗ��p
	bool m_is_used_special[2];	//�X�y�V�����Z���g�p���ꂽ��[�X�y�V�����Z�������o�I�����_�Ŏg�p�����Ƃ݂Ȃ����](true:�g�p�ρ@false:���g�p)
	bool m_is_invocating[2];	//���݃X�y�V�����Z���������ł��邩(true:�������@false:������ or ������)
	bool  m_special_staging_f[2];//�X�y�V�����Z�������o�t���O[true:���o���@false:���o���ĂȂ�]

	float m_Explosion_size[2];	//[�X�y�V�����Z:�G�ɑ�_���[�W]�G�t�F�N�g�摜�T�C�Y�ύX�p
	float m_Explosion_width[2];	//[�X�y�V�����Z:�G�ɑ�_���[�W]�G�t�F�N�g�摜�̕��ύX�p
	float m_Explosion_pos[2];	//[�X�y�V�����Z:�G�ɑ�_���[�W]�G�t�F�N�g�摜�̈ʒu�ύX�p
	int   m_Explosion_target[2];//[�X�y�V�����Z:�G�ɑ�_���[�W]�G�t�F�N�g�ΏەύX�p
	float m_Explosion_angle[2];	//[�X�y�V�����Z:�G�ɑ�_���[�W]�G�t�F�N�g�p�x�ύX�p

	float m_Fracture_Ray_pos[2];	//[�X�y�V�����Z:���E��]�G�t�F�N�g�摜�̈ʒu�ύX�p
	float m_Fracture_Ray_width[2];	//[�X�y�V�����Z:���E��]�G�t�F�N�g�摜�̕��ύX�p

	float m_Immortality_size[2];	//[�X�y�V�����Z:��莞�Ԗ��G]�G�t�F�N�g�摜�T�C�Y�ύX�p
	

	float m_Special_effect_alpha[2];	//�X�y�V�����Z�G�t�F�N�g�摜��alpha(���ߓx)
	float m_Special_effect_alpha_vec[2];//�X�y�V�����Z�G�t�F�N�g�摜�̓��ߓx�x�N�g��

	//���ȉ���ObjPlanet(Enemy)���瑗���Ă�������擾����p
	int  m_enemy_special_equipment;//�G�������̃X�y�V�����Z(0:�������@1:�G�ɑ�_���[�W�@2:���E���@3:��莞�Ԗ��G�@4:���Y�������A�b�v�@5:�Z���̎m�C���A�b�v)
	bool m_enemy_special_button;//�G�p�X�y�V�����Z�����{�^��(true:�����@false:�������ĂȂ�)


	//���I�u�W�F�N�g���擾�p�̃|�C���^�����ꂼ��錾
	//���X�y�V�����Z�{�^���̏������e�I�u�W�F�N�g�ɑ�������A�t�Ɏ擾�����肷��ׂ̂��́B
	CObjFight *FightScene;
	CObjPlanet *Planet[2];
	CObjRocketButton *PodMissile[5];
};