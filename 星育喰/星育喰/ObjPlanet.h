#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "ObjFight.h"	//���N���X�Ƃ��Ē�`���邽�ߓǂݍ���
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�f��(�v���C���[ & �G)
class CObjPlanet :public CObjFight //CObjFight���p������
{
public:
	CObjPlanet(float x, float y, float hp, int type, float siz = 0);//���W+HP+�^�C�v+�T�C�Y
	~CObjPlanet() {};
	void Init();	//�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();    //�h���[

	float GetX() { return m_px; }
	//float GetY() { return m_py; }
	float GetHp() { return m_hp; }	//HP�擾�֐�
	//float GetSiz() { return m_size; }
	bool GetInvincible() { return m_invincible_f; }//���G�ł��邩�ǂ����Ԃ�
	void SetDamage() { m_hp -= 1; }//�Ăяo���ƃ_���[�W����(HP)���s��[�X�y�V�����Z:�G�ɑ�_���[�W�p]
	void SetScale_down() { m_size -= m_size / 20; }////�Ăяo���ƃ_���[�W����(SIZE)���s��[�X�y�V�����Z:�G�ɑ�_���[�W�p]
	void SetInvincible(bool is_Invincible) { m_invincible_f = is_Invincible; }//���G�t���O�ݒ�p[�X�y�V�����Z:��莞�Ԗ��G�p]
	void SetRecastBuff(float buff) { m_enemy_recast_buff = buff; }//�o�t�{���ݒ�p[�X�y�V�����Z:���Y�������A�b�v�p]
	void SetDamageBuff(float buff) { m_damage_buff = buff; }//�o�t�{���ݒ�p[�X�y�V�����Z:�Z���̎m�C���A�b�v�p]
	void SetEeatF() { m_eat_f = true; }//�Z�b�g�򂤃t���O

	void SetDelF() { m_del_f = true; }//�Z�b�g�����t���O
private:

	float m_px;			//�����WX
	float m_py;			//�����WY
	float m_size;		//���T�C�Y
	float m_siz_max;	//�T�C�Y�}�b�N�X
	float m_siz_vec;	//�T�C�Y�ύX�x�N�g��
	float m_siz_spd;	//�T�C�Y�ύX�X�s�[�h
	float m_get_siz;	//�Q�b�g�T�C�Y
	float m_mov_spd;	//�f���ړ��X�s�[�h

	float m_hp;			//�q�b�g�|�C���g
	float m_get_hp;		//�Q�b�gHP
	int m_cnt;			//�J�E���g
	int m_type;		//�f���^�C�v(��l�� == 0 != �G)
	int m_img_nam;	//�摜(image)�i���o�[

	bool m_invincible_f;	//���G�t���O(true:���G�@false:���G�ł͂Ȃ�)[�X�y�V�����Z:��莞�Ԗ��G�p]
	float m_enemy_recast_buff;//�G�l�~�[�~�T�C���|�b�h���L���X�g�^�C���̃o�t�{��[�X�y�V�����Z:���Y�������A�b�v�p]
	float m_damage_buff;		//�_���[�W�̃o�t�{��[�X�y�V�����Z:�Z���̎m�C���A�b�v�p]


	int m_time;
	int m_attackf;		//�G�̍U���^�C�v

	float m_create_x;	//�G�f���~�T�C���|�b�h�쐬X�ʒu�����p
	
	int m_ani[4];
	int m_ani_time;
	int m_ani_frame;

	bool m_eat_f;		//�򂤃t���O(true = ��)
	float m_eat_spd;
	bool m_del_f;		//�����t���O(true = ����)

	int m_cntf;			//fight��m_cnt�ϐ��̒l���i�[����p
	int m_mov_stop;		//

	int Enemy_Attack_pattern_x;  //�G�U���p�^�[���̉����ǂݍ��ޗp
	int Enemy_Attack_pattern_y;  //�G�U���p�^�[���̏c���ǂݍ��ޗp
};