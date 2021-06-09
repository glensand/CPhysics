#include "Test.h"

bool Test::IsPassed() const
{
    return m_passed;
}

void Test::Assert(bool expressionResult)
{
    m_passed &= expressionResult;
}

GlobalTest::~GlobalTest()
{
    for (auto* test : m_tests)
        delete test;
}

GlobalTest& GlobalTest::Instance()
{
    static GlobalTest instance;
    return instance;
}

void GlobalTest::Run()
{
    for (auto* test : m_tests)
    {
        test->Run();
        std::cout << (test->IsPassed() ? "Passed" : "Failed") << std::endl;
    }
}

bool GlobalTest::RegisterTest(Test* test)
{
    m_tests.push_back(test);
    return true;
}
