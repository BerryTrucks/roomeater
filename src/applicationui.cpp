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

#include "applicationui.hpp"
#include "logic/ListParser.h"
#include "controllers/MediatorController.h"
#include "solution/NaiveMaximumSolutionFinder.h"
#include "solution/NaiveMinimalSolutionFinder.h"
#include "solution/NaiveBothSidesSolutionFinder.h"
#include "solution/NaiveWithFeeSolutionFinder.h"
#include "solution/NaiveCouplesTogetherSolutionFinder.h"
#include <QDebug>
#include <bb/cascades/Application>
#include <bb/cascades/LocaleHandler>

using namespace bb::cascades;

ApplicationUI::ApplicationUI() :
        QObject()
{
    // prepare the localization
    m_pTranslator = new QTranslator(this);
    m_pLocaleHandler = new LocaleHandler(this);

    bool res = QObject::connect(m_pLocaleHandler, SIGNAL(systemLanguageChanged()), this, SLOT(onSystemLanguageChanged()));
    // This is only available in Debug builds
    Q_ASSERT(res);
    // Since the variable is not used in the app, this is added to avoid a
    // compiler warning
    Q_UNUSED(res);

    // initial load
    onSystemLanguageChanged();

    // Create scene document from main.qml asset, the parent is set
    // to ensure the document gets destroyed properly at shut down.
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
    personsController = new PersonsController();
    qml->setContextProperty("_people", personsController);

    roomsController = new RoomsController();
    qml->setContextProperty("_room", roomsController);

    MediatorController *mediator = new MediatorController(this);
    mediator->setPersonController(personsController);
    mediator->setRoomController(roomsController);
    qml->setContextProperty("_mediator", mediator);

    solver = new Solver(this);

    QObject::connect(solver, SIGNAL(problemSolved()), personsController, SLOT(updateView()));
    QObject::connect(solver, SIGNAL(problemSolved()), roomsController, SLOT(updateView()));
    QObject::connect(solver, SIGNAL(problemSolved()), this, SLOT(stopIndicator()));



    QObject::connect(personsController, SIGNAL(updateOtherViews()), roomsController, SLOT(updateView()));
    QObject::connect(roomsController, SIGNAL(updateOtherViews()), personsController, SLOT(updateView()));
    qml->setContextProperty("_app", this);

    // Create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();
    textView = root->findChild<QObject*>("dataToParse");

    QObject* assignAction = root->findChild<QObject*>("assign");
    if (assignAction){
        bool result = QObject::connect(assignAction, SIGNAL(onAction()), this, SLOT(tryToSolve()));
        qDebug()<< "Connection Assign result = " << result << endl;
    }else{
        qDebug() << "ASSIGN NOT FOUND" << endl;
    }

    dataLoader = new DataLoader(this);
    ListParser* listParser = new ListParser(this);

    if (!QObject::connect(listParser, SIGNAL(parsingProblemsUpdate(QString)), this, SLOT(showMessageToUser(QString)))){
        qWarning() << "Could not connect {updateStatus} to {showMessageToUser}";
    }

    QObject::connect(listParser, SIGNAL(peopleFound(QList<Person*>)), personsController , SLOT(assignPeople(QList<Person*>)));
    QObject::connect(dataLoader, SIGNAL(dataLoadedFromFile(QString)), this, SLOT(updateTextView(QString)));

    if (textView){
        bool result = QObject::connect(textView, SIGNAL(passDataToParse(QString)), listParser, SLOT(extractPeople(QString)));
        qDebug() << "Connection textView PassDataToParse result = " << result << endl;
    }else{
        qDebug() << "TEXTVIEW NOT FOUND" << endl;
    }
//    QObject *parseAction = root->findChild<QObject*>("assign");
//    if (parseAction){
//        bool result = QObject::connect(parseAction, SIGNAL(onTrigg()), listParser, SLOT(extractPerson(QString)));
//        qDebug() << "Connection Parse result = " << result;
//    }else{
//        qDebug() << "ASSIGN NOT FOUND";
//    }

    QObject *loadBtn = root->findChild<QObject*>("loadBtn");
    if (loadBtn){
        bool result = QObject::connect(loadBtn, SIGNAL(clicked()), dataLoader, SLOT(loadData()));
        qDebug() << "Connection Load = " << result << endl;
    }else{
        qDebug() <<"LOAD NOT FOUND";
    }

    rootContainer = root->findChild<QObject*>("root");
    if (!rootContainer){
        qDebug() << "ROOT CONTAINER NOT FOUND";
    }

    Application::instance()->setScene(root);
    // Set created root object as the application scene
}

void ApplicationUI::updateTextView(QString data){
    QMetaObject::invokeMethod(textView, "updateContent", Q_ARG(QVariant, data));
}


void ApplicationUI::onSystemLanguageChanged()
{
    QCoreApplication::instance()->removeTranslator(m_pTranslator);
    // Initiate, load and install the application translation files.
    QString locale_string = QLocale().name();
    QString file_name = QString("MoockupRoomsAssignement_%1").arg(locale_string);
    if (m_pTranslator->load(file_name, "app/native/qm")) {
        QCoreApplication::instance()->installTranslator(m_pTranslator);
    }
}

void ApplicationUI::stopIndicator()
{
    QMetaObject::invokeMethod(rootContainer, "activityDone");
}

void ApplicationUI::tryToSolve()
{
    qDebug() << "Trying to solve problem" << endl;
    solver->solveProblem(personsController->getGroups(), roomsController->getAvailableRooms());
}

void ApplicationUI::setSolver(int option)
{
    roomsController->clearAllRooms();
    qDebug() << "Setting solution finder to option " << option << endl;
    solver->setSolution(option);
}

void ApplicationUI::setDataFile(QString fileName)
{
    dataLoader->setDataFile(fileName);
}
void ApplicationUI::showMessageToUser(QString message)
{
    qDebug() << message;
    QMetaObject::invokeMethod(rootContainer, "showToast", Q_ARG(QVariant, message));
}
