//�摜�t�@�C���̊i�[�Ɠǂݍ��݂ƕ\��

#ifndef _Image
#define _Image

class ImageFile{	//�C���[�W�t�@�C���̃N���X
	friend class Buffer;
	friend class kind;
	friend class Hchk;
public:
	//�����o�֐�
	int     FileRead(char *ReadfileName,int i);//�t�@�C�����ǂݍ���
	int     ImageFileRead();//�t�@�C���ǂݍ���
	int     ChangePalette();//�p���b�g���̐ݒ�
	int     ChangeImageSize();//�摜�T�C�Y���i�[
	int     ChangeImage();//�摜���i�[
	void    FreeImage();//���������

	int SetWindowSize2( int sx, int fx, int fy );
	int     SetConsolePalatte();
int     SetConsoleStringAttributesBuffer( int posX, int posY);


private:
	//�����o�ϐ�
	char    *fileName;
	int     point;      // �ǂݏo���ʒu
    int     datSize;    // �o�b�t�@�T�C�Y
    char    *buf;       // �o�b�t�@�|�C���^

    int         imgWidth, imgHight;         // �摜�T�C�Y

    int         bufferSizeX, bufferSizeY;   // �R���\�[���o�b�t�@�T�C�Y
    int         screenSizeX, screenSizeY;   // �R���\�[����ʃT�C�Y

    int         paletteSize;                // �p���b�g��

    COLORREF    palette[16];                // �p���b�g�f�[�^

    CHAR_INFO   *pImg;                      // �摜�f�[�^�i�����ƐF�j
};

class Buffer{
public:

	void Init(ImageFile Buff);//������
	void SetMap(ImageFile Buff);//�}�b�v�f�[�^�ǂݍ���
	void SetBuf(ImageFile Buff,int x,int y,int plx);//�摜�T�C�Y�@���W�@�`��o�b�t�@�[�ɓ����
	void SetBufM(ImageFile Buff,int x,int y,int plx);//�摜�T�C�Y�@���W�@�`��o�b�t�@�[�ɓ����(�t����)
	void SetBufD(ImageFile Buff,int x,int y,int plx);//�_���[�W�摜�\��
	void SetBufED(ImageFile Buff,int x,int y,int plx);//�G�̃_���[�W�\��
	void SetBufMD(ImageFile Buff,int x,int y,int plx);//�_���[�W�\��(�t����)
	void SetBufState(ImageFile Buff,int x,int y,int plx,int num);//�X�e�[�^�X�p�o�b�t�@
	void DrawBuf(ImageFile Buf,int plx);//�S������ւ�
	void SetMapBHXY(ImageFile Buff);//����
	void SetMapBHX(ImageFile Buff);//����X�̂�
	void SetMapB(ImageFile Buff);//��
	void SetMapWX(ImageFile Buff);//����X�̂�
	void SetMapW(ImageFile Buff);//��
private:
	CHAR_INFO   *pImge;//�}�b�v�f�[�^�̂�
	CHAR_INFO   *drawImge;//�L�����N�^�[�Ȃǂ������Ă���
	int screenX;//����̉摜�T�C�Y�i�[
	int screenY;
	int plx;//�v���C���[�̍��W�f�[�^�Ƀv���X�������W
};

class kind{//�L�����N�^�[�̏�Ԃ��i�[
public:
	void anim(int i,char *FName);//�A�j���[�V�����p�̉摜�i�[
	void Del();//�S�ď�����

ImageFile *animation;
private:	
};

#endif