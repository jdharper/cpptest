#include <typeinfo>
#include "cppTest.h"


void TestResult::addPass(TestRunner * test)
{
	//std::cout << "Passed: " << test->name().c_str() << std::endl;
}

void TestResult::addError(TestRunner * test, const TestError & error)
{
	std::cout << "Error in " << test->name().c_str() << std::endl
		<< "    " << error.message.c_str() << " : " << error.filename << ':' << error.line << ' ' << std::endl;
}

void TestResult::addException(TestRunner * test, const TestException & exception)
{
	std::cout << "Unexpected exception in " << test->name().c_str() << std::endl
		<< "    " << typeid(exception).name() << " : " << exception.message.c_str() << std::endl;

}

TestException::TestException(const char * message, std::exception & exception)
	: message(message),
	  exception(exception)
{
}

TestError::TestError(const char * message, size_t line, const char * filename)
	: message(message),
	  line(line),
	  filename(filename)
{
}

TestRunner::TestRunner(TestRunner * parent, const char * _name) :
	parent(parent),
	_name(_name)
{
}

std::string TestRunner::name() const
{
	std::string parentName = "";
	if (parent)
	{
		parentName = parent->name();
		if (parentName.size() > 0)
			parentName += " : ";
	}
	return parentName + _name;

}

TestGroup::TestGroup(TestGroup * parent, const char * name) :
	TestRunner(parent, name)
{
	if (parent)
		parent->addTest(this);
}

void TestGroup::addTest(TestRunner * runner)
{
	tests.push_back(runner);
}

void TestGroup::run(TestResult & result)
{
	tests_t::iterator it;
	for (it = tests.begin(); it != tests.end(); ++it)
	{
		TestRunner * test = *it;
		test->run(result);
	}
}

TestGroup::TestGroup(const char * name) :
	TestRunner(getTestRegistry(), name)
{
	static_cast<TestGroup *>(parent)->addTest(this);
}

TestRegistry :: TestRegistry() :
	TestGroup(0, "")
{
}

TestRegistry * getTestRegistry()
{
	static TestRegistry * theTestRegistry;
	if (!theTestRegistry)
		theTestRegistry = new TestRegistry();
	return theTestRegistry;
}

Test :: Test(TestGroup * parent, const char * name) :
	TestRunner(parent, name)
{
	parent->addTest(this);
}

void Test :: run(TestResult & _result)
{
	result = &_result;
	try
	{
		go();
	}
	catch (TestError & te)
	{
		result->addError(this, te);
		return;
	}
	catch (std::exception & e)
	{
		result->addException(this, TestException("Unexpected Exception", e));
		return;
	}
	result->addPass(this);
}





