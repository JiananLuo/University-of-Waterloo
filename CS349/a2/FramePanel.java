import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JSlider;

public class FramePanel extends JPanel implements Observer
{
	private Model model;
	private JButton playForwardButton;
	private JButton playBackwardButton;
	private JSlider frameSlider;
	private JButton startButton;
	private JButton endButton;
	private boolean isManuallyListenerFlag = true;

	public FramePanel(Model model)
	{
		this.model = model;
		this.setLayout(new BorderLayout());
		this.setBorder(BorderFactory.createLineBorder(Color.GRAY));

		framePanelInit();
	}

	private void framePanelInit()
	{
		frameSliderInit();
		animationButtonInit();
		frameButtonInit();
	}

	private void frameButtonInit()
	{
		JPanel setFramePanel = new JPanel();
		startButton = new JButton("Start");
		startButton.addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e)
			{
				frameSlider.setValue(0);
				model.setCurrentPoint(0);
			}
		});
		endButton = new JButton("End");
		endButton.addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e)
			{
				frameSlider.setValue(model.getTotalPoint());
				model.setCurrentPoint(model.getTotalPoint());
			}
		});
		setFramePanel.add(startButton);
		setFramePanel.add(endButton);
		this.add(setFramePanel, BorderLayout.EAST);
	}

	private void animationButtonInit()
	{
		playForwardButton = new JButton(">>");
		playForwardButton.addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e)
			{
				model.playAnimationForward();
			}
		});
		playBackwardButton = new JButton("<<");
		playBackwardButton.addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e)
			{
				model.playAnimationBackward();
			}
		});
		JPanel playFramePanel = new JPanel();
		playFramePanel.add(playBackwardButton);
		playFramePanel.add(playForwardButton);
		this.add(playFramePanel, BorderLayout.WEST);
	}

	private void frameSliderInit()
	{
		this.frameSlider = new JSlider(JSlider.HORIZONTAL, 0, model.getTotalFrame(),
				model.getCurrentFrame());
		this.frameSlider.setMinorTickSpacing(1);
		this.frameSlider.setMajorTickSpacing(5);
		this.frameSlider.setPaintTicks(true);
		this.frameSlider.addChangeListener(e ->
		{
			int currentPoint = this.frameSlider.getValue();
			if (isManuallyListenerFlag == true)
			{
				model.setCurrentPoint(currentPoint);
			}
		});
		this.add(frameSlider, BorderLayout.CENTER);
	}

	@Override
	public void update(Object observable)
	{
		isManuallyListenerFlag = false;
		this.frameSlider.setMaximum(model.getTotalPoint());
		this.frameSlider.setValue(model.getCurrentPoint());
		isManuallyListenerFlag = true;

		if (model.getCurrentPoint() == 0)
		{
			playForwardButton.setEnabled(true);
			playBackwardButton.setEnabled(false);
			startButton.setEnabled(false);
			endButton.setEnabled(true);
		}
		else if (model.getCurrentPoint() == model.getTotalPoint())
		{
			playForwardButton.setEnabled(false);
			playBackwardButton.setEnabled(true);
			startButton.setEnabled(true);
			endButton.setEnabled(false);
		}
		else
		{
			playForwardButton.setEnabled(true);
			playBackwardButton.setEnabled(true);
			startButton.setEnabled(true);
			endButton.setEnabled(true);

		}
	}
}
