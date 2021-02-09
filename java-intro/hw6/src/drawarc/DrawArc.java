package drawarc;

import javax.swing.*;
import java.awt.*;

public class DrawArc extends JFrame {
    public DrawArc() {
        super("DrawArc");
        setSize(600, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);
        g.setColor(Color.GREEN);
        g.fillRect(296, 296, 8, 200);
        g.setColor(Color.BLUE);
        for (int i = 0; i < 4; i++) {
            g.fillArc(200, 200, 200, 200, 30 + i * 90, 30);
        }
        g.setColor(Color.BLACK);
        g.drawString("Welcome to Java World", 10, 500);
    }

    public static void main(String[] args) {
        DrawArc app = new DrawArc();
    }
}
