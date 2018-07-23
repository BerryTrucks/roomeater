/*
 * Group.cpp
 *
 *  Created on: 6 lis 2015
 *      Author: Kamil
 */

#include <src/model/Group.h>

Group::Group(QObject *parent)
{
    // TODO Auto-generated constructor stub
    m_numberOfPeople = 0;
    m_valueOfGroup = 0;
}

Group::~Group()
{
    // TODO Auto-generated destructor stub
}

Gender Group::getGender()
{
    if (m_members.length() > 0){
        return m_members.first()->getGender();
    }
    return NOT_SET;
}

void Group::setRoom(Room& room)
{
    for (int i = 0; i < m_members.length(); i++){
        m_members.at(i)->setRoom(&room);
    }
}

void Group::addPerson(Person* p)
{
    if (p == NULL){
        qWarning () << "Adding NULL person to the group!" << endl;
        return;
    }
    m_members.append(p);
    m_numberOfPeople++;
    m_valueOfGroup = p->getValue();
}

QString Group::getNames()
{
    QString names;
    for (int i = 0; i < m_members.length(); i++){
        names = m_members.at(i)->getFirstName() + "" +  m_members.at(i)->getLastName() + ", ";
    }
    return names;
}
