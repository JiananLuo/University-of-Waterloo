import java.awt.Color;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.*;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import javax.swing.filechooser.FileNameExtensionFilter;

public class Model
{
	public static String Extension_BINARY = ".bin";

	private ArrayList<Observer> observers;
	private ArrayList<Stroke> strokes;
	private Color color;
	private int thickness;
	private int currentFrame;
	private int totalFrame;
	private int currentPoint;
	private boolean playMode;
	private boolean playBackward = false;
	private boolean saved;

	public Model()
	{
		this.observers = new ArrayList<Observer>();
		this.strokes = new ArrayList<Stroke>();
		this.color = Color.BLACK;
		this.thickness = 3;
		this.currentFrame = 0;
		this.totalFrame = 0;
		this.playMode = false;
		this.saved = true;
	}

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

	public List<Stroke> getStrokes()
	{
		return this.strokes;
	}

	public void addStroke(Stroke stroke)
	{
		this.saved = false;
		this.strokes.add(stroke);
		this.totalFrame = this.currentFrame + 1;
		notifyObservers();
		this.currentFrame = this.totalFrame;
		notifyObservers();
	}

	public void setStrokes(ArrayList<Stroke> strokes)
	{
		this.strokes = strokes;
		this.setTotalFrame(this.strokes.size());
		this.setCurrentFrame(this.strokes.size());
	}

	public void removeLastNStrokes(int lastN)
	{
		this.strokes.subList(strokes.size() - lastN, strokes.size()).clear();
		this.totalFrame -= lastN;
		this.currentFrame = this.totalFrame;
		notifyObservers();
	}

	public void removeLastNPoints(int lastN)
	{
		for (int i = this.totalFrame - 1; i >= 0; i--)
		{
			Stroke lastStroke = strokes.get(i);
			int currentStrokePoints = lastStroke.getNumOfPoints();
			if (lastN >= currentStrokePoints)
			{
				lastN -= currentStrokePoints;
				this.strokes.subList(strokes.size() - 1, strokes.size()).clear();
				this.totalFrame -= 1;
				this.currentFrame = this.totalFrame;
			}
			else
			{
				lastStroke.removeLastNPoints(lastN);
				break;
			}
		}
		notifyObservers();
	}

	public void clearAllStrokes()
	{
		this.saved = true;
		removeLastNStrokes(this.totalFrame);
	}

	public void setColor(Color color)
	{
		this.color = color;
		notifyObservers();
	}

	public Color getColor()
	{
		return this.color;
	}

	public void setThickness(int thickness)
	{
		this.thickness = thickness;
		notifyObservers();
	}

	public int getThickness()
	{
		return this.thickness;
	}

	public void setCurrentFrame(int currentFrame)
	{
		this.currentFrame = currentFrame;
		notifyObservers();
	}

	public int getCurrentFrame()
	{
		return this.currentFrame;
	}

	public void setTotalFrame(int totalFrame)
	{
		this.totalFrame = totalFrame;
		notifyObservers();
	}

	public int getTotalFrame()
	{
		return this.totalFrame;
	}

	public void setCurrentPoint(int currentPoint)
	{
		this.currentPoint = currentPoint;
		notifyObservers();
	}

	public int getCurrentPoint()
	{
		return this.currentPoint;
	}

	public int getTotalPoint()
	{
		int totalPoints = 0;
		for (int i = 0; i < strokes.size(); i++)
		{
			totalPoints += strokes.get(i).getNumOfPoints();
		}
		return totalPoints;
	}

	public void playAnimationForward()
	{
		this.playMode = true;
		this.playBackward = false;
		notifyObservers();
	}

	public void playAnimationBackward()
	{
		this.playMode = true;
		this.playBackward = true;
		notifyObservers();
	}

	public boolean isPlayMode()
	{
		return this.playMode;
	}

	public boolean isPlayBackward()
	{
		return this.playBackward;
	}

	public boolean setPlayMode(boolean playMode)
	{
		return this.playMode = playMode;
	}

	public boolean isSaved()
	{
		return this.saved;
	}

	public void saveBinaryFile(File file)
	{
		try
		{
			file.createNewFile();
			FileOutputStream fileOut = new FileOutputStream(file, false);
			ObjectOutputStream out = new ObjectOutputStream(fileOut);
			out.writeObject(this.strokes);
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
			this.setStrokes((ArrayList<Stroke>) save.readObject());
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

	public void checkSavedBeforeClear()
	{
		if (!this.isSaved())
		{
			int dialogResult = JOptionPane.showConfirmDialog(null,
					"Your changes will be lost if you close this item without saving. Save it now?",
					"Warning", JOptionPane.YES_NO_CANCEL_OPTION);
			if (dialogResult == JOptionPane.YES_OPTION)
			{
				this.showSaveDialog();
				this.clearAllStrokes();
			}
			else if (dialogResult == JOptionPane.NO_OPTION)
			{
				this.clearAllStrokes();
			}
			else
			{
				return;
			}
		}
		else
		{
			this.clearAllStrokes();
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
