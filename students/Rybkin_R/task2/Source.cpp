#define _CRT_SECURE_NO_WARNINGS
#define strt "Событий нет"

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <string.h>
#include <locale.h>
using namespace std;
class EventCalendar {
	int day[30];
	int	month[30];
	int year[30];
	char **Event;
public:
	EventCalendar(char *str, int Num = -1, int y = 0, int m = 0, int d = 0)//
	{
		Event = (char**)malloc(30 * sizeof(char*));
		for (int i = 0; i < 30; i++)
		{
			year[i] = 0;
			month[i] = 0;
			day[i] = 0;
			Event[i] = (char*)malloc(strlen(strt) + 1);
			strcpy(Event[i], strt);
		}
		if ((Num > -1) && (Num < 30))
		{
			free(Event[Num]);
			Event[Num] = (char*)malloc(strlen(str) + 1);
			strcpy(Event[Num], str);
		}
	}
	~EventCalendar()
	{
		free(Event);
	}
	EventCalendar& operator=(const EventCalendar& calendar)
	{
		for (int i = 0; i < 29; i++)
		{
			day[i] = calendar.day[i];
			month[i] = calendar.month[i];
			year[i] = calendar.year[i];
			free(Event[i]);
			Event[i] = (char*)malloc(strlen(calendar.Event[i]) + 1);
			strcpy(Event[i], calendar.Event[i]);
			return *this;
		}
	}
	void InputEvent(int Num, int _year, int _month, int _day, char *str)
	{
		if ((Num > -1) && (Num < 30))
		{
			if ((_year > 0 && _year < 2020) && (_month > 0 && _month < 13) && (_day > 0 && _day < 32))
			{
				year[Num] = _year;
				month[Num] = _month;
				day[Num] = _day;
				free(Event[Num]);
				Event[Num] = (char*)malloc(strlen(str) + 1);
				strcpy(Event[Num], str);
			}
		}
		else
			cout << "Не удалось установить дату с событием, некорректно задан номер события";
	}
	void OutEvent(int Num)
	{
		cout << year[Num] << "." << month[Num] << "." << day[Num] << " " << Event[Num];
	}
	void ShiftHelp1(int Num, int _year, int _month, int _day)
	{
		if ((_day + day[Num]) > 32)
		{
			month[Num] = month[Num] - 1;
			day[Num] = (_day + day[Num]) - 31;
		}
		else
			day[Num] = day[Num] + _day;

		if ((_month + month[Num]) > 13)
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
	}//Вспомогательная функция для метода ShiftEvrnt
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
	setlocale(LC_ALL, "rus");
	class EventCalendar calendar;
	cout << "Введите номер события ";
	cin >> Num; cout << "\n";
	cout << "Введите событие: ";
	cin >> str; cout << "\n"; // использую sin а не gets, потому что студия не определяет gets
	cout << "Введите дату события в формате: год месяц день: ";
	cin >> y >> m >> d; cout << "\n";
	calendar.InputEvent(Num, y, m, d, str);
	calendar.OutEvent(Num); cout << "\n";
	cout << "Введите дату, с которой хотите найти разницу в формате: год месяц число: ";
	cin >> y >> m >> d; cout << "\n";
	calendar.Difference(Num, y, m, d);
	cout << "Введите на сколько хотите сместить дату события и вперед(1) или назад(2): год месяц число направление: ";
	cin >> y >> m >> d >> id; cout << "\n";
	calendar.ShiftEvent(Num, y, m, d, id);
	calendar.OutEvent(Num);
	system("pause");
}