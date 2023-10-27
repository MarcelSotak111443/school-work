import javax.swing.*;
import java.awt.*;

public abstract class Objects extends JPanel {
    public abstract Objects findContain(Point p);
    public abstract Color getColor();
    public abstract void paintComponent(Graphics g);
    public abstract void setX(int x);

    public abstract void setY(int y);
    public abstract void setAplhla();

}
