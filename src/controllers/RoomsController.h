/*
 * RoomsController.h
 *
 *  Created on: 2 lis 2015
 *      Author: Kamil
 */

#ifndef ROOMSCONTROLLER_H_
#define ROOMSCONTROLLER_H_

#include <bb/cascades/GroupDataModel>
#include <bb/data/JsonDataAccess>
#include "src/model/Room.hpp"

using namespace bb::data;
using namespace bb::cascades;

class Room;

class RoomsController : public QObject
{
Q_OBJECT
Q_PROPERTY(bb::cascades::DataModel* dataModel READ dataModel CONSTANT)
Q_PROPERTY(bb::cascades::DataModel* availableRoomsDataModel READ availableRoomsDataModel CONSTANT)
public:

    RoomsController(QObject *parent = 0);
    virtual ~RoomsController();
    void loadData();
    void saveData();
    void clearAllRooms();
    Room* getRoom(uint hash);
    QList<Room*> & getAllRooms();
    QList<Room*> & getAvailableRooms();
    public slots:
    Q_INVOKABLE void updateView();
    Q_INVOKABLE void updateAvailableRoomsView();
    Q_INVOKABLE void freeUp(QString id);
    Q_INVOKABLE void remove(QString id);
//    Q_INVOKABLE void edit(QString id);
    Q_INVOKABLE void swap(QString fromId, QString toId);
    Q_INVOKABLE void makeAvailable(QString id);
    Q_INVOKABLE void makeUnavailable(QString id);
    Q_INVOKABLE bool updateAndSaveRoom(uint id, QString building, int capacity, int floor, QString number, bool hasShower);

    signals:
    void updateOtherViews();
private:
    QList<Room*> m_rooms;
    GroupDataModel * model;
    GroupDataModel * dataModel() const;
    GroupDataModel * availableRoomsModel;
    GroupDataModel * availableRoomsDataModel() const;
};

#endif /* ROOMSCONTROLLER_H_ */
