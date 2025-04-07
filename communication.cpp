#include "communication.h"
#include "myconstants.h"
#include <QList>
#include <QSerialPort>
#include <QTime>
#include <QRegularExpression>
#include <QSerialPortInfo>
#include <QThread>

// checks if the string is valid for converting it to BD_ADDR
bool validToConvertToBDAddr(const QString& input) {
    if (input.length() != 12 || !input.contains(QRegularExpression("^[0-9A-Fa-f]{12}$"))) {
        return false;
    }
    return true;
}

// function that converts string input to address in bytes
QByteArray convertBDAddr(const QString& input) {
    QByteArray addr = QByteArray::fromHex(input.toUtf8());
    std::reverse(addr.begin(), addr.end());
    return addr;
}

// sends required bytes for reset
qint64 writeReset(QSerialPort& port) {
    if (!port.isOpen()) {
        qDebug() << "Failed to write: port is non opened," << QTime::currentTime();
        return -1;
    }

    // declaring and initializing command to send
    static const char command[] = {0x01, 0x03, 0x0C, 0x00};
    return port.write(command, myConstants::basicCmdLen);
}

// sends required bytes for reading the BD_ADDR
qint64 writeReadBDAddr(QSerialPort& port) {
    if (!port.isOpen()) {
        qDebug() << "Failed to write: port is non opened," << QTime::currentTime();
        return -1;
    }

    // declaring and initializing command to send
    static const char command[] = {0x01, 0x09, 0x10, 0x00};
    return port.write(command, myConstants::basicCmdLen);
}

qint64 writeWriteBDAddr(QSerialPort& port, const QByteArray& addr) {
    if (!port.isOpen()) {
        qDebug() << "Failed to write: port is non opened," << QTime::currentTime();
        return -1;
    }

    // declaring and partly initializing command to send
    static char command[myConstants::basicCmdLen + myConstants::BDAddrLen]
        = {0x01, 0x01, static_cast<char>(0xFC), 0x06};

    // pointer to part of message that is responsible for address
    char* cmdAddrPtr = command + myConstants::basicCmdLen;

    // copying address to message
    for (qint16 i = 0; i < myConstants::BDAddrLen; ++i) {
        cmdAddrPtr[i] = addr[i];
    }

    return port.write(command, myConstants::basicCmdLen + myConstants::BDAddrLen);
}

QSerialPort* findPort(QObject* parent) {

    // creating list of available ports
    QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();

    // initializing and adjusting port that will be returned
    QSerialPort* port = new QSerialPort(parent);
    port->setBaudRate(QSerialPort::Baud115200);
    port->setDataBits(QSerialPort::Data8);
    port->setFlowControl(QSerialPort::HardwareControl);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);

    // finding required port
    for (auto portInfoIt = availablePorts.cbegin(); portInfoIt != availablePorts.cend(); ++portInfoIt) {
        if (portInfoIt->vendorIdentifier() == myConstants::requiredVendorIdentifier
            && portInfoIt->productIdentifier() == myConstants::requiredProductIdentifier)
        {
            port->setPort(*portInfoIt);

            // opening the port and checking if the port was failed to open
            if (!port->open(QSerialPort::ReadWrite)) {
                qDebug() << "Failed to open the port" << port->portName();
                continue;
            }

            // checking if host failed to write bytes
            if (writeReset(*port) != 4) {
                qDebug() << "Failed to send :(" << port->portName();
                port->close();
                continue;
            }

            // checking if controller responded and waiting for it to sends expected number of bytes
            while (port->bytesAvailable() < myConstants::expectedResetResponseLen) {
                if (!port->waitForReadyRead(1000)) {
                    port->close();
                    continue;
                }
            }

            // clearing read buffer
            port->clear();

            return port;
        }
    }

    delete port;
    return nullptr;
}
