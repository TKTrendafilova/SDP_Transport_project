#ifndef __BUS_STATION_HPP
#define __BUS_STATION_HPP

#include"List.hpp"
#include"Bus.hpp"
class BusStation {
private:
	char* m_name;
	unsigned m_numberOfStation;
	std::vector<Bus> m_listOfBuses;//Ще бъде вектор, защото достъпът до елементи е константен, докато при спъсък достъпът до елемент е линеен

public:
	BusStation();
	BusStation(char* nameOfStation, unsigned numberOfStation, std::vector<Bus> listOfBuses);
	BusStation(const BusStation& otherStation);
	BusStation& operator=(const BusStation& otherStattion);
	~BusStation();

	
	char* getName() const;
	unsigned getNumberOfStation() const;
	std::vector<Bus> getListOfBuses()const;

	Bus getBusWithNumber(unsigned num)const;

	void setNameStation(char* newName);
	void setNumberOfStattion(unsigned newNumber);
	void setListOfBuses(std::vector<Bus>& newListOfBuses);//тествано е 

	void addNewBus(const Bus& newBus);
	void removeBus(unsigned numberBusToDelete);
	bool passedABusWithANumber(unsigned numberBus);//Дали автобус с номер numberBus минава през спирката
	void showScheduleOfBuses();

	void serializeBusStation(std::ofstream& ofs) const;
	void deserializeBusStation(std::ifstream& ifs);

private:
	static const unsigned LEN_NAME = 128;
	static const unsigned START_NUM = 0;
	static const int POS = -1;

	void copyData(char*newname, const std::vector<Bus>& buses);
	void deleteData();

	unsigned getSizeOfListBuses();

};


#endif
