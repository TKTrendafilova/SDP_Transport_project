#include"Transport.hpp"

unsigned Transport::getCountV()const {
	return m_countV;
}

void Transport::swap(unsigned& a, unsigned& b)
{
	unsigned temp = a;
	a = b;
	b = temp;
}

unsigned Transport::getCountE()const {
	return m_countE;
}

void Transport::setCountV(unsigned newCountV)
{
	m_countV = newCountV;
}

void Transport::setCountE(unsigned newCountE)
{
	m_countE = newCountE;
}

void Transport::addStation(BusStation& station)
{
	for (unsigned i = 0; i < m_countV; ++i) {
		if (m_V.at(i).m_station.getNumberOfStation() == station.getNumberOfStation()) {
			std::cout << "Station " << station.getNumberOfStation() << " exsits." << std::endl;
			return;
		}
	}

	m_V.push_back(station);

	++m_countV;
	++maxCountV;
}

unsigned Transport::countEdges(unsigned numbStation) const {
	for (unsigned i = 0; i < m_countV; ++i) {
		if (m_V[i].m_station.getNumberOfStation() == numbStation) {
			return m_V[i].m_E.size();
		}
	}
}

void Transport::addEdge(BusStation& from, BusStation& to, Bus& bus)
{
	//Трябва да добавим автобус между двете спирки
	//Валидация
	if (!bus.hasVisitStation(from.getNumberOfStation()) || !bus.hasVisitStation(to.getNumberOfStation()) ){
		std::cout << "Error! Bus " << bus.getNumberOfBus() << " not visit bus station " << from.getName() << " or not visit bus station "
			<< to.getName() << ". " << std::endl;
		return;
		/* За да бъде добавено ребро между две станции, посредствум автобус, то автобуса трябва да съдържа в маршрута си тези две станции.
		*  Добавянето на двете спирки в данните на автобуса трябва да е е станало преди това.
		*  Между две спирки може да има повече от едно ребро, поради възможността повече от един аввтобус да минава през тях,тле ще
		*  имаме мултиграф. 
 		*/
	}
	

	//from.addNewBus(bus);
	//to.addNewBus(bus);
	
	for (unsigned i = 0; i < m_countV; ++i) {
		int posTo=-1;
		if (m_V[i].m_station.getNumberOfStation() == to.getNumberOfStation()) {
			posTo = i;
		}
		if (m_V[i].m_station.getNumberOfStation() == from.getNumberOfStation()) {
			if (m_V[i].m_E.empty()) {
				m_V[i].m_station = from;
				m_V[i].m_E.push_back(Edge(to,bus.getNumberOfBus()));
				
				//Добавка, за да работи addBus коректно
				if (m_V[i].m_station.passedABusWithANumber(bus.getNumberOfBus()) == false) {
					m_V[i].m_station.addNewBus(bus);
				}
				
				if (posTo == -1) {
					for (unsigned m = i + 1; m < m_countV; ++m) {
						if (m_V[m].m_station.getNumberOfStation() == to.getNumberOfStation() && m_V[m].m_station.passedABusWithANumber(bus.getNumberOfBus())==false) {
							m_V[m].m_station.addNewBus(bus);
							break;
						}
					}
				}

				break;
			}
			else {
				m_V[i].m_E.push_back(Edge(to, bus.getNumberOfBus()));
				//Добавка, за да работи addBus коректно

				if (m_V[i].m_station.passedABusWithANumber(bus.getNumberOfBus()) == false) {
					m_V[i].m_station.addNewBus(bus);
				}

				if (posTo == -1) {
					for (unsigned m = i + 1; m < m_countV; ++m) {
						if (m_V[m].m_station.getNumberOfStation() == to.getNumberOfStation() && m_V[m].m_station.passedABusWithANumber(bus.getNumberOfBus()) == false) {//Може би проверката за опсетеност е излишна тъкй като се справих с проблема с дубрлирането като направих валидация в BusStation::addBus()
							m_V[m].m_station.addNewBus(bus);
							break;
						}
					}
				}

			//	std::cout << "Successfull added "/*<<m_V[i].m_E.size()*/ << std::endl;
				break;
			}
		}
	}
	++m_countE;
}

bool Transport::hasStationWithNumber(unsigned number) const
{
	for (unsigned i = 0; i < m_countV; ++i) {
		if (m_V.at(i).m_station.getNumberOfStation() == number) {
			return true;
		}
	}
	return false;
}

bool Transport::hasEdgeWithBus(BusStation& from, BusStation& to, unsigned busNumber)
{
	if (from.passedABusWithANumber(busNumber) == false || to.passedABusWithANumber(busNumber) == false) {
		return false;
	}
	for (unsigned i = 0; i < m_countV; ++i) {
		if (m_V[i].m_station.getNumberOfStation() == from.getNumberOfStation()) {//Сверяваме номерата на станциите, защото те са еднакви и няма оператор==
			std::list<Edge>::iterator it =m_V[i].m_E.begin();
			while (it != m_V[i].m_E.end()) {
				
				if (it->m_to.getNumberOfStation() == to.getNumberOfStation()&& it->m_numberOfBus==busNumber) {
					return true;
				}
				++it;
			}
		}
	}
	return false;
}

void Transport::removeStation(unsigned numberOfStation)
{
	int pos = DEFAULT_VALUE_FOR_POS;
	for (unsigned i = 0; i < m_countV; ++i) {
		if (m_V[i].m_station.getNumberOfStation() == numberOfStation) {
			pos = i;
			break;
		}
	}
	if (pos == DEFAULT_VALUE_FOR_POS) {
		std::cout << "Station " << numberOfStation << " is not exist." << std::endl;
		return;
	}
	if (pos != DEFAULT_VALUE_FOR_POS) {
		std::vector<Bus> busesPassingStop = m_V[pos].m_station.getListOfBuses();
		unsigned size = busesPassingStop.size();

		//Преди да изтриием станцията от транспортната мрежа, трябва да се изтрие станцията от графика на всички автобуси минаващи през нея.
		for (unsigned i = 0; i < size; ++i) {
			
			//m_V[pos].m_station.getListOfBuses().at(i).removeStation(numberOfStation);
			busesPassingStop.at(i).removeStation(numberOfStation);//работи
		//	std::cout << "busesPassingStop.at(i) has station: " << busesPassingStop.at(i).hasVisitStation(numberOfStation) << std::endl;

		}
	
		m_V[pos].m_station.setListOfBuses(busesPassingStop);//setListOfBuses работи(тестван)
		//m_V[pos].m_station.showScheduleOfBuses();

		/*std::vector<Bus> b = m_V[pos].m_station.getListOfBuses();
		std::cout << "transport: remove bus list: size= " <<b.size()<< std::endl;
		for (size_t f = 0; f < b.size(); ++f) {
			b.at(f).printScheduleForAllStations();
		}*/


		//Изтриване на спирката от транспортната мрежа.
		while (pos != m_countV - 1) {
			m_V[pos] = m_V[pos + 1];
			m_V[pos].m_station = m_V[pos + 1].m_station;
			m_V[pos].m_E = m_V[pos + 1].m_E;
			++pos;
		}
		--m_countV;
	}
}
int Transport::addStationInRunProgram(BusStation& station)
{
	for (unsigned i = 0; i < m_countV; ++i) {
		if (m_V.at(i).m_station.getNumberOfStation() == station.getNumberOfStation()) {
			std::cout << "Station " << station.getNumberOfStation() << " exsits." << std::endl;
			return -1;
		}
	}

	m_V.push_back(station);

	for (unsigned i = 0; i < m_countV; ++i) {
		std::vector<Bus> buses = station.getListOfBuses();
		size_t size = buses.size();
		for (size_t j = 0; j < size; ++j) {

			if (m_V[i].m_station.passedABusWithANumber(buses.at(j).getNumberOfBus())==true) {
				
				std::vector<Schedule> sh2 = m_V[i].m_station.getBusWithNumber(buses.at(j).getNumberOfBus()).getSchedule();
				std::vector<Schedule> sh1 = buses.at(j).getSchedule();
				
				size_t sizeSh2 = sh2.size();
				size_t sizeSh1 = sh1.size();

				for (size_t k = 0; k < sizeSh2; ++k) {
					//std::cout << sh2.at(k).getArrivalTimeOfIndex(0) << "   " << sh1.at(sizeSh1-1).getArrivalTimeOfIndex(0)/*buses.at(j).getScheduleForStation(station.getNumberOfStation()).getArrivalTimeOfIndex(0)*/<< std::endl;
					if (sh2.at(k).getArrivalTimeOfIndex(0) < sh1.at(sizeSh1-1).getArrivalTimeOfIndex(0)) {
						addEdge(m_V[i].m_station, station, buses.at(j));
					}
					else {
						addEdge(station, m_V[i].m_station, buses.at(j));
					//	std::cout << "else "<<hasEdge(station, m_V[i].m_station)<<"  "<<hasEdge(m_V[i].m_station, station) << std::endl;
					}
				}
			}
		}
	}
	++m_countV;
	++maxCountV;
	return 1;
}
/* След изтриване на спирка от градската мрежа, извежада и разписа на автобусите, които са минавали ппрез тази сприка
*/
void Transport::printScheduleForStation(unsigned numberOfStation) const
{
	unsigned maxForJ = m_V.at(m_countV - 1).m_station.getNumberOfStation();//Гарантирано ни е че спиркити са от 0 до N-1
	
	bool flag = false;

	/* Има пробелем, когато е изтрита една спирка от транспортната мрежа при принтиране на разписа се извежда и разписа на автобус
	*  за вече изтритата стнация.
	*/
	for (unsigned i = 0; i < m_countV; ++i) {
		if (m_V.at(i).m_station.getNumberOfStation() == numberOfStation) {
			flag = true;
			BusStation busStation = m_V[i].m_station;
			//if (hasStationWithNumber(busStation.getNumberOfStation()) == true) {//добавен е if за ди видя дали ще показва само информация за станциите, които съществуват
				/*busStation.showScheduleOfBuses();
				return;*/
			//}

			std::vector<Bus> buses = m_V[i].m_station.getListOfBuses();
			size_t size = buses.size();
			for (size_t i = 0; i < size; ++i) {
				//for (size_t j = 0; j <= m_countV; ++j) {//не трябва да е до m_countV защото при триене на произволна станция ще върви до броя на станциите , а възмогно да има станция с по-голяма номер от броя на станциите
				//	if (/*buses.at(i).hasVisitStation(j) == true &&*/ hasStationWithNumber(j)==true) {
				//		buses.at(i).printScheduleForStation(j);
				//		
				//	}
				//}
				for (size_t j = 0; j <= maxForJ; ++j) {
					//std::cout << "j= " << j << " hasStWithNumber: " << hasStationWithNumber(j) << std::endl;
					if (/*buses.at(i).hasVisitStation(j) == true &&*/ hasStationWithNumber(j) == true) {
						//std::cout <<"buses.at(i).getNumberOfBus():" <<buses.at(i).getNumberOfBus() << std::endl;
					//	if (buses.at(i).hasVisitStation(j) == true) {
						//	buses.at(i).printScheduleForStation(j);//09.08.2021
						printShForBus(buses.at(i).getNumberOfBus());
						break;
					//	}		
					}
				}
			}
			return;
		}
	}
	if (flag == false) {
		std::cout << "Bus station " << numberOfStation << " is not exist." << std::endl;
	}
	
}

void Transport::printStation() const
{
	for (unsigned i = 0; i < m_countV; ++i) {
		std::cout << m_V[i].m_station.getNumberOfStation() << " ";
	}
	std::cout << std::endl;
}

bool Transport::hasBusInNetwork(unsigned numberBus) const
{
	for (unsigned i = 0; i < m_countV; ++i) {
		BusStation temp = m_V[i].m_station;
		std::vector<Bus> tempBusList = temp.getListOfBuses();
		unsigned size = tempBusList.size();
		for (size_t i = 0; i < size; ++i) {
			if (tempBusList.at(i).getNumberOfBus() == numberBus) {
				return true;
			}
		}
	}
	return false;
}

void Transport::addScheduleForBusInNetwork(unsigned numberBus, Schedule& sh)
{
	//Няма валидация, тъй като ще се използва само в ManageTransport::runProgram
	for (unsigned i = 0; i < m_countV; ++i) {
		BusStation temp = m_V[i].m_station;
		std::vector<Bus> tempBusList = temp.getListOfBuses();
		size_t size = tempBusList.size();
		for (size_t j = 0; j < size; ++j) {
			if (tempBusList.at(j).getNumberOfBus() == numberBus) {
				std::vector<Schedule> newSh = m_V[i].m_station.getListOfBuses().at(j).getSchedule();
				newSh.push_back(sh);
				tempBusList.at(j).setScheduleForEachBusStation(newSh);
				//std::cout << "m_V[i].m_station.getListOfBuses().at(j).addScheduleForStation(sh); ";
				m_V[i].m_station.setListOfBuses(tempBusList);
				//m_V[i].m_station.getListOfBuses().at(j).printScheduleForAllStations();
				//m_V[i].m_station.showScheduleOfBuses();
				return;
			}
		}
	}
}


//Bus Transport::getBusFromTransport(unsigned numberOfBus)
//{
//	for (int i = 0; i < m_countV; ++i) {
//		BusStation temp = m_V[i].m_station;
//		std::vector<Bus> tempBusList = temp.getListOfBuses();
//		unsigned size = tempBusList.size();
//		for (int i = 0; i < size; ++i) {
//			if (tempBusList.at(i).getNumberOfBus() == numberOfBus) {
//				return tempBusList.at(i);
//			}
//		}
//	}
//	std::cout << "no bus " << numberOfBus << std::endl;
//	return Bus();
//}

void Transport::serializeTransport(std::ofstream& ofs) 
{
	if (!ofs.is_open()) {
		std::cout << "File is not open." << std::endl;
		return;
	}

	ofs.write((const char*)&m_countV, sizeof(m_countV));
	ofs.write((const char*)&m_countE, sizeof(m_countE));

	Node* temp = new(std::nothrow) Node[m_countV];
	for (unsigned i = 0; i < m_countV; ++i) {
		temp[i] = m_V[i];
	}
	ofs.write((const char*)&temp, sizeof(temp));

	/*if (ofs.good()) {
		std::cout << "yes tr" << std::endl;
	}
	else {
		std::cout << "no tr ser" << std::endl;
	}*/
}

void Transport::deserializeTransport(std::ifstream& ifs) {
	if (!ifs.is_open()) {
		std::cout << "File is not open." << std::endl;
		return;
	}
	ifs.read((char*)&m_countV, sizeof(m_countV));
	ifs.read((char*)&m_countE, sizeof(m_countE));

	Transport::Node* temp = new(std::nothrow) Transport::Node[m_countV];
	if (temp == nullptr) {
		std::cout << "Not enought memory. " << std::endl;
		return;
	}
	ifs.read((char*)&temp, sizeof(temp));
	for (unsigned i = 0; i< m_countV; ++i) {	
		m_V.push_back(temp[i]);
	}
	/*if (ifs.good()) {
		std::cout << "transport deserialization- yes" << std::endl;
	}
	else {
		std::cout << "Transport deserialization-no" << std::endl;
	}*/

}


unsigned Transport::biggestNumOfStation() const
{
	return m_V.at(m_countV - 1).m_station.getNumberOfStation();
}

void Transport::clearMemory()
{
	m_V.clear();
}

void Transport::addBus(Bus& newBus)
{
	//Тази функция ще се използва след направена валидация на маршрута на автобуса(вече е била направена провека дали такива станции съществеват).
	unsigned countStation = newBus.getCountOfStations();
	unsigned* route = new(std::nothrow) unsigned[countStation];
	if (route == nullptr) {
		std::cout << "Not enought memory for route. The procedure for adding a new bus will be terminated." << std::endl;
		return;
	}

	route = newBus.getRoute();

	if (countStation > 1) {
		for (unsigned i = 0; i < countStation; ++i) {
			if (i != countStation - 1) {
				BusStation from = getStation(route[i]);
				BusStation to = getStation(route[i + 1]);

				//DEBUG
				//std::cout << from.getNumberOfStation() << "	" << to.getNumberOfStation() << std::endl;

				//Проверка за всеки случай, но е излишна при направените съображения на ред 697
				if (from.getName() == nullptr || to.getName() == nullptr) {
					std::cout << "Invalid data. The procedure for adding a new bus will be terminated." << std::endl;
					return;
				}
				addEdge(from, to, newBus);
				
			}
			else {
				for (unsigned j = 0; j < m_countV; ++j) {
					if (m_V[j].m_station.getNumberOfStation() == route[countStation-1]) {
						m_V[j].m_station.addNewBus(newBus);
					}
				}
			}
		}
	}
	//Ако автобусът минава през само една спирка
	else {
		for (unsigned i = 0; i < m_countV; ++i) {
			if (m_V[i].m_station.getNumberOfStation() == route[0]) {
				m_V[i].m_station.addNewBus(newBus);
			}
		}
	}
}

void Transport::printShForBus(unsigned busNum) const
{
	for (unsigned i = 0; i < m_countV; ++i) {
		std::vector<Bus> lisOfB = m_V[i].m_station.getListOfBuses();
		for (size_t j = 0; j < lisOfB.size(); ++j) {
			if (lisOfB.at(j).getNumberOfBus() == busNum) {
				lisOfB.at(j).printScheduleForAllStations();
				return;
			}
		}
	}
}


void Transport::addNewCourse(unsigned numBus)
{
	/*if (hasBusInNetwork(numBus) == false) {
		std::cout << "Bus " << numBus << " is not exist. Tthe procedure for adding a new course will be terminated." << std::endl;
		return;
	}*/

	for (unsigned i = 0; i < m_countV; ++i) {
		std::vector<Bus> listOfBuses = m_V[i].m_station.getListOfBuses();
		
		size_t size = listOfBuses.size();

		for (size_t j = 0; j < size; ++j) {
			//Намерен е автобуса
			if (listOfBuses.at(j).getNumberOfBus() == numBus) {
				
				unsigned countStationInRoute = listOfBuses[j].getCountOfStations();
				std::vector<unsigned> route;

				for (unsigned y = 0; y < countStationInRoute; ++y) {
					
					if (hasStationWithNumber(listOfBuses.at(j).getSchedule().at(y).getNumberOfStation())) {
						route.push_back(listOfBuses.at(j).getSchedule().at(y).getNumberOfStation());//ok
					}
				}

				std::cout << "Please enter the times in sequence" << std::endl;
				std::vector<Schedule> newSchedules;

				//Преминаване през всички станции, през които минава автобуса
				size_t size = route.size();
				for (size_t k = 0; k <size; ++k) {
					unsigned time;

					//Валидация на въведеното време
					do {
						std::cout << "Time for station " << route.at(k) << ": ";
						std::cin >> time;
					} while (time > MAX_MIN || time < 0);
					
					Schedule tempSh = listOfBuses.at(j).getScheduleForStation(route[k]);
					tempSh.addNewArrivalTime(time);

					//Сортиранe на графика, за да работи коректно програмата в последствие.
					//tempSh.sortArrivalTime();
					newSchedules.push_back(tempSh);

				}
				size_t sizeNewSche = newSchedules.size();
				for (size_t t = 0; t < sizeNewSche; ++t) {
					newSchedules.at(t).sortArrivalTime();
				}
				listOfBuses.at(j).setScheduleForEachBusStation(newSchedules);

				//std::cout << "listOfBuses.at(j).setScheduleForEachBusStation(newSchedules);";
			//	listOfBuses.at(j).printScheduleForAllStations();
				m_V[i].m_station.setListOfBuses(listOfBuses);

				//m_V[i].m_station.getListOfBuses().at(j).printScheduleForAllStations();

				return;				
			}
		}
	}
	std::cout << "Bus " << numBus << " is not exist. Tthe procedure for adding a new course will be terminated." << std::endl;
}


bool Transport::hasEdge(BusStation& from, BusStation& to) {
	for (int i = 0; i < m_countV; ++i) {
		if (m_V[i].m_station.getNumberOfStation() == from.getNumberOfStation()) {//Сверяваме номерата на станциите, защото те са еднакви и няма оператор==
			std::list<Edge>::iterator it = m_V[i].m_E.begin();
			while (it != m_V[i].m_E.end()) {
				if (it->m_to.getNumberOfStation() == to.getNumberOfStation()) {
					return true;
				}
				++it;
			}
		}
	}
	return false;
}

int Transport::minTimeToReachBusStation(BusStation& from, BusStation& to, unsigned timeToReachBusStation1)
{
	//Трабва да има автобус от from до to.
	if (hasEdge(from, to) == false) {
		std::cout << "No direct bus" << std::endl;
		return -1;
	}

	std::vector<Bus> busFrom = from.getListOfBuses();
	size_t size = busFrom.size();
	std::vector<Schedule> scheduleFrom;//разписи на автобусите минаващи през from
	std::vector<Schedule> scheduleTo;//разписи на автобусите минаващи през to
	std::vector<unsigned> busesNumber;
	for (size_t i = 0; i < size; ++i) {
	//	busFrom.at(i).getScheduleForStation(to.getNumberOfStation());

		//Взимаме разписанието на вески автобус от станция from до станция to
		if (busFrom.at(i).hasVisitStation(to.getNumberOfStation()) == true) {
			//Взимаме разписанието на автобуса, когато пристига на стайнция from
			scheduleFrom.push_back(busFrom.at(i).getScheduleForStation(from.getNumberOfStation()));
			
			/*busFrom.at(i).getScheduleForStation(from.getNumberOfStation()).printSchedule();
			scheduleFrom.front().printSchedule();
			std::cout << "schedulefrom: " << scheduleFrom.size() << std::endl;*/

			//Взимаме разписанието на автобус, когато пристига на станция to
			scheduleTo.push_back(busFrom.at(i).getScheduleForStation(to.getNumberOfStation()));
			busesNumber.push_back(busFrom.at(i).getNumberOfBus());
				
		}
	}

	//std::cout << "After getSchedule for every bus: " << scheduleFrom.size() << " " << scheduleTo.size() << std::endl;
	size_t sizeOfSchedules = scheduleFrom.size();
	for (size_t k = 0; k < sizeOfSchedules; ++k) {
		size_t tempSize = scheduleFrom.at(k).getSizeOfArrivalTime();
		if (k == sizeOfSchedules - 1 && scheduleFrom.at(k).getArrivalTimeOfIndex(tempSize - 1) < timeToReachBusStation1) {
			std::cout << "No bus" << std::endl;
			return -1;
		}
	}

	/* Ако има само един автобус между двете сприки, то ще върне най-бързото време за отпътуване от спирка from до спирка to, т.е
	*  взимаме най-близкото време за заминаване от спирка from до спирка to, което е времето от разписа на from  след времето 
	*  на приситгане на станция from- timeToReachBusStation1
	*/
	if (sizeOfSchedules == 1) {
			//return schedule.front().getNextArrivalTimeAfter(timeToReachBusStation1);
		unsigned timeBusReachFromAfterWaiting = scheduleFrom.front().getNextArrivalTimeAfter(timeToReachBusStation1);
			//std::cout << "timeBusReachFromAfterWaiting: " << timeBusReachFromAfterWaiting << std::endl;
			//Позиция на времето, в което ще пристигне автобуса, на който трябва да се качим
		unsigned pos = scheduleFrom.front().getIndexOfTime(timeBusReachFromAfterWaiting);
			//std::cout << "pos: " << pos << std::endl;

			/* Време за изчакване= времето на пристигане на автобуса, на който трябва да се качим, на спирка from -
			 *  време на пристигане на пътника на сприка from 
			*/
		unsigned waitingTime = timeBusReachFromAfterWaiting - timeToReachBusStation1;

			/* Време за достигане от едната до другата спирка=
			*  време изчакване + разликата от времето на пристигане на спирка to и времето на тръгване от спирка from
			*/
		unsigned allTimeToReachStationTo = waitingTime + (scheduleTo.front().getArrivalTimeOfIndex(pos)- scheduleFrom.front().getArrivalTimeOfIndex(pos));
		numberOfBus = busesNumber.front();
	}
	/* Има повече от един автобус, който върви от станция from до станция to.
	*  В такъв случай минаваме по разписанието на автобуса за достигане на станция from и взимаме най-близкото време за 
	*  отпътуване от станцията след времето на пристигане на нея.
	*/

	unsigned sizeScheduleFrom = scheduleFrom.size();
	unsigned startTime = scheduleFrom.front().getNextArrivalTimeAfter(timeToReachBusStation1);
	unsigned waitingTime = startTime - timeToReachBusStation1;
		//DEBUG
		//std::cout << "waiting time: " << waitingTime << std::endl;

	unsigned tempWaitingTime = waitingTime;

		//време за преминаване от станция Х до станция У= време за изчакване+ време път между двете станции
	unsigned minAllTimeToGetDestinationFromTo = waitingTime + (scheduleTo.front().getNextArrivalTimeAfter(startTime) - startTime);//timeToReachBusStation1 + (scheduleTo.front().getNextArrivalTimeAfter(startTime)- startTime);
		

	unsigned tempTimeToGetDestinationFromTo = minAllTimeToGetDestinationFromTo;

	for (int i = 0; i < sizeScheduleFrom; ++i) {
		unsigned help = scheduleFrom.at(i).getNextArrivalTimeAfter(timeToReachBusStation1);
		tempWaitingTime =help - timeToReachBusStation1;
		tempTimeToGetDestinationFromTo = tempWaitingTime + (scheduleTo.at(i).getNextArrivalTimeAfter(help) - help);// timeToReachBusStation1 +(scheduleTo.at(i).getNextArrivalTimeAfter(timeToReachBusStation1)-scheduleFrom.at(i).getNextArrivalTimeAfter(timeToReachBusStation1)));
		if (tempTimeToGetDestinationFromTo< minAllTimeToGetDestinationFromTo) {
			swap(minAllTimeToGetDestinationFromTo, tempTimeToGetDestinationFromTo);
				//waitingTime = tempWaitingTime;//може би не ни трябва
			numberOfBus = busesNumber.at(i);
		}
	}
	return minAllTimeToGetDestinationFromTo;
}

Bus Transport::getBusFromTransport(unsigned numberOfBus)const 
{
	//Няма валидация, защото ще изпалзва след вече напрвена такава в addNewStation
	for (unsigned i = 0; i < m_countV; ++i) {
		std::vector<Bus> listOfBuses = m_V[i].m_station.getListOfBuses();
		size_t size = listOfBuses.size();
		for (size_t j = 0; j < size; ++j) {
			if (listOfBuses.at(j).getNumberOfBus() == numberOfBus) {
				return listOfBuses.at(j);
			}
		}
	}
}

BusStation Transport::getStation(unsigned numberStation) const
{
	for (unsigned i = 0; i < m_countV; ++i) {
		if (m_V[i].m_station.getNumberOfStation() == numberStation) {
			return m_V[i].m_station;
		}
	}
	std::cout << "Bus station " << numberStation << " is not exist." << std::endl;
	return BusStation();
}

void Transport::printBusesOfStation(unsigned num) const
{
	std::vector<Bus> buses;
	for (unsigned i = 0; i < m_countV; ++i) {
		if (m_V.at(i).m_station.getNumberOfStation() == num) {
			buses=m_V.at(i).m_station.getListOfBuses();
			break;
		}
		if (m_V.at(i).m_station.getNumberOfStation() != num && i == m_countV - 1) {
			std::cout << "Bus station " << num << " is not exist." << std::endl;
			return;
		}
	}
	

	std::cout << "Buses of station " << num << ": ";
	size_t size = buses.size();
	for(size_t i=0;i<size;++i){
		std::cout << buses.at(i).getNumberOfBus() << " ";
	}
	std::cout << std::endl;
}

unsigned Transport::numberBusWithMinTimeToReachBusStation(BusStation& from, BusStation& to, unsigned timeToReachBusStation1)
{
	return numberOfBus;
}

void Transport::printTheShortestPath(BusStation& startBusStation, BusStation& finalBusStation, unsigned timeToStart)
{
	//Валидация
	if (hasStationWithNumber(startBusStation.getNumberOfStation()) == false || hasStationWithNumber(finalBusStation.getNumberOfStation()) == false) {
		std::cout << "Invalid data." << std::endl;
		return;
	}
	
	static const int NO_PARENT = -3;
	static const int START_PARENT = -1;
	std::vector<int> parent;
	std::vector<unsigned> distance;
	unsigned countStation = 0;

	unsigned  toSumCorrect=0;
	for (unsigned i = 0; i < m_countV; ++i) {
		parent.push_back(START_PARENT);
		distance.push_back(std::numeric_limits<unsigned int>::max());
	}

	parent[startBusStation.getNumberOfStation()] = NO_PARENT;

	distance[startBusStation.getNumberOfStation()]= timeToStart;

	std::vector<unsigned> buses;
	
	Heap<std::pair<unsigned, int>> helpHeap;
	helpHeap.push(std::pair<unsigned, int>(distance[startBusStation.getNumberOfStation()], startBusStation.getNumberOfStation()));

	unsigned sumTime = 0;
	unsigned helpTimeToCalculateAllTimeToTravel = 0;
	while (!helpHeap.empty()) {
		unsigned currentNodeDistance = helpHeap.top().first;
		int currentNodeNumber = helpHeap.top().second;

		//Провим го с bfs
		if (currentNodeNumber == finalBusStation.getNumberOfStation()) {
			//std::cout << "The time you will travel from station " << startBusStation.getNumberOfStation() << " to station "
			//	<< finalBusStation.getNumberOfStation() << " is " << sumTime-timeToStart << "." << std::endl;//това е часът в който ще пристигнем на последната станция.
			

			//std::cout << "countStation= " << countStation << std::endl;

			if (countStation > 2) {
				std::cout << "The time when you reach the last station is " << sumTime - toSumCorrect << std::endl;
				std::cout << "Time to reach from station " << startBusStation.getNumberOfStation() << " to station " << finalBusStation.getNumberOfStation()
					<< " is " << sumTime - toSumCorrect - timeToStart << ". " << std::endl;

				std::cout << "The order of the stations through which you will pass in the ones derived from the last station is: ";
				for (int backNumb = currentNodeNumber; backNumb != NO_PARENT; backNumb = parent[backNumb]) {

					std::cout << m_V[backNumb].m_station.getNumberOfStation() << " ";
				}
				std::cout << std::endl;
				std::cout << "Buses: ";
				for (size_t t = 0; t < buses.size(); ++t) {
					std::cout << buses.at(t) << " ";
				}
				std::cout << std::endl;
				return;
			}
			else {
				std::cout << "Time to reach from station " << startBusStation.getNumberOfStation() << " to station " << finalBusStation.getNumberOfStation()
					<< " is " << sumTime << ". " << std::endl;

				//	std::cout << "print: " << currentNodeNumber << " " << finalBusStation.getNumberOfStation() << std::endl;
				std::cout << "The order of the stations through which you will pass in the ones derived from the last station is: ";
				for (int backNumb = currentNodeNumber; backNumb != NO_PARENT; backNumb = parent[backNumb]) {

					std::cout << m_V[backNumb].m_station.getNumberOfStation() << " ";
				}
				std::cout << std::endl;
				std::cout << "Buses: ";
				for (size_t t = 0; t < buses.size(); ++t) {
					std::cout << buses.at(t) << " ";
				}
				std::cout << std::endl;
				return;
			}
			
		}

		helpHeap.pop();
		Transport::Node currentNode = m_V[currentNodeNumber].m_station;
		currentNode.m_E = m_V[currentNodeNumber].m_E;
		++countStation;
		
		unsigned s;
		for (std::list<Transport::Edge>::iterator it = currentNode.m_E.begin(); it != currentNode.m_E.end(); ++it) {
			//std::cout << currentNode.m_station.getNumberOfStation() << "	" << it->m_to.getNumberOfStation() << std::endl;

			int newDistance = minTimeToReachBusStation(currentNode.m_station, it->m_to, distance[currentNode.m_station.getNumberOfStation()]/*+sumTime*/);
		//	std::cout << "After minTimeToReachBusStation distance[...]: " << distance[currentNode.m_station.getNumberOfStation()] << std::endl;
			if (newDistance == -1) {
				std::cout << "Invalid data." << std::endl;
				return;
			}
			
			buses.push_back(numberBusWithMinTimeToReachBusStation(currentNode.m_station, it->m_to, newDistance));
			if (it == currentNode.m_E.begin()) {
				s = newDistance;
				if (toSumCorrect == 0) {//Правя го за по-добър изход
					toSumCorrect = s;
				}
			}

			if (it == currentNode.m_E.begin()) {
				helpTimeToCalculateAllTimeToTravel = timeToStart;
			}
			//newDistance на всяко пръвъртане на цикъла ще времето от началота на пътуването до момнета на дадената спирка
			//Време на пътуване е равно на newDistance- timeToStart
			//Newdistance e моментът в който сме достигнали дадена станция

			//std::cout << "From station " << currentNodeNumber << ", station " << it->m_to.getNumberOfStation() << " is reached in " << newDistance<< " minutes." << std::endl;
			if (distance[it->m_to.getNumberOfStation()] > newDistance) {
				parent[it->m_to.getNumberOfStation()] = currentNodeNumber;
				//std::cout << "parent[it->m_to.getNumberOfStation()]= " << parent[it->m_to.getNumberOfStation()] << std::endl;
				
				distance[it->m_to.getNumberOfStation()] = newDistance/*+ distance[currentNode.m_station.getNumberOfStation()]*/;//++distanse[currentN.m_st]
				//std::cout << "distance[it->m_to.getNumberOfStation()]= " << /*newDistance*/ distance[it->m_to.getNumberOfStation()]+s << std::endl;
				helpHeap.push(std::pair<unsigned, int>(newDistance, it->m_to.getNumberOfStation()));
				sumTime += newDistance;
			}
			
		}
	}
	std::cout << "There is no way." << std::endl;
}

BusStation Transport::getStation(unsigned numberOfStation)
{
	//BusStation notExistStation;
	//notExistStation.setNumberOfStattion(-1);//невалидна станция
	for (int i = 0; i < m_countV; ++i) {
		if (m_V[i].m_station.getNumberOfStation() == numberOfStation) {
			return m_V[i].m_station;
		}
	}
	std::cout << "Station " << numberOfStation << " is not of transport network." << std::endl;
	//return notExistStation;
}

//void Transport::Node::serializeNode(std::ofstream& ofs) {
//	if (!ofs.is_open()) {
//		std::cout << "File is not open" << std::endl;
//		return;
//	}
//
//	unsigned size = m_E.size();
//	for (int i = 0; i < size; ++i) {
//		m_E.front().serializeEdge(ofs);
//		m_E.pop_front();
//	}
//
//	m_station.serializeBusStation(ofs);
//
//	if (ofs.good()) {
//		std::cout << "yes Node ser" << std::endl;
//	}
//	else {
//		std::cout << "No node ser" << std::endl;
//	}
//}
//
//
//void Transport::Node::deserializeNode(std::ifstream& ifs) {
//	if (!ifs.is_open()) {
//		std::cout << "File is not open" << std::endl;
//		return;
//	}
//
//	int size = ifs.tellg() / sizeof(Edge);
//	Edge* temp = new(std::nothrow) Edge[size];
//	if (temp != nullptr) {
//		ifs.read((char*)&temp, sizeof(temp));
//		for (int i = 0; i < size; ++i) {
//			m_E.push_back(temp[i]);
//		}
//	}
//	else {
//		std::cout << "Not enought memory for read data." << std::endl;
//		return;
//	}
//
//	if (ifs.good()) {
//		std::cout << "yes node deserialize" << std::endl;
//	}
//	else {
//		std::cout << "no  node deserialize " << std::endl;
//	}
//}



//void Transport::changeRouteOfBus(unsigned busNumber)
//{
//	for (unsigned i = 0; i < m_countV; ++i) {
//		//Взимане на автобисите минави през сатницята
//		std::vector<Bus> tempBusList = m_V[i].m_station.getListOfBuses();
//		std::vector<Schedule> newSchedule;
//		size_t sizeTemp = tempBusList.size();
//
//		unsigned stationNumber;
//
//		for (size_t j = 0; j < sizeTemp; ++j) {
//
//			if (tempBusList.at(j).getNumberOfBus() == busNumber) {
//				std::cout << "Please enter the count of bus stops: ";
//				unsigned countBusStops;
//				std::cin >> countBusStops;
//
//				unsigned beforeChnage = tempBusList.at(j).getCountOfStations();
//
//				unsigned* route = new(std::nothrow) unsigned[countBusStops];
//				if (route == nullptr) {
//					std::cout << "Not enought memory for route. Error! The procedure for changing the route of bus " << busNumber << " will be terminated. " << std::endl;
//					return;
//				}
//
//				std::cout << "Please enter the stop numbers in the order in which the bus passes through them." << std::endl;
//				tempBusList.at(j).setCountOfStation(countBusStops);
//				
//				for (unsigned k = 0; k < countBusStops; ++k) {
//					//Валидация дали има такава станция в мрежата
//					do {
//						std::cout << "Please enter the station number: ";
//						std::cin >> stationNumber;
//					} while (hasStationWithNumber(stationNumber) == false);
//					
//					route[k] = stationNumber;
//
//					std::cout << "Please enter how many times a day the bus passes through this stop: ";
//					unsigned timesToStation;
//					std::cin >> timesToStation;
//
//					std::vector<unsigned> arrivalTime;
//
//					std::cout << "Please enter the data from the bus arrival schedule in ascending order." << std::endl;
//					for (int t = 0; t < timesToStation; ++t) {
//						unsigned time;
//						if (t == 0) {
//							std::cout << "Time: ";
//							std::cin >> time;
//											
//							std::cout << arrivalTime.size() << std::endl;
//							arrivalTime.push_back(time);				
//						}
//						else {
//							//Гарантира възходящ ред
//							do {
//								std::cout << "Time: ";
//								std::cin >> time;
//							}while (arrivalTime.at(t - 1) > time/*arrivalTime[i - 1] > arrivalTime[i]*/);
//											//arrivalTime[i] = time;
//							arrivalTime.push_back(time);
//						}
//									
//					}
//					Schedule sh(stationNumber, arrivalTime);//work
//
//					//std::cout << "DEBUG: sh info:" << sh.getNumberOfStation() << std::endl;
//					//sh.printSchedule();
//
//					newSchedule.push_back(sh);//work
//					//newSchedule.at(0).printSchedule();//work
//				}
//				tempBusList.at(j).setScheduleForEachBusStation(newSchedule);//wokr
//				//std::cout << "tempBusList.at(j).printScheduleForAllStations()" << std::endl;
//				//tempBusList.at(j).printScheduleForAllStations();//До тук работи коректно
//
//				//std::cout << "m_V[i].m_station.getListOfBuses().at(j).getNumber(): " << m_V[i].m_station.getListOfBuses().at(j).getNumberOfBus() << std::endl;
//				m_V[i].m_station.getListOfBuses().at(j).setCountOfStation(countBusStops);
//				m_V[i].m_station.setListOfBuses(tempBusList);
//
//
//				/*m_V[i].m_station.getListOfBuses().at(j).setScheduleForEachBusStation(newSchedule);
//				std::cout << "m_V[i].m_station.getListOfBuses().at(j).setScheduleForEachBusStation(newSchedule);" << std::endl;
//				m_V[i].m_station.getListOfBuses().at(j).printScheduleForAllStations();
//
//				m_V[i].m_station.getListOfBuses().at(j).setRoute(route, countBusStops);*/
//				return;
//			}
//		}
//	}
//	std::cout << "Bus " << busNumber << " is not exist." << std::endl;
//
//	//for (int i = 0; i < m_countV; ++i) {
//	//	std::vector<Schedule> scheduleForBus;
//	//	unsigned stationNumber;
//	//	BusStation temp = m_V[i].m_station;
//	//	std::vector<Bus> tempBusList = temp.getListOfBuses();
//	//	unsigned size = tempBusList.size();
//	//	for (int j = 0; j < size; ++j) {
//	//		std::cout << "in second if" << std::endl;
//	//		if (tempBusList.at(j).getNumberOfBus() == busNumber) {
//	//			
//	//			std::cout << "Please enter the number of bus stops: ";
//	//			unsigned numberOfBusStopes;
//	//			std::cin >> numberOfBusStopes;
//
//	//			unsigned beforeChnage = tempBusList.at(j).getCountOfStations();
//
//	//			tempBusList.at(j).setCountOfStation(numberOfBusStopes);
//
//	//			std::cout << "cntOfSt: " << tempBusList.at(j).getCountOfStations() << std::endl;
//
//	//			unsigned* route = new(std::nothrow) unsigned[numberOfBusStopes];
//
//	//			if (route == nullptr) {
//	//				std::cout << "Not enought memory for route. Error! The procedure for changing the route of bus " << busNumber << " will be terminated. " << std::endl;
//	//				tempBusList.at(j).setCountOfStation(beforeChnage);
//	//				return;
//	//			}
//
//	//			std::cout << "Please enter the stop numbers in the order in which the bus passes through them." << std::endl;
//
//	//			//std::vector<Schedule> scheduleForBus;
//
//	//			//Въвеждане на разписа на автобуса за всяка станция
//	//			for (int k = 0; k < numberOfBusStopes; ++k) {
//	//				//unsigned stationNumber;
//	//				std::cout << "Please enter the station number: ";
//	//				std::cin >> stationNumber;
//
//	//				route[k] = stationNumber;
//
//	//				std::cout << "Please enter how many times a day the bus passes through this stop: " << std::endl;
//	//				unsigned timesToStation;
//	//				std::cin >> timesToStation;
//
//	//				//unsigned* arrivalTime = new(std::nothrow) unsigned[timesToStation];
//	//				//if (arrivalTime == nullptr) {
//	//				//	std::cout<< "Not enought memory for arrival time.Error!The procedure for changing the route of bus " << numberOfBus << " will be terminated. " << std::endl;
//	//				//	return;
//	//				//}
//	//				std::vector<unsigned> arrivalTime;
//
//	//				std::cout << "Please enter the data from the bus arrival schedule in ascending order." << std::endl;
//	//				for (int t = 0; t < timesToStation; ++t) {
//	//					unsigned time;
//	//					if (t == 0) {
//	//						//std::cout << "if" << std::endl;
//	//						std::cout << "Time: ";
//	//						std::cin >> time;
//	//						//std::cout << "***" << std::endl;
//	//						//arrivalTime[i] = time;
//	//						std::cout << arrivalTime.size() << std::endl;
//	//						arrivalTime.push_back(time);
//	//						//std::cout << "iudfaldfsd" << std::endl;
//	//						//arrivalTime.push_back(time);
//	//					}
//	//					else {
//	//						//Гарантира възходящ ред
//	//						do {
//	//							std::cout << "Time: ";
//	//							std::cin >> time;
//	//						}while (arrivalTime.at(t - 1) > time/*arrivalTime[i - 1] > arrivalTime[i]*/);
//	//						//arrivalTime[i] = time;
//	//						arrivalTime.push_back(time);
//	//					}
//	//				
//	//				}
//
//	//				Schedule sh(stationNumber, arrivalTime);
//	//				scheduleForBus.push_back(sh);
//	//			}
//	//			std::cout << "/////////////////////////////" << std::endl;
//	//			size_t size = scheduleForBus.size();
//	//			
//	//			std::cout << "size: " << size << std::endl;
//	//			std::cout << "first: " << scheduleForBus.at(0).getArrivalTimeOfIndex(1) << std:: endl;
//
//	//			tempBusList.at(j).setScheduleForEachBusStation(scheduleForBus);
//	//			tempBusList.at(j).setRoute(route, numberOfBusStopes);
//
//	//			std::cout << "in func: " << std::endl;
//	//			std::cout << tempBusList.at(j).getNumberOfBus() << std::endl;
//	//			
//	//			//m_V[i].m_station.setListOfBuses(tempBusList);
//	//			
//	//			for (size_t y = 0; y < m_countV; ++y) {
//	//				if (m_V[y].m_station.getNumberOfStation() == stationNumber) {
//	//					std::cout << "in if" << std::endl;
//	//					m_V[y].m_station.setListOfBuses(tempBusList);
//	//				}
//	//			}
//	//			return;
//	//		}
//	//	}
//	//}
//	//std::cout << "no bus " << numberOfBus << std::endl;
//
//	//Bus busToChange = getBusFromTransport(busNumber);
//	////Ако не е открит автобус
//	//if (busToChange.getNumberOfBus() == 0) {
//	//	std::cout << "Bus " << busNumber<<" is not exist." << std::endl;
//	//	return;
//	//}
//	//std::cout << "Please enter the number of bus stops: ";
//	//unsigned numberOfBusStopes;
//	//std::cin >> numberOfBusStopes;
//
//	//unsigned beforeChnage = busToChange.getCountOfStations();
//
//	//busToChange.setCountOfStation(numberOfBusStopes);
//
//	//unsigned* route = new(std::nothrow) unsigned[numberOfBusStopes];
//	//if (route == nullptr) {
//	//	std::cout << "Not enought memory for route. Error! The procedure for changing the route of bus " << numberOfBus << " will be terminated. " << std::endl;
//	//	busToChange.setCountOfStation(beforeChnage);
//	//	return;
//	//}
//
//	//std::cout << "Please enter the stop numbers in the order in which the bus passes through them." << std::endl;
//
//	//std::vector<Schedule> scheduleForBus;
//
//	////Въвеждане на разписа на автобуса за всяка станция
//	//for (int i = 0; i < numberOfBusStopes; ++i) {
//	//	unsigned stationNumber;
//	//	std::cout << "Please enter the station number: ";
//	//	std::cin >> stationNumber;
//
//	//	route[i] = stationNumber;
//
//	//	std::cout << "Please enter how many times a day the bus passes through this stop: " << std::endl;
//	//	unsigned timesToStation;
//	//	std::cin >> timesToStation;
//
//	//	//unsigned* arrivalTime = new(std::nothrow) unsigned[timesToStation];
//	//	//if (arrivalTime == nullptr) {
//	//	//	std::cout<< "Not enought memory for arrival time.Error!The procedure for changing the route of bus " << numberOfBus << " will be terminated. " << std::endl;
//	//	//	return;
//	//	//}
//	//	std::vector<unsigned> arrivalTime;
//
//	//	std::cout << "Please enter the data from the bus arrival schedule in ascending order." << std::endl;
//	//	for (int i = 0; i < timesToStation; ++i) {
//	//		unsigned time;
//	//		if (i == 0) {
//	//			std::cout << "if" << std::endl;
//	//			std::cout << "Time: ";
//	//			std::cin >> time;
//	//			std::cout << "***" << std::endl;
//	//			//arrivalTime[i] = time;
//	//			std::cout << arrivalTime.size() << std::endl;
//	//			arrivalTime.push_back(time);
//	//			std::cout << "iudfaldfsd" << std::endl;
//	//			//arrivalTime.push_back(time);
//	//		}
//	//		else {
//	//			//Гарантира възходящ ред
//	//			do {
//	//				std::cout << "Time: ";
//	//				std::cin >> time;
//	//			}while (arrivalTime.at(i - 1) > time/*arrivalTime[i - 1] > arrivalTime[i]*/);
//	//			//arrivalTime[i] = time;
//	//			arrivalTime.push_back(time);
//	//		}
//	//	
//	//	}
//
//	//	Schedule sh(stationNumber, arrivalTime);
//	//	scheduleForBus.push_back(sh);
//	//}
//
//	//busToChange.setScheduleForEachBusStation(scheduleForBus);
//	//busToChange.setRoute(route, numberOfBusStopes);
//}
