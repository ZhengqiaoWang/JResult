#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "JResult/JResult.h"
#include "doctest.h"

class TestClass
{
public:
    TestClass() { printf("ctor, copy: %d, mov: %d\n", copy_count, mov_count); }
    TestClass(const TestClass &other) : copy_count(other.copy_count + 1), mov_count(other.mov_count)
    {
        printf("copy ctor, copy: %d, mov: %d\n", copy_count, mov_count);
    }
    TestClass(TestClass &&other) : copy_count(other.copy_count), mov_count(other.mov_count + 1)
    {
        printf("mov ctor, copy: %d, mov: %d\n", copy_count, mov_count);
    }

public:
    int copy_count{0};
    int mov_count{0};

public:
    void printCount() const
    {
        printf("copy: %d, mov: %d\n", copy_count, mov_count);
    }
};

TEST_CASE("test TestClass")
{
    TestClass tc;
    tc.printCount();
    CHECK(tc.copy_count == 0);
    CHECK(tc.mov_count == 0);

    SUBCASE("copy")
    {
        TestClass tc2(tc);
        tc2.printCount();
        CHECK(tc2.copy_count == 1);
        CHECK(tc2.mov_count == 0);
    }

    SUBCASE("move")
    {
        TestClass tc2(std::move(tc));
        tc2.printCount();
        CHECK(tc2.copy_count == 0);
        CHECK(tc2.mov_count == 1);
    }
}

TEST_CASE("test success")
{
    auto r = JResult<TestClass, std::string>::success(TestClass());
    CHECK(r.isSuccess());
    CHECK(r.isFailure() == false);
    CHECK(r.getSuccessPtr()->copy_count == 0);
    CHECK(r.getSuccessPtr()->mov_count == 1);
    CHECK(r.getFailurePtr() == nullptr);
}

TEST_CASE("test failure")
{
    auto r = JResult<TestClass, std::string>::failure("error");
    CHECK(r.isSuccess() == false);
    CHECK(r.isFailure());
    CHECK(r.getSuccessPtr() == nullptr);
    CHECK(r.getFailurePtr()->compare("error") == 0);
}

TEST_CASE("test operator =")
{
    printf("test operator =\n");
    SUBCASE("copy")
    {
        printf("copy\n");
        SUBCASE("success")
        {
            printf("success\n");
            auto r = JResult<long, TestClass>::success(1);
            JResult<double, TestClass> l = r;
            CHECK(l.isSuccess());
            CHECK(l.isFailure() == false);
            CHECK(*l.getSuccessPtr() == 1);
            CHECK(l.getFailurePtr() == nullptr);
        }
        SUBCASE("failure")
        {
            printf("failure\n");
            auto r = JResult<long, TestClass>::failure(std::move(TestClass()));
            JResult<double, TestClass> l = r;
            CHECK(l.isSuccess() == false);
            CHECK(l.isFailure());
            CHECK(l.getSuccessPtr() == nullptr);
            CHECK(l.getFailurePtr()->copy_count == 1);
            CHECK(l.getFailurePtr()->mov_count == 1);
            l.getFailurePtr()->printCount();
        }
    }
    SUBCASE("move")
    {
        printf("move\n");
        SUBCASE("success")
        {
            printf("success\n");
            auto r = JResult<long, TestClass>::success(1);
            JResult<double, TestClass> l = std::move(r);
            CHECK(l.isSuccess());
            CHECK(l.isFailure() == false);
            CHECK(*l.getSuccessPtr() == 1);
            CHECK(l.getFailurePtr() == nullptr);
        }
        SUBCASE("failure")
        {
            printf("failure\n");
            auto r = JResult<long, TestClass>::failure(std::move(TestClass()));
            JResult<double, TestClass> l = std::move(r);
            CHECK(l.isSuccess() == false);
            CHECK(l.isFailure());
            CHECK(l.getSuccessPtr() == nullptr);
            CHECK(l.getFailurePtr()->copy_count == 0);
            CHECK(l.getFailurePtr()->mov_count == 2);
            l.getFailurePtr()->printCount();
        }
    }
}