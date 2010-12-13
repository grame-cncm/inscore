
class QGraphicsScene;
class QApplication;

class DebugListener
{
	public :
		virtual void update() = 0;
};


#ifdef __cplusplus
extern "C" {
#endif


void getBitmap(QGraphicsScene* scene, unsigned int* dest, int w, int h);
QGraphicsScene* start (QApplication* appl);
void setListener (DebugListener* listener);

#ifdef __cplusplus
}
#endif
