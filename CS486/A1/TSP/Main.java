package AStarTSP;

import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map.Entry;
import java.util.Scanner;

public class Main {
	// city list
	static List<City> cities = new ArrayList<City>();
	// h for all cities
	static HashMap<String, Double> cityH;
	// the final path for sale man
	static String minPath = null;
	// total distance the sale man needs to travel
	static double miniumValue;
	// program run time
	private static long startTime;

	public static void main(String argv[]) {
		startTime = System.currentTimeMillis();
		generateCitiesList(argv[0]);
		findPath();
		returnToStartCity();
	}

	/**
	 * City initialization
	 * @param argv carry the file name
	 */
	private static void generateCitiesList(String fileName) {
		try {
			// file reader && city initialization
			Scanner scanner = new Scanner(new File(fileName));
			int numOfCity = scanner.nextInt();
			for (int i = 0; i < numOfCity; i++) {
				cities.add(new City(scanner.next(), scanner.nextInt(), scanner.nextInt()));
			}
			scanner.close();

			// generate city distance to other cities
			for (City cityA : cities) {
				for (City cityB : cities) {
					cityA.addDistanceToPair(cityB.getCityName(), calcCityDist(cityA, cityB));
				}
			}

			// h for all cities
			cityH = cities.get(0).getDistanceToOtherCity();
		} catch (Exception e) {
			System.out.println("Some thing goes wrong with the input file.");
			System.exit(1);
		}
	}

	/**
	 * Main loop looking for the minimum distance path
	 */
	private static void findPath() {
		// initialize the path list
		HashMap<String, Double> pathList = new HashMap<String, Double>();
		pathList.put("A", 0.0);
		while (true) {
			// find least value node
			String currMinPath = null;
			double currMinVal = Double.MAX_VALUE;
			for (Entry<String, Double> entry : pathList.entrySet()) {
				if (entry.getValue() < currMinVal) {
					currMinPath = entry.getKey();
					currMinVal = entry.getValue();
				}
			}

			// expand minPath Node or finish
			ArrayList<String> currPath = new ArrayList<String>(Arrays.asList(currMinPath.split("\\s")));
			String lastCity = currPath.get(currPath.size() - 1);
			pathList.put(currMinPath, currMinVal - cityH.get(lastCity));

			// expand minPath Node if not reach to end yet
			if (currPath.size() != cities.size()) {
				double currentShortestPathDistance = pathList.get(currMinPath);
				// pop up original node
				pathList.remove(currMinPath);
				// add all possible new nodes with 1 extra city append in the end
				for (City nextCity : cities) {
					if (!currMinPath.contains(nextCity.getCityName())) {
						pathList.put(currMinPath + " " + nextCity.getCityName(),
								currentShortestPathDistance + nextCity.getDistanceTo(lastCity) + nextCity.getCityH());
					}
				}
			} else {
				// append A the first city in the end
				minPath = currMinPath + " A";
				miniumValue = pathList.get(currMinPath) + cityH.get(lastCity);
				return;
			}
		}
	}

	/**
	 * Print final route and total distance sale man needs to travel.
	 */
	private static void returnToStartCity() {
		long endTime = System.currentTimeMillis();
		long totalTime = endTime - startTime;
		System.out.println("Path: " + minPath);
		System.out.println("Total Distance: " + miniumValue);
		System.out.println("Run time: " + totalTime + "ms");
		System.exit(0);
	}

	/**
	 * Return the distance between the provide 2 cities.
	 * @param cityA the first city
	 * @param cityB the second city
	 * @return
	 */
	private static double calcCityDist(City cityA, City cityB) {
		return Math.sqrt((Math.pow((cityA.getCityX() - cityB.getCityX()), 2)
				+ Math.pow((cityA.getCityY() - cityB.getCityY()), 2)));
	}
}
