#ifndef SPREADER_H
#define SPREADER_H

#include "spreaderRunner.h"
#include "QuadraticProbing.h"
#include "BinaryHeap.h"

//class Person2;



class Person2{
  public:
    Person2();
    Person2(Person person);
    Person2(int x){id = x;}
    int id;
    int countMet;
    int* peopleMet;
    int* periods;
    bool known;
    int dayInfected;
    bool findDayInfected(int previous, int period);
    
  private:

};

//const int MAX_POP = 2500001;
//Person2 BAD = Person2(-1);

/*class TableInfo{
  public:
  Person2 person;
  int daysTillInfected; //dv
  bool known; //always initially false

 
  int findDV(int prevDV, int period){
    int temp = 0;
    
    while((prevDV + 3 + temp)%period != 0){
      temp++;
    }

    if(prevDV + 3 + temp < daysTillInfected){
      daysTillInfected = prevDV + 3 + temp;
    }
    return 0;
  }//findDV
};*/

class Person2Ptr{
  public:
  Person2Ptr(const Person2* person){
    //cout<<"Id: " << person->id <<endl;
    idPtr = person->id;
    dayInfectedPtr = person->dayInfected;
  }
  Person2Ptr(){}
  bool operator<(const Person2Ptr& rhs) const{
    return(dayInfectedPtr < rhs.dayInfectedPtr);
  }

  int idPtr;
  int dayInfectedPtr;
};

class Spreader
{
	public:
		int days;
  		Person2** newPeople;
  		Spreader(const Person *people, int population);
  		int simulate(int starterIDs[], int starterCount, int commandLineOption);
  		void starterInfect(int* starterIDs, int starterCount);
    		void becomingKnown(Person2* person);
		BinaryHeap<Person2Ptr> heap;

  //data members
  //QuadraticHashTable <int> hashTable = QuadraticHashTable<int>(-1, 1000);
  //QuadraticHashTable<Person2> table = QuadraticHashTable<Person2>(BAD, MAX_POP);
  //BinaryHeap <Person2> heap = BinaryHeap<Person2>(MAX_POP);
};

#endif /* SPREADER_H */

