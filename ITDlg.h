
// ITDlg.h: файл заголовка
//

#pragma once
#include "Drawer.h"

// Диалоговое окно CITDlg
class CITDlg : public CDialogEx
{
	// Создание
public:
	CITDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	double A1;
	double f1;
	double phi1;
	double A2;
	double f2;
	double phi2;
	double A3;
	double f3;
	double phi3;
	double fd;
	int N;
	double A;
	double alpha;
	double beta;
	double sigma;
	void FirstPlot();//Построение первого графика
	double signal(double A1, double A2, double A3, double phi1, double phi2, double phi3, double f1, double f2, double f3, int N, int i);
	void SecondPlot();//Построение второго графика
	void AddNoise();//функция шума
	vector<double> X;//сигнал с шумом
	vector <double> x;//чистый сигнал
	vector<double> Dot;//вектор точек
	vector<double> AA;//вектор модулей частот
	vector<double> A_Re;//действительная
	vector<double> A_Im;//и мнимая части частоты
	vector<double> AA_Reduced;//очищенные модули частот
	vector<double> X_Reduced;//очищенный график
	Drawer DisSin;//рисовалка для первого графика
	Drawer AK;//рисовалка для второго графика
	Drawer Signals;//рисовалка третьего графика
	afx_msg void ReduceNoise();

};
