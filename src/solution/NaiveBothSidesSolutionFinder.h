/*
 * NaiveBothSidesSolutionFinder.h
 *
 *  Created on: 9 lis 2015
 *      Author: Kamil
 */

#ifndef NAIVEBOTHSIDESSOLUTIONFINDER_H_
#define NAIVEBOTHSIDESSOLUTIONFINDER_H_

#include "src/interfaces/ISolutionFinder.h"
#include <QObject>

class NaiveBothSidesSolutionFinder: public QObject, public ISolutionFinder
{
    Q_OBJECT
    Q_INTERFACES(ISolutionFinder)
public:
    NaiveBothSidesSolutionFinder(QObject *parent = 0);
    virtual ~NaiveBothSidesSolutionFinder();
    void findSolution(const QList<Group*> & groups, const QList<Room*> & rooms);
    signals:
    void problemSolved();
};

#endif /* NAIVEBOTHSIDESSOLUTIONFINDER_H_ */
