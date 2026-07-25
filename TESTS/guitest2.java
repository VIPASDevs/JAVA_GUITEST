import javax.swing.*;
import java.awt.*;

public class guitest2 {
	public static void main(String[] args) {
		JFrame frame = new JFrame("TYPE TEST");
		
		JTextField textField = new JTextField(20); //creates a field for text
		//"20" creates 20 collumns, I estimate each collums to be an inch (do not know the actual PX for that)
		JButton button = new JButton("SUBMIT");
		
		button.addActionListener( e -> {
			String text = textField.getText(); //gets text input
			JOptionPane.showMessageDialog(frame, "YOU TYPED: " + text);
		});
		
		frame.setLayout(new FlowLayout()); //creates the layout
		
		frame.add(textField); //adds it to the frame
		frame.add(button); //adds it to the frame
		
		frame.setSize(400, 300); //sets the size. Width first, Height second
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); //allows the 'X' button to close it
		frame.setVisible(true); //allows it to be drawn
	}
}
