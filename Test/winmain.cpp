#undef UNICODE  // Unicodeではなく、マルチバイト文字を使う

#include "Direct3d.h"
#include "SceneManager.h"
#include "TestScene.h"
#include "System.h"
#include "resource.h"
//#include "Input.h"

//---------------------------------
//マクロ定義
//---------------------------------
#define CLASS_NAME    "DX21Smpl"// ウインドウクラスの名前
#define WINDOW_NAME  "せっ犬"// ウィンドウの名前

#define SCREEN_WIDTH (1280)	// ウインドウの幅
#define SCREEN_HEIGHT (720)	// ウインドウの高さ

//---------------------------------
//グローバル変数
//---------------------------------

HWND hWnd; // H=Handle=ポインタ WND=Window

//--------------------------------
// 関数のプロトタイプ宣言
//--------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// WinMain関数を作る
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
	
	RegisterClassEx(&wc); // Windowsにウインドウ情報を登録

	
	hWnd = CreateWindowEx(0,// 拡張ウィンドウスタイル
		CLASS_NAME,// ウィンドウクラスの名前
		WINDOW_NAME,// ウィンドウの名前
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,// ウィンドウスタイル
		CW_USEDEFAULT,// ウィンドウの左上Ｘ座標
		CW_USEDEFAULT,// ウィンドウの左上Ｙ座標 
		SCREEN_WIDTH,// ウィンドウの幅
		SCREEN_HEIGHT,// ウィンドウの高さ
		NULL,// 親ウィンドウのハンドル
		NULL,// メニューハンドルまたは子ウィンドウID
		hInstance,// インスタンスハンドル
		NULL);// ウィンドウ作成データ

	// 指定されたウィンドウの表示状態を設定(ウィンドウを表示)
	ShowWindow(hWnd, nCmdShow);
	// ウィンドウの状態を直ちに反映(ウィンドウのクライアント領域を更新)
	UpdateWindow(hWnd);

	// Direct3Dの初期化関数を呼び出す
	Direct3D_Init(hWnd);

	//TestScene* CTestScene;	//テストシーン
	//CTestScene = new TestScene;
	Input_Init();
	Sound_Initialize();
	System_Init();
	GameSound_Init();
	SceneManager::Init();
	
	MSG msg;
	// メインループ
	for (;;) {
		// 前回のループからユーザー操作があったか調べる
		BOOL doesMessageExist = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

		if (doesMessageExist)
		{
			// 間接的にウインドウプロシージャを呼び出す
			DispatchMessage(&msg);

			// アプリ終了命令が来た
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
	//サウンドデータの解放
	GameSound_Uninit();

	// Direct3Dの解放関数を呼び出す
	Direct3D_Release();

	Input_Release();
	Sound_Release();
	UnregisterClass(CLASS_NAME, hInstance);

	SceneManager::Uninit();

	return (int)msg.wParam;

}

// ウインドウプロシージャ関数を作る
// ※関数を作れるのはグローバル領域(=どの関数の中でもない場所)だけ！
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// uMsg（この関数の第2引数）が、ユーザー操作のID情報
	switch (uMsg)
	{
	case WM_DESTROY:// ウィンドウ破棄のメッセージ
		PostQuitMessage(0);// “WM_QUIT”メッセージを送る　→　アプリ終了
		break;

	case WM_CLOSE:  // xボタンが押されたら
		DestroyWindow(hWnd);  // “WM_DESTROY”メッセージを送る
		break;

	case WM_LBUTTONDOWN: // 左クリックされたとき
		Input_SetKeyDown(LOWORD(VK_LBUTTON));
		break;
	case WM_LBUTTONUP: // 左クリックされたとき
		Input_SetKeyUp(LOWORD(VK_LBUTTON));
		break;

	case WM_RBUTTONDOWN: // 右クリックされたとき
		Input_SetKeyDown(LOWORD(VK_RBUTTON));
		break;
	case WM_RBUTTONUP: // 右クリックされたとき
		Input_SetKeyUp(LOWORD(VK_RBUTTON));
		break;

	case WM_MOUSEMOVE: // マウスカーソルが動いたとき
		Input_SetMousePos(lParam);
		break;

	case WM_KEYDOWN:
		// キーが押された時のリアクションを書く
		Input_SetKeyDown(LOWORD(wParam));
		break;

	case WM_KEYUP: // キーが離されたイベント
		Input_SetKeyUp(LOWORD(wParam));
		break;

	default:
		// 上のcase以外の場合の処理を実行
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}

	return 0;
}