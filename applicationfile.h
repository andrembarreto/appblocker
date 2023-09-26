#ifndef APPLICATIONFILE_H
#define APPLICATIONFILE_H

#include <QObject>
#include <QFile>
#include <QThread>

#include "unblockworker.h"

class ApplicationFile : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationFile(std::filesystem::path filePath, QObject *parent = nullptr);
    bool isBlocked();

public slots:
    void block();
    void unblock(QString pass);
    void setUnblockPass(QString pass);
    void setBlockTime(int time);
    static void unblock(std::filesystem::path path, QFileDevice::Permissions permissions, bool &blockStatus);
    void setBlockStatusFalse();

signals:
    void unblockRequest();
    void changeBlockTimeRequest(int blockTime);

private:
    QString _name;
    QFileDevice::Permissions _permissions;
    const std::filesystem::path _path;
    QString _unblockPass;
    bool _blocked;
    int _blockTime; // ms
    QThread *_unblockThread;
    UnblockWorker *_worker;
};

#endif // APPLICATIONFILE_H
