/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/CPhysics
 */

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cassert>

class Test
{
public:
    virtual ~Test() = default;
    virtual void Run() = 0;
    bool IsPassed() const;

private:
    void Assert(bool expressionResult);
    bool m_passed{ true };
};

class GlobalTest final
{
    using TestList = std::vector<Test*>;
public:
    ~GlobalTest();
    GlobalTest(GlobalTest&) = delete;
    GlobalTest(GlobalTest&&) = delete;
    GlobalTest& operator=(GlobalTest&&) = delete;
    GlobalTest& operator=(GlobalTest&) = delete;

    static GlobalTest& Instance();

    void Run();
    bool RegisterTest(Test* test);

private:
    GlobalTest() = default;
    TestList m_tests;
};

#define TEST_NAME_STR(Name) #Name

#define TEST(GroupName, TestName) \
class GroupName##TestName final : public Test \
{   \
    virtual void Run() override \
    {   \
        std::cout << TEST_NAME_STR(GroupName##TestName) << ": "; \
    }   \
    void RunImpl(); \
};\
static bool GroupName##TestName##_registered = GlobalTest::Instance().RegisterTest(new GroupName##TestName); \
void GroupName##TestName::RunImpl() \

#define OPEN_ASSERT(expression) Assert(expression)