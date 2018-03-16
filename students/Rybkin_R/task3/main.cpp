#include <fstream>
#include <iostream>
#include <cstdio>
#include <clocale>

using namespace std;

class FunctionTabulator
{
	int NumberOfPoints;
	double BoundMin;
	double BoundMax;
	double *ResArr;
	double(*Function)(double);
public:
	FunctionTabulator(int _NumberOfPoints = 1, double _BoundMin = 0, double _BoundMax = 0)
	{
		NumberOfPoints = _NumberOfPoints;
		BoundMin = _BoundMin;
		BoundMax = _BoundMax;
		ResArr = new double[_NumberOfPoints];
	}
	FunctionTabulator(double(*_Function)(double), int _NumberOfPoints = 1, double _BoundMin = 0, double _BoundMax = 0)
	{
		NumberOfPoints = _NumberOfPoints;
		BoundMin = _BoundMin;
		BoundMax = _BoundMax;
		ResArr = new double[_NumberOfPoints];
		Function = _Function;
	}
	FunctionTabulator(FunctionTabulator const &tab)
	{
		NumberOfPoints = tab.NumberOfPoints;
		BoundMin = tab.BoundMin;
		BoundMax = tab.BoundMax;
		ResArr = new double[NumberOfPoints];
		Function = tab.Function;
		for (int i = 0; i < NumberOfPoints; i++)
			ResArr[i] = tab.ResArr[i];
	}
	FunctionTabulator& operator=(const FunctionTabulator& tab)
	{
		if (this == &tab)
			return *this;
		if (NumberOfPoints != tab.NumberOfPoints)
		{
			delete[] ResArr;
			ResArr = new double[tab.NumberOfPoints];
			NumberOfPoints = tab.NumberOfPoints;
		}
		BoundMin = tab.BoundMin;
		BoundMax = tab.BoundMax;
		Function = tab.Function;
		for (int i = 0; i < NumberOfPoints; i++)
			ResArr[i] = tab.ResArr[i];
		return *this;
	}
	~FunctionTabulator()
	{
		delete[] ResArr;
	}
	int GetNumberOfPoints()
	{
		return NumberOfPoints;
	}
	double GetBoundMin()
	{
		return BoundMin;
	}
	double GetBoundMax()
	{
		return BoundMax;
	}
	double(*(GetFunction()))(double) { return Function; }
	void SetFunction(double(*_Function)(double))
	{
		Function = _Function;
	}
	void SetNumberOfPoints(int points)
	{
		NumberOfPoints = points;
		delete[] ResArr;
		ResArr = new double[points];
	}
	void SetBounds(double min, double max)
	{
		BoundMin = min;
		BoundMax = max;
	}
	void Tabulate()
	{
		double x = BoundMin;
		double step = (BoundMax - BoundMin) / NumberOfPoints;//шаг в табуляции
		for (int i = 0; i < NumberOfPoints; i++)
		{
			ResArr[i] = Function(x);
			x += step;
		}
	}
	void SaveReportTab()//Функция, создающая отчет в папке с проектом.
	{
		double step = (BoundMax - BoundMin) / NumberOfPoints;//шаг в табуляции
		double x = BoundMin;
		ofstream file;
		file.open("report.txt");//создает текстовый документ в папке с проектом
		file << "Границы табулирования: от " << BoundMin << " до " << BoundMax << endl;
		file << "Количество точек = " << NumberOfPoints << endl;
		file << "Шаг табуляции = " << step << endl;
		for (int i = 0; i <NumberOfPoints; i++)
		{
			file << "Значение аргумента = " << x << " Значение функции = " << ResArr[i] << endl;
			x += step;
		}
		file.close();
	}
	double GetPoint(int index)
	{
		return ResArr[index];
	}
	double *GetAllPoints()
	{
		return  ResArr;
	}

};
double TestFunc(double x)// Функция, которая подвергается табуляции.
{
	return (x*x);
}
void OutReport(double *arr, double min, double max, int num)
{
	double step = (max - min) / num;
	double x = min;
	cout << "Границы табулирования: от " << min << " до " << max << endl;
	cout << "Количество точек = " << num << endl;
	cout << "Шаг табуляции = " << step << endl;
	for (int i = 0; i < num; i++)
	{
		cout << "Значение аргумента = " << x << " Значение функции = " << arr[i] << endl;
		x += step;
	}

}

int main()
{
	int num;
	int min, max;
	double(*f)(double);
	f = TestFunc;
	setlocale(LC_ALL, "Russian");
	FunctionTabulator sqr;
	sqr.SetFunction(f);
	cout << "Введите количество точек табуляции ";
	cin >> num; cout << endl;
	sqr.SetNumberOfPoints(num);
	cout << "Введите границы табуляции ";
	cin >> min >> max; cout << endl;
	sqr.SetBounds(min, max);
	sqr.Tabulate();
	OutReport(sqr.GetAllPoints(), sqr.GetBoundMin(), sqr.GetBoundMax(), sqr.GetNumberOfPoints());
	sqr.SaveReportTab();
	system("pause");
}