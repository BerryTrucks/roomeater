/*
 * Solver.h
 *
 *  Created on: 6 lis 2015
 *      Author: Kamil
 */

#ifndef SOLVER_H_
#define SOLVER_H_

#include "src/interfaces/ISolutionFinder.h"
#include <QObject>

class Solver: public QObject
{
    Q_OBJECT
public:
    Solver(QObject *parent = 0);
    virtual ~Solver();
    void solveProblem(const QList<Group*> & groups, const QList<Room*> & rooms);

    void setSolution(int solutionNr);
signals:
    void problemSolved();
private:
    ISolutionFinder * m_solutionFinder;
};
#endif /* SOLVER_H_ */
