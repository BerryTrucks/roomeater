/*
 * NaiveMinimalSolutionFinder.cpp
 *
 *  Created on: 9 lis 2015
 *      Author: Kamil
 */

#include <src/solution/NaiveMinimalSolutionFinder.h>

NaiveMinimalSolutionFinder::NaiveMinimalSolutionFinder(QObject *parent)
{
    // TODO Auto-generated constructor stub
}

NaiveMinimalSolutionFinder::~NaiveMinimalSolutionFinder()
{
    // TODO Auto-generated destructor stub
}

void NaiveMinimalSolutionFinder::findSolution(const QList<Group*>& groups,
        const QList<Room*>& rooms)
{
    int ** wages = new int*[groups.length()];
    for (int i = 0; i < groups.length(); i++){
        wages[i] = new int[rooms.length()];
    }

    int foundMinVal = 1000000, associatedIndex = 0;
    bool validAssign = false;
    for (int i = groups.length() - 1; i >= 0; i--){
        for (int j = 0; j < rooms.length(); j++){
            qDebug() << "i = " << i << " j = " << j << " maxVal = " << foundMinVal << endl;
            int wage = groups.at(i)->getValue() * rooms.at(j)->getValue();
            qDebug() << "Waga = " << wage << endl;
            wages[i][j] = wage;
            if (wages[i][j] < foundMinVal){
                if(rooms.at(j)->getGender() != NOT_SET){
                    if (rooms.at(j)->getGender() == groups.at(i)->getGender()){
                        if (rooms.at(j)->getPeopleInRoom() + groups.at(i)->getNumberOfPeople() <= rooms.at(j)->getCapacity()){
                            foundMinVal = wages[i][j];
                            associatedIndex = j;
                            validAssign = true;
                            qDebug() << "Found possible solution with value " << foundMinVal << endl;
                        }else{
                            qDebug() << QString("Room = (%1/%2). People in group = %3").arg(rooms.at(j)->getPeopleInRoom()).arg(rooms.at(j)->getCapacity()).arg(groups.at(i)->getNumberOfPeople()) << endl;
                        }
                    }else{
                        qDebug() << QString("Room gender = %1, group gender = %2").arg(rooms.at(j)->getGender()).arg(groups.at(i)->getGender()) << endl;
                    }
                }else{
                    if (rooms.at(j)->getPeopleInRoom() + groups.at(i)->getNumberOfPeople() <= rooms.at(j)->getCapacity()){
                        foundMinVal = wages[i][j];
                        associatedIndex = j;
                        validAssign = true;
                        qDebug() << "Found possible solution with value " << foundMinVal << endl;
                    }else{
                        qDebug() << QString("Room = (%1/%2). People in group = %3").arg(rooms.at(j)->getPeopleInRoom()).arg(rooms.at(j)->getCapacity()).arg(groups.at(i)->getNumberOfPeople()) << endl;
                    }
                }
            }
        }
        if (validAssign){
            groups.at(i)->setRoom((*rooms.at(associatedIndex)));
            qDebug() << QString("%1 get room nr %2 on %3 floor").arg(groups.at(i)->getNames()).arg(rooms.at(associatedIndex)->getNumber()).arg(rooms.at(associatedIndex)->getFloor());
            validAssign = false;
            associatedIndex = -1;
            foundMinVal = 1000000;
        }
    }
    /*
     * dla każdej osoby iterujemy po pokojach (startujemy od końca listy)
     * sprawdzamy czy w pokoju juz jest jakas płeć i czy pasujemy -> jak nie to nastepny pokoj
     * sprawdzamy czy po wlozeniu osoby do pokoju nie przekroczymy limitu -> jak tak to nastepny pokoj
     * wybieramy najniższą wartosć i przypisujemy osobe do pokoju i pokoj do osoby
     * jak pokoj nie mial plci to ustawiamy, i dostosowywujemy ilosc osob w pokoju (moze we wczesniejszym kroku)
     */
    qDebug()<< "Problem solved." << endl;
}
