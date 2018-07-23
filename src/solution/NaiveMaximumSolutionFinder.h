/*
 * NaiveSolutionFinder.h
 *
 *  Created on: 6 lis 2015
 *      Author: Kamil
 */

#ifndef NAIVESOLUTIONFINDER_H_
#define NAIVESOLUTIONFINDER_H_

#include "src/interfaces/ISolutionFinder.h"
#include <QObject>

class NaiveMaximumSolutionFinder: public QObject, public ISolutionFinder
{
    Q_OBJECT
    Q_INTERFACES(ISolutionFinder)
public:
    NaiveMaximumSolutionFinder(QObject *parent = 0);
    virtual ~NaiveMaximumSolutionFinder();
    void findSolution(const QList<Group*> & groups, const QList<Room*> & rooms);
    signals:
    void problemSolved();
};

#endif /* NAIVESOLUTIONFINDER_H_ */
