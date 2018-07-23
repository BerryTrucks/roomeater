/*
 * Solver.cpp
 *
 *  Created on: 6 lis 2015
 *      Author: Kamil
 */

#include <src/solution/Solver.h>
#include "NaiveMaximumSolutionFinder.h"
#include "NaiveMinimalSolutionFinder.h"
#include "NaiveBothSidesSolutionFinder.h"
#include "NaiveWithFeeSolutionFinder.h"
#include "NaiveCouplesTogetherSolutionFinder.h"

Solver::Solver(QObject *parent)
{
    // TODO Auto-generated constructor stub
    m_solutionFinder = NULL;
    setSolution(-1);
}

Solver::~Solver()
{
    // TODO Auto-generated destructor stub
}

void Solver::solveProblem(const QList<Group*>& groups, const QList<Room*>& rooms)
{
    if (groups.length() == 0 || rooms.length() == 0){
        qWarning()<< "Trying to solve the problem with empty groups or rooms!" << endl;
        return;
    }
    if (m_solutionFinder != NULL){
        m_solutionFinder->findSolution(groups, rooms);
    }
    delete &rooms;
    emit problemSolved();
}

void Solver::setSolution(int solutionNr)
{
    if (m_solutionFinder){
        qDebug() << "Removing existing solution finder";
        delete m_solutionFinder;
        m_solutionFinder = NULL;
    }
    switch (solutionNr) {
        case 0:
            m_solutionFinder = new NaiveMinimalSolutionFinder();
            break;
        case 1:
            m_solutionFinder = new NaiveMaximumSolutionFinder();
            break;
        case 2:
            m_solutionFinder = new NaiveBothSidesSolutionFinder();
            break;
        case 3:
            m_solutionFinder = new NaiveWithFeeSolutionFinder();
            break;
        case 4:
            m_solutionFinder = new NaiveCouplesTogetherSolutionFinder();
            break;
        default:
            m_solutionFinder = new NaiveWithFeeSolutionFinder();
            break;
    }

    QObject *obj = dynamic_cast<QObject*>(m_solutionFinder);
    qDebug() << "New solution finder = " + QString("%1").arg(obj->metaObject()->className());
}
