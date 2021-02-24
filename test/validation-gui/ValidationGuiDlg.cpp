
// ValidationGuiDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "validation-gui.h"
#include "ValidationGuiDlg.h"
#include "afxdialogex.h"

#include "../../libsrc/linear_least_squares.h"
#include "../../libsrc/ridge_regression.h"
using namespace csv;
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define RANDOM(__min__, __max__) ((int)(((double)((rand()<<15) | (rand()&0) | rand())) / ((RAND_MAX<<15 | RAND_MAX) + 1) * (((__max__) + 1) - (__min__))) + (__min__))



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CValidationGuiDlg dialog



CValidationGuiDlg::CValidationGuiDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VALIDATIONGUI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CValidationGuiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STA_CANVAS, m_c_staCanvas);
}

BEGIN_MESSAGE_MAP(CValidationGuiDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_RESIDUAL_PLOTS, &CValidationGuiDlg::OnBnClickedBtnResidualPlots)
END_MESSAGE_MAP()


// CValidationGuiDlg message handlers

BOOL CValidationGuiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	srand((uint32_t)time(nullptr));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CValidationGuiDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CValidationGuiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CValidationGuiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CValidationGuiDlg::OnBnClickedBtnResidualPlots()
{
	ridge_regression rr;
	linear_least_squares::residual_list bhd_train;
	linear_least_squares::residual_list bhd_test;
	linear_least_squares::parameter_vector pv;
	vector<double> inferred_train;
	vector<double> inferred_test;
	vector<double> residuals_train;
	vector<double> residuals_test;
	vector<bool> trains;

	CSVReader reader("data/BostonHousing.csv");
	CSVFileInfo info = csv::get_file_info("data/BostonHousing.csv");

	trains.resize(info.n_rows);

	size_t cnt = trains.size() * 75 / 100;
	while(cnt)
	{
		for(auto t : trains)
		{
			if(t) continue;
			if(!RANDOM(0, 1)) continue;

			cnt--;
			t = true;
			if(cnt == 0) break;
		}
	}

	for(auto t : trains)
	{
		CSVRow row;
		reader.read_row(row);

		linear_least_squares::residual_list& bhd = t ? bhd_train : bhd_test;

		bhd.push_back({});
		bhd.back().y = row["medv"].get<double>();

		for(size_t i=0; i<row.size()-1; i++)
		{
			bhd.back().x.push_back(row[i].get<double>());
		}
	}

	pv = rr.solve(bhd_train, 1.0);

	double min_x = 100000.0, max_x = -100000.0;
	double min_y = 100000.0, max_y = -100000.0;

	for(auto& itm : bhd_train)
	{
		inferred_train.push_back(pv.back());
		for(size_t i=0; i<itm.x.size(); i++)
			inferred_train.back() += pv[i] * itm.x[i];

		residuals_train.push_back(itm.y - inferred_train.back());

		min_x = min(min_x, inferred_train.back());
		max_x = max(max_x, inferred_train.back());
		min_y = min(min_y, residuals_train.back());
		max_y = max(max_y, residuals_train.back());
	}

	for(auto& itm : bhd_test)
	{
		inferred_test.push_back(pv.back());
		for(size_t i=0; i<itm.x.size(); i++)
			inferred_test.back() += pv[i] * itm.x[i];

		residuals_test.push_back(itm.y - inferred_test.back());

		min_x = min(min_x, inferred_test.back());
		max_x = max(max_x, inferred_test.back());
		min_y = min(min_y, residuals_test.back());
		max_y = max(max_y, residuals_test.back());
	}

	CClientDC dc(&m_c_staCanvas);
	CRect rt;
	m_c_staCanvas.GetClientRect(&rt);
	dc.FillSolidRect(rt, RGB(208, 208, 208));
	dc.SetBkMode(TRANSPARENT);
	dc.TextOut(1, 1, L"x-axis: predicted, y-axis: residual");
	dc.TextOut(1, 18, L"red: training data, blue: test data");

	size_t i;
	HGDIOBJ old;

	old = dc.SelectObject(CreateSolidBrush(RGB(255, 0, 0)));
	for(i=0; i<bhd_train.size(); i++)
	{
		int x = (int)((double)(rt.Width() - 30) * ((inferred_train[i] - min_x) / (max_x - min_x)));
		int y = (int)((double)(rt.Height() - 30) * ((residuals_train[i] - min_y) / (max_y - min_y)));

		dc.Ellipse(x+10, y+10, x+10+7, y+10+7);
	}
	dc.SelectObject(old);

	old = dc.SelectObject(CreateSolidBrush(RGB(0, 0, 255)));
	for(i=0; i<bhd_test.size(); i++)
	{
		int x = (int)((double)(rt.Width() - 30) * ((inferred_test[i] - min_x) / (max_x - min_x)));
		int y = (int)((double)(rt.Height() - 30) * ((residuals_test[i] - min_y) / (max_y - min_y)));

		dc.Rectangle(x+10, y+10, x+10+7, y+10+7);
	}
	dc.SelectObject(old);


	double mse_train = 0.0;
	double mse_test = 0.0;
	double cod_train = 0.0;
	double cod_test = 0.0;
	double y_mean_train = 0.0;
	double y_mean_test = 0.0;
	double y_dist_train = 0.0;
	double y_dist_test = 0.0;


	for(i=0; i<bhd_train.size(); i++)
	{
		mse_train += pow(bhd_train[i].y - inferred_train[i], 2.0);
		y_mean_train += bhd_train[i].y;
	}
	mse_train /= bhd_train.size();
	y_mean_train /= bhd_train.size();

	for(i=0; i<bhd_test.size(); i++)
	{
		mse_test += pow(bhd_test[i].y - inferred_test[i], 2.0);
		y_mean_test += bhd_test[i].y;
	}
	mse_test /= bhd_test.size();
	y_mean_test /= bhd_test.size();

	for(i=0; i<bhd_train.size(); i++)
	{
		y_dist_train += pow(bhd_train[i].y - y_mean_train, 2.0);
	}
	y_dist_train /= bhd_train.size();

	for(i=0; i<bhd_test.size(); i++)
	{
		y_dist_test += pow(bhd_test[i].y - y_mean_test, 2.0);
	}
	y_dist_test /= bhd_test.size();

	cod_train = 1 - (mse_train / y_dist_train);
	cod_test = 1 - (mse_test / y_dist_test);

	CString sidx = L"";
	sidx.Format(L"trained - MSE: %.3lf, CoD: %.3lf", mse_train, cod_train);
	dc.TextOut(1, 35, sidx);
	sidx.Format(L"test - MSE: %.3lf, CoD: %.3lf", mse_test, cod_test);
	dc.TextOut(1, 52, sidx);
}
