//======================================================================================
// ���O�FGsmeMain.h
// �����F�Q�[�����C�����
//======================================================================================

#pragma once
#include "Stage.h"
#include "Select.h"
#include "Result.h"
#include "Bath_Stage.h"
#include "Table_Stage.h"
#include "Pause.h"
#include "Room_Stage.h"
#include "Tutorial.h"

class GameMain :
	public Scene
{
private:

	XMFLOAT3 camera = { 0.0f,0.0f,1.0f };			//�J�������W
	Stage* mStage;									//�X�e�[�W
	Pause* mPause;									//�|�[�Y

	bool PauseState;								//�|�[�Y����
	int StageID;									//�X�e�[�WID

public:
	
	GameMain();			//�R���X�g���N�^
	~GameMain();		//�f�X�g���N�^

	//�X�V
	void Update(void);
	//�X�V
	void Draw(void);

};

//======================================================================================
// �S���ҁF		�����S
// ��������F�@ 2022-12-01
// �`�[�����F	����	
//======================================================================================

