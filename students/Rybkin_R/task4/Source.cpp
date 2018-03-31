#include <iostream>
#include <clocale>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>
#include <Windows.h>
#include <math.h>

using namespace std;

struct Information
{
	string Name;
	string Produсer;
	string Screenwriter;
	string Composer;
	int Fees;
	int Year;
	int Month;
	int Day;
	Information(string _Name = "Без названия", int _Year = 1, int _Month = 1, int _Fees = 0, int _Day = 1, string _Producer = "Не указан", string _Screenwriter = "Не указан", string _Composer = "не указан")
	{
		Name = _Name;
		Produсer = _Producer;
		Screenwriter = _Screenwriter;
		Composer = _Composer;
		Year = _Year;
		Month = _Month;
		Day = _Day;
		Fees = _Fees;
	}
	Information(Information const &Info)
	{
		Name = Info.Name;
		Produсer = Info.Produсer;
		Screenwriter = Info.Screenwriter;
		Composer = Info.Composer;
		Fees = Info.Fees;
		Year = Info.Year;
		Month = Info.Month;
		Day = Info.Day;
	}
	Information& operator=(const Information &Info)
	{
		if (this == &Info)
			return *this;
		Name = Info.Name;
		Produсer = Info.Produсer;
		Screenwriter = Info.Screenwriter;
		Composer = Info.Composer;
		Fees = Info.Fees;
		Year = Info.Year;
		Month = Info.Month;
		Day = Info.Day;
		return *this;
	}
	// Перегрузка > для сортировки.
	bool operator > (const Information &Info)
	{
		unsigned int i = 0;
		bool flag = false;
		if (Year > Info.Year)
			flag = true;
		if (!flag)
			if (Year == Info.Year)
				while ((i < size(Name)) && (i < size(Info.Name)))
				{
					if (Name[i] < Info.Name[i])
					{
						flag = true;
						break;
					}
					i++;
				}

		return flag;
	}
};
class Filmoteka
{
	vector<Information>Films;
public:
	Filmoteka() {}
	Filmoteka(Filmoteka const & _Filmoteka)
	{
		Films = _Filmoteka.Films;
	}
	Filmoteka& operator = (const Filmoteka & _Filmoteka)
	{
		if (this == &_Filmoteka)
			return *this;
		Films = _Filmoteka.Films;
		return *this;
	}
	vector<Information>& GetFilms()
	{
		return Films;
	}
	void SortAdd()
	{
		if (Films.size() > 1)
		{
			Information tmp;
			for (unsigned int i = 1; i < Films.size(); i++)
				for (int j = i - 1; j >= 0; j--)
					if (Films[j + 1] > Films[j])
					{
						tmp = Films[j + 1];
						Films[j + 1] = Films[j];
						Films[j] = tmp;
					}
		}
	}
	void SortFees()
	{
		if (Films.size() > 1)
		{
			Information tmp;
			for (unsigned int i = 1; i < Films.size(); i++)
				for (int j = i - 1; j >= 0; j--)
					if (Films[j + 1].Fees > Films[j].Fees)
					{
						tmp = Films[j + 1];
						Films[j + 1] = Films[j];
						Films[j] = tmp;
					}
		}
	}
	string GetName(int _index)
	{
		return Films[_index].Name;
	}
	string GetProducer(int _index)
	{
		return Films[_index].Produсer;
	}
	string GetScreenwriter(int _index)
	{
		return Films[_index].Screenwriter;
	}
	string GetComposer(int _index)
	{
		return Films[_index].Composer;
	}
	int GetYear(int _index)
	{
		return Films[_index].Year;
	}
	int GetMonth(int _index)
	{
		return Films[_index].Month;
	}
	int GetDay(int _index)
	{
		return Films[_index].Day;
	}
	int GetFees(int _index)
	{
		return Films[_index].Fees;
	}
	void AddFilm(string _Name = "Без названия", int _Year = 1, int _Month = 1, int _Day = 1, int _Fees = 0, string _Producer = "Не указан", string _Screenwriter = "Не указан", string _Composer = "не указан")
	{
		Information tmp;
		tmp.Name = _Name;
		tmp.Year = _Year;
		tmp.Month = _Month;
		tmp.Day = _Day;
		tmp.Produсer = _Producer;
		tmp.Screenwriter = _Screenwriter;
		tmp.Composer = _Composer;
		tmp.Fees = _Fees;
		Films.push_back(tmp);
		SortAdd();
	}
	int GetNumberFilms()
	{
		return (int)Films.size();
	}
	int SearchFilmName(int tmp, string _Name)
	{
		tmp = -1;
		for (int i = 0; i < Films.size(); i++)
		{
			if (Films[i].Name == _Name)
			{
				tmp = i; ;
				break;
			}
		}
		return tmp;

	}
	void DeleteFilm(int _index)
	{
		Films.erase(Films.begin() + _index);
	}
	bool ControlDate(int _Year, int _Month, int _Day)
	{
		bool flag = true;
		if (_Year < 0)
			flag = false;
		else
			if ((_Month > 12) || (_Month < 1))
				flag = false;
			else
				if (_Day < 0 || _Day>31)
					flag = false;
				else
				{
					if (_Month == 4 || _Month == 6 || _Month == 9 || _Month == 11)
					{
						if (_Day > 30)
							flag = false;
					}
					else
						if (_Month == 2)
						{
							if ((_Year % 4 == 0) || (_Year % 400 == 0))
							{
								if (_Day > 29)
									flag = false;
							}
							else
								if (_Day > 28)
									flag = false;
						}
				}
		return flag;
	}
	void ChangeFilm(int _index, string _Name = "Без названия", int _Year = 1, int _Month = 1, int _Day = 1, int _Fees = 0, string _Producer = "Не указан", string _Screenwriter = "Не указан", string _Composer = "не указан")
	{
		Films[_index].Name = _Name;
		Films[_index].Year = _Year;
		Films[_index].Month = _Month;
		Films[_index].Day = _Day;
		Films[_index].Produсer = _Producer;
		Films[_index].Screenwriter = _Screenwriter;
		Films[_index].Composer = _Composer;
		Films[_index].Fees = _Fees;
	}
	//Фильмотка будет сохранена в файл FilmotekaBin.txt в папке с проектом в бинарном виде и в файле Filmoteka.txt для понятного просмотра, а также в файле FilmotekaRec для считывания.
	void SaveFilmoteka()
	{
		ofstream file;
		file.open("Filmoteka.txt");
		if (!file.is_open())
			cout << "Ошибка открытия";
		else
			for (int i = 0; i < Films.size(); i++)
			{
				file << "Название фильма: " << Films[i].Name << endl;
				file << "Дата выхода: " << Films[i].Year << "." << Films[i].Month << "." << Films[i].Day << endl;
				file << "Сборы: " << Films[i].Fees << endl;
				file << "Режиссер: " << Films[i].Produсer << endl;
				file << "Сценарист: " << Films[i].Screenwriter << endl;
				file << "Композитор: " << Films[i].Composer << endl << endl;
			}
		file.close();
		ofstream File;
		File.open("FilmotekaRec.txt");
		if (!File.is_open())
			cout << "Ошибка открытия";
		else
			for (int i = 0; i < Films.size(); i++)
			{
				File << Films[i].Name << endl;
				File << Films[i].Year << " " << Films[i].Month << " " << Films[i].Day << endl;
				File << Films[i].Fees << endl;
				File << Films[i].Produсer << endl;
				File << Films[i].Screenwriter << endl;
				File << Films[i].Composer << endl;
			}
		File.close();
		ofstream fil;
		fil.open("FilmotekaBin.txt");
		if (!fil.is_open())
			cout << "Ошибка открытия";
		else
			fil.write((char*)&Films, sizeof(Films));
		fil.close();
	}
	Filmoteka ReadFilmotekaBin(Filmoteka &_Library)
	{
		ifstream file;
		file.open("FilmotekaBin.txt");
		if (!file.is_open())
			cout << "Ошибка открытия";
		else
			while (file.read((char*)&_Library.Films, sizeof(Information)))
			{
			}
		file.close();
		return _Library;
	}
	Filmoteka ReadFilmoteka(Filmoteka _Library)
	{
		Information tmp;
		ifstream fout;
		fout.open("FilmotekaRec.txt");
		if (!fout.is_open())
			cout << "Ошибка открытия";
		else
			while (!fout.eof())
			{
				getline(fout, tmp.Name);
				fout >> tmp.Year >> tmp.Month >> tmp.Day;
				fout >> tmp.Fees;
				fout.ignore();
				getline(fout, tmp.Produсer);
				getline(fout, tmp.Screenwriter);
				getline(fout, tmp.Composer);
				fout.ignore();
				_Library.Films.push_back(tmp);
			}
		fout.close();
		return _Library;
	}
};
void Print(int _index, Filmoteka _Library)
{
	cout << "Название фильма: " << _Library.GetName(_index) << endl;
	cout << "Дата выхода: " << _Library.GetYear(_index) << "." << _Library.GetMonth(_index) << "." << _Library.GetDay(_index) << endl;
	cout << "Сборы: " << _Library.GetFees(_index) << endl;
	cout << "Режиссер: " << _Library.GetProducer(_index) << endl;
	cout << "Сценарист: " << _Library.GetScreenwriter(_index) << endl;
	cout << "Композитор: " << _Library.GetComposer(_index) << endl << endl;
}
void PrintFilmProducer(string _Producer, Filmoteka _Library)
{
	bool flag = false;
	for (int i = 0; i < _Library.GetNumberFilms(); i++)
		if (_Library.GetProducer(i) == _Producer)
		{
			Print(i, _Library);
			flag = true;
		}
	if (!flag)
		cout << "Фильмов данного режиссера не найдено." << endl;
}
void PrintFilmYear(int _Year, Filmoteka _Library)
{
	bool flag = false;
	for (int i = 0; i < _Library.GetNumberFilms(); i++)
		if (_Library.GetYear(i) == _Year)
		{
			Print(i, _Library);
			flag = true;
		}
	if (!flag)
		cout << "Фильмов в данном году не найдено." << endl;
}
void PrintFilmSearch(string _Name, int _Year, Filmoteka _Library)
{
	bool flag = false;
	for (int i = 0; i < _Library.GetNumberFilms(); i++)
		if ((_Library.GetName(i) == _Name) && (_Library.GetYear(i) == _Year))
		{
			Print(i, _Library);
			flag = true;
		}
	if (!flag)
		cout << "Фильм с данными параметрами не найден." << endl;
}
void PrintFees(int _Number, Filmoteka _Library)
{
	if (_Number > _Library.GetNumberFilms())
	{
		cout << "Количество запрашиваемых фильмов превышает общее количество. Будет выведено - " << _Library.GetNumberFilms() << endl;
		_Number = _Library.GetNumberFilms();
	}
	_Library.SortFees();
	for (int i = 0; i < _Number; i++)
		Print(i, _Library);
}
void PrintFeesYear(int _Number, int _Year, Filmoteka _Library)
{
	int num = 0;
	for (int i = 0; i < _Library.GetNumberFilms(); i++)
		if (_Library.GetYear(i) == _Year)
			num++;
	if (num == 0)
	{
		cout << "Не найдено ни одного фильма " << _Year << " года" << endl;
		return;
	}
	if (_Number > num)
		cout << "Количество запрашиваемых фильмов превышает количество фильмов данного года. Будет выведено - " << num << endl;
	else
		num = _Number;
	_Library.SortFees();
	int i = 0, k = 0;
	while (i < num)
	{
		if (_Library.GetYear(k) == _Year)
		{
			Print(k, _Library);
			i++;
		}
		k++;
	}
}
void Menu()
{
	cout << "1. Добавить новый фильм" << endl;
	cout << "2. Изменить данные фильма" << endl;
	cout << "3. Найти фильм" << endl;
	cout << "4. Вывести все фильмы заданного режиссера" << endl;;
	cout << "5. Вывести все фильмы, вышедшие в прокат в выбранном году" << endl;
	cout << "6. Вывести заданное число фильмов с наибольшими сборами " << endl;
	cout << "7. Вывести заданное число фильмов с наибольшими сборами в выбранном году " << endl;
	cout << "8. Узнать текущее число фильмов" << endl;
	cout << "9. Удалить фильм " << endl;
	cout << "10. Сохранить фильмотеку в файл " << endl;
	cout << "11. Считать фильмотеку из файла." << endl;
	cout << "12. Выход" << endl;
	cout << "Ваш выбор: ";
}
int main()
{
	SetConsoleCP(1251);// Для ввода на Кириллице, если не отображает на русском, нужно поменять шрифт консоли на Lucida Console
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");
	string Name, Produсer, Screenwriter, Composer;
	int indicator = 0, number = 0, i = 0, j;
	int Year, Month, Day, Fees;
	Filmoteka Library;
	Filmoteka lib;
	while (indicator != 12)
	{
		system("cls");
		Menu();
		cin >> indicator;
		system("cls");
		switch (indicator)
		{
		case 1:
			cout << "Введите название фильма: ";
			cin.ignore();
			getline(cin, Name);
			do
			{
				cout << endl << "Введите дату выхода(Год месяц число): ";
				cin >> Year >> Month >> Day;
			} while (!Library.ControlDate(Year, Month, Day));
			cout << endl << "Введите сборы(в рублях): ";
			cin >> Fees;
			cout << endl << "Введите фамилию режиссера: ";
			cin.ignore();
			getline(cin, Produсer);
			cout << endl << "Введите фамилию сценариста: ";
			getline(cin, Screenwriter);
			cout << endl << "Введите фамилию композитора: ";
			getline(cin, Composer);
			Library.AddFilm(Name, Year, Month, Day, Fees, Produсer, Screenwriter, Composer);
			cout << endl << "Фильм добавлен!" << endl;
			system("pause");
			break;
		case 2:
			cout << "Введите название фильма, который хотите изменить: ";
			cin.ignore();
			getline(cin, Name);
			if (Library.SearchFilmName(i, Name) < 0)
			{
				cout << endl << "Фильм с данным названием не найден.";
				system("pause");
				break;
			}
			j = Library.SearchFilmName(i, Name);
			cout << "Введите название нового фильма: ";
			getline(cin, Name);
			do
			{
				cout << endl << "Введите дату выхода(Год месяц число): ";
				cin >> Year >> Month >> Day;
			} while (!Library.ControlDate(Year, Month, Day));
			cout << endl << "Введите сборы(в рублях): ";
			cin >> Fees;
			cout << endl << "Введите фамилию режиссера: ";
			cin.ignore();
			getline(cin, Produсer);
			cout << endl << "Введите фамилию сценариста: ";
			getline(cin, Screenwriter);
			cout << endl << "Введите фамилию композитора: ";
			getline(cin, Composer);
			Library.ChangeFilm(j, Name, Year, Month, Day, Fees, Produсer, Screenwriter, Composer);
			cout << "Фильм изменен!" << endl;
			system("pause");
			break;
		case 3:
			cout << "Введите название фильма: ";
			cin.ignore();
			getline(cin, Name);
			cout << endl << "Введите год: ";
			cin >> Year;
			cout << endl;
			PrintFilmSearch(Name, Year, Library);
			system("pause");
			break;
		case 4:
			cout << "Введите фамилию режиссера: ";
			cin.ignore();
			getline(cin, Produсer);
			PrintFilmProducer(Produсer, Library);
			system("pause");
			break;
		case 5:
			cout << "Введите год: ";
			cin >> Year;
			PrintFilmYear(Year, Library);
			system("pause");
			break;
		case 6:
			cout << "Введите количество фильмов: ";
			cin >> number;
			cout << endl;
			PrintFees(number, Library);
			system("pause");
			break;
		case 7:
			cout << "Введите количество фильмов: ";
			cin >> number;
			cout << endl;
			cout << "Введите год: ";
			cin >> Year;
			cout << endl;
			PrintFeesYear(number, Year, Library);
			system("pause");
			break;
		case 8:
			cout << "Количество фильмов = " << Library.GetNumberFilms() << endl;
			system("pause");
			break;
		case 9:
			cout << "Введите название фильма, который хотите удалить: ";
			cin.ignore();
			getline(cin, Name);
			if (Library.SearchFilmName(i, Name) < 0)
			{
				cout << endl << "Фильм с данным названием не найден.";
				system("pause");
				break;
			}
			j = Library.SearchFilmName(i, Name);
			Library.DeleteFilm(j);
			cout << "Фильм удален!" << endl;;
			system("pause");
			break;
		case 10:
			Library.SaveFilmoteka();
			cout << "Файл сохранен!" << endl;
			system("pause");
			break;
		case 11:
			cout << "1-Считать бинарный объект; 2-Считать с файла: ";
			cin >> j;
			if (j == 1)
			{
				Library.ReadFilmotekaBin(lib);
				cout << endl << "Файл прочитан!" << endl;
			}
			else
			{
				lib = Library.ReadFilmoteka(lib);
				cout << endl << "Файл прочитан!" << endl;
			}
			//Если раскоментировать, то распечатает первый элемент , считаный любым способом. Сначала нужно сохранить в пункте 10.
			//Print(0, lib);
			system("pause");
			break;
		case 12: break;
		default:
			cout << "Данной команды нет. Проверьте ввод." << endl;
			system("pause");
		}
	}
}