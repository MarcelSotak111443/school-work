import lombok.Getter;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.List;

public class Surface extends JPanel {
    @Getter
    List<Cross> crosses;
    @Getter
    List<Line> lines;


    public Surface() {
        crosses = new ArrayList<>();
        lines = new ArrayList<>();
        this.setLayout(new BorderLayout());
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        for (Cross pic : crosses) {
            g.setColor(pic.getColor());


            g.fillRect(pic.getX(), pic.getY() + pic.getVyska() / 3, pic.getSirka(), pic.getVyska() / 3);
            g.fillRect(pic.getX() + pic.getSirka() / 3, pic.getY(), pic.getSirka() / 3, pic.getVyska());

        }
        for (Line line : lines){
            g.setColor(line.getColor());
            g.drawLine(line.getX(),line.getY(),line.getLastClickX(),line.getLastClickY());
        }
    }
    public int WTF(){
        return crosses.size();
    }
    //ZISTI CI SA NACHADZA TAM KDE MA
    public Cross getCross(Point p){
        for (Cross pic: crosses){
            Rectangle rec = new Rectangle(pic.getX() , pic.getY() + pic.getVyska()/3, pic.getSirka(),  pic.getVyska() / 3);
            Rectangle rec2 = new Rectangle(pic.getX() + pic.getSirka() / 3, pic.getY() , pic.getSirka() / 3, pic.getVyska());
            if (rec.contains(p) || rec2.contains(p))
                return pic;
        }
        return null;
    }
}

