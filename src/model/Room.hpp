/*
 * Room.h
 *
 *  Created on: 2 lis 2015
 *      Author: Kamil
 */

#ifndef ROOM_HPP_
#define ROOM_HPP_

#include <QObject>
#include "Person.hpp"
#include "Group.h"
#include "src/enums/Building.hpp"
#include "src/enums/RoomStandard.hpp"
#include "src/enums/Gender.hpp"

class Person;
class Group;

class Room : QObject
{
Q_OBJECT
public:
    Room(QObject *parent = 0);
    virtual ~Room();

    const QList<Person*>& getPersons() const
    {
        return m_assignedPersons;
    }

    const QString& getBuilding() const
    {
        return m_building;
    }

    void setBuilding(QString building)
    {
        m_building = building;
        updateHash();
    }

    int getCapacity() const
    {
        return m_capacity;
    }

    void setCapacity(int capacity)
    {
        m_capacity = capacity;
    }

    int getFloor() const
    {
        return m_floor;
    }

    void setFloor(int floor)
    {
        m_floor = floor;
        updateHash();
    }

    Gender getGender() const
    {
        return m_genderAssigned;
    }

    const QString& getNumber() const
    {
        return m_number;
    }

    void setNumber(const QString& number)
    {
        m_number = number;
        updateHash();
    }

    RoomStandard getStandard() const
    {
        return m_standard;
    }

    void setStandard(RoomStandard standard)
    {
        m_standard = standard;
        if (standard == SHOWER){
            m_value = 100;
        }
    }

    int getValue() const
    {
        return m_value;
    }

    int getPeopleInRoom();

    void addPerson(Person & person);

    bool isAvailable() const
    {
        return m_isAvailable;
    }

    void setIsAvailable(bool isAvailable)
    {
        m_isAvailable = isAvailable;
        m_genderAssigned = NOT_SET;
    }

    uint getHash() const
    {
        return m_hash;
    }

    void clearRoom();

    void removePerson(Person* person);

    QString toString();

private:
    void updateHash();
    int m_value;
    QString m_number;
    int m_floor;
    QString m_building;
    RoomStandard m_standard;
    int m_capacity;
    QList<Person*> m_assignedPersons;
    bool m_isAvailable;
    Gender m_genderAssigned;
    uint m_hash;
};

#endif /* ROOM_HPP_ */
