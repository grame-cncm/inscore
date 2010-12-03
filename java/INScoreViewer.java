/*
   Copyright (C) 2010 Sony CSL Paris
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

import java.awt.*;
import java.awt.event.*;
import java.awt.print.*;
import java.io.*;
import javax.swing.*;
import javax.swing.event.*;
import INScore.*;

public class INScoreViewer {  
   
    public static void main(String[] args) {
        JFrame win = new inscoreviewerGUI();
        win.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        win.setVisible(true);
    }
}

class INScoreListener implements INScoreViewListener {  
	Component fView;
    public INScoreListener (Component view)			{ fView = view; }
	public void update() {
		fView.repaint();
    }
}

class scorePanel extends Canvas implements Printable {
 	static {
        try {
			System.loadLibrary("jniINScore");
		} catch (UnsatisfiedLinkError e) {
			System.err.println("Native code library failed to load." + e);
		}
	}

	INScore fscore;
	INScoreListener flistener;
	
	public scorePanel()	{ 
		fscore = new INScore(); 
		flistener = new INScoreListener(this);
		fscore.SetViewListener (flistener);
	}

	public Dimension getPreferredSize()		{ return new Dimension(500,500); }


	public void paint(Graphics g) {
		fscore.Draw (g, getSize().width, getSize().height);
	}
	
	public int print(Graphics g, PageFormat pf, int page) throws PrinterException {
		if (page >= 1)
			return NO_SUCH_PAGE;

		Graphics2D g2d = (Graphics2D)g;
		g2d.translate(pf.getImageableX(), pf.getImageableY());
		int w = (int)pf.getImageableWidth();
		int h = (int)pf.getImageableHeight();
		fscore.Draw (g, w, h);
		return PAGE_EXISTS;
	}
}


///// inscoreviewerGUI
class inscoreviewerGUI extends JFrame {
    String	 fTitle = "INScore Viewer Java";
	Menu     ffileMenu = new Menu("File");		// declare and create new menu
    MenuItem fprintItem = new MenuItem("Print");	// create new menu item
    MenuItem fquitItem = new MenuItem("Quit");	// another menu item
	scorePanel fscore = new scorePanel();

    
    public inscoreviewerGUI() {
        //... Add listeners to menu items
        fprintItem.addActionListener(new PrintAction(fscore));
        fquitItem.addActionListener(new QuitAction());
        
        //... Menubar, menus, menu items.  Use indentation to show structure.
        MenuBar menubar = new MenuBar();  // declare and create new menu bar
		menubar.add(ffileMenu);			// add the menu to the menubar
		ffileMenu.add(fprintItem);		// add the menu item to the menu
		ffileMenu.addSeparator();			// add separator line to menu
		ffileMenu.add(fquitItem);
        
        //... Content pane: create, layout, add components
        JPanel content = new JPanel();
        content.setBackground(Color.white);
        content.setLayout(new BorderLayout());
        content.add(fscore, BorderLayout.CENTER);

        //... Set JFrame's menubar, content pane, and title.
        this.setContentPane(content);       // Set windows content pane..
        this.setMenuBar(menubar);          // Set windows menubar.
        this.setTitle(fTitle);
        this.pack();
    }
    

	//// PrintAction
	class PrintAction implements ActionListener {
         scorePanel fscore;
         public PrintAction(scorePanel score)	{ fscore = score; }
		 public void actionPerformed(ActionEvent e) {
			 PrinterJob job = PrinterJob.getPrinterJob();
			 job.setPrintable(fscore);
			 boolean ok = job.printDialog();
			 if (ok) {
				 try {
					  job.print();
				 } catch (PrinterException ex) {
					System.err.println("printing exception: " + ex);
				 }
			 }
		}
    }
    
	/// QuitAction
    class QuitAction implements ActionListener {
        public void actionPerformed(ActionEvent e) { System.exit(0); }
    }
}
