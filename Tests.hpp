#ifndef __TEST_BUS_HPP
#define __TEST_BUS_HPP
#pragma warning(disable:4996)//Remove strcpy problem

#include<iostream>
#include<cstring>
#include"Bus.hpp"
#include"List.hpp"
#include"ScheduleForEachBusStop.hpp"
#include"BusStation.hpp"
#include"Transport.hpp"
//#include"Heap.hpp"

void testBus() {
	Schedule sh;
	sh.setNumberOfStation(1);
	//std::cout << "Scheduele for station: " << sh.getNumberOfStation() << std::endl;
	sh.addNewArrivalTime(12);
	sh.addNewArrivalTime(15);
	sh.addNewArrivalTime(30);

	Schedule sh1;
	sh1.setNumberOfStation(28);
	sh1.addNewArrivalTime(89);
	sh1.addNewArrivalTime(101);
	sh1.addNewArrivalTime(230);

	Schedule sh2;
	sh2.setNumberOfStation(3);
	sh2.addNewArrivalTime(8);
	sh2.addNewArrivalTime(10);
	sh2.addNewArrivalTime(23);

	std::vector<Schedule> schedules;
	schedules.push_back(sh);
	schedules.push_back(sh1);
	schedules.push_back(sh2);

	Bus bus1;

	std::cout << "Bus1 capacity: " << bus1.getCapacity() << std::endl; //getCapacity work
	bus1.addNewStation(1); //work
	bus1.addNewStation(2);
	bus1.addNewStation(3);
	bus1.addNewStation(25);
	bus1.addNewStation(7);
	bus1.addNewStation(15);
	bus1.addNewStation(17);
	bus1.addNewStation(78);
	bus1.addNewStation(14);
	bus1.addNewStation(29);
	bus1.addNewStation(31);
	bus1.addNewStation(5);
	bus1.addNewStation(28);
	bus1.addNewStation(25);
	bus1.addNewStation(101);
	bus1.addNewStation(55);
	bus1.addNewStation(57);
	bus1.addNewStation(21);
	bus1.setNumber(1);

	bus1.printRoute();
	std::cout << "Capacity of bus 1: " << bus1.getCapacity() << std::endl;

	std::cout << std::endl << "Count of station of bus 1: " << bus1.getCountOfStations() << std::endl;//work
	bus1.addScheduleForStation(sh);
	bus1.addScheduleForStation(sh1);
	bus1.addScheduleForStation(sh2);

	std::cout << "print info for station 1: " << std::endl;
	bus1.printScheduleForStation(1);
	bus1.printScheduleForStation(28);
	bus1.printScheduleForStation(3);
	
	//Тествай конемтираните части след вече добовените разписи за всяко спирка.
	//Test copy constr.   //It's OK
	Bus bus2 = bus1;
	bus2.setNumber(2);
	std::cout << "Bus 2 Number is: " << bus2.getNumberOfBus() << std::endl
		<< "Bus2 capacity is: " << bus2.getCapacity() << std::endl;
	bus2.printRoute();
	std::cout << std::endl << std::endl << std::endl;

	//Test operator=     // It's OK
	Bus bus3;
	bus3 = bus1;
	bus3.setNumber(3);
	std::cout << "Bus 3 Number is: " << bus3.getNumberOfBus() << std::endl
		<< "Bus3 capacity is: " << bus3.getCapacity() << std::endl;
	bus3.printRoute();

	Schedule schBus1 = bus1.getScheduleForStation(1);//work
	std::cout << "get schedule for station" << std::endl;

	schBus1.printSchedule();

	std::cout << std::endl << "bus1 route: " << std::endl;
	bus1.printRoute();
	std::cout << std::endl;


	//it's ok
	bus1.removeStation(14);
	std::cout << "After remove 14 of bus1: "<<bus1.getCountOfStations() << std::endl;
	bus1.printRoute();

	bus1.removeStation(25);
	std::cout << "After remove 25 of bus1: " << bus1.getCountOfStations() << std::endl;
	bus1.printRoute();

	bus1.removeStation(101);
	std::cout << "After remove 101 of bus1: " << bus1.getCountOfStations() << std::endl;
	bus1.printRoute();

	bus1.removeStation(57);
	std::cout << "After remove 57 of bus1: " << bus1.getCountOfStations() << std::endl;
	bus1.printRoute();

	bus1.removeStation(78);
	std::cout << "After remove 78 of bus1: " << bus1.getCountOfStations() << std::endl;
	bus1.printRoute();

	bus1.removeStation(1);
	std::cout << "After remove 1 of bus1: " << bus1.getCountOfStations() << std::endl;
	bus1.printRoute();
	bus1.printScheduleForAllStations();
	bus1.printScheduleForStation(1);

	//Test setSchedule
	//OKKKK
	std::cout << "BEfor setSchedule: " << std::endl;
	bus1.printScheduleForAllStations();
	std::vector<Schedule> shNEw;
	shNEw.push_back(sh);
	shNEw.push_back(sh2);
	bus1.setScheduleForEachBusStation(shNEw);
	std::cout << "AFTER SETSCHEDULE: " << std::endl;
	bus1.printScheduleForAllStations();

	Bus busWrite;
	busWrite.setNumber(2000);
	busWrite.addScheduleForStation(sh);
	busWrite.addScheduleForStation(sh1);
	busWrite.addScheduleForStation(sh2);

	std::cout << "Before write to file: " << busWrite.getNumberOfBus() << " " << busWrite.getCountOfStations() << " " << busWrite.getCapacity() << std::endl;
	busWrite.printRoute();
	busWrite.printScheduleForAllStations();

	std::ofstream ofs("Bus.bin", std::ios::out | std::ios::binary);
	busWrite.serializeBus(ofs);
	ofs.close();

	std::ifstream ifs("Bus.bin", std::ios::in | std::ios::binary);
	Bus busRead;
	busRead.deserializeBus(ifs);
	ifs.close();

	std::cout << "After read: " << busRead.getNumberOfBus() << " " << busRead.getCountOfStations() << " " << busRead.getCapacity() << std::endl;
	busRead.printRoute();
	busRead.printScheduleForAllStations();

}

void testList() {
	//List is OK
	List<int> list;

	for (int i = 0; i < 10; ++i) {
		list.push_back(i);
	}

	std::cout << "Elements of list: ";
	for (int i = 0; i < 10; ++i) {
		std::cout << list.getAt(i) << " ";
	}
	std::cout << std::endl;

	std::cout << "Front: " << list.getFront() << std::endl
		<< "Back: " << list.getBack() << std::endl
		<< "At 3: " << list.getAt(3) << std::endl;

	list.pop_front();

	std::cout << "After pop_front: " << list.getFront() << std::endl;

	list.pop_back();
	std::cout << "After pop_back: " << list.getBack() << std::endl;

	std::cout << "getAt(5): " << list.getAt(5) << std::endl;
	list.insert(101, 5);
	std::cout << "list.insert(101, 5): " << list.getAt(6) << std::endl;

	list.push_front(11);
	std::cout << "list.push_front(11): " << list.getFront() << std::endl;

	list.push_back(99);
	std::cout << "list.push_back(99): " << list.getBack() << std::endl;

	std::cout << "List of pos 7: " << list.getAt(7) << std::endl;
	list.remove(7);
	std::cout << "list.remove(7): " << list.getAt(7) << std::endl;
}

//void testHeap() {
//	Heap<int> testHeap;
//
//	testHeap.push(7);
//	testHeap.push(1);
//	testHeap.push(3);
//
//	std::cout << "Size of heap:  " << testHeap.size() << std::endl;
//
//	std::cout << std::endl;
//
//	std::cout << "Top: " << testHeap.top() << std::endl;
//
//	testHeap.pop();
//
//	std::cout << std::endl << "After pop, top is: " << testHeap.top() << std::endl;
//	testHeap.pop();
//	//Ще остане само 7 след втория  pop
//
//	/*std::cout << std::endl << "Print elements: " << std::endl;
//	for (; !testHeap.empty(); testHeap.pop()) {
//		std::cout << testHeap.top() << " ";
//	}
//	std::cout << std::endl;*/
//
//	std::cout << std::endl;
//
//	testHeap.push(5);
//	testHeap.push(4);
//	testHeap.push(29);
//	testHeap.push(31);
//
//	std::cout << "After push, size is:  " << testHeap.size() << std::endl;
//
//	std::cout << std::endl << "Print elements: " << std::endl;
//	for (; !testHeap.empty(); testHeap.pop()) {
//		std::cout << testHeap.top() << " ";
//	}
//	std::cout << std::endl;
//}

void testSchedule(){//ok
	Schedule sh;
	std::cout << "Scheduele for station: " << sh.getNumberOfStation() << std::endl;
	sh.addNewArrivalTime(12);
	sh.addNewArrivalTime(15);
	sh.addNewArrivalTime(30); 
	sh.addNewArrivalTime(60); 
	sh.addNewArrivalTime(70); 
	sh.addNewArrivalTime(79); 
	sh.addNewArrivalTime(87);
	sh.addNewArrivalTime(99);

	sh.printSchedule();
	std::cout << "Time in index 7: " << sh.getArrivalTimeOfIndex(7) << std::endl;
	std::cout << "Time in index 1: " << sh.getArrivalTimeOfIndex(1) << std::endl;
	std::cout << "Time in index 5: " << sh.getArrivalTimeOfIndex(5) << std::endl;

	Schedule sh2 = sh;
	std::cout << sh2.getNumberOfStation()<< std::endl;
	std::cout << sh2.getArrivalTimeOfIndex(7) << std::endl;
	sh2.printSchedule();
	sh2.setNumberOfStation(2);
	std::cout << "number st of sh2: " << sh2.getNumberOfStation()<<std::endl;
	sh2.addNewArrivalTime(101);
	sh2.printSchedule();

	Schedule sh3;
	sh3 = sh2;
	std::cout << "Print info of sh3" << std::endl;
	sh3.printSchedule();

	std::cout << "Before write to file: "<<sh.getNumberOfStation() << std::endl;
	sh.printSchedule();
	

	std::ofstream ofs("Schedule.bin", std::ios::out | std::ios::binary);
	sh.serializeSchedule(ofs);
	ofs.close();

	std::ifstream ifs("Schedule.bin", std::ios::in | std::ios::binary);
	Schedule schdeuleRead;
	schdeuleRead.deserializeSchedule(ifs);
	ifs.close();
	std::cout << "After read file: "<<schdeuleRead.getNumberOfStation() << std::endl;
	schdeuleRead.printSchedule();
}

void testBusStation() {
	Schedule sh;
	sh.setNumberOfStation(1);
	//std::cout << "Scheduele for station: " << sh.getNumberOfStation() << std::endl;
	sh.addNewArrivalTime(12);
	sh.addNewArrivalTime(15);
	sh.addNewArrivalTime(30);

	Schedule sh1;
	sh1.setNumberOfStation(28);
	sh1.addNewArrivalTime(89);
	sh1.addNewArrivalTime(101);
	sh1.addNewArrivalTime(230);

	Schedule sh2;
	sh2.setNumberOfStation(3);
	sh2.addNewArrivalTime(8);
	sh2.addNewArrivalTime(10);
	sh2.addNewArrivalTime(23);

	std::vector<Schedule> schedules;
	schedules.push_back(sh);
	schedules.push_back(sh1);
	schedules.push_back(sh2);

	unsigned* route = new (std::nothrow) unsigned[3];
	route[0] = 1;
	route[1] = 28;
	route[2] = 3;

	Bus bus1;

	bus1.addScheduleForStation(sh);
	bus1.addScheduleForStation(sh1);
	bus1.addScheduleForStation(sh2);

	bus1.printScheduleForStation(3);
	bus1.printScheduleForStation(2);
	bus1.printScheduleForStation(28);

	bus1.printScheduleForAllStations();


	Bus bus2 = bus1;
	bus2.setNumber(29);
	std::cout << "Bus number: " << bus2.getNumberOfBus() << std::endl;
	bus2.printScheduleForAllStations();

	Schedule sh3;
	sh3.setNumberOfStation(7);
	sh3.addNewArrivalTime(280);
	sh3.addNewArrivalTime(300);
	sh3.addNewArrivalTime(360);

	bus2.addScheduleForStation(sh3);

	bus2.printScheduleForAllStations();


	//bus2.addNewStation(14);
	//std::cout << std::endl << std::endl << std::endl;

	//bus2.printScheduleForAllStations();
	
	std::vector<Bus> busVec;
	busVec.push_back(bus1);
	busVec.push_back(bus2);

	char* name = new char[strlen("Test Bus Station") + 1];
	strcpy(name, "Test Bus Station");
	//std::cout << "name: " << name << std::endl;
	BusStation busStation(name, 1, busVec);
	std::cout << "Bus station name: " << busStation.getName() << std::endl
		<< busStation.getNumberOfStation() << std::endl;

	busStation.showScheduleOfBuses();

	std::cout << std::endl << std::endl;

	Bus bus5;
	bus5.setNumber(5);
	bus5.addScheduleForStation(sh3);

	//05.08.2021
	//To test setListOfBuses. It's ok!
	/*std::vector<Bus> newBuses;
	newBuses.push_back(bus1);
	newBuses.push_back(bus5);
	newBuses.push_back(bus2);

	std::cout << "BEFORE SET LIST OF BUSES: " << std::endl;
	busStation.showScheduleOfBuses();

	busStation.setListOfBuses(newBuses);
	std::cout << "AFTER SET LIST OF BUSES: " << std::endl;
	std::cout << "passed a bus: " << busStation.passedABusWithANumber(5) << std::endl;*/

	busStation.addNewBus(bus5);
	busStation.showScheduleOfBuses();

	/*std::cout << "Remove bus1" << std::endl;
	busStation.removeBus(1);*/

	busStation.setNumberOfStattion(7);
	std::cout << "Bus station number " << busStation.getNumberOfStation() << std::endl;
	std::cout << "bus1 hasVisit(28): ";
	if (bus1.hasVisitStation(28) == true)
		std::cout << "true" << std::endl;
	else std::cout << "false" << std::endl;

	//ok
	std::cout << "bus1 hasVisit(29): " << bus1.hasVisitStation(29) << std::endl;
	std::cout << "Bus1 hasVisit(1): " << bus1.hasVisitStation(1) << std::endl;
	std::cout << "Bus1 hasVisit(3): " << bus1.hasVisitStation(3) << std::endl;
	bus1.printRoute();
	

	//ok
	std::cout << "Bus station passedABus(1): " << busStation.passedABusWithANumber(1) << std::endl
		<< "Bus station passedABus(29): " << busStation.passedABusWithANumber(29) << std::endl
		<< "Bus stattion passedABus(101): " << busStation.passedABusWithANumber(101) << std::endl
		<< "Bus stattion passedABus(0): " << busStation.passedABusWithANumber(0) << std::endl

		<< "Bus sation passedABus(3): " << busStation.passedABusWithANumber(3) << std::endl;

	//Test copy-constructor- ok
	BusStation busStation2 = busStation;
	busStation2.setNumberOfStattion(2);

	std::cout << "after change number of station 2: " << busStation2.getNumberOfStation() << std::endl;

	//Test getListOfBuses-OK
	std::vector<Bus> buses;
	buses = busStation2.getListOfBuses();

	int size = buses.size();
	std::cout << "After get list of Buses: " << std::endl;
	for (int i = 0; i < size; ++i) {
		std::cout << buses.at(i).getNumberOfBus() << " ";
	}
	std::cout << std::endl;

	std::cout << "Print busStation list of buses" << std::endl;
	for (int i = 0; i < busStation.getListOfBuses().size(); ++i) {
		std::cout << busStation.getListOfBuses().at(i).getNumberOfBus() << " ";
	}

	std::cout << std::endl << std::endl;

	//is ok
	busStation.removeBus(29);

	std::cout << "Print busStation list of buses" << std::endl;
	for (int i = 0; i < busStation.getListOfBuses().size(); ++i) {
		std::cout << busStation.getListOfBuses().at(i).getNumberOfBus() << " ";
	}
	std::cout << std::endl;

	busStation.removeBus(0);
	std::cout << "Print busStation list of buses" << std::endl;
	for (int i = 0; i < busStation.getListOfBuses().size(); ++i) {
		std::cout << busStation.getListOfBuses().at(i).getNumberOfBus() << " ";
	}
	std::cout << std::endl;

	busStation.removeBus(5);
	std::cout << "Print busStation list of buses" << std::endl;
	for (int i = 0; i < busStation.getListOfBuses().size(); ++i) {
		std::cout << busStation.getListOfBuses().at(i).getNumberOfBus() << " ";
	}
	std::cout << std::endl;

}

//void testHeap() {
//	eap<int> pq;
//
//	pq.push(3);
//	pq.push(2);
//	pq.push(15);
//
//	cout << "Size is " << pq.size() << endl;
//	cout << pq.top() << " ";
//	pq.pop();
//
//	cout << pq.top() << " ";
//	pq.pop();
//
//	pq.push(5);
//	pq.push(4);
//	pq.push(45);
//
//	cout << endl << "Size is " << pq.size() << endl;
//	for (; !pq.empty(); pq.pop()) {
//		cout << pq.top() << " ";
//	}
//}

void testTransport() {
	Schedule sh1;
	sh1.setNumberOfStation(0);
	sh1.addNewArrivalTime(110);
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

	Schedule sh4;
	sh4.setNumberOfStation(3);
	sh4.addNewArrivalTime(320);
	sh4.addNewArrivalTime(323);
	sh4.addNewArrivalTime(326);
	sh4.addNewArrivalTime(329);
	sh4.addNewArrivalTime(331);

	Bus bus2 = bus1;
	/*Schedule sh12;
	sh12.setNumberOfStation(0);
	sh12.addNewArrivalTime(120);
	sh12.addNewArrivalTime(130);
	sh12.addNewArrivalTime(140);
	sh12.addNewArrivalTime(150);
	sh12.addNewArrivalTime(160);

	std::vector<Schedule> scheduleB2;
	scheduleB2.push_back(sh12);
	scheduleB2.push_back(sh2);
	scheduleB2.push_back(sh3);
	scheduleB2.push_back(sh4);

	bus2.setScheduleForEachBusStation(scheduleB2);
	std::cout << "After setschedule bus2" << std::endl;
	bus2.printScheduleForAllStations();
	bus1.printScheduleForAllStations();*/

	bus2.setNumber(29);
	bus2.addNewStation(3);
	bus2.addScheduleForStation(sh4);

	std::vector<Bus> busVec;
	busVec.push_back(bus2);
	busVec.push_back(bus1);
	

	char* name = new char[strlen("Test Bus Station") + 1];
	strcpy(name, "Test Bus Station");
	//std::cout << "name: " << name << std::endl;
	//BusStation busStation(name, 1, busVec);

	BusStation busStation1(name, 0, busVec);
	//std::cout << "BUSSTATION1 BUSES: ";
	//for (int i = 0; i < busVec.size(); ++i) {
	//	std::cout << busVec.at(i).getNumberOfBus() << " ";
	//}
	//busStation1.setNumberOfStattion(0);
	//busStation1.addNewBus(bus1);
	//busStation1.addNewBus(bus2);

	BusStation busStation2(name,1, busVec);
	//busStation2.setNumberOfStattion(1);
	//busStation2.addNewBus(bus1);
	//busStation2.addNewBus(bus2);

	BusStation busStation3(name,2,busVec);
	/*busStation3.setNumberOfStattion(2);
	busStation3.addNewBus(bus1);
	busStation3.addNewBus(bus2);*/

	busVec.pop_back();

	BusStation busStation4(name,3,busVec);
	/*busStation4.setNumberOfStattion(3);
	busStation4.addNewBus(bus2);*/

	Transport tr(0, 0);
	tr.addStation(busStation1);
	tr.addStation(busStation2);
	tr.addStation(busStation3);
	tr.addStation(busStation4);

	std::cout << "Has station 0: " << tr.hasStationWithNumber(0) << std::endl;
	std::cout << "Has station 1: " << tr.hasStationWithNumber(1) << std::endl;
	std::cout << "Has station 2: " << tr.hasStationWithNumber(2) << std::endl;
	std::cout << "Has station 3: " << tr.hasStationWithNumber(3) << std::endl;
	std::cout << "Has station 5: " << tr.hasStationWithNumber(5) << std::endl;

	std::cout << std::endl;

	std::cout << "Station 0 cntBus: " << busStation1.getListOfBuses().size() << std::endl;
	std::cout << "Station 1 cntBus: " << busStation2.getListOfBuses().size() << std::endl;
	std::cout << "Station 2 cntBus: " << busStation3.getListOfBuses().size() << std::endl;
	std::cout << "Station 3 cntBus: " << busStation4.getListOfBuses().size() << std::endl;

	std::cout << "Station 3/4 bus: " << busStation4.getListOfBuses().front().getNumberOfBus() << std::endl;

	tr.addEdge(busStation1, busStation2, bus1);
	tr.addEdge(busStation1, busStation2, bus2);

	tr.addEdge(busStation2, busStation3, bus1);
	tr.addEdge(busStation2, busStation3, bus2);

	tr.addEdge(busStation3, busStation4, bus2);

	std::cout << "getCountV: " << tr.getCountV() << std::endl
		<< "getCountE: " << tr.getCountE() << std::endl;

	std::cout << "countEdges 0: " << tr.countEdges(0) << std::endl;
	std::cout << "countEdges 1: " << tr.countEdges(1) << std::endl;
	std::cout << "countEdges 2: " << tr.countEdges(2) << std::endl;
	std::cout << "countEdges 3: " << tr.countEdges(3) << std::endl;


	std::cout << "..................................................................................." << std::endl;
	std::cout << "Has edge1(0,1): " << tr.hasEdgeWithBus(busStation1, busStation2, 3)<<std::endl;
	std::cout << "Has edge1(0,1): " << tr.hasEdgeWithBus(busStation1, busStation2, 1) << std::endl;

	std::cout << "Has edge1(1,2): " << tr.hasEdgeWithBus(busStation2, busStation3,29)<<std::endl;
	std::cout << "Has edge1(2,3): " << tr.hasEdgeWithBus(busStation3, busStation4, 29) << std::endl; 
	std::cout << "Has edge1(2,3): " << tr.hasEdgeWithBus(busStation3, busStation4, 23) << std::endl;

	std::cout << "Has edge1(0,3): " << tr.hasEdgeWithBus(busStation1, busStation4, 29) << std::endl;
	//TODO:Помисили как да оправиш грешките при hasEdge между два несъседни върха и когато е подаден номер на 
	//     автобус, който не е свързва двете станции
	std::cout << "after" << std::endl;
	std::cout << "Has edge(0,1): " << tr.hasEdge(busStation1, busStation2) << std::endl;
	std::cout << "Has edge(1,2): " << tr.hasEdge(busStation2, busStation3) << std::endl;
	std::cout << "Has edge(2,3): " << tr.hasEdge(busStation3, busStation4) << std::endl;
	std::cout << "Has edge(0,3): " << tr.hasEdge(busStation1, busStation4) << std::endl;

	

	

	std::cout<<"min time to reach: "<<tr.minTimeToReachBusStation(busStation1, busStation2, 110)<<std::endl;//работи. Измисли по-хубави разписи, за да дава различна стойност от тази на времето за изчакване
	std::cout << "min time to reach: " << tr.minTimeToReachBusStation(busStation1, busStation3, 120) << std::endl;
	std::cout << "min time to reach: " << tr.minTimeToReachBusStation(busStation1, busStation4, 120) << std::endl;
	std::cout << "min time to reach: " << tr.minTimeToReachBusStation(busStation2, busStation4, 120) << std::endl;

	std::cout << "min time to reach: " << tr.minTimeToReachBusStation(busStation1, busStation2, 165) << std::endl;
	std::cout << "min time to reach: " << tr.minTimeToReachBusStation(busStation2, busStation3, 140) << std::endl;
	std::cout << "min time to reach: " << tr.minTimeToReachBusStation(busStation3, busStation4, 180) << std::endl;

	
	//tr.printBusesOfStation(7);
	

	tr.printTheShortestPath(busStation1, busStation4, 110);
	tr.printTheShortestPath(busStation1, busStation2, 110);
	tr.printTheShortestPath(busStation3, busStation4, 180);
	//tr.printTheShortestPath(busStation1, busStation2, 165);

	//ok
	std::cout << std::endl;
	BusStation b1 = tr.getStation(0);
	std::cout << b1.getNumberOfStation() << std::endl;

	BusStation b2=tr.getStation(7);
	std::cout << "end" << std::endl;

	tr.printStation();
	std::cout << "remove 2" << std::endl;
	tr.removeStation(2);
	tr.printStation();
	tr.printScheduleForStation(0);
	tr.printScheduleForStation(1);
	tr.printScheduleForStation(2);
	tr.printScheduleForStation(3);



	std::cout << "remove 9" << std::endl;
	tr.removeStation(9);
	tr.printStation();

	std::cout << "remove 3" << std::endl;
	tr.removeStation(3);
	tr.printStation();

	//ok
	std::cout << "Has bus 29; " << tr.hasBusInNetwork(29) << std::endl;
	std::cout << "Has bus 87: " << tr.hasBusInNetwork(87) << std::endl;
	std::cout << "Has bus 3: " << tr.hasBusInNetwork(3) << std::endl;
	std::cout << "Has bus 15: " << tr.hasBusInNetwork(15) << std::endl;

	//Това не работи, може би не ни и трябва.
	/*std::cout << std::endl;
	std::cout << "Bus min time to reach: " << tr.numberBusWithMinTimeToReachBusStation(busStation1, busStation2, 110) << std::endl;
	std::cout << "Bus min time to reach: " << tr.numberBusWithMinTimeToReachBusStation(busStation1, busStation2, 120) << std::endl;
	std::cout << "Bus min time to reach: " << tr.numberBusWithMinTimeToReachBusStation(busStation1, busStation2, 165) << std::endl;*/


}

void testFileWork() {
	Schedule sh;
	sh.setNumberOfStation(1);
	sh.addNewArrivalTime(12);
	sh.addNewArrivalTime(15);
	sh.addNewArrivalTime(30);

	Schedule sh1;
	sh1.setNumberOfStation(28);
	sh1.addNewArrivalTime(89);
	sh1.addNewArrivalTime(101);
	sh1.addNewArrivalTime(230);


	std::vector<Schedule> schedules;
	schedules.push_back(sh);
	schedules.push_back(sh1);


	Bus bus1;
	std::ofstream ofs1("Schedule1.bin", std::ios::out | std::ios::binary);
	sh1.serializeSchedule(ofs1);//ok
	ofs1.close();

	std::ifstream ifs1("Schedule1.bin", std::ios::in | std::ios::binary);

	Schedule scheduleRead;
	scheduleRead.deserializeSchedule(ifs1);//ok
	scheduleRead.printSchedule();
	ifs1.close();

	bus1.addScheduleForStation(sh);
	bus1.addScheduleForStation(sh1);

	bus1.printRoute();
	std::cout << std::endl;
	bus1.printScheduleForAllStations();
	std::cout << std::endl;

	std::ofstream ofsBus("Bus1.bin", std::ios::out | std::ios::binary);
	bus1.serializeBus(ofsBus);//ok
	ofsBus.close();


	std::cout << "before deserialize" << std::endl;
	Bus bus2;
	std::ifstream ifsBus("Bus1.bin", std::ios::in | std::ios::binary);//ok
	bus2.deserializeBus(ifsBus);
	ifsBus.close();

	std::cout << "Bus 2 print: " << std::endl;
	bus2.setNumber(2);
	bus2.printRoute();
	bus2.printScheduleForStation(28);
	bus2.printScheduleForAllStations();

	std::vector<Bus> busVec;
	busVec.push_back(bus1);
	busVec.push_back(bus2);

	char* name = new char[strlen("Test Bus Station") + 1];
	strcpy(name, "Test Bus Station");
	//std::cout << "name: " << name << std::endl;
	BusStation busStation(name, 1, busVec);
	std::cout << "Bus station name: " << busStation.getName() << std::endl
		<< busStation.getNumberOfStation() << std::endl;

	std::ofstream ofsBS("BusStation.bin", std::ios::out | std::ios::binary);
	busStation.serializeBusStation(ofsBS);//ok
	ofsBS.close();

	std::ifstream ifsBS("BusStation.bin", std::ios::in | std::ios::binary);
	BusStation busStation2;
	busStation2.deserializeBusStation(ifsBS);//ok
	ifsBS.close();

	busStation2.setNumberOfStattion(2);
	std::vector<Bus>buses = busStation2.getListOfBuses();
	int size = buses.size();

	std::cout << "BS2 number: " << busStation2.getNumberOfStation() << std::endl;
	for (int i = 0; i < size; ++i) {
		buses.at(i).printScheduleForAllStations();
		std::cout << "--------------------------------" << std::endl;
	}
}

#endif
