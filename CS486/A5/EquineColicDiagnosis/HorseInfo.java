package EquineColicDiagnosis;

import java.util.ArrayList;

public class HorseInfo {

	public static enum Factor {
		K,
		NA,
		CL,
		HCO3,
		Endotoxin,
		Aniongap,
		PLA2,
		SDH,
		GLDH,
		TPP,
		Breathrate,
		PCV,
		Pulserate,
		Fibrinogen,
		Dimer,
		FibperDim
	}

	private boolean isHealthy;
	private ArrayList<Double> factors;

	public HorseInfo(String[] info) {
		factors = new ArrayList<Double>();
		for (int i = 0; i < info.length - 1; i++) {
			this.factors.add(Double.valueOf(info[i]));
		}
		this.isHealthy = (info[16].equals("healthy.")) ? true : false;
	}

	public boolean isHealthy() {
		return this.isHealthy;
	}

	public ArrayList<Double> getFactors() {
		return this.factors;
	}
}
