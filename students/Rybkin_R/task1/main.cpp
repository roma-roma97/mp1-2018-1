#include <iostream>
using namespace std;
class Converter {
	double t = 0.0; // по умолчанию тепература равна 0 в C
public:
	Converter(double a) : t(a) {}
	Converter operator=(double d)
	{
		t = d;
		return *this;
	} // перегрузка оператора присваивания
	void TempC()
	{
		cout << "Температура = " << t << "C \n";
	}
	void TempF()
	{
		cout << "Температура = " << Farengeit() << "F \n";
	}
	void TempK()
	{
		cout << "Температура = " << Kelvin() << "K \n";
	}
	void TempRa()
	{
		cout << "Температура = " << Rankin() << "Ra \n";
	}
	void TempR()
	{
		cout << "Температура = " << Reomyr() << "R \n";
	}
	void PrintAll()
	{
		cout << "Температура по шкале Цельсия = " << t << "\n";
		cout << "Температура по шкале Кельвина = " << Kelvin() << "\n";
		cout << "Температура по шкале Фаренгейта = " << Farengeit() << "\n";
		cout << "Температура по шкале Ранкина = " << Rankin() << "\n";
		cout << "Температура по шкале Реомюра = " << Reomyr() << "\n";
	}  //Выводит на консоль температуру во всех видах
	void Print()
	{
		int id;
		cout << "По какой шкале вы хотите узнать температуру: \n";
		cout << "0 - по шкале Цельсия \n";
		cout << "1 - по шкале Фаренгейта \n";
		cout << "2 - по шкале Кельвина \n";
		cout << "3 - по шкале Ранкина \n";
		cout << "4 - по шкале Реомюра \n";
		cout << "5 - сразу во всех \n";

		cin >> id;
		switch (id)
		{
		case 0: TempC(); break;
		case 1: TempF(); break;
		case 2: TempK(); break;
		case 3: TempRa(); break;
		case 4: TempR(); break;
		case 5: PrintAll(); break;
		}
	}
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
	cout << "Введите температуру : ";//Установление  температуры
	cin >> a;
	Converter Monday(a);
	Monday.Print();
	Monday = 7.0;//присваивание
	Monday.Print();
	system("pause");
	return 0;
}
