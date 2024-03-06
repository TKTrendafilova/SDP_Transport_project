#include<iostream>
#include"Bus.hpp"

Bus::Bus()
	:m_number(startCountOfStation)//връща 0, като по подразбиране няма автобус с номер 0
	,m_route(nullptr)
	,m_countOfStation(startCountOfStation)
	,m_capacity(startCapacity)
{
	m_route = new (std::nothrow) unsigned[m_capacity];
	if (m_route == nullptr) {
		std::cout << "Not enought memory for route of bus" << std::endl;
		return;
	}
}

Bus::Bus(unsigned numberOfBus, unsigned * routeOfBus, unsigned countOfStation, unsigned capacity,std::vector<Schedule> schedule)
	:m_number(numberOfBus)
	, m_route(nullptr)
	, m_countOfStation(countOfStation)
	, m_capacity(capacity)
	
{
	m_route = new (std::nothrow) unsigned [m_capacity];
	if (m_route == nullptr) {
		std::cout << "Not enought memory for route of bus" << std::endl;
		return;
	}

	for (unsigned i = 0; i < m_countOfStation; ++i) {
		m_route[i] = routeOfBus[i];
	}

	m_sheduleForEachBusStation = schedule;
}

Bus::Bus(const Bus& otherBus)
	:m_number(startCountOfStation)//за да няма warning
	,m_countOfStation(startCountOfStation)
	,m_capacity(startCapacity)
{
	if (this != &otherBus) {
		copy(otherBus);
	}
}

Bus& Bus::operator=(const Bus& otherBus)
{
	if (this != &otherBus) {
		clearMemory();
		copy(otherBus);
	}
	return *this;
}

Bus::~Bus()
{
	clearMemory();
}

unsigned Bus::getNumberOfBus() const
{
	return m_number;
}

unsigned Bus::getCapacity() const
{
	return m_capacity;
}

unsigned Bus::getCountOfStations() const
{
	//return m_countOfStation;
	return m_sheduleForEachBusStation.size();
}

unsigned* Bus::getRoute() const
{
	return m_route;
}

void Bus::printRoute() const
{
	std::cout << "Bus number " << m_number << " route: " << std::endl;
	for (unsigned i = 0; i < m_countOfStation; ++i) {
		std::cout << m_route[i] << std::endl;
	}
}

Schedule Bus::getScheduleForStation(unsigned numberOfStation) const
{
	//Тук не правя валидация, защото тази функция ще се използва само в Transport.
	//Там преди да е извикана ще бъде направена валидация за спирката

	for (unsigned i = 0; i < m_countOfStation; ++i) {
		if (m_sheduleForEachBusStation.at(i).getNumberOfStation() == numberOfStation) {
			return m_sheduleForEachBusStation.at(i);
		}
	}
}

std::vector<Schedule> Bus::getSchedule() const
{
	return m_sheduleForEachBusStation;
}

void Bus::addNewStation(unsigned numOfStaion)
{
	if (m_countOfStation >= m_capacity) {
		resize();
	}
	m_route[m_countOfStation] = numOfStaion;
	++m_countOfStation;
}

void Bus::setNumber(unsigned number)
{
	m_number = number;
}

void Bus::setRoute(unsigned* route, unsigned size)
{
	clearMemory();
	//Подсигуряване на нужния капацитет
	while (size > m_capacity) {
		m_capacity = m_capacity * 2;
	}
	m_route = new (std::nothrow) unsigned[m_capacity];
	if (m_route == nullptr) {
		std::cout << "Not enought memory for route of bus" << std::endl;
		return;
	}
	
	for (unsigned i = 0; i < size; ++i) {
		m_route[i] = route[i];
	}

}

void Bus::setCountOfStation(unsigned newCount)
{
	m_countOfStation = newCount;
}

void Bus::setScheduleForEachBusStation(std::vector<Schedule>& newSh)
{
	//Използва се, като не се променя маршрута на автобуса
	//Маршрута си отства същия и за снатнциите от него се променят графиците
	m_sheduleForEachBusStation.clear();
	
	size_t size = newSh.size();
	for (size_t i = 0; i < size; ++i) {
		m_sheduleForEachBusStation.push_back(newSh.at(i));
	}
	
}

void Bus::addScheduleForStation(Schedule& sh)
{
	m_sheduleForEachBusStation.push_back(sh);
	addNewStation(sh.getNumberOfStation());//добавяне на номера на станцията на към маршрута на автобуса
	
}

void Bus::printScheduleForStation(unsigned numberStation)
{
	
	size_t size = m_sheduleForEachBusStation.size();

	for (size_t i = 0; i < size; ++i) {
		if (m_sheduleForEachBusStation.at(i).getNumberOfStation() == numberStation) {
			std::cout << "Bus " << m_number << "  schedule for station ";

			m_sheduleForEachBusStation.at(i).printSchedule();
			return;
		}
		if (m_sheduleForEachBusStation.at(i).getNumberOfStation() != numberStation && i == size - 1) {
			std::cout << "Stop " << numberStation << " is not part of bus " << m_number << " line." << std::endl;
		}
	}
}

void Bus::printScheduleForAllStations()
{
	size_t size = m_sheduleForEachBusStation.size();
	
	for (size_t i = 0; i < size; ++i) {
		std::cout << "Bus " << m_number << " schedule for station ";
		if(hasVisitStation(m_sheduleForEachBusStation.at(i).getNumberOfStation())==true)
			m_sheduleForEachBusStation.at(i).printSchedule();
	}

	//Закоментирано след коментара в Transport::printScheduleForStation
	/*for (unsigned i = 0; i < size; ++i) {
		printScheduleForStation(m_route[i]);
	}*/
}

bool Bus::hasVisitStation(unsigned numberStation)
{
	size_t size = m_sheduleForEachBusStation.size();
	for (size_t i = 0; i < size; ++i) {
		if (m_sheduleForEachBusStation.at(i).getNumberOfStation() == numberStation) {
			return true;
		}
	}
	return false;
}

void Bus::removeStation(unsigned numberStation)
{
	int pos = POS;
	int posSchedule = POS;
	for (unsigned i = 0; i < m_countOfStation; ++i) {
		if (m_route[i] == numberStation) {
			pos = i;
			break;
		}
	}
	size_t size = m_sheduleForEachBusStation.size();
	for (size_t i = 0; i < size; ++i) {
		if (m_sheduleForEachBusStation.at(i).getNumberOfStation() == numberStation) {
			posSchedule = i;
			break;
		}
	}
	
	if (pos == POS) {
		std::cout << "Bus station " << numberStation << " is not part of the route of bus " << m_number << "." << std::endl;
	}
	if (pos != POS && posSchedule!=POS) {
		while (pos != m_countOfStation - 1) {
			m_route[pos] = m_route[pos + 1];
			++pos;
		}
		--m_countOfStation;
		
		while (posSchedule != size-1) {
			m_sheduleForEachBusStation[posSchedule] = m_sheduleForEachBusStation[posSchedule + 1];
			++posSchedule;
		}
	
		m_sheduleForEachBusStation.pop_back();
	
	}

}

void Bus::serializeBus(std::ofstream& ofs) const
{
	if (!ofs.is_open()) {
		std::cout << "File is not open!" << std::endl;
		return;
	}
	
	ofs.write((const char*)&m_number, sizeof(m_number));
	ofs.write((const char*)&m_countOfStation, sizeof(m_countOfStation));
	ofs.write((const char*)&m_capacity, sizeof(m_capacity));

	////Не съм много сигурна дали така трябва
	//for (unsigned i = 0; i < m_countOfStation; ++i) {
	//	ofs.write((const char*)&m_route[i], sizeof(m_route[i]));
	//}

	//Друг начин на закоментираната част
	unsigned* tempR = new(std::nothrow) unsigned[m_countOfStation];
	if (tempR == nullptr) {
		std::cout << "Not enought memory. Error!" << std::endl;
		return;
	}

	for (unsigned i = 0; i < m_countOfStation; ++i) {
		tempR[i] = m_route[i];
	}
	ofs.write((const char*)&tempR, sizeof(tempR));

	Schedule* temp = new(std::nothrow) Schedule[m_countOfStation];
	if (temp == nullptr) {
		std::cout << "Not enought memory" << std::endl;
		return;
	}
	for (unsigned i = 0; i < m_countOfStation; ++i) {
		temp[i] = m_sheduleForEachBusStation[i];
	}

	ofs.write((const char*)&temp, sizeof(temp));
	/*ofs.write((const char*)&temp, sizeof(temp));
	if (ofs.good()) {
		std::cout << "Successfully serialize!" << std::endl;
	}
	else {
		std::cout << "Serialize failed!" << std::endl;
	}*/
}

void Bus::deserializeBus(std::ifstream& ifs)
{
	if (!ifs.is_open())
	{
		std::cout << "File is not open!" << std::endl;

		return;
	}

	ifs.read((char*)&m_number, sizeof(m_number));
	ifs.read((char*)&m_countOfStation, sizeof(m_countOfStation));
	ifs.read((char*)&m_capacity, sizeof(m_capacity));
	
	//Не съм много сигурна дали така трябва. Но май е вярно
	m_route = new(std::nothrow) unsigned[m_capacity];
	if (m_route == nullptr) {
		std::cout << "Error!" << std::endl;
	}
	/*for (unsigned i = 0; i < m_countOfStation; ++i) {
		ifs.read((char*)& m_route[i], sizeof(m_route[i]));
	}*/

	//Друг начина на закоментираната част
	unsigned* tempR = new(std::nothrow) unsigned[m_countOfStation];
	if (tempR == nullptr) {
		std::cout << "Not enought memory." << std::endl;
		return;
	}

	ifs.read((char*)&tempR, sizeof(tempR));

	for (unsigned i = 0; i < m_countOfStation; ++i) {
		m_route[i] = tempR[i];
	}
	Schedule* temp = new(std::nothrow) Schedule[m_countOfStation];
	ifs.read((char*)&temp, sizeof(temp));
	for (unsigned i = 0; i < m_countOfStation; ++i) {
		m_sheduleForEachBusStation.push_back(temp[i]);
	}
	/*
	if (ifs.good()) {
		std::cout << "yes,  deserilize" << std::endl;
	}
	else {
		std::cout << "no, deserialize" << std::endl;
	}*/
}

void Bus::copy(const Bus& other)
{
	m_number = other.m_number;
	m_countOfStation = other.m_countOfStation;
	m_capacity = other.m_capacity;

	m_route = new(std::nothrow) unsigned[m_capacity];
	if (m_route == nullptr) {
		std::cout << "Not enought memory for route of bus" << std::endl;
		return;
	}
	
	for (unsigned i = 0; i < m_countOfStation; ++i) {
		m_route[i] = other.m_route[i];
	}

	m_sheduleForEachBusStation.clear();
	m_sheduleForEachBusStation = other.m_sheduleForEachBusStation;
	
}

void Bus::clearMemory()
{
	delete[] m_route;
	m_route = nullptr;

	m_sheduleForEachBusStation.clear();
}

void Bus::resize()
{
	unsigned newCapacity = m_capacity * 2;
	unsigned* newRoute = new(std::nothrow) unsigned[newCapacity];
	
	if (newRoute == nullptr) {
		std::cout << "error! Not enought memory for resize!" << std::endl;
		return;
	}

	for (unsigned i = 0; i < m_capacity; ++i) {
		newRoute[i] = m_route[i];
	}

	m_capacity = newCapacity;
	delete[] m_route;
	m_route = newRoute;
}


