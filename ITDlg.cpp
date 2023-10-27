
// ITDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "IT.h"
#include "ITDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define M_PI 3.14159265358979323846

// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
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


// Диалоговое окно CITDlg



CITDlg::CITDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IT_DIALOG, pParent)
	, A1(1)
	, f1(1)
	, phi1(15)
	, A2(2)
	, f2(2)
	, phi2(30)
	, A3(3)
	, f3(3)
	, phi3(45)
	, fd(100)
	, N(300)
	, alpha(0.1)
	, beta (0.8)
	, sigma(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CITDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, A1);
	DDX_Text(pDX, IDC_EDIT2, f1);
	DDX_Text(pDX, IDC_EDIT3, phi1);
	DDX_Text(pDX, IDC_EDIT4, A2);
	DDX_Text(pDX, IDC_EDIT5, f2);
	DDX_Text(pDX, IDC_EDIT6, phi2);
	DDX_Text(pDX, IDC_EDIT7, A3);
	DDX_Text(pDX, IDC_EDIT8, f3);
	DDX_Text(pDX, IDC_EDIT9, phi3);
	DDX_Text(pDX, IDC_EDIT10, fd);
	DDX_Text(pDX, IDC_EDIT11, N);
	DDX_Text(pDX, IDC_EDIT13, alpha);
	DDX_Text(pDX, IDC_EDIT14, beta);
	DDX_Text(pDX, IDC_EDIT12, sigma);
}

BEGIN_MESSAGE_MAP(CITDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CITDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDOK2, &CITDlg::ReduceNoise)
END_MESSAGE_MAP()


// Обработчики сообщений CITDlg

BOOL CITDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
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

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	DisSin.Create(GetDlgItem(IDC_PIC1)->GetSafeHwnd());
	AK.Create(GetDlgItem(IDC_PIC2)->GetSafeHwnd());
	Signals.Create(GetDlgItem(IDC_PIC3)->GetSafeHwnd());
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CITDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CITDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CITDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

double CITDlg::signal(double A1, double A2, double A3, double phi1, double phi2, double phi3, double f1, double f2, double f3, int N, int i)
{
	return A1 * sin(2 * M_PI * f1 * i / fd + phi1) + A2 * sin(2 * M_PI * f2 * i / fd + phi2) + A3 * sin(2 * M_PI * f3 * i / fd + phi3);
}

void CITDlg::FirstPlot() {
	UpdateData(TRUE);

	phi1 = phi1 / 180 * M_PI;
	phi2 = phi2 / 180 * M_PI;
	phi3 = phi3 / 180 * M_PI;
	A = A1 + A2 + A3;
	for (int i = 0; i < N; i++) {
		double temp = signal(A1, A2, A3, phi1, phi2, phi3, f1, f2, f3, N, i);
		X.push_back(temp);
		x.push_back(temp);
		Dot.push_back(i);
	}
	AddNoise();
	DisSin.DrawGrid(X, 1, Dot, N, A,Dot[N-1]);
	DisSin.DrawAnimation(X, 1, Dot, N, A, Dot[N - 1],1);
}

double random() {
	return rand() - RAND_MAX / 2;
}

void CITDlg::AddNoise() {
	double* g = new double[N];//параметр шума
	for (int i = 0; i < N; i++) {
		g[i] = 0;
		for (int k = 0; k < 12; k++) {
			g[i] += random();
		}
	}
	double beta(0);//параметр шума
	double chisl(0), znam(0);//временные переменные
	for (int i = 0; i < N; i++) {
		chisl += X[i] * X[i];
		znam += g[i] * g[i];
	}
	beta = sqrt(alpha * chisl / znam);
	for (int i = 0; i < N; i++) {
		X[i] += beta * g[i];
		if (X[i] > A) A = X[i];
	}
}



void CITDlg::SecondPlot() {
	Dot.clear();
	for (int k = 0; k < N; k++) {
		double Re(0), Im(0);
		for (int n = 0; n < N; n++) {
			Re += X[n] * cos(2 * M_PI * k * n / N);
			Im -= X[n] * sin(2 * M_PI * k * n / N);
		}
		A_Re.push_back(Re);
		A_Im.push_back(Im);
		AA.push_back(sqrt(Re * Re + Im * Im));
		Dot.push_back(k * fd / N);
		if (AA[k] > A)A = AA[k];
	}
	AK.DrawGrid(AA, 2, Dot, N, A,Dot[N-1]);
	AK.DrawAnimation(AA, 2, Dot, N, A,Dot[N - 1],1);
}

void CITDlg::OnBnClickedOk()//сгенерировать сигнал
{
	//почистить память
	X.clear();
	x.clear();
	Dot.clear();
	AA.clear();
	A_Re.clear();
	A_Im.clear();
	AA_Reduced.clear();
	X_Reduced.clear();
	//построить графики
	FirstPlot();
	SecondPlot();
}


void CITDlg::ReduceNoise()//очистить шум
{
	//очищаем память
	AA_Reduced.clear();
	X_Reduced.clear();
	Dot.clear();
	UpdateData(TRUE);//считываем новые значения beta
	double E(0);//полная энергия зашумленного сигнала
	for (int i = 0; i < N - 1; i++) {
		E += AA[i] * AA[i]; //определяем как квадрат амплитуды
	}
	double E_signal = beta * E;//предполагаемя энергия очищенного сигнала
	double E_before(0); //переменная для сравнения
	int i = 0;
	//Очищаем спектр
	do {
		E_before += A_Re[i] * A_Re[i] + A_Im[i] * A_Im[i];//считываем энергию с левого
		E_before += A_Re[N - 1 - i] * A_Re[N - 1 - i] + A_Im[N - 1 - i] * A_Im[N - 1 - i]; //и правого концов частотного графика параллельно
		i++;
	} while (E_before <= E_signal);
	//зануляем середину спектра
	for (int j = 0; j <= i; j++) {
		AA_Reduced.push_back(AA[j]);
		if (AA_Reduced[j] > A)A = AA_Reduced[j];
		Dot.push_back(j * fd / N);
	}
	for (int j = i+1; j < N - 1 - i; j++) {
		AA_Reduced.push_back(0);
		Dot.push_back(j * fd / N);
	}
	for (int j = N-1-i; j <= N-1; j++) {
		AA_Reduced.push_back(AA[j]);
		Dot.push_back(j * fd / N);
	}
	//рисуем очищенный модуль спектра
	AK.DrawGrid(AA, 2, Dot, N, A, Dot[N - 1]); 
	AK.DrawAnimation(AA, 2, Dot, N, A, Dot[N - 1], 1);//спектр зашумленного сигнала
	AK.DrawAnimation(AA_Reduced, 2, Dot, N, A, Dot[N - 1],2);//спектр очищенного сигнала
	vector<double> dots;//вектор точек для построения
	//обратное преобразование фурье
	A = 0;//максимальное значение y на графике
	//рисуем очищенный сигнал по ощиченному спектру
	for (int j = 0; j < N; j++) {
		double Re_temp(0), Im_temp(0);
		for (int k = 0; k <=i; k++) {
			Re_temp += A_Re[k] * cos(2 * M_PI * k * j / N) - A_Im[k] * sin(2 * M_PI * k * j / N);	
		}
		for (int k = N-1-i; k < N-1; k++) {
			Re_temp += A_Re[k] * cos(2 * M_PI * k * j / N) - A_Im[k] * sin(2 * M_PI * k * j / N);
		}
		if (Re_temp / N > A) A = Re_temp / N;
		X_Reduced.push_back(Re_temp/N);
		dots.push_back(j);
	}
	double E_dif(0);//энергия разности значений
	
	E_signal = 0;
	A = 0;
	Dot.clear();
	//количественно сравниваем очищенный и истинный сигналы
	for (int i = 0; i < N; i++) {
		E_dif += (X_Reduced[i] - x[i]) * (X_Reduced[i] - x[i]);
		E_signal = x[i] * x[i];
		if (x[i] > A) A = x[i];
		Dot.push_back(i);
	}
	sigma = round(sqrt(E_dif / E_before)*1000)/1000;
	UpdateData(FALSE);
	dots.clear();
	//рисуем очищенный и истинный сигналы
	Signals.DrawGrid(X_Reduced, 3, Dot, N, A, Dot[N - 1]);
	Signals.DrawAnimation(x, 3, Dot, N, A, Dot[N - 1], 3);
	Signals.DrawAnimation(X_Reduced, 1, Dot, N, A, Dot[N - 1],2);

}
