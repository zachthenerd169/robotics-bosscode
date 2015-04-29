
import java.awt.image.BufferedImage;
import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;

import javax.imageio.ImageIO;

import edu.ufl.digitalworlds.j4k.J4KSDK;
/*
 * Copyright 2011-2014, Digital Worlds Institute, University of 
 * Florida, Angelos Barmpoutis.
 * All rights reserved.
 *
 * When this program is used for academic or research purposes, 
 * please cite the following article that introduced this Java library: 
 * 
 * A. Barmpoutis. "Tensor Body: Real-time Reconstruction of the Human Body 
 * and Avatar Synthesis from RGB-D', IEEE Transactions on Cybernetics, 
 * October 2013, Vol. 43(5), Pages: 1347-1356. 
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *     * Redistributions of source code must retain this copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce this
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
public class SimpleKinect extends J4KSDK {

	int counter=0;
	long time=0;
	
	@Override
	public void onSkeletonFrameEvent(boolean[] skeleton_tracked, float[] positions, float[] orientations, byte[] joint_status) {
//		System.out.println("A new skeleton frame was received.");
//		System.out.println("HELLO LUUUUUUUUKA");
	}

	@Override
	public void onColorFrameEvent(byte[] color_frame) {
		try {
			 
//			BufferedImage originalImage = ImageIO.read(new File(
//					"c:/darksouls.jpg"));
// 
//			// convert BufferedImage to byte array
//			ByteArrayOutputStream baos = new ByteArrayOutputStream();
//			ImageIO.write(originalImage, "jpg", baos);
//			baos.flush();
//			imageInByte = baos.toByteArray();
//			baos.close();
 
			// convert byte array back to BufferedImage
			byte[] imageInByte = color_frame;
			InputStream in = new ByteArrayInputStream(imageInByte);
			BufferedImage bImageFromConvert = ImageIO.read(in);
			bImageFromConvert = new BufferedImage(1280, 960, BufferedImage.TYPE_INT_RGB);
			for (int y = 0; y < 1280; y++)
			{
				for (int x = 0; x < 960; x++)
				{
					bImageFromConvert.setRGB(x, y, color_frame[y*960+x]);
				}
			}
 
			ImageIO.write(bImageFromConvert, "png", new File("c:/new-darksouls.png"));
 
		} catch (IOException e) {
			System.out.println(e.getMessage());
		}
		
		System.out.println(color_frame.length);
//		System.out.println("A new color frame was received.");
	}
	

	@Override
	public void onInfraredFrameEvent(short[] data) {
//		short[][] pixels = new short[640][480];
//		
//		for (int i = 0; i < data.length; i++)
//		{
//			int x = i % 640;
//			int y = i / 640;
//			pixels[x][y] = data[i];
//		}
//		
//		short maxVal = Short.MAX_VALUE;
//		for (int x = 0; x < 640; x++)
//		{
//			for (int y = 0; y < 480; y++)
//			{
//				if (pixels[x][y] < maxVal)
//					maxVal = pixels[x][y];
//			}
//		}
//		
//		System.out.println(maxVal);
//		
//		if(viewer==null || viewer.videoTexture==null || !use_infrared) return;
//		int sz=getInfraredWidth()*getInfraredHeight();
//		byte bgra[]=new byte[sz*4];
//		int idx=0;
//		int iv=0;
//		short sv=0;
//		byte bv=0;
//		for(int i=0;i<sz;i++)
//		{
//			sv=data[i];
//			iv=sv >= 0 ? sv : 0x10000 + sv; 
//			bv=(byte)( (iv & 0xfff8)>>6);
//			bgra[idx]=bv;idx++;
//			bgra[idx]=bv;idx++;
//			bgra[idx]=bv;idx++;
//			bgra[idx]=0;idx++;
//		}
//		
//		viewer.videoTexture.update(getInfraredWidth(), getInfraredHeight(), bgra);
	}


	@Override
	public void onDepthFrameEvent(short[] depth_frame, byte[] body_index, float[] XYZ, float[] UV) {
//		System.out.println("A new depth frame was received.");
		
//		DepthMap map=new DepthMap(getDepthWidth(),getDepthHeight(),XYZ);
////		map.setPlayerIndex(depth_frame, body_index);
////		if(UV!=null) map.setUV(UV);
////		map.setMaximumAllowedDeltaZ(5);
//		
//		float a[]=getAccelerometerReading();
//		a[0] = (a[0]*100)/100f;
//		a[1] = (a[1]*100)/100f;
//		a[2] = (a[2]*100)/100f;
//		
//		float maxX = Float.MIN_VALUE;
//		float maxY = Float.MIN_VALUE;
//		float maxZ = Float.MIN_VALUE;
//		float minX = Float.MAX_VALUE;
//		float minY = Float.MAX_VALUE;
//		float minZ = Float.MAX_VALUE;
//		
//		for (int i = 0; i < XYZ.length; i += 3)
//		{
//			if (XYZ[i] > maxX)
//				maxX = XYZ[i];
//			if (XYZ[i+1] > maxY)
//				maxY = XYZ[i+1];
//			if (XYZ[i+2] > maxZ)
//				maxZ = XYZ[i+2];
//			if (XYZ[i] < minX)
//				minX = XYZ[i];
//			if (XYZ[i+1] < minY)
//				minY = XYZ[i+1];
//			if (XYZ[i+2] < minZ)
//				minZ = XYZ[i+2];
//		}
//		
//		minX *= 100f;
//		minY *= 100f;
//		minZ *= 100f;
//		maxX *= 100f;
//		maxY *= 100f;
//		maxZ *= 100f;
//		
//		System.out.println(XYZ[i] + "\t" + XYZ[i+1] + "\t" + XYZ[i+2]);
//		System.out.println(a[0] + "\t" + a[1] + "\t" + a[2] + "\t" + minX + "\t" + minY + "\t" + minZ + "\t" + maxX + "\t" + maxY + "\t" + maxZ);
//		System.out.println(XYZ[0] + "\t" + XYZ[1] + "\t" + XYZ[2]);
		
//		if(counter==0)
//			time=new Date().getTime();
//		counter+=1;
	}
//	
//	public static void main(String[] args)
//	{
//		
//		if(System.getProperty("os.arch").toLowerCase().indexOf("64")<0)
//		{
//			System.out.println("WARNING: You are running a 32bit version of Java.");
//			System.out.println("This may reduce significantly the performance of this application.");
//			System.out.println("It is strongly adviced to exit this program and install a 64bit version of Java.\n");
//		}
//		
//		System.out.println("This program will run for about 30 seconds.");
//		SimpleExample kinect=new SimpleExample();
////		kinect.start(J4KSDK.COLOR|J4KSDK.DEPTH|J4KSDK.XYZ|J4KSDK.INFRARED|J4KSDK.SKELETON);
////		kinect.start(J4KSDK.XYZ);
//		kinect.start(J4KSDK.INFRARED);
//		short[] output = kinect.getInfraredFrame();
//		
//		System.out.println();
//		
//		//Sleep for 30 seconds.
////		try {Thread.sleep(3000000);} catch (InterruptedException e) {}
//		
//		
//		kinect.stop();		
////		System.out.println("FPS: "+kinect.counter*1000.0/(new Date().getTime()-kinect.time));
//	}

	
}
