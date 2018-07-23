/*
 * NaiveWithFeeSolutionFInder.cpp
 *
 *  Created on: 10 lis 2015
 *      Author: Kamil
 */

#include <src/solution/NaiveWithFeeSolutionFinder.h>

NaiveWithFeeSolutionFinder::NaiveWithFeeSolutionFinder(QObject *parent)
{
    // TODO Auto-generated constructor stub

}

NaiveWithFeeSolutionFinder::~NaiveWithFeeSolutionFinder()
{
    // TODO Auto-generated destructor stub
}

void NaiveWithFeeSolutionFinder::findSolution(const QList<Group*>& groups,
        const QList<Room*>& rooms)
{
    /*
     * dla każdej grupy iterujemy po pokojach
     * przypisujemy temu rozwiazaniu wartosc -> ta grupa w tym pokoju
     * sprawdzamy czy w pokoju juz jest jakas płeć
     *  jak jest to sprawdzamy czy pasujemy -> jak nie pasujemy to sprawdzmy kolejny pokoj
     *  sprawdzamy czy po dodaniu ludzi z grupy nie przekroczymy pojemosci pokoju -> jak tak to sprawdzmy nastepny pokoj
     *  jesli wartosc rozwiazania jest wieksza od dotychczasowo znalezionej to zapamietujemy je
     * jesli nie ma jeszcze nikogo w pokoju
     *  sprawdzamy czy grupa ktora sie zajmujemy to para (wazna, lub mniej wazna -> z poczatku czy z konca listy priorytetow)
     *    sprawdzmy czy po wlozeniu pary do pokoju zapewlnimy go do pelna
     *     jesli NIE to zapamietujemy to rozwiazanie jako DOBRE
     *     jesli TAK (pokoj jest pelny) to zapamietujemy to rozwiazanie jako NAJLEPSZE
     *   jesli grupa nie jest parą
     *    sprawdzmy czy obecne rozwiazanie jest lepsze od ostatniego znalezionego
     *    jesli tak to zapamietujemy
     */
    int ** wages = new int*[groups.length()];
    for (int i = 0; i < groups.length(); i++){
        wages[i] = new int[rooms.length()];
    }

    int goodMaxVal = 0, goodIndex = 0;
    int theBestMaxVal = 0, theBestIndex = 0;
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
                        if (rooms.at(j)->getPeopleInRoom() + groups.at(i)->getNumberOfPeople() < rooms.at(j)->getCapacity()){
                            if (wages[i][j] > goodMaxVal){
                                goodIndex = j;
                                goodMaxVal = wages[i][j];
                                validAssign = true;
                            }
                        }else{ // the best is to put couple to fill out the room right when it is assign to the room, which means always to 2 person room
                            if (wages[i][j] > theBestMaxVal){
                                theBestIndex = j;
                                theBestMaxVal = wages[i][j];
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
            if (theBestIndex != -1){
                goodIndex = theBestIndex;
            }
            groups.at(i)->setRoom((*rooms.at(goodIndex)));
            qDebug() << QString("%1 get room nr %2 on %3 floor").arg(groups.at(i)->getNames()).arg(rooms.at(goodIndex)->getNumber()).arg(rooms.at(goodIndex)->getFloor());
            validAssign = false;
            goodIndex = -1;
            goodMaxVal = 0;
            theBestIndex = -1;
            theBestMaxVal  = 0;
        }
    }
    qDebug()<< "Problem solved." << endl;
}
