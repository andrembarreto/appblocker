#include <QTest>
#include <QTimer>
#include <QDir>

#include "applicationfile.h"
#include "wrongpassexception.h"

class TestApplicationFile: public QObject
{
    Q_OBJECT
private slots:
    void init();
    void cleanup();

    void canBlock();
    void canUnblockWithCorrectPass();
    void shouldThrowWrongPassException();
    void unblocksAfterSetPeriod();
};

void TestApplicationFile::init() {
    QFile testFile("testFile");
    if (!testFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QFAIL("Failed to create the file");
    }
    testFile.close();
    testFile.setPermissions(QFileDevice::ExeUser);
}

void TestApplicationFile::cleanup() {
    QFile::remove("testFile");
}

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
    QTest::qSleep(1);
    QVERIFY(!appFile.isBlocked());
}

QTEST_APPLESS_MAIN(TestApplicationFile)

#include "testapplicationfile.moc"

// TODO: ADD FIXTURES TO AVOID CODE DUPLICATION
