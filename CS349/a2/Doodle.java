public class Doodle
{
	public static void main(String[] args)
	{
		Model model = new Model();

		MenuBar menuBar = new MenuBar(model);
		ColorPalette colorPalette = new ColorPalette(model);
		StrokeThickness strokeThickness = new StrokeThickness(model);
		DotModel dotModel = new DotModel(model);
		FunctionPanel functionPanel = new FunctionPanel(colorPalette, strokeThickness, dotModel);
		DrawPanel drawPanel = new DrawPanel(model);
		FramePanel framePanel = new FramePanel(model);
		DoodlePanel doodlePanel = new DoodlePanel(model, menuBar, functionPanel, framePanel,
				drawPanel);

		model.addObserver(menuBar);
		model.addObserver(colorPalette);
		model.addObserver(dotModel);
		model.addObserver(drawPanel);
		model.addObserver(framePanel);

		DoodleView view = new DoodleView(doodlePanel);
		model.notifyObservers();
	}
}
