import java.util.Enumeration;

import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;


public class SerialTestFour 
{
	SerialPort serialPort;
	CommPortIdentifier portId = null;
	Enumeration portEnum = CommPortIdentifier.getPortIdentifiers();
	public void initialize()
	{
		while (portEnum.hasMoreElements()) 
		{
			CommPortIdentifier currPortId = (CommPortIdentifier) portEnum.nextElement();
		}
	

	}
}
