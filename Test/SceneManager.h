#pragma once
//======================================================================================
// ���O�FSceneManager.h
// �����F�V�[���Ǘ�
//======================================================================================

//------------------------------------
//		include
//------------------------------------
#include"Scene.h"
#include"Fade.h"
#include"Fade_Bubble.h"
#include"Fade_Dogrun.h"
#include"System.h"

//------------------------------------
//		�񋓌^
//------------------------------------

enum SceneStateID
{
	NONE_SCENE = 0,
	TITLE,
	SELECT,
	GAME_MAIN,
	POSE,
	RESULT,
};
//------------------------------------
//		�N���X
//------------------------------------
class SceneManager
{
private:
	
	static Scene* mScene;							//�V�[��
	static Fade* mFade[3];							//�t�F�[�h�p
	
public:
	static void Init(void);							//������
	static void Uninit(void);						
	static void SceneChange(SceneStateID scene,Fade_Type Fade_Name);	//�V�[���ؑ֊֐�
	static int Update(void);						//�X�V
	static void Draw(void);							//�`��
};


//======================================================================================
//�S���ҁF�����S
//������F2022/11/25
//======================================================================================

