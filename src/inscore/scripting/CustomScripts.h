/*

  INScore Project

  Copyright (C) 2015  Grame

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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/

#ifndef CUSTOMSCRIPTS_H
#define CUSTOMSCRIPTS_H

#include <QObject>
#include <QJSValueList>
#include <QString>

namespace inscore
{

/*!
 * \brief The CustomScripts class. Contains custom functions added to javascript engine
 */
class CustomScripts : public QObject
{
		Q_OBJECT
    public:
        CustomScripts(QObject *parent = 0);
        virtual ~CustomScripts();

        public slots:
		// All callback method of this object must be slot method.
        // Their arguments must be of type const QMetaType
        QString version();
        QString osname();
		QJSValue readfile(const QString &filename);
		void print(const QVariantList &args);
		void post(const QVariantList &args);
};

} // namespace

#endif // CUSTOMSCRIPTS_H
