#ifndef APPLICATIONFILE_H
#define APPLICATIONFILE_H

#include <QObject>
#include <QFile>

class ApplicationFile : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationFile(QObject *parent = nullptr);
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
    std::filesystem::path _path;
    QString _unblockPass;
    bool _blocked;
    int _blockTime; // ms
};

#endif // APPLICATIONFILE_H
