//======================================================================================
// ���O�FStage.h
// �����F�e�X�e�[�W�̃x�[�X
//======================================================================================
#pragma once
#include "Player.h"
#include "Dog.h"
#include "Cat.h"
#include "MiniMap.h"
#include "Frisbee.h"
#include "Dirt.h"
#include "Floor.h"
#include "SceneManager.h"
#include "Babble.h"
#include  <math.h>
#include "Robot.h"

#define FontU_Size 1.0f / 5.0f
#define FontV_Size 1.0f / 2.0f

#define BABBLMAX 50			//�A�ő吔
#define BLOCKMAX 3			//��Q���ő吔
#define sqr(n) ((n)*(n))	//�����v�Z�p

#define ZOOMMAX 0.000001f	//�J�����̃Y�[��

//�C�x���g
enum Ivent {
	NONE_IVENT,		//�Ȃ�̃C�x���g�ł��Ȃ�
	DOG_IVENT,		//���̃C�x���g
	CAT_IVENT,		//�L�̃C�x���g
	IVENT_END
};

class Stage 
{
protected:

	Cat* mCat;								//�L
	Dog* mDog;								//��
	Player* mPlayer;						//�v���C���[
	Frisbee* mFrisbee;						//�t���X�r�[
	Floor* mFloor;							//��
	Robot* mRobot;							//���{�b�g
	StaticObject* mBlock[BLOCKMAX];			//��Q��(3��ނ̏�Q��)
	HitSquare* mBlockHit[BLOCKMAX];			//��Q���̓�����

	Babble* mBabble[BABBLMAX];				//�A
	int BabbleNum;			
	
	//StaticObject* mObj[3];					//��Q��(3���)

	XMFLOAT3 mCamera;						//�J����
	StaticObject* mBackGround;				//�w�i
	ID3D11ShaderResourceView* mBgTex;		//�w�i�e�N�X�`���p�ϐ�

	ID3D11ShaderResourceView* mTimeBackTex;	//���Ԕw�i�p�ϐ�
	StaticObject* mTimeBack;				//���ԕ\���p
	ID3D11ShaderResourceView* mNumTex[10];	//���ԃe�N�X�`���p�ϐ�
	StaticObject* mTime[4];					//���ԕ\���p
	ID3D11ShaderResourceView* mCatMarkTex;	//�L�}�[�J�[�e�N�X�`��
	StaticObject* mCatMark;					//�L�}�[�J�[

	HitSquare* mRobotHit;					//���{�b�g�̓�����


	float fTime = 900000.0f;				//�������Ԍv��(�~���b)
	float fCatTime = 0.0f;					//�L���o�����鎞��
	float VibrationTime = 0.0f;				//�U�����鎞��
	bool mSound[5] = { false };

	int ClearNum;							//����Ă��Ȃ���
	int mMapInfo[STAGE_HIGHT][STAGE_WIDTH];		//�X�e�[�W���

	float fCameraZoom;		//�J�����Y�[����
	float fDogCryTime = 0.0f;		//����������

private:
	
public:

	int Score;								//�X�R�A
	bool TimeActive = true;					//�������ԏI�����Ă��邩�ǂ���
	MiniMap* mMiniMap;						//�~�j�}�b�v
	SOUND_LABEL mBGMSound;					// BGM�̃��x���̕ϐ�

	void DrawTime(float Num);				//���ԕ\��(�~���b�Ŏ󂯎��)

	void DrawMiniMap(void);		//�~�j�}�b�v�̕\��
	void CameraSet(void);		//�J�����̐���

	virtual void Update();	    //�X�V
	virtual void Draw();		//�`��

};

