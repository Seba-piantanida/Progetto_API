# Highway Route Planner 🛣️⚡

**Algorithms and Data Structures Final Project**

An efficient C implementation designed to manage a highway system and calculate optimal travel routes for electric vehicles. The goal is to minimize the number of stops between stations while adhering to strict time and memory constraints.

## 📋 Project Overview

The system models a highway as a sequence of service stations located at specific distances. Each station maintains a fleet of electric vehicles with varying battery ranges (autonomy).

The core feature is the **Route Planning** algorithm, which solves the following problem:
Given a starting point and a destination, find the path that requires the **minimum number of stops**.

### Key Logic & Constraints
* **Minimal Stops:** The primary objective is to reach the destination with the fewest intermediate stops.
* **Tie-Breaking Rule:** If multiple paths share the same minimal number of stops, the algorithm selects the path where the intermediate stations have the shortest distance from the start of the highway (lexicographically smallest path).
* **Efficiency:** Designed to handle large datasets using optimized data structures, respecting the 32-bit integer limits for distances.
* **Fleet Limit:** Each station manages up to 512 vehicles.

## ⚙️ Functionalities

The application parses commands from `stdin` to modify the highway structure or request paths:

* `aggiungi-stazione` (Add Station): Adds a new station with a set of vehicles.
* `demolisci-stazione` (Demolish Station): Removes an existing station.
* `aggiungi-auto` (Add Car): Adds a vehicle to an existing station's fleet.
* `rottama-auto` (Scrap Car): Removes a specific vehicle from a station.
* `pianifica-percorso` (Plan Route): Outputs the optimal sequence of stations for the trip.

## 🛠️ Build and Run

To compile the project using GCC:

```bash
gcc -o highway_planner main.c -O2
