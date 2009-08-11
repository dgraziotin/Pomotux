/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
#define _CXXTEST_LONGLONG long long
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
    CxxTest::ErrorPrinter tmp;
    return CxxTest::Main<CxxTest::ErrorPrinter>( tmp, argc, argv );
}
bool ActivityTest_init = false;
#include "TestActivity.h"

static ActivityTest suite_ActivityTest;

static CxxTest::List Tests_ActivityTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ActivityTest( "TestActivity.h", 14, "ActivityTest", suite_ActivityTest, Tests_ActivityTest );

static class TestDescription_ActivityTest_testCreateOneActivity : public CxxTest::RealTestDescription {
public:
 TestDescription_ActivityTest_testCreateOneActivity() : CxxTest::RealTestDescription( Tests_ActivityTest, suiteDescription_ActivityTest, 67, "testCreateOneActivity" ) {}
 void runTest() { suite_ActivityTest.testCreateOneActivity(); }
} testDescription_ActivityTest_testCreateOneActivity;

static class TestDescription_ActivityTest_testModifyActivity : public CxxTest::RealTestDescription {
public:
 TestDescription_ActivityTest_testModifyActivity() : CxxTest::RealTestDescription( Tests_ActivityTest, suiteDescription_ActivityTest, 95, "testModifyActivity" ) {}
 void runTest() { suite_ActivityTest.testModifyActivity(); }
} testDescription_ActivityTest_testModifyActivity;

static class TestDescription_ActivityTest_testDeleteActivity : public CxxTest::RealTestDescription {
public:
 TestDescription_ActivityTest_testDeleteActivity() : CxxTest::RealTestDescription( Tests_ActivityTest, suiteDescription_ActivityTest, 115, "testDeleteActivity" ) {}
 void runTest() { suite_ActivityTest.testDeleteActivity(); }
} testDescription_ActivityTest_testDeleteActivity;

#include "TestTodotodaySheet.h"

static TestTodoTodaySheet suite_TestTodoTodaySheet;

static CxxTest::List Tests_TestTodoTodaySheet = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TestTodoTodaySheet( "TestTodotodaySheet.h", 14, "TestTodoTodaySheet", suite_TestTodoTodaySheet, Tests_TestTodoTodaySheet );

static class TestDescription_TestTodoTodaySheet_testScheduleActivity : public CxxTest::RealTestDescription {
public:
 TestDescription_TestTodoTodaySheet_testScheduleActivity() : CxxTest::RealTestDescription( Tests_TestTodoTodaySheet, suiteDescription_TestTodoTodaySheet, 74, "testScheduleActivity" ) {}
 void runTest() { suite_TestTodoTodaySheet.testScheduleActivity(); }
} testDescription_TestTodoTodaySheet_testScheduleActivity;

static class TestDescription_TestTodoTodaySheet_testDeleteActivityAfterSchedule : public CxxTest::RealTestDescription {
public:
 TestDescription_TestTodoTodaySheet_testDeleteActivityAfterSchedule() : CxxTest::RealTestDescription( Tests_TestTodoTodaySheet, suiteDescription_TestTodoTodaySheet, 91, "testDeleteActivityAfterSchedule" ) {}
 void runTest() { suite_TestTodoTodaySheet.testDeleteActivityAfterSchedule(); }
} testDescription_TestTodoTodaySheet_testDeleteActivityAfterSchedule;

static class TestDescription_TestTodoTodaySheet_testTTSConsistency : public CxxTest::RealTestDescription {
public:
 TestDescription_TestTodoTodaySheet_testTTSConsistency() : CxxTest::RealTestDescription( Tests_TestTodoTodaySheet, suiteDescription_TestTodoTodaySheet, 111, "testTTSConsistency" ) {}
 void runTest() { suite_TestTodoTodaySheet.testTTSConsistency(); }
} testDescription_TestTodoTodaySheet_testTTSConsistency;

static class TestDescription_TestTodoTodaySheet_testPostponeActivity : public CxxTest::RealTestDescription {
public:
 TestDescription_TestTodoTodaySheet_testPostponeActivity() : CxxTest::RealTestDescription( Tests_TestTodoTodaySheet, suiteDescription_TestTodoTodaySheet, 143, "testPostponeActivity" ) {}
 void runTest() { suite_TestTodoTodaySheet.testPostponeActivity(); }
} testDescription_TestTodoTodaySheet_testPostponeActivity;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
