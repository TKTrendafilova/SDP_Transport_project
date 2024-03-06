#pragma warning(disable:4996)// за да няма грешка с strcpy
#include<fstream>
#include<cstring>
#include"ManageTransport.hpp"

Manager::Manager(){}

void Manager::open(char* fileName)
{
	std::ifstream ifs(fileName, std::ios::in | std::ios::binary);

	if (!ifs.is_open()) {
		std::cout << "File is not open." << std::endl;
		return;
	}

	ptrIfs = &ifs;
	isSuccessfullyOpenFile = true;

	strcpy(m_nameFile, fileName);

	m_transport.deserializeTransport(ifs);

	if (ifs.good()) {
		std::cout << std::endl << "Successfully opened file " << fileName << std::endl << std::endl;
	}
	else {
		std::cout << "File is not readen." << std::endl;
	}

	ifs.close();
}

void Manager::closeFile()
{
	if (ptrIfs == nullptr && ptrOfs == nullptr) {
		std::cout << std::endl << "Unvalid operation!" << std::endl << std::endl;
		return;
	}

	m_transport.clearMemory();
	isSuccessfullyOpenFile = false;

	std::cout << std::endl << "Successfully closed file." << std::endl << std::endl;
}

void Manager::save()
{
	std::ofstream ofs(m_nameFile, std::ios::out | std::ios::binary);
	if (!ofs.is_open()) {
		std::cout << std::endl << "The file is not saved." << std::endl << std::endl;
		return;
	}
	
	m_transport.serializeTransport(ofs);

	if (ofs.good()) {
		std::cout << std::endl << "Successfully saved " << m_nameFile << std::endl << std::endl;
	}
	else {
		std::cout << std::endl << "Save has failed. " << std::endl << std::endl;
	}
}

void Manager::saveAs(char* newFileName)
{
	std::ofstream ofs(newFileName, std::ios::out | std::ios::binary);

	if (!ofs.is_open()) {
		std::cout << "File is not open! Error";
		return;
	}

	m_transport.serializeTransport(ofs);

	if (ofs.good()) {
		std::cout << std::endl << "Successfully saved another file " << newFileName << std::endl;
	}
	else {
		std::cout << std::endl << "Unsuccessfully saved another file " << newFileName << std::endl;
	}
}



void Manager::help() const
{
	std::cout << std::endl << "The following commands are supported:" << std::endl;
	std::cout << "save" << '\t' << "saves the currently opened file" << std::endl
		<< "help" << '\t' << "prints this information" << std::endl
		<< "close" << '\t' << "to close opened file" << std::endl
		<< "exit" << '\t' << "exit the program" << std::endl
		<< "add bus" << '\t' << "to add new bus" << std::endl
		<< "open<file name>" << '\t' << "opens<file name>" << std::endl
		<< "saveas<file name>" << '\t' << "saves the currently open file in <file name>" << std::endl
		<< "add bus" << '\t' << "to add new bus" << std::endl
		<< "add station" << '\t' << "to add new station" << std::endl
		<< "has bus<bus number>" << '\t' << "check if there is a bus with a number <bus number>" << std::endl
		<< "has station" << '\t' << "check if there is a stop with a specific number" << std::endl
		<< "remove station" << '\t' << "to remove station" << std::endl
		<< "has direct path" << '\t' << "check if there is a bus from one station to another" << std::endl
		<< "print shortest path" << '\t' << "print the shortest route from one station to another" << std::endl
		<< "print schedule for station <number>" << '\t' << "shows the bus schedule for station with number <number>" << std::endl
		//<< "change route of bus <bus number>" << '\t' << "changes the route of the bus with a number <bus number>" << std::endl
		<< "add new course" << '\t' << "to add new course of bus" << std::endl
		<< "print buses for station<numberOfStation>" << '\t' << "print list of buses passing through a stop with a number <numberOfStation>" << std::endl << std::endl;
		
		
		
		//<< "add new course <bus number>" << '\t' << "to add new course of bus with number <number bus>" << std::endl
		
}

void Manager::addStation(BusStation& station)
{
	m_transport.addStation(station);
}

void Manager::removeStation(unsigned numberOfStation)
{
	m_transport.removeStation(numberOfStation);
}

bool Manager::hasStationWithNumber(unsigned numberOfStation)
{
	return m_transport.hasStationWithNumber(numberOfStation);
}

bool Manager::hasEdge(unsigned numberOfFirstStation, unsigned numberOfSecondStation)
{
	BusStation from = m_transport.getStation(numberOfFirstStation);
	BusStation to = m_transport.getStation(numberOfSecondStation);

	//Ако и двете станции съществуват
	//if (from.getNumberOfStation() != -1 && to.getNumberOfStation() != -1) {
		if (m_transport.hasEdge(from, to) == true) {
			std::cout << "There is a direct bus from station " << numberOfFirstStation << " to station " << numberOfSecondStation << "." << std::endl;
			return true;
		}
		else {
			std::cout << "There is no direct bus from station " << numberOfFirstStation << " to station " << numberOfSecondStation << "." << std::endl;
			return false;
		}
	//}
}

void Manager::printShortestPath(unsigned numberFromStation, unsigned numberToStation, unsigned startTime)
{
	if (hasStationWithNumber(numberFromStation) == false) {
		std::cout << "Station " << numberFromStation << " is not exist." << std::endl;
		return;
	}

	if (hasStationWithNumber(numberToStation) == false) {
		std::cout << "Station " << numberToStation << " is not exist." << std::endl;
		return;
	}

	BusStation busStationFrom = m_transport.getStation(numberFromStation);
	BusStation busStationTo = m_transport.getStation(numberToStation);

	m_transport.printTheShortestPath(busStationFrom, busStationTo, startTime);
}

void Manager::printListOfBuses(unsigned numberOfStation) const
{
	m_transport.printBusesOfStation(numberOfStation);
}

void Manager::printScheduleForStation(unsigned numberOfStation) const
{
	m_transport.printScheduleForStation(numberOfStation);
}

//void Manager::changeRouteOfBus(unsigned busNumber)
//{
//	m_transport.changeRouteOfBus(busNumber);
//}

void Manager::addNewBus(Bus& newBus)
{
	m_transport.addBus(newBus);
}
//
void Manager::addNewCourse(unsigned numBus)
{
	m_transport.addNewCourse(numBus);
}

//bool Manager::hasBus(unsigned numBus) const
//{
//	return m_transport.hasBusInNetwork(numBus);
//}

//void Manager::printStation() const
//{
//	m_transport.printStation();
//}

const bool Manager::hasBus(unsigned numBus) const
{
	return m_transport.hasBusInNetwork(numBus);
}

void Manager::runProgram()
{
	char command[MAX_LEN_COMMAND];

	for (;;) {
		std::cout << "Enter command: ";
		std::cin.getline(command, MAX_LEN_COMMAND);

		if (strcmp(command, "help") == 0) {
			help();
		}

		if (strcmp(command, "open") == 0) {
			char fileName[MAX_LEN_NAME_STATION];
			//std::cout << "file name: ";
			std::cout << "Please enter file name: ";

			std::cin.getline(fileName, MAX_LEN_NAME_STATION);

			//std::cout << "File name in function open is: " << fileName << std::endl;

			m_nameFile = new(std::nothrow) char[strlen(fileName) + 1];
			if (m_nameFile == nullptr) {
				std::cout << "Not enought memory for m_nameFile in open()." << std::endl;
			}
			strcpy(m_nameFile, fileName);

			open(fileName);
		}

		if (strcmp(command, "save") == 0) {
			//Проверка дали има успешно отворен файл, на който да е приложима операцията  save()
			if (isSuccessfullyOpenFile == true) {
				save();
			}
			else {
				std::cout << std::endl << "There is an unsuccessfully opened file." << std::endl << std::endl;
			}
		}

		if (strcmp(command, "saveas") == 0) {
			if (isSuccessfullyOpenFile == true) {
				char newNameFile[MAX_LEN_NAME_STATION];
				std::cin.getline(newNameFile, MAX_LEN_NAME_STATION);
				saveAs(newNameFile);
			}
			else {
				std::cout << std::endl << "There is an unsuccessfully opened file." << std::endl << std::endl;
			}
		}

		if (strcmp(command, "close") == 0) {
			if (isSuccessfullyOpenFile == true) {
				closeFile();
			}
			else {
				std::cout << std::endl << "There is an unsuccessfully opned file." << std::endl << std::endl;
			}
		}

		if (strcmp(command, "add station") == 0) {

			//Може би не трябва да има провека, за да може да се изгради изцяло нова мрежа
			if (isSuccessfullyOpenFile == true) {
				//Тъй като спирките са номерирани от 0 до N-1, то се предполага, че новодобавената спирка ще е с номер N.
				char name[MAX_LEN_NAME_STATION];
				unsigned stationNumber;

				std::cout << "You want to add new station. Please enter the station details." << std::endl;

				std::cout << "Station name: ";
				std::cin.getline(name, MAX_LEN_NAME_STATION);

				std::cout << "Station number: ";
				std::cin >> stationNumber;

				//Проверка дали вече такава станиция с този номер съществува
				if (m_transport.hasStationWithNumber(stationNumber) == true) {
					std::cout << "Station " << stationNumber << " is exist." << std::endl;
					continue;
				}
				BusStation station;

				
				//Ако е възможно номерът да е различен от N, проверката на ред 106 е излишна.
				//номерът на спирката трябва да е N. Проверка дали въведеният номер е равен на N, в случая m_countV.
				if (stationNumber == /*m_transport.getCountV()*/m_transport.biggestNumOfStation()+1) {//Най -големият номер на връх
					//Въвеждане на броя на автобусите, които ще преминават на новата спирка.
					std::cout << "Please enter how many buses will pass through the station: ";
					unsigned countBusesForStation;
					std::cin >> countBusesForStation;

					std::vector<Bus> buses;

					for (unsigned i = 0; i < countBusesForStation; ++i) {
						unsigned numberBus;
						std::cout << "Enter bus number: ";
						std::cin >> numberBus;
						unsigned numberOfPasses;

						//Проверка дали вече този автобус съществува в транспортната мрежа
						if (/*m_transport.hasBusInNetwork(stationNumber)*/hasBus(numberBus) == true) {
						//	std::cout << "Hasbus Inf " << std::endl;
							Schedule schedule;
							schedule.setNumberOfStation(stationNumber);
							//въвеждане данни за разпис
							std::cout << "Enter how many time in one day bus " << numberBus << " pass the station: ";
							std::cin >> numberOfPasses;
							unsigned time;
							unsigned beforeTime;
							std::cout << "Please enter the arrival time in ascending order." << std::endl;
							for (unsigned i = 0; i < numberOfPasses; ++i) {
								if (i == 0) {
									do {
										std::cout << "Arrival time: ";
										std::cin >> time;
									} while (time > MAX_MIN || time < 0);
									
									beforeTime = time;
									schedule.addNewArrivalTime(time);
									continue;
								}
								do {
									std::cout << "Arrival time: ";
									std::cin >> time;
								} while (beforeTime > time || time>MAX_MIN);
								beforeTime = time;
								schedule.addNewArrivalTime(time);
							}
							//Добавяме новия разпис към разписа за автобуса
							m_transport.addScheduleForBusInNetwork(numberBus, schedule);
							buses.push_back(m_transport.getBusFromTransport(numberBus));
						}
						else {
							Schedule schedule;
							schedule.setNumberOfStation(stationNumber);
							//въвеждане данни за разпис
							std::cout << "Enter how many time in one day bus " << numberBus << " pass the station: ";
							std::cin >> numberOfPasses;
							unsigned time;
							/*for (int i = 0; i < numberOfPasses; ++i) {
								std::cin >> time;
								schedule.addNewArrivalTime(time);
							}*/
							unsigned beforeTime;
							std::cout << "Please enter the arrival time in ascending order." << std::endl;
							for (unsigned i = 0; i < numberOfPasses; ++i) {
								if (i == 0) {
									do {
										std::cout << "Arrival time: ";
										std::cin >> time;
									} while (time > MAX_MIN || time < 0);

									beforeTime = time;
									schedule.addNewArrivalTime(time);
									continue;
								}
								do {
									std::cout << "Arrival time: ";
									std::cin >> time;
								} while (beforeTime > time || time > MAX_MIN);
								beforeTime = time;
								schedule.addNewArrivalTime(time);
							}
							Bus bus;
							bus.setNumber(numberBus);
							bus.addScheduleForStation(schedule);
							buses.push_back(bus);
						}
					}
					station.setNameStation(name);
					station.setNumberOfStattion(stationNumber);
					station.setListOfBuses(buses);

					//m_transport.addStation(station);
					int res= m_transport.addStationInRunProgram(station);
				}
				else {
					std::cout << "Invalid station number." << std::endl;
				}
			}
			else {
				std::cout << std::endl << "There is an unsuccessfully opened file." << std::endl << std::endl;
			}
		}

		if (strcmp(command, "add bus") == 0) {

			if (isSuccessfullyOpenFile == true) {
				std::cout << "You want to add a new bus. Please enter the number of bus: ";
				unsigned numberOfBus;
				std::vector<Schedule> scheduleForEachBusStation;
				//Валидация номерът на автобуса да не е на автобус от мрежата или ==0
				do {
					std::cin >> numberOfBus;
				} while (numberOfBus == 0 || m_transport.hasBusInNetwork(numberOfBus) == true);

				std::cout << "Please enter the count of stations on the bus route: ";
				unsigned countOfStation;
				std::cin >> countOfStation;

				unsigned* route = new(std::nothrow) unsigned[countOfStation];
				if (route == nullptr) {
					std::cout << "Not enought memory for route. The procedure for adding a new bus will be terminated." << std::endl;
					return;
				}

				std::cout << "Please enter the details of the bus stops in the order of passing through them." << std::endl;

				for (unsigned i = 0; i < countOfStation; ++i) {
					unsigned numberStation;
					//Валидация спирката вече да е час от транспортната мрежа
					do {
						std::cout << "Please enter station number: ";
						std::cin >> numberStation;
					} while (hasStationWithNumber(numberStation) == false);

					route[i] = numberStation;

					std::cout << "Please enter how many times the bus will pass through stop " << numberStation << " in ascending order: ";
					unsigned countTimes;
					std::cin >> countTimes;
					unsigned time;


					std::vector<unsigned> arrivalTime;

					for (unsigned j = 0; j < countTimes; ++j) {
						//Валидация да е във възходящ ред
						if (j == 0) {
							//валидация на времето
							do {
								std::cout << "Arrival time: ";
								std::cin >> time;
							} while (time > MAX_MIN || time < 0);

							arrivalTime.push_back(time);
						}
						else {
							do {
								std::cout << "Arrival time: ";
								std::cin >> time;

							} while (time < arrivalTime.at(j - 1) || time>MAX_MIN || time < 0);
							arrivalTime.push_back(time);
						}
					}
					Schedule tempSh(numberStation, arrivalTime);
					scheduleForEachBusStation.push_back(tempSh);
				}

				Bus newBus(numberOfBus, route, countOfStation, countOfStation, scheduleForEachBusStation);//помисли за друг по-добър начин за капацитета
				newBus.printRoute();
				addNewBus(newBus);
			}
			else {
				std::cout << std::endl << "There is an unsuccessfully opened file." << std::endl << std::endl;

			}
		}

		if (strcmp(command, "add new course") == 0) {
			if (isSuccessfullyOpenFile == true) {
				std::cout << "Please enter the bus number: ";
				unsigned busNumber;
				std::cin >> busNumber;

				if (hasBus(busNumber) == false) {
					std::cout << "Bus " << busNumber << " is not exist" << std::endl;
					continue;
				}

				addNewCourse(busNumber);
			}
			else {
				std::cout << std::endl << "There is an unsuccessfully opened file." << std::endl << std::endl;
			}
		}

		if (strcmp(command, "remove station") == 0) {
			if (isSuccessfullyOpenFile == true) {
				std::cout << "You want to remove station. Please enter station number: ";
				unsigned numberStation;
				std::cin >> numberStation;
				removeStation(numberStation);
			}
			else {
				std::cout << std::endl << "There is an unsuccessfully opened file." << std::endl << std::endl;
			}
		}

		if (strcmp(command, "has station") == 0) {
			if (isSuccessfullyOpenFile == true) {
				//Ще проверяваме само по номер на станция.
				std::cout << "Please enter station number: ";
				unsigned stationNumber;
				std::cin >> stationNumber;
				if (/*m_transport.hasStationWithNumber(stationNumber)*/hasStationWithNumber(stationNumber) == true) {
					std::cout << "Station " << stationNumber << " exsist." << std::endl;
				}
				else {
					std::cout << "Station " << stationNumber << " is not exsit." << std::endl;
				}
			}
			else {
				std::cout << std::endl << "There is an unsuccessfully opened file." << std::endl << std::endl;
			}
		}

		if (strcmp(command, "has direct path") == 0) {
			if (isSuccessfullyOpenFile == true) {
				std::cout << "Please, enter first the start station number and then the end station number: ";
				unsigned startStation, finalStation;
				std::cin >> startStation >> finalStation;
				hasEdge(startStation, finalStation);
			}
			else {
				std::cout << std::endl << "There is an unsuccessfully opened file." << std::endl << std::endl;
			}
		}

		if (strcmp(command, "print shortest path") == 0) {
			if (isSuccessfullyOpenFile == true) {
				std::cout << "Please, enter the start station number, the final station number and time to start from start station: ";
				unsigned startStation, finalStation, timeToStart;
				std::cin >> startStation >> finalStation >> timeToStart;
				printShortestPath(startStation, finalStation, timeToStart);
			}
			else {
				std::cout << std::endl << "There is an unsuccessfully opened file." << std::endl << std::endl;
			}
		}

		if (strcmp(command, "print buses for station") == 0) {
			if (isSuccessfullyOpenFile == true) {
				std::cout << "Please, enter station number: ";
				unsigned stationNumber;
				std::cin >> stationNumber;

				printListOfBuses(stationNumber);
			}
			else {
				std::cout << std::endl << "There is an unsuccessfully opened file." << std::endl << std::endl;

			}
		}

		if (strcmp(command, "print schedule for station") == 0) {
			if (isSuccessfullyOpenFile == true) {
				std::cout << "Please, enter station number: ";
				unsigned stationNumber;
				std::cin >> stationNumber;
				printScheduleForStation(stationNumber);
			}
			else {
				std::cout << std::endl << "There is an unsuccessfully opened file." << std::endl << std::endl;

			}
		}

		/*if (strcmp(command, "change route of bus") == 0) {
			if (isSuccessfullyOpenFile == true) {
				std::cout << "Please enter bus number: ";
				unsigned busNumber;
				std::cin >> busNumber;

				changeRouteOfBus(busNumber);
			}
			else {
				std::cout << std::endl << "There is an unsuccessfully opened file." << std::endl << std::endl;
			}
		}*/

		if (strcmp(command, "has bus") == 0) {
			if (isSuccessfullyOpenFile == true) {
				std::cout << "Please enter bus number: ";
				unsigned num;
				std::cin >> num;

				if (hasBus(num) == true) {
					std::cout << "Bus " << num << " exist." << std::endl;
				}
				else {
					std::cout << "Bus " << num << " is not exist." << std::endl;
				}
			}
			else {
				std::cout << std::endl << "There is an unsuccessfully opened file." << std::endl << std::endl;
			}
		}

		if (strcmp(command, "exit") == 0) {
			std::cout << "End of program" << std::endl;
			break;
			return;
		}

		/*if (strcmp(command, "print schedule for bus") == 0) {
			if (isSuccessfullyOpenFile == true) {
				unsigned num;
				std::cin >> num;
				m_transport.printShForBus(num);
			}
			else {

			}
			
		}*/
	}
}

//int Manager::printShForBus(unsigned numBus) const
//{
//	m_transport.printShForBus(numBus);
//	return -1;
//}
