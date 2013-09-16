
// TestDirectXDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "TestDirectX.h"
#include "TestDirectXDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// DirectX 관련 헤더 인클루드
#include <d3d11.h>

// DirectX 관련 lib 추가
#pragma comment (lib, "d3d11.lib")

// DirectX 전역 선언
IDXGISwapChain	*swapchain;
ID3D11Device	*dev;
ID3D11DeviceContext	*devcon;

// DirectX 함수선언

// Direct3D를 셋업하고 초기화한다
void InitD3D(HWND hWnd);	

// Direct3D를 닫고 릴리즈한다
void Clean3D(void);

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg(); 

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

// 이 함수는 Direct3D를 사용하기 위한 초기화작업 및 준비작업을 합니다.
void InitD3D( HWND hWnd )
{
	// 스왑체인의 구조체를 선언합니다
	DXGI_SWAP_CHAIN_DESC scd;

	// 구조체를 초기화합니다
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	// 스왑체인 구조체를 채워넣습니다

	// 버퍼 개수를 정합니다
	scd.BufferCount = 1;

	//32bit 칼라를 사용합니다
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// 스왑체인을 어떻게 사용할 지 알려줍니다
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// 사용될 윈도우를 알려줍니다.
	scd.OutputWindow = hWnd;

	// 멀티샘플 사용 수를 정합니다
	scd.SampleDesc.Count = 4;

	// 창모드/ 전체화면 모드를 정합니다
	scd.Windowed = TRUE;

	// device, device-context, 스왑체인 등을 생성합니다 - scd 구조체를 이용합니다
	D3D11CreateDeviceAndSwapChain(NULL,
									D3D_DRIVER_TYPE_HARDWARE,
									NULL,
									NULL,
									NULL,
									NULL,
									D3D11_SDK_VERSION,
									&scd,
									&swapchain,
									&dev,
									NULL,
									&devcon);

}

// Direct3D를 닫고, 릴리즈합니다
void Clean3D( void )
{
	swapchain->Release();
	dev->Release();
	devcon->Release();
}

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestDirectXDlg 대화 상자



CTestDirectXDlg::CTestDirectXDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestDirectXDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDirectXDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestDirectXDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CTestDirectXDlg 메시지 처리기

BOOL CTestDirectXDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTestDirectXDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTestDirectXDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTestDirectXDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

