//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//---Call_Planet�֐�
//����1�@int group	:�O���[�v����
//����2�@int select	:�f���I��
//�����e
//�^�C�g����ʁA�z�[����ʂ̓G�f��(�w�i)���Ăяo���֐��B
//�G�f��(�w�i)��3���݂��邽�߁A
//�S�Ă̓G�f���̉摜��3�O���[�v�ɕ����A
//��������A���ꂼ��w�肳�ꂽ(�����_����)�G�f���f�[�^��Ԃ��B
void Call_Planet(int group, int select)
{
	if (group == 0)
	{
		if (select == 1)
		{
			//�G�f��1��ǂݍ���20�Ԃɓo�^
			Draw::LoadImage(L"���f��.png", 20, TEX_SIZE_512);	
		}
		else if (select == 2)
		{
			//�G�f��2��ǂݍ���20�Ԃɓo�^
			Draw::LoadImage(L"���f��.png", 20, TEX_SIZE_512);
		}
		else if (select == 3)
		{
			//�G�f��3��ǂݍ���20�Ԃɓo�^
			Draw::LoadImage(L"���f��.png", 20, TEX_SIZE_512);
		}
		else  //(select == 4)
		{
			//�G�f��4��ǂݍ���20�Ԃɓo�^
			Draw::LoadImage(L"����.png", 20, TEX_SIZE_512);
		}
	}

	else if (group == 1)
	{
		if (select == 1)
		{
			//�G�f��1��ǂݍ���22�Ԃɓo�^
			Draw::LoadImage(L"���C�h1 128x.png", 22, TEX_SIZE_512);
		}
		else if (select == 2)
		{
			//�G�f��2��ǂݍ���22�Ԃɓo�^
			Draw::LoadImage(L"���C�h1 128x.png", 22, TEX_SIZE_512);
		}
		else if (select == 3)
		{
			//�G�f��3��ǂݍ���22�Ԃɓo�^
			Draw::LoadImage(L"���C�h1 128x.png", 22, TEX_SIZE_512);
		}
		else  //(select == 4)
		{
			//�G�f��4��ǂݍ���22�Ԃɓo�^
			Draw::LoadImage(L"����.png", 22, TEX_SIZE_512);
		}
	}

	else  //(group == 2)
	{
		if (select == 1)
		{
			//�G�f��1��ǂݍ���24�Ԃɓo�^
			Draw::LoadImage(L"�ڂ₯����.png", 24, TEX_SIZE_512);
		}
		else if (select == 2)
		{
			//�G�f��2��ǂݍ���24�Ԃɓo�^
			Draw::LoadImage(L"�ڂ₯����.png", 24, TEX_SIZE_512);
		}
		else if (select == 3)
		{
			//�G�f��3��ǂݍ���24�Ԃɓo�^
			Draw::LoadImage(L"�ڂ₯����.png", 24, TEX_SIZE_512);
		}
		else  //(select == 4)
		{
			//�G�f��4��ǂݍ���24�Ԃɓo�^
			Draw::LoadImage(L"����.png", 24, TEX_SIZE_512);
		}
	}

}