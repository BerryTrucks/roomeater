/*
 * DataLoader.cpp
 *
 *  Created on: 2 lis 2015
 *      Author: Kamil
 */

#include <src/logic/DataLoader.h>
#include <QFile>
#include <QTextStream>
#include <QtDebug>

DataLoader::DataLoader(QObject *parent)
{
    m_fileName = "16Jan16";
}

void DataLoader::loadData(){
    qDebug() << "Slot reached" << endl;
    emit dataLoadedFromFile(getData());
}

DataLoader::~DataLoader()
{
    // TODO Auto-generated destructor stub
}

QString DataLoader::getData()
{
    QString result;
    QString path = QString("app/native/assets/data/%1.txt").arg(m_fileName);
    QFile textFile(path);
    if (textFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&textFile);
        QString line;
        do {
            line = in.readLine();
            result += line + QString("\n");
        } while (!line.isNull());
    }else{
        qDebug() << "Cannot open file" << endl;
    }
    textFile.close();
    return result;
}

void DataLoader::setDataFile(QString& fileName)
{
    m_fileName = fileName;
}
