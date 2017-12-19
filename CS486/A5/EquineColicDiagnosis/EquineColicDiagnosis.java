package EquineColicDiagnosis;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.AbstractMap.SimpleEntry;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Scanner;

public class EquineColicDiagnosis {

	public static void main(String[] args) {
		ArrayList<HorseInfo> horseInfoList = new ArrayList<HorseInfo>();
		readInput(horseInfoList);
		DTree decisionTree = new DTree();
		DTL(horseInfoList, decisionTree, MODE(horseInfoList));
		printDecisionTree(decisionTree);
	}

	private static void readInput(ArrayList<HorseInfo> horseInfoList) {
		String line;
		String[] info;
		try {
			@SuppressWarnings("resource")
			Scanner scanner = new Scanner(new File("/Users/JiananLuo/Desktop/A5/horseTrain.txt"));
			while (scanner.hasNextLine()) {
				line = scanner.nextLine();
				info = line.split(",");
				horseInfoList.add(new HorseInfo(info));
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
			System.err.println("Please make sure file exist.");
			System.exit(1);
		}
	}

	private static void DTL(ArrayList<HorseInfo> infoList, DTree decisionTree, boolean mode) {
		if (infoList.size() == 0) {
			decisionTree.setHealthy(mode);
			return;
		}

		if (isSameClassification(infoList)) {
			decisionTree.setHealthy(infoList.get(0).isHealthy());
			return;
		}

		if (infoList.get(0).getFactors().size() == 0) {
			decisionTree.setHealthy(mode);
			return;
		}

		SimpleEntry<Integer, Double> attribute = chooseAttribute(new ArrayList<HorseInfo>(infoList));
		decisionTree.setFactor(attribute.getKey());
		decisionTree.setThreshold(attribute.getValue());

		decisionTree.left = new DTree();
		decisionTree.right = new DTree();

		ArrayList<HorseInfo> leftchild = new ArrayList<HorseInfo>();
		ArrayList<HorseInfo> rightchild = new ArrayList<HorseInfo>();

		for (int i = 0; i < infoList.size(); i++) {
			if (infoList.get(i).getFactors().get(decisionTree.getFactor().ordinal()) > decisionTree.getThreshold()) {
				rightchild.add(infoList.get(i));
			} else {
				leftchild.add(infoList.get(i));
			}
		}
		DTL(leftchild, decisionTree.left, MODE(infoList));
		DTL(rightchild, decisionTree.right, MODE(infoList));
	}

	private static boolean isSameClassification(ArrayList<HorseInfo> infoList) {
		boolean temp = infoList.get(0).isHealthy();
		for (HorseInfo horseInfo : infoList) {
			if (temp != horseInfo.isHealthy()) {
				return false;
			}
		}
		return true;
	}

	private static SimpleEntry<Integer, Double> chooseAttribute(ArrayList<HorseInfo> horseInfoList) {
		int currentAttributeIndex = 0;
		double currentThreshold = Double.MAX_VALUE, currentRemainder = Double.MAX_VALUE;

		for (int i = 0; i < horseInfoList.get(0).getFactors().size(); i++) {
			final int tmpIndex = i;
			Collections.sort(horseInfoList, new Comparator<HorseInfo>() {
				public int compare(HorseInfo o1, HorseInfo o2) {
					return Double.compare(o1.getFactors().get(tmpIndex), o2.getFactors().get(tmpIndex));
				}
			});

			int sizeInfoList = horseInfoList.size();
			for (int j = 1; j < sizeInfoList; j++) {
				double lastFactorValue = horseInfoList.get(j - 1).getFactors().get(i);
				double thisFactorValue = horseInfoList.get(j).getFactors().get(i);
				if (lastFactorValue == thisFactorValue) {
					continue;
				}
				int k = 0;
				int h1 = 0, h2 = 0;
				for (; k < sizeInfoList; k++) {
					if (horseInfoList.get(k).isHealthy()) {
						if (k < j)
							h1++;
						else
							h2++;
					}
				}
				int c1 = j - h1, c2 = sizeInfoList - j - h2;
				double e1 = ENTROPY(h1, c1), e2 = ENTROPY(h2, c2);
				double tempRemainder = ((h1 + c1) * e1 + (h2 + c2) * e2) / sizeInfoList;
				if (currentRemainder > tempRemainder) {
					currentAttributeIndex = i;
					currentThreshold = (lastFactorValue + thisFactorValue) / 2;
					currentRemainder = tempRemainder;
				}
			}
		}
		return new SimpleEntry<Integer, Double>(currentAttributeIndex, currentThreshold);
	}

	private static boolean MODE(ArrayList<HorseInfo> infoList) {
		int count = 0;
		for (HorseInfo info : infoList) {
			if (info.isHealthy()) {
				count++;
			}
		}
		return (count > infoList.size() / 2) ? true : false;
	}

	private static double ENTROPY(double a, double b) {
		double log1 = (a == 0) ? 0 : logarithmBaseTwo(a / (a + b));
		double log2 = (b == 0) ? 0 : logarithmBaseTwo(b / (a + b));
		return -1 * (a * log1 + b * log2) / (a + b);
	}

	private static double logarithmBaseTwo(double a) {
		return Math.log(a) / Math.log(2);
	}

	private static void printDecisionTree(DTree dt) {
		if (dt == null || dt.isModified()) {
			return;
		}
		System.out.println("Node: " + dt.getFactor() + "\t\tThreshold: " + dt.getThreshold());
		System.out.println(dt.left.isModified() ? (dt.left.isHealthy() ? "Healthy" : "Colin") : dt.left.getFactor());
		System.out.println(dt.right.isModified() ? (dt.right.isHealthy() ? "Healthy" : "Colin") : dt.right.getFactor());
		System.out.println();
		printDecisionTree(dt.left);
		printDecisionTree(dt.right);
	}
}
