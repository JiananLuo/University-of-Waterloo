import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.GridLayout;

import javax.swing.JPanel;

public class DotModel extends JPanel implements Observer
{
	private Model model;

	public DotModel(Model model)
	{
		this.model = model;
		this.setLayout(new GridLayout(1, 1));
        setPreferredSize(new Dimension(this.getWidth(), 50));
        setMinimumSize(new Dimension(this.getWidth(), 50));
        setMaximumSize(new Dimension(this.getWidth(), 250));
	}

	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		int thickness = model.getThickness();
		g.setColor(model.getColor());
		g.fillOval(this.getWidth()/2-thickness, this.getHeight()/2-thickness, thickness * 2, thickness * 2);
	}

	@Override
	public void update(Object observable)
	{
		repaint();

	}
}
