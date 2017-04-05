import javax.swing.JMenuBar;

public class PaperDolls
{
	static double scaleUpperLimit = 1.5;
	static double scaleLowerLimit = 0.5;

	public static void main(String[] args)
	{
		Model model = new Model();
		model.resetAllParts();

		JMenuBar menuBar = new MenuBar(model);
		DollPanel dollPanel = new DollPanel(model);
		PaperDollView view = new PaperDollView(dollPanel, menuBar);

		model.addObserver(dollPanel);
		model.notifyObservers();
	}
}