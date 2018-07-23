/*
 * Room.cpp
 *
 *  Created on: 2 lis 2015
 *      Author: Kamil
 */

#include "Room.hpp"
#include "src/enums/Building.hpp"
#include "src/enums/Gender.hpp"
#include "src/enums/RoomStandard.hpp"
#include <QDebug>

Room::Room(QObject *parent)
{
    // TODO Auto-generated constructor stub
    m_floor = 0;
    m_building = "Main";
    m_capacity = 2;
    m_genderAssigned = NOT_SET;
    m_isAvailable = true;
    m_standard = NO_SHOWER;
    m_number = "1";
    m_value = 10;
    updateHash();
    /*
     * z prysznicem - 100
     * bez prysznica - 10
     */
}

Room::~Room()
{
    // TODO Auto-generated destructor stub
}

int Room::getPeopleInRoom()
{
    return m_assignedPersons.length();
}

void Room::addPerson(Person & person)
{
    if (m_assignedPersons.length() == m_capacity){
        qWarning() << "Room is full!" << endl;
        return;
    }
    m_assignedPersons.append(&person);
    m_genderAssigned = person.getGender();
}

void Room::updateHash()
{
    QString base = QString("%1-%2-%3").arg(m_building).arg(m_floor).arg(m_number);
    m_hash = qHash(base);
}

void Room::clearRoom()
{
    for (int i = 0; i < m_assignedPersons.length(); i++){
        if (m_assignedPersons.at(i)->getRoom()){
            m_assignedPersons.at(i)->leaveRoom();
        }
    }
    m_assignedPersons.clear();
    m_genderAssigned = NOT_SET;
}

void Room::removePerson(Person* person)
{
    if (!person){
        qDebug() << "Tried to remove NULL person";
        return;
    }
    if (!m_assignedPersons.removeOne(person)){
        qWarning() << QString("Problem removing %1 from %2").arg(person->toString()).arg(toString());
    }
    if (m_assignedPersons.length() == 0){
        m_genderAssigned = NOT_SET;
    }
}

QString Room::toString()
{
    QString output = QString("Room %1 in %2 at %3 floor, capacity %4").arg(m_number).arg(m_building).arg(m_floor).arg(m_capacity);
    return output;
}
