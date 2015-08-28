/*

  INScore Project

  Copyright (C) 2009,2010  Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#include <QDebug>
#include <QPainter>
//#include <algorithm>
#include <QGraphicsRectItem>
#include <QHostAddress>
#include <QTcpSocket>

#include "VHttpdView.h"
#include "IHttpd.h"

using namespace std;
using namespace libmapping;

namespace inscore
{

//----------------------------------------------------------------------
class GQRCode : public QGraphicsRectItem
{
	const IObject* fObject;
	const QRcode*  fQrcode;
	public:
				 GQRCode (QGraphicsItem * parent = 0): fObject(0), fQrcode(0) {}
		virtual ~GQRCode() {}
		
	void setObject (const IObject* o)		{ fObject = o; }
	void setQRCode (const QRcode* code)		{ fQrcode = code; }
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
};

//----------------------------------------------------------------------
void GQRCode::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	QRectF rect = boundingRect();

	if(fQrcode){
		QColor color(fObject->getR(), fObject->getG(), fObject->getB() , fObject->getA());

        painter->setPen(Qt::NoPen);
        painter->setBrush (color);
        const int s = fQrcode->width > 0 ? fQrcode->width : 1;
        const double w = rect.width();
        const double h = rect.height();
        const double scalex = w / s;
        const double scaley = h / s;
        for(int y=0; y<s; y++){
            const int yy = y*s;
            for(int x=0; x<s; x++){
                const int xx = yy + x;
                const unsigned char b = fQrcode->data[xx];
                if(b & 0x01){
                    const double rx1 = x*scalex, ry1 = y*scaley;
                    QRectF r(rx1, ry1, scalex, scaley);
                    painter->drawRects(&r,1);
                }
            }
        }
	}
}

//----------------------------------------------------------------------
MouseEventAble<GQRCode>*  VHttpdView::item() const		{ return (MouseEventAble<GQRCode>*)fItem; }

static QString getIPNum()
{
	QString     result;
	QTcpSocket  sock;
	
	sock.connectToHost("8.8.8.8", 53); // google DNS, or somethingelse reliable
	if (sock.waitForConnected()) {
		QHostAddress IP = sock.localAddress();
		result = IP.toString(); 
	}
	return result;
}


//----------------------------------------------------------------------
VHttpdView::VHttpdView(QGraphicsScene * scene, const IHttpd* server)
	: VMappedShapeView( scene , new MouseEventAble<GQRCode>(server) )
{
	item()->setObject (server);
}

//----------------------------------------------------------------------
VHttpdView::~VHttpdView()
{
	item()->setQRCode (0);
	if ( fQRCode ) QRcode_free (fQRCode);
	fQRCode = 0;
}

//----------------------------------------------------------------------
void VHttpdView::updateView( IHttpd * server  )
{
	if (!fQRCode) {
		QString ip = getIPNum();
		QString url;
		if (ip.size()) {
			url = "http://" + ip + ":" + QString::number(server->getPort()) + "/";
			fQRCode = QRcode_encodeString(url.toStdString().c_str(), 0, QR_ECLEVEL_H, QR_MODE_8, 1);
			item()->setQRCode (fQRCode);
		}
		else fQRCode = 0;
	}

	server->cleanupSync();
	float h = relative2SceneHeight(server->getHeight());
	float w = relative2SceneWidth(server->getWidth());
	QRectF newRect( 0,0, w, h );
	item()->setRect( newRect );
	itemChanged();
	VGraphicsItemView::drawBoundingBox (server);
	VShapeView::updateView( server );
}

} // end namespoace
