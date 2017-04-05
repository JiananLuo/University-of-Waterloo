import javax.swing.BorderFactory;
import javax.swing.JPanel;

import java.awt.*;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import java.io.IOException;
import java.util.Vector;

public class DollPanel extends JPanel implements Observer
{
	private Sprite interactiveSprite = null;
	private Model model;

	public DollPanel(Model model)
	{
		super();
		this.model = model;
		this.setLayout(new BorderLayout());
		this.setBorder(BorderFactory.createLineBorder(Color.GRAY));

		this.addMouseListener(new MouseAdapter() {
			public void mousePressed(java.awt.event.MouseEvent e)
			{
				handleMousePress(e);
			}

			public void mouseReleased(MouseEvent e)
			{
				handleMouseReleased(e);
			}
		});
		this.addMouseMotionListener(new MouseMotionAdapter() {
			public void mouseDragged(MouseEvent e)
			{
				handleMouseDragged(e);
			}
		});
	}

	/**
	 * Handles mouse events
	 */
	private void handleMousePress(java.awt.event.MouseEvent e)
	{
		model.spriteModified();
		
		Vector<Sprite> sprites = model.getSprites();
		for (Sprite sprite : sprites)
		{
			interactiveSprite = sprite.getSpriteHit(e);
			if (interactiveSprite != null)
			{
				interactiveSprite.handleMouseDownEvent(e);
				break;
			}
		}
	}

	private void handleMouseReleased(MouseEvent e)
	{
		if (interactiveSprite != null)
		{
			interactiveSprite.handleMouseUp(e);
			repaint();
		}
		interactiveSprite = null;
	}

	private void handleMouseDragged(MouseEvent e)
	{
		if (interactiveSprite != null)
		{
			interactiveSprite.handleMouseDragEvent(e);
			repaint();
		}
	}

	/**
	 * Initiate sprite
	 */
	public static Sprite makeSprite() throws IOException
	{
		// torso
		 ImageSprite torso = new ImageSprite(Sprite.SPRITE_TYPE_TORSO, 200, 100, 0.0 ,"torso.png");

		// head
		ImageSprite head = new ImageSprite(Sprite.SPRITE_TYPE_HEAD, 17, -60, 50.0, "head.png");
		head.setAnchorPoint(35, 70);

		// upper arm
		ImageSprite leftUpperArm = new ImageSprite(Sprite.SPRITE_TYPE_UPPER_ARM, -65, 13, 360.0, "leftUpperArm.png");
		ImageSprite rightUpperArm = new ImageSprite(Sprite.SPRITE_TYPE_UPPER_ARM, 80, 13, 360.0, "rightUpperArm.png");
		leftUpperArm.setAnchorPoint(70, 40);
		rightUpperArm.setAnchorPoint(10, 40);

		// lower arm
		ImageSprite leftLowerArm = new ImageSprite(Sprite.SPRITE_TYPE_LOWER_ARM, -15, 110, 135.0, "leftLowerArm.png");
		ImageSprite rightLowerArm = new ImageSprite(Sprite.SPRITE_TYPE_LOWER_ARM, 40, 110, 135.0, "rightLowerArm.png");
		leftLowerArm.setAnchorPoint(30, 15);
		rightLowerArm.setAnchorPoint(25, 15);

		// hand
		ImageSprite leftHand = new ImageSprite(Sprite.SPRITE_TYPE_HAND, -15, 40, 35.0, "leftHand.png");
		ImageSprite rightHand = new ImageSprite(Sprite.SPRITE_TYPE_HAND, 20, 40, 35.0, "rightHand.png");
		leftHand.setAnchorPoint(30, 5);
		rightHand.setAnchorPoint(15, 5);

		// upper leg
		ImageSprite leftUpperLeg = new ImageSprite(Sprite.SPRITE_TYPE_UPPER_LEG, -17, 185, 90.0, "leftUpperLeg.png");
		ImageSprite rightUpperLeg = new ImageSprite(Sprite.SPRITE_TYPE_UPPER_LEG, 56, 185, 90.0, "rightUpperLeg.png");
		leftUpperLeg.setAnchorPoint(45, 20);
		rightUpperLeg.setAnchorPoint(20, 20);

		// lower leg
		ImageSprite leftLowerLeg = new ImageSprite(Sprite.SPRITE_TYPE_LOWER_LEG, -11, 80, 90.0, "leftLowerLeg.png");
		ImageSprite rightLowerLeg = new ImageSprite(Sprite.SPRITE_TYPE_LOWER_LEG, 0, 80, 90.0, "rightLowerLeg.png");
		leftLowerLeg.setAnchorPoint(40, 15);
		rightLowerLeg.setAnchorPoint(40, 15);

		// foot
		ImageSprite leftFoot = new ImageSprite(Sprite.SPRITE_TYPE_FOOT, 0, 98, 35.0, "leftFoot.png");
		ImageSprite rightFoot = new ImageSprite(Sprite.SPRITE_TYPE_FOOT, 16, 94, 35.0, "rightFoot.png");
		leftFoot.setAnchorPoint(32, 6);
		rightFoot.setAnchorPoint(32, 6);

		// build scene graph
		torso.addChild(head);

		torso.addChild(leftUpperLeg);
		leftUpperLeg.addChild(leftLowerLeg);
		leftLowerLeg.addChild(leftFoot);
		torso.addChild(rightUpperLeg);
		rightUpperLeg.addChild(rightLowerLeg);
		rightLowerLeg.addChild(rightFoot);

		torso.addChild(leftUpperArm);
		leftUpperArm.addChild(leftLowerArm);
		leftLowerArm.addChild(leftHand);
		torso.addChild(rightUpperArm);
		rightUpperArm.addChild(rightLowerArm);
		rightLowerArm.addChild(rightHand);
		return torso;
	}

	public void paint(Graphics g)
	{
		g.setColor(Color.WHITE);
		g.fillRect(0, 0, this.getWidth(), this.getHeight());
		g.setColor(Color.BLACK);

		Vector<Sprite> sprites = model.getSprites();
		for (Sprite sprite : sprites)
		{
			sprite.draw((Graphics2D) g);
		}
	}

	@Override
	public void update(Object observable)
	{
		repaint();
	}
}
