
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
		virtual bool 	openUrl (const std::string& url)	{ cout << "TestGlue::openUrl " << url << endl; return true; };
		virtual void	startView ()				{ cout << "TestGlue::startView " << endl; };
		virtual void	stopView  ()				{ cout << "TestGlue::stopView " << endl; };

		virtual std::string viewVersion() const 	{ cout << "TestGlue::viewVersion " << endl; return "Testview version 0.1"; };
		virtual std::string getIP() const 			{ cout << "TestGlue::getIP " << endl; return "localhost"; };
};


static void create_obj (const char* type, const char* address)
{
	INScore::MessagePtr msg = INScore::newMessage("set");
	INScore::add(msg, type);
	INScore::add(msg, 0.5f);
	INScore::add(msg, 0.5f);
	INScore::postMessage(address, msg);
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
	INScore::postMessage("/ITL", "hello"); cout << "ok" << endl;
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

static void test_load ()
{
	cout << "\nLoad tests:" << endl;
	const char* script2 =  "/ITL/scene new; \
							/ITL/scene/label 	(set txt label), (yorigin 1.1), (y 0.5), (x 0), (fontSize 11);";
	const char* script1 =  "/ITL/scene new; \
							/ITL/scene/rect1 set rect 0.2 0.2; \
							/ITL/scene/rect1 x 0.5; \
							/ITL/scene/rect1 y 0.1;";
	cout << "  loadInscore:       " << INScore::loadInscore (script1, true) << endl;
	cout << "  loadInscore2:      " << INScore::loadInscore2 (script2) << endl;
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

static void test_sync (INScoreGlue * glue)
{
	cout << "\nTest sync:" << endl;
	INScore::MessagePtr msg = INScore::newMessage("new");
	INScore::postMessage("/ITL/scene", msg);

	create_obj("rect", "/ITL/scene/rect");
	create_obj("ellipse", "/ITL/scene/circ");

	msg = INScore::newMessage();
	INScore::add(msg, "ellipse");
	INScore::add(msg, "rect");
	INScore::postMessage("/ITL/scene/sync", msg);
	
	msg = INScore::newMessage("get");
	INScore::postMessage("/ITL/scene", msg);
	
	msg = INScore::newMessage("get");
	INScore::postMessage("/ITL/scene/sync", msg);
	glue->timeTask();
}

static void test_hierarchy_bug (INScoreGlue * glue)
{
	create_obj ("rect" , "/ITL/scene/rect");
	INScore::MessagePtr msg = INScore::newMessage("del");
	INScore::postMessage("/ITL/scene/*", msg);
	create_obj ("rect" , "/ITL/scene/rect");
	create_obj ("ellipse" , "/ITL/scene/rect/e");
	glue->timeTask();
}

static void test_img_map_bug (INScoreGlue * glue)
{
	INScore::MessagePtr msg = INScore::newMessage("new");
	INScore::postMessage("/ITL/scene", msg);
	glue->timeTask();
	msg = INScore::newMessage("set");
	INScore::add(msg, "img");
	INScore::add(msg, "/Users/fober/src/INScore/git/javascript/imgs/stevictoire/sc0.png");
	INScore::postMessage("/ITL/scene/img", msg);
	glue->timeTask();
	msg = INScore::newMessage("get");
	INScore::postMessage("/ITL/scene", msg);
	glue->timeTask();
	msg = INScore::newMessage("map");
	INScore::add(msg, "( [140, 3949[ [0, 619[ ) ( [0:0:0, 0:4:30[ )");
	INScore::postMessage("/ITL/scene/img", msg);
	glue->timeTask();
	msg = INScore::newMessage("get");
	INScore::add(msg, "map");
	INScore::postMessage("/ITL/scene/img", msg);
	glue->timeTask();
}

int main (int argc, char*argv[])
{
	cout << "INScore lib tests" << endl;
	TestGlue appglue;
	INScoreGlue* glue = test_start (&appglue);
//	test_messages ();
//	test_load ();
//	test_glue (glue);
//	test_sync (glue);
//	test_hierarchy_bug (glue);
	test_img_map_bug (glue);
	test_stop (glue);
	return 0;
}

