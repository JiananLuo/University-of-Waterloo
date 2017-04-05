import java.awt.Color;
import java.awt.event.KeyEvent;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;
import javax.swing.KeyStroke;

public class MenuBar extends JMenuBar
{
	Model model;

	public MenuBar(Model model)
	{
		this.model = model;
		this.setBorder(BorderFactory.createLineBorder(Color.GRAY));
		addMenu();
	}

	private void addMenu()
	{
		JMenu Menu_FILE = new JMenu("File");
		this.add(Menu_FILE);

		JMenuItem MenuItem_RESET = new JMenuItem("Reset");
		JMenuItem MenuItem_SAVE = new JMenuItem("Save");
		JMenuItem MenuItem_LOAD = new JMenuItem("Load");
		JMenuItem MenuItem_QUIT = new JMenuItem("Quit");
		MenuItem_RESET .setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_R, KeyEvent.CTRL_DOWN_MASK));
		MenuItem_RESET.addActionListener(e ->
		{
			model.resetAllParts();
		});
		MenuItem_SAVE.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S, KeyEvent.CTRL_DOWN_MASK));
		MenuItem_SAVE.addActionListener(e ->
		{
			model.showSaveDialog();
		});
		MenuItem_LOAD.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_L, KeyEvent.CTRL_DOWN_MASK));
		MenuItem_LOAD.addActionListener(e ->
		{
			if (!model.checkSavedBeforeClear())
			{
				model.clearSprites();
				model.showLoadDialog();
			}
		});
		MenuItem_QUIT.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_Q, KeyEvent.CTRL_DOWN_MASK));
		MenuItem_QUIT.addActionListener(e ->
		{
			System.exit(0);
		});
        Menu_FILE.add(MenuItem_RESET);
        Menu_FILE.addSeparator();
        Menu_FILE.add(MenuItem_SAVE);
        Menu_FILE.add(MenuItem_LOAD);
        Menu_FILE.addSeparator();
        Menu_FILE.add(MenuItem_QUIT);
	}
}
