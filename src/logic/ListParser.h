/*
 * ListParser.h
 *
 *  Created on: 2 lis 2015
 *      Author: Kamil
 */

#ifndef LISTPARSER_H_
#define LISTPARSER_H_

#include <QObject>
#include "src/model/Person.hpp"


class Person;

class ListParser : public QObject
{
Q_OBJECT

public slots:
    void extractPeople(QString data);
public:
    ListParser(QObject *parent = 0);
    virtual ~ListParser();
signals:
    void peopleFound(QList<Person*> persons);
    void parsingProblemsUpdate(QString rows);
private:
    void parseInput(QString);
//    QList<Person*> m_parsedData;

};

#endif /* LISTPARSER_H_ */
