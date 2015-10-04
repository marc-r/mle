#include <cmath>

#include <algorithm>
#include <iostream>
#include <random>

#include "routes.h"


using namespace std;

constexpr int N_ITER = 1'000'000;

int main() {
  auto cities = generateCities();
  auto distances = calcDistances(cities);

  // Create default route
  Route route;
  iota(begin(route), end(route), 0);

  default_random_engine generator;
  uniform_int_distribution<int> idist(0, N_CITIES - 1);
  double current_fitness = getRouteDistance(distances, route);
  for (int i = 0; i < N_ITER; ++i) {
    int swap_pos1 = idist(generator);
    int swap_pos2 = idist(generator);

    swap(route[swap_pos1], route[swap_pos2]);

    double new_fitness = getRouteDistance(distances, route);
    if (new_fitness < current_fitness) {
      current_fitness = new_fitness;
      cout << "Found a better route: " << current_fitness << endl;
    } else {
      swap(route[swap_pos1], route[swap_pos2]);
    }
  }

  cout << "The best route has: " << current_fitness << endl;

  return 0;
}

