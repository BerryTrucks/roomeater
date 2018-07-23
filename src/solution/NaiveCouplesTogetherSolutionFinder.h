/*
 * NaiveCouplesTogetherSolutionFinder.h
 *
 *  Created on: 10 lis 2015
 *      Author: Kamil
 */

#ifndef NAIVECOUPLESTOGETHERSOLUTIONFINDER_H_
#define NAIVECOUPLESTOGETHERSOLUTIONFINDER_H_

#include "src/interfaces/ISolutionFinder.h"
#include <QObject>

class NaiveCouplesTogetherSolutionFinder: public QObject, public ISolutionFinder
{
    Q_OBJECT
    Q_INTERFACES(ISolutionFinder)
public:
    NaiveCouplesTogetherSolutionFinder(QObject *parent = 0);
    virtual ~NaiveCouplesTogetherSolutionFinder();
    void findSolution(const QList<Group*> & groups, const QList<Room*> & rooms);
    signals:
    void problemSolved();
};

#endif /* NAIVECOUPLESTOGETHERSOLUTIONFINDER_H_ */
