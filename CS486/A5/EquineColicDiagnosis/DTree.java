package EquineColicDiagnosis;

import EquineColicDiagnosis.HorseInfo.Factor;

public class DTree {
	private Factor factor;
	private double threshold;
	private boolean healthy;
	private boolean modified;
	public DTree left;
	public DTree right;

	public void setFactor(int enume) {
		this.factor = Factor.values()[enume];
	}

	public Factor getFactor() {
		return this.factor;
	}

	public void setThreshold(double threshold) {
		this.threshold = threshold;
	}

	public double getThreshold() {
		return this.threshold;
	}

	public void setHealthy(boolean healthy) {
		this.healthy = healthy;
		this.modified = true;
	}

	public boolean isHealthy() {
		return this.healthy;
	}

	public boolean isModified() {
		return this.modified;
	}
}
