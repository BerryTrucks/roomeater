/*
 * NaiveBothSidesSolutionFinder.cpp
 *
 *  Created on: 9 lis 2015
 *      Author: Kamil
 */

#include <src/solution/NaiveBothSidesSolutionFinder.h>

NaiveBothSidesSolutionFinder::NaiveBothSidesSolutionFinder(QObject *parent)
{
    // TODO Auto-generated constructor stub

}

NaiveBothSidesSolutionFinder::~NaiveBothSidesSolutionFinder()
{
    // TODO Auto-generated destructor stub
}

void NaiveBothSidesSolutionFinder::findSolution(const QList<Group*>& groups,
        const QList<Room*>& rooms)
{
    int ** wages = new int*[groups.length()];
    for (int i = 0; i < groups.length(); i++){
        wages[i] = new int[rooms.length()];
    }

    int minFoundValDolnaGrupa = 1000000, maxFoundValGornaGrupa = 0, indexFounfMaxValGornaGrupa = 0, indexFoundMinDolnaGrupa = 0;
    bool validMaxGornaGrupa = false, validMinDolnaGrupa = false;
    for (int gorna = 0, dolna = groups.length() - 1 - gorna; gorna < groups.length() && dolna >= gorna; gorna++, dolna--){
        Group* grupaGorna = groups.at(gorna);
        Group* grupaDolna = groups.at(dolna);
        for (int j = 0; j < rooms.length(); j++){
            Room* room = rooms.at(j);
            int wagaDlaGornejGrupy = grupaGorna->getValue() * room->getValue();
            int wagaDlaDolnejGrupy = grupaDolna->getValue() * room->getValue();
            qDebug() << "Waga Gornej grupy= " << wagaDlaGornejGrupy << endl;
            qDebug() << "Waga Dolnej grupy= " << wagaDlaDolnejGrupy << endl;
            wages[gorna][j] = wagaDlaGornejGrupy;
            wages[dolna][j] = wagaDlaDolnejGrupy;
            if(room->getGender() != NOT_SET){
                if (room->getGender() == grupaGorna->getGender()){
                    if (room->getPeopleInRoom() + grupaGorna->getNumberOfPeople() <= room->getCapacity()){
                        if (wagaDlaGornejGrupy > maxFoundValGornaGrupa){
                            maxFoundValGornaGrupa = wagaDlaGornejGrupy;
                            indexFounfMaxValGornaGrupa = j;
                            validMaxGornaGrupa = true;
                            qDebug() << "Found MIN possible solution with value " << maxFoundValGornaGrupa << endl;
                        }
                    }
                }
                if (room->getGender() == grupaDolna->getGender()){
                    if (room->getPeopleInRoom() + grupaDolna->getNumberOfPeople() <= room->getCapacity()){
                        if (wagaDlaDolnejGrupy < minFoundValDolnaGrupa){
                            minFoundValDolnaGrupa = wagaDlaDolnejGrupy;
                            indexFoundMinDolnaGrupa = j;
                            validMinDolnaGrupa = true;
                            qDebug() << "Found MIN possible solution with value " << minFoundValDolnaGrupa << endl;
                        }
                    }
                }
            }else{
                if (room->getPeopleInRoom() + grupaGorna->getNumberOfPeople() <= room->getCapacity()){
                    if (wagaDlaGornejGrupy > maxFoundValGornaGrupa){
                        maxFoundValGornaGrupa = wagaDlaGornejGrupy;
                        indexFounfMaxValGornaGrupa = j;
                        validMaxGornaGrupa = true;
                        qDebug() << "Found MAX possible solution with value " << maxFoundValGornaGrupa << endl;
                    }
                }
                if (room->getPeopleInRoom() + grupaDolna->getNumberOfPeople() <= room->getCapacity()){
                    if (wagaDlaDolnejGrupy < minFoundValDolnaGrupa){
                        minFoundValDolnaGrupa = wagaDlaDolnejGrupy;
                        indexFoundMinDolnaGrupa = j;
                        validMinDolnaGrupa = true;
                        qDebug() << "Found MIN possible solution with value " << minFoundValDolnaGrupa << endl;
                    }
                }
            }
        }
        if (validMaxGornaGrupa){
            grupaGorna->setRoom((*rooms.at(indexFounfMaxValGornaGrupa)));
            qDebug() << QString("%1 get room nr %2 on %3 floor").arg(grupaGorna->getNames()).arg(rooms.at(indexFounfMaxValGornaGrupa)->getNumber()).arg(rooms.at(indexFounfMaxValGornaGrupa)->getFloor());
            validMaxGornaGrupa = false;
            indexFounfMaxValGornaGrupa = -1;
            maxFoundValGornaGrupa = 0;
        }
        if (validMinDolnaGrupa){
            grupaDolna->setRoom((*rooms.at(indexFoundMinDolnaGrupa)));
            qDebug() << QString("%1 get room nr %2 on %3 floor").arg(grupaDolna->getNames()).arg(rooms.at(indexFoundMinDolnaGrupa)->getNumber()).arg(rooms.at(indexFoundMinDolnaGrupa)->getFloor());
            validMinDolnaGrupa = false;
            indexFoundMinDolnaGrupa = -1;
            minFoundValDolnaGrupa = 1000000;
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
