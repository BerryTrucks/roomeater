/*
 * NaiveWithFeeSolutionFInder.h
 *
 *  Created on: 10 lis 2015
 *      Author: Kamil
 */

#ifndef NAIVEWITHFEESOLUTIONFINDER_H_
#define NAIVEWITHFEESOLUTIONFINDER_H_

#include "src/interfaces/ISolutionFinder.h"
#include <QObject>

class NaiveWithFeeSolutionFinder: public QObject, public ISolutionFinder
{
    Q_OBJECT
    Q_INTERFACES(ISolutionFinder)
public:
    NaiveWithFeeSolutionFinder(QObject *parent = 0);
    virtual ~NaiveWithFeeSolutionFinder();
    void findSolution(const QList<Group*> & groups, const QList<Room*> & rooms);
    signals:
    void problemSolved();
};

#endif /* NAIVEWITHFEESOLUTIONFINDER_H_ */
