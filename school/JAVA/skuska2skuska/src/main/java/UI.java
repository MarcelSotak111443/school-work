import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class UI implements ActionListener {

    private JButton tree;
    private JButton move;

    // private EnumChosenObject enumChosenObject;
    private Surface surface;
    private Logic logic;
    private Color color;
    private JLabel label;
    private JButton buttonChanceColor;
    private Color[] colorsPaletter;
    //  private EnumActivity enumActivity;
    private EnumAction enumAction;
    private int i;


    public UI() {
        //   enumChosenObject = EnumChosenObject.CROSS;
        //   enumActivity = EnumActivity.DEFAULT;
        i = 0;
        surface = new Surface();
        logic = new Logic(surface);
        enumAction = EnumAction.TREE;
        colorsPaletter = new Color[3];
        colorsPaletter[0] = Color.RED;
        colorsPaletter[1] = Color.CYAN;
        colorsPaletter[2] = Color.GRAY;


        JFrame jFrame = new JFrame();
        jFrame.setSize(800, 800);
        jFrame.setResizable(true);
        jFrame.setFocusable(true);
        jFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        jFrame.setLayout(new BorderLayout());

        //3 buttony
        JPanel jpanelTop = new JPanel(new GridLayout(1, 4));
        tree = new JButton("TREE");
        move = new JButton("MOVE");
        buttonChanceColor = new JButton("CHANGE COLOR");


        label = new JLabel("Vyber", SwingConstants.CENTER);

        label.setOpaque(true);

        jpanelTop.add(tree);
        jpanelTop.add(move);
        jpanelTop.add(label);
        jpanelTop.add(buttonChanceColor);


        tree.addActionListener(this);
        move.addActionListener(this);
        buttonChanceColor.addActionListener(this);

        jFrame.add(surface);

        jFrame.add(jpanelTop, BorderLayout.NORTH);
        surface.addMouseMotionListener(logic);
        surface.addMouseListener(logic);
        surface.setFocusable(true);

        //   jFrame.setFocusable(true);
        jFrame.setVisible(true);

    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource().equals(tree)){
            label.setText("KRESLENIE");
            enumAction = EnumAction.TREE;

        }
        if (e.getSource().equals(move)){
            label.setText("PRESUVANIE");
            enumAction = EnumAction.MOVING;
        }

        if (e.getSource().equals(buttonChanceColor)){
            label.setBackground(colorsPaletter[i]);
            logic.setColor(colorsPaletter[i]);
            i++;
            if (i > 2)
                i = 0;
        }
        logic.setEnumAction(enumAction);
    }
}
    
