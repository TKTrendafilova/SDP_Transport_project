#ifndef __BUS_HPP
#define __BUS_HPP

#include<vector>
#include<fstream>
#include"ScheduleForEachBusStop.hpp"

class Bus {
private:
	unsigned * m_route;
	unsigned m_number;
	unsigned m_countOfStation;
	unsigned m_capacity;
	
	std::vector<Schedule> m_sheduleForEachBusStation;
	
public:
	static const unsigned startCapacity = 8;
	static const unsigned startCountOfStation = 0;
	static const int POS = -1;
	//Big4
	Bus();
	Bus(unsigned numberOfBus, unsigned * routeOfBus, unsigned countOfStation,unsigned capacity,std::vector<Schedule> schedule);
	Bus(const Bus& otherBus);
	Bus& operator=(const Bus& otherBus);
	~Bus();

	//Help function
	unsigned getNumberOfBus()const;
	unsigned getCapacity()const;
	unsigned getCountOfStations()const;
	unsigned* getRoute()const;
	void printRoute()const;//Само за тестване, не се използва в Transport

	//Взима разписа на автобесна сприка с даден номер
	Schedule getScheduleForStation(unsigned numberOfStation)const;

	//Взима списъка с разписи за всички станции
	std::vector<Schedule> getSchedule()const;

	//Добавяне на нова спирка към маршрута
	void addNewStation(unsigned numOfStaion);

	void setNumber(unsigned number);
	void setRoute(unsigned* route, unsigned size);
	void setCountOfStation(unsigned newCount);
	void setScheduleForEachBusStation(std::vector<Schedule>& newSh);//ok

	//Добавяне на нов график
	void addScheduleForStation(Schedule& sh);

	void printScheduleForStation(unsigned numberStation);
	void printScheduleForAllStations();

	//За порверка дали автобус посещава дадена спирка
	bool hasVisitStation(unsigned numberStation);

	/* Премахване на автобусна сприка от маршрута и от списъка с графици за всяка станция
	* Ще ми трябва при премахването на спирка от цялата транспортна мрежа
	*/
	void removeStation(unsigned numberStation);//тествано 

	//Работа с файлове
	void serializeBus(std::ofstream& ofs) const;
	void deserializeBus(std::ifstream& ifs);
	
private:
	void copy(const Bus& other);
	void clearMemory();
	void resize();
};

#endif
