/*
 * ListParser.cpp
 *
 *  Created on: 2 lis 2015
 *      Author: Kamil
 */

#include <src/logic/ListParser.h>
#include <QStringList>
#include <QRegExp>
#include <QString>
#include <QtDebug>


static const QString COUPLE_STRING = QString("couple");
static const QString MALE_STRING = QString("male");
static const QString FEMALE_STRING = QString("female");
static const QString YES = QString("ja");
static const QString NO = QString("nein");
static const QString WORDS_SEPARATOR = QString("\\s");
static const QString LINES_SEPARATOR = QString("[\r\n]");

ListParser::ListParser(QObject *parent)
{
    // TODO Auto-generated constructor stub
}

ListParser::~ListParser()
{
    // TODO Auto-generated destructor stub
}

void ListParser::extractPeople(QString data){
    if (data.isNull() || data.isEmpty()){
        qDebug() << "Data is null or empty" << endl;
        return;
    }
    parseInput(data);
}

Person* extractPartCouple(QStringList personRow, QString spouseName){
    Person *p = new Person();
    p->setGender(IMP_COUPLE);
    bool nameDiscovered = false;
    QString personName;
    for (int i = 1; i < personRow.length(); i++){
        QString currentWord = personRow[i];
        // if name hasn't been found
        // and current word does not contain first 3 letters of spouse name
        if  (!nameDiscovered && !currentWord.contains(spouseName.left(3))){
            personName += currentWord + QString(" ");
            continue;
        }else if (!nameDiscovered){
            p->setFirstName(personName);
            nameDiscovered = true;
        }
        if (currentWord.toLower() ==  YES || currentWord.toLower() == NO){
            bool value = false;
            if (currentWord.toLower() == YES){
                value = true;
            }
            if (personRow.length() - i == 3){
                p->setIsSnoorer(value);
            }else if (personRow.length() - i == 2){
                p->setIsAllTakeCourse(value);
            }else if (personRow.length() - i == 1){
                p->setIsDriver(value);
            }
        }
    }
    if (p->getFirstName().isEmpty()){
        delete p;
        return NULL;
    }
    return p;
}

Person* extractPerson(QStringList personRow){
    Person *p = new Person();
    bool nameDiscovered = false;
    QString personName;
    if (personRow.at(0).toLower() == MALE_STRING){
        p->setGender(MALE);
    }else if (personRow.at(0).toLower() == FEMALE_STRING){
        p->setGender(FEMALE);
    }else {
        qWarning() << "This should not happen - person is different than MALE or FEMALE" << endl;
    }
    for (int i = 1; i < personRow.length(); i++){
        QString currentWord = personRow[i];
        bool result = false;
        currentWord.toInt(&result);
        if (result){
            nameDiscovered = true;
            p->setFirstName(personName);
        }
        if (!nameDiscovered){
            personName += currentWord + QString(" ");
        }
        if (currentWord.toLower() ==  YES || currentWord.toLower() == NO){
            bool value = false;
            if (currentWord.toLower() == YES){
                value = true;
            }
            if (personRow.length() - i == 2){
                p->setIsSnoorer(value);
            }else if (personRow.length() - i == 1){
                p->setIsDriver(value);
            }
        }
    }
    if (p->getFirstName() == NULL){
        delete p;
        return NULL;
    }
    return p;
}

void ListParser::parseInput(QString qString)
{
    if (qString.isEmpty()){
        return;
    }
    int CHAR_TO_CONSIDER = 30;
    QString problemLines;
    QList<Person*> * people = new QList<Person*>;
    QStringList rows = qString.split(QRegExp(LINES_SEPARATOR),QString::SkipEmptyParts);
    for (int i = 0; i < rows.length(); i++){
        QString row = rows.at(i);
        if (!rows.at(i).contains(COUPLE_STRING, Qt::CaseInsensitive) && !rows.at(i).contains(FEMALE_STRING, Qt::CaseInsensitive) && !rows.at(i).contains(MALE_STRING, Qt::CaseInsensitive)){
            qDebug() << QString("Line does not contain |%1| OR |%2| OR |%3|").arg(COUPLE_STRING).arg(FEMALE_STRING).arg(MALE_STRING);
            qDebug() << row;
            continue;
        }
        QStringList personWords = row.split(QRegExp(WORDS_SEPARATOR));
        personWords.removeAll("");
        QString firstWordInRow = personWords[0];
        if (firstWordInRow.toLower() == COUPLE_STRING){
            QString spouseRow = rows.at(i+1);
            QStringList spouseWords = spouseRow.split(QRegExp(WORDS_SEPARATOR));
            QString personFirstName = personWords.at(1);
            QString spouseFirstName = spouseWords.at(1);
            Person * person = extractPartCouple(personWords, spouseFirstName);
            if (person == NULL){
                problemLines.append(row.left(CHAR_TO_CONSIDER));
                problemLines.append("\n");
                i++;
                continue;
            }
            Person * spouse = extractPartCouple(spouseWords, personFirstName);
            if (spouse == NULL){
                problemLines.append(row.left(CHAR_TO_CONSIDER));
                problemLines.append("\n");
                delete person;
                i++;
                continue;
            }
            if (!person->isIsAllTakeCOurse() && !person->isIsDriver() && !spouse->isIsAllTakeCOurse() && !spouse->isIsDriver()){
                person->setGender(COUPLE);
                spouse->setGender(COUPLE);
            }
            person->setSpouse(spouse);
            spouse->setSpouse(person);
            qDebug() << "Person in couple " << person->toString() << endl;
            qDebug() << "Spouse in couple " << spouse->toString() << endl;
            people->append(person);
            people->append(spouse);
            i++;
            continue;
        }
        else if (firstWordInRow.toLower() == MALE_STRING || firstWordInRow.toLower() == FEMALE_STRING){
            Person * person = extractPerson(personWords);
            if (person == NULL){
                problemLines.append(row.left(CHAR_TO_CONSIDER));
                problemLines.append("\n");
                continue;
            }
            qDebug() << "Person " << person->toString() << endl;
            people->append(person);
            continue;
        } else{
            problemLines.append(row.left(CHAR_TO_CONSIDER));
            problemLines.append("\n");
            qDebug() << "No such a category" << endl;
        }
    }
    if (!problemLines.isEmpty()){
        emit parsingProblemsUpdate(problemLines);
    }
    if (people->length() == 0){
        delete people;
    }else{
        emit peopleFound((*people));
    }
}
