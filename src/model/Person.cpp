/*
 * Person.cpp
 *
 *  Created on: 2 lis 2015
 *      Author: Kamil
 */

#include "Person.hpp"

Person::Person(QObject *parent)
{
    m_gender = IMP_COUPLE;
    m_isAllTakeCourse = false;
    m_isDriver = false;
    m_isSnoorer = false;
    m_spouse = NULL;
    m_valueForSolution = 1;
    m_assosiatedRoom = NULL;
    updateHash();
    /*
     * para wysoko 10
     * kobieta 5
     * mezczyzna 2
     * para nisko 1
     */
}

Person::~Person()
{
    // TODO Auto-generated destructor stub
}

QString Person::toString()
{
    QString output = QString("%1 %2 IsSnoorer(%3) IsDriver(%4) Gender(%5)").arg(m_firstName).arg(m_lastName).arg(m_isSnoorer).arg(m_isDriver).arg(m_gender);
    return output;
}

void Person::setRoom(Room* room)
{
    if (!room){
        qDebug() << "Tried to set NULL room";
        return;
    }
    if (m_assosiatedRoom){
        qWarning() << QString("%1 %2 is already in room!").arg(m_firstName).arg(m_lastName) << endl;
        return;
    }
    if (!room->isAvailable()){
        qWarning() << "Trying to set Unavailable room" << endl;
        return;
    }
    if (room->getPeopleInRoom() == room->getCapacity()){
        qWarning() << "Room is already full" << endl;
        return;
    }
    m_assosiatedRoom = room;
    room->addPerson(*this);
}

void Person::leaveRoom()
{
    if (m_assosiatedRoom){
        m_assosiatedRoom = NULL;
    }
}

void Person::updateHash()
{
    QString base = QString("%1-%2-%3").arg(m_firstName).arg(m_lastName).arg(m_gender);
    m_Hash = qHash(base);
}
