#define _CRT_SECURE_NO_WARNINGS
#define STRT "Событий нет"

#include <cstdio>
#include <iostream>
#include <math.h>
#include <cstring>
#include <clocale>
#include <windows.h>
using namespace std;
class EventCalendar {
	int day[30];
	int	month[30];
	int year[30];
	char **Event;
public:
	EventCalendar(char *str = "Событий нет", int Num = -1, int y = 0, int m = 0, int d = 0)
	{
		Event = new char*[30];
		for (int i = 0; i < 30; i++)
		{
			year[i] = 0;
			month[i] = 0;
			day[i] = 0;
			Event[i] = new char[strlen(STRT) + 1];
			strcpy(Event[i], STRT);
		}
		if ((Num > -1) && (Num < 30))
		{
			delete[] Event[Num];
			Event[Num] = new char[strlen(str) + 1];
			strcpy(Event[Num], str);
		}
	}
	~EventCalendar()
	{
		for (int i = 0; i < 30; i++)
			delete[] Event[i];
		delete[] Event;
	}
	EventCalendar& operator=(const EventCalendar& calendar)
	{
		for (int i = 0; i < 30; i++)
		{
			day[i] = calendar.day[i];
			month[i] = calendar.month[i];
			year[i] = calendar.year[i];
			delete[] Event[i];//free(Event[i]);
			Event[i] = new char[strlen(calendar.Event[i]) + 1];
			strcpy(Event[i], calendar.Event[i]);
		}
		return *this;
	}
	void InputEvent(int Num, int _year, int _month, int _day, char *str)
	{
		if ((Num > -1) && (Num < 30))
			if ((_year > 0 && _year < 2021) && (_month > 0 && _month < 13) && (_day > 0 && _day < 32))
			{
				year[Num] = _year;
				month[Num] = _month;
				day[Num] = _day;
				delete[] Event[Num];
				Event[Num] = new char[strlen(str) + 1];
				strcpy(Event[Num], str);
			}
	}
	void OutEvent(int Num)
	{
		cout << year[Num] << "." << month[Num] << "." << day[Num] << " " << Event[Num];
	}
	void ShiftHelp1(int Num, int _year, int _month, int _day)
	{
		if ((_day + day[Num]) > 31)
		{
			month[Num] = month[Num] + 1;
			day[Num] = (_day + day[Num]) - 31;
		}
		else
			day[Num] = day[Num] + _day;

		if ((_month + month[Num]) > 12)
		{
			year[Num] = year[Num] + 1;
			month[Num] = (_month + month[Num]) - 12;
		}
		else
			month[Num] += _month;

		year[Num] = year[Num] + _year;
	}//Вспомогательная функция для метода ShiftEvent
	void ShiftHelp2(int Num, int _year, int _month, int _day)
	{
		if ((day[Num] - _day) <1)
		{
			month[Num] = month[Num] - 1;
			day[Num] = 31 - (_day - day[Num]);
		}
		else
			day[Num] = day[Num] - _day;

		if ((month[Num] - _month) < 1)
		{
			year[Num] = year[Num] - 1;
			month[Num] = 12 - (_month - month[Num]);
		}
		else
			month[Num] = month[Num] - _month;

		year[Num] = year[Num] - _year;
	}//Вспомогательная функция для метода ShiftEvent
	void ShiftEvent(int Num, int _year, int _month, int _day, int id)
	{
		switch (id)
		{
		case 1:ShiftHelp1(Num, _year, _month, _day); break;
		case 2:ShiftHelp2(Num, _year, _month, _day); break;
		}

	}
	void Difference(int Num, int _year, int _month, int _day)
	{
		cout << "Разница составляет " << abs(year[Num] - _year) << " лет," << abs(month[Num] - _month) << " месяцев," << abs(day[Num] - _day) << " дней \n";
	}
	int Day(int Num)
	{
		return day[Num];
	}
	int Month(int Num)
	{
		return month[Num];
	}
	int Year(int Num)
	{
		return year[Num];
	}
};



int main()
{
	int d, m, y, id, Num;
	char str[200];
	SetConsoleCP(1251);// Для ввода на Кириллице, если не отображает на русском, нужно поменять шрифт консоли на Lucida Console
	SetConsoleOutputCP(1251);//
	setlocale(LC_ALL, "Russian");
	class EventCalendar calendar;
	cout << "Введите номер события(от 0 до 29) ";
	cin >> Num; cout << endl;
	cout << "Введите событие: ";
	cin.ignore();
	cin.getline(str, 200, '\n'); cout << endl;
	cout << "Введите дату события в формате: год месяц день: "; // если дата будет больше 2020 12 31 то программа не запишет ее.
	cin >> y >> m >> d; cout << endl;
	calendar.InputEvent(Num, y, m, d, str);
	calendar.OutEvent(Num); cout << endl;
	cout << "Введите дату, с которой хотите найти разницу в формате: год месяц число: ";
	cin >> y >> m >> d; cout << endl;
	calendar.Difference(Num, y, m, d);
	cout << "Введите на сколько хотите сместить дату события и вперед(1) или назад(2) в формате: год месяц число направление: ";
	cin >> y >> m >> d >> id; cout << endl;
	calendar.ShiftEvent(Num, y, m, d, id);
	calendar.OutEvent(Num);
	system("pause");
}