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
    	int powerLevel = 1;
    	
    	if (key == 'W')
    		send(powerLevel, 1); //forward
    	if (key == 'S')
    		send(powerLevel, 2); //backwards
    	if (key == 'A')
    		send(powerLevel, 3); //turn left
    	if (key == 'D')
    		send(powerLevel, 4); //turn right
    }

    public void keyReleased(KeyEvent e)
    {
    	char key = (char) e.getKeyCode();
    	keyDown[key] = false;
    	
    	if (!keyDown['W'] && !keyDown['A'] && !keyDown['S'] && !keyDown['D'])
    		send(0); //stop
    	System.out.println(key);
    }
    public void send(int powerLevel, int mode)
    {
    	send(powerLevel + mode*4);
    }
    
    public void send(int num)
    {
        out.write(num);
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
