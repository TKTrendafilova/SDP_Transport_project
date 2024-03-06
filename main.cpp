#include<iostream>
#include "Bus.hpp"
#include "Tests.hpp"
#include "List.hpp"
#include "ManageTransport.hpp"

int main() {
	//testBus();
	//testList();
	//testSchedule();

	//testBusStation();
	//testHeap();

	//testTransport();


	//testFileWork();

	Schedule sh1;
	sh1.setNumberOfStation(0);
	sh1.addNewArrivalTime(120);
	sh1.addNewArrivalTime(130);
	sh1.addNewArrivalTime(140);
	sh1.addNewArrivalTime(150);
	sh1.addNewArrivalTime(160);

	Schedule sh2;
	sh2.setNumberOfStation(1);
	sh2.addNewArrivalTime(150);
	sh2.addNewArrivalTime(160);
	sh2.addNewArrivalTime(170);
	sh2.addNewArrivalTime(180);
	sh2.addNewArrivalTime(190);

	Schedule sh3;
	sh3.setNumberOfStation(2);
	sh3.addNewArrivalTime(230);
	sh3.addNewArrivalTime(240);
	sh3.addNewArrivalTime(250);
	sh3.addNewArrivalTime(260);
	sh3.addNewArrivalTime(270);

	std::vector<Schedule> schedules;
	schedules.push_back(sh1);
	schedules.push_back(sh2);
	schedules.push_back(sh3);

	unsigned* route = new (std::nothrow) unsigned[3];
	route[0] = 0;
	route[1] = 1;
	route[2] = 2;

	Bus bus1;
	bus1.setNumber(3);
	bus1.addScheduleForStation(sh1);
	bus1.addScheduleForStation(sh2);
	bus1.addScheduleForStation(sh3);

	//std::cout << "Before schedule: " << std::endl;
	//bus1.printScheduleForAllStations();
	//std::vector<Schedule> shV;
	//shV.push_back(sh1);

	//bus1.setScheduleForEachBusStation(shV);//ok

	//
	//bus1.printScheduleForAllStations();
	//bus1.printRoute();

	Schedule sh4;
	sh4.setNumberOfStation(3);
	sh4.addNewArrivalTime(320);
	sh4.addNewArrivalTime(323);
	sh4.addNewArrivalTime(326);
	sh4.addNewArrivalTime(329);
	sh4.addNewArrivalTime(331);

	Bus bus2 = bus1;
	bus2.setNumber(29);
	bus2.addNewStation(3);
	bus2.addScheduleForStation(sh4);

	std::vector<Bus> busVec;
	busVec.push_back(bus2);
	busVec.push_back(bus1);


	char* name = new char[strlen("Test Bus Station") + 1];
	strcpy(name, "Test Bus Station");
	
	BusStation busStation1(name, 0, busVec);
	
	BusStation busStation2(name, 1, busVec);

	BusStation busStation3(name, 2, busVec);

	busVec.pop_back();

	BusStation busStation4(name, 3, busVec);
	
	Transport tr(0, 0);
	tr.addStation(busStation1);
	tr.addStation(busStation2);
	tr.addStation(busStation3);
	tr.addStation(busStation4);

	tr.addEdge(busStation1, busStation2, bus1);
	tr.addEdge(busStation1, busStation2, bus2);

	tr.addEdge(busStation2, busStation3, bus1);
	tr.addEdge(busStation2, busStation3, bus2);

	tr.addEdge(busStation3, busStation4, bus2);


	std::ofstream ofs("Transport.bin", std::ios::out | std::ios::binary);
	tr.serializeTransport(ofs);//ok
	ofs.close();
	tr.printStation();
	tr.printScheduleForStation(0);
	std::cout << std::endl << std::endl << std::endl;
	tr.printScheduleForStation(3);
	
	Transport tr2(0,0);// m_countV= 0= m_countE
	std::ifstream ifs("Transport.bin", std::ios::in | std::ios::binary);
	tr2.deserializeTransport(ifs);//ok
	ifs.close();

	std::cout << "print after deserialize: " << std::endl;
	std::cout << tr2.getCountE() << " " << tr2.getCountV() << std::endl;
	std::cout << std::endl << std::endl;
	tr2.printStation();
	tr2.printScheduleForStation(0);
	std::cout << std::endl << std::endl << std::endl;

	tr2.printScheduleForStation(4);

	Manager m;
	m.runProgram();


	return 0;

}