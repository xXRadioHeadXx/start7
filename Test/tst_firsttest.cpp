#include <QtTest>

// add necessary includes here

class FirstTest : public QObject
{
    Q_OBJECT

public:
    FirstTest();
    ~FirstTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

FirstTest::FirstTest()
{

}

FirstTest::~FirstTest()
{

}

void FirstTest::initTestCase()
{

}

void FirstTest::cleanupTestCase()
{

}

void FirstTest::test_case1()
{

}

QTEST_APPLESS_MAIN(FirstTest)

#include "tst_firsttest.moc"
