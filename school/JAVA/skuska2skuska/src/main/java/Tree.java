import lombok.Getter;
import lombok.Setter;

import java.awt.*;

public class Tree {
    @Getter
    @Setter
    private int x;
    @Getter
    @Setter
    private int y;
    @Getter
    private  int sirka;
    @Getter
    private  int vyska;
    @Getter
    @Setter
    private Color color;



    public Tree(int stlaceneX, int stlaceneY, int pusteneX, int pusteneY, Color color) {
        this.sirka = Math.abs(pusteneX - stlaceneX);
        this.vyska = Math.abs(pusteneY - stlaceneY);
        this.x = this.mensieCislo(pusteneX, stlaceneX);
        this.y = this.mensieCislo(pusteneY, stlaceneY);
        this.color = color;

    }
    public int mensieCislo(int cislo1, int cislo2) {
        return Math.min(cislo1, cislo2);
    }



}

