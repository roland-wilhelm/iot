package de.thesycon.usbiodemo.usbioapp;
import java.awt.Component;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.util.Vector;

import javax.swing.JPanel;

public abstract class PanelPage extends JPanel {

	public abstract String getPageName();

	public abstract void initGUIelements();

	public Vector getControlComponentsVector() { return null;}

	public GridBagLayout layout = new GridBagLayout();

	public PanelPage() {
		this.setDoubleBuffered(true);
		this.setLayout(layout);
		this.initGUIelements();
	}

	public void updateStateOfControls(boolean isOpen) {
		Vector Components = getControlComponentsVector();
		Component comp;
		if (Components != null) {
			for (int i = 0; i < Components.size() ; i++) {
				comp = (Component)Components.elementAt(i);
				comp.setEnabled(isOpen);
			}
		}
	}

	public static GridBagConstraints makegbc (int x, int y, int width, int height) {
		GridBagConstraints gbc = new GridBagConstraints();
		gbc.gridx = x;
		gbc.gridy = y;
		gbc.gridwidth = width;
		gbc.gridheight = height;
		gbc.insets = new Insets(1, 1, 1, 1);
		return gbc;
	}

	public static GridBagConstraints makegbc (int x, int y, int width, int height,int weightx,int weighty,int fill,int anchor) {
		GridBagConstraints gbc = new GridBagConstraints();
		gbc.gridx = x;
		gbc.gridy = y;
		gbc.gridwidth = width;
		gbc.gridheight = height;
		gbc.insets = new Insets(1, 1, 1, 1);
		gbc.weightx = weightx;
		gbc.weighty = weighty;
		gbc.fill = fill;
		gbc.anchor = anchor;
		return gbc;
	}

}