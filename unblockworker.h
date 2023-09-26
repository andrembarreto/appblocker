#ifndef UNBLOCKWORKER_H
#define UNBLOCKWORKER_H

#include <QObject>
#include <QFile>
#include <thread>
#include <chrono>

class UnblockWorker : public QObject
{
    Q_OBJECT
public:
    explicit UnblockWorker(QFileDevice::Permissions permissions, std::filesystem::path path,
                           QObject *parent = nullptr);

signals:
    void unblocked();

public slots:
    void setBlockInterval(int interval);
    void unblockAfterInterval();

private:
    QFileDevice::Permissions _permissions;
    std::filesystem::path _path;
    int _interval;
};

#endif // UNBLOCKWORKER_H
