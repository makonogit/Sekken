#include "Fade_Dogrun.h"

extern DWORD gDeltaTime;
int Fade_Dogrun::mState = NONE_FADE;


//<><><><><><><><><><><><><><><><><><>
// �֐����FFade_Dogrun
// �����F�R���X�g���N�^
//<><><><><><><><><><><><><><><><><><>
Fade_Dogrun::Fade_Dogrun()
{

	//�ϐ��̏�����
	fiFlg = 0;
	feFlg = 0;

	color = { 0.0f,0.0f,0.0f,1.0f };
	camera = { 0.0f,0.0f,1.0f };

	LoadTexture(L"assets/images/Character/Dog/Run_dog.png", &mpTexture);
	LoadTexture(L"assets/Test.png", &BackTexture);

	//�t�F�[�h�p�I�u�W�F�N�g�̏�����
	Dogrun = new AnimObject(camera);
	Dogrun->mSprite->SetTexture(mpTexture);
	Dogrun->SetPosition(2.0f, -0.5f);
	Dogrun->SetSize(1.0f, 1.0f);
	Dogrun->mAnimObject->mDirection = D_LEFT;
	Dogrun->mAnimObject->fAnimSpeed = 0.01f;

	for (int i = 0; i < 2; i++)
	{
		Back[i] = new StaticObject(camera);
		Back[i]->mSprite->SetTexture(BackTexture);
		Back[i]->mSprite->SetColor(color);
		Back[i]->SetSize(2.8f,1.0f);

		if (i == 0)
		{
			Back[i]->SetPosition(2.75f, -0.5f);
		}
		else
		{
			Back[i]->SetPosition(-2.75f, 0.5f);

		}
	}
	Sound_Init(SOUND_LABEL_SE000);
	Fade_Dogrun::mState = NONE_FADE;
}

Fade_Dogrun::~Fade_Dogrun()
{
	Sound_Uninit(SOUND_LABEL_SE000);
	delete Dogrun;
	delete Back[0];
	delete Back[1];

}

void Fade_Dogrun::FadeIn(void)
{
	if (Fade_Dogrun::mState == FADE_OUT_END || Fade_Dogrun::mState == NONE_FADE) {
		Play(SOUND_LABEL_SE000);
		Fade_Dogrun::mState = FADE_IN;
	}
}

void Fade_Dogrun::FadeOut(void)
{
	if (Fade_Dogrun::mState == FADE_IN_END || Fade_Dogrun::mState == NONE_FADE) {
		Play(SOUND_LABEL_SE000);
		Fade_Dogrun::mState = FADE_OUT;
	}
}


//<><><><><><><><><><><><><><><><><><>
// �֐����FUpdate
// �����F�X�V
//<><><><><><><><><><><><><><><><><><>
void Fade_Dogrun::Update()
{
	//��Ԃ��ƂɃt�F�[�h�C���E�A�E�g����
	switch (Fade_Dogrun::mState)
	{
	case NONE_FADE:
		break;
	case FADE_IN:
		
		//�t�F�[�h�C���p�̃|�W�V�����ɃZ�b�g����
		if (feFlg == 0)
		{
			Dogrun->SetPosition(1.8f, 0.5f);
			Back[0]->SetPosition(0.0f, 0.5f);
			Back[1]->SetPosition(0.0f, -0.5f);
			feFlg = 1;
		}

		//�����E�[�ɍs���܂œ�����
		if (feFlg == 1) {
			if (Back[0]->mSprite->mCenter.x >= -2.75f)
			{//�w�i��[�܂ňړ�
				Back[0]->mSprite->mCenter.x -= 0.002f * gDeltaTime;
			}
			if (Dogrun->mSprite->mCenter.x >= -2.75f) 
			{//����[�܂ňړ�
				Dogrun->mSprite->mCenter.x -= 0.002f * gDeltaTime;
			}

			//�����[�܂ňړ������玟�̏���
			if (Back[0]->mSprite->mCenter.x <= -2.75f && Dogrun->mSprite->mCenter.x <= -2.75f) {
				feFlg = 2;
			}
		}

		//�摜�̃|�W�V�������ăZ�b�g���A���̏�����
		if (feFlg == 2)
		{
			Dogrun->SetPosition(-1.8f, -0.5f);
			Dogrun->mAnimObject->mDirection = D_UP;
			feFlg = 3;
		}

		//�������[�ɍs���܂œ�����
		if (feFlg == 3) {
			
			if (Dogrun->mSprite->mCenter.x <= 2.75f)
			{//����[�܂ňړ�
				Dogrun->mSprite->mCenter.x += 0.002f * gDeltaTime;
			}
			if (Back[1]->mSprite->mCenter.x <= 2.75f) 
			{//�w�i��[�܂ňړ�
				Back[1]->mSprite->mCenter.x += 0.002f * gDeltaTime;
			}

			//�����[�܂ňړ�������t�F�[�h�I��
			if (Dogrun->mSprite->mCenter.x >= 2.75f && Back[1]->mSprite->mCenter.x >= 2.75f) 
			{
				Dogrun->mAnimObject->mDirection = D_LEFT;
				Fade_Dogrun::mState = FADE_IN_END;
				feFlg = 0;
			}
		}

		break;
	case FADE_OUT:

		//�������[�ɍs���܂œ�����
		if (Dogrun->mSprite->mCenter.x > -2.75f && Back[0]->mSprite->mCenter.x >= 0.0f &&fiFlg == 0)
		{
			Dogrun->mSprite->mCenter.x -= 0.002f * gDeltaTime;
			Back[0]->mSprite->mCenter.x -= 0.002f * gDeltaTime;
		}
		else if (fiFlg == 0)		//��ʒ[�ɍs�����玟�̏�����
		{
			fiFlg = 1;
		}

		//�摜�̃|�W�V�������ăZ�b�g���A���̏�����
		if (fiFlg == 1)
		{
			Dogrun->mAnimObject->mDirection = D_UP;
			Dogrun->SetPosition(-1.8f, 0.5f);
			fiFlg = 2;
		}

		//�����E�[�ɍs���܂œ�����
		if (Dogrun->mSprite->mCenter.x < 2.0f && Back[1]->mSprite->mCenter.x <= 0.0f && fiFlg == 2)
		{
			Dogrun->mSprite->mCenter.x += 0.002f * gDeltaTime;
			Back[1]->mSprite->mCenter.x += 0.002f * gDeltaTime;
		}
		else if (fiFlg == 2)		//��ʒ[�ɍs�����玟�̏�����
		{
			fiFlg = 3;
		}

		if (fiFlg == 3)		//�t�F�[�h���I�����Ă�����Ȃɂ����Ă��Ȃ���Ԃɂ���
		{
			Fade_Dogrun::mState = FADE_OUT_END;
			fiFlg = 0;
			Dogrun->SetPosition(1.8f, 0.5f);
			Dogrun->mAnimObject->mDirection = D_LEFT;
		}
		break;
	default:
		Fade_Dogrun::mState = NONE_FADE;
		break;
	}

	//�X�v���C�g�̍X�V
	for (int i = 0; i < 2; i++) {
		Back[i]->Update();
	}

	Dogrun->Update();

}

//<><><><><><><><><><><><><><><><><><>
// �֐����FUpdate
// �����F�`��
//<><><><><><><><><><><><><><><><><><>
void Fade_Dogrun::Draw()
{
	for (int i = 0; i < 2; i++) {
		Back[i]->Draw();
	}

	Dogrun->Draw();
}

//======================================================================================
// �S���ҁF		���z��
// ��������F�@ 2022-12-05
// �`�[�����F	����	
//======================================================================================