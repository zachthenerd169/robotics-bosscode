import java.awt.AWTEvent;
import java.awt.Toolkit;
import java.awt.event.AWTEventListener;

import javax.swing.JFrame;

public class TestConsoleKeyInputListener extends JFrame{
      
      public TestConsoleKeyInputListener() {
            Toolkit defaultTookKit = Toolkit.getDefaultToolkit();
            defaultTookKit.addAWTEventListener(new AWTEventListener() {
                  public void eventDispatched(AWTEvent event) {
                        System.out.println("HELLO");
                  }
            }, AWTEvent.KEY_EVENT_MASK);
            
            AWTEventListener[] listeners = defaultTookKit.getAWTEventListeners();
            System.out.println(listeners.length);
      }
      
      public static void main(String[] args) {
            JFrame frame = new TestConsoleKeyInputListener();
            frame.setSize(0, 0);
            frame.pack();
            frame.show();
      }
}
