import java.awt.*;
import javax.swing.*;

public class PaperDollView extends JFrame
{
	private Container container;
	private int weight = 1280, height = 800;

	public PaperDollView(DollPanel paperDollPanel, JMenuBar menubar)
	{
		this.setJMenuBar(menubar);
		this.setTitle("PaperDoll");
		this.setSize(weight, height);
		this.setResizable(false);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		container = getContentPane();
		container.add(paperDollPanel);

		setVisible(true);
	}
}