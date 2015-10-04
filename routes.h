#include <cmath>

#include <array>
#include <algorithm>
#include <random>

#include <armadillo>

constexpr int N_CITIES = 100;

using Route = std::array<int, N_CITIES>;

struct City {
    double x, y;
};

double getRouteDistance(const arma::mat &distances, const Route &route);
double getDistance(City city, City city2);
std::vector<City> generateCities();
arma::mat calcDistances(const std::vector<City> &cities);


double getRouteDistance(const arma::mat &distances, const Route &route) {
  double distance = 0;
  for (int i = 0; i < N_CITIES; ++i) {
    if (i == N_CITIES - 1) {
      distance += distances(route[i], route[0]);
    } else {
      distance += distances(route[i], route[i + 1]);
    }
  }
  return distance;
}

double getDistance(City city, City city2) {
  double x = city.x - city2.x;
  double y = city.y - city2.y;

  return sqrt(x * x + y * y);
}

std::vector<City> generateCities() {
  static constexpr double MAX_COORD = 1000.0;

  std::default_random_engine generator;
  std::uniform_real_distribution<double> dist(0, MAX_COORD);

  std::vector<City> cities(N_CITIES);
  std::generate(begin(cities), end(cities), [&]() {
    return City{dist(generator), dist(generator)};
  });

  return cities;
}

arma::mat calcDistances(const std::vector<City> &cities) {
  arma::mat distances(N_CITIES, N_CITIES);
  for (int i = 0; i < N_CITIES; ++i) {
    for (int j = 0; j < N_CITIES; ++j) {
      distances(i, j) = getDistance(cities[i], cities[j]);
    }
  }
  return distances;
}
