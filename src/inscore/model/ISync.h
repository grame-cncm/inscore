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


#ifndef __ISync__
#define __ISync__

#include "IObject.h"
#include "OSCStream.h"
#include "smartpointer.h"

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class Master;
typedef libmapping::SMARTP<Master> SMaster;

//--------------------------------------------------------------------------
/*!
	\brief a master object associated to its node synchronization modes
*/
class Master : public libmapping::smartable
{
	public:
		typedef std::vector< std::string > SyncOptions;

		enum VAlignType { kUnknown=-1, kSyncOver=0, kSyncTop, kSyncBottom, kSyncFrame, kDefaultSyncAlign=kSyncOver};
		enum SyncType	{ kTypeUnknown=-1, kSyncRelative, kSyncAbsolute, kDefaultSync=kSyncRelative};
		enum StretchType {	kStretchUnknown=0x8000,
							kNoStretch=0,							///< no stretch
							kStretchH=1,							///< horizontal stretch 
							kStretchHH=2,							///< horizontal stretch but without inner distortion when possible
							kStretchV=4,							///< vertical stretch
							kStretchHV = kStretchH + kStretchV,		///< horizontal and vertical stretch
							kStretchHHV = kStretchHH + kStretchV,	///< horizontal and vertical stretch without inner distortion
							kDefaultStretch=kNoStretch};
		
		static SMaster create() { return new Master(); }
		static SMaster create(const SIObject& o, VAlignType syncmode, StretchType stretchmode, SyncType mode, const std::string& masterMapName , const std::string& slaveMapName )
						{  return new Master(o, syncmode, stretchmode, mode, masterMapName, slaveMapName); }
		
		const SIObject& getMaster() const		{ return fMaster; }
		VAlignType		getAlignment() const	{ return fAlignment; }
		StretchType		getStretch() const		{ return fStretch; }
		SyncType		getMode() const			{ return fSyncType; }
		float			getDy() const			{ return fDy; }
		const std::string& getMasterMapName() const	{ return fMasterMapName; }
		const std::string& getSlaveMapName() const	{ return fSlaveMapName; }

		void			setDy (float dy) 		{ fDy = dy; fModified = true; }
		bool			modified() const 		{ return fModified; }
        void			modified(bool) 	{ fModified = false; }

	static std::string	syncalign2string(int syncmode);
	static std::string	synctype2string(int sync);
	static VAlignType	string2syncalign(std::string syncmode);
	static SyncType		string2synctype(std::string syncmode);
	static std::string	stretchmode2string(int syncmode);
	static StretchType	string2stretchmode(std::string syncmode);	

	static void initMap();

	protected:
				 Master() 
					: fAlignment(kDefaultSyncAlign), fStretch(kDefaultStretch), fSyncType(kSyncRelative), fDy(0), fMasterMapName(""), fSlaveMapName("") {}
				 Master(const SIObject& o, VAlignType vmode, StretchType hmode, SyncType mode, const std::string& masterMapName, const std::string& slaveMapName )
					:	fMaster(o), fAlignment(vmode), fStretch(hmode), fSyncType(mode), fDy(0),
						fMasterMapName(masterMapName), fSlaveMapName(slaveMapName), fModified(true) {}
		virtual ~Master() {}

	private:
	
	static std::map<std::string, VAlignType>	fAlignStr;
	static std::map<std::string, StretchType>	fStretchStr;
	static std::map<std::string, SyncType>		fTypeStr;
	
	SIObject	fMaster;
	VAlignType	fAlignment;
	StretchType	fStretch;
	SyncType	fSyncType;
	float		fDy;
	std::string	fMasterMapName;
	std::string	fSlaveMapName;
	bool		fModified;
};

//OSCStream&		operator << (OSCStream&, const Master&);
IMessage&		operator << (IMessage&, const Master&);


//--------------------------------------------------------------------------
/*!
	\brief objects synchronization management
	
	actually a surjection from SIObject to Master 
*/
class ISync
{
	bool fModified;
	bool checkLoop(const SIObject slave, SIObject master);
	std::map<SIObject, std::vector<SMaster> > fSlaves2Masters;
	std::map<SIObject, std::vector<SIObject> > fMasters2Slaves;
    
	public:	
		typedef std::map<SIObject, std::vector<SMaster> >::const_iterator	const_slave_iterator;
		typedef std::map<SIObject, std::vector<SMaster> >::iterator			slave_iterator;
		typedef std::map<SIObject, std::vector<SIObject> >::const_iterator	const_master_iterator;
		typedef std::map<SIObject, std::vector<SIObject> >::iterator		master_iterator;
        enum relation{ kNoRelation = 0, kSlave = 1, kMaster = 2 };

				 ISync() : fModified(false) {}
		virtual ~ISync() {}
    
		/*! \brief returns true if the object has at least one master
			\param s the slave object
		*/
        bool hasMaster(SIObject s) const {return fSlaves2Masters.find(s) != fSlaves2Masters.end();}
    
		/*! \brief returns true if the object has at least one slave
			\param m the master object
		*/
        bool hasSlave(SIObject m) const {return fMasters2Slaves.find(m) != fMasters2Slaves.end();}

		/*! \brief returns the vector of masters for a slave
			\param slave the slave object
		*/
        std::vector<SMaster> getMasters(SIObject slave) const;

		/*! \brief returns the master corresponding to name and map
			\param slave	the slave object
			\param master	the master name
			\param map		the master map name
		*/
		SMaster getMaster(SIObject slave, const std::string& master, const std::string& map) const;

		/*! \brief returns the vector of slaves for a master
			\param master the master object
		*/
        std::vector<SIObject> getSlaves(const SIObject master) const;
    
		/*! \brief returns the map slaves to masters
		*/
        std::map<SIObject, std::vector<SMaster> > getSlaves2Masters() const;

		/*! \brief adds a slave -> master relation between two objects
			\param o1 the first object
			\param o2 the second object
		*/
        relation getRelation(SIObject o1, SIObject o2) const;

		/*! \brief adds a slave -> master relation between two objects
			\param slave the slave object
			\param master the master object
		*/
		void	sync(const SIObject& slave, SMaster master);

		/*! \brief removes a slave from the sync set
			\param o the object to be removed from the relations set
		*/
		void	remove(SIObject o, SMaster m=0);
    
		/*! \brief sort a set of nodes according to their relations
			\param nodes the set of nodes to be sorted
		*/
		IObject::subnodes	topologicalSort(IObject::subnodes& nodes) const;

		/*! \brief sort a set of nodes according to their relations (inverted compared to topologicalSort() )
			\param nodes the set of nodes to be sorted
		*/
		IObject::subnodes invertedTopologicalSort(IObject::subnodes& nodes) const;

		/*! \brief returns the modified state of the synchronization set
		*/
		bool	modified()					{ return fModified; }

		/*! \brief sets the modified state of the synchronization set
		*/
		void	modified(bool state)		{ fModified = state; }

		/*! \brief relations set cleanup
		
			Cleanup of the relations set consists in removing a relation when one of the part
			of this relation is flagged as deleted.
		*/
		void	cleanup();

		/// debug utility
		void	print(std::ostream& out) const;

		/// \brief a periodic task to propagate modification state from masters to slaves
		virtual void ptask ();

};

std::ostream& operator << (std::ostream& out, const ISync& sync);

/*! @} */

} // end namespoace

#endif
