#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define FACILITY_MES_MAX_FONT_LINE (6) //�{��(���ɁA������)�̕K�v�f��&�T�C�Y���b�Z�[�W�̍ő�t�H���g�s��
#define FACILITY_MAX_LV (3) //�{��(���ɁA������)��MAX���x��
#define MAT_NAME_CHAR_DATA_STORE_NUM (7) //�f�ޖ��̕����f�[�^�i�[�\��

//�I�u�W�F�N�g�F�琬���
class CObjTraining :public CObj
{
public:
	CObjTraining() {};
	~CObjTraining() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[
private:
	float m_size;		//�v���C���[�f���̃T�C�Y

	int m_Mig_time;		//�z�[����ʂɃV�[���ڍs����ۂ̎��ԊǗ��ϐ�
protected:
	int Allocation(int type_num, int up_down_check);//�U�蕪���֐�
	void Facility_message(int Facility_Level);//�{��(���ɁA������)�̕K�v�f��&�T�C�Y���b�Z�[�W�`��֐�

	float m_mou_x;		 //�}�E�X�̈ʒuX
	float m_mou_y;		 //�}�E�X�̈ʒuY
	bool  m_mou_r;		 //�}�E�X�v�b�V���m�F(�E�N���b�N)
	bool  m_mou_l;		 //�}�E�X�v�b�V���m�F(���N���b�N)
	bool  m_introduce_f; //�{�ݏЉ�E�C���h�E�\���Ǘ��t���O(true:�\�� / false:��\��)
	bool  m_finalcheck_f;//�ŏI�m�F�E�C���h�E�\���Ǘ��t���O(true:�\�� / false:��\��)
	//bool  m_help_f;		 //�w���v�E�C���h�E�\���Ǘ��t���O  (true:�\��/false:��\��)
	bool  m_key_lf;		 //���N���b�N�p�L�[�t���O
	static bool m_key_rf;//�E�N���b�N�p�L�[�t���O

	float m_Back_Button_color;	//�߂�{�^���J���[���x

	wchar_t m_message[18];		//�}�E�X�J�[�\���㕔�ɕ`�悷��ȈՃ��b�Z�[�W(�G���[���b�Z�[�W�A���x��UP�\����)�̃t�H���g�p
	float	m_message_red_color;	//�ȈՃ��b�Z�[�W�J���[(Red)
	float	m_message_green_color;	//�ȈՃ��b�Z�[�W�J���[(Green)
	float	m_message_blue_color;	//�ȈՃ��b�Z�[�W�J���[(Blue)
	float	m_alpha;				//�}�E�X�J�[�\���㕔�ɕ`�悷��O���t�B�b�N�̓��ߓx(�A���t�@�l)

	float m_Yes_Button_color;		//�ŏI�m�F[�͂�]�{�^���J���[(Red)���ߗp
	float m_No_Button_color;		//�ŏI�m�F[������]�{�^���J���[(Blue)���ߗp

	//���{��(���ɁA������)LvUP�������Ɏg�p����z��
	wchar_t m_Facility_message[FACILITY_MES_MAX_FONT_LINE][22];	//�{��(���ɁA������)�̕K�v�f��&�T�C�Y���b�Z�[�W�̃t�H���g�p(�f�ޖ�����)
	wchar_t m_message_Mat_name[MAT_NAME_CHAR_DATA_STORE_NUM];	//�e���b�Z�[�W(���ɁA�������A����|�b�h)�̑f�ޖ��t�H���g�p(���݃E�C���h�E�T�C�Y�I�ɑS�p6��������������Ȃ��悤�ɂ��Ă���)

	float  m_Facility_next_Size_num[FACILITY_MAX_LV - 1];	//�{��(���ɁA������)�̎���LVUP�ɕK�v�ȃT�C�Y(HP)�Ǘ��p
	wchar_t m_Facility_next_Mat_name[FACILITY_MAX_LV - 1][MAT_NAME_CHAR_DATA_STORE_NUM];//�{��(���ɁA������)�̎���LVUP�ɕK�v�ȑf�ނ̖��O�Ǘ��p
	int *m_Facility_next_Mat_type[FACILITY_MAX_LV - 1];		//�{��(���ɁA������)�̎���LVUP�ɕK�v�ȑf�ގ�ނƂ��̑f�ނ̏��������Ǘ�����|�C���^
	int  m_Facility_next_Mat_num[FACILITY_MAX_LV - 1];		//�{��(���ɁA������)�̎���LVUP�ɕK�v�ȑf�ސ��Ǘ��p(���ŕK�v�f��1��ނƂ��čl���Ă���B2��ވȏ�Ȃ炻�̕�Mat_type��Mat_num��z��\���̂ɓ���đ��₷�\��)


	static bool scene_change_start;	//�V�[���؂�ւ����o�J�n��`����t���O
	static int  player_level;		//�v���C���[�f�����x��(�z���C�g�A�E�g��������Ŏg��)
	static int  window_start_manage;//�{�݃E�C���h�E�̋N���Ǘ��t���O

	//���e�{�݃E�C���h�E(�߂�{�^���܂�)�ɗ񋓌^�Ŏ��ʔԍ�������U��
	enum window_id	
	{
		Default,	//�f�t�H���g�B�ǂ̃E�C���h�E���J���Ă��Ȃ���ԁB
		BackButton,	//�߂�{�^���������āA�z�[����ʂɖ߂낤�Ƃ��Ă����ԁB
		Barracks,	//���ɃE�C���h�E���J���Ă����ԁB
		Institute,	//�������E�C���h�E���J���Ă����ԁB
		Missile,	//�~�T�C���E�C���h�E���J���Ă����ԁB
		Equipment,	//����|�b�h�E�C���h�E���J���Ă����ԁB
		Warehouse,	//�q�ɃE�B���h�E���J���Ă����ԁB
		Materials,	//���ރE�B���h�E���J���Ă����ԁB
		Residents,	//�Z���E�B���h�E���J���Ă����ԁB
		Specialskill,//�X�y�V�����Z�E�B���h�E���J���Ă����ԁB
		Soubicheck,	//�����E�B���h�E���J���Ă����ԁB
		//Help,		//�w���v�E�B���h�E���J���Ă����ԁB
	};
};