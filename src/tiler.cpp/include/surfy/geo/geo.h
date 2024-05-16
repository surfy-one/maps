#ifndef SURFY_GEO_HPP
#define SURFY_GEO_HPP

namespace surfy::geo {

	struct Tile {
		int zoom;
		int x;
		int y;
	};

	using Tiles = std::vector<Tile>;

	std::vector<double> normalize(double lng, double lat) {
		double x = lng / 360.0 + 0.5;
		double sinlat = std::sin(lat * M_PI / 180.0);
		double y = 0.5 - 0.25 * std::log((1.0 + sinlat) / (1.0 - sinlat)) / M_PI;

		return {x, y};
	}

	/*

	std::vector<int> bounds = tilesRange(zoom, westSouth[0], westSouth[1], eastNorth[0], eastNorth[1]);
	
	for (int x = bounds[0]; x < bounds[2]; ++x) {
		for (int y = bounds[1]; y < bounds[3]; ++y) {
			{zoom, x, y};
		}
	}

	*/

	std::array<int, 4> tiles(int zoom, double x1, double y1, double x2, double y2) {
		int Z2 = std::pow(2, zoom);

		int west = static_cast<int>(std::floor(x1 * Z2));
		int north = static_cast<int>(std::floor(y1 * Z2));
		int east = static_cast<int>(std::ceil(x2 * Z2));
		int south = static_cast<int>(std::ceil(y2 * Z2));

		return {west, north, east, south};
	}

	/*

	Get Tile BBox

	*/

	std::string tileBBox(int zoom, int xtile, int ytile) {
		double Z2 = std::pow(2, zoom);

		double west = xtile / Z2 * 360.0 - 180.0;
		double northRad = std::atan(std::sinh(M_PI * (1 - 2 * ytile / Z2)));
		double north = northRad * 180.0 / M_PI;

		double east = (xtile + 1) / Z2 * 360.0 - 180.0;
		double southRad = std::atan(std::sinh(M_PI * (1 - 2 * (ytile + 1) / Z2)));
		double south = southRad * 180.0 / M_PI;

		// Stringify automaticaly rounds float to 6 decimals
		std::vector<double> tile = {
			west,
			north,
			east,
			south
		};

		std::string polygon = "(" +
			std::to_string(tile[2]) + " " + std::to_string(tile[3]) + ", " +
			std::to_string(tile[2]) + " " + std::to_string(tile[1]) + ", " +
			std::to_string(tile[0]) + " " + std::to_string(tile[1]) + ", " +
			std::to_string(tile[0]) + " " + std::to_string(tile[3]) + ", " +
			std::to_string(tile[2]) + " " + std::to_string(tile[3]) + ")";
		return polygon;
	}
}

#endif