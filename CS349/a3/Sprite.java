import java.awt.Graphics2D;
import java.awt.event.MouseEvent;
import java.awt.geom.AffineTransform;
import java.awt.geom.Point2D;
import java.io.Serializable;
import java.util.Vector;

/**
 * A building block for creating your own shapes that can be transformed and
 * that can respond to input. This class is provided as an example; you will
 * likely need to modify it to meet the assignment requirements.
 * 
 * Michael Terry & Jeff Avery
 */
public abstract class Sprite implements Serializable
{
	static int SPRITE_TYPE_TORSO = 0;
	static int SPRITE_TYPE_HEAD = 1;
	static int SPRITE_TYPE_UPPER_ARM = 2;
	static int SPRITE_TYPE_LOWER_ARM = 3;
	static int SPRITE_TYPE_HAND = 4;
	static int SPRITE_TYPE_UPPER_LEG = 5;
	static int SPRITE_TYPE_LOWER_LEG = 6;
	static int SPRITE_TYPE_FOOT = 7;

	protected enum InteractionMode
	{
		IDLE, DRAGGING, SCALING, ROT_AND_SCALE
	}

	private Sprite parent = null;
	private Vector<Sprite> children = new Vector<Sprite>();

	protected AffineTransform rotateMatrix = new AffineTransform();
	protected AffineTransform scaleMatrix = new AffineTransform();
	protected AffineTransform translateMatrix = new AffineTransform();

	protected int type;
	protected int x;
	protected int y;
	protected int anchorX;
	protected int anchorY;
	protected double rotLimit;
	protected double realRotated;
	protected double fakeRotated;
	protected double realScaled;
	protected Point2D lastPoint = null;
	protected InteractionMode interactionMode = InteractionMode.IDLE;
	protected String image;

	public Sprite()
	{
	}

	public Sprite(Sprite parent)
	{
		if (parent != null)
		{
			parent.addChild(this);
		}
	}

	public void addChild(Sprite s)
	{
		children.add(s);
		s.setParent(this);
	}

	public Sprite getParent()
	{
		return parent;
	}

	private void setParent(Sprite s)
	{
		this.parent = s;
	}

	/**
	 * Handles mouse events
	 */
	protected void handleMouseDownEvent(MouseEvent e)
	{
		lastPoint = e.getPoint();
		if (e.getButton() == MouseEvent.BUTTON1)
		{
			if (this.type == SPRITE_TYPE_TORSO)
			{
				interactionMode = InteractionMode.DRAGGING;
			}
			else
			{
				interactionMode = InteractionMode.ROT_AND_SCALE;
			}
		}
		else if (e.getButton() == MouseEvent.BUTTON3)
		{

			// && (Math.abs(this.clickedX - this.anchorX) < 3))
			if ((this.type == SPRITE_TYPE_UPPER_LEG || this.type == SPRITE_TYPE_LOWER_LEG))
			{
				interactionMode = InteractionMode.SCALING;
			}
		}
	}

	protected void handleMouseDragEvent(MouseEvent e)
	{
		Point2D oldPoint = lastPoint;
		Point2D newPoint = e.getPoint();
		switch (interactionMode)
		{
			case IDLE:
				// no-op (shouldn't get here)
				break;
			case DRAGGING:
				double x_trans = newPoint.getX() - oldPoint.getX();
				double y_trans = newPoint.getY() - oldPoint.getY();
				translateMatrix.translate(x_trans, y_trans);
				break;
			case ROT_AND_SCALE:
				double upperRotLimit = this.rotLimit;
				double lowerRotLimit = -this.rotLimit;

				AffineTransform aTrans = this.getFullTransform();
				Point2D realAnchor = new Point2D.Float(this.anchorX, this.anchorY);
				aTrans.transform(realAnchor, realAnchor);

				double newXDiff = newPoint.getX() - realAnchor.getX();
				double newYDiff = newPoint.getY() - realAnchor.getY();
				double oldXDiff = oldPoint.getX() - realAnchor.getX();
				double oldYDiff = oldPoint.getY() - realAnchor.getY();
				double angleDiff = calcualteAngleDiff(newXDiff, newYDiff, oldXDiff, oldYDiff);

				// Ignore case
				if (this.rotLimit != 360 && (this.realRotated == upperRotLimit && angleDiff > 0)
						|| this.realRotated == lowerRotLimit && angleDiff < 0)
				{
					break;
				}
				else // Rotate case
				{
					double newRadius;
					this.fakeRotated += angleDiff;
					// Rotate within the range
					if (this.rotLimit == 360 || (this.fakeRotated <= upperRotLimit
							&& this.fakeRotated >= lowerRotLimit))
					{
						this.fakeRotated %= 360;
						newRadius = Math.toRadians(angleDiff);
					}
					else
					{
						// Over Upper Limit
						if (this.fakeRotated > upperRotLimit)
						{
							this.fakeRotated = upperRotLimit;
							newRadius = Math.toRadians(upperRotLimit)
									- Math.toRadians(this.realRotated);
						}
						else// Below Lower Limit
						{
							this.fakeRotated = lowerRotLimit;
							newRadius = Math.toRadians(lowerRotLimit)
									- Math.toRadians(this.realRotated);
						}
					}
					rotateMatrix.rotate(newRadius, this.anchorX, this.anchorY);
					this.realRotated = this.fakeRotated;
				}

				// check if need to scale
				if (this.type == Sprite.SPRITE_TYPE_LOWER_LEG
						|| this.type == Sprite.SPRITE_TYPE_UPPER_LEG)
				{
					double oldDis = Math.sqrt(oldXDiff * oldXDiff + oldYDiff * oldYDiff);
					double newDis = Math.sqrt(newXDiff * newXDiff + newYDiff * newYDiff);
					double delta = Math.toRadians(this.realRotated);
					double theta1 = Math.atan2(oldPoint.getX() - this.anchorX,
							this.anchorY - oldPoint.getY());
					double thetaOld = theta1 - delta;
					double theta2 = Math.atan2(newPoint.getX() - this.anchorX,
							this.anchorY - newPoint.getY());
					double thetaNew = theta2 - delta;

					double h1 = Math.cos(thetaOld) * oldDis;
					double h2 = Math.cos(thetaNew) * newDis;

					double newFactorY = h2 / h1;
					legScale(newFactorY);
				}
				break;
		}

		lastPoint = e.getPoint();
	}

	protected void handleMouseUp(MouseEvent e)
	{
		interactionMode = InteractionMode.IDLE;
		this.fakeRotated = this.realRotated;
	}

	/**
	 * Translate Rotate Scale Helper
	 */
	private double calcualteAngleDiff(double newXDiff, double newYDiff, double oldXDiff,
			double oldYDiff)
	{
		double angleNew = Math.toDegrees(Math.atan(newXDiff / newYDiff));
		if ((newXDiff > 0 && newYDiff < 0) || (newXDiff <= 0 && newYDiff < 0))
		{
			angleNew += 180;
		}
		double angleOld = Math.toDegrees(Math.atan(oldXDiff / oldYDiff));
		if ((oldXDiff > 0 && oldYDiff < 0) || (oldXDiff <= 0 && oldYDiff < 0))
		{
			angleOld += 180;
		}
		double angleDiff = angleNew - angleOld;
		angleDiff = 360 - angleDiff;
		angleDiff %= 360;
		if (angleDiff > 180)
		{
			angleDiff -= 360;
		}
		return angleDiff;
	}

	private void legScale(double newFactorY)
	{
		double scaleLowerLimit = PaperDolls.scaleLowerLimit;
		double scaleUpperLimit = PaperDolls.scaleUpperLimit;
		if ((this.realScaled == scaleUpperLimit && newFactorY > 1)
				|| (this.realScaled == scaleLowerLimit && newFactorY < 1))
		{
			return;
		}

		if (this.realScaled * newFactorY >= scaleLowerLimit
				&& this.realScaled * newFactorY <= scaleUpperLimit)
		{
			this.realScaled *= newFactorY;
		}
		else
		{
			// Over Upper Limit
			if (newFactorY > 1)
			{
				newFactorY = scaleUpperLimit / this.realScaled;
				this.realScaled = scaleUpperLimit;
			}
			else // Below Lower Limit
			{
				newFactorY = scaleLowerLimit / this.realScaled;
				this.realScaled = scaleLowerLimit;
			}
		}
		scaleMatrix.scale(1, newFactorY);

		keepFootSize(newFactorY);
	}

	private void keepFootSize(double newFactorY)
	{
		Sprite lowerLeg;
		Sprite foot;
		// UpperLeg case
		if (this.type == Sprite.SPRITE_TYPE_UPPER_LEG)
		{
			lowerLeg = this.children.get(0);
			lowerLeg.realScaled = this.realScaled;
			foot = lowerLeg.children.get(0);
		}
		else// LowerLeg case
		{
			foot = this.children.get(0);
		}

		foot.realScaled = newFactorY;
		foot.scaleMatrix.scale(1, 1 / newFactorY);
	}

	/**
	 * Locates the sprite that was hit by the given event. You *may* need to
	 * modify this method, depending on how you modify other parts of the class.
	 * 
	 * @return The sprite that was hit, or null if no sprite was hit
	 */
	public Sprite getSpriteHit(MouseEvent e)
	{
		for (Sprite sprite : children)
		{
			Sprite s = sprite.getSpriteHit(e);
			if (s != null)
			{
				return s;
			}
		}
		if (this.pointInside(e.getPoint()))
		{
			return this;
		}
		return null;
	}

	/**
	 * Matrix Logic here
	 */
	public AffineTransform getFullTransform()
	{
		AffineTransform returnTransform = new AffineTransform();
		Sprite curSprite = this;
		while (curSprite != null)
		{
			returnTransform.preConcatenate(curSprite.getLocalTransform());
			curSprite = curSprite.getParent();
		}
		return returnTransform;
	}

	public AffineTransform getLocalTransform()
	{
		AffineTransform TRSMaxtrix = new AffineTransform();
		TRSMaxtrix.concatenate(translateMatrix);
		TRSMaxtrix.concatenate(rotateMatrix);
		TRSMaxtrix.concatenate(scaleMatrix);
		return TRSMaxtrix;
	}

	public void draw(Graphics2D g)
	{
		AffineTransform oldTransform = g.getTransform();

		// Set to our transform
		g.setTransform(this.getFullTransform());

		// Draw the sprite (delegated to sub-classes)
		this.drawSprite(g);

		// Restore original transform
		g.setTransform(oldTransform);

		// Draw children
		for (Sprite sprite : children)
		{
			sprite.draw(g);
		}
	}

	public abstract boolean pointInside(Point2D p);

	protected abstract void drawSprite(Graphics2D g);
}