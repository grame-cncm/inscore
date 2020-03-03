
#include <iostream>

#include "INScore.h"

using namespace std;
using namespace inscore;

template<typename T> const char* checkPtr(T* ptr)
{
	return ptr ? "ok" : "fail";
}

//--------------------------------------------------------------------------
class TestGlue : public INScoreApplicationGlue
{
	public :
				 TestGlue() {}
		virtual ~TestGlue() {}
		virtual void 	showMouse (bool state) 				{ cout << "TestGlue::showMouse " << state << endl; }
		virtual bool 	openUrl (const std::string& url)	{ cout << "TestGlue::openUrl " << url << endl; };
		virtual void	startView ()				{ cout << "TestGlue::startView " << endl; };
		virtual void	stopView  ()				{ cout << "TestGlue::stopView " << endl; };

		virtual std::string viewVersion() const 	{ cout << "TestGlue::viewVersion " << endl; return "Testview version 0.1"; };
		virtual std::string getIP() const 			{ cout << "TestGlue::getIP " << endl; return "localhost"; };
};


static void create_rect ()
{
	INScore::MessagePtr msg = INScore::newMessage("set");
	INScore::add(msg, "rect");
	INScore::add(msg, "1");
	INScore::add(msg, "1");
	INScore::postMessage("/ITL/scene/rect", msg);
}

static void test_messages ()
{
	cout << "\nMessages:" << endl;
	cout << "  newMessage:    " << checkPtr(INScore::newMessage()) << endl;
	cout << "  newMessageM:   " << checkPtr(INScore::newMessage("get")) << endl;
	INScore::MessagePtr msg = INScore::newMessage();
	cout << "  msgAdd Str:    ";
	INScore::add(msg, "time"); cout << "ok" << endl;
	cout << "  msgAdd Foat:   ";
	INScore::add(msg, 1.1f); cout << "ok" << endl;
	cout << "  msgAdd Int     ";
	INScore::add(msg, 0); cout << "ok" << endl;
	cout << "  delMessage:    ";
	INScore::delMessage(msg); cout << "ok" << endl;

	msg = INScore::newMessage();
	INScore::add(msg, "get");
	INScore::add(msg, "time");
	cout << "  postMessage:         ";
	INScore::postMessage("/ITL", msg); cout << "ok" << endl;
	cout << "  postMessage Str:     ";
	INScore::postMessage("/ITL", "get"); cout << "ok" << endl;
	cout << "  postMessage Str I:   ";
	INScore::postMessage("/ITL", "get", 1); cout << "ok" << endl;
	cout << "  postMessage Str F:   " ;
	INScore::postMessage("/ITL", "get", 1.1f); cout << "ok" << endl;
	cout << "  postMessage Str Str: ";
	INScore::postMessage("/ITL", "get", "rate"); cout << "ok" << endl;
}

static INScoreGlue* test_start (TestGlue * appglue)
{
	cout << "\nStart inscore:" << endl;
	cout << "  start:         ";
	return INScore::start (7000, 7001, 7002, appglue);
}

static void test_glue (INScoreGlue * glue)
{
	cout << "\nTest inscore glue:" << endl;
	cout << "  getRate:       " << glue->getRate() << endl;
	cout << "  timeTask:      "; glue->timeTask(); cout << "ok" << endl;
	cout << "  sorterTask:    "; glue->sorterTask(); cout << "ok" << endl;
}

static void test_stop (INScoreGlue * glue)
{
	cout << "\nStop inscore:" << endl;
	cout << "  stop:         ";
	INScore::stop (glue);
}

int main (int argc, char*argv[])
{
	cout << "INScore lib tests" << endl;
	TestGlue appglue;
	INScoreGlue* glue = test_start (&appglue);
	test_messages ();
	test_glue (glue);
	test_stop (glue);
	return 0;
}

