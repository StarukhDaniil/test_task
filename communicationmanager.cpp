#include "communicationmanager.h"
#include "communication.h"
#include "mainwindow.h"
#include "myconstants.h"

CommunicationManager::CommunicationManager(MainWindow& mainWindow, QObject *parent)
    : QObject{parent}
    , port(findPort(this))
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
        QObject::connect(ownThread, &QThread::finished, port, &QObject::deleteLater);
    }
    ownThread->start();

    // QObject::connect(ownThread, &QThread::finished, this, &QObject::deleteLater);
    // QObject::connect(ownThread, &QThread::finished, port, &QObject::deleteLater);
    // QObject::connect(ownThread, &QThread::finished , ownThread, &QObject::deleteLater);

    // connecting buttons with their functionality
    QObject::connect(resetBtn, &QPushButton::clicked,
                     this, &CommunicationManager::reset, Qt::QueuedConnection);
    QObject::connect(readBDAddrBtn, &QPushButton::clicked,
                     this, &CommunicationManager::readBDAddr, Qt::QueuedConnection);
    QObject::connect(&mainWindow, &MainWindow::writeBDAddr,
                     this, &CommunicationManager::writeBDAddr, Qt::QueuedConnection);

    // connecting reading output from controller with displaying output
    QObject::connect(this, &CommunicationManager::writeResponse,
                     &mainWindow, &MainWindow::writeResponse, Qt::QueuedConnection);
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

    // checking if the port is opened
    if (!port->isOpen()) {
        emit writeResponse("Error: port is closed");
        return;
    }

    // asking controller for reading BD_ADDR
    writeReset(*port);

    // checking if controller responded and waiting for it to sends expected number of bytes
    while (port->bytesAvailable() < myConstants::expectedResetResponseLen) {
        if (!port->waitForReadyRead(1000)) {
            emit writeResponse("Failed to read :(");
            return;
        }
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


    // checking if the port is opened
    if (!port->isOpen()) {
        emit writeResponse("Error: port is closed");
        return;
    }

    // asking controller for reading BD_ADDR
    writeReadBDAddr(*port);

    // checking if controller responded and waiting for it to sends expected number of bytes
    while (port->bytesAvailable() < myConstants::expectedReadBDAddrResponseLen) {
        if (!port->waitForReadyRead(1000)) {
            emit writeResponse("Failed to read :(");
            return;
        }
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

    // checking if the port is opened
    if (!port->isOpen()) {
        emit writeResponse("Error: port is closed");
        return;
    }

    // checking if the entered input is valid for converting to BD_ADDR
    if (!validToConvertToBDAddr(input)) {
        emit writeResponse("Incorrect input");
        return;
    }

    // asking controller for reading BD_ADDR
    writeWriteBDAddr(*port, convertBDAddr(input));

    // checking if controller responded and waiting for it to sends expected number of bytes
    while (port->bytesAvailable() < myConstants::expectedWriteBDAddrResponseLen) {
        if (!port->waitForReadyRead(1000)) {
            emit writeResponse("Failed to read :(");
            return;
        }
    }

    // asking to write response
    emit writeResponse(port->readAll().toHex(' '));
}

CommunicationManager::~CommunicationManager() {
    ownThread->wait();
    ownThread->quit();
    delete ownThread;
}
