#include <iostream>  // for debugging
//#include "LinkedList.h"
#include "spreader.h"
#include <climits>
using namespace std;

Person2::Person2(Person person){
  id = person.ID;
  peopleMet = new int[person.peopleMet];
  periods = new int[person.peopleMet];
  known = false;
  dayInfected = INT_MAX;
  countMet = person.peopleMet;
  for(int i = 0; i < person.peopleMet; i++){
    periods[i] = person.visitors[i].period;
    peopleMet[i] = person.visitors[i].ID;
  }
}

bool Person2::findDayInfected(int previous, int period){
	//if(known==false){
		//bool check=false;
		int temp=previous+3;
		//cout<< temp << endl;
		while(temp%period!=0){
			temp++;
		}
		if(temp<dayInfected){
			dayInfected=temp;
			return true;
		}
		else{
			return false;
		}
	//}
}

Spreader::Spreader(const Person *people, int population)
{
  // Students write this. 
  // Note that people will be deleted before simulate() is called.
  newPeople = new Person2*[population];
  for(int i=0; i<population; i++){
	newPeople[i] = new Person2(people[i]);
  }
  days=0;
  heap = BinaryHeap<Person2Ptr>(40000000);
} // Spreader()

void Spreader::becomingKnown(Person2* person){
	//cout<< "Hello" <<endl;
	//bool check=true;
	bool check2=true;
	if(person->known==false){
		//cout << "Called!"<<endl;
		/*for(int i=0; i<person->countMet; i++){
			if(newPeople[person->peopleMet[i]]->known==false){
				check=false;
				break;
			}
		}*/
		//if(check==false){
			//cout <<"Called 3!" <<endl;
			for(int i=0; i<person->countMet; i++){
				//cout << "Called 4" <<endl;
				if(newPeople[person->peopleMet[i]]->known==false){
					check2 = newPeople[person->peopleMet[i]]->findDayInfected(person->dayInfected, person->periods[i]);
					/*Person2Ptr* ptr = new Person2Ptr(newPeople[person->peopleMet[i]]);
					Person2Ptr temp = *ptr;
					heap.insert(temp);*/
					if(check2){
						heap.insert(Person2Ptr(newPeople[person->peopleMet[i]]));
					}
				}
			}
		//}
		//else{
			if(person->dayInfected>days && days != INT_MAX){
				days=person->dayInfected;
			}
		//}
		person->known=true;
	}
}

void Spreader::starterInfect(int starterIDs[], int starterCount){
  for(int i = 0; i < starterCount; i++){
  	//newPeople[starterIDs[i]]->known = true;
	newPeople[starterIDs[i]]->dayInfected = 0;
	becomingKnown(newPeople[starterIDs[i]]);
  }
}//starterInfect

int Spreader::simulate(int starterIDs[], int starterCount, int commandLineOption)
{
  int personID=0;
  Person2Ptr ptr;
  starterInfect(starterIDs, starterCount);
  /*for(int i = 0; i<20; i++){
	cout<< " ID: " << newPeople[i]->id << " Number: " << newPeople[i]->countMet;
	for(int j=0; j<newPeople[i]->countMet; j++){
		cout << " Person met: " << newPeople[i]->peopleMet[j] << " Period: " << newPeople[i]->periods[j];
	}
	cout << endl;
  }*/
  while(heap.isEmpty() == false){
	ptr = heap.findMin();
	personID=ptr.idPtr;
	becomingKnown(newPeople[personID]);
	heap.deleteMin();
  }
  // commandLineOption may be used to signal the program to do whatever the students 
  // want, or nothing at all.

  // Students write this.  Returns days until of last person catches the virus
  //cout<< "HI"<<endl;
  return days; // to avoid warnings for now.
}

