#include <vector>
#include <memory>
#include <iostream>
#include <sstream>

class TestRegistry;
TestRegistry * getTestRegistry();
class Test;
class TestError;
class TestException;
class TestRunner;

class TestResult
{
public:
	void addError(TestRunner * test, const TestError & error);
	void addException(TestRunner * test, const TestException & exception);
	void addPass(TestRunner * test);
};

class TestException
{
public:
	TestException(const char * message, std::exception & exception);
	std::string message;
	std::exception exception;
};

class TestError
{
public:
	TestError(const char * message, size_t line, const char * filename);
	std::string message;
	size_t line;
	const char * filename;
};

class TestRunner
{
public:
	TestRunner(TestRunner * parent, const char * _name);
	std::string name() const;
	virtual void run(TestResult &)= 0;
	virtual ~TestRunner() { }

	TestRunner * parent;
	std::string _name;
private:
#if __cplusplus >= 201103L
	TestRunner() = delete;
#else
	TestRunner();
#endif
	
};

class TestGroup : public TestRunner
{
public:
	TestGroup(const char * name);
	TestGroup(TestGroup * parent, const char * name);
	void addTest(TestRunner * runner);
	void run(TestResult & result);

private:
#if __cplusplus >= 201103L
	TestGroup() = delete;
#else
	TestGroup();
#endif
	
	std::string _name;
	typedef std::vector<TestRunner *> tests_t;
	tests_t tests;
};

class TestRegistry : public TestGroup
{
public:
	TestRegistry();
};

class Test : public TestRunner
{
public:
	Test(TestGroup * parent, const char * name);
	void run(TestResult & _result);
protected:
	TestResult * result;
private:
#if __cplusplus >= 201103L
	Test() = delete;
#else
	Test();
#endif
	virtual void go() = 0;

};


#define DEF_TEST(GROUP,NAME) \
class TEST_##GROUP##_##NAME : public Test { \
public: \
    TEST_##GROUP##_##NAME() : Test(&GROUP_instance_##GROUP, #NAME){} \
	void go(); \
}; \
TEST_##GROUP##_##NAME TEST_instance_##GROUP##_##NAME; \
void TEST_##GROUP##_##NAME::go()

#define DEF_GROUP(GROUP) TestGroup GROUP_instance_##GROUP(#GROUP);

#define FAILURE(msg) do { throw TestError((msg),__LINE__,__FILE__); } while(0)
#define CHECK(cond)  do { if(!(cond)) { std::ostringstream s; s << "condition " << #cond << " is false."; FAILURE(s.str().c_str()); } } while(0)
#define CHECK_EXPECT(value,expect) do { if (!((value) == (expect))) { std::ostringstream s; s << value << " != " << expect; FAILURE(s.str().c_str()); } } while(0)


