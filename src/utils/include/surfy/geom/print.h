/*

Printer

*/

namespace surfy::geom {

	namespace print {
		/*

		Point

		*/

		void point(std::ostream& os, const Point& point) {
			os << point.x << " " << point.y;
		}

		/*

		Line

		*/

		void line(std::ostream& os, const std::vector<Point>& coords) {
			os << "(";
			size_t length = coords.size();
			for (size_t i = 0; i < length; ++i) {
				point(os, coords[i]);
				if (i != length - 1) {
					os << ", ";
				}
			}
			os << ")";
		}

		/*

		Polygon

		*/

		void polygon(std::ostream& os, const Polygon& poly) {
			os << "(";

			line(os, poly.outer.coords);

			if (!poly.inner.coords.empty()) {
				os << ",";
				line(os, poly.inner.coords);
			}

			os << ")";
		}
	}
}