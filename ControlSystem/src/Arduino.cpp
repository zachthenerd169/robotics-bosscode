#include "../Arduino.h"

void Arduino::writeToMotors(std::string message)
{
    cout<<"mode "<<mode << " powerLevel: "<<powerLevel<<endl;
    //int fd=-1; //status
    const char* port="/dev/cu.usbmodem1411"; //default for stephanie's laptop
    const char* test_message="hello arduino!";
    int rc; //status
    
    char* buf=(char*)malloc(BUF_MAX*sizeof(char));
    char eolchar = '\n'; //when receive messages line by line
    
    printf("setting baud rate to %d\n", BAUDRATE);
    cout<<"setting serial port to: "<<port<<endl;
    
    /*fd = serialport_init(port, BAUDRATE); //opening port
    (fd == -1) ? cout<< "couldn't open port" << endl : cout<< "opened port " << port << endl;
    serialport_flush(fd);
    
    fd==-1 ? cout<<"serial port not opened"<<endl : printf("sending messages: %d %d\n", mode, powerLevel); //sending test message*/
    
    // Sends over the mode
    // Accounts for little-endian and big-endian machines
    char highMode = (mode >> (8*3)) & 0xff;
    char lowMode = (mode >> (8*0)) & 0xff;
    char modeToSend = highMode >  lowMode ? highMode : lowMode;
    printf("modetosend: %c\n", modeToSend+48);
    rc = serialport_writebyte(fd, modeToSend); //writing the to the arduino
    if(rc==-1) perror("error writing");
    
    // Send over the power level if it is valid
    if(powerLevel >= 0) {
        // Accounts for little-endian and big-endian machines
        char highPower = (powerLevel >> (8*3)) & 0xff;
        char lowPower = (powerLevel >> (8*0)) & 0xff;
        char powerToSend = highPower > lowPower ? highPower : lowPower;
        rc = serialport_writebyte(fd, powerToSend); //writing the to the arduino
        if(rc==-1) perror("error writing");
    }
    
    if( fd == -1) perror("serial port not opened");
    memset(buf,0,BUF_MAX); //clearing buffer
    serialport_read_until(fd, buf, eolchar, BUF_MAX, TIMEOUT); //'Arduino received <message>'
    printf("in write arduino: %s\n", buf); //printing out what server receives from arduino
   
    return buf;
    
    //WHEN YOU DON'T HAVE AN ARDUINO JUST USE THIS
    //have to do some shit to get char*
    /*string arduinoMess = "Arduino received ";
    char *tempMess = new char[arduinoMess.length() + 1];
    strcpy(tempMess, arduinoMess.c_str());
    return strcat(tempMess, message); //returning message received from arduino (test)
    return NULL;*/
}