/*
 * NaiveCouplesTogetherSolutionFinder.cpp
 *
 *  Created on: 10 lis 2015
 *      Author: Kamil
 */

#include <src/solution/NaiveCouplesTogetherSolutionFinder.h>

NaiveCouplesTogetherSolutionFinder::NaiveCouplesTogetherSolutionFinder(QObject *parent)
{
    // TODO Auto-generated constructor stub
}

NaiveCouplesTogetherSolutionFinder::~NaiveCouplesTogetherSolutionFinder()
{
    // TODO Auto-generated destructor stub
}

void NaiveCouplesTogetherSolutionFinder::findSolution(const QList<Group*>& groups,
        const QList<Room*>& rooms)
{
    int ** wages = new int*[groups.length()];
    for (int i = 0; i < groups.length(); i++){
        wages[i] = new int[rooms.length()];
    }

    int goodMaxVal = 0, goodIndex = 0;
    bool validAssign = false;
    for (int i = 0; i <groups.length(); i++){
        for (int j = 0; j < rooms.length(); j++){
            qDebug() << "i = " << i << " j = " << j << " maxVal = " << goodMaxVal << endl;
            int wage = groups.at(i)->getValue() * rooms.at(j)->getValue();
            qDebug() << "Waga = " << wage << endl;
            wages[i][j] = wage;
            if(rooms.at(j)->getGender() != NOT_SET){
                if (rooms.at(j)->getGender() == groups.at(i)->getGender()){
                    if (rooms.at(j)->getPeopleInRoom() + groups.at(i)->getNumberOfPeople() <= rooms.at(j)->getCapacity()){
                        if (wages[i][j] > goodMaxVal){
                            goodMaxVal = wages[i][j];
                            goodIndex = j;
                            validAssign = true;
                            qDebug() << "Found possible solution with value " << goodMaxVal << endl;
                        }
                    }else{
                        qDebug() << QString("Room = (%1/%2). People in group = %3").arg(rooms.at(j)->getPeopleInRoom()).arg(rooms.at(j)->getCapacity()).arg(groups.at(i)->getNumberOfPeople()) << endl;
                    }
                }else{
                    qDebug() << QString("Room gender = %1, group gender = %2").arg(rooms.at(j)->getGender()).arg(groups.at(i)->getGender()) << endl;
                }
            }
            else
            {
                if (rooms.at(j)->getPeopleInRoom() + groups.at(i)->getNumberOfPeople() <= rooms.at(j)->getCapacity()){
                    if (groups.at(i)->getGender() == IMP_COUPLE || groups.at(i)->getGender() == COUPLE){
                        if ((rooms.at(j)->getCapacity() - rooms.at(j)->getPeopleInRoom() + groups.at(i)->getNumberOfPeople()) % 2 == 0){
                            if (wages[i][j] > goodMaxVal){
                                goodMaxVal = wages[i][j];
                                goodIndex = j;
                                validAssign = true;
                            }
                        }
                    }else{
                        if (wages[i][j] > goodMaxVal){
                            goodMaxVal = wages[i][j];
                            goodIndex = j;
                            validAssign = true;
                        }
                    }
                    qDebug() << "Found possible solution with value " << goodMaxVal << endl;
                }else{
                    qDebug() << QString("Room = (%1/%2). People in group = %3").arg(rooms.at(j)->getPeopleInRoom()).arg(rooms.at(j)->getCapacity()).arg(groups.at(i)->getNumberOfPeople()) << endl;
                }
            }

        }
        if (validAssign){
            groups.at(i)->setRoom((*rooms.at(goodIndex)));
            qDebug() << QString("%1 get room nr %2 on %3 floor").arg(groups.at(i)->getNames()).arg(rooms.at(goodIndex)->getNumber()).arg(rooms.at(goodIndex)->getFloor());
            validAssign = false;
            goodIndex = -1;
            goodMaxVal = 0;
        }
    }
    /*
     * dla każdej osoby iterujemy po pokojach
     * sprawdzamy czy w pokoju juz jest jakas płeć i czy pasujemy -> jak nie to nastepny pokoj
     * sprawdzamy czy po wlozeniu osoby do pokoju nie przekroczymy limitu -> jak tak to nastepny pokoj
     * wybieramy najwyższą wartosć i przypisujemy osobe do pokoju i pokoj do osoby
     * jak pokoj nie mial plci to ustawiamy, i dostosowywujemy ilosc osob w pokoju (moze we wczesniejszym kroku)
     */
    qDebug()<< "Problem solved." << endl;
}
