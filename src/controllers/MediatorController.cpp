/*
 * MediatorController.cpp
 *
 *  Created on: 12 lis 2015
 *      Author: Kamil
 */

#include <src/controllers/MediatorController.h>

MediatorController::MediatorController(QObject *parent)
{
    // TODO Auto-generated constructor stub
    personController = NULL;
    roomsController = NULL;
}

MediatorController::~MediatorController()
{
    // TODO Auto-generated destructor stub
}

void MediatorController::assignPersonToRoom(QString personID, QString roomID)
{
    if (personController && roomsController) {
        Person* p = personController->getPerson(personID.toUInt());
        Room* r = roomsController->getRoom(roomID.toUInt());
        if (p && r) {
            if (p->getRoom()){
                QString hashOfRoomThatPersonIsActuallyIn = QString("%1").arg(p->getRoom()->getHash());
                if (hashOfRoomThatPersonIsActuallyIn == roomID) {
                    qDebug() << QString("%1 is already in %2").arg(p->toString()).arg(r->toString());
                    return;
                }
            }
            if (r->getPeopleInRoom() < r->getCapacity()) {
                if (p->getRoom()) {
                    p->leaveRoom();
                }
                p->setRoom(r);
                qDebug() << QString("Assigning %1 to %2").arg(p->getFirstName()).arg(r->toString());
                personController->updateView();
                roomsController->updateView();
            }
        } else {
            qWarning() << QString("Found person{0x%1} or room{0x%2} is null").arg((quintptr) ((p))).arg((quintptr) ((r)));
        }
    } else {
        qWarning() << "Room or person controller is null";
    }
}
