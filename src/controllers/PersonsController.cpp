/*
 * PersonsController.cpp
 *
 *  Created on: 2 lis 2015
 *      Author: Kamil
 */

#include <src/controllers/PersonsController.h>
#include <src/enums/Gender.hpp>
#include <QDebug>
#include <bb/data/JsonDataAccess>
#include <bb/data/XmlDataAccess>

using namespace bb::data;

PersonsController::PersonsController(QObject *parent)
{
    // TODO Auto-generated constructor stub
    model = new GroupDataModel();
}

PersonsController::~PersonsController()
{
    // TODO Auto-generated destructor stub
}

void PersonsController::assignPeople(QList<Person*> people){
    qDebug() << "Assigned data" << endl;
    if (!m_persons.isEmpty()){
        for (int i = 0; i < m_persons.length(); i++){
            qDebug() << "Deleting: " << m_persons.at(i)->toString();
            delete m_persons.at(i);
        }
    }
    m_persons = people;
    extractGroups();
    updateView();
    emit updateOtherViews();
}

GroupDataModel* PersonsController::dataModel() const
{
    return model;
}

void PersonsController::updateView()
{
    qDebug() << "Will try to update the view of people" << endl;
    if (m_persons.isEmpty()){
        return;
    }
    model->clear();
    for (int i = m_persons.length() - 1; i >= 0; i--){
        QVariantMap personToMap;
        personToMap["firstName"] = m_persons.at(i)->getFirstName();
        personToMap["lastName"] = m_persons.at(i)->getLastName();
        QString color = "###";
        if (m_persons.at(i)->getGender() == MALE){
            color = "male-sign.png";
        } else if (m_persons.at(i)->getGender() == FEMALE) {
            color = "female-sign.png";
        } else {
            color = "couple-sign.png";
        }
        personToMap["gender"] = color;
        QString spouse = "";
        if (m_persons.at(i)->getSpouse() != NULL){
            spouse = m_persons.at(i)->getSpouse()->getFirstName() + " " + m_persons.at(i)->getSpouse()->getLastName();
        }
        personToMap["spouse"] = spouse;
        QString room = "";
        if (m_persons.at(i)->getRoom() != NULL){
            room = QString("%1: Nr %2 on %3 floor").arg(m_persons.at(i)->getRoom()->getBuilding()).arg(m_persons.at(i)->getRoom()->getNumber()).arg(m_persons.at(i)->getRoom()->getFloor());
        }
        personToMap["room"] = room;
        personToMap["hash"] = m_persons.at(i)->getHash();
        model->insert(personToMap);
        personToMap.clear();
    }
}

void PersonsController::extractGroups()
{
    m_groups.clear();
    for (int i= 0; i < m_persons.length(); i++){
        Group *g = new Group();
        if (m_persons.at(i)->getSpouse() != NULL){
            g->addPerson(m_persons.at(i));
            if (i < m_persons.length() - 1){ // TODO - cos tu jest zle
                g->addPerson(m_persons.at(i + 1));
            } else {
                qDebug() << "Last person is a part of a couple. That should not happen" << endl;
            }
            m_groups.append(g);
            i++;
        }
        else{
            g->addPerson(m_persons.at(i));
            m_groups.append(g);
        }
    }
}

QList<Group*> & PersonsController::getGroups()
{
    return m_groups;
}

void PersonsController::unassign(QString id)
{
    if (id.isEmpty()){
        qWarning() << "Hash for person is empty" << endl;
        return;
    }
    for (int i = 0; i < m_persons.length(); i++){
        QString base = QString("%1").arg(m_persons.at(i)->getHash());
        if (base == id){
            if (m_persons.at(i)->getRoom()){
                m_persons.at(i)->getRoom()->removePerson(m_persons.at(i));
                m_persons.at(i)->leaveRoom();
                break;
            }
        }
    }
    updateView();
    emit updateOtherViews();
}

Person* PersonsController::getPerson(uint hash)
{
    for (int i = 0; i < m_persons.length(); i++){
        if (m_persons.at(i)->getHash() == hash){
            return m_persons.at(i);
        }
    }
    return NULL;
}
