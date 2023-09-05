#include "applicationfile.h"
#include "wrongpassexception.h"

ApplicationFile::ApplicationFile(std::filesystem::path filePath, QObject *parent) : QObject{parent}, _path(filePath) {
    _blockTime = 0;
    _blocked = false;
    _timer.setSingleShot(true);

    QObject::connect(&_timer, &QTimer::timeout, this, [this](){
        unblock();
    });
}

void ApplicationFile::block() {
    _permissions = QFile::permissions(_path);
    QFileDevice::Permissions blockExecPermissions = _permissions & 0xeeee; // removing exe permission
    QFile file(_path);
    file.setPermissions(blockExecPermissions);
    _blocked = true;

    if(_blockTime) {
        _timer.setInterval(_blockTime);
        _timer.start();
    };
}

void ApplicationFile::unblock() {
    if(!_blocked) return; // might have been unblocked with pass before timer fires

    QFile file(_path);
    file.setPermissions(_permissions);
    _blocked = false;
}

void ApplicationFile::unblock(QString pass) {
    if(pass == _unblockPass) unblock();
    else throw WrongPassException();
}

void ApplicationFile::setUnblockPass(QString pass) {
    _unblockPass = pass;
}

void ApplicationFile::setBlockTime(int time) {
    _blockTime = time;
}

bool ApplicationFile::isBlocked() {
    return _blocked;
}
