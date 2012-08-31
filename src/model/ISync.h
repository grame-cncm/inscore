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

		enum VAlignType { kUnknown=-1, kSyncOver=0, kSyncTop, kSyncBottom, kDefaultSync=kSyncOver};
		enum StretchType {	kStretchUnknown=0x8000, kNoStretch=0, kStretchH=1, kStretchHH=2, kStretchV=4, 
							kStretchHV = kStretchH + kStretchV, kStretchHHV = kStretchHH + kStretchV, 
							kDefaultStretch=kNoStretch};
//		enum { kLinearInterpolation, kNoInterpolation, kDefaultInterpolation=kLinearInterpolation };
		
		static SMaster create() { return new Master(); }
		static SMaster create(const SIObject& o, VAlignType syncmode, StretchType stretchmode, /*const SyncOptions& options ,*/ const std::string& masterMapName , const std::string& slaveMapName )
						{  return new Master(o, syncmode, stretchmode, masterMapName, slaveMapName); }
//		static SMaster create(const SIObject& o, VAlignType syncmode, StretchType stretchmode, float dy , int interpolate , 
//							const SyncOptions& options , const std::string& masterMapName , const std::string& slaveMapName )
//						{  return new Master(o, syncmode, stretchmode, dy, interpolate, options, masterMapName, slaveMapName); }
		
		const SIObject& getMaster() const		{ return fMaster; }
		VAlignType		getAlignment() const	{ return fAlignment; }
		StretchType		getStretch() const		{ return fStretch; }
		float			getDy() const			{ return fDy; }
//		int				getInterpolate() const	{ return fInterpolate; }
//		const SyncOptions& getCustomOptions() const { return fCustomOptions; }
		const std::string& getMasterMapName() const	{ return fMasterMapName; }
		const std::string& getSlaveMapName() const	{ return fSlaveMapName; }

		void			setDy (float dy) 		{ fDy = dy; fModified = true; }
		bool			modified() const 		{ return fModified; }
		void			modified(bool state) 	{ fModified = false; }

		static std::string	syncmode2string(int syncmode);
		static VAlignType	string2syncmode(std::string syncmode);		
		static std::string	stretchmode2string(int syncmode);
		static StretchType	string2stretchmode(std::string syncmode);	
//		static std::string	interpolatemode2string(int interpolateMode);
//		static int			string2interpolatemode(std::string syncmode);

//		float&			getDyRef() 			{ return fDy; }

	static void initMap();

	protected:
				 Master() 
					: fAlignment(kDefaultSync), fStretch(kDefaultStretch), fDy(0), fMasterMapName(""), fSlaveMapName("") {}
				 Master(const SIObject& o, VAlignType vmode, StretchType hmode, /*const SyncOptions& options,*/ const std::string& masterMapName, const std::string& slaveMapName ) 
					:	fMaster(o), fAlignment(vmode), fStretch(hmode), fDy(0), //, fCustomOptions(options) , 
						fMasterMapName(masterMapName), fSlaveMapName(slaveMapName), fModified(true) {}

//				 Master() 
//					: fAlignment(kDefaultSync), fStretch(kDefaultStretch), fDy(0), fInterpolate(kDefaultInterpolation), fMasterMapName(""), fSlaveMapName("") {}
//				 Master(const SIObject& o, VAlignType syncmode, StretchType stretchmode, float dy , int interpolate , 
//							const SyncOptions& options , const std::string& masterMapName , const std::string& slaveMapName ) 
//					:	fMaster(o), fAlignment(syncmode), fStretch(stretchmode), 
//						fDy(dy), fInterpolate(interpolate) , fCustomOptions(options) , fMasterMapName(masterMapName), fSlaveMapName(slaveMapName) {}
		virtual ~Master() {}

	private:
	
	static std::map<std::string, VAlignType>	fSyncStr;
	static std::map<std::string, StretchType>	fStretchStr;
//	static std::map<std::string, int>	fInterpolationStr;
	
	SIObject	fMaster;
	VAlignType	fAlignment;
	StretchType	fStretch;
	float		fDy;
//	int			fInterpolate;
//	SyncOptions fCustomOptions;
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
class ISync : public std::map<SIObject, SMaster>
{
	bool fModified;
	bool checkLoop(const IObject* slave, IObject* master);
	
	public:	
		typedef std::map<SIObject, SMaster>::const_iterator	const_iterator;

				 ISync() : fModified(false) {}
		virtual ~ISync() {}

		/*! \brief adds a slave -> master relation between two objects
			\param slave the slave object
			\param master the master object
		*/
		void	sync(const SIObject& slave, SMaster master);

		/*! \brief removes a slave from the sync set
			\param o the object to be removed from the relations set
		*/
		void	remove(SIObject o);

		/*! \brief sort a set of nodes according to their relations
			\param nodes the set of nodes to be sorted
		*/
//		void	topologicalSort(IObject::subnodes& nodes) const;

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

};

std::ostream& operator << (std::ostream& out, const ISync& sync);

/*! @} */

} // end namespoace

#endif
