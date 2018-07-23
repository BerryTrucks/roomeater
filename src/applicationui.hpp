/*
 * Copyright (c) 2011-2015 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ApplicationUI_HPP_
#define ApplicationUI_HPP_

#include <QObject>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/QmlDocument>
#include "controllers/PersonsController.h"
#include "controllers/RoomsController.h"
#include "src/solution/Solver.h"
#include "logic/DataLoader.h"

namespace bb
{
    namespace cascades
    {
        class LocaleHandler;
    }
}

class QTranslator;

/*!
 * @brief Application UI object
 *
 * Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class ApplicationUI : public QObject
{
    Q_OBJECT
public:
    ApplicationUI();
    virtual ~ApplicationUI() {}
    Q_INVOKABLE void setSolver(int option);
    Q_INVOKABLE void setDataFile(QString fileName);
private slots:
    void onSystemLanguageChanged();
    void updateTextView(QString);
    void stopIndicator();
    void tryToSolve();
    void showMessageToUser(QString message);

private:
    QObject* textView;
    QObject* rootContainer;
    PersonsController* personsController;
    RoomsController* roomsController;
    DataLoader* dataLoader;
    Solver* solver;
    QTranslator* m_pTranslator;
    bb::cascades::LocaleHandler* m_pLocaleHandler;
};

#endif /* ApplicationUI_HPP_ */
