#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QSerialPortInfo>
#include <QSerialPort>

QSerialPort* findPort();

qint64 writeReset(QSerialPort& port);

qint64 writeReadBDAddr(QSerialPort& port);

bool validToConvertToBDAddr(QString& input);

QByteArray convertBDAddr(const QString& input);

qint64 writeWriteBDAddr(QSerialPort& port, QByteArray& addr);

#endif // COMMUNICATION_H
