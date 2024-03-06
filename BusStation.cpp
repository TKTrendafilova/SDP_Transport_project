#pragma warning(disable:4996)//Remove strcpy problem
#include<cstring>
#include<iostream>
#include"BusStation.hpp"

BusStation::BusStation()
	:m_name(nullptr)
	,m_numberOfStation(START_NUM)
{
}

BusStation::BusStation(char* nameOfStation, unsigned numberOfStation, std::vector<Bus> listOfBuses)
	:m_name(nullptr)
	,m_numberOfStation(numberOfStation)
{
	copyData(nameOfStation, listOfBuses);
}

BusStation::BusStation(const BusStation& otherStation)
	:m_name(nullptr)
	,m_numberOfStation(otherStation.m_numberOfStation)
{
	copyData(otherStation.m_name, otherStation.m_listOfBuses);
}

BusStation& BusStation::operator=(const BusStation& otherStattion)
{
	if (this != &otherStattion) {
		deleteData();
		m_numberOfStation = otherStattion.m_numberOfStation;
		copyData(otherStattion.m_name, otherStattion.m_listOfBuses);
	}
	return *this;
}

BusStation::~BusStation()
{
	deleteData();
}

char* BusStation::getName() const
{
	return m_name;
}

unsigned BusStation::getNumberOfStation() const
{
	return m_numberOfStation;
}

std::vector<Bus> BusStation::getListOfBuses() const
{
	return m_listOfBuses;
}

Bus BusStation::getBusWithNumber(unsigned num) const
{
	//Няма валидация, защото ще се използва само в Transport::addStation след веченаправена валидация
	size_t size = m_listOfBuses.size();
	for (size_t i = 0; i < size; ++i) {
		if (m_listOfBuses.at(i).getNumberOfBus() == num) {
			return m_listOfBuses.at(i);
		}
	}
}

void BusStation::setNameStation(char* newName)
{
	//std::cout << "SetNameStation" << std::endl;
	//delete[] m_name;

	unsigned lenOfName = strlen(newName);
	m_name = new(std::nothrow)char[lenOfName + 1];
	if (m_name == nullptr) {
		std::cout << "Not enought memory for copy name of station!Error!" << std::endl;
		return;
	}
	strcpy(m_name, newName);
}

void BusStation::setNumberOfStattion(unsigned newNumber) 
{
	m_numberOfStation=newNumber;
}

void BusStation::setListOfBuses(std::vector<Bus>& newListOfBuses)
{
	m_listOfBuses.clear();
	size_t size = newListOfBuses.size();

	for (size_t i = 0; i < size; ++i) {
		m_listOfBuses.push_back(newListOfBuses.at(i));
	}
}

void BusStation::addNewBus(const Bus& newBus)
{
	//Валидация, че автобусът е нов за спирката
	if (passedABusWithANumber(newBus.getNumberOfBus()) == false) {
		//std::cout << "BusStation::addNewBus\n";
		m_listOfBuses.push_back(newBus);
	}
}

void BusStation::removeBus(unsigned numberBusToDelete)
{
	unsigned size = getSizeOfListBuses();
	int pos = POS;
	for (int i = 0; i < size; ++i) {
		if (m_listOfBuses.at(i).getNumberOfBus() == numberBusToDelete) {
			pos = i;
			break;
		}
	}
	//Тази проверка работи
	if (pos == POS) {
		std::cout << "Bus " << numberBusToDelete << " does not pass throught a stop " << m_numberOfStation << "." << std::endl;
	}
	if (pos == size - 1) {
		m_listOfBuses.pop_back();
	}
	if (pos != POS && pos!=size-1) {
		while (pos != size -1) {
			m_listOfBuses.at(pos) = m_listOfBuses.at(pos + 1);
			++pos;
		}
		m_listOfBuses.pop_back();
	}
	
}

bool BusStation::passedABusWithANumber(unsigned numberBus)
{
	int size = m_listOfBuses.size();
	for (int i = 0; i < size; ++i) {
		if (m_listOfBuses.at(i).getNumberOfBus() == numberBus) {
			return true;
		}
	}
	return false;
}

void BusStation::showScheduleOfBuses()
{
	unsigned size = getSizeOfListBuses();
	for (int i = 0; i < size; ++i) {
		m_listOfBuses.at(i).printScheduleForAllStations();
	}
}

void BusStation::serializeBusStation(std::ofstream& ofs) const
{
	if (!ofs.is_open()) {
		std::cout << "File is not open!" << std::endl;
		return;
	}
	
	unsigned lenName = strlen(m_name);
	ofs.write((const char*)&lenName, sizeof(lenName));

	ofs.write(m_name, lenName);

	ofs.write((const char*)&m_numberOfStation, sizeof(m_numberOfStation));

	unsigned size = m_listOfBuses.size();

	//Добавям го, за да ми е по-лесно четенето от файл
	ofs.write((const char*)&size, sizeof(size));

	Bus* temp = new(std::nothrow) Bus[size];
	if (temp == nullptr) {
		std::cout << "Not enought memory. Error!" << std::endl;//До тук ще бъде записана информацията във файла
		return;
	}
		
	for (int i = 0; i < size; ++i) {
		temp[i] = m_listOfBuses[i];
	}
	ofs.write((const char*)&temp, sizeof(temp));
	
	//DEBUG
	/*if (ofs.good()) {
		std::cout << "Successfully serialize!" << std::endl;
	}
	else {
		std::cout << "Serialize failed!" << std::endl;
	}*/
}

void BusStation::deserializeBusStation(std::ifstream& ifs)
{
	if (!ifs.is_open()) {
		std::cout << "File is not open. Error!" << std::endl;
		return;
	}

	unsigned lenName;
	ifs.read((char*)&lenName, sizeof(lenName));

	m_name = new(std::nothrow) char[lenName + 1];
	if (m_name) {
		ifs.read(m_name, lenName);
		m_name[lenName] = '\0';
	}
	else {
		std::cout << "Not enought memory for name in deserialize method." << std::endl;
		return;
	}

	ifs.read((char*)&m_numberOfStation, sizeof(m_numberOfStation));

	unsigned size;
	ifs.read((char*)&size, sizeof(size));

	Bus* temp = new(std::nothrow) Bus[size];
	if (temp != nullptr) {
		ifs.read((char*)&temp, sizeof(temp));
		for (int i = 0; i < size; ++i) {
			m_listOfBuses.push_back(temp[i]);
		}
	}
	else {
		std::cout << "Not enought memory for read list of buses. Error!" << std::endl;
		return;
	}

	/*if (ifs.good()) {
		std::cout << "Successfully deserialize!" << std::endl;
	}
	else {
		std::cout << "Deserialize failed!" << std::endl;
	}*/

}

void BusStation::copyData(char* newname, const std::vector<Bus>& buses)
{
	//delete[] m_name;
	////m_name = nullptr;

	//strcpy(m_name, newname);
	setNameStation(newname);

	unsigned size = buses.size();
	for (int i = 0; i < size; ++i) {
		m_listOfBuses.push_back(buses.at(i));
	}
}

void BusStation::deleteData()
{
	delete[] m_name;
	m_name = nullptr;

	m_listOfBuses.clear();
}

unsigned BusStation::getSizeOfListBuses()
{
	return m_listOfBuses.size();
}
