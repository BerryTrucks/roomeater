/*
 * NaiveMinimalSolutionFinder.h
 *
 *  Created on: 9 lis 2015
 *      Author: Kamil
 */

#ifndef NAIVEMINIMALSOLUTIONFINDER_H_
#define NAIVEMINIMALSOLUTIONFINDER_H_

#include "src/interfaces/ISolutionFinder.h"
#include <QObject>

class NaiveMinimalSolutionFinder: public QObject, public ISolutionFinder
{
    Q_OBJECT
    Q_INTERFACES(ISolutionFinder)
public:
    NaiveMinimalSolutionFinder(QObject *parent = 0);
    virtual ~NaiveMinimalSolutionFinder();
    void findSolution(const QList<Group*> & groups, const QList<Room*> & rooms);
    signals:
    void problemSolved();
};

#endif /* NAIVEMINIMALSOLUTIONFINDER_H_ */
