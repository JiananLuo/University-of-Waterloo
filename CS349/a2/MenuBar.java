import java.awt.Color;
import java.awt.Dimension;
import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JPopupMenu;

public class MenuBar extends JPanel implements Observer
{
	Model model;
	JButton Menu_FILE;
	JMenuItem MenuItem_NEW;
	JMenuItem MenuItem_SAVE;
	JMenuItem MenuItem_LOAD;
	JMenuItem MenuItem_QUIT;
	final JPopupMenu POPUP_FILE = new JPopupMenu();

	public MenuBar(Model model)
	{
		this.model = model;
		this.setLayout(null);
		this.setBorder(BorderFactory.createLineBorder(Color.GRAY));
		this.setPreferredSize(new Dimension(796, 24));
		addMenu();
	}

	private void addMenu()
	{
		Menu_FILE = new JButton("File");
		Menu_FILE.addActionListener(e ->
		{
			POPUP_FILE.show(Menu_FILE, 0, Menu_FILE.getY() + Menu_FILE.getHeight());
		});
		Menu_FILE.setBounds(2, 2, 60, 20);
		this.add(Menu_FILE);

		MenuItem_NEW = new JMenuItem("New");
		MenuItem_SAVE = new JMenuItem("Save");
		MenuItem_LOAD = new JMenuItem("Load");
		MenuItem_QUIT = new JMenuItem("Quit");
		MenuItem_NEW.addActionListener(e ->
		{
			model.checkSavedBeforeClear();
		});
		MenuItem_SAVE.addActionListener(e ->
		{
			model.showSaveDialog();
		});
		MenuItem_LOAD.addActionListener(e ->
		{
			if (!model.checkSavedBeforeClear())
			{
				model.clearAllStrokes();
				model.showLoadDialog();
			}
		});
		MenuItem_QUIT.addActionListener(e ->
		{
			if (!model.checkSavedBeforeClear())
			{
				System.exit(0);
			}
		});
		POPUP_FILE.add(MenuItem_NEW);
		POPUP_FILE.add(MenuItem_SAVE);
		POPUP_FILE.add(MenuItem_LOAD);
		POPUP_FILE.add(MenuItem_QUIT);
	}

	@Override
	public void update(Object observable)
	{
		if (model.isSaved())
		{
			MenuItem_SAVE.setEnabled(false);
		}
		else
		{
			MenuItem_SAVE.setEnabled(true);
		}
	}
}
