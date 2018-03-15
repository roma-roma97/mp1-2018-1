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
	friend void SaveReport(FunctionTabulator& object);
public:
	FunctionTabulator(int _PointsTab = 1, double _BoundMin = 0, double _BoundMax = 0)
	{
		PointsTab = _PointsTab;
		BoundMin = _BoundMin;
		BoundMax = _BoundMax;
		ResArr = new double[_PointsTab];
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
	double GetBoundMin()
	{
		return BoundMin;
	}
	double GetBoundMax()
	{
		return BoundMax;
	}
	void InputPointsTab(int points)
	{
		PointsTab = points;
		delete[] ResArr;
		ResArr = new double[points];
	}
	void InputBound(double min, double max)
	{
		BoundMin = min;
		BoundMax = max;
	}
	void Tabulator(double(*func)(double))
	{
		double x = BoundMin;
		double step = (BoundMax - BoundMin) / PointsTab;//шаг в табуляции
		for (int i = 0; i < PointsTab; i++)
		{
			ResArr[i] = func(x);
			x += step;
		}
	}
	double GetTab(int i)
	{
		return ResArr[i];
	}

};
double TestFunc(double x)// Функция, которая подвергается табуляции.
{
	return (x*x);
}
void SaveReport(FunctionTabulator& object)//Функция, создающая отчет в папке с проектом.
{
	double step = (object.BoundMax - object.BoundMin) / object.PointsTab;//шаг в табуляции
	double x = object.BoundMin;
	ofstream file;
	file.open("report.txt");//создает текстовый документ в папке с проектом
	file << "Границы табулирования: от " << object.BoundMin << " до " << object.BoundMax << endl;
	file << "Количество точек = " << object.PointsTab << endl;
	file << "Шаг табуляции = " << step << endl;
	for (int i = 0; i <object.PointsTab; i++)
	{
		file << "Значение аргумента = " << x << " Значение функции = " << object.ResArr[i] << endl;
		x += step;
	}
	file.close();
}
void OutReport(FunctionTabulator& object)
{
	double step = (object.GetBoundMax() - object.GetBoundMin()) / object.GetPointsTab();
	double x = object.GetBoundMin();
	cout << "Границы табулирования: от " << object.GetBoundMin() << " до " << object.GetBoundMax() << endl;
	cout << "Количество точек = " << object.GetPointsTab() << endl;
	cout << "Шаг табуляции = " << step << endl;
	for (int i = 0; i < object.GetPointsTab(); i++)
	{
		cout << "Значение аргумента = " << x << " Значение функции = " << object.GetTab(i) << endl;
		x += step;
	}

}

int main()
{
	int Num;
	int min, max;
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
	sqr.Tabulator(f);
	OutReport(sqr);
	//Функция SaveReport сохраняет отчет об табулировании в отдельный текстовый файл, который создается в папке с проектом.
	SaveReport(sqr);
	system("pause");
}