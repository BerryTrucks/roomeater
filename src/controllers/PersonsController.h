/*
 * PersonsController.h
 *
 *  Created on: 2 lis 2015
 *      Author: Kamil
 */

#ifndef PERSONSCONTROLLER_H_
#define PERSONSCONTROLLER_H_

#include <bb/cascades/GroupDataModel>
#include <QObject>
#include "src/model/Person.hpp"
#include "src/model/Group.h"

using namespace bb::cascades;


class Person;
class Group;

class PersonsController : public QObject
{
Q_OBJECT

Q_PROPERTY(bb::cascades::DataModel* dataModel READ dataModel CONSTANT)
public slots:
    void assignPeople(QList<Person*> people);
    Q_INVOKABLE void updateView();

public:
    PersonsController(QObject *parent = 0);
    virtual ~PersonsController();
    QList<Group*> & getGroups();
    Person* getPerson(uint hash);
    Q_INVOKABLE void unassign(QString id);
    signals:
    void updateOtherViews();
private:
    void extractGroups();
    QList<Person*> m_persons;
    QList<Group*> m_groups;
    GroupDataModel * model;
    GroupDataModel * dataModel() const;
};

#endif /* PERSONSCONTROLLER_H_ */
