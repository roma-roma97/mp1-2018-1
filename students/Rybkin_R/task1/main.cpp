#include <iostream>
using namespace std;
class ConverterTemperature {
	double t;
public:
	ConverterTemperature(double a = 0) : t(a) {}
	ConverterTemperature& operator=(double _t)
	{
		t = _t;
		return *this;
	} // присваивание классу числа типа double
	ConverterTemperature& operator=(const ConverterTemperature& temperature)
	{
		t = temperature.t;
		return *this;
	}//оператор присваивания между объектами одного класса
	void TemperatureC()
	{
		cout << "Температура = " << t << "C \n";
	}
	void TemperatureF()
	{
		cout << "Температура = " << Farengeit() << "F \n";
	}
	void TemperatureK()
	{
		cout << "Температура = " << Kelvin() << "K \n";
	}
	void TemperatureRa()
	{
		cout << "Температура = " << Rankin() << "Ra \n";
	}
	void TemperatureR()
	{
		cout << "Температура = " << Reomyr() << "R \n";
	}
	void TemperatureAll()
	{
		TemperatureC();
		TemperatureF();
		TemperatureK();
		TemperatureRa();
		TemperatureR();
	}  //Вывод на консоль температуры во всех шкалах
	double Farengeit()
	{
		return (9.0 / 5.0)*t + 32.0;
	}
	double Kelvin()
	{
		return t + 273.0;
	}
	double Rankin()
	{
		return (t + 273.0)*(9.0 / 5.0);
	}
	double Reomyr()
	{
		return (4.0 / 5.0)*t;
	}
	double Celc()
	{
		return t;
	}
};
int main()
{
	double a;
	setlocale(LC_ALL, "Russian");
	cout << "Введите температуру : ";
	cin >> a;
	ConverterTemperature Monday(a);
	ConverterTemperature Tuesday(5);
	Monday.TemperatureC(); // 74-78 строка вывод на консоль 
	Monday.TemperatureF();
	Monday.TemperatureK();
	Monday.TemperatureRa();
	Monday.TemperatureR();
	cout << "\n";
	Monday = 7.0; // Присваивание числа классу
	Monday.TemperatureAll();
	cout << "\n";
	Monday = Tuesday;//Присваивание между классами
	Monday.TemperatureAll();
	system("pause");
	return 0;
}