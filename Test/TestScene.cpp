#include "TestScene.h"
#include"Sound.h"
#include "Input.h"
#include"Sprite.h"
#include"SceneManager.h"
#include"WICTextureLoader.h"

using namespace DirectX;

TestScene::TestScene(void)
{
	mFade = new Fade();
	LoadTexture(L"assets/Test.png", &TestTexture);
	camera = { 0.0f,0.0f,1.0f };
	TestFrisbe = new Sprite(camera);
	TestFrisbe->SetTexture(TestTexture);

	StickTrigger = false;

	Sound_Initialize();	//�T�E���h����������

	Input_Init();// ����������

}

TestScene::~TestScene(void)
{
	delete mFade;
	delete TestFrisbe;
	Sound_Release();
	Input_Release();
}

void TestScene::Draw(void)
{
	// DIRECT3D�\���̂ɃA�N�Z�X����
	DIRECT3D* d3d = Direct3D_Get();

	// ��ʂ̓h��Ԃ�����
	float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };  // rgba  0.0f-1.0f
	d3d->context->ClearRenderTargetView(d3d->renderTarget,
		color);

	
	TestFrisbe->Draw();
	mFade->Draw();

	// �_�u���o�b�t�@�̐؂�ւ�
	d3d->swapChain->Present(0, 0);

}

float BGMVolume = 1.0f;

void TestScene::Update(void)
{
	Input_Update();			//�R���g���[���[�̍X�V����
	float Move = 0.0001f;	//�ړ��W��

//	//-------------�R���g���[���[����-------------------
//	if (Input_GetButtonDown(A)) {
//		/*
//		if (Input_GetLeftStick_X() > 0.0005f || Input_GetLeftStick_X() < -0.0005f &&
//			Input_GetLeftStick_Y() > 0.0005f || Input_GetLeftStick_Y() < -0.0005f) {
//			
//			if (!StickTrigger) {
//				OldStickPos_x = Input_GetLeftStick_X();
//				OldStickPos_y = Input_GetLeftStick_Y();
//				StickTrigger = true;
//			}
//		}
//		else {
//			
//		}
//*/
//	}
//	else {
//		
//		//StickTrigger = false;
//
//		//TestSprite->mCenterX += Input_GetLeftStick_X() * Move;
//		//TestSprite->mCenterY += Input_GetLeftStick_Y() * Move;
//
//		////���W�ۑ�
//		//if (StickTrigger) {
//		//	TestFrisbe->mCenterX += OldStickPos_x * 0.0005f;
//		//	TestFrisbe->mCenterY += OldStickPos_y * 0.0005f;
//		//	
//		//	if (TestFrisbe->mCenterX > 0.8f) {
//		//		TestFrisbe->mCenterX = 0.8f;
//		//		StickTrigger = false;
//		//	}
//		//	if (TestFrisbe->mCenterX < -0.8f) {
//		//		TestFrisbe->mCenterX = -0.8f;
//		//		StickTrigger = false;
//		//	}
//		//	if (TestFrisbe->mCenterY > 0.8f) {
//		//		TestFrisbe->mCenterY = 0.8f;
//		//		StickTrigger = false;
//		//	}
//		//	if (TestFrisbe->mCenterY < -0.8f) {
//		//		TestFrisbe->mCenterY = -0.8f;
//		//		StickTrigger = false;
//		//	}
//		//}
//		//else {
//		//	TestFrisbe->mCenterX = TestSprite->mCenterX;
//		//	TestFrisbe->mCenterY = TestSprite->mCenterY;
//		//}
//	}

	TestFrisbe->mCenter.x += Input_GetLeftStick_X() * 0.001f;
	TestFrisbe->mCenter.y += Input_GetLeftStick_Y() * 0.001f;



	if (Input_GetButtonTrigger(B)) {

		//Input_SetVibration(1000, 1000);
		mFade->FadeOut();

	}
	if (Input_GetButtonTrigger(A)) {

		mFade->FadeIn();

	}

	if (Input_GetButtonTrigger(X)) {

	}
	if (Input_GetButtonTrigger(Y)) {
		Stop(SOUND_LABEL_BGM000);	//BGM�̒�~
		GetSoundState(SOUND_LABEL_SE000);
	}
	if (Input_GetButtonDown(UP)) {
		BGMVolume += 0.0001f;
		SetVolume(SOUND_LABEL_BGM000, BGMVolume);
	}
	if (Input_GetButtonDown(DOWN)) {
		BGMVolume -= 0.0001f;
		SetVolume(SOUND_LABEL_BGM000, BGMVolume);
	}
	if (Input_GetButtonTrigger(LEFT)) {
		Resume(SOUND_LABEL_BGM000);
		
	}

	GetSoundState(SOUND_LABEL_BGM000);
	
	

	TestFrisbe->Update();
	mFade->Update();
}
