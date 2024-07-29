// AutoCloseWnd.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "AutoCloseWnd.h"
#include "AutoCloseWndDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 生成GUID的互斥体名称
#define MUTEX_NAME _T("EscHotkey_Mutex")
// CAutoCloseWndApp

BEGIN_MESSAGE_MAP(CAutoCloseWndApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CAutoCloseWndApp 构造

CAutoCloseWndApp::CAutoCloseWndApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CAutoCloseWndApp 对象

CAutoCloseWndApp theApp;


// CAutoCloseWndApp 初始化

BOOL CAutoCloseWndApp::InitInstance()
{
	// 创建一个互斥体
	HANDLE hMutex = CreateMutex(NULL, TRUE, MUTEX_NAME);

	// 检查错误代码
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		// 如果互斥体已经存在，说明已有一个实例在运行
		AfxMessageBox(_T("应用程序已经在运行。"));
		return FALSE; // 阻止新实例启动
	}

	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CAutoCloseWndDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}


int CAutoCloseWndApp::ExitInstance()
{
	// 在应用程序退出时释放互斥体
	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, MUTEX_NAME);
	if (hMutex)
	{
		CloseHandle(hMutex);
	}

	return CWinApp::ExitInstance();
}