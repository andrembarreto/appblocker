#include "applicationfile.h"
#include "wrongpassexception.h"

ApplicationFile::ApplicationFile(std::filesystem::path filePath, QObject *parent) : QObject{parent}, _path(filePath) {
    _blockTime = 0;
    _blocked = false;
    _permissions = QFile::permissions(_path);

    _unblockThread = new QThread;
    _worker = new UnblockWorker(_permissions, _path);
    _worker->moveToThread(_unblockThread);

    QObject::connect(this, &ApplicationFile::unblockRequest, _worker, &UnblockWorker::unblockAfterInterval, Qt::QueuedConnection);
    QObject::connect(this, &ApplicationFile::changeBlockTimeRequest, _worker, &UnblockWorker::setBlockInterval, Qt::QueuedConnection);
    QObject::connect(_worker, &UnblockWorker::unblocked, this, &ApplicationFile::setBlockStatusFalse, Qt::QueuedConnection);

    _unblockThread->start();
}

void ApplicationFile::setBlockStatusFalse() {
    _blocked = false;
}

void ApplicationFile::block() {
    QFileDevice::Permissions blockExecPermissions = _permissions & 0xfeff; // removing exe permission
    QFile file(_path);
    file.setPermissions(blockExecPermissions);
    _blocked = true;

    if(_blockTime) {
        emit unblockRequest();
    }
}

void ApplicationFile::unblock(std::filesystem::path path, QFileDevice::Permissions permissions, bool &blockStatus) {
    if(!blockStatus) return; // might have been unblocked with pass before timer fires

    QFile file(path);
    file.setPermissions(permissions);
    blockStatus = false;
}

void ApplicationFile::unblock(QString pass) {
    if(pass == _unblockPass) unblock(_path, _permissions, _blocked);
    else throw WrongPassException();
}

void ApplicationFile::setUnblockPass(QString pass) {
    _unblockPass = pass;
}

void ApplicationFile::setBlockTime(int time) {
    _blockTime = time;
    emit changeBlockTimeRequest(_blockTime);
}

bool ApplicationFile::isBlocked() {
    return _blocked;
}
