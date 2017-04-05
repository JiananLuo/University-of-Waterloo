import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;
import java.util.Vector;

import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import javax.swing.filechooser.FileNameExtensionFilter;

public class Model
{
	public static String Extension_BINARY = ".bin";

	private Vector<Sprite> sprites;
	private ArrayList<Observer> observers;
	private boolean saved;

	public Model()
	{
		this.sprites = new Vector<Sprite>();
		this.observers = new ArrayList<Observer>();
		saved = true;
	}

	/**
	 * observer
	 */
	public void addObserver(Observer observer)
	{
		this.observers.add(observer);
	}

	public void removeObserver(Observer observer)
	{
		this.observers.remove(observer);
	}

	public void notifyObservers()
	{
		for (Observer observer : this.observers)
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

	public void spriteModified()
	{
		this.saved = false;
	}

	/**
	 * Sprite
	 */
	public Vector<Sprite> getSprites()
	{
		return sprites;
	}

	public void clearSprites()
	{
		this.sprites.clear();
		notifyObservers();
	}

	public void resetAllParts()
	{
		this.sprites.clear();
		try
		{
			sprites.add(DollPanel.makeSprite());
		}
		catch (IOException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		notifyObservers();
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
			out.writeObject(this.sprites);
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
			this.sprites = ((Vector<Sprite>) save.readObject());
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

	public boolean checkSavedBeforeClear()
	{
		boolean cancelled = false;
		if (!this.isSaved())
		{
			int dialogResult = JOptionPane.showConfirmDialog(null,
					"Your changes will be lost if you close this item without saving. Save it now?",
					"Warning", JOptionPane.YES_NO_CANCEL_OPTION);
			if (dialogResult == JOptionPane.YES_OPTION)
			{
				this.showSaveDialog();
				this.clearSprites();
			}
			else if (dialogResult == JOptionPane.NO_OPTION)
			{
				this.clearSprites();
			}
			else
			{
				cancelled = true;
			}
		}
		else
		{
			this.clearSprites();
		}
		return cancelled;
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
