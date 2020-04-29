#include "stdafx.h"
#include "SkinModel.h"
#include "Stopwatch.h"
#include <Psapi.h>      // Psapi.Lib


/// ///////////////////////////////////////////////////////////////////
// �O���[�o���ϐ��B
///////////////////////////////////////////////////////////////////
HWND			g_hWnd = NULL;				//�E�B���h�E�n���h���B
GraphicsEngine* g_graphicsEngine = NULL;	//�O���t�B�b�N�X�G���W���B



CMatrix g_viewMatrix = CMatrix::Identity();		//�r���[�s��B
CMatrix g_projMatrix = CMatrix::Identity();		//�v���W�F�N�V�����s��B

const int NUM_UNITY_CHAN = 1;						//���j�e�B�����̐��B
SkinModel g_unityChanModel[NUM_UNITY_CHAN];	//


///////////////////////////////////////////////////////////////////
//���b�Z�[�W�v���V�[�W���B
//hWnd�����b�Z�[�W�𑗂��Ă����E�B���h�E�̃n���h���B
//msg�����b�Z�[�W�̎�ށB
//wParam��lParam�͈����B���͋C�ɂ��Ȃ��Ă悢�B
///////////////////////////////////////////////////////////////////
LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//�����Ă������b�Z�[�W�ŏ����𕪊򂳂���B
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;	
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}

///////////////////////////////////////////////////////////////////
// �E�B���h�E�̏������B
///////////////////////////////////////////////////////////////////
void InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�E�B���h�E�N���X�̃p�����[�^��ݒ�(�P�Ȃ�\���̂̕ϐ��̏������ł��B)
	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX),		//�\���̂̃T�C�Y�B
		CS_CLASSDC,				//�E�B���h�E�̃X�^�C���B
								//�����̎w��ŃX�N���[���o�[��������ł��邪�A�Q�[���ł͕s�v�Ȃ̂�CS_CLASSDC�ł悢�B
		MsgProc,				//���b�Z�[�W�v���V�[�W��(��q)
		0,						//0�ł����B
		0,						//0�ł����B
		GetModuleHandle(NULL),	//���̃N���X�̂��߂̃E�C���h�E�v���V�[�W��������C���X�^���X�n���h���B
								//�����C�ɂ��Ȃ��Ă悢�B
		NULL,					//�A�C�R���̃n���h���B�A�C�R����ς������ꍇ������ύX����B�Ƃ肠��������ł����B
		NULL,					//�}�E�X�J�[�\���̃n���h���BNULL�̏ꍇ�̓f�t�H���g�B
		NULL,					//�E�B���h�E�̔w�i�F�BNULL�̏ꍇ�̓f�t�H���g�B
		NULL,					//���j���[���BNULL�ł����B
		TEXT("Sample_01"),		//�E�B���h�E�N���X�ɕt���閼�O�B
		NULL					//NULL�ł����B
	};
	//�E�B���h�E�N���X�̓o�^�B
	RegisterClassEx(&wc);

	// �E�B���h�E�̍쐬�B
	g_hWnd = CreateWindow(
		TEXT("Sample_01"),		//�g�p����E�B���h�E�N���X�̖��O�B
								//��قǍ쐬�����E�B���h�E�N���X�Ɠ������O�ɂ���B
		TEXT("Sample_01"),		//�E�B���h�E�̖��O�B�E�B���h�E�N���X�̖��O�ƕʖ��ł��悢�B
		WS_OVERLAPPEDWINDOW,	//�E�B���h�E�X�^�C���B�Q�[���ł͊�{�I��WS_OVERLAPPEDWINDOW�ł����A
		0,						//�E�B���h�E�̏���X���W�B
		0,						//�E�B���h�E�̏���Y���W�B
		(UINT)FRAME_BUFFER_W,	//�E�B���h�E�̕��B
		(UINT)FRAME_BUFFER_H,	//�E�B���h�E�̍����B
		NULL,					//�e�E�B���h�E�B�Q�[���ł͊�{�I��NULL�ł����B
		NULL,					//���j���[�B����NULL�ł����B
		hInstance,				//�A�v���P�[�V�����̃C���X�^���X�B
		NULL
	);

	ShowWindow(g_hWnd, nCmdShow);

}

///////////////////////////////////////////////////////////////////
// ���t���[���Ă΂��Q�[���̕`�揈���B
///////////////////////////////////////////////////////////////////
void Render()
{
	
	g_graphicsEngine->BegineRender();
	///////////////////////////////////////////
	CVector3 pos;
	pos.x = 475.0f;
	pos.y = 150.0f;
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisX(), -90.0f);
	for (int i = 0; i < NUM_UNITY_CHAN; i++) {
		if (i % 20 == 0 && i != 0 ) {
			pos.x = 475.0f;
			pos.y -= 80.0f;
		}
		g_unityChanModel[i].UpdateWorldMatrix(pos, qRot, CVector3::One());
		pos.x -= 50.0f;
		g_unityChanModel[i].Draw( g_viewMatrix, g_projMatrix );
	}
	//�����܂Ń��f���\���Ɋ֌W����v���O�����B
	///////////////////////////////////////////
	g_graphicsEngine->EndRender();
}

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	::AllocConsole();               // �R�}���h�v�����v�g���\�������
	freopen("CON", "r", stdin);     // �W�����͂̊��蓖��
	freopen("CON", "w", stdout);    // �W���o�͂̊��蓖��

	DWORD dwProcessID = GetCurrentProcessId();

	//�E�B���h�E�̏������B
	InitWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow);


	//DirectX�̏������B
	g_graphicsEngine = new GraphicsEngine();
	g_graphicsEngine->Init(g_hWnd);
	
	//�J�����s����쐬�B
	g_viewMatrix.MakeLookAt(
		{ 0.0f, 0.0f, 500.0f },		//���_�B
		{ 0.0f, 0.0f, 0.0f },		//�����_�B
		{ 0.0f, 1.0f, 0.0f }		//������B
	);
	//�v���W�F�N�V�����s����쐬�B
	g_projMatrix.MakeProjectionMatrix(
		CMath::DegToRad(60.0f),				//��p�B
		FRAME_BUFFER_W/FRAME_BUFFER_H ,		//�A�X�y�N�g��B
		1.0f,								//�ߕ��ʁB
		1000.0f								//�����ʁB
	);
	/////////////////////////////////////////////////////////
	//���f����������
	//���Ԍv��
	Stopwatch sw;
	sw.Start();
	for (int i = 0; i < NUM_UNITY_CHAN; i++) {
		g_unityChanModel[i].Init(L"Assets/modelData/unityChan.cmo");
	}
	sw.Stop();

	printf("���������ԁ@=�@%f �~���b\n", sw.GetElapsedMillisecond());

	HANDLE hProcess;
	PROCESS_MEMORY_COUNTERS pmc = { 0 };

	if ((hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwProcessID)) != NULL) {
		if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
			printf("���݂̃������g�p�ʁ@=�@%lu MB\n", pmc.WorkingSetSize / 1024 / 1024);
		}

		CloseHandle(hProcess);
	}

	
	
	//���b�Z�[�W�\���̂̕ϐ�msg���������B
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)	//���b�Z�[�W���[�v
	{
		//�E�B���h�E����̃��b�Z�[�W���󂯎��B
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//�`�揈���B
			Render();
		}
	}
	::FreeConsole();
}