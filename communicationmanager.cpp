#include "communicationmanager.h"
#include "communication.h"
#include "mainwindow.h"

CommunicationManager::CommunicationManager(MainWindow& mainWindow, QObject *parent)
    : QObject{parent}
    , port(findPort())
    , resetBtn(mainWindow.getResetBtn())
    , readBDAddrBtn(mainWindow.getReadBDAddrBtn())
    , writeBDAddrBtn(mainWindow.getWriteBDAddrBtn())
    , output(mainWindow.getOutput())
    , input(mainWindow.getInput())
    , mainWindow(&mainWindow)
    , ownThread(new QThread(this))
{
    /* moving communication manager and port to its own thread,
     * so there is no lag in uiwhen waiting for response */
    this->moveToThread(ownThread);
    if (port != nullptr) {
        port->moveToThread(ownThread);
    }
    ownThread->start();

    // connecting buttons with their functionality
    QObject::connect(resetBtn, &QPushButton::clicked,
                     this, &CommunicationManager::reset, Qt::QueuedConnection);
    QObject::connect(readBDAddrBtn, &QPushButton::clicked,
                     this, &CommunicationManager::readBDAddr, Qt::QueuedConnection);
    QObject::connect(&mainWindow, &MainWindow::writeBDAddr,
                     this, &CommunicationManager::writeBDAddr, Qt::QueuedConnection);

    // connecting reading output from controller with displaying output
    QObject::connect(this, &CommunicationManager::writeResponse,
                     &mainWindow, &MainWindow::writeResponse);
}


void CommunicationManager::reset() {
    // checking if the port is found
    if (port == nullptr) {

        // if the port is not found, trying to find again
        port = findPort();
        if (port == nullptr) {
            emit writeResponse("Failed to find the controller");
            return;
        }

        // if port is successfullt found, adding it to own thread
        port->moveToThread(ownThread);
    }

    // asking controller for reading BD_ADDR
    writeReset(*port);

    // checking if controller responded
    if (!port->waitForReadyRead(1000)) {
        emit writeResponse("Failed to read :(");
        return;
    }

    // asking to write response
    emit writeResponse(port->readAll().toHex(' '));
}

void CommunicationManager::readBDAddr() {
    // checking if the port is found
    if (port == nullptr) {

        // if the port is not found, trying to find again
        port = findPort();
        if (port == nullptr) {
            emit writeResponse("Failed to find the controller");
            return;
        }

        // if port is successfullt found, adding it to own thread
        port->moveToThread(ownThread);
    }

    // asking controller for reading BD_ADDR
    writeReadBDAddr(*port);

    // checking if controller responded
    if (!port->waitForReadyRead(1000)) {
        emit writeResponse("Failed to read :(");
        return;
    }

    // asking to write response
    emit writeResponse(port->readAll().toHex(' '));
}

void CommunicationManager::writeBDAddr(const QString& input) {
    // checking if the port is found
    if (port == nullptr) {

        // if the port is not found, trying to find again
        port = findPort();
        if (port == nullptr) {
            emit writeResponse("Failed to find the controller");
            return;
        }

        // if port is successfullt found, adding it to own thread
        port->moveToThread(ownThread);
    }
    if (!validToConvertToBDAddr(input)) {
        emit writeResponse("Incorrect input");
        return;
    }

    // asking controller for reading BD_ADDR
    writeWriteBDAddr(*port, convertBDAddr(input));

    // checking if controller responded
    if (!port->waitForReadyRead(1000)) {
        emit writeResponse("Failed to read :(");
        return;
    }

    // asking to write response
    emit writeResponse(port->readAll().toHex(' '));
}

CommunicationManager::~CommunicationManager() {
    ownThread->quit();
    ownThread->wait();
    port->close();
    delete port;
}
