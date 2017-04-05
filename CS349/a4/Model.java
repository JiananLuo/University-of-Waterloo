import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JFileChooser;
import javax.swing.filechooser.FileNameExtensionFilter;

import com.google.api.services.youtube.model.SearchResult;

public class Model
{
	public static String Extension_BINARY = ".bin";

	private boolean saved;
	private boolean resultChanged;

	private String searchField;
	private ArrayList<Video> videos;
	private ArrayList<Observer> observers;
	private int rating;
	private int panelType;

	public Model()
	{
		saved = true;
		this.resultChanged = false;
		this.observers = new ArrayList<Observer>();
		this.searchField = "";
		this.videos = new ArrayList<Video>();
		this.rating = 0;
		this.panelType = YouTubePanelResultPanel.LIST_VIEW;
	}

	/**
	 * observer
	 */
	public void addObserver(Observer observer)
	{
		this.observers.add(observer);
	}

	public void notifyObservers()
	{
		for (Observer observer : observers)
		{
			observer.update(this);
		}
	}

	/**
	 * saved
	 */
	public boolean isSaved()
	{
		return this.saved;
	}

	public void setChanged(boolean resultChanged)
	{
		this.resultChanged = resultChanged;
	}

	public boolean isChanged()
	{
		return this.resultChanged;
	}

	public void spriteModified()
	{
		this.saved = false;
	}

	public void setSearchField(String field)
	{
		this.searchField = field;
	}

	/**
	 * Video
	 */
	public void setVideos(ArrayList<Video> videos)
	{
		this.resultChanged = true;
		this.videos = videos;
		for (int i = 0; i < videos.size(); i++)
		{
			YouTubePanelResultPanel.listViewPanels.get(i).setInfo(videos.get(i));
			YouTubePanelResultPanel.gridViewPanels.get(i).setInfo(videos.get(i));
		}
	}

	public void setVideos(List<SearchResult> results)
	{
		videos.clear();
		this.resultChanged = true;
		for (int i = 0; i < results.size(); i++)
		{
			SearchResult result = results.get(i);
			Video video = new Video(result, i);
			videos.add(video);
		}
		this.notifyObservers();
	}

	public ArrayList<Video> getVideos()
	{
		return videos;
	}

	public void clearVideos()
	{
		this.videos.clear();
		notifyObservers();
	}

	public void setRating(int rating)
	{
		this.rating = rating;
		this.notifyObservers();
	}

	public int getRating()
	{
		return this.rating;
	}

	public int getPanelType()
	{
		return this.panelType;
	}

	public void setView(int panelType)
	{
		this.panelType = panelType;
		this.notifyObservers();
	}

	/**
	 * save & save
	 */
	public void saveBinaryFile(File file)
	{
		try
		{
			file.createNewFile();
			FileOutputStream fileOut = new FileOutputStream(file, false);
			ObjectOutputStream out = new ObjectOutputStream(fileOut);
			out.writeObject(this.searchField);
			out.writeObject(this.videos);
			out.close();
			fileOut.close();
			this.saved = true;
			notifyObservers();
		}
		catch (Exception e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void loadBinaryFile(File file)
	{
		try
		{
			FileInputStream saveFile = new FileInputStream(file);
			ObjectInputStream save = new ObjectInputStream(saveFile);
			String searchField = (String) save.readObject();
			this.setVideos(((ArrayList<Video>) save.readObject()));
			this.searchField = searchField;
			YouTubePanelControlPanel.searchField.setText(searchField);
			save.close();
			this.saved = true;
			notifyObservers();
		}
		catch (Exception e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void showSaveDialog()
	{
		JFileChooser fileChooser = new JFileChooser();
		fileChooser.setDialogTitle("Save As");
		fileChooser.addChoosableFileFilter(new FileNameExtensionFilter("Binary Files", "bin"));
		int dialogResult = fileChooser.showSaveDialog(null);
		if (dialogResult == JFileChooser.APPROVE_OPTION)
		{
			File file = fileChooser.getSelectedFile();
			String filename = fileChooser.getSelectedFile().toString();
			if (!filename.endsWith(Extension_BINARY))
			{
				filename += Extension_BINARY;
				file = new File(filename);
			}
			this.saveBinaryFile(file);
		}
	}

	public void showLoadDialog()
	{
		JFileChooser fileChooser = new JFileChooser();
		fileChooser.setDialogTitle("Load");
		fileChooser.addChoosableFileFilter(new FileNameExtensionFilter("Binary Files", "bin"));
		int dialogResult = fileChooser.showOpenDialog(null);
		if (dialogResult == JFileChooser.APPROVE_OPTION)
		{
			File file = fileChooser.getSelectedFile();
			this.loadBinaryFile(file);
		}
	}
}
