#include <QTest>
#include <QTimer>
#include <QDir>

#include <chrono>
#include <thread>

#include "applicationfile.h"
#include "wrongpassexception.h"

class TestApplicationFile: public QObject
{
    Q_OBJECT
private slots:
    void canBlock();
    void canUnblockWithCorrectPass();
    void shouldThrowWrongPassException();
    void unblocksAfterSetPeriod();
};

void TestApplicationFile::canBlock() {
    ApplicationFile appFile(std::filesystem::path(QString(QDir::currentPath() + "/testFile").toStdString()));
    appFile.block();
    QVERIFY(appFile.isBlocked());
}

void TestApplicationFile::canUnblockWithCorrectPass() {
    ApplicationFile appFile(std::filesystem::path(QString(QDir::currentPath() + "/testFile").toStdString()));
    QString pass = "pass123";
    appFile.setUnblockPass(pass);
    appFile.block();
    appFile.unblock(pass);
    QVERIFY(!appFile.isBlocked());
}

void TestApplicationFile::shouldThrowWrongPassException() {
    ApplicationFile appFile(std::filesystem::path(QString(QDir::currentPath() + "/testFile").toStdString()));
    QString pass = "pass123";
    appFile.setUnblockPass(pass);
    appFile.block();
    QVERIFY_THROWS_EXCEPTION(WrongPassException, appFile.unblock(pass+"a"));
}

void TestApplicationFile::unblocksAfterSetPeriod() {
    ApplicationFile appFile(std::filesystem::path(QString(QDir::currentPath() + "/testFile").toStdString()));
    appFile.setBlockTime(1);
    appFile.block();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    QVERIFY(!appFile.isBlocked());
}

QTEST_APPLESS_MAIN(TestApplicationFile)

#include "tst_testapplicationfile.moc"

// TODO: ADD FIXTURES TO AVOID CODE DUPLICATION
