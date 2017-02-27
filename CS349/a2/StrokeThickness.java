import java.awt.BorderLayout;
import java.awt.Dimension;

import javax.swing.JPanel;
import javax.swing.JSlider;

public class StrokeThickness extends JPanel
{
	private Model model;

	public StrokeThickness(Model model)
	{
		this.model = model;
		setLayout(new BorderLayout());
		setPreferredSize(new Dimension(this.getWidth(), this.getHeight()));
		setMinimumSize(new Dimension(this.getWidth(), this.getHeight()));
		setMaximumSize(new Dimension(this.getWidth(), this.getHeight()));

		addThicknessSlider(model);
	}

	private void addThicknessSlider(Model model)
	{
		JSlider thicknessSlider = new JSlider(JSlider.HORIZONTAL, 0, 10, model.getThickness());
		thicknessSlider.setMinorTickSpacing(2);
		thicknessSlider.setMajorTickSpacing(5);
		thicknessSlider.setPaintTicks(true);
		thicknessSlider.setPaintLabels(true);
		thicknessSlider.addChangeListener(e ->
		{
			int thickness = thicknessSlider.getValue();
			this.model.setThickness(thickness);
		});
		this.add(thicknessSlider);
	}

}
