#ifndef __MANAGE_TRANSPORT_HPP
#define __MANAGE_TRANSPORT_HPP

#include"Transport.hpp"

class Manager {
private:
	Transport m_transport;

public:
	static unsigned const MAX_LEN_COMMAND = 32;//Константа за максимална дължина на команда.
	static unsigned const MAX_LEN_NAME_STATION = 128;
	static unsigned const MAX_MIN = 1440;
	

	Manager();

	//Променлива, която пази името на файла, с който е работено, за да се изпълни след това save()
	char* m_nameFile = nullptr;

	//Дали има успешно отворен файл
	bool isSuccessfullyOpenFile = false;


	//Указатели към файловете
	std::ifstream* ptrIfs = nullptr;
	std::ofstream* ptrOfs = nullptr;

	//Съхранение на данните за гедската мрежа във файл.
	//Помощни средства за работа с файл
	void open(char* fileName);
	void closeFile();//може би не е нужно
	void save();
	void saveAs(char* newFileName);
	
	//Помощна спирка, койта извежда командите
	void help()const;

	//Добавяне на нова спирка
	void addStation(BusStation& station);

	//Премахване на спирка
	void removeStation(unsigned numberOfStation);

	//Има ли станция с даден номер
	bool hasStationWithNumber(unsigned numberOfStation);

	//Има ли автобус от една спирка да друга- директно без прикачване
	bool hasEdge(unsigned numberOfFirstStation, unsigned numberOfSecondStation);//може би не ти трябва не го прави

	//Минималния по време път от една спирка до друга
	void printShortestPath(unsigned numberFromStation, unsigned numberToStation, unsigned startTime);

	//Показва списъка с автобуси, минаващи през дадена спирка
	void printListOfBuses(unsigned numberOfStation)const;

	//Показва разписа на автоббусите минаващи през дадена спирка
	void printScheduleForStation(unsigned numberOfStation) const;

	//Промяна маршрут на автобус
	//void changeRouteOfBus(unsigned busNumber);//Не е нужно

	//Добавяне на нов автобус
	void addNewBus(Bus& newBus);

	//Добавяне на нов курс
	void addNewCourse(unsigned numBus);

	//Проверка дали има автобус в мрежата
	const bool hasBus(unsigned numBus) const;
	
	//Извежда номерата на сприките от транспортната мрежа
	//void printStation()const;
	
	void runProgram();

	//To debug
	//int printShForBus(unsigned numBus) const;
};

#endif
