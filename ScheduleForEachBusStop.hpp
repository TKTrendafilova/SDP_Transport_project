#ifndef __SCHEDULE_FOR_EACH_BUS_STOP
#define __SCHEDULE_FOR_EACH_BUS_STOP

#include<vector>
#include<fstream>

class Schedule {
private:
	unsigned m_numberStation;
	std::vector<unsigned> m_arrivalTime;
	//Няма да е списък, защото при списъка има линеен достъп до елементи , но пък добавянето и пхремахването е константно.
	//От друга страна при динамичния масив има константен достъп до елементите, бърз достъп до паметта и линеен преразход на паметта-знаем кога е преоразмеряването 

public:
	//Big 4
	Schedule();
	Schedule(unsigned numberStation , std::vector<unsigned> arrivalTime);
	Schedule(const Schedule& otherSchedule) ;
	Schedule& operator= (const Schedule& otherSchedule) ;
	//~Schedule();//add 09.08.2021//може би не е е нужно
	

	void addNewArrivalTime(unsigned time);
	
	void printSchedule() const;
	unsigned getArrivalTimeOfIndex(unsigned index) const;
	unsigned getNextArrivalTimeAfter(unsigned timeBefore)const;
	unsigned getNumberOfStation()const;

	//Взимане на индекса на време от разписа на станцията.
	unsigned getIndexOfTime(unsigned time)const;

	void setNumberOfStation(unsigned number);

	void serializeSchedule(std::ofstream& ofs) const;
	void deserializeSchedule(std::ifstream& ifs);
	size_t getSizeOfArrivalTime()const;
	void sortArrivalTime();

private: 
	static const unsigned defaultNumberStation = 0;
	static const unsigned invalidTime = 1440;
	void copyArrivalTime(const std::vector<unsigned>& other);
	
	//Помощна функция, която ще използвам при сортирането.
	void swap(unsigned& data1, unsigned& data2);

	/* Избирам да сортирам времето на пристигане чрез пираминадално сортиране. Алгоритъмът за пирамидално сортиране е бърз сортиращ алгоритъм, 
	* който има сложност O(nlogn) по брой сравения и присвоявания. Знаем, че това е и теоритичната долна граница за соортиращ алгоритъм.
	* Освен това използва константна памет, универсален е и е частичен. Минус на този алгоритъм е че не е стабилен, но в случай това не е много голямо
	* значение.
	*/
	void heapify(std::vector<unsigned>& arr, int size,  int index);
	void heapSort(std::vector<unsigned>& arr);
};

#endif
