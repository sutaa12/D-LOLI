#ifndef _base
#define _base

//���W�ƃt���O�̊i�[�N���X
class Base{
	//�R���X�g���N�^
public:
	Base();
	void InputX(int px);//���W�i�[
	void InputY(int py);
	void Input(int px,int py);

	int x;
	int y;
	int Flag;//����̊m��t���O�i�����̂�)
	int MFlag;//����̊m��t���O(�����ȊO)
	int POSFlag;//�����̃t���O
	int LifeFlag;//�����t���O
	float DFlag;//�����_���g���t���O �^�ϊ��Ő؂�̂ĂŃA�j���[�V��������Ƃ�
};
#endif