/*
 * MediatorController.h
 *
 *  Created on: 12 lis 2015
 *      Author: Kamil
 */

#ifndef MEDIATORCONTROLLER_H_
#define MEDIATORCONTROLLER_H_

#include <QObject>
#include "PersonsController.h"
#include "RoomsController.h"

class MediatorController: public QObject
{
Q_OBJECT
public:
    MediatorController(QObject *parent = 0);
    virtual ~MediatorController();
    void setPersonController(PersonsController *p){
        personController = p;
    }
    void setRoomController(RoomsController *r){
        roomsController = r;
    }
    Q_INVOKABLE
    void assignPersonToRoom(QString personID, QString roomID);

private:
    // TODO: make interfaces for these controllers -> loose coupling
    PersonsController* personController;
    RoomsController* roomsController;
};

#endif /* MEDIATORCONTROLLER_H_ */
