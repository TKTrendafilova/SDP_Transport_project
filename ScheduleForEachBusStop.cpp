#include<iostream>
#include"ScheduleForEachBusStop.hpp"

Schedule::Schedule()
	:m_numberStation(defaultNumberStation)
{
}

Schedule::Schedule(unsigned numberStation, std::vector<unsigned> arrivalTime)
	:m_numberStation(numberStation)
{
	copyArrivalTime(arrivalTime);
}

Schedule::Schedule(const Schedule& otherSchedule)
	:m_numberStation(otherSchedule.m_numberStation)
{
	copyArrivalTime(otherSchedule.m_arrivalTime);
}

Schedule& Schedule::operator=(const Schedule& otherSchedule)
{
	if (this != &otherSchedule) {
		m_arrivalTime.clear();
		m_numberStation = otherSchedule.m_numberStation;
		copyArrivalTime(otherSchedule.m_arrivalTime);
	}
	return *this;
}

void Schedule::addNewArrivalTime(unsigned time)
{
	m_arrivalTime.push_back(time);
}

void Schedule::printSchedule() const
{
	std::cout << m_numberStation<<": " ;
	size_t size = m_arrivalTime.size();

	for (size_t i = 0; i < size; ++i) {
		if (i == size - 1) {
			std::cout << m_arrivalTime[i]<<std::endl;
		}
		else {
			std::cout << m_arrivalTime[i] << ", ";
		}
	}
	std::cout << std::endl;
}

unsigned Schedule::getNumberOfStation() const
{
	return m_numberStation;
}

unsigned Schedule::getIndexOfTime(unsigned time) const
{
	//Няма вализадиця, защото ще се изпълзва само в Transport и преди това със сигурност подаденото време ще е от разписа на спърката.
	size_t size = m_arrivalTime.size();
	for (size_t i = 0; i < size; ++i) {
		if (m_arrivalTime.at(i) == time) {
			return i;
		}
	}
}

void Schedule::setNumberOfStation(unsigned number)
{
	m_numberStation = number;
}

void Schedule::serializeSchedule(std::ofstream& ofs) const
{
	if (!ofs.is_open()) {
		std::cout << "File is not open! Error!" << std::endl;
		return;
	}

	ofs.write((const char*)&m_numberStation, sizeof(m_numberStation));

	//Добавям го, за да ми е по-лесно прочитането
	unsigned size = m_arrivalTime.size();

	ofs.write((const char*)&size, sizeof(size));

	unsigned* temp = new(std::nothrow) unsigned[size];
	if (temp == nullptr) {
		std::cout << "Not enought memory. Error!" << std::endl;
		return;
	}

	for (unsigned i = 0; i < size; ++i) {
		temp[i] = m_arrivalTime[i];
	}

	ofs.write((const char*)&temp, sizeof(temp));
	
	//// DEBUG
	//if (ofs.good()) {
	//	std::cout << "Successfully serialize!" << std::endl;
	//}
	//else {
	//	std::cout << "Serialize failed!" << std::endl;
	//}
}

void Schedule::deserializeSchedule(std::ifstream& ifs)
{
	if (!ifs.is_open()) {
		std::cout << "File is not open. Error!" << std::endl;
		return;
	}

	ifs.read((char*)&m_numberStation, sizeof(m_numberStation));

	unsigned size;
	ifs.read((char*)&size, sizeof(size));

	unsigned* temp = new(std::nothrow) unsigned[size];
	if (temp != nullptr) {
		ifs.read((char*)&temp, sizeof(temp));
		for (unsigned i = 0; i < size; ++i) {
			m_arrivalTime.push_back(temp[i]);
		}
	}
	else {
		std::cout << "Not enought memory for read arrival time. Error!" << std::endl;
		return;
	}

	/*if (ifs.good()) {
		std::cout<<"Successfully deserialize!" << std::endl;
	}
	else {
		std::cout << "Deserialize failed!" << std::endl;
	}*/
}

size_t Schedule::getSizeOfArrivalTime() const
{
	return m_arrivalTime.size();
}

void Schedule::sortArrivalTime()
{
	heapSort(m_arrivalTime);
}

void Schedule::copyArrivalTime(const std::vector<unsigned>& other)
{
	size_t size = other.size();
	for (size_t i = 0; i < size; ++i) {
		m_arrivalTime.push_back(other.at(i));
	}
}

void Schedule::swap(unsigned& data1, unsigned& data2)
{
	unsigned temp = data1;
	data1 = data2;
	data2 = temp;
}

void Schedule::heapify(std::vector<unsigned>& arr, int  size, int index)
{
    int largest = index;
	int right = 2 * index + 2;
	int left = 2 * index + 1;

//	Ако лявото дете е по-голямо от корена
	if (left<size && arr[left]> arr[largest]) {
		largest = left;
	}
	
//	Ако дясното дете е по-голямо от корена
	if (right<size && arr[right]>arr[largest]) {
		largest = right;
	}

	if (largest != index) {
		swap(arr[index], arr[largest]);
		heapify(arr, size, largest);
	}
}

void Schedule::heapSort(std::vector<unsigned>& arr)
{
	size_t size = arr.size();

	for (int i = size / 2 - 1; i >=0; --i) {
		//std::cout << "for 1" << std::endl;
		heapify(arr, size, i);
	}

	for (size_t i = size - 1; i > 0; --i) {
		//std::cout << "for 2" << std::endl;
		swap(arr[0], arr[i]);
		--size;
		heapify(arr, i, 0);
	}
}



unsigned Schedule::getArrivalTimeOfIndex(unsigned index) const
{
	if (index > m_arrivalTime.size()) {
		std::cout << "Not valid operation." << std::endl;
		unsigned invalid = invalidTime;
		return invalid;
	}
	return m_arrivalTime.at(index);
}

unsigned Schedule::getNextArrivalTimeAfter(unsigned timeBefore) const
{
	//това ще се използва в Transport
	size_t size = m_arrivalTime.size();
	if (timeBefore > getArrivalTimeOfIndex(size - 1)) {
		std::cout << "Out of range. Error!" << std::endl;
		unsigned invalid = invalidTime;
		return invalid;//направи число, което е по-голямо от броя на минутите в денонощието и така ще знаеш, че това време не е от разписа
	}
	for (size_t i = 0; i < size; ++i) {
		if (timeBefore <= m_arrivalTime.at(i)) {
			return m_arrivalTime.at(i);
		}
	}
}
