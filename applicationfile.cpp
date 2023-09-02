#include "applicationfile.h"

ApplicationFile::ApplicationFile(QObject *parent)
    : QObject{parent}
{

}

void ApplicationFile::block() {

}

void ApplicationFile::unblock(QString pass) {

}

void ApplicationFile::setUnblockPass(QString pass) {

}

void ApplicationFile::setBlockTime(int time) {

}

bool ApplicationFile::isBlocked() {
    return _blocked;
}
