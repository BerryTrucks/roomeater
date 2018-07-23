/*
 * Person.h
 *
 *  Created on: 2 lis 2015
 *      Author: Kamil
 */

#ifndef PERSON_HPP_
#define PERSON_HPP_

#include <QObject>
#include "src/enums/Gender.hpp"
#include "Room.hpp"
#include <QDebug>

class Room;

class Person: public QObject
{
Q_OBJECT
public:
    Person(QObject *parent = 0);

    virtual ~Person();

    const QList<Person*>& getAlreadyWasInRoomWith() const
    {
        return m_alreadyWasInRoomWith;
    }

    void setAlreadyWasInRoomWith(const QList<Person*>& alreadyWasInRoomWith)
    {
        m_alreadyWasInRoomWith = alreadyWasInRoomWith;
    }

    const QString& getFirstName() const
    {
        return m_firstName;
    }

    void setFirstName(const QString& firstName)
    {
        m_firstName = firstName;
        updateHash();
    }

    Gender getGender() const
    {
        return m_gender;
    }

    void setGender(Gender gender)
    {
        m_gender = gender;
        switch (gender) {
            case MALE:
                m_valueForSolution = 2;
                break;
            case FEMALE:
                m_valueForSolution = 5;
                break;
            case IMP_COUPLE:
                m_valueForSolution = 10;
                break;
            case COUPLE:
                m_valueForSolution = 1;
                break;
            default:
                m_valueForSolution = 1;
                break;
        }
        updateHash();
    }

    bool isIsAllTakeCOurse() const
    {
        return m_isAllTakeCourse;
    }

    void setIsAllTakeCourse(bool isAllTakeCourse)
    {
        m_isAllTakeCourse = isAllTakeCourse;
    }

    bool isIsDriver() const
    {
        return m_isDriver;
    }

    void setIsDriver(bool isDriver)
    {
        m_isDriver = isDriver;
    }

    void setIsSnoorer(bool isSnoorer)
    {
        m_isSnoorer = isSnoorer;
    }

    const QString& getLastName() const
    {
        return m_lastName;
    }

    void setLastName(const QString& lastName)
    {
        m_lastName = lastName;
        updateHash();
    }

    const Person* getSpouse() const
    {
        return m_spouse;
    }

    void setSpouse(const Person* spouse)
    {
        m_spouse = spouse;
    }

    Room* getRoom()
    {
        return m_assosiatedRoom;
    }

    void setRoom(Room* room);

    QString toString();

    int getValue() const
    {
        return m_valueForSolution;
    }

    uint getHash() const
    {
        return m_Hash;
    }

    void leaveRoom();

private:
    void updateHash();
    int m_valueForSolution;
    QString m_firstName;
    QString m_lastName;
    bool m_isSnoorer;
    const Person * m_spouse;
    bool m_isDriver;
    bool m_isAllTakeCourse;
    Gender m_gender;
    Room * m_assosiatedRoom;
    QList<Person*> m_alreadyWasInRoomWith;
//    QList<Person*> m_preferedMates;
    uint m_Hash;
};
#endif /* PERSON_HPP_ */
