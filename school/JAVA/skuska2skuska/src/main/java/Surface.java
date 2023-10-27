import lombok.Getter;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.util.ArrayList;
import java.util.List;

public class Surface extends JPanel {
    @Getter
    List<Tree> trees;



    public Surface(){
        trees = new ArrayList<>();
    }
    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        for (Tree pic : trees) {
            g.setColor(pic.getColor());

            g.fillOval(pic.getX(), pic.getY(), pic.getSirka(), 2 * pic.getVyska() / 3);
            g.fillRect(pic.getX() + pic.getSirka() / 3, pic.getY() + pic.getVyska() / 2, pic.getSirka() / 3, pic.getVyska() / 2);

        }
    }

    public Tree getTrees(Point p){
        for (Tree pic: trees){
            Ellipse2D ellipse2D  = new Ellipse2D.Double(pic.getX(), pic.getY(), pic.getSirka(), 2 * pic.getVyska() / 3);
            Rectangle rec2 = new Rectangle(pic.getX() + pic.getSirka() / 3, pic.getY() + pic.getVyska() / 2, pic.getSirka() / 3, pic.getVyska() / 2);
            if (ellipse2D.contains(p) || rec2.contains(p))
                return pic;
        }
        return null;
    }

}
