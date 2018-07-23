/*
 * Group.h
 *
 *  Created on: 6 lis 2015
 *      Author: Kamil
 */

#ifndef GROUP_H_
#define GROUP_H_

#include "src/model/Person.hpp"
#include "src/model/Group.h"

class Person;
class Room;

class Group
{
public:
    Group(QObject *parent = 0);
    virtual ~Group();

    int getNumberOfPeople() const
    {
        return m_numberOfPeople;
    }

    int getValue() const
    {
        return m_valueOfGroup;
    }
    Gender getGender();

    void setRoom(Room & room);

    void addPerson(Person* p);

    QString getNames();

private:
    int m_numberOfPeople;
    QList<Person*> m_members;
    int m_valueOfGroup;
};

#endif /* GROUP_H_ */
