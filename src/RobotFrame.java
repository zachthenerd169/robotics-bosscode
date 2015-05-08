import java.awt.BorderLayout;

import javax.swing.JFrame;

import edu.ufl.digitalworlds.j4k.J4KSDK;

public class RobotFrame extends JFrame
{
	public RobotPanel panel;
	
	public RobotFrame()
	{
		super("Test");
		SimpleKinect kinect=new SimpleKinect();
//		kinect.start(J4KSDK.DEPTH);
//		kinect.start(J4KSDK.XYZ);
//		kinect.start(J4KSDK.INFRARED);
		kinect.start(J4KSDK.COLOR);

		try {Thread.sleep(1000);} catch (InterruptedException e) {}
		
		panel = new RobotPanel(kinect);
		add(panel, BorderLayout.CENTER);
		
//		while (true)
//		{
//			System.out.println("oh no");
//			panel.repaint();
//			
//			try {Thread.sleep(1000);} catch (InterruptedException e) {}
//		}
	}
	
	public static void main(String[] args)
	{
		RobotFrame robotFrame = new RobotFrame();
		robotFrame.setSize(1800, 900);
		robotFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		robotFrame.setVisible(true);
	}
}
