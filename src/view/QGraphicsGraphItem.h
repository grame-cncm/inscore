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


#ifndef __QGraphicsGraphItem__
#define __QGraphicsGraphItem__

#include <QGraphicsRectItem>
#include "GraphicSignal.h"

namespace INScore
{

/*!
\addtogroup ITLView
@{
*/

/**
*	\brief A QGraphicsItem displaying data in a graph.

	The basic rendering principle :
	the graphic area is sliced in 'stripes'
*
*/
class QGraphicsGraphItem : public QGraphicsRectItem
{

	public :
		enum LineStyle { kCurveLine = 0 , kStepLine };	    /// < The curve shape: kCurveLine is a smooth line, kStepLine is 'little sticks'.
		enum DrawPath { kBoth = 0 , kBottom , kTop };	    /// < Draw the top/bottom/both bound of the graph with the pen.

		QGraphicsGraphItem(QGraphicsItem * parent = 0);
		virtual ~QGraphicsGraphItem();

		/**
		*	\brief QGraphicsItem implementation.
		*/
		void paint( QPainter * painter, const QStyleOptionGraphicsItem *, QWidget * );

		/**
		*	\brief Indicates that a signal is constant.
		*
		*	\param signal is the index in terms of '6 components', 'complete' graphic signal, ranges from 0 to infinity.
		*	\param dimension is the index of the component inside a signal, ranges from 0 to 5.
		*/
		void notifyConst( int signal , int dimension , bool isConst );

		const std::vector<std::vector<bool> >& constSignals() const { return fConstSignals; }

		/**
		*	\brief Puts a GraphicFrames in the buffer.
		*/
		QGraphicsGraphItem& operator <<  (const GraphicFrames& frame);

		/**
		*	\brief Clears the GraphicFrames buffer.
		*/
		void clear()				{ fFrames.clear(); }

		const std::vector<GraphicFrames>& frames() const	{ return fFrames; }

		/**
		*	\brief Sets the default frame. The default frame is used when frames().size() < size().
		*
		*	Note: the fDefaultFrame is not used in this version of QGraphicsGraphItem, that does not use cache rendering.
		*/
		void setDefaultFrame(const GraphicFrames& f )		{ fDefaultFrame = f; }

		/**
		* \brief Sets the buffer size (the number of drawn frames). If bufferSize < frames().size(), the oldest frames values are popped out.
		*/
		void setSize( int bufferSize );
		int size() const { return fBufferSize; }

		LineStyle lineStyle() const { return fLineStyle; }
		void setLineStyle(const LineStyle& lineStyle) { if (fLineStyle != lineStyle) {fLineStyle = lineStyle; updateDrawer(); update();} }

		void setDrawPath(const DrawPath& drawPath) { fDrawPath = drawPath; update(); }
		const DrawPath& drawPath() const { return fDrawPath; }

		/**
		*	brief If 'ignoreSignalColor==true', the color component of the graphic signal won't be used for filling, but the defaultFillColor() will be used instead.
		*/
//		void setIgnoreSignalColor(bool ignoreSignalColor) { fIgnoreSignalColor = ignoreSignalColor; update(); }
//		bool ignoreSignalColor() const { return fIgnoreSignalColor; }

		/**
		*	brief If 'penIgnoreSignalColor==true', the color component of the graphic signal won't be used for outlining, but the defaultPenColor() will be used instead.
		*/
//		void setPenIgnoreSignalColor(bool penIgnoreSignalColor) { fPenIgnoreSignalColor = penIgnoreSignalColor; update(); }
//		bool penIgnoreSignalColor() const { return fPenIgnoreSignalColor; }

		/**
		* \brief Sets the default 'fill' color. The default 'fill' color is used to fill the graph if ignoreSignalColor() is true.
		*/
		void setDefaultFillColor(const QColor& color) { fDefaultFillColor = color; update(); }
		const QColor& defaultFillColor() const { return fDefaultFillColor; }

		/**
		* \brief Sets the default 'pen' color. The default 'pen' color is used to outline the graph if penIgnoreSignalColor() is true.
		*/
		void setDefaultPenColor(const QColor& color) { fDefaultPenColor = color; update(); }
		const QColor& defaultPenColor() const { return fDefaultPenColor; }

	protected :

		/// \brief The Drawer provides some indirections relative to the style of the graph.
		class Drawer
		{
			public:
				Drawer() {}
				virtual ~Drawer() {}
				/*! \brief  Add path-elements corresponding to points[index] to the path.
				*	"backward==true" means that the path is built from right to left.
				*/
				virtual void setPath( QPainterPath& path , const QList<QPointF>& points , int index , int stripeWidth, bool backWard = false ) const = 0;
				virtual int numberOfStripes(int bufferSize) const = 0;	// Number of 'full-width' stripes of the graph.
				virtual float startX(int index , int stripeWidth) = 0;	// Left border of a stripe, according to its index and the current stripeWidth.
		};
		class StepDrawer: public Drawer
		{
			public:
				StepDrawer() {}
				virtual ~StepDrawer() {}
				virtual void setPath( QPainterPath& path , const QList<QPointF>& points , int index , int stripeWidth, bool backWard ) const;
				virtual int numberOfStripes(int bufferSize) const			{ return bufferSize; }	// With a StepDrawer, there is 1 stripe for 1 value.
				virtual float startX(int startIndex , int stripeWidth)	{ return startIndex * stripeWidth; }
		};
		class CurveDrawer: public Drawer
		{
			public:
				CurveDrawer() {}
				virtual ~CurveDrawer() {}
				virtual void setPath( QPainterPath& path , const QList<QPointF>& points , int index , int stripeWidth, bool backWard ) const;
				virtual int numberOfStripes(int bufferSize) const			{ return bufferSize - 1; }	// With a CurveDrawer, there is 1 stripe for 1 value, excepted for the first and last
																										// values, who only have half-stripes.
				virtual float startX(int startIndex , int stripeWidth)	{ return ( startIndex - 0.5 )* stripeWidth; }	// As the first stripe is only an half-stripe, an half-stripeWidth
																														// is removed from the standard value.
		};
		void updateDrawer();

		void paint( QPainter * painter , int startIndex , int endIndex );

		QPointF getPoint( float value , int index , float yMin , float yMax ) const;
		QPointF getPoint( float value , int index ) const;
		float getX(int index) const;
		float getY( float value , float yMin , float yMax ) const;

		/*! \brief The stripeWidth is the thickness on x-axis of a stripe. It is an integer value.
		*		It's computed as the actual width on screen of the QGraphicsGraphItem (taking
		*		the scale into account), divided by the number of stripes of the graph, ceiled to integer.
		*/
		int computeStripeWidth() const;

		/*!	\brief The width of the cache image used for painting.
		*		The computed value is the number of stripes * stripeWidth().
		*/
		int computeCacheWidth() const;

		/*!	\brief The width of the cache image used for painting.
		*		The computed value is the actual height on screen of the QGraphicsGraphItem (taking
		*		the scale into account).
		*/
		int computeCacheHeight() const;

		int stripeWidth() const { return fStripeWidth; }
		int cacheWidth() const	{ return fCacheWidth; }
		int cacheHeight() const { return fCacheHeight; }

		static float YMinusT( const GraphicFrame& frame ) 		{ return frame.getPos() - frame.getThickness(); }
		static float YPlusT( const GraphicFrame& frame ) 		{ return frame.getPos() + frame.getThickness(); }
		static float  Y( const GraphicFrame& frame ) 			{ return frame.getPos(); }
		static float YMinusHalfT( const GraphicFrame& frame ) 	{ return frame.getPos() - frame.getThickness()/2.0f; }
		static float YPlusHalfT( const GraphicFrame& frame ) 	{ return frame.getPos() + frame.getThickness()/2.0f; }

		void clearCache();

		std::vector<GraphicFrames> fFrames;					// the signals data
		std::vector<std::vector<bool> > fConstSignals;		// a list of const signals
		float mMin, mMax;									// actually -1 and 1
		int fNewData;		// unused
		int fBufferSize;									// actually the parallel signal size
//		QPixmap * fCache;

		// drawing options
		LineStyle fLineStyle;
//		ThicknessMode fThicknessMode;
		DrawPath fDrawPath;
//		bool fIgnoreSignalColor, fPenIgnoreSignalColor;
		QColor fDefaultFillColor, fDefaultPenColor;

		GraphicFrames fDefaultFrame;	// unused
		int fCacheWidth, fCacheHeight, fStripeWidth;		// the drawing area properties

		// a set of indirections set according to drawing options
		typedef float (*FrameValueComputeFunction)( const INScore::GraphicFrame& frame );
		Drawer * fCurrentDrawer;							// computes the graph envelope according to the graph style
		FrameValueComputeFunction fBottomLineComputeFunction, fTopLineComputeFunction;
};

} // end namespoace

#endif
