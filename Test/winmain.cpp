#undef UNICODE  // Unicode�ł͂Ȃ��A�}���`�o�C�g�������g��

#include "Direct3d.h"
#include "SceneManager.h"
#include "TestScene.h"
#include "System.h"
#include "resource.h"
//#include "Input.h"

//---------------------------------
//�}�N����`
//---------------------------------
#define CLASS_NAME    "DX21Smpl"// �E�C���h�E�N���X�̖��O
#define WINDOW_NAME  "������"// �E�B���h�E�̖��O

#define SCREEN_WIDTH (1280)	// �E�C���h�E�̕�
#define SCREEN_HEIGHT (720)	// �E�C���h�E�̍���

//---------------------------------
//�O���[�o���ϐ�
//---------------------------------

HWND hWnd; // H=Handle=�|�C���^ WND=Window

//--------------------------------
// �֐��̃v���g�^�C�v�錾
//--------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// WinMain�֐������
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc; // WND = Window

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_CLASSDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = CLASS_NAME;
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));

	//nCmdShow = SW_MAXIMIZE;
	
	RegisterClassEx(&wc); // Windows�ɃE�C���h�E����o�^

	
	hWnd = CreateWindowEx(0,// �g���E�B���h�E�X�^�C��
		CLASS_NAME,// �E�B���h�E�N���X�̖��O
		WINDOW_NAME,// �E�B���h�E�̖��O
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,// �E�B���h�E�X�^�C��
		CW_USEDEFAULT,// �E�B���h�E�̍���w���W
		CW_USEDEFAULT,// �E�B���h�E�̍���x���W 
		SCREEN_WIDTH,// �E�B���h�E�̕�
		SCREEN_HEIGHT,// �E�B���h�E�̍���
		NULL,// �e�E�B���h�E�̃n���h��
		NULL,// ���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,// �C���X�^���X�n���h��
		NULL);// �E�B���h�E�쐬�f�[�^

	// �w�肳�ꂽ�E�B���h�E�̕\����Ԃ�ݒ�(�E�B���h�E��\��)
	ShowWindow(hWnd, nCmdShow);
	// �E�B���h�E�̏�Ԃ𒼂��ɔ��f(�E�B���h�E�̃N���C�A���g�̈���X�V)
	UpdateWindow(hWnd);

	// Direct3D�̏������֐����Ăяo��
	Direct3D_Init(hWnd);

	//TestScene* CTestScene;	//�e�X�g�V�[��
	//CTestScene = new TestScene;
	Input_Init();
	Sound_Initialize();
	System_Init();
	GameSound_Init();
	SceneManager::Init();
	
	MSG msg;
	// ���C�����[�v
	for (;;) {
		// �O��̃��[�v���烆�[�U�[���삪�����������ׂ�
		BOOL doesMessageExist = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

		if (doesMessageExist)
		{
			// �ԐړI�ɃE�C���h�E�v���V�[�W�����Ăяo��
			DispatchMessage(&msg);

			// �A�v���I�����߂�����
			if (msg.message == WM_QUIT) {
				break;
			}
		}
		else
		{

			if (SceneManager::Update() == -1) {
				break;
			}

			SceneManager::Draw();

			System_Update();
		
			Input_Update();
			
		}
	}
	//�T�E���h�f�[�^�̉��
	GameSound_Uninit();

	// Direct3D�̉���֐����Ăяo��
	Direct3D_Release();

	Input_Release();
	Sound_Release();
	UnregisterClass(CLASS_NAME, hInstance);

	SceneManager::Uninit();

	return (int)msg.wParam;

}

// �E�C���h�E�v���V�[�W���֐������
// ���֐�������̂̓O���[�o���̈�(=�ǂ̊֐��̒��ł��Ȃ��ꏊ)�����I
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// uMsg�i���̊֐��̑�2�����j���A���[�U�[�����ID���
	switch (uMsg)
	{
	case WM_DESTROY:// �E�B���h�E�j���̃��b�Z�[�W
		PostQuitMessage(0);// �gWM_QUIT�h���b�Z�[�W�𑗂�@���@�A�v���I��
		break;

	case WM_CLOSE:  // x�{�^���������ꂽ��
		DestroyWindow(hWnd);  // �gWM_DESTROY�h���b�Z�[�W�𑗂�
		break;

	case WM_LBUTTONDOWN: // ���N���b�N���ꂽ�Ƃ�
		Input_SetKeyDown(LOWORD(VK_LBUTTON));
		break;
	case WM_LBUTTONUP: // ���N���b�N���ꂽ�Ƃ�
		Input_SetKeyUp(LOWORD(VK_LBUTTON));
		break;

	case WM_RBUTTONDOWN: // �E�N���b�N���ꂽ�Ƃ�
		Input_SetKeyDown(LOWORD(VK_RBUTTON));
		break;
	case WM_RBUTTONUP: // �E�N���b�N���ꂽ�Ƃ�
		Input_SetKeyUp(LOWORD(VK_RBUTTON));
		break;

	case WM_MOUSEMOVE: // �}�E�X�J�[�\�����������Ƃ�
		Input_SetMousePos(lParam);
		break;

	case WM_KEYDOWN:
		// �L�[�������ꂽ���̃��A�N�V����������
		Input_SetKeyDown(LOWORD(wParam));
		break;

	case WM_KEYUP: // �L�[�������ꂽ�C�x���g
		Input_SetKeyUp(LOWORD(wParam));
		break;

	default:
		// ���case�ȊO�̏ꍇ�̏��������s
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}

	return 0;
}