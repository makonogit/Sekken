//------------------------------------
//		include
//------------------------------------
#include "GameMain.h"

//<><><><><><><><><><><><><><><><><><>
// �֐����FGameMain
// �����F�R���X�g���N�^
//<><><><><><><><><><><><><><><><><><>
GameMain::GameMain()
{

	PauseState = false;	//�|�[�Y���ł͂Ȃ�
	
	StageID = Select::GetStageID();		//�X�e�[�WID�̎󂯎��

	//�X�e�[�W�̃C���X�^���X����
	switch (StageID)
	{
	case BATH_STAGE:
		mStage = new Bath_Stage;
		break;
	case TABLE_STAGE:
		mStage = new Table_Stage;
		break;
	case ROOM_STAGE:
		mStage = new Room_Stage;
		break;
	case TUTORIAL_STAGE:
		mStage = new Tutorial;
		break;
	default:
		break;
	}

}

//<><><><><><><><><><><><><><><><><><>
// �֐����F~GameMain
// �����F�f�X�g���N�^
//<><><><><><><><><><><><><><><><><><>
GameMain::~GameMain()
{
	delete mStage;
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FUpdate
// �����F�X�V
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//<><><><><><><><><><><><><><><><><><>
void GameMain::Update(void)
{
	//�X�^�[�g�{�^���Ń|�[�Y
	if (Input_GetButtonTrigger(START) || Input_GetKeyTrigger(VK_ESCAPE)) {
		if (PauseState) {
			PauseState = false;
			delete mPause;
			Resume(mStage->mBGMSound);
			Resume(SOUND_LABEL_SE013);
			Resume(SOUND_LABEL_SE019);
			Resume(SOUND_LABEL_SE023);
		}
		else {
			PauseState = true;
			mPause = new Pause();
			Stop(mStage->mBGMSound);
			Stop(SOUND_LABEL_SE013);
			Stop(SOUND_LABEL_SE019);
			Stop(SOUND_LABEL_SE021);
			Stop(SOUND_LABEL_SE023);
			Input_SetVibration(0, 0);	//�U�����~�߂�
		}
		
	}
	
	//�|�[�Y���Ȃ�|�[�Y�ȊO�̍X�V�͌Ă΂Ȃ�
	if (PauseState) {
		
		mPause->Update();

		switch (mPause->SceneSelect()) {
		case 0:
			PauseState = false;
			Resume(mStage->mBGMSound);
			break;
		case 1:
			PauseState = false;
			SceneManager::SceneChange(GAME_MAIN,NONE_TYPE);
			break;
		case 2:
			PauseState = false;
			SceneManager::SceneChange(TITLE,NONE_TYPE);	//�^�C�g���ֈړ��A�t�F�[�h���Ȃ�
			break;
		default:
			break;
		}
	}
	else if(mStage->TimeActive){
		mStage->Update();
	}
	else {
		Result::GetScore(mStage->Score);
		Stop(mStage->mBGMSound);
		Fade_Dogrun::FadeOut();
		if (Fade_Dogrun::mState == FADE_OUT_END) {
			SceneManager::SceneChange(RESULT, DOGRUN_FADE);
		}
	}

}


//<><><><><><><><><><><><><><><><><><>
// �֐����FDraw
// �����F�`��
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//<><><><><><><><><><><><><><><><><><>
void GameMain::Draw(void)
{
	
	mStage->Draw();
	
	if (PauseState) {
		mPause->Draw();
	}
}

//======================================================================================
// �S���ҁF		�����S
// ��������F�@ 2022-12-01
// �`�[�����F	����	
//======================================================================================