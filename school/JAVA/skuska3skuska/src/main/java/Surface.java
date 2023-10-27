import lombok.Getter;
import lombok.Setter;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.util.ArrayList;
import java.util.List;

public class Surface extends JPanel {


    List<Tree> trees;


    @Getter
    @Setter
    List<Line> lines;
    @Getter
    @Setter
    List<Objects> tvary;
    Point p;

    public Surface() {
        trees = new ArrayList<>();

        lines = new ArrayList<>();
        tvary = new ArrayList<>();
        p = new Point();
    }


    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        for (Objects objects : tvary) {
            g.setColor(objects.getColor());
            objects.paintComponent(g);
        }
        for (Line line : lines) {
            g.setColor(line.getColor());
            g.drawLine(line.getX(),line.getY(),line.getLastClickX(),line.getLastClickY());
        }

    }
    public Objects getObject(Point p) {
        for (Objects objects : tvary) {
            if (objects.findContain(p) != null)
                return objects;
        }
        return null;
    }
}






