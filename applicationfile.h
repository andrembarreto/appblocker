#ifndef APPLICATIONFILE_H
#define APPLICATIONFILE_H

#include <QObject>
#include <QFile>
#include <QTimer>

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

signals:
    void unblocked();

private:
    void unblock();

    QString _name;
    QFileDevice::Permissions _permissions;
    const std::filesystem::path _path;
    QString _unblockPass;
    bool _blocked;
    int _blockTime; // ms
    QTimer _timer;
};

#endif // APPLICATIONFILE_H
