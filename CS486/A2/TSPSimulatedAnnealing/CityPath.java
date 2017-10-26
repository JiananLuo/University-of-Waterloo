package TSPSimulatedAnnealing;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.Random;

public class CityPath {
	private Random rand;
	private int citySize;
	private double temperature, coldDownValue;
	private int swapNodeAIndex, swapNodeBIndex;
	private List<City> optimalCities, neighborCities;
	private double utility;

	/**
	 * constructor for CityPath
	 * @param cities the start state of cityPath
	 * @param temperature the T
	 * @param coldDownValue the deserase value for T
	 */
	public CityPath(ArrayList<City> cities, double temperature, double coldDownValue) {
		this.rand = new Random();

		this.optimalCities = cities;
		this.neighborCities = new ArrayList<City>(cities);
		this.citySize = this.optimalCities.size();
		this.temperature = temperature;
		this.coldDownValue = coldDownValue;
		this.swapNodeAIndex = 0;
		this.swapNodeBIndex = 0;
		this.utility = Double.MAX_VALUE;
	}

	/**
	 * start to annealing the optimal solution
	 */
	public void startAnnealing() {
		while (this.temperature > 0) {
			this.generateRandomNeighbor();
			this.checkIsBetterSolution();
			this.temperature -= this.coldDownValue;
		}
		this.printResult();
	}

	/**
	 * generate a random neighbor for the current path, mutate it by swap 2 random city
	 */
	private void generateRandomNeighbor() {
		swapCity(this.neighborCities);
		swapNodeAIndex = this.rand.nextInt(citySize - 2) + 1;
		do {
			swapNodeBIndex = this.rand.nextInt(citySize - 2) + 1;
		} while (swapNodeAIndex == swapNodeBIndex);
		swapCity(this.neighborCities);
	}

	/**
	 * check if the mutated path is a better solution
	 */
	private void checkIsBetterSolution() {
		// recalculate the path utility
		double currentUtility = 0;
		String lastCity = neighborCities.get(0).getCityName();
		for (int i = 1; i < neighborCities.size(); i++) {
			currentUtility += neighborCities.get(i).getDistanceTo(lastCity);
			lastCity = neighborCities.get(i).getCityName();
		}
		double deltaV = this.utility - currentUtility;
		// if better, go better solution
		if (deltaV > 0) {
			updateOptimalPath(currentUtility);
		}
		// if not better, take probability
		else {
			double exp = deltaV / this.temperature;
			double probability = Math.exp(exp);
			if (probability > this.rand.nextDouble()) {
				updateOptimalPath(currentUtility);
			}
		}
	}

	/**
	 * update the optimal path && set the optimal utility
	 * @param currentUtility the optimal utility
	 */
	private void updateOptimalPath(double currentUtility) {
		this.utility = currentUtility;
		swapCity(this.optimalCities);
		this.swapNodeAIndex = 0;
		this.swapNodeBIndex = 0;
	}

	/**
	 * swap 2 city in a list by the indexes
	 * @param cities
	 */
	private void swapCity(List<City> cities) {
		Collections.swap(cities, swapNodeAIndex, swapNodeBIndex);
	}

	/**
	 * print the result
	 */
	private void printResult() {
		Function<City, String> getCityName = City::getCityName;
		String cityNames = this.optimalCities.stream().map(getCityName).collect(Collectors.joining(" "));
		System.out.println(cityNames);
		System.out.println(this.utility);
	}
}
