#ifndef __TRANSPORT_HPP
#define __TRANSPORT_HPP

#include<iostream>
#include<vector>
#include<list>
#include"BusStation.hpp"
#include"List.hpp"
#include"Heap.hpp"

class Transport {
private:
	struct Edge {
		BusStation m_to;
		unsigned m_numberOfBus;
		//Ребро ще има само, когато ще има автобус, който изпълнява курс от една сприка до другата- to.
		Edge(){}
		Edge(BusStation to,unsigned numbBus)
			:m_to(to)
			,m_numberOfBus(numbBus)
		{}
		unsigned getNumberOfBusOfEdge()const {
			return m_numberOfBus;
		}
	};

	struct Node {
	//	List<Edge> m_E;
		std::list<Edge> m_E;
		BusStation m_station;

		Node() {}
		Node(BusStation station) 
			:m_station(station)
		{}


		//void serializeNode(std::ofstream& ofs);
		//void deserializeNode(std::ifstream& ifs);
	};

	std::vector<Node> m_V;//Множество от върхове- върховете ще са автобусните спирки

	unsigned m_countV;
	unsigned m_countE;

private:
	unsigned numberOfBus;//помощна променлива
	//Помощна променлива за printScheduleForStation()
	 unsigned  maxCountV;
	void swap(unsigned& a, unsigned& b);
public:
	Transport():m_countV(0),m_countE(0){}

	Transport(unsigned v, unsigned e)
		: m_countV(v)
		, m_countE(e)
	{
		/*for (int i = 0; i < m_countE; ++i) {
			m_V.push_back(Transport::Node().m_station.setNumberOfStattion(i));
		}*/
	}

	static const int DEFAULT_VALUE_FOR_POS = -1;
	static const unsigned MAX_MIN = 1440;

	void printBusesOfStation(unsigned num)const;

	unsigned getCountV()const;
	unsigned getCountE()const;

	BusStation getStation(unsigned numberOfStation);

	void setCountV(unsigned newCountV);
	void setCountE(unsigned newCountE);

	void addStation(BusStation& station);
	int addStationInRunProgram(BusStation& station);//Добавям я, за да мога да добавям спирка в процес на работа на програмата, докато пръвто addStation иска след това зъдължително addedge
	void removeStation(unsigned numberOfStation);
	bool hasStationWithNumber(unsigned numberStation)const;

	unsigned countEdges(unsigned numbStation) const;
	
	void addEdge(BusStation& from, BusStation& to, Bus& busFromTo);
	bool hasEdgeWithBus(BusStation& from, BusStation& to, unsigned busNumber);
	bool hasEdge(BusStation& from, BusStation& to);

	BusStation getStation(unsigned numberStation) const;
	Bus getBusFromTransport(unsigned numberOfBus) const;

	//Връща минималното време за достигане от станция from до станция to, след пристигане на станция from в час timeToReachBusStation1
	int minTimeToReachBusStation(BusStation& from, BusStation& to, unsigned timeToReachBusStation1);

	//Връща номера на автобуса, с който за най-бързо време ще достигнем от станция from до станция to
	unsigned numberBusWithMinTimeToReachBusStation(BusStation& from, BusStation& to, unsigned timeToReachBusStation1);

	//Извеждане на най-къс път по време от зададена начална, крайна спирка и време на тръгване
	void printTheShortestPath(BusStation& startBusStation, BusStation& finalBusStation, unsigned timeToStart);

	//Показване на разписа на автобусите минаващи през дадена спирка
	void printScheduleForStation(unsigned numberOfStation)const;// work

	//Извеждане на номерата на спирките
	void printStation()const;

	//Проверка дали в транспортната мрежа има автобус с даден номер
	bool hasBusInNetwork(unsigned numberBus) const;

	//Добавяне на нов разпис за нова станзия на автобус от транспортната мрежа
	void addScheduleForBusInNetwork(unsigned numberBus, Schedule& sh);//Да се тества

	//Работа с файлове
	void serializeTransport(std::ofstream& ofs) /*const*/;
	void deserializeTransport(std::ifstream& ifs);//to be defined

	//Проманя на маршрута на автобус от трянспортната мрежа
	//void changeRouteOfBus(unsigned busNumber);не работи и няма нужда от него

	//Връща най-големият номер на станция
	unsigned biggestNumOfStation()const;
	
	//Изчистване на данните
	void clearMemory();

	//Добавяне на нов автобус
	void addBus(Bus& newBus);

	//Добавяне на курс
	void addNewCourse(unsigned numBus);

	//to debug
	void printShForBus(unsigned busNum)const;

};

#endif
