project(MLE_UE1)
cmake_minimum_required(VERSION 2.8)

add_definitions(-std=c++14 -Wall -Werror)

add_executable(HillClimbing hill_climbing.cpp routes.h)

add_executable(SimulatedAnnealing simulated_annealing.cpp routes.h)
