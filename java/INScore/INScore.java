/*
   Copyright (C) 2010 Grame
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

       * Redistributions of source code must retain the above copyright
         notice, this list of conditions and the following disclaimer.
       * Redistributions in binary form must reproduce the above copyright
         notice, this list of conditions and the following disclaimer in the
         documentation and/or other materials provided with the distribution.
       * Neither the name of Sony CSL Paris nor the names of its contributors 
         may be used to endorse or promote products derived from this software 
         without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
   EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


package INScore;
import INScore.*;
import java.awt.*;
import java.awt.image.*;

/**
	The main INScore API.
*/
public class INScore
{
	final long fINSHandler;
	final long fINSListener;

    static {
        try {
			Init ();
			System.out.println("INScore version " + GetVersion() + " - JNI interface version " + GetJNIVersion() + " initialized.");
		} catch (UnsatisfiedLinkError e) {
			System.err.println("INScore native code library initialization failed.\n" + e);
		}
    }

	/**	Gives the library version number as a string

        Version number format is  MAJOR.MINOR
	*/
	public static native final String GetVersion();

	/**	Gives the JNI library version number as a string

        Version number format is  MAJOR.MINOR
	*/
	public static native final String GetJNIVersion();

	
	/** INScore constructor.
	*/
    public INScore ()	{ fINSHandler = 0; }

	
	/** Start INScore services.
		
		@param timeInterval the time task interval (in mls). A null value 
		       means no time task, in this case the time task should be 
			   at the java client rate. 
		@param udpin the INScore listening udp port number
		@param udpout the output udp port number
		@param udperr the error udp port number
	*/
    public native void Start (int timeInterval, int udpin, int udpout, int udperr);

	
	/** Start INScore services.
		
		This method is equivalent to Start(timeInterval, udpin, udpin+1, udpin+2)
		
		@param timeInterval the time task interval (in mls). A null value 
		       means no time task, in this case the time task should be 
			   at the java client rate. 
		@param udpin the INScore listening udp port number
	*/
    public void Start (int timeInterval, int udpin) {
		Start (timeInterval, udpin, udpin+1, udpin+2);
	}

	/** Stops the INScore services.
	*/
    public native void Stop ();

	/** Draws the score into a bitmap.
	
		Actually, draws the score to an offscreen that is next copied to the destination bitmap.
		@param dst the destination bitmap ARGB array
		@param w the bitmap width
		@param h the bitmap height
	*/
   public native synchronized void GetBitmap (int[] dst, int w, int h);

	/** Manual call of the TimeTask.
	
		A Java client may choose to manually call the INScore time task. 
		This task do the following: 
		 - applies the incoming OSC messages to the internal model, 
		 - propagates the modifications to the score view. In case of view change,
		   the INScoreViewListener::update is called
	
		@see #Start
		@see INScoreViewListener
	*/
   public native synchronized void TimeTask ();

	/**	Sets a listener that will be notified of the view updates

 		@param listener an object that impements INScoreViewListener
	*/
	public native final void SetViewListener(INScoreViewListener listener);

	/** Draws the score.
	
		Drawing the score should be typically called from the paint method of a Canvas.
		@param g a Graphics
		@param w the desired drawing width
		@param h the desired drawing heigth
	*/
   public synchronized void  Draw (Graphics g, int w, int h) {
		class foo implements ImageObserver {
			public boolean	imageUpdate(Image img, int infoflags, int x, int y, int width, int height) { return true; }
		}
		BufferedImage img = new BufferedImage (w, h, BufferedImage.TYPE_4BYTE_ABGR_PRE);
		int[] outPixels = new int[w*h];
		GetBitmap (outPixels, w, h);
		img.setRGB( 0, 0, w, h, outPixels, 0, w );
		g.drawImage (img, 0, 0, new foo());
	}
	
	/** Internal jni initialization method.
		Automatically called at package init.
	*/
    static native void	Init ();
}

