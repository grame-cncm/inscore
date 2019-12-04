/*

  INScore viewer
  Copyright (C) 2011  Grame

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

#ifndef __INScoreAppl__
#define __INScoreAppl__

#include <string>
#include <vector>

#include <QApplication>
#include <QTimer>

#include "INScore.h"

class QMenuBar;

//_______________________________________________________________________
class INScoreTimer : public QTimer
{
	inscore::INScoreGlue *	fGlue = 0;

	public:
				 INScoreTimer() {}
		virtual ~INScoreTimer() { stop(); }

		void 	start(inscore::INScoreGlue * glue);
		void 	timerEvent(QTimerEvent *event) override;
};

//_______________________________________________________________________
class INScoreAppl : public QApplication, public inscore::INScoreApplicationGlue
{
	Q_OBJECT

	QMenuBar *fMenuBar;
	bool	 fStarted;
	std::vector<std::string> fPendingOpen;			// a list of inscore files that should be opened
	std::string				 fPendingBuffer;		// a buffer that should be parsed

	int 					fRate = 0;
	int 					fTimerId = 0;
	inscore::INScoreGlue *	fGlue = 0;
	INScoreTimer			fSorterTask;

	public :
				 INScoreAppl (int & argc, char ** argv );
		virtual ~INScoreAppl();

		void	start (int udpinport, int udpoutport);
		void	stop  ();

		void	setupMenu();
		void	showMobileMenu();
		void	started();
		void	readArgs(int argc, char ** argv);

		void	startView () override;
		void	stopView  () override;
		bool	event(QEvent *ev) override;
		void 	showMouse (bool state) override;
		bool 	openUrl (const char* url) override;
		std::string getIP() const override;

	protected:
		void 	timerEvent(QTimerEvent *event) override;

	static void open(const std::string& file);
	static void read(const std::string& buffer);

	public slots:
		void about();
		void logwindow();
};


#endif
