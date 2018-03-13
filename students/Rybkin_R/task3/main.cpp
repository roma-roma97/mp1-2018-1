#include <fstream>
#include <iostream>
#include <cstdio>
#include <clocale>

using namespace std;

class FunctionTabulator
{
	int PointsTab;
	double BoundMin;
	double BoundMax;
	double *ResArr;
public:
	FunctionTabulator(double _PointsTab = 1, double _BoundMin = 0, double _BoundMax = 0)
	{
		PointsTab = _PointsTab;
		BoundMin = _BoundMin;
		BoundMax = _BoundMax;
	}
	FunctionTabulator(FunctionTabulator const &tab)
	{
		PointsTab = tab.PointsTab;
		BoundMin = tab.BoundMin;
		BoundMax = tab.BoundMax;
		ResArr = new double[PointsTab];
		for (int i = 0; i < PointsTab; i++)
			ResArr[i] = tab.ResArr[i];
	}
	~FunctionTabulator()
	{
		delete[] ResArr;
	}
	int GetPointsTab()
	{
		return PointsTab;
	}
	double GetBondMin()
	{
		return BoundMin;
	}
	double GetBondMax()
	{
		return BoundMax;
	}
	void InputPointsTab(int points)
	{
		PointsTab = points;
	}
	void InputBound(double min, double max)
	{
		BoundMin = min;
		BoundMax = max;
	}
	void Tabulator(double(*func)(double))
	{
		ResArr = new double[PointsTab];
		double x = BoundMin;
		double step = (BoundMax - BoundMin) / PointsTab;//шаг в табуляции
		for (int i = 0; i < PointsTab; i++)
		{
			ResArr[i] = func(x);
			x += step;
		}
	}
	void CloneTab(double *arr, double(*func)(double))
	{
		Tabulator(func);
		for (int i = 0; i < PointsTab; i++)
			arr[i] = ResArr[i];
	}
};
double TestFunc(double x)// Функция, которая подвергается табуляции.
{
	return (x*x);
}
void SaveReport(double *arr, double max, double min, int point)//Функция, создающая отчет в папке с проектом.
{
	double step = (max - min) / point;//шаг в табуляции
	double x = min;
	ofstream file;
	file.open("report.txt");//создает текстовый документ в папке с проектом
	file << "Границы табулирования: от " << min << " до " << max << endl;
	file << "Количество точек = " << point << endl;
	file << "Шаг табуляции = " << step << endl;
	for (int i = 0; i < point; i++)
	{
		file << "Значение аргумента = " << x << " Значение функции = " << arr[i] << endl;
		x += step;
	}
	file.close();
}
void OutReport(double *arr, double max, double min, int point)
{
	double step = (max - min) / point;
	double x = min;
	cout << "Границы табулирования: от " << min << " до " << max << endl;
	cout << "Количество точек = " << point << endl;
	cout << "Шаг табуляции = " << step << endl;
	for (int i = 0; i < point; i++)
	{
		cout << "Значение аргумента = " << x << " Значение функции = " << arr[i] << endl;
		x += step;
	}
}


int main()
{
	int Num;
	int min, max;
	double *Result;
	double(*f)(double);
	f = TestFunc;
	setlocale(LC_ALL, "Russian");
	FunctionTabulator sqr;
	cout << "Введите количество точек табуляции ";
	cin >> Num; cout << endl;
	sqr.InputPointsTab(Num);
	cout << "Введите границы табуляции ";
	cin >> min >> max; cout << endl;
	sqr.InputBound(min, max);
	Result = new double[sqr.GetPointsTab()];
	sqr.CloneTab(Result, f);
	OutReport(Result, sqr.GetBondMax(), sqr.GetBondMin(), sqr.GetPointsTab());
	// Функция SaveReport сохраняет отчет об табулировании в отдельный текстовый файл, который создается в папке с проектом.
	SaveReport(Result, sqr.GetBondMax(), sqr.GetBondMin(), sqr.GetPointsTab());
	system("pause");
}