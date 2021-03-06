#include <iostream>
#include <clocale>
#include <string>
#include <cstdlib>
#include <vector>
#include <Windows.h>
#include <time.h>
#include <fstream>

#define NumberOfSeatsPlaces 100
#define NumberOfSleepingPlaces 18
#define NumberOfCompartmentPlaces 36
#define NumberOfReservedSeatPlaces 54
#define NN "Нижний Новгород"
#define MSK "Москва"
#define CostSeated 1500
#define CostRes 2000
#define CostCom 2700
#define CostSleep 3500

using namespace std;

struct Date
{
	int Year;
	int Month;
	int Day;
	Date(int _Year = 1, int _Month = 1, int _Day = 1) : Year(_Year), Month(_Month), Day(_Day) {};
	Date NextDay()
	{
		Day++;
		if ((Year % 4 == 0) || (Year % 400 == 0))
			if (Month == 2)
				if (Day > 29)
				{
					Day = 1;
					Month++;
					return *this;
				}
		if ((Day > 31) && (Month == 1 || Month == 3 || Month == 5 || Month == 7 || Month == 8 || Month == 10 || Month == 12))
		{
			Day = 1;;
			Month++;
			if (Month > 12)
			{
				Month = 1;
				Year++;
			}
			return *this;
		}
		if ((Day > 30) && (Month == 4 || Month == 6 || Month == 9 || Month == 11))
		{
			Day = 1;
			Month++;
			if (Month > 12)
			{
				Month = 1;
				Year++;
			}
			return *this;
		}
		if (Month == 2)
		{
			if (Day > 28)
			{
				Day = 1;
				Month++;
			}
		}
		return *this;
	}
	bool operator==(const Date &_Date)
	{
		bool flag = false;
		if ((Day == _Date.Day) && (Month == _Date.Month) && (Year = _Date.Year))
			flag = true;
		return flag;
	}
};
struct Time
{
	int Hour;
	int Minutes;
	Time(int _Hour = 0, int _Minutes = 0) : Hour(_Hour), Minutes(_Minutes) {};
	bool operator==(const Time &_Time)
	{
		bool flag = false;
		if ((Hour == _Time.Hour) && (Minutes == _Time.Minutes))
			flag = true;
		return flag;
	}
};
struct InfoName
{
	string Surname;
	string Name;
	string Patronymic;
	InfoName(string _Surname = "", string _Name = "", string _Patronymic = "") :Surname(_Surname), Name(_Name), Patronymic(_Patronymic) {};
};
struct Place
{
	InfoName Name;
	int Reservation;
	int Number;
	bool PurchaseIndicator;
	Place(int _Number = 1, int _Reservation = 0, bool _PurchaseIndicator = false) : Reservation(_Reservation), Number(_Number), PurchaseIndicator(_PurchaseIndicator) {};
};
//Wagons
struct SeatedWagon
{
	float Cost;
	int Number;
	int FreePlace;
	vector<Place> Places;
	SeatedWagon(int _Number = 1, float _Cost = CostSeated, int _FreePlace = NumberOfSeatsPlaces)
	{
		Place Plasess;
		Number = Number;
		Cost = _Cost;
		FreePlace = _FreePlace;
		for (int i = 1; i <= NumberOfSeatsPlaces; i++)
		{
			Plasess.Number = i;
			Places.push_back(Plasess);
		}
	}
	bool ControlPlaces(int _Number)
	{
		bool flag = false;
		if (FreePlace > _Number)
			flag = true;
		return flag;
	}
};
struct ReservedSeat
{
	float Cost;
	int Number;
	int FreePlace;
	vector<Place> Places;
	ReservedSeat(int _Number = 1, float _Cost = CostRes, int _FreePlace = NumberOfReservedSeatPlaces)
	{
		Place Plasess;
		Number = Number;
		Cost = _Cost;
		FreePlace = _FreePlace;
		for (int i = 1; i <= NumberOfReservedSeatPlaces; i++)
		{
			Plasess.Number = i;
			Places.push_back(Plasess);
		}
	}
	bool ControlPlaces(int _Number)
	{
		bool flag = false;
		if (FreePlace > _Number)
			flag = true;
		return flag;
	}
};
struct CompartmentWagon
{
	float Cost;
	int Number;
	int FreePlace;
	vector<Place> Places;
	CompartmentWagon(int _Number = 1, float _Cost = CostCom, int _FreePlace = NumberOfCompartmentPlaces)
	{
		Place Plasess;
		Number = Number;
		Cost = _Cost;
		FreePlace = _FreePlace;
		for (int i = 1; i <= NumberOfCompartmentPlaces; i++)
		{
			Plasess.Number = i;
			Places.push_back(Plasess);
		}
	}
	bool ControlPlaces(int _Number)
	{
		bool flag = false;
		if (FreePlace > _Number)
			flag = true;
		return flag;
	}
};
struct SleepingWagon
{
	float Cost;
	int Number;
	int FreePlace;
	vector<Place> Places;
	SleepingWagon(int _Number = 1, float _Cost = CostSleep, int _FreePlace = NumberOfSleepingPlaces)
	{
		Place Plasess;
		Number = Number;
		Cost = _Cost;
		FreePlace = _FreePlace;
		for (int i = 1; i <= NumberOfSleepingPlaces; i++)
		{
			Plasess.Number = i;
			Places.push_back(Plasess);
		}
	}
	bool ControlPlaces(int _Number)
	{
		bool flag = false;
		if (FreePlace > _Number)
			flag = true;
		return flag;
	}
};
//Trains
struct TrainSwallow
{
	Date Data;
	Time Times;
	int Number;
	string StationDeparture;
	string StationArrival;
	SeatedWagon Wagon[8];
	TrainSwallow(int _Number = 1, string _StationDeparture = NN, string _StationArrival = MSK)
	{
		Number = _Number;
		StationArrival = _StationArrival;
		StationDeparture = _StationDeparture;
		for (int i = 0; i < 8; i++)
			Wagon[i].Number = i + 1;
	}
};
struct TrainCompany
{
	Date Data;
	Time Times;
	int Number;
	string StationDeparture;
	string StationArrival;
	ReservedSeat WagonRes[4];
	CompartmentWagon WagonCom[6];
	SleepingWagon WagonSleep[2];
	TrainCompany(int _Number = 1, string _StationDeparture = NN, string _StationArrival = MSK)
	{
		int tmp = 0;
		StationArrival = _StationArrival;
		StationDeparture = _StationDeparture;
		Number = _Number;
		for (int i = 0; i < 2; i++)
			WagonSleep[i].Number = i + 1;
		for (int i = 2; i < 8; i++)
			WagonCom[tmp++].Number = i + 1;
		tmp = 0;
		for (int i = 8; i < 12; i++)
			WagonRes[tmp++].Number = i + 1;
	}
};
struct TrainFast
{
	Date Data;
	Time Times;
	int Number;
	string StationDeparture;
	string StationArrival;
	ReservedSeat WagonRes[4];
	CompartmentWagon WagonCom[8];
	TrainFast(int _Number = 1, string _StationDeparture = NN, string _StationArrival = MSK)
	{
		int tmp = 0;
		StationArrival = _StationArrival;
		StationDeparture = _StationDeparture;
		for (int i = 0; i < 4; i++)
			WagonCom[tmp++].Number = i + 1;
		tmp = 0;
		for (int i = 4; i < 12; i++)
			WagonRes[tmp++].Number = i + 1;
	}
};
//
struct Ticket
{
	static int ID;
	int id;
	Date Data;
	InfoName Name;
	Time Times;
	string StationOfDeparture;
	string ArrivalStation;
	string View;
	float Cost;
	int NumberTrain;
	int NumberWagon;
	int NumberPlace;
	Ticket(InfoName _Name, Date _Data, float _Cost = 0, int _NumberTrain = 1, int _NumberWagon = 0, int _NumberPlace = 1, string _StationOfDeparture = "", string _ArrivalStation = "", string _View = "Сидячий", int _id = 0)
	{
		StationOfDeparture = _StationOfDeparture;
		ArrivalStation = _ArrivalStation;
		Cost = _Cost;
		NumberTrain = _NumberTrain;
		NumberWagon = _NumberWagon;
		NumberPlace = _NumberPlace;
		View = _View;
		id = _id;
	}
	static int NextID()
	{
		ID++;
		return ID;
	}
	void SetTicket(InfoName _Name, Date _Data, Time _Time, float _Cost = 0, int _NumberTrain = 1, int _NumberWagon = 0, int _NumberPlace = 1, string _StationOfDeparture = "", string _ArrivalStation = "", string _View = "Сидячий", int _id = 0)
	{
		Data = _Data;
		Name = _Name;
		StationOfDeparture = _StationOfDeparture;
		ArrivalStation = _ArrivalStation;
		Cost = _Cost;
		NumberTrain = _NumberTrain;
		NumberWagon = _NumberWagon;
		NumberPlace = _NumberPlace;
		View = _View;
		Times = _Time;
		id = _id;
	}
};
int Ticket::ID = 0;
struct TheGorkyRailway
{
	vector<Ticket> Tickets;
	TrainSwallow SmallowNN_1[30];
	TrainSwallow SmallowNN_2[30];
	TrainSwallow SmallowNN_3[30];
	TrainSwallow SmallowMSK_1[30];
	TrainSwallow SmallowMSK_2[30];
	TrainSwallow SmallowMSK_3[30];
	TrainCompany CompanyNN[30];
	TrainCompany CompanyMSK[30];
	TrainFast FastNN[30];
	TrainFast FastMSK[30];
	TheGorkyRailway()
	{
		for (int i = 0; i < 30; i++)
		{
			SmallowNN_1[i].Number = 10;
			SmallowNN_1[i].Times.Hour = 5;
			SmallowNN_1[i].Times.Minutes = 0;
			SmallowNN_1[i].StationDeparture = NN;
			SmallowNN_1[i].StationArrival = MSK;
			SmallowNN_2[i].Number = 20;
			SmallowNN_2[i].Times.Hour = 7;
			SmallowNN_2[i].Times.Minutes = 0;
			SmallowNN_2[i].StationDeparture = NN;
			SmallowNN_2[i].StationArrival = MSK;
			SmallowNN_3[i].Number = 30;
			SmallowNN_3[i].Times.Hour = 11;
			SmallowNN_3[i].Times.Minutes = 0;
			SmallowNN_3[i].StationDeparture = NN;
			SmallowNN_3[i].StationArrival = MSK;
			SmallowMSK_1[i].Number = 40;
			SmallowMSK_1[i].Times.Hour = 10;
			SmallowMSK_1[i].Times.Minutes = 0;
			SmallowMSK_1[i].StationDeparture = MSK;
			SmallowMSK_1[i].StationArrival = NN;
			SmallowMSK_2[i].Number = 50;
			SmallowMSK_2[i].Times.Hour = 15;
			SmallowMSK_2[i].Times.Minutes = 0;
			SmallowMSK_2[i].StationDeparture = MSK;
			SmallowMSK_2[i].StationArrival = NN;
			SmallowMSK_3[i].Number = 60;
			SmallowMSK_3[i].Times.Hour = 19;
			SmallowMSK_3[i].Times.Minutes = 0;
			SmallowMSK_3[i].StationDeparture = MSK;
			SmallowMSK_3[i].StationArrival = NN;
			CompanyNN[i].Number = 70;
			CompanyNN[i].Times.Hour = 0;
			CompanyNN[i].Times.Minutes = 0;
			CompanyNN[i].StationDeparture = NN;
			CompanyNN[i].StationArrival = MSK;
			CompanyMSK[i].Number = 80;
			CompanyMSK[i].Times.Hour = 21;
			CompanyMSK[i].Number = 00;
			CompanyMSK[i].StationDeparture = MSK;
			CompanyMSK[i].StationArrival = NN;
			FastNN[i].Number = 90;
			FastNN[i].Times.Hour = 1;
			FastNN[i].Times.Minutes = 30;
			FastNN[i].StationDeparture = NN;
			FastNN[i].StationArrival = MSK;
			FastMSK[i].Number = 100;
			FastMSK[i].Times.Hour = 13;
			FastMSK[i].Times.Minutes = 0;
			FastMSK[i].StationDeparture = MSK;
			FastMSK[i].StationArrival = NN;
		}
	}
	void CreatedData(Date _Date)
	{
		SmallowNN_1[0].Data = _Date;
		SmallowNN_2[0].Data = _Date;
		SmallowNN_3[0].Data = _Date;
		SmallowMSK_1[0].Data = _Date;
		SmallowMSK_2[0].Data = _Date;
		SmallowMSK_3[0].Data = _Date;
		CompanyNN[0].Data = _Date;
		CompanyMSK[0].Data = _Date;
		FastNN[0].Data = _Date;
		FastMSK[0].Data = _Date;
		for (int i = 1; i < 30; i++)
		{
			SmallowNN_1[i].Data = SmallowNN_1[i - 1].Data.NextDay();
			SmallowNN_2[i].Data = SmallowNN_2[i - 1].Data.NextDay();
			SmallowNN_3[i].Data = SmallowNN_3[i - 1].Data.NextDay();
			SmallowMSK_1[i].Data = SmallowMSK_1[i - 1].Data.NextDay();
			SmallowMSK_2[i].Data = SmallowMSK_2[i - 1].Data.NextDay();
			SmallowMSK_3[i].Data = SmallowMSK_3[i - 1].Data.NextDay();
			CompanyNN[i].Data = CompanyNN[i - 1].Data.NextDay();
			CompanyMSK[i].Data = CompanyMSK[i - 1].Data.NextDay();;
			FastNN[i].Data = FastNN[i - 1].Data.NextDay();
			FastMSK[i].Data = FastNN[i - 1].Data.NextDay();
		}
	}
};
class RailwayTicketOffice
{
	TheGorkyRailway Gorky;
public:
	RailwayTicketOffice(Date _Date)
	{
		Gorky.CreatedData(_Date);
	}
	bool DeleteTicket(int _id)
	{
		bool flag = false;
		for (unsigned int i = 0; i < size(Gorky.Tickets); i++)
		{
			if (Gorky.Tickets[i].id == _id)
			{
				for (int j = 0; j < 30; j++)
					if (Gorky.SmallowNN_1[j].Data == Gorky.Tickets[i].Data)
						if (Gorky.Tickets[i].StationOfDeparture == NN)
						{
							if (Gorky.SmallowNN_1[j].Times == Gorky.Tickets[i].Times)
							{
								Gorky.SmallowNN_1[j].Wagon[Gorky.Tickets[i].NumberWagon].Places[Gorky.Tickets[i].NumberPlace].Reservation = 0;
								Gorky.SmallowNN_1[j].Wagon[Gorky.Tickets[i].NumberWagon].Places[Gorky.Tickets[i].NumberPlace].PurchaseIndicator = false;
								Gorky.SmallowNN_1[j].Wagon[Gorky.Tickets[i].NumberWagon].FreePlace++;
							}
							if (Gorky.SmallowNN_2[j].Times == Gorky.Tickets[i].Times)
							{
								Gorky.SmallowNN_2[j].Wagon[Gorky.Tickets[i].NumberWagon].Places[Gorky.Tickets[i].NumberPlace].Reservation = 0;
								Gorky.SmallowNN_2[j].Wagon[Gorky.Tickets[i].NumberWagon].Places[Gorky.Tickets[i].NumberPlace].PurchaseIndicator = false;
								Gorky.SmallowNN_2[j].Wagon[Gorky.Tickets[i].NumberWagon].FreePlace++;
							}
							if (Gorky.SmallowNN_3[j].Times == Gorky.Tickets[i].Times)
							{
								Gorky.SmallowNN_3[j].Wagon[Gorky.Tickets[i].NumberWagon].Places[Gorky.Tickets[i].NumberPlace].Reservation = 0;
								Gorky.SmallowNN_3[j].Wagon[Gorky.Tickets[i].NumberWagon].Places[Gorky.Tickets[i].NumberPlace].PurchaseIndicator = false;
								Gorky.SmallowNN_3[j].Wagon[Gorky.Tickets[i].NumberWagon].FreePlace++;
							}
							if (Gorky.CompanyNN[j].Times == Gorky.Tickets[i].Times)
							{
								if (Gorky.Tickets[i].View == "СВ")
								{
									Gorky.CompanyNN[j].WagonSleep[Gorky.Tickets[i].NumberWagon - 1].Places[Gorky.Tickets[i].NumberPlace].Reservation = 0;
									Gorky.CompanyNN[j].WagonSleep[Gorky.Tickets[i].NumberWagon - 1].Places[Gorky.Tickets[i].NumberPlace].PurchaseIndicator = false;
									Gorky.CompanyNN[j].WagonSleep[Gorky.Tickets[i].NumberWagon - 1].FreePlace++;
								}
								if (Gorky.Tickets[i].View == "Купе")
								{
									Gorky.CompanyNN[j].WagonCom[Gorky.Tickets[i].NumberWagon - 3].Places[Gorky.Tickets[i].NumberPlace].Reservation = 0;
									Gorky.CompanyNN[j].WagonCom[Gorky.Tickets[i].NumberWagon - 3].Places[Gorky.Tickets[i].NumberPlace].PurchaseIndicator = false;
									Gorky.CompanyNN[j].WagonCom[Gorky.Tickets[i].NumberWagon - 3].FreePlace++;
								}
								else
								{
									Gorky.CompanyNN[j].WagonRes[Gorky.Tickets[i].NumberWagon - 9].Places[Gorky.Tickets[i].NumberPlace].Reservation = 0;
									Gorky.CompanyNN[j].WagonRes[Gorky.Tickets[i].NumberWagon - 9].Places[Gorky.Tickets[i].NumberPlace].PurchaseIndicator = false;
									Gorky.CompanyNN[j].WagonRes[Gorky.Tickets[i].NumberWagon - 9].FreePlace++;
								}

							}
							if (Gorky.FastNN[j].Times == Gorky.Tickets[i].Times)
							{
								if (Gorky.Tickets[i].View == "Купе")
								{
									Gorky.FastNN[j].WagonCom[Gorky.Tickets[i].NumberWagon - 1].Places[Gorky.Tickets[i].NumberPlace].Reservation = 0;
									Gorky.FastNN[j].WagonCom[Gorky.Tickets[i].NumberWagon - 1].Places[Gorky.Tickets[i].NumberPlace].PurchaseIndicator = false;
									Gorky.FastNN[j].WagonCom[Gorky.Tickets[i].NumberWagon - 1].FreePlace++;
								}
								else
								{
									Gorky.FastNN[j].WagonRes[Gorky.Tickets[i].NumberWagon - 5].Places[Gorky.Tickets[i].NumberPlace].Reservation = 0;
									Gorky.FastNN[j].WagonRes[Gorky.Tickets[i].NumberWagon - 5].Places[Gorky.Tickets[i].NumberPlace].PurchaseIndicator = false;
									Gorky.FastNN[j].WagonRes[Gorky.Tickets[i].NumberWagon - 5].FreePlace++;
								}
							}
						}
						else
						{
							if (Gorky.SmallowMSK_1[j].Times == Gorky.Tickets[i].Times)
							{
								Gorky.SmallowMSK_1[j].Wagon[Gorky.Tickets[i].NumberWagon].Places[Gorky.Tickets[i].NumberPlace].Reservation = 0;
								Gorky.SmallowMSK_1[j].Wagon[Gorky.Tickets[i].NumberWagon].Places[Gorky.Tickets[i].NumberPlace].PurchaseIndicator = false;
								Gorky.SmallowMSK_1[j].Wagon[Gorky.Tickets[i].NumberWagon].FreePlace++;
							}
							if (Gorky.SmallowMSK_2[j].Times == Gorky.Tickets[i].Times)
							{
								Gorky.SmallowMSK_2[j].Wagon[Gorky.Tickets[i].NumberWagon].Places[Gorky.Tickets[i].NumberPlace].Reservation = 0;
								Gorky.SmallowMSK_2[j].Wagon[Gorky.Tickets[i].NumberWagon].Places[Gorky.Tickets[i].NumberPlace].PurchaseIndicator = false;
								Gorky.SmallowMSK_2[j].Wagon[Gorky.Tickets[i].NumberWagon].FreePlace++;
							}
							if (Gorky.SmallowMSK_3[j].Times == Gorky.Tickets[i].Times)
							{
								Gorky.SmallowMSK_3[j].Wagon[Gorky.Tickets[i].NumberWagon].Places[Gorky.Tickets[i].NumberPlace].Reservation = 0;
								Gorky.SmallowMSK_3[j].Wagon[Gorky.Tickets[i].NumberWagon].Places[Gorky.Tickets[i].NumberPlace].PurchaseIndicator = false;
								Gorky.SmallowMSK_3[j].Wagon[Gorky.Tickets[i].NumberWagon].FreePlace++;
							}
							if (Gorky.CompanyMSK[j].Times == Gorky.Tickets[i].Times)
							{
								if (Gorky.Tickets[i].View == "СВ")
								{
									Gorky.CompanyMSK[j].WagonSleep[Gorky.Tickets[i].NumberWagon - 1].Places[Gorky.Tickets[i].NumberPlace].Reservation = 0;
									Gorky.CompanyMSK[j].WagonSleep[Gorky.Tickets[i].NumberWagon - 1].Places[Gorky.Tickets[i].NumberPlace].PurchaseIndicator = false;
									Gorky.CompanyMSK[j].WagonSleep[Gorky.Tickets[i].NumberWagon - 1].FreePlace++;
								}
								if (Gorky.Tickets[i].View == "Купе")
								{
									Gorky.CompanyMSK[j].WagonCom[Gorky.Tickets[i].NumberWagon - 3].Places[Gorky.Tickets[i].NumberPlace].Reservation = 0;
									Gorky.CompanyMSK[j].WagonCom[Gorky.Tickets[i].NumberWagon - 3].Places[Gorky.Tickets[i].NumberPlace].PurchaseIndicator = false;
									Gorky.CompanyMSK[j].WagonCom[Gorky.Tickets[i].NumberWagon - 3].FreePlace++;
								}
								else
								{
									Gorky.CompanyMSK[j].WagonRes[Gorky.Tickets[i].NumberWagon - 9].Places[Gorky.Tickets[i].NumberPlace].Reservation = 0;
									Gorky.CompanyMSK[j].WagonRes[Gorky.Tickets[i].NumberWagon - 9].Places[Gorky.Tickets[i].NumberPlace].PurchaseIndicator = false;
									Gorky.CompanyMSK[j].WagonRes[Gorky.Tickets[i].NumberWagon - 9].FreePlace++;
								}

							}
							if (Gorky.FastMSK[j].Times == Gorky.Tickets[i].Times)
							{
								if (Gorky.Tickets[i].View == "Купе")
								{
									Gorky.FastMSK[j].WagonCom[Gorky.Tickets[i].NumberWagon - 1].Places[Gorky.Tickets[i].NumberPlace].Reservation = 0;
									Gorky.FastMSK[j].WagonCom[Gorky.Tickets[i].NumberWagon - 1].Places[Gorky.Tickets[i].NumberPlace].PurchaseIndicator = false;
									Gorky.FastMSK[j].WagonCom[Gorky.Tickets[i].NumberWagon - 1].FreePlace++;
								}
								else
								{
									Gorky.FastMSK[j].WagonRes[Gorky.Tickets[i].NumberWagon - 5].Places[Gorky.Tickets[i].NumberPlace].Reservation = 0;
									Gorky.FastMSK[j].WagonRes[Gorky.Tickets[i].NumberWagon - 5].Places[Gorky.Tickets[i].NumberPlace].PurchaseIndicator = false;
									Gorky.FastMSK[j].WagonRes[Gorky.Tickets[i].NumberWagon - 5].FreePlace++;
								}
							}
						}
				flag = true;
			}
			Gorky.Tickets.erase(Gorky.Tickets.begin() + i);
			ReservCopy();
		}
		return flag;
	}
	bool ControlFreePlaces(Date _Date, string _Departure, Time _Time, int _Number, string _View)
	{
		bool flag = false;
		for (int j = 0; j < 30; j++)
			if (Gorky.SmallowNN_1[j].Data == _Date)
				if (_Departure == NN)
				{
					if (Gorky.SmallowNN_1[j].Times == _Time)
					{
						for (int i = 0; i < 8; i++)
							if (Gorky.SmallowNN_1[j].Wagon[i].ControlPlaces(_Number))
							{
								flag = true;
								break;
							}
						break;
					}
					if (Gorky.SmallowNN_2[j].Times == _Time)
					{
						for (int i = 0; i < 8; i++)
							if (Gorky.SmallowNN_2[j].Wagon[i].ControlPlaces(_Number))
							{
								flag = true;
								break;
							}
						break;
					}
					if (Gorky.SmallowNN_3[j].Times == _Time)
					{
						for (int i = 0; i < 8; i++)
							if (Gorky.SmallowNN_3[j].Wagon[i].ControlPlaces(_Number))
							{
								flag = true;
								break;
							}
						break;
					}
					if (Gorky.CompanyNN[j].Times == _Time)
					{
						if (_View == "СВ")
						{
							for (int i = 0; i < 2; i++)
								if (Gorky.CompanyNN[j].WagonSleep[i].ControlPlaces(_Number))
								{
									flag = true;
									break;
								}
							break;
						}
						if (_View == "Купе")
						{
							for (int i = 0; i < 6; i++)
								if (Gorky.CompanyNN[j].WagonCom[i].ControlPlaces(_Number))
								{
									flag = true;
									break;
								}
							break;
						}
						else
						{
							for (int i = 0; i < 4; i++)
								if (Gorky.CompanyNN[j].WagonRes[i].ControlPlaces(_Number))
								{
									flag = true;
									break;
								}
							break;
						}

					}
					if (Gorky.FastNN[j].Times == _Time)
					{
						if (_View == "Купе")
						{
							for (int i = 0; i < 8; i++)
								if (Gorky.FastNN[j].WagonCom[i].ControlPlaces(_Number))
								{
									flag = true;
									break;
								}
							break;
						}
						else
						{
							for (int i = 0; i < 4; i++)
								if (Gorky.CompanyNN[j].WagonRes[i].ControlPlaces(_Number))
								{
									flag = true;
									break;
								}
							break;
						}
					}
				}
				else
				{
					if (Gorky.SmallowMSK_1[j].Times == _Time)
					{
						for (int i = 0; i < 8; i++)
							if (Gorky.SmallowMSK_1[j].Wagon[i].ControlPlaces(_Number))
							{
								flag = true;
								break;
							}
						break;
					}
					if (Gorky.SmallowMSK_2[j].Times == _Time)
					{
						for (int i = 0; i < 8; i++)
							if (Gorky.SmallowMSK_2[j].Wagon[i].ControlPlaces(_Number))
							{
								flag = true;
								break;
							}
						break;
					}
					if (Gorky.SmallowMSK_3[j].Times == _Time)
					{
						for (int i = 0; i < 8; i++)
							if (Gorky.SmallowMSK_3[j].Wagon[i].ControlPlaces(_Number))
							{
								flag = true;
								break;
							}
						break;
					}
					if (Gorky.CompanyMSK[j].Times == _Time)
					{
						if (_View == "СВ")
						{
							for (int i = 0; i < 2; i++)
								if (Gorky.CompanyMSK[j].WagonSleep[i].ControlPlaces(_Number))
								{
									flag = true;
									break;
								}
							break;
						}
						if (_View == "Купе")
						{
							for (int i = 0; i < 6; i++)
								if (Gorky.CompanyMSK[j].WagonCom[i].ControlPlaces(_Number))
								{
									flag = true;
									break;
								}
							break;
						}
						else
						{
							for (int i = 0; i < 4; i++)
								if (Gorky.CompanyMSK[j].WagonRes[i].ControlPlaces(_Number))
								{
									flag = true;
									break;
								}
							break;
						}

					}
					if (Gorky.FastMSK[j].Times == _Time)
					{
						if (_View == "Купе")
						{
							for (int i = 0; i < 8; i++)
								if (Gorky.FastMSK[j].WagonCom[i].ControlPlaces(_Number))
								{
									flag = true;
									break;
								}
							break;
						}
						else
						{
							for (int i = 0; i < 4; i++)
								if (Gorky.CompanyMSK[j].WagonRes[i].ControlPlaces(_Number))
								{
									flag = true;
									break;
								}
							break;
						}
					}
				}
		return flag;
	}
	bool ReservePlaces(Date _Date, string _Departure, Time _Time, InfoName _Name, int _Number, string _View)
	{
		Ticket Tick(_Name, _Date);
		int LastNumberPlace = 0;
		int tmp = 0;
		bool flag = false;
		if (ControlFreePlaces(_Date, _Departure, _Time, _Number, _View))
		{
			for (int j = 0; j < 30; j++)
				if (Gorky.SmallowNN_1[j].Data == _Date)
					if (_Departure == NN)
					{
						if (Gorky.SmallowNN_1[j].Times == _Time)
						{
							for (int i = 0; i < 8; i++)
								if (Gorky.SmallowNN_1[j].Wagon[i].ControlPlaces(_Number))
								{
									while (tmp <= _Number)
									{
										for (LastNumberPlace; LastNumberPlace < NumberOfSeatsPlaces; LastNumberPlace++)
											if (Gorky.SmallowNN_1[j].Wagon[i].Places[LastNumberPlace].Reservation == 0)
											{
												Gorky.SmallowNN_1[j].Wagon[i].Places[LastNumberPlace].Reservation = 1;
												Gorky.SmallowNN_1[j].Wagon[i].Places[LastNumberPlace].Name = _Name;
												Tick.SetTicket(_Name, _Date, _Time, CostSeated, Gorky.SmallowNN_1[1].Number, Gorky.SmallowNN_1[j].Wagon[i].Number, Gorky.SmallowNN_2[j].Wagon[i].Places[LastNumberPlace].Number, NN, MSK, _View, Ticket::NextID());
												Gorky.Tickets.push_back(Tick);
												tmp++;
												break;
											}
									}
									flag = true;
									break;
								}

						}
						if (Gorky.SmallowNN_2[j].Times == _Time)
						{
							for (int i = 0; i < 8; i++)
								if (Gorky.SmallowNN_2[j].Wagon[i].ControlPlaces(_Number))
								{
									while (tmp <= _Number)
									{
										for (LastNumberPlace; LastNumberPlace < NumberOfSeatsPlaces; LastNumberPlace++)
											if (Gorky.SmallowNN_2[j].Wagon[i].Places[LastNumberPlace].Reservation == 0)
											{
												Gorky.SmallowNN_2[j].Wagon[i].Places[LastNumberPlace].Reservation = 1;
												Gorky.SmallowNN_2[j].Wagon[i].Places[LastNumberPlace].Name = _Name;
												Tick.SetTicket(_Name, _Date, _Time, CostSeated, Gorky.SmallowNN_2[1].Number, Gorky.SmallowNN_2[j].Wagon[i].Number, Gorky.SmallowNN_2[j].Wagon[i].Places[LastNumberPlace].Number, NN, MSK, _View, Ticket::NextID());
												Gorky.Tickets.push_back(Tick);
												tmp++;
												break;
											}
									}
									flag = true;
									break;
								}
							break;
						}
						if (Gorky.SmallowNN_3[j].Times == _Time)
						{
							for (int i = 0; i < 8; i++)
								if (Gorky.SmallowNN_3[j].Wagon[i].ControlPlaces(_Number))
								{
									while (tmp <= _Number)
									{
										for (LastNumberPlace; LastNumberPlace < NumberOfSeatsPlaces; LastNumberPlace++)
											if (Gorky.SmallowNN_3[j].Wagon[i].Places[LastNumberPlace].Reservation == 0)
											{
												Gorky.SmallowNN_3[j].Wagon[i].Places[LastNumberPlace].Reservation = 1;
												Gorky.SmallowNN_3[j].Wagon[i].Places[LastNumberPlace].Name = _Name;
												Tick.SetTicket(_Name, _Date, _Time, CostSeated, Gorky.SmallowNN_3[1].Number, Gorky.SmallowNN_3[j].Wagon[i].Number, Gorky.SmallowNN_3[j].Wagon[i].Places[LastNumberPlace].Number, NN, MSK, _View, Ticket::NextID());
												Gorky.Tickets.push_back(Tick);
												tmp++;
												break;
											}
									}
									flag = true;
									break;
								}
							break;
						}
						if (Gorky.CompanyNN[j].Times == _Time)
						{
							if (_View == "СВ")
							{
								for (int i = 0; i < 2; i++)
									if (Gorky.CompanyNN[j].WagonSleep[i].ControlPlaces(_Number))
									{
										while (tmp <= _Number)
										{
											for (LastNumberPlace; LastNumberPlace < NumberOfSeatsPlaces; LastNumberPlace++)
												if (Gorky.CompanyNN[j].WagonSleep[i].Places[LastNumberPlace].Reservation == 0)
												{
													Gorky.CompanyNN[j].WagonSleep[i].Places[LastNumberPlace].Reservation = 1;
													Gorky.CompanyNN[j].WagonSleep[i].Places[LastNumberPlace].Name = _Name;
													Tick.SetTicket(_Name, _Date, _Time, CostSleep, Gorky.CompanyNN[0].Number, Gorky.CompanyNN[j].WagonSleep[i].Number, Gorky.CompanyNN[j].WagonSleep[i].Places[LastNumberPlace].Number, NN, MSK, _View, Ticket::NextID());
													Gorky.Tickets.push_back(Tick);
													tmp++;
													break;
												}
										}
										flag = true;
										break;
									}
								break;
							}
							if (_View == "Купе")
							{
								for (int i = 0; i < 6; i++)
									if (Gorky.CompanyNN[j].WagonCom[i].ControlPlaces(_Number))
									{
										while (tmp <= _Number)
										{
											for (LastNumberPlace; LastNumberPlace < NumberOfSeatsPlaces; LastNumberPlace++)
												if (Gorky.CompanyNN[j].WagonCom[i].Places[LastNumberPlace].Reservation == 0)
												{
													Gorky.CompanyNN[j].WagonCom[i].Places[LastNumberPlace].Reservation = 1;
													Gorky.CompanyNN[j].WagonCom[i].Places[LastNumberPlace].Name = _Name;
													Tick.SetTicket(_Name, _Date, _Time, CostCom, Gorky.CompanyNN[0].Number, Gorky.CompanyNN[j].WagonCom[i].Number, Gorky.CompanyNN[j].WagonCom[i].Places[LastNumberPlace].Number, NN, MSK, _View, Ticket::NextID());
													Gorky.Tickets.push_back(Tick);
													tmp++;
													break;
												}
										}
										flag = true;
										break;
									}
								break;
							}
							else
							{
								for (int i = 0; i < 4; i++)
									if (Gorky.CompanyNN[j].WagonRes[i].ControlPlaces(_Number))
									{
										while (tmp <= _Number)
										{
											for (LastNumberPlace; LastNumberPlace < NumberOfSeatsPlaces; LastNumberPlace++)
												if (Gorky.CompanyNN[j].WagonRes[i].Places[LastNumberPlace].Reservation == 0)
												{
													Gorky.CompanyNN[j].WagonRes[i].Places[LastNumberPlace].Reservation = 1;
													Gorky.CompanyNN[j].WagonRes[i].Places[LastNumberPlace].Name = _Name;
													Tick.SetTicket(_Name, _Date, _Time, CostRes, Gorky.CompanyNN[0].Number, Gorky.CompanyNN[j].WagonRes[i].Number, Gorky.CompanyNN[j].WagonRes[i].Places[LastNumberPlace].Number, NN, MSK, _View, Ticket::NextID());
													Gorky.Tickets.push_back(Tick);
													tmp++;
													break;
												}
										}
										flag = true;
										break;
									}
								break;
							}
						}
						if (Gorky.FastNN[j].Times == _Time)
						{
							if (_View == "Купе")
							{
								for (int i = 0; i < 8; i++)
									if (Gorky.FastNN[j].WagonCom[i].ControlPlaces(_Number))
									{
										while (tmp <= _Number)
										{
											for (LastNumberPlace; LastNumberPlace < NumberOfSeatsPlaces; LastNumberPlace++)
												if (Gorky.FastNN[j].WagonCom[i].Places[LastNumberPlace].Reservation == 0)
												{
													Gorky.FastNN[j].WagonCom[i].Places[LastNumberPlace].Reservation = 1;
													Gorky.FastNN[j].WagonCom[i].Places[LastNumberPlace].Name = _Name;
													Tick.SetTicket(_Name, _Date, _Time, CostCom, Gorky.FastNN[1].Number, Gorky.FastNN[j].WagonCom[i].Number, Gorky.FastNN[j].WagonCom[i].Places[LastNumberPlace].Number, NN, MSK, _View, Ticket::NextID());
													Gorky.Tickets.push_back(Tick);
													tmp++;
													break;
												}
										}
										flag = true;
										break;
									}
								break;
							}
							else
							{
								for (int i = 0; i < 4; i++)
									if (Gorky.FastNN[j].WagonRes[i].ControlPlaces(_Number))
									{
										while (tmp <= _Number)
										{
											for (LastNumberPlace; LastNumberPlace < NumberOfSeatsPlaces; LastNumberPlace++)
												if (Gorky.FastNN[j].WagonRes[i].Places[LastNumberPlace].Reservation == 0)
												{
													Gorky.FastNN[j].WagonRes[i].Places[LastNumberPlace].Reservation = 1;
													Gorky.FastNN[j].WagonRes[i].Places[LastNumberPlace].Name = _Name;
													Tick.SetTicket(_Name, _Date, _Time, CostRes, Gorky.FastNN[1].Number, Gorky.CompanyNN[j].WagonRes[i].Number, Gorky.FastNN[j].WagonRes[i].Places[LastNumberPlace].Number, NN, MSK, _View, Ticket::NextID());
													Gorky.Tickets.push_back(Tick);
													tmp++;
													break;
												}
										}
										flag = true;
										break;
									}
								break;
							}
						}
					}
					else
					{
						if (Gorky.SmallowMSK_1[j].Times == _Time)
						{
							for (int i = 0; i < 8; i++)
								if (Gorky.SmallowMSK_1[j].Wagon[i].ControlPlaces(_Number))
								{
									while (tmp <= _Number)
									{
										for (LastNumberPlace; LastNumberPlace < NumberOfSeatsPlaces; LastNumberPlace++)
											if (Gorky.SmallowMSK_1[j].Wagon[i].Places[LastNumberPlace].Reservation == 0)
											{
												Gorky.SmallowMSK_1[j].Wagon[i].Places[LastNumberPlace].Reservation = 1;
												Gorky.SmallowMSK_1[j].Wagon[i].Places[LastNumberPlace].Name = _Name;
												Tick.SetTicket(_Name, _Date, _Time, CostSeated, Gorky.SmallowMSK_1[1].Number, Gorky.SmallowMSK_1[j].Wagon[i].Number, Gorky.SmallowMSK_1[j].Wagon[i].Places[LastNumberPlace].Number, MSK, NN, _View, Ticket::NextID());
												Gorky.Tickets.push_back(Tick);
												tmp++;
												break;
											}
									}
									flag = true;
									break;
								}
							break;
						}
						if (Gorky.SmallowMSK_2[j].Times == _Time)
						{
							for (int i = 0; i < 8; i++)
								if (Gorky.SmallowMSK_2[j].Wagon[i].ControlPlaces(_Number))
								{
									while (tmp <= _Number)
									{
										for (LastNumberPlace; LastNumberPlace < NumberOfSeatsPlaces; LastNumberPlace++)
											if (Gorky.SmallowMSK_2[j].Wagon[i].Places[LastNumberPlace].Reservation == 0)
											{
												Gorky.SmallowMSK_2[j].Wagon[i].Places[LastNumberPlace].Reservation = 1;
												Gorky.SmallowMSK_2[j].Wagon[i].Places[LastNumberPlace].Name = _Name;
												Tick.SetTicket(_Name, _Date, _Time, CostSeated, Gorky.SmallowMSK_2[1].Number, Gorky.SmallowMSK_2[j].Wagon[i].Number, Gorky.SmallowMSK_2[j].Wagon[i].Places[LastNumberPlace].Number, MSK, NN, _View, Ticket::NextID());
												Gorky.Tickets.push_back(Tick);
												tmp++;
												break;
											}
									}
									flag = true;
									break;
								}
							break;
						}
						if (Gorky.SmallowMSK_3[j].Times == _Time)
						{
							for (int i = 0; i < 8; i++)
								if (Gorky.SmallowMSK_3[j].Wagon[i].ControlPlaces(_Number))
								{
									while (tmp <= _Number)
									{
										for (LastNumberPlace; LastNumberPlace < NumberOfSeatsPlaces; LastNumberPlace++)
											if (Gorky.SmallowMSK_3[j].Wagon[i].Places[LastNumberPlace].Reservation == 0)
											{
												Gorky.SmallowMSK_3[j].Wagon[i].Places[LastNumberPlace].Reservation = 1;
												Gorky.SmallowMSK_3[j].Wagon[i].Places[LastNumberPlace].Name = _Name;
												Tick.SetTicket(_Name, _Date, _Time, CostSeated, Gorky.SmallowMSK_3[1].Number, Gorky.SmallowMSK_3[j].Wagon[i].Number, Gorky.SmallowMSK_3[j].Wagon[i].Places[LastNumberPlace].Number, MSK, NN, _View, Ticket::NextID());
												Gorky.Tickets.push_back(Tick);
												tmp++;
												break;
											}
									}
									flag = true;
									break;
								}
							break;
						}
						if (Gorky.CompanyMSK[j].Times == _Time)
						{
							if (_View == "СВ")
							{
								for (int i = 0; i < 2; i++)
									if (Gorky.CompanyMSK[j].WagonSleep[i].ControlPlaces(_Number))
									{
										while (tmp <= _Number)
										{
											for (LastNumberPlace; LastNumberPlace < NumberOfSeatsPlaces; LastNumberPlace++)
												if (Gorky.CompanyMSK[j].WagonSleep[i].Places[LastNumberPlace].Reservation == 0)
												{
													Gorky.CompanyMSK[j].WagonSleep[i].Places[LastNumberPlace].Reservation = 1;
													Gorky.CompanyMSK[j].WagonSleep[i].Places[LastNumberPlace].Name = _Name;
													Tick.SetTicket(_Name, _Date, _Time, CostSeated, Gorky.CompanyMSK[1].Number, Gorky.CompanyMSK[j].WagonSleep[i].Number, Gorky.CompanyMSK[j].WagonSleep[i].Places[LastNumberPlace].Number, MSK, NN, _View, Ticket::NextID());
													Gorky.Tickets.push_back(Tick);
													tmp++;
													break;
												}
										}
										flag = true;
										break;
									}
								break;
							}
							if (_View == "Купе")
							{
								for (int i = 0; i < 6; i++)
									if (Gorky.CompanyMSK[j].WagonCom[i].ControlPlaces(_Number))
									{
										while (tmp <= _Number)
										{
											for (LastNumberPlace; LastNumberPlace < NumberOfSeatsPlaces; LastNumberPlace++)
												if (Gorky.CompanyMSK[j].WagonCom[i].Places[LastNumberPlace].Reservation == 0)
												{
													Gorky.CompanyMSK[j].WagonCom[i].Places[LastNumberPlace].Reservation = 1;
													Gorky.CompanyMSK[j].WagonCom[i].Places[LastNumberPlace].Name = _Name;
													Tick.SetTicket(_Name, _Date, _Time, CostCom, Gorky.CompanyMSK[1].Number, Gorky.CompanyMSK[j].WagonCom[i].Number, Gorky.CompanyMSK[j].WagonCom[i].Places[LastNumberPlace].Number, MSK, NN, _View, Ticket::NextID());
													Gorky.Tickets.push_back(Tick);
													tmp++;
													break;
												}
										}
										flag = true;
										break;
									}
								break;
							}
							else
							{
								for (int i = 0; i < 4; i++)
									if (Gorky.CompanyMSK[j].WagonRes[i].ControlPlaces(_Number))
									{
										while (tmp <= _Number)
										{
											for (LastNumberPlace; LastNumberPlace < NumberOfSeatsPlaces; LastNumberPlace++)
												if (Gorky.CompanyMSK[j].WagonRes[i].Places[LastNumberPlace].Reservation == 0)
												{
													Gorky.CompanyMSK[j].WagonRes[i].Places[LastNumberPlace].Reservation = 1;
													Gorky.CompanyMSK[j].WagonRes[i].Places[LastNumberPlace].Name = _Name;
													Tick.SetTicket(_Name, _Date, _Time, CostSeated, Gorky.CompanyMSK[1].Number, Gorky.CompanyMSK[j].WagonRes[i].Number, Gorky.CompanyMSK[j].WagonRes[i].Places[LastNumberPlace].Number, MSK, NN, _View, Ticket::NextID());
													Gorky.Tickets.push_back(Tick);
													tmp++;
													break;
												}
										}
										flag = true;
										break;
									}
								break;
							}

						}
						if (Gorky.FastMSK[j].Times == _Time)
						{
							if (_View == "Купе")
							{
								for (int i = 0; i < 8; i++)
									if (Gorky.FastMSK[j].WagonCom[i].ControlPlaces(_Number))
									{
										while (tmp <= _Number)
										{
											for (LastNumberPlace; LastNumberPlace < NumberOfSeatsPlaces; LastNumberPlace++)
												if (Gorky.FastMSK[j].WagonCom[i].Places[LastNumberPlace].Reservation == 0)
												{
													Gorky.FastMSK[j].WagonCom[i].Places[LastNumberPlace].Reservation = 1;
													Gorky.FastMSK[j].WagonCom[i].Places[LastNumberPlace].Name = _Name;
													Tick.SetTicket(_Name, _Date, _Time, CostCom, Gorky.FastMSK[1].Number, Gorky.FastMSK[j].WagonCom[i].Number, Gorky.FastMSK[j].WagonCom[i].Places[LastNumberPlace].Number, MSK, NN, _View, Ticket::NextID());
													Gorky.Tickets.push_back(Tick);
													tmp++;
													break;
												}
										}
										flag = true;
										break;
									}
								break;
							}
							else
							{
								for (int i = 0; i < 4; i++)
									if (Gorky.FastMSK[j].WagonRes[i].ControlPlaces(_Number))
									{
										while (tmp <= _Number)
										{
											for (LastNumberPlace; LastNumberPlace < NumberOfSeatsPlaces; LastNumberPlace++)
												if (Gorky.FastMSK[j].WagonRes[i].Places[LastNumberPlace].Reservation == 0)
												{
													Gorky.FastMSK[j].WagonRes[i].Places[LastNumberPlace].Reservation = 1;
													Gorky.FastMSK[j].WagonRes[i].Places[LastNumberPlace].Name = _Name;
													Tick.SetTicket(_Name, _Date, _Time, CostRes, Gorky.FastMSK[1].Number, Gorky.FastMSK[j].WagonRes[i].Number, Gorky.FastMSK[j].WagonRes[i].Places[LastNumberPlace].Number, MSK, NN, _View, Ticket::NextID());
													Gorky.Tickets.push_back(Tick);
													tmp++;
													break;
												}
										}
										flag = true;
										break;
									}
								break;
							}
						}
					}
			ReservCopy();
		}
		return flag;
	}
	bool ControlDate(Date _Date)
	{
		bool flag = false;
		for (int i = 0; i < 30; i++)
			if (Gorky.SmallowNN_1[i].Data == _Date)
			{
				flag = true;
				break;
			}
		return flag;
	}
	int SumPrice(string _View, int _Number)
	{
		int sum;
		if (_View == "Сидячий")
			sum = _Number * CostSeated;
		if (_View == "СВ")
			sum = _Number * CostSleep;
		if (_View == "Купе")
			sum = _Number * CostCom;
		if (_View == "Плацкарт")
			sum = _Number * CostRes;
		return sum;
	}
	void SaveTicket(string Title, int _Number)
	{
		ofstream file;
		file.open(Title);
		if (!file.is_open())
			cout << "Ошибка открытия";
		else
		{
			for (int i = 0; i < _Number; i++)
			{
				file << "ФИО: " << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].Name.Patronymic << " " << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].Name.Name << " " << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].Name.Surname << endl;
				file << "Номер поезда: " << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].NumberTrain << endl;
				file << "Дата отправления: " << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].Data.Day << "." << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].Data.Month << "." << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].Data.Year << endl;
				file << "Время отправления: " << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].Times.Hour << ":" << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].Times.Minutes << endl;
				file << "Станция отправления: " << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].StationOfDeparture << endl;
				file << "Станция прибытия: " << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].ArrivalStation << endl;
				file << "Номер вагона: " << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].NumberWagon << endl;
				file << "Тип вагона: " << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].View << endl;
				file << "Место: " << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].NumberPlace << endl;
				file << "ID:" << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].id << endl;
				file << "Цена: " << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].Cost << endl << endl;;
			}
		}
		file.close();
	}
	void ShowTicket(int _Number)
	{
		for (int i = 0; i < _Number; i++)
		{
			cout << "ФИО: " << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].Name.Patronymic << " " << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].Name.Name << " " << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].Name.Surname << endl;
			cout << "Номер поезда: " << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].NumberTrain << endl;
			cout << "Дата отправления: " << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].Data.Day << "." << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].Data.Month << "." << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].Data.Year << endl;
			cout << "Время отправления: " << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].Times.Hour << ":" << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].Times.Minutes << endl;
			cout << "Станция отправления: " << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].StationOfDeparture << endl;
			cout << "Станция прибытия: " << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].ArrivalStation << endl;
			cout << "Номер вагона: " << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].NumberWagon << endl;
			cout << "Тип вагона: " << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].View << endl;
			cout << "Место: " << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].NumberPlace << endl;
			cout << "ID:" << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].id << endl;
			cout << "Цена: " << Gorky.Tickets[Gorky.Tickets.size() - 1 - i].Cost << endl << endl;;
		}
	}
	void ReservCopy()
	{
		ofstream fil;
		fil.open("ReservCopy.txt");
		fil.write((char*)&Gorky, sizeof(Gorky));
		fil.close();
	}
	RailwayTicketOffice ReadCopy(RailwayTicketOffice &_Office)
	{
		ifstream file;
		file.open("ReservCopy.txt");
		if (!file.is_open())
			cout << "Ошибка открытия";
		else
			while (file.read((char*)&_Office.Gorky, sizeof(TheGorkyRailway)))
			{
			}
		file.close();
		return _Office;
	}
};
//Вспомогательные функции 
void Menu()
{
	cout << "1. Узнать расписание" << endl;
	cout << "2. Проверить наличие свободных мест" << endl;
	cout << "3. Купить билет" << endl;
	cout << "4. Вернуть билет" << endl;
	cout << "5. Узнать стоимость" << endl;
	cout << "6. Выход" << endl;
}
void Timetable()
{
	cout << "Отправление: " << NN << "                      " << MSK << endl;
	cout << "00:00 \"Фирменный\" №70" << "                       " << "10:00 \"Лвсточка\" №40" << endl;
	cout << "01:30 \"Скорый\" №90   " << "                       " << "13:00 \"Скорый\" №100" << endl;
	cout << "05:00 \"Ласточка\" №10 " << "                       " << "15:00 \"Ласточка\" №50" << endl;
	cout << "07:00 \"Ласточка\" №20 " << "                       " << "19:00 \"Ласточка\" №60" << endl;
	cout << "11:00 \"Ласточка\" №30 " << "                       " << "21:00 \"Фирменный\" №80" << endl;
}
InfoName SetName()
{
	InfoName _Name;
	string str;
	cout << "Введите фамилию: ";
	cin.ignore();
	getline(cin, str);
	_Name.Patronymic = str;
	cout << endl << "Введите имя: ";
	getline(cin, str);
	_Name.Name = str;
	cout << endl << "Введите отчество: ";
	getline(cin, str);
	_Name.Surname = str;
	cout << endl;
	return _Name;
}
Date SetData()
{
	Date _Date;
	int Year, Month, Day;
	cout << "Введите дату(в формате число месяц год):" << endl;
	cin >> Day >> Month >> Year;
	_Date.Day = Day;
	_Date.Month = Month;
	_Date.Year = Year;
	return _Date;
}
string SetDeporture()
{
	string tmp;
	int ind = 0;
	cout << "1. Нижний Новгород - Москва " << endl;
	cout << "2. Москва - Нижний Новгород " << endl;
	while (ind == 0)
	{
		cin >> ind;
		switch (ind)
		{
		case 1: tmp = NN; break;
		case 2: tmp = MSK; break;
		default: cout << "Неверно выбран маршрут, повторите" << endl; ind = 0; system("pause");
		}
	}
	return tmp;
}
string SetTypeWagon()
{
	string _Type;
	int ind = 0;
	cout << "Выберите тип вагона:" << endl;
	cout << "1. Сидячий(\"Ласточка\")" << endl;
	cout << "2. Плацкарт(\"Скорый\",\"Фирменный\")" << endl;
	cout << "3. СВ(\"Фирменный\")" << endl;
	cout << "4. Купе(\"Скорый\",\"Фирменный\")" << endl;
	while (ind == 0)
	{
		cin >> ind;
		switch (ind)
		{
		case 1:
			_Type = "Сидячий";
			break;
		case 2:
			_Type = "Плацкарт";
			break;
		case 3:
			_Type = "СВ";
			break;
		case 4:
			_Type = "Купе";
			break;
		default: cout << "Повторите " << endl; ind = 0; system("pause");
		}
	}
	return _Type;
}
Time SetTime(string _Dep)
{
	Time _Time;
	int ind = 0;
	cout << "Отправление: " << NN << "                      " << MSK << endl;
	cout << "1. 00:00 \"Фирменный\" №70" << "                       " << "10:00 \"Ласточка\" №40" << endl;
	cout << "2. 01:30 \"Скорый\" №90   " << "                       " << "13:00 \"Скорый\" №100" << endl;
	cout << "3. 05:00 \"Ласточка\" №10 " << "                       " << "15:00 \"Ласточка\" №50" << endl;
	cout << "4. 07:00 \"Ласточка\" №20 " << "                       " << "19:00 \"Ласточка\" №60" << endl;
	cout << "5. 11:00 \"Ласточка\" №30 " << "                       " << "21:00 \"Фирменный\" №80" << endl;
	while (ind == 0)
	{
		cin >> ind;
		if (_Dep == NN)
			switch (ind)
			{
			case 1: _Time.Hour = 00; _Time.Minutes = 00; break;
			case 2: _Time.Hour = 01; _Time.Minutes = 30; break;
			case 3: _Time.Hour = 05; _Time.Minutes = 00; break;
			case 4: _Time.Hour = 07; _Time.Minutes = 00; break;
			case 5: _Time.Hour = 11; _Time.Minutes = 00; break;
			default: cout << "Повторите ввод:" << endl; ind = 0; system("pause");
			}
		else
			switch (ind)
			{
			case 1: _Time.Hour = 10; _Time.Minutes = 00; break;
			case 2: _Time.Hour = 13; _Time.Minutes = 00; break;
			case 3: _Time.Hour = 15; _Time.Minutes = 00; break;
			case 4: _Time.Hour = 19; _Time.Minutes = 00; break;
			case 5: _Time.Hour = 21; _Time.Minutes = 00; break;
			default: cout << "Повторите ввод:" << endl; ind = 0; system("pause");
			}
	}
	return _Time;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	int tmp = 0;
	int number;
	string Title;
	string Deporture;
	string TypeWagon;
	InfoName Name;
	Time Times;
	Date Data;
	Data.Day = 0;
	Data.Month = 1;
	Data.Year = 2018;
	RailwayTicketOffice TicketOffice(Data);
	int indicator = 0;
	while (indicator != 5)
	{
		system("cls");
		Menu();
		cin >> indicator;
		system("cls");
		switch (indicator)
		{
		case 1:
			Timetable();
			system("pause");
			break;
		case 2:
			Deporture = SetDeporture();
			while (tmp == 0)
			{
				Data = SetData();
				if (!TicketOffice.ControlDate(Data))
					cout << "Билетов на данное число не найдено, повторите ввод: " << endl;
				else
					tmp = -1;
			}
			Times = SetTime(Deporture);
			TypeWagon = SetTypeWagon();
			cout << "Введите количество билетов:" << endl;
			cin >> number;
			if (!TicketOffice.ControlFreePlaces(Data, Deporture, Times, number, TypeWagon))
				cout << "Мест нет" << endl;
			else
				cout << "Места есть" << endl;
			system("pause");
			break;
		case 3:
			Name = SetName();
			Deporture = SetDeporture();
			while (tmp == 0)
			{
				Data = SetData();
				if (!TicketOffice.ControlDate(Data))
					cout << "Билетов на данное число не найдено, повторите ввод: " << endl;
				else
					tmp = -1;
			}
			Times = SetTime(Deporture);
			TypeWagon = SetTypeWagon();
			cout << "Введите количество билетов:" << endl;
			cin >> number;
			if (!TicketOffice.ReservePlaces(Data, Deporture, Times, Name, number, TypeWagon))
				cout << "Не удалось произвести покупку" << endl;
			else
			{
				TicketOffice.ShowTicket(number);
				cout << "Билеты куплены" << endl;
			}
			cout << "Введите название файла, в который сохранить билеты(***.txt): " << endl;
			cin.ignore();
			getline(cin, Title);
			TicketOffice.SaveTicket(Title, number);
			system("pause");
			break;
		case 4:
			int id;
			cout << "Введите id, указанный на билете:" << endl;
			cin >> id;
			if (TicketOffice.DeleteTicket(id))
				cout << "Билет удален" << endl;
			else
				cout << "Не удалось удалить билет" << endl;
			system("pause");
			break;
		case 5:
			Deporture = SetDeporture();
			while (tmp == 0)
			{
				Data = SetData();
				if (!TicketOffice.ControlDate(Data))
					cout << "Билетов на данное число не найдено, повторите ввод: " << endl;
				else
					tmp = -1;
			}
			Times = SetTime(Deporture);
			TypeWagon = SetTypeWagon();
			cout << "Введите количество билетов:" << endl;
			cin >> number;
			cout << "Стоимость: " << TicketOffice.SumPrice(TypeWagon, number);
			system("pause");
			break;
		case 6:
			indicator = 6;
			break;
		default:
			cout << "Данной команды нет. Проверьте ввод." << endl;
			system("pause");
		}
	}
}