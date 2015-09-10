//- BinaryCalc.java
import java.awt.Dimension;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

import javax.swing.JApplet;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

public class Control extends JApplet implements KeyListener {

    private JPanel panel;
    public boolean[] keyDown = new boolean[256];
    
    public ServerSocket srvr;
    public Socket skt;
    public BufferedReader in;
    public PrintWriter out;
    
    public int powerLevel1 = 10;
    public int powerLevel2 = 10;

    public boolean isLocked = false;
    
	public Control() {
        super();

        panel = new JPanel();
        this.add(panel);

        panel.addKeyListener(this);
        panel.requestFocusInWindow();
        
        System.out.println("Starting controller");
  	  Scanner input = new Scanner(System.in);
  	  try
  	  {
	      srvr = new ServerSocket(1234);
	      skt = srvr.accept();
	      in = new BufferedReader(new
	              InputStreamReader(skt.getInputStream()));
	      out = new PrintWriter(skt.getOutputStream(), true);         
	      
	      System.out.println("Controller finished");
  	  }
  	  catch (IOException e)
  	  {
  		  e.printStackTrace();
  	  }

    }

    @Override
    public void init() {
        JOptionPane.showMessageDialog(this, "applet");
        panel.setFocusable(true);
        panel.requestFocus();
        
    }

    public void keyPressed(KeyEvent e) {
//        JOptionPane.showMessageDialog(this, (char) e.getKeyCode());
//    	char key = (char) e.getKeyCode();
//    	System.out.println(key);
    	char key = (char) e.getKeyCode();
    	if (!keyDown[key])
    		keyPressedOnce(key);
    	keyDown[key] = true;
    }
    
    public void keyPressedOnce(char key)
    {
    	if (key == 'P') //lock mode
    	{
    		isLocked = !isLocked;
    		send(0);
    	}
		
		if (isLocked)
			return;
    	
    	if (key == 'U')
    		powerLevel1 += 5;
    	if (key == 'J')
    		powerLevel1 -= 5;
    	if (key == 'I')
    		powerLevel2 += 5;
    	if (key == 'K')
    		powerLevel2 -= 5;
    	
    	if (powerLevel1 <= 0)
    		powerLevel1 = 0;
    	if (powerLevel1 >= 125) //actually 127 max
    		powerLevel1 = 125;
    	if (powerLevel2 <= 0)
    		powerLevel2 = 0;
    	if (powerLevel2 >= 125)
    		powerLevel2 = 125;
    	
    	if (key == 'W')
    		send(1, powerLevel1, powerLevel2); //forward
    	if (key == 'S')
    		send(2, powerLevel1, powerLevel2); //backwards
    	if (key == 'A')
    		send(3, powerLevel1, powerLevel2); //turn left
    	if (key == 'D')
    		send(4, powerLevel1, powerLevel2); //turn right
    	
    	if (key == 'F')
    		send(5); //digger drop
    	if (key == 'R')
    		send(6); //digger up
    	
    	if (key == 'T')
    		send(7); //bucket dump
    	if (key == 'G')
    		send(8); //bucker retract
    	
    	if (key == ' ')
    		send(0);
    	
    	System.out.println(key + " " + powerLevel1 + " " + powerLevel2);
    }

    public void keyReleased(KeyEvent e)
    {
    	char key = (char) e.getKeyCode();
    	keyDown[key] = false;
    	
    	if (!keyDown['W'] && !keyDown['A'] && !keyDown['S'] && !keyDown['D']
    			&& (key == 'W' || key == 'A' || key == 'S' || key == 'D'))
    	{
    		send(0); //stop
    	}
    }

    public void send(int num)
    {
        out.write(num);
        out.flush();        
    }
    
    public void send(int mode, int powerLevel1, int powerLevel2)
    {
        out.write(mode);
        out.write(powerLevel1);
        out.write(powerLevel2);
        out.flush();
    }


    public void keyTyped(KeyEvent e)
    {
    }

    public JPanel getPanel() { return panel; }

    public static void main(String args[]) {
        JFrame frame = new JFrame("Binary Calculator");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setMinimumSize(new Dimension(320, 240));

        Control kalkulator = new Control();
        frame.add(kalkulator);

        frame.pack();
        frame.setVisible(true);
        kalkulator.getPanel().requestFocusInWindow();
    }

}
