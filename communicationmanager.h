#ifndef COMMUNICATIONMANAGER_H
#define COMMUNICATIONMANAGER_H

#include <QObject>
#include <QPushButton>
#include <QSerialPort>
#include <QThread>
#include <QLineEdit>
#include "mainwindow.h"

/* class that will connect buttons and their functionality
 * to be called not blocking the main thread */
class CommunicationManager : public QObject
{
    Q_OBJECT

public:
    explicit CommunicationManager(MainWindow& mainWindow, QObject *parent = nullptr);
    ~CommunicationManager();

private:
    QSerialPort* port;
    QPushButton* resetBtn;
    QPushButton* readBDAddrBtn;
    QPushButton* writeBDAddrBtn;
    QListWidget* output;
    QLineEdit* input;
    MainWindow* mainWindow;

    QThread* ownThread;

public slots:
    void reset();
    void readBDAddr();
    void writeBDAddr(const QString& input);

signals:
    void writeResponse(const QString& output);
};

#endif // COMMUNICATIONMANAGER_H
