package view;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.util.ArrayList;

import javax.swing.JFrame;
import javax.swing.JPanel;

import ds.Pair;

public class Pie extends JPanel
{
    int value[];
    String label[];
    int start = 0;
    int start2 = 360;

    Color[] colors = {Color.red, Color.green, Color.blue, Color.orange, Color.cyan, Color.darkGray, Color.magenta, Color.black, Color.yellow, Color.pink};
    public Pie(ArrayList<Pair> pairs)
    {
        value = new int[pairs.size()];
        label = new String[pairs.size()];

        for(int i = 0; i<pairs.size(); i++)
        {
            value[i] = pairs.get(i).num;
            label[i] = pairs.get(i).country;
        }
    }

    public void paintComponent(Graphics g)  {
         super.paintComponent(g);
         if (value == null) {
             return;
         }
        for(int i = 0; i<value.length; i++) {
            g.setColor(colors[i%colors.length]);
            g.fillArc(150, 100, 400, 400, start, value[i]);
            int x = (int)(-20 + 350 + 240*Math.cos(Math.toRadians(start2 - value[i]/2)));
            int y = (int)(300 + 240*Math.sin(Math.toRadians(start2 - value[i]/2)));
            g.drawString(label[i], x, y);
            start2 = start2 - value[i];
            start = start + value[i];
        }

    }

//    public static void main(String args[])
//    {
//        JFrame f = new JFrame("Piechart");
//        Pie p = new Pie(new String[]{"72","72","72","72","72"});
//
//        f.add(p);
//        p.setPreferredSize(new Dimension(400, 400));
//        f.pack();
//        f.setLocationRelativeTo(null);
//        f.setVisible(true);
//        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
//
//        f.repaint();
//    }
}
