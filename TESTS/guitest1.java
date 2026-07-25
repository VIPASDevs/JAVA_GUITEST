//'*' means import everything within 'Swing'import java.swing.*;
import javax.swing.*; //Swing provides GUI components (windows, buttons, labels, text fields, and more I do not know yet)
import java.awt.*; //AWT provides managers such as colours, layout, fonts, and others I do not know yet

public class guitest1 {
	public static void main(String[] args) {
		//JFrame creats a new window (hence the name JFrame, assuming it means JAVA Frame).
		JFrame frame = new JFrame("GUI TEST");
		
		//This following line sets the size. Look further into it
		frame.setSize(400, 300); //it goes "(Width, Height);"
		
		//This following line tells the program what the 'X' button does (commonly known as the 'Close Window/Application Button'
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		//This following line creates a neat little button
		JButton button = new JButton("CLICK HERE"); //whatever is in the qoutes appear on the button)
		
		
		//This following line(s) requests a "ActionListener"
		//This tells JAVA to do something when the button is clicked
		button.addActionListener( e -> //e represents the ActionListener object describing the click
			//Displays a pop-up dialog
			//frame = parent window that owns it
			JOptionPane.showMessageDialog(frame, "Hello, World!")
		);
		
		
		//Set the layout manager
		//FlowLayout places like this: BUTTON1, BUTTON2, BUTTON3, and so on
		frame.setLayout(new FlowLayout());
		
		
		//This following line adds the button to the window
		//Creating a component is not enough, has to be added to a container
		frame.add(button);
		
		
		//Following line makes it visible. Before this, it only exists in memory
		frame.setVisible(true);
	}
}
