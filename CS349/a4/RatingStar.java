import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import javax.swing.JPanel;

public class RatingStar extends JPanel
{
	private int width;
	private int height;

	int index;
	boolean rated;
	boolean isFilter;

	RatingStar(int index, int width, int height, boolean isFilter)
	{
		this.index = index;
		this.rated = false;
		this.isFilter = isFilter;

		this.width = width;
		this.height = height;

		this.setPreferredSize(new Dimension(this.width, this.height));

		initMouseListener();
	}

	private void initMouseListener()
	{
		this.addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e)
			{
				if (isFilter)
				{
					RatingFilterPanel parent = (RatingFilterPanel) RatingStar.this.getParent();
					parent.setRating(RatingStar.this.index);
				}
				else
				{
					RatingPanel parent = (RatingPanel) RatingStar.this.getParent();
					parent.setRating(RatingStar.this.index);
				}
			}
		});
	}

	public void setRated(boolean rated)
	{
		this.rated = rated;
		this.repaint();
	}

	public void paint(Graphics g)
	{
		g.drawImage((rated) ? Main.rating1 : Main.rating0, 0, 0, this.width, this.height, this);
	}
}
