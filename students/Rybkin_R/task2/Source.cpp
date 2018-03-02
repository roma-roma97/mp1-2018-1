#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <string.h>
#include <locale.h>
using namespace std;
class EventCalendar {
	int day;
	int	month;
	int year;
	char *Event;
public:
	bool flag = true;
	EventCalendar(char *str = "События нет", int y = 0, int m = 0, int d = 0)
	{
		year = y;
		month = m;
		day = d;
		Event = new char[strlen(str) + 1];
		strcpy(Event, str);
	}
	~EventCalendar()
	{
		delete[] Event;
	}
	EventCalendar& operator=(const EventCalendar& Event)
	{
		day = Event.day;
		month = Event.month;
		year = Event.year;
		return *this;
	}
	void InputEvent(int _year, int _month, int _day, char *str)
	{
		if ((_year > 0 && _year < 2020) && (_month > 0 && _month < 13) && (_day > 0 && _day < 32))
		{
			year = _year;
			month = _month;
			day = _day;
			delete[] Event;
			Event = new char[sizeof(str) + 1];
			strcpy(Event, str);
			flag = false;
		}
	}
	void OutEvent()
	{
		cout << year << "." << month << "." << day << " " << Event;
	}
	void ShiftHelp1(int _year, int _month, int _day)
	{
		if ((_day + day) > 32)
		{
			month += 1;
			day = (_day + day) - 31;
		}
		else
			day += _day;

		if ((_month + month) > 13)
		{
			year += 1;
			month = (_month + month) - 12;
		}
		else
			month += _month;

		year += _year;
	}
	void ShiftHelp2(int _year, int _month, int _day)
	{
		if ((day - _day) <1)
		{
			month -= 1;
			day = 31 - (_day - day);
		}
		else
			day -= _day;

		if ((month - _month) < 1)
		{
			year -= 1;
			month = 12 - (_month - month);
		}
		else
			month -= _month;

		year -= _year;
	}
	void ShiftEvent(int _year, int _month, int _day, int id)
	{
		switch (id)
		{
		case 1:ShiftHelp1(_year, _month, _day); break;
		case 2:ShiftHelp2(_year, _month, _day); break;
		}

	}
	void Difference(int _year, int _month, int _day)
	{
		cout << "Разница составляет " << abs(year - _year) << " лет," << abs(month - _month) << " месяцев," << abs(day - _day) << " дней \n";
	}
	int Day()
	{
		return day;
	}
	int Month()
	{
		return month;
	}
	int Year()
	{
		return year;
	}

};



int main()
{
	int d, m, y, id;
	char str[200];
	setlocale(LC_ALL, "Russian");
	cout << "Введите событие: ";
	cin >> str; cout << "\n"; // использую sin а не gets, потому что студия не определяет gets
	class EventCalendar calendar(str);
	while (calendar.flag)
	{
		cout << "Введите дату события в формате: год месяц день ";
		cin >> y >> m >> d; cout << "\n";
		calendar.InputEvent(y, m, d, str);
		if (calendar.flag)
			cout << "Некорректно введена дата "; cout << "\n";
	}
	calendar.OutEvent(); cout << "\n";
	cout << "Введите дату, с которой хотите  найти разницу в формате: год месяц число";
	cin >> y >> m >> d; cout << "\n";
	calendar.Difference(y, m, d);
	cout << "Введите на сколько хотите сместить дату события и вперед(1) или назад(2): год месяц число направление: ";
	cin >> y >> m >> d >> id; cout << "\n";
	calendar.ShiftEvent(y, m, d, id);
	calendar.OutEvent();
	system("pause");
}