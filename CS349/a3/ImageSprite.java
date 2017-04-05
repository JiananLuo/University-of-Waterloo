import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.geom.AffineTransform;
import java.awt.geom.NoninvertibleTransformException;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;
import java.awt.geom.RectangularShape;
import java.io.IOException;
import java.io.Serializable;

import java.net.URL;
import javax.imageio.ImageIO;

public class ImageSprite extends Sprite implements Serializable
{
	protected RectangularShape shape = null;

	public ImageSprite(int spriteType, int x, int y, double rotLimit, String path)
			throws IOException
	{
		super();
		this.x = x;
		this.y = y;
		this.type = spriteType;
		this.rotLimit = rotLimit;
		this.realScaled = 1.0;
		this.image = path;
		
		URL url = getClass().getResource(path);
		Image spriteImage = ImageIO.read(url);
		shape = new Rectangle2D.Double(0, 0, spriteImage.getWidth(null),
				spriteImage.getHeight(null));
		this.translateMatrix.translate(x, y);
	}

	public boolean pointInside(Point2D p)
	{
		AffineTransform fullTransform = this.getFullTransform();
		AffineTransform inverseTransform = null;
		try
		{
			inverseTransform = fullTransform.createInverse();
		}
		catch (NoninvertibleTransformException e)
		{
			e.printStackTrace();
		}
		Point2D newPoint = (Point2D) p.clone();
		inverseTransform.transform(newPoint, newPoint);
		return shape.contains(newPoint);
	}

	protected void drawSprite(Graphics2D g)
	{
		g.setColor(Color.BLACK);
		Image spriteImage = null;
		try
		{
			spriteImage = ImageIO.read(getClass().getResource(this.image));
		}
		catch (IOException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		g.drawImage(spriteImage, null, null);
	}

	public void setAnchorPoint(int x, int y)
	{
		this.anchorX = x;
		this.anchorY = y;
	}
}