package colorword;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ColorWord {
    private static Color[] colors = {Color.RED, Color.YELLOW, Color.MAGENTA};
    private static String[] colorStrings = {"red", "yellow", "magenta"};

    public static void main(String[] args) {
        JFrame frame = new JFrame("Color World");
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.setSize(300, 300);
        JPanel contentPanel = new JPanel();
        JTextField textField = new JTextField("Color World");
        textField.setFont(new Font("Arial", Font.PLAIN, 30));
        textField.setEditable(false);
        textField.setBorder(BorderFactory.createLineBorder(Color.BLACK));
        contentPanel.add(textField);
        ButtonGroup colorButtonGroup = new ButtonGroup();
        JRadioButton[] colorButtons = new JRadioButton[3];
        JPanel colorButtonPanel = new JPanel();
        for (int i = 0; i < 3; i++) {
            colorButtons[i] = new JRadioButton(colorStrings[i]);
            colorButtons[i].addActionListener(new ColorButtonListener(colors[i], textField));
            colorButtonGroup.add(colorButtons[i]);
            colorButtonPanel.add(colorButtons[i]);
        }
        contentPanel.add(colorButtonPanel);
        frame.setContentPane(contentPanel);
        frame.setVisible(true);
    }
}

class ColorButtonListener implements ActionListener {
    private Color color;
    private JTextField textField;

    ColorButtonListener(Color c, JTextField tf) {
        color = c;
        textField = tf;
    }

    @Override
    public void actionPerformed(ActionEvent actionEvent) {
        textField.setForeground(color);
    }
}
