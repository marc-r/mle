
#include "routes.h"

using namespace std;

constexpr int N_ITER = 1'000'000;

double w(double x, double y, double T) { return exp(-(y - x) / T); }

int main(int argc, char **argv) {
  auto cities = generateCities();
  auto distances = calcDistances(cities);

  Route route;
  iota(begin(route), end(route), 0);

  default_random_engine generator;
  uniform_real_distribution<double> trial(0.0, 1.0);
  uniform_int_distribution<int> idist(0, N_CITIES - 1);
  double current_fitness = getRouteDistance(distances, route);
  double temperature = 40.0f;
  double epsilon = temperature / N_ITER;

  for (int i = 0; i < N_ITER; ++i) {
    int swap_pos1 = idist(generator);
    int swap_pos2 = idist(generator);

    swap(route[swap_pos1], route[swap_pos2]);

    double new_fitness = getRouteDistance(distances, route);
    double p = w(current_fitness, new_fitness, temperature);
    if (new_fitness < current_fitness || trial(generator) < p) {
      current_fitness = new_fitness;
      cout << "Found a better route: " << current_fitness << endl;
    } else {
      swap(route[swap_pos1], route[swap_pos2]);
    }
    temperature -= epsilon;
  }

  cout << "The best route has: " << current_fitness << endl;
}
