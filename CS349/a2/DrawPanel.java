import javax.swing.BorderFactory;
import javax.swing.JPanel;
import javax.swing.Timer;

import java.awt.*;
import java.awt.event.*;
import java.util.List;

public class DrawPanel extends JPanel implements Observer, ActionListener
{
	static final int TIME_BETWEEN_FRAMES_IN_MS = 10;
	private Stroke currentStroke;
	private Model model;

	Timer timer = new Timer(17, (ActionListener) this);

	public DrawPanel(Model model)
	{
		super();
		this.model = model;
		this.setLayout(new BorderLayout());
		this.setBorder(BorderFactory.createLineBorder(Color.GRAY));

		initMouseListener(model);
	}

	private void initMouseListener(Model model)
	{
		this.addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e)
			{
				if (model.getTotalPoint() != model.getCurrentPoint())
				{
					model.removeLastNPoints(model.getTotalPoint() - model.getCurrentPoint());
				}
				int currentPoints = model.getCurrentPoint();
				currentStroke = new Stroke(model.getColor(), model.getThickness());
				currentStroke.addPoint(new Point(e.getX(), e.getY()));
				currentStroke.addPoint(new Point(e.getX(), e.getY()));
				currentPoints += 2;
				model.setCurrentPoint(currentPoints);
				model.addStroke(currentStroke);
			}

		});
		this.addMouseMotionListener(new MouseMotionAdapter() {
			public void mouseDragged(MouseEvent e)
			{
				currentStroke.addPoint(new Point(e.getX(), e.getY()));
				int currentPoints = DrawPanel.this.model.getCurrentPoint();
				currentPoints += 1;
				DrawPanel.this.model.setCurrentPoint(currentPoints);
			}
		});
	}

	public void paintComponent(Graphics g)
	{
		super.paintComponents(g);
		Graphics2D g2 = (Graphics2D) g;
		List<Stroke> strokes = model.getStrokes();
		Stroke currentStroke;
		int pointsLeftCount = model.getCurrentPoint();
		for (int i = 0; i < model.getCurrentFrame(); i++)
		{
			currentStroke = strokes.get(i);
			int currentStrokePoints = currentStroke.getNumOfPoints();
			if (pointsLeftCount >= currentStrokePoints)
			{
				drawStroke(g2, currentStroke, model.isPlayMode(), currentStroke.getNumOfPoints());
				pointsLeftCount -= currentStrokePoints;
			}
			else
			{
				drawStroke(g2, currentStroke, model.isPlayMode(), pointsLeftCount);
				break;
			}
		}
	}

	public void drawStroke(Graphics2D g2, Stroke stroke, boolean playMode, int currentPointsCount)
	{
		g2.setColor(stroke.getColor());
		g2.setStroke(new BasicStroke(stroke.getThickness()));
		List<Point> p = stroke.getPoints();
		for (int j = 0; j < currentPointsCount - 1; j++)
		{
			g2.drawLine(p.get(j).x, p.get(j).y, p.get(j + 1).x, p.get(j + 1).y);
		}
	}

	@Override
	public void update(Object observable)
	{
		repaint();
		if (model.isPlayMode())
		{
			timer.start();
		}
	}

	@Override
	public void actionPerformed(ActionEvent e)
	{
		if (model.isPlayMode())
		{
			int currPoint = model.getCurrentPoint();
			int endPoint;
			int diffPoint;
			if (model.isPlayMode())
			{
				if (model.isPlayBackward())
				{
					endPoint = 0;
					diffPoint = -1;
				}
				else
				{
					endPoint = model.getTotalPoint();
					diffPoint = 1;
				}
				if (currPoint != endPoint)
				{
					currPoint += diffPoint;
					model.setCurrentPoint(currPoint);
				}
				else
				{
					model.setPlayMode(false);
				}
			}
			else
			{
				timer.stop();
			}
		}
	}
}
