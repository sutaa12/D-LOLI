
#ifndef _HCK
#define _HCK
class Hchk{

public:
//�G�ƃv���C���[�̓����蔻��
	void HchkInit(ImageFile Player,ImageFile Onemy);//������
	int Hitcheck(int px,int plx,int py,int ox,int oy);//�����蔻��
	int HitcheckEB(int px,int plx,int py,int ox,int oy);//�����蔻��
	int HitcheckO(int px,int plx,int py,int ox,int oy);//�����蔻�葫��

private:
int Oheight;//�Ώۂ̍���
int Owidth;//�Ώۂ̕�
int Pheight;//�v���C���[�̍���
int Pwidth;//�v���C���[�̕�
CHAR_INFO *Pimage;
CHAR_INFO *Oimage;

};

#endif


