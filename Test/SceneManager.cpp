//======================================================================================
//		SceneManager�N���X
//======================================================================================

//------------------------------------
//		include
//------------------------------------
#include "SceneManager.h"
#include "Title.h"
#include "GameMain.h"
#include "Select.h"
#include "Result.h"

//�V�[������ɂ��Ă���
Scene* SceneManager::mScene = NULL;
Fade* SceneManager::mFade[] = {NULL,NULL,NULL};

//------------------------------------
//		�����o�[�֐�
//------------------------------------


//<><><><><><><><><><><><><><><><><><>
// �֐����FInit
// �����F�X�V
//<><><><><><><><><><><><><><><><><><>
void SceneManager::Init(void)
{
	mScene = new Title();
	mFade[0] = new Fade();
	mFade[1] = new Fade_Bubble();
	mFade[2] = new Fade_Dogrun();
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FUnInit
// �����F�X�V
//<><><><><><><><><><><><><><><><><><>
void SceneManager::Uninit(void)
{
	for (int i = 0; i < 3; i++) {
		delete mFade[i];
	}
}


//<><><><><><><><><><><><><><><><><><>
// �֐����F�V�[���`�F���W�֐�
// �����F�V�[���̕ύX
// �����F�V�[��ID
// �߂�l�F�Ȃ�
//<><><><><><><><><><><><><><><><><><>
void SceneManager::SceneChange(SceneStateID scene,Fade_Type Fade_Name)
{
	
	if (mScene != NULL) {
		delete mScene;
	}

	//�t�F�[�h�C��
	switch (Fade_Name)
	{
	case NOMAL_FADE:
		Fade::FadeIn();
		break;
	case BUBBLE_FADE:
		Fade_Bubble::FadeIn();
		break;
	case DOGRUN_FADE:
		Fade_Dogrun::FadeIn();
		break;
	default:
		break;
	}
	
	//�|�����[�t�B�Y���ŃV�[���𐶐�����
	switch (scene)
	{
	case NONE_SCENE:		//�ǂ��̃V�[���ł��Ȃ����Delete����
		mScene = NULL;
		break;
	case TITLE:
		mScene = new Title;
		break;
	case SELECT:
		mScene = new Select;
		break;
	case GAME_MAIN:
		mScene = new GameMain;
		break;
	case POSE:
		break;
	case RESULT:
		mScene = new Result;
		break;
	default:
		break;
	}

}

//<><><><><><><><><><><><><><><><><><>
// �֐����FUpdate
// �����F�X�V
//<><><><><><><><><><><><><><><><><><>
int SceneManager::Update(void)
{
	if (mScene != NULL) {
		mScene->Update();
		for (int i = 0; i < 3; i++) {
			mFade[i]->Update();
		}
	}
	else {
		return -1;
	}

	return 0;
}


//<><><><><><><><><><><><><><><><><><>
// �֐����FDraw
// �����F�`��
//<><><><><><><><><><><><><><><><><><>
void SceneManager::Draw(void)
{
	// DIRECT3D�\���̂ɃA�N�Z�X����
	DIRECT3D* d3d = Direct3D_Get();
	// ��ʂ̓h��Ԃ�����
	float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };  // rgba  0.0f-1.0f
	d3d->context->ClearRenderTargetView(d3d->renderTarget,
		color);
	
	if (mScene != NULL) {
		mScene->Draw();
		for (int i = 0; i < 3; i++) {
			mFade[i]->Draw();
		}
	}

	// �_�u���o�b�t�@�̐؂�ւ�
	d3d->swapChain->Present(0, 0);

}


//======================================================================================
// �S���ҁF		�����S
// �`�[�����F	����
//======================================================================================