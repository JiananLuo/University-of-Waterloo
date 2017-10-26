package TSPSimulatedAnnealing;

import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
	// city list
	static ArrayList<City> cities = new ArrayList<City>();

	/**
	 * main function
	 * @param argv[0] the input file path, ex: ~/Desktop/randTSP/problem36
	 * @param argv[1] the temperature value, ex: 400
	 * @param argv[2] the cold-down value, ex: 0.000005
	 */
	public static void main(String argv[]) {
		generateCitiesList(argv[0]);
		CityPath cityPath = new CityPath(cities, Double.parseDouble(argv[1]), Double.parseDouble(argv[2]));
		cityPath.startAnnealing();
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
			cities.add(new City(cities.get(0).getCityName(), cities.get(0).getCityX(), cities.get(0).getCityY()));
			scanner.close();

			// generate city distance to other cities
			for (City cityA : cities) {
				for (City cityB : cities) {
					cityA.addDistanceToPair(cityB.getCityName(), calcCityDist(cityA, cityB));
				}
			}

		} catch (Exception e) {
			System.out.println("Some thing goes wrong with the input file.");
			System.exit(1);
		}
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
