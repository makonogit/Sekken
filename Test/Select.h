//======================================================================================
// ���O�FSelect.h
// �����F�X�e�[�W�I�����
//======================================================================================
#pragma once
#include "SceneManager.h"

#define MAXSTAGE 3	//�ő�X�e�[�W��

//�I���X�e�[�W��ID
enum STAGETID {
	ROOM_STAGE,
	BATH_STAGE,
	TABLE_STAGE,
	TUTORIAL_STAGE,
};

class Select : 
	public Scene
{
private:

	//��]���
	enum RotaState {
		LEFT_ROTA,
		RIGHT_ROTA,
		NONE_ROTA
	};

	int StageID[MAXSTAGE];						//�X�e�[�WID�̕��я�
	static int SelectStageID;					//�I�𒆂̃X�e�[�WID
	static int mInput;							//���͏��

	int Rota;									//��]���
	int Stage_Info;								//�X�e�[�W�ڍו\��
	bool Stage_Dicision;						//�X�e�[�W���肵�Ă��邩

	ID3D11ShaderResourceView* mBgTex;				//�w�i�e�N�X�`��
	ID3D11ShaderResourceView* mTableObjTex;			//�e�[�u���e�N�X�`��
	ID3D11ShaderResourceView* mBathObjTex;			//���C�e�N�X�`��
	ID3D11ShaderResourceView* mRoomObjTex;			//�����e�N�X�`��
	ID3D11ShaderResourceView* mStartUITex;			//�X�^�[�g�{�^���e�N�X�`��
	ID3D11ShaderResourceView* mCancelUITex;			//�L�����Z���{�^���e�N�X�`��
	ID3D11ShaderResourceView* mDifficultyUITex;			//��ՓxUI�e�N�X�`��
	ID3D11ShaderResourceView* mDifficultyBackUITex;			//��ՓxUI�e�N�X�`��
	ID3D11ShaderResourceView* mRankUITex[4];			//��ՓxUI�e�N�X�`��
	ID3D11ShaderResourceView* mRankBackUITex;			//��ՓxUI�e�N�X�`��
	ID3D11ShaderResourceView* mTutorialUITex;			//�`���[�g���A���e�N�X�`��
	ID3D11ShaderResourceView* mStageNameBackTex;		//�X�e�[�W����UI�e�N�X�`��
	ID3D11ShaderResourceView* mTableNameUITex;		//�e�[�u������UI�e�N�X�`��
	ID3D11ShaderResourceView* mBathNameUITex;		//�����C�ꖼ��UI�e�N�X�`��
	ID3D11ShaderResourceView* mRoomNameUITex;		//���֖���UI�e�N�X�`��
	ID3D11ShaderResourceView* mLevelFontTex;		//��ՓxUI�e�N�X�`��
	ID3D11ShaderResourceView* mTimeLimitTex;		//�������ԃe�N�X�`��
	ID3D11ShaderResourceView* mSelectTex;			//�w�X�e�[�W�I���x
	ID3D11ShaderResourceView* mSelectBackTex;		//�w�i

	StaticObject* mBg;								//�w�i
	StaticObject* mObject[MAXSTAGE];				//�Q�[���I�u�W�F�N�g
	StaticObject* mStartUI;							//�J�nUI
	StaticObject* mCancelUI;						//�L�����Z��UI
	StaticObject* mTutorialUI;						//�`���[�g���A��UI
	StaticObject* mDifficultyUI;							//��ՓxUI
	StaticObject* mDifficultyBackUI;							//��ՓxUI
	StaticObject* mRankUI;							//�������Ԏ���UI
	StaticObject* mRankBackUI;							//�������Ԏ���UI
	StaticObject* mStageNameUI;						//�X�e�[�W����UI
	StaticObject* mStageNameBackUI;						//�X�e�[�W����UI
	StaticObject* mSelectUI;						//�w�X�e�[�W�I���x
	StaticObject* mSelectBackUI;					//�w�i

	XMFLOAT3 camera = { 0.0f,0.0f,1.0f };			//�J�������W

	int BGMChange = false;
	SOUND_LABEL BGM;
	SOUND_LABEL OldBGM;
	float mBGMTime;

	Sprite::RGBA Red = { 1.0f,0.0f,0.0f,1.0f };		//�e�X�g�p��
	Sprite::RGBA White = { 1.0f,1.0f,1.0f,1.0f };	//�e�X�g�p��

public:

	Select();						//�R���X�g���N�^
	~Select();						//�f�X�g���N�^
	//�X�e�[�WID���擾����
	static int GetStageID(void);	
	//���͏����擾����@0:�R���g���[���[�@1:�L�[�{�[�h
	static int GetInput(void);
	//�X�e�[�W�I��
	void StageSelect(void);
	//�X�e�[�W�ڍ�
	void StageInfo(void);
	//�X�V
	void Update(void) override;			
	//�X�V
	void Draw(void) override;			

};

//======================================================================================
// �S���ҁF		�����S
// ��������F�@ 2022-12-01
// �`�[�����F	����	
//======================================================================================

