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
	string Produ�er;
	string Screenwriter;
	string Composer;
	int Fees;
	int Year;
	int Month;
	int Day;
	Information(string _Name = "��� ��������", int _Year = 1, int _Month = 1, int _Fees = 0, int _Day = 1, string _Producer = "�� ������", string _Screenwriter = "�� ������", string _Composer = "�� ������")
	{
		Name = _Name;
		Produ�er = _Producer;
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
		Produ�er = Info.Produ�er;
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
		Produ�er = Info.Produ�er;
		Screenwriter = Info.Screenwriter;
		Composer = Info.Composer;
		Fees = Info.Fees;
		Year = Info.Year;
		Month = Info.Month;
		Day = Info.Day;
		return *this;
	}
	// ���������� > ��� ����������.
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
		return Films[_index].Produ�er;
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
	void AddFilm(string _Name = "��� ��������", int _Year = 1, int _Month = 1, int _Day = 1, int _Fees = 0, string _Producer = "�� ������", string _Screenwriter = "�� ������", string _Composer = "�� ������")
	{
		Information tmp;
		tmp.Name = _Name;
		tmp.Year = _Year;
		tmp.Month = _Month;
		tmp.Day = _Day;
		tmp.Produ�er = _Producer;
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
	void ChangeFilm(int _index, string _Name = "��� ��������", int _Year = 1, int _Month = 1, int _Day = 1, int _Fees = 0, string _Producer = "�� ������", string _Screenwriter = "�� ������", string _Composer = "�� ������")
	{
		Films[_index].Name = _Name;
		Films[_index].Year = _Year;
		Films[_index].Month = _Month;
		Films[_index].Day = _Day;
		Films[_index].Produ�er = _Producer;
		Films[_index].Screenwriter = _Screenwriter;
		Films[_index].Composer = _Composer;
		Films[_index].Fees = _Fees;
	}
	//��������� ����� ��������� � ���� FilmotekaBin.txt � ����� � �������� � �������� ���� � � ����� Filmoteka.txt ��� ��������� ���������, � ����� � ����� FilmotekaRec ��� ����������.
	void SaveFilmoteka()
	{
		ofstream file;
		file.open("Filmoteka.txt");
		if (!file.is_open())
			cout << "������ ��������";
		else
			for (int i = 0; i < Films.size(); i++)
			{
				file << "�������� ������: " << Films[i].Name << endl;
				file << "���� ������: " << Films[i].Year << "." << Films[i].Month << "." << Films[i].Day << endl;
				file << "�����: " << Films[i].Fees << endl;
				file << "��������: " << Films[i].Produ�er << endl;
				file << "���������: " << Films[i].Screenwriter << endl;
				file << "����������: " << Films[i].Composer << endl << endl;
			}
		file.close();
		ofstream File;
		File.open("FilmotekaRec.txt");
		if (!File.is_open())
			cout << "������ ��������";
		else
			for (int i = 0; i < Films.size(); i++)
			{
				File << Films[i].Name << endl;
				File << Films[i].Year << " " << Films[i].Month << " " << Films[i].Day << endl;
				File << Films[i].Fees << endl;
				File << Films[i].Produ�er << endl;
				File << Films[i].Screenwriter << endl;
				File << Films[i].Composer << endl;
			}
		File.close();
		ofstream fil;
		fil.open("FilmotekaBin.txt");
		if (!fil.is_open())
			cout << "������ ��������";
		else
			fil.write((char*)&Films, sizeof(Films));
		fil.close();
	}
	Filmoteka ReadFilmotekaBin(Filmoteka &_Library)
	{
		ifstream file;
		file.open("FilmotekaBin.txt");
		if (!file.is_open())
			cout << "������ ��������";
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
			cout << "������ ��������";
		else
			while (!fout.eof())
			{
				getline(fout, tmp.Name);
				fout >> tmp.Year >> tmp.Month >> tmp.Day;
				fout >> tmp.Fees;
				fout.ignore();
				getline(fout, tmp.Produ�er);
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
	cout << "�������� ������: " << _Library.GetName(_index) << endl;
	cout << "���� ������: " << _Library.GetYear(_index) << "." << _Library.GetMonth(_index) << "." << _Library.GetDay(_index) << endl;
	cout << "�����: " << _Library.GetFees(_index) << endl;
	cout << "��������: " << _Library.GetProducer(_index) << endl;
	cout << "���������: " << _Library.GetScreenwriter(_index) << endl;
	cout << "����������: " << _Library.GetComposer(_index) << endl << endl;
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
		cout << "������� ������� ��������� �� �������." << endl;
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
		cout << "������� � ������ ���� �� �������." << endl;
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
		cout << "����� � ������� ����������� �� ������." << endl;
}
void PrintFees(int _Number, Filmoteka _Library)
{
	if (_Number > _Library.GetNumberFilms())
	{
		cout << "���������� ������������� ������� ��������� ����� ����������. ����� �������� - " << _Library.GetNumberFilms() << endl;
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
		cout << "�� ������� �� ������ ������ " << _Year << " ����" << endl;
		return;
	}
	if (_Number > num)
		cout << "���������� ������������� ������� ��������� ���������� ������� ������� ����. ����� �������� - " << num << endl;
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
	cout << "1. �������� ����� �����" << endl;
	cout << "2. �������� ������ ������" << endl;
	cout << "3. ����� �����" << endl;
	cout << "4. ������� ��� ������ ��������� ���������" << endl;;
	cout << "5. ������� ��� ������, �������� � ������ � ��������� ����" << endl;
	cout << "6. ������� �������� ����� ������� � ����������� ������� " << endl;
	cout << "7. ������� �������� ����� ������� � ����������� ������� � ��������� ���� " << endl;
	cout << "8. ������ ������� ����� �������" << endl;
	cout << "9. ������� ����� " << endl;
	cout << "10. ��������� ���������� � ���� " << endl;
	cout << "11. ������� ���������� �� �����." << endl;
	cout << "12. �����" << endl;
	cout << "��� �����: ";
}
int main()
{
	SetConsoleCP(1251);// ��� ����� �� ���������, ���� �� ���������� �� �������, ����� �������� ����� ������� �� Lucida Console
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");
	string Name, Produ�er, Screenwriter, Composer;
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
			cout << "������� �������� ������: ";
			cin.ignore();
			getline(cin, Name);
			do
			{
				cout << endl << "������� ���� ������(��� ����� �����): ";
				cin >> Year >> Month >> Day;
			} while (!Library.ControlDate(Year, Month, Day));
			cout << endl << "������� �����(� ������): ";
			cin >> Fees;
			cout << endl << "������� ������� ���������: ";
			cin.ignore();
			getline(cin, Produ�er);
			cout << endl << "������� ������� ����������: ";
			getline(cin, Screenwriter);
			cout << endl << "������� ������� �����������: ";
			getline(cin, Composer);
			Library.AddFilm(Name, Year, Month, Day, Fees, Produ�er, Screenwriter, Composer);
			cout << endl << "����� ��������!" << endl;
			system("pause");
			break;
		case 2:
			cout << "������� �������� ������, ������� ������ ��������: ";
			cin.ignore();
			getline(cin, Name);
			if (Library.SearchFilmName(i, Name) < 0)
			{
				cout << endl << "����� � ������ ��������� �� ������.";
				system("pause");
				break;
			}
			j = Library.SearchFilmName(i, Name);
			cout << "������� �������� ������ ������: ";
			getline(cin, Name);
			do
			{
				cout << endl << "������� ���� ������(��� ����� �����): ";
				cin >> Year >> Month >> Day;
			} while (!Library.ControlDate(Year, Month, Day));
			cout << endl << "������� �����(� ������): ";
			cin >> Fees;
			cout << endl << "������� ������� ���������: ";
			cin.ignore();
			getline(cin, Produ�er);
			cout << endl << "������� ������� ����������: ";
			getline(cin, Screenwriter);
			cout << endl << "������� ������� �����������: ";
			getline(cin, Composer);
			Library.ChangeFilm(j, Name, Year, Month, Day, Fees, Produ�er, Screenwriter, Composer);
			cout << "����� �������!" << endl;
			system("pause");
			break;
		case 3:
			cout << "������� �������� ������: ";
			cin.ignore();
			getline(cin, Name);
			cout << endl << "������� ���: ";
			cin >> Year;
			cout << endl;
			PrintFilmSearch(Name, Year, Library);
			system("pause");
			break;
		case 4:
			cout << "������� ������� ���������: ";
			cin.ignore();
			getline(cin, Produ�er);
			PrintFilmProducer(Produ�er, Library);
			system("pause");
			break;
		case 5:
			cout << "������� ���: ";
			cin >> Year;
			PrintFilmYear(Year, Library);
			system("pause");
			break;
		case 6:
			cout << "������� ���������� �������: ";
			cin >> number;
			cout << endl;
			PrintFees(number, Library);
			system("pause");
			break;
		case 7:
			cout << "������� ���������� �������: ";
			cin >> number;
			cout << endl;
			cout << "������� ���: ";
			cin >> Year;
			cout << endl;
			PrintFeesYear(number, Year, Library);
			system("pause");
			break;
		case 8:
			cout << "���������� ������� = " << Library.GetNumberFilms() << endl;
			system("pause");
			break;
		case 9:
			cout << "������� �������� ������, ������� ������ �������: ";
			cin.ignore();
			getline(cin, Name);
			if (Library.SearchFilmName(i, Name) < 0)
			{
				cout << endl << "����� � ������ ��������� �� ������.";
				system("pause");
				break;
			}
			j = Library.SearchFilmName(i, Name);
			Library.DeleteFilm(j);
			cout << "����� ������!" << endl;;
			system("pause");
			break;
		case 10:
			Library.SaveFilmoteka();
			cout << "���� ��������!" << endl;
			system("pause");
			break;
		case 11:
			cout << "1-������� �������� ������; 2-������� � �����: ";
			cin >> j;
			if (j == 1)
			{
				Library.ReadFilmotekaBin(lib);
				cout << endl << "���� ��������!" << endl;
			}
			else
			{
				lib = Library.ReadFilmoteka(lib);
				cout << endl << "���� ��������!" << endl;
			}
			//���� ����������������, �� ����������� ������ ������� , �������� ����� ��������. ������� ����� ��������� � ������ 10.
			//Print(0, lib);
			system("pause");
			break;
		case 12: break;
		default:
			cout << "������ ������� ���. ��������� ����." << endl;
			system("pause");
		}
	}
}