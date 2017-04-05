import java.awt.Image;
import java.io.IOException;
import java.util.List;

import javax.imageio.ImageIO;
import javax.swing.SwingUtilities;

import com.google.api.services.youtube.model.SearchResult;

public class Main
{
	public static Image rating0;
	public static Image rating1;
	public static ModelYouTube youtubeModel;

	public static void main(String[] args)
	{
		Runnable mainTask = () ->
		{

			try
			{
				rating0 = ImageIO.read(Main.class.getResource("rating0.png"));
				rating1 = ImageIO.read(Main.class.getResource("rating1.png"));
			}
			catch (IOException e)
			{
				// TODO Auto-generated catch block
				e.printStackTrace();
			}

			youtubeModel = new ModelYouTube("AIzaSyAdxzVLyfRH--AazBWDKr7fr5Wf-8gMJ6E");
			;
			Model model = new Model();

			YouTubePanel youtubePanel = new YouTubePanel(model);
			new YouTubeView(youtubePanel);

			model.notifyObservers();
		};

		Thread mainThread = new Thread(() ->
		{
			try
			{
				SwingUtilities.invokeAndWait(mainTask);
			}
			catch (Exception e)
			{
				e.printStackTrace();
			}
		});
		mainThread.start();
	}
}