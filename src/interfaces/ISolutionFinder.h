/*
 * SolutionFinder.h
 *
 *  Created on: 6 lis 2015
 *      Author: Kamil
 */

#ifndef SOLUTIONFINDER_H_
#define SOLUTIONFINDER_H_

#include "src/model/Group.h"

class ISolutionFinder
{
public:
    ISolutionFinder(){};
    virtual ~ISolutionFinder(){};
    virtual void findSolution(const QList<Group*> & groups, const QList<Room*> & rooms) = 0;
signals:
    virtual void problemSolved() = 0;
};

Q_DECLARE_INTERFACE(ISolutionFinder, "ISolutionFinder")

#endif /* SOLUTIONFINDER_H_ */
