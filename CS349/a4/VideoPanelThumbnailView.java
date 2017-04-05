import java.awt.Desktop;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URI;
import java.net.URISyntaxException;
import java.net.URL;

import javax.imageio.ImageIO;
import javax.swing.JPanel;

public class VideoPanelThumbnailView extends JPanel implements Observer
{
	static int width = 120;
	static int height = 90;

	private String imageURL;
	private String navigateURL;

	private Image thumbnail;

	VideoPanelThumbnailView(String imageURL, String navigateURL)
	{
		this.setPreferredSize(new Dimension(width, height));
		this.setURL(imageURL, navigateURL);
		initMouseListener();
	}

	private void initMouseListener()
	{
		this.addMouseListener(new MouseAdapter() {
			public void mouseClicked(MouseEvent e)
			{
				try
				{
					Desktop desktop = Desktop.isDesktopSupported() ? Desktop.getDesktop() : null;
					if (desktop != null && desktop.isSupported(Desktop.Action.BROWSE))
					{
						desktop.browse(new URL(navigateURL).toURI());
					}
				}
				catch (Exception e1)
				{
					System.err.println("Could not open webpage.");
				}
			}
		});
	}

	public void setURL(String imageURL, String navigateURL)
	{
		this.imageURL = imageURL;
		this.navigateURL = navigateURL;
		try
		{
			thumbnail = ImageIO.read(new URL(this.imageURL));
		}
		catch (Exception e)
		{
		}
		repaint();
	}

	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		g.drawImage(thumbnail, 0, 0, width, height, this);
	}

	@Override
	public void update(Object observable)
	{
		repaint();
	}

}
