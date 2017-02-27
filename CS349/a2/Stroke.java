import java.awt.Color;
import java.awt.Point;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class Stroke implements Serializable
{
	private Color color;
	private int thickness;
	private ArrayList<Point> points;

	public Stroke(Color color, int thickness)
	{
		this.color = color;
		this.thickness = thickness;
		this.points = new ArrayList<Point>();
	}

	public List<Point> getPoints()
	{
		return this.points;
	}

	public int getNumOfPoints()
	{
		return this.points.size();
	}

	public Color getColor()
	{
		return this.color;
	}

	public int getThickness()
	{
		return this.thickness;
	}

	public void addPoint(Point p)
	{
		points.add(p);
	}

	public void removeLastNPoints(int lastN)
	{
		this.points.subList(points.size() - lastN, points.size()).clear();
	}
}
