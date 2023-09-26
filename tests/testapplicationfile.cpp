#include <QTest>

#include "applicationfile.h"
#include "wrongpassexception.h"

class TestApplicationFile: public QObject
{
    Q_OBJECT
    ApplicationFile *appFile;
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

    appFile = new ApplicationFile(testFile.filesystemFileName());
}

void TestApplicationFile::cleanup() {
    delete appFile;
    QFile::remove("testFile");
}

void TestApplicationFile::canBlock() {
    appFile->block();
    QVERIFY(appFile->isBlocked());
}

void TestApplicationFile::canUnblockWithCorrectPass() {
    QString pass = "pass123";
    appFile->setUnblockPass(pass);
    appFile->block();
    appFile->unblock(pass);
    QVERIFY(!appFile->isBlocked());
}

void TestApplicationFile::shouldThrowWrongPassException() {
    QString pass = "pass123";
    appFile->setUnblockPass(pass);
    appFile->block();
    QVERIFY_THROWS_EXCEPTION(WrongPassException, appFile->unblock(pass+"a"));
}

void TestApplicationFile::unblocksAfterSetPeriod() {
    appFile->setBlockTime(5);
    appFile->block();
    QTRY_COMPARE_EQ_WITH_TIMEOUT(appFile->isBlocked(), false, 5);
}

QTEST_MAIN(TestApplicationFile)

#include "testapplicationfile.moc"
