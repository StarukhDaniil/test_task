#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QSerialPort>
#include <QString>
#include <QByteArray>

QSerialPort* findPort();

qint64 writeReset(QSerialPort& port);

qint64 writeReadBDAddr(QSerialPort& port);

bool validToConvertToBDAddr(const QString& input);

QByteArray convertBDAddr(const QString& input);

qint64 writeWriteBDAddr(QSerialPort& port, const QByteArray& addr);

#endif // COMMUNICATION_H
