import java.awt.Color;
import java.awt.Graphics;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import javax.swing.JPanel;


public class RobotPanel extends JPanel
{
	public SimpleKinect kinect;
	
	private ExecutorService threadExecutor = Executors.newCachedThreadPool();
	
	public float[][] heightmap = new float[1000][1000];
	
	public RobotPanel(SimpleKinect kinect)
	{
		this.kinect = kinect;
		threadExecutor.execute(new Runnable() {

			@Override
			public void run() {
				// TODO Auto-generated method stub
				while (true)
				{
//					System.out.println("Hi");
					update();
					repaint();
					
					try {Thread.sleep(100);} catch (InterruptedException e) {e.printStackTrace();}
				}
			}
			
		});
	}
	
	public void update()
	{
		
	}
	
	public void paintComponent(Graphics g)
	{
//		drawBlue(g);
		drawInfrared(g);
	}
	
	public void drawBlue(Graphics g)
	{
		byte[] output = kinect.getColorFrame();
		
		int smallestValue = 50000;
		int largestValue = -50000;
		
//		System.out.println(output.length);
		
		int[][] image = new int[640][480];
		
		for (int i = 0; i < output.length; i += 4)
		{
			int cb = output[i] & 0xFF;
			int cg = output[i+1] & 0xFF;
			int cr = output[i+2] & 0xFF;
			int ca = output[i+3] & 0xFF;
			
			int x = 639 - (i/4) % 640;
			int y = (i/4) / 640;
			
			image[x][y] = clamp255(cr*2 - penalty(cg) - penalty(cb));
		}
		
		int[][] origImage = new int[640][480];
		for (int i = 0; i < output.length; i += 4)
		{
			int x = 639 - (i/4) % 640;
			int y = (i/4) / 640;
			
			origImage[x][y] = image[x][y];
		}
		
		//copyo
//		int gaussAmt = 1;
//		int[][] oldImage = new int[640 + gaussAmt*2][482 + gaussAmt*2];
//		for (int j = 0; j < 1; j++)
//		{
//			for (int i = 0; i < output.length; i += 4)
//			{
//				int x = 639 - (i/4) % 640;
//				int y = (i/4) / 640;
//				
//				oldImage[x+1][y+1] = image[x][y];
//			}
//	
//			for (int i = 0; i < output.length; i += 4)
//			{
//				int x = 639 - (i/4) % 640;
//				int y = (i/4) / 640;
//	
//				int sum = 0;
//				
//				for (int yy = -gaussAmt; yy <= gaussAmt; yy++)
//				{
//					for (int xx = -gaussAmt; xx <= gaussAmt; xx++)
//					{
//						sum += oldImage[x+xx+gaussAmt][y+yy+gaussAmt];
//					}
//				}
//				sum /= (gaussAmt*2+1);
//				sum /= (gaussAmt*2+1);
//				sum = penalty(sum);
//	
//				image[x][y] = sum;
//			}
//		}

		for (int i = 0; i < output.length; i += 4)
		{
			int x = 639 - (i/4) % 640;
			int y = (i/4) / 640;
			
			g.setColor(new Color(origImage[x][y],origImage[x][y],origImage[x][y]));
			g.drawRect(x, y, 1, 1);
			g.setColor(new Color(image[x][y], image[x][y], image[x][y]));
			g.drawRect(x+640, y, 1, 1);
		}
	}
	
	public int siggy(int x)
	{
		double dx = x / 256.;
		double y = 1./(1.+Math.pow(Math.E, (-10.*(dx-0.5))));
		return (int) (y * 256.);
	}
	
	public int penalty(int x)
	{
		float fx = x / 256f;
		float func = -(fx-1)*(fx-1)+1;
		return (int) (func * 256f);
	}
	
	public void drawInfrared(Graphics g)
	{
		short[] output = kinect.getInfraredFrame();
		
		int smallestValue = 50000;
		int largestValue = -50000;
		
		System.out.println(output.length);
		
		for (int i = 0; i < output.length; i++)
		{
			int x = 640 - i % 640;
			int y = i / 640;
			
			if (output[i] < smallestValue && output[i] > 0)
				smallestValue = output[i];
			if (output[i] > largestValue)
				largestValue = output[i];
			
//			System.out.println(output[i]*255f/9768);
			g.setColor(new Color(clamp(0f, 1f, (output[i] - smallestValue)/10000f), clamp(0f, 1f, (output[i] - smallestValue)/25000f), clamp(0f, 1f, (output[i] - smallestValue)/31000f)));
			
//			drawPixel(g, x, y, 1);
			g.drawRect(2*x, 2*y, 2, 2);
		}
	}
	
	public void drawDepth(Graphics g)
	{
		super.paintComponent(g);

		float[] output = kinect.getXYZ();
		float[] acc = kinect.getAccelerometerReading();
		acc[0] *= 100f;
		acc[1] *= 100f;
		acc[2] *= 100f;
		
		System.out.println(acc[0] + " " + acc[1] + " " + acc[2]);
		
//		System.out.println(output.length);
		
		for (int i = 0; i < output.length; i += 3)
		{
			float scale = 300f;
			
			float x = output[i] * scale;
			float y = output[i+1] * scale;
			float z = output[i+2] * scale;
			
			if (x == 0 && z == 0)
				continue;
			
			int xNew = (int) clamp(0f, 999f, (int) x + 500);
			int zNew = (int) clamp(0f, 999f, (int) z + 500);
			
			heightmap[xNew][zNew] = y;
//			System.out.println(x + " " + z);
			
			g.drawRect((int) x + 500, (int) z, 3, 3);
		}

		
		
//		short[] output = kinect.getDepthFrame();
//		
//		int smallestValue = 50000;
//		int largestValue = -50000;
//		
//		for (int i = 0; i < output.length; i++)
//		{
//			int x = 320 - i % 320;
//			int y = i / 320;
//			
//			if (output[i] < smallestValue && output[i] > 0)
//				smallestValue = output[i];
//			if (output[i] > largestValue)
//				largestValue = output[i];
//		}
//		
//		for (int i = 0; i < output.length; i++)
//		{
//			int x = 320 - i % 320;
//			int y = i / 320;
//			
////			System.out.println(output[i]*255f/9768);
////			g.setColor(new Color(clamp(0f, 1f, (output[i] - smallestValue)/10000f), clamp(0f, 1f, (output[i] - smallestValue)/25000f), clamp(0f, 1f, (output[i] - smallestValue)/31000f)));
//			
////			drawPixel(g, x, y, 3);
//		}
//		
//		float[][] heightmap = new float[10000][10000];
//		
//		float robotX = 0;
//		float robotY = 0;
//		
//		float horFOV = (float) (57f * Math.PI / 180f);
//		float verFOV = (float) (43f * Math.PI / 180f);
//		
//		for (int i = 0; i < output.length; i++)
//		{
//			int arrX = 320 - i % 320;
//			int arrY = i / 320;
//			
//			float d = output[i];
//			float lenX = 320;
//			float lenY = 240;
//			
//			float absX = (float) (d * Math.sin(horFOV * arrX / lenX));
//			float absY = (float) (d * Math.cos(horFOV * arrX / lenX));
//			float absZ = (float) (d * Math.sin(verFOV * arrY / lenY)); //height
//			
//			int xNew = (int) clamp(0f, 9999f, absX+2000f);
//			int yNew = (int) clamp(0f, 9999f, absY-2000f);
//			heightmap[xNew][yNew] = absZ;
//		}
//		
//
//		for (int x = 0; x < heightmap.length; x++)
//		{
//			for (int y = 0; y < heightmap[0].length; y++)
//			{
//				float height = heightmap[x][y];
//				if (height != 0f) { }
////					System.out.println(height);
//				else
//					continue;
//				
//				float percent = clamp(0f, 1f, height);
////				System.out.println(x + " " + y + " " + percent);
//				g.setColor(new Color(1f, 0f, 0f));
//				g.fillRect((int) (x * 0.1f), (int) (y * 0.1f), 10, 10);
//				
////				drawPixel(g, x, y, 1f);
//			}
//		}
		
		
		
//		System.out.println(smallestValue);
//		System.out.println(largestValue);
//		System.out.println(output.length);
	}
	
	public float clamp(float min, float max, float num)
	{
		if (num < min)
			return min;
		if (num > max)
			return max;
		return num;
	}

	public int clamp255(int num)
	{
		if (num < 0)
			return 0;
		if (num > 255)
			return 255;
		return num;
	}

	public void drawPixel(Graphics g, int x, int y, float size)
	{
		g.fillRect((int) (x*size), (int) (y*size), (int) size, (int) size);
	}
}
