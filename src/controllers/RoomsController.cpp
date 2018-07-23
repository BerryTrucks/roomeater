/*
 * RoomsController.cpp
 *
 *  Created on: 2 lis 2015
 *      Author: Kamil
 */

#include <src/controllers/RoomsController.h>
#include <bb/data/JsonDataAccess>
#include <bb/data/XmlDataAccess>
#include "src/model/Room.hpp"

using namespace bb::cascades;

RoomsController::RoomsController(QObject *parent)
{
    // TODO Auto-generated constructor stub
    model = new GroupDataModel();
    availableRoomsModel = new GroupDataModel();
    m_rooms = QList<Room*>();
    Room * r = new Room();
    r->setCapacity(3);
    r->setFloor(1);
    r->setNumber("2");
    r->setStandard(SHOWER);
    m_rooms.append(r);
    Room * r1 = new Room();
    r1->setCapacity(2);
    r1->setNumber("5");
    r1->setFloor(1);
    r1->setStandard(SHOWER);
    m_rooms.append(r1);
    Room * r1x = new Room();
    r1x->setCapacity(4);
    r1x->setNumber("6");
    r1x->setFloor(1);
    r1x->setStandard(SHOWER);
    m_rooms.append(r1x);

    Room * r2 = new Room();
    r2->setCapacity(3);
    r2->setNumber("9");
    r2->setFloor(2);
    r2->setStandard(SHOWER);
    m_rooms.append(r2);
    Room * r3 = new Room();
    r3->setCapacity(2);
    r3->setNumber("10");
    r3->setFloor(2);
    r3->setStandard(NO_SHOWER);
    m_rooms.append(r3);
    Room * r4 = new Room();
    r4->setCapacity(2);
    r4->setNumber("11");
    r4->setFloor(2);
    r4->setStandard(NO_SHOWER);
    m_rooms.append(r4);
    Room * r5 = new Room();
    r5->setCapacity(3);
    r5->setNumber("12");
    r5->setFloor(2);
    r5->setStandard(NO_SHOWER);
    m_rooms.append(r5);
    Room * r6 = new Room();
    r6->setCapacity(2);
    r6->setNumber("13");
    r6->setFloor(2);
    r6->setStandard(NO_SHOWER);
    m_rooms.append(r6);
    Room * r7 = new Room();
    r7->setCapacity(2);
    r7->setNumber("14");
    r7->setFloor(2);
    r7->setStandard(NO_SHOWER);
    m_rooms.append(r7);
    Room * r8 = new Room();
    r8->setCapacity(3);
    r8->setNumber("15");
    r8->setFloor(2);
    r8->setStandard(NO_SHOWER);
    m_rooms.append(r8);
    Room * r9 = new Room();
    r9->setCapacity(4);
    r9->setNumber("16");
    r9->setFloor(2);
    r9->setStandard(NO_SHOWER);
    m_rooms.append(r9);

    Room * r10 = new Room();
    r10->setCapacity(2);
    r10->setNumber("18");
    r10->setFloor(3);
    r10->setStandard(NO_SHOWER);
    r10->setIsAvailable(false);
    m_rooms.append(r10);
    Room * r11 = new Room();
    r11->setCapacity(3);
    r11->setNumber("19");
    r11->setFloor(3);
    r11->setStandard(NO_SHOWER);
    r11->setIsAvailable(false);
    m_rooms.append(r11);
    Room * r12 = new Room();
    r12->setCapacity(3);
    r12->setNumber("20");
    r12->setFloor(3);
    r12->setStandard(NO_SHOWER);
    r12->setIsAvailable(false);
    m_rooms.append(r12);
    Room * r13 = new Room();
    r13->setCapacity(2);
    r13->setNumber("21");
    r13->setFloor(3);
    r13->setStandard(NO_SHOWER);
    r13->setIsAvailable(false);
    m_rooms.append(r13);
    Room * r14 = new Room();
    r14->setCapacity(2);
    r14->setNumber("22");
    r14->setFloor(3);
    r14->setStandard(NO_SHOWER);
    r14->setIsAvailable(false);
    m_rooms.append(r14);
    Room * r15 = new Room();
    r15->setCapacity(3);
    r15->setNumber("23");
    r15->setFloor(3);
    r15->setStandard(NO_SHOWER);
    r15->setIsAvailable(false);
    m_rooms.append(r15);
    Room * r16 = new Room();
    r16->setCapacity(3);
    r16->setNumber("24");
    r16->setFloor(3);
    r16->setStandard(NO_SHOWER);
    r16->setIsAvailable(false);
    m_rooms.append(r16);

    Room * r17 = new Room();
    r17->setCapacity(2);
    r17->setNumber("1");
    r17->setFloor(1);
    r17->setStandard(SHOWER);
    r17->setBuilding("Anbau");
    r17->setIsAvailable(false);
    m_rooms.append(r17);
    Room * r18 = new Room();
    r18->setCapacity(2);
    r18->setNumber("2");
    r18->setFloor(1);
    r18->setStandard(SHOWER);
    r18->setIsAvailable(false);
    r18->setBuilding("Anbau");
    m_rooms.append(r18);
    Room * r19 = new Room();
    r19->setCapacity(3);
    r19->setNumber("3");
    r19->setFloor(1);
    r19->setStandard(SHOWER);
    r19->setIsAvailable(false);
    r19->setBuilding("Anbau");
    m_rooms.append(r19);
    Room * r20 = new Room();
    r20->setCapacity(3);
    r20->setNumber("4");
    r20->setFloor(1);
    r20->setStandard(SHOWER);
    r20->setIsAvailable(false);
    r20->setBuilding("Anbau");
    m_rooms.append(r20);
    Room * r21 = new Room();
    r21->setCapacity(2);
    r21->setNumber("5");
    r21->setFloor(1);
    r21->setStandard(SHOWER);
    r21->setIsAvailable(false);
    r21->setBuilding("Anbau");
    m_rooms.append(r21);


    Room * r30 = new Room();
    r30->setCapacity(5);
    r30->setNumber("1");
    r30->setFloor(0);
    r30->setStandard(SHOWER);
    r30->setIsAvailable(true);
    r30->setBuilding("Lakehouse");
    m_rooms.append(r30);

    saveData();
    loadData();
}

RoomsController::~RoomsController()
{
    // TODO Auto-generated destructor stub
}

void RoomsController::loadData()
{
    // TODO
    QList<Room*> loadedRooms = QList<Room*>();
    JsonDataAccess jda;
    QString mJsonDataPath = "savedRooms.json";
    const QDir home = QDir::home();
    QVariant data = jda.load(home.absoluteFilePath(mJsonDataPath));

    if (jda.hasError()) {
        bb::data::DataAccessError error = jda.error();
        qDebug() << "JSON loading error: " << error.errorType() << ": "
                << error.errorMessage();
    } else {
        qDebug() << "JSon loaded";
    }

    QVariantList list = data.toList();
    foreach( QVariant v, list){
        Room *r = new Room();
        QVariantMap roomMap = v.toMap();
        r->setBuilding(roomMap["building"].toString());
        r->setCapacity(roomMap["capacity"].toInt());
        r->setFloor(roomMap["floor"].toInt());
        r->setNumber(roomMap["number"].toString());
        r->setStandard((RoomStandard)roomMap["standard"].toInt());
        loadedRooms.append(r);
    }
    m_rooms = loadedRooms;
}

void RoomsController::saveData()
{
    QString mJsonDataPath = "savedRooms.json";

    QVariantList dataToSave;
    QVariantMap room;
    for (int i = 0; i < m_rooms.length(); i++){
        room["building"] = m_rooms.at(i)->getBuilding();
        room["capacity"] = m_rooms.at(i)->getCapacity();
        room["floor"] = m_rooms.at(i)->getFloor();
        room["number"] = m_rooms.at(i)->getNumber();
        room["standard"] = m_rooms.at(i)->getStandard();
        room["value"] = m_rooms.at(i)->getValue();
        dataToSave << room;
    }

    const QDir home = QDir::home();
    QFile fileToSafe(home.absoluteFilePath(mJsonDataPath));
    fileToSafe.open(QIODevice::WriteOnly);
    if (fileToSafe.isOpen()){
        JsonDataAccess jda(&fileToSafe);
        jda.save(dataToSave, &fileToSafe);

        if (jda.hasError()) {
            bb::data::DataAccessError error = jda.error();
            qDebug() << "JSON loading error: " << error.errorType() << ": " << error.errorMessage();
        }else {
            fileToSafe.close();
        }
    }
}

void RoomsController::updateView()
{
    if (m_rooms.isEmpty()){
        return;
    }
    model->clear();
    for (int i = m_rooms.length() - 1; i >= 0; i--){
        QVariantMap roomToMap;
        roomToMap["roomNumber"] = m_rooms.at(i)->getNumber();
        if (m_rooms.at(i)->getStandard() == SHOWER){
            roomToMap["standard"] = "room_with_shower.png";
        }else{
            roomToMap["standard"] = "room_no_shower.png";
        }
        roomToMap["floor"] = m_rooms.at(i)->getFloor();
        roomToMap["capacity"] = QString("%1").arg(m_rooms.at(i)->getCapacity());
        roomToMap["peopleIn"] = QString("%1").arg(m_rooms.at(i)->getPeopleInRoom());
        QString peopleInRoom = "";
        if (!m_rooms.at(i)->getPersons().isEmpty()){
            for (int j = 0; j < m_rooms.at(i)->getPersons().length(); j++){
                peopleInRoom += QString("%1 %2").arg(m_rooms.at(i)->getPersons().at(j)->getFirstName()).arg(m_rooms.at(i)->getPersons().at(j)->getLastName());
            }
        }
        roomToMap["people"] = peopleInRoom;
        roomToMap["build"] = m_rooms.at(i)->getBuilding();
        roomToMap["hash"] = m_rooms.at(i)->getHash();
        if (m_rooms.at(i)->isAvailable()){
            roomToMap["avail"] = "";
        } else {
            roomToMap["avail"] = "N/A";
        }
        model->insert(roomToMap);
        roomToMap.clear();
    }
}

void RoomsController::clearAllRooms()
{
    for (int i = 0; i < m_rooms.length(); i++){
        m_rooms.at(i)->clearRoom();
    }
    updateView();
    emit updateOtherViews();
}

void RoomsController::updateAvailableRoomsView()
{
    if (m_rooms.isEmpty()){
        return;
    }
    availableRoomsModel->clear();
    for (int i = m_rooms.length() - 1; i >= 0; i--){
        if (m_rooms.at(i)->isAvailable() && m_rooms.at(i)->getCapacity() > m_rooms.at(i)->getPeopleInRoom()){
            QVariantMap roomToMap;
            roomToMap["roomNumber"] = m_rooms.at(i)->getNumber();
            if (m_rooms.at(i)->getStandard() == SHOWER){
                roomToMap["standard"] = "room_with_shower.png";
            }else{
                roomToMap["standard"] = "room_no_shower.png";
            }
            roomToMap["floor"] = m_rooms.at(i)->getFloor();
            roomToMap["capacity"] = QString("%1").arg(m_rooms.at(i)->getCapacity());
            roomToMap["peopleIn"] = QString("%1").arg(m_rooms.at(i)->getPeopleInRoom());
            QString peopleInRoom = "";
            if (!m_rooms.at(i)->getPersons().isEmpty()){
                for (int j = 0; j < m_rooms.at(i)->getPersons().length(); j++){
                    peopleInRoom += QString("%1 %2").arg(m_rooms.at(i)->getPersons().at(j)->getFirstName()).arg(m_rooms.at(i)->getPersons().at(j)->getLastName());
                }
            }
            roomToMap["people"] = peopleInRoom;
            roomToMap["build"] = m_rooms.at(i)->getBuilding();
            roomToMap["hash"] = m_rooms.at(i)->getHash();
            if (m_rooms.at(i)->isAvailable()){
                roomToMap["avail"] = "";
            } else {
                roomToMap["avail"] = "N/A";
            }
            availableRoomsModel->insert(roomToMap);
            roomToMap.clear();
        }
    }
}

GroupDataModel* RoomsController::dataModel() const
{
    return model;
}

QList<Room*>& RoomsController::getAllRooms()
{
    return m_rooms;
}

void RoomsController::freeUp(QString id)
{
    if (id.isEmpty()){
        qDebug()<< "Hash is empty string" << endl;
        return;
    }
    for (int i = 0; i < m_rooms.length(); i++){
        QString hash = QString("%1").arg(m_rooms.at(i)->getHash());
        if (hash == id){
            for(int j = 0; j < m_rooms.at(i)->getPersons().length(); j++){
                m_rooms.at(i)->getPersons().at(j)->leaveRoom();
            }
            m_rooms.at(i)->clearRoom();
            break;
        }
    }
    updateView();
    emit updateOtherViews();
}

void RoomsController::makeAvailable(QString id)
{
    if (id.isEmpty()){
        qDebug()<< "Hash is empty string" << endl;
        return;
    }
    for (int i = 0; i < m_rooms.length(); i++){
        QString hash = QString("%1").arg(m_rooms.at(i)->getHash());
        if (hash == id){
            m_rooms.at(i)->setIsAvailable(true);
            break;
        }
    }
    updateView();
    emit updateOtherViews();
}

void RoomsController::makeUnavailable(QString id)
{
    if (id.isEmpty()){
        qDebug()<< "Hash is empty string" << endl;
        return;
    }
    for (int i = 0; i < m_rooms.length(); i++){
        QString hash = QString("%1").arg(m_rooms.at(i)->getHash());
        if (hash == id){
            for(int j = 0; j < m_rooms.at(i)->getPersons().length(); j++){
                m_rooms.at(i)->getPersons().at(j)->leaveRoom();
            }
            m_rooms.at(i)->clearRoom();
            m_rooms.at(i)->setIsAvailable(false);
            break;
        }
    }
    updateView();
    emit updateOtherViews();
}

void RoomsController::remove(QString id)
{
    if (id.isNull() || id.isEmpty()){
        qDebug()<< "Hash is null or empty string" << endl;
        return;
    }
    for (int i = 0; i < m_rooms.length(); i++){
        QString hash = QString("%1").arg(m_rooms.at(i)->getHash());
        if (hash == id){
            for(int j = 0; j < m_rooms.at(i)->getPersons().length(); j++){
                m_rooms.at(i)->getPersons().at(j)->leaveRoom();
            }
            m_rooms.at(i)->clearRoom();
            delete m_rooms.at(i);
            m_rooms.removeAt(i);
            break;
        }
    }
    updateView();
    emit updateOtherViews();
}

QList<Room*>& RoomsController::getAvailableRooms()
{
    QList<Room*> *availableRooms = new QList<Room*>();
    for (int i = 0; i < m_rooms.length(); i++){
        if (m_rooms.at(i)->isAvailable()){
            availableRooms->append(m_rooms.at(i));
        }
    }
    return (*availableRooms);
}

void RoomsController::swap(QString fromId, QString toId)
{
    if (fromId.isEmpty() || toId.isEmpty()){
        qDebug() << "One of the room Id to swap is empty" << endl;
        return;
    }
    Room *fromRoom = NULL, *toRoom = NULL;
    for (int i = 0; i < m_rooms.length(); i++){
        QString hash = QString("%1").arg(m_rooms.at(i)->getHash());
        if (hash == fromId){
            fromRoom = m_rooms.at(i);
            continue;
        }
        if (hash == toId){
            toRoom = m_rooms.at(i);
            continue;
        }
    }
    if (fromRoom && toRoom){
        QList<Person*> toPeople = toRoom->getPersons();
        toRoom->clearRoom();
        QList<Person*> fromPeople = fromRoom->getPersons();
        fromRoom->clearRoom();
        for (int i = 0; i < fromPeople.length(); i++){
            if(toRoom->getPeopleInRoom() < toRoom->getCapacity()){
                fromPeople.at(i)->setRoom(toRoom);
            }
            else{
                fromPeople.at(i)->leaveRoom();
            }
        }
        for (int i = 0; i < toPeople.length() && fromRoom; i++){
            if (fromRoom->getPeopleInRoom() < fromRoom->getCapacity()){
                toPeople.at(i)->setRoom(fromRoom);
            }
            else{
                toPeople.at(i)->leaveRoom();
            }
        }
    }
    updateView();
    emit updateOtherViews();
}

GroupDataModel* RoomsController::availableRoomsDataModel() const
{
    return availableRoomsModel;
}

Room* RoomsController::getRoom(uint hash)
{
    for (int i = 0; i < m_rooms.length(); i++){
        if (m_rooms.at(i)->getHash() == hash){
            return m_rooms.at(i);
        }
    }
    return NULL;
}

bool RoomsController::updateAndSaveRoom(uint id, QString building, int capacity,
        int floor, QString number, bool hasShower)
{
    uint hash = id;//.toUInt();
    int cap = capacity;//.toInt();// validation needed
    int fl = floor;//.toInt();// validation needed
    if (id == 0) {
        Room* newRoom = new Room();
        newRoom->setBuilding(building);
        newRoom->setCapacity(cap);
        newRoom->setFloor(fl);
        newRoom->setNumber(number);
        if (hasShower){
            newRoom->setStandard(SHOWER);
        } else {
            newRoom->setStandard(NO_SHOWER);
        }
        m_rooms.append(newRoom);
        updateView();
        emit updateOtherViews();
        return true;
    }
    for (int i = 0; i < m_rooms.length(); i++){
        if (m_rooms.at(i)->getHash() == hash){
            m_rooms.at(i)->setBuilding(building);
            m_rooms.at(i)->setCapacity(cap);
            m_rooms.at(i)->setFloor(fl);
            m_rooms.at(i)->setNumber(number);
            if (hasShower){
                m_rooms.at(i)->setStandard(SHOWER);
            } else {
                m_rooms.at(i)->setStandard(NO_SHOWER);
            }
            updateView();
            emit updateOtherViews();
            return true;
        } else {
            continue;
        }
    }
    return false;
}
