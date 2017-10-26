package AStarTSP;

import java.util.HashMap;

public class City {
	private String name;
	private int x;
	private int y;
	private HashMap<String, Double> distanceToOtherCity;

	/**
	 * constructor for City
	 * @param name the given name
	 * @param x the given x coordinate
	 * @param y the given y coordinate
	 */
	public City(String name, int x, int y) {
		this.name = name;
		this.x = x;
		this.y = y;
		distanceToOtherCity = new HashMap<String, Double>();
	}

	/**
	 * get the city name
	 * @return the city name
	 */
	public String getCityName() {
		return this.name;
	}

	/**
	 * get the city x coordinate
	 * @return the city x coordinate
	 */
	public int getCityX() {
		return this.x;
	}

	/**
	 * get the city y coordinate
	 * @return the city y coordinate
	 */
	public int getCityY() {
		return this.y;
	}

	/**
	 * get the city h
	 * @return the city h
	 */
	public double getCityH() {
		return this.distanceToOtherCity.get("A");
	}

	/**
	 * add the city/distance pair to the map
	 * @param city the given city
	 * @param distance the given distance
	 */
	public void addDistanceToPair(String city, double distance) {
		distanceToOtherCity.put(city, distance);
	}

	/**
	 * get the distance to all cities
	 * @return the distance to the given city
	 */
	public HashMap<String, Double> getDistanceToOtherCity() {
		return this.distanceToOtherCity;
	}

	/**
	 * get the distance to the given city
	 * @param city given city
	 * @return the distance to the given city
	 */
	public double getDistanceTo(String city) {
		return distanceToOtherCity.get(city);
	}
}
