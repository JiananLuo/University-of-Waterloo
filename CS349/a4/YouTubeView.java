import java.awt.*;
import javax.swing.*;

public class YouTubeView extends JFrame
{
	private Container container;
	private int weight = 800, height = 600;

	public YouTubeView(YouTubePanel youtubePanel)
	{
		this.setTitle("YouTubeGallery");
		this.setSize(weight, height);
		this.setMinimumSize(new Dimension(490, 300));
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		container = getContentPane();
		container.add(youtubePanel);

		setVisible(true);
	}
}