import java.awt.image.*;
import java.io.File;
import java.io.IOException;
import javax.imageio.*;
 
public class HoughTransform
{
	//transforms the original image data in the inputData object and
	//creates the hough space
	public static ArrayData houghTransform(ArrayData inputData, int thetaAxisSize, int rAxisSize, int minContrast)
	{
	    int width = inputData.width;
	    int height = inputData.height;
	    int maxRadius = (int)Math.ceil(Math.hypot(width, height));
//	    System.out.println("width: " +  width);
//	    System.out.println("height: " + height);
//	    System.out.println(maxRadius);
	    int halfRAxisSize = rAxisSize >>> 1;
	    ArrayData outputData = new ArrayData(thetaAxisSize, rAxisSize);
	    // x output ranges from 0 to pi
	    // y output ranges from -maxRadius to maxRadius
	    double[] sinTable = new double[thetaAxisSize];
	    double[] cosTable = new double[thetaAxisSize];
	    for (int theta = thetaAxisSize - 1; theta >= 0; theta--)
	    {
		    double thetaRadians = theta * Math.PI / thetaAxisSize;
		    sinTable[theta] = Math.sin(thetaRadians);
		    cosTable[theta] = Math.cos(thetaRadians);
	    }
 
	    for (int y = height - 1; y >= 0; y--)
	    {
	    	for (int x = width - 1; x >= 0; x--)
	    	{
	    		if (inputData.contrast(x, y, minContrast))
	    		{
	    			for (int theta = thetaAxisSize - 1; theta >= 0; theta--)
	    			{
	    				double r = cosTable[theta] * x + sinTable[theta] * y;
	    				int rScaled = (int)Math.round(r * halfRAxisSize / maxRadius) + halfRAxisSize;
	    				outputData.accumulate(theta, rScaled, 1);
	    			}
	    		}
	    	}
	    }
	    return outputData;
	}
 
	public static ArrayData getArrayDataFromImage(String filename) throws IOException
	{
		BufferedImage inputImage = ImageIO.read(new File(filename));
		int width = inputImage.getWidth();
		int height = inputImage.getHeight();
		int[] rgbData = inputImage.getRGB(0, 0, width, height, null, 0, width);
    	ArrayData arrayData = new ArrayData(width, height);
    	// Flip y axis when reading image
    	for (int y = 0; y < height; y++)
    	{
    		for (int x = 0; x < width; x++)
    		{
    			int rgbValue = rgbData[y * width + x];
    			rgbValue = (int)(((rgbValue & 0xFF0000) >>> 16) * 0.30 + ((rgbValue & 0xFF00) >>> 8) * 0.59 + (rgbValue & 0xFF) * 0.11);
    			arrayData.set(x, height - 1 - y, rgbValue);
    		}
    	}
    	return arrayData;
	}
 
	public static void writeOutputImage(String filename, ArrayData arrayData) throws IOException
	{
		int max = arrayData.getMax();
		BufferedImage outputImage = new BufferedImage(arrayData.width, arrayData.height, BufferedImage.TYPE_INT_ARGB);
		for (int y = 0; y < arrayData.height; y++)
		{
			for (int x = 0; x < arrayData.width; x++)
			{
				int n = Math.min((int)Math.round(arrayData.get(x, y) * 255.0 / max), 255);
				outputImage.setRGB(x, arrayData.height - 1 - y, (n << 16) | (n << 8) | 0x90 | -0x01000000);
			}
		}
		ImageIO.write(outputImage, "PNG", new File(filename));
		return;
	}
  
	//added code by me
	public static void getLines(ArrayData arrayData)
	{
		int width = arrayData.width;
		int height = arrayData.height;
		//set the max values so we can see what we get
		int max1 = -1, max2 = -1, max3 = -1, max4 = -1, max5 = -1;
		int value;
		int x1=0,y1=0,x2=0,y2=0,x3=0,y3=0,x4=0,y4=0,x5=0,y5=0;
		
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				value = arrayData.get(x,y);
				if(value > max1)
				{
					max1 = value;
					x1 = x;
					y1 = y;
				}
				else if(value > max2)// && value != max1 && value != max3 && value != max4 && value != max5)
				{
					max2 = value;
					x2 = x;
					y2 = x;
				}
				else if(value > max3)// && value != max1 && value != max2 && value != max4 && value != max2)
				{
					max3 = value;
					x3 = x;
					y3 = y;
				}
				else if (value > max4)// && value != max1 && value != max2 && value != max3 && value != max5)
				{
					max4 = value;
					x4 = x; 
					y4 = y;
				}
				else if(value>max5)// && value != max1 && value != max2 && value != max3 && value != max4 )
				{
					max5 = value;
					x5 = x;
					y5 = y;
				}
			}
		}
		// x output ranges from 0 to pi
	    // y output ranges from -maxRadius to maxRadius
	    int maxRadius = (int)Math.ceil(Math.hypot(width, height)); //line stolen from HoughTransform function
		
		//calculate and output the line values
	    //convert rho values
	    //maxRadius is 400 for this program
	    // subtract 240 to place 0 in middle of y axis and allow for neg values
	    //convert size by multiplying by maxRadius/240;
	    
		double rho1 = (y1 - 240)*(maxRadius/240);
		double rho2 = (y2 - 240)*(maxRadius/240);
		double rho3 = (y3 - 240)*(maxRadius/240);
		double rho4 = (y4 - 240)*(maxRadius/240);
		double rho5 = (y5 - 240)*(maxRadius/240);

		double theta1 = (x1/640.0)*2*Math.PI;
		double theta2 = (x2/640.0)*2*Math.PI;
		double theta3 = (x3/640.0)*2*Math.PI;
		double theta4 = (x4/640.0)*2*Math.PI;
		double theta5 = (x5/640.0)*2*Math.PI;
		
		System.out.println("Max1: "+max1+"\n\tx:"+x1+"\n\ty:"+y1+"\n\trho:"+rho1+"\n\ttheta: "+theta1);
		System.out.println("Max2: "+max2+"\n\tx:"+x2+"\n\ty:"+y2+"\n\trho:"+rho2+"\n\ttheta: "+theta2);
		System.out.println("Max3: "+max3+"\n\tx:"+x3+"\n\ty:"+y3+"\n\trho:"+rho3+"\n\ttheta: "+theta3);
		System.out.println("Max4: "+max4+"\n\tx:"+x4+"\n\ty:"+y4+"\n\trho:"+rho4+"\n\ttheta: "+theta4);
		System.out.println("Max5: "+max5+"\n\tx:"+x5+"\n\ty:"+y5+"\n\trho:"+rho5+"\n\ttheta: "+theta5);
		
	}
 
//	public static void main(String[] args) throws IOException
//	{	
//		String[] bargs = {"Paper.jpg", "HoughTransformImage.png", "640", "480", "100"};
//		ArrayData inputData = getArrayDataFromImage(bargs[0]);
//		int minContrast = (bargs.length >= 4) ? 64 : Integer.parseInt(bargs[4]);
//		ArrayData outputData = houghTransform(inputData, Integer.parseInt(bargs[2]), Integer.parseInt(bargs[3]), minContrast);
//		writeOutputImage(bargs[1], outputData);
//		getLines(outputData);
//		return;
//	}
}