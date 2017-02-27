import java.awt.*;
import javax.swing.*;

public class DoodleView extends JFrame
{

	private Container container;
	private int minWeight = 500, minHeight = 450;

	public DoodleView(DoodlePanel doodlePanel)
	{
		this.setTitle("Doodle");
		this.setMinimumSize(new Dimension(minWeight, minHeight));
		this.setSize(804, 626);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		container = getContentPane();
		container.add(doodlePanel);

		setVisible(true);
	}
}
