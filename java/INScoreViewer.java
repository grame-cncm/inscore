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
   
    public void update() {
		System.out.println("JAVA >>> INScoreListener update\n");
    }
}

class scorePanel extends Canvas implements Printable {
 	static {
        try {
			System.loadLibrary("jniINScore");
		} catch (UnsatisfiedLinkError e) {
			System.err.println("Native code library failed to load.\n" + e);
		}
	}

	INScore m_score;
	INScoreListener m_listener;
	
	public scorePanel()	{ 
		m_score = new INScore(); 
		m_listener = new INScoreListener();
//		m_score.SetViewListener (m_listener);
	}

	public Dimension getPreferredSize()		{ return new Dimension(500,500); }


	public void paint(Graphics g) {
		m_score.Draw (g, getSize().width, getSize().height);
	}
	
	public int print(Graphics g, PageFormat pf, int page) throws PrinterException {
		if (page >= 1)
			return NO_SUCH_PAGE;

		Graphics2D g2d = (Graphics2D)g;
		g2d.translate(pf.getImageableX(), pf.getImageableY());
		int w = (int)pf.getImageableWidth();
		int h = (int)pf.getImageableHeight();

		return PAGE_EXISTS;
	}
}


///// inscoreviewerGUI
class inscoreviewerGUI extends JFrame {
    String	 m_Title = "INScore Viewer Java";
	Menu     m_fileMenu = new Menu("File");		// declare and create new menu
    MenuItem m_printItem = new MenuItem("Print");	// create new menu item
    MenuItem m_quitItem = new MenuItem("Quit");	// another menu item
	scorePanel m_score = new scorePanel();

    
    public inscoreviewerGUI() {
        //... Add listeners to menu items
        m_printItem.addActionListener(new PrintAction(m_score));
        m_quitItem.addActionListener(new QuitAction());
        
        //... Menubar, menus, menu items.  Use indentation to show structure.
        MenuBar menubar = new MenuBar();  // declare and create new menu bar
		menubar.add(m_fileMenu);			// add the menu to the menubar
		m_fileMenu.add(m_printItem);		// add the menu item to the menu
		m_fileMenu.addSeparator();			// add separator line to menu
		m_fileMenu.add(m_quitItem);
        
        //... Content pane: create, layout, add components
        JPanel content = new JPanel();
        content.setBackground(Color.white);
        content.setLayout(new BorderLayout());
        content.add(m_score, BorderLayout.CENTER);

        //... Set JFrame's menubar, content pane, and title.
        this.setContentPane(content);       // Set windows content pane..
        this.setMenuBar(menubar);          // Set windows menubar.
        this.setTitle(m_Title);
        this.pack();
    }
    

	//// PrintAction
	class PrintAction implements ActionListener {
         scorePanel m_score;
         public PrintAction(scorePanel score)	{ m_score = score; }
		 public void actionPerformed(ActionEvent e) {
			 PrinterJob job = PrinterJob.getPrinterJob();
			 job.setPrintable(m_score);
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
