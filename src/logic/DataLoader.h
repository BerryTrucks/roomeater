/*
 * DataLoader.h
 *
 *  Created on: 2 lis 2015
 *      Author: Kamil
 */

#ifndef DATALOADER_H_
#define DATALOADER_H_

#include <QObject>

class DataLoader : public QObject
{
Q_OBJECT
public slots:
    void loadData();
public:
    DataLoader(QObject *parent = 0);
    virtual ~DataLoader();
    QString getData();
    void setDataFile(QString & fileName);
signals:
    void dataLoadedFromFile(QString data);
private:
    QString m_fileName;
};

#endif /* DATALOADER_H_ */
