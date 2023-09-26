#include "unblockworker.h"

UnblockWorker::UnblockWorker(QFileDevice::Permissions permissions, std::filesystem::path path,
                             QObject *parent)
    : QObject{parent}
{
    _path = path;
    _permissions = permissions;
    _interval = 0;
}

void UnblockWorker::unblockAfterInterval() {
    std::this_thread::sleep_for(std::chrono::milliseconds(_interval));
    QFile file(_path);
    file.setPermissions(_permissions);
    emit unblocked();
}

void UnblockWorker::setBlockInterval(int interval) {
    _interval = interval;
}
