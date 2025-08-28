#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <climits>
#include <cmath>
#include <iomanip>
using namespace std;

class Graph_M {
public:
    class Vertex {
    public:
        string line;
        unordered_map<string, int> neighbors;
    };

    unordered_map<string, Vertex> stations;

    void addVertex(const string& stationName, const string& line) {
        if (stations.count(stationName)) {
            // If station already exists, just append new line info
            if (stations[stationName].line.find(line) == string::npos) {
                stations[stationName].line += " & " + line;
            }
        } else {
            Vertex station;
            station.line = line;
            stations[stationName] = station;
        }
    }

    void addEdge(const string& station1, const string& station2, int distance) {
        if (stations.count(station1) && stations.count(station2)) {
            stations[station1].neighbors[station2] = distance;
            stations[station2].neighbors[station1] = distance;
        }
    }

    void display_Map() {
        cout << "\n\t🗺️  Delhi Metro Map" << endl;
        cout << "\t--------------------------" << endl;

        for (auto& stationPair : stations) {
            cout << stationPair.first << " (" << stationPair.second.line << ")";
            if (stationPair.second.line.find("&") != string::npos)
                cout << " 🔁 Interchange Station";
            cout << " =>\n";

            for (auto& neighborPair : stationPair.second.neighbors) {
                cout << "\t" << setw(25) << left << neighborPair.first
                     << "Distance: " << neighborPair.second << " km" << endl;
            }
        }

        cout << "\t--------------------------\n" << endl;
    }

    void display_Stations() {
        cout << "\n📍 Available Stations:\n";
        cout << "--------------------------" << endl;
        int i = 1;
        for (auto& stationPair : stations) {
            cout << i++ << ". " << stationPair.first << " (" << stationPair.second.line << ")";
            if (stationPair.second.line.find("&") != string::npos)
                cout << " 🔁 Interchange Station";
            cout << endl;
        }
        cout << "--------------------------\n" << endl;
    }

    string Get_Minimum_Distance(const string& src, const string& dst) {
        if (!stations.count(src) || !stations.count(dst)) {
            return "❌ Error: One or both station names are invalid.";
        }

        unordered_map<string, int> distances;
        unordered_map<string, string> parents;
        unordered_map<string, bool> visited;
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;

        for (auto& station : stations)
            distances[station.first] = INT_MAX;

        distances[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
          int currentDistance= pq.top().first;
            string currentStation=pq.top().second;
            pq.pop();

            if (visited[currentStation]) continue;
            visited[currentStation] = true;

            if (currentStation == dst) {
                string path = dst, current = dst;
                int totalStops = 0;
                while (current != src) {
                    current = parents[current];
                    path = current + " -> " + path;
                    totalStops++;
                }
                return "🚉 Path: " + path +
                       "\n📏 Total Distance: " + to_string(currentDistance) + " km" +
                       "\n🚏 Total Stations: " + to_string(totalStops + 1);
            }

            for (auto& neighbor : stations[currentStation].neighbors) {
                int lineChangePenalty = 0;
                if (stations[neighbor.first].line != stations[currentStation].line)
                    lineChangePenalty = 1; // 1 km penalty for transfer

                int newDistance = currentDistance + neighbor.second + lineChangePenalty;

                if (newDistance < distances[neighbor.first]) {
                    distances[neighbor.first] = newDistance;
                    parents[neighbor.first] = currentStation;
                    pq.push({newDistance, neighbor.first});
                }
            }
        }
        return "❌ No path found between " + src + " and " + dst;
    }

    string Get_Minimum_Time(const string& src, const string& dst) {
        if (!stations.count(src) || !stations.count(dst)) {
            return "❌ Error: One or both station names are invalid.";
        }

        unordered_map<string, int> times;
        unordered_map<string, string> parents;
        unordered_map<string, bool> visited;
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;

        for (auto& station : stations)
            times[station.first] = INT_MAX;

        times[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
           int currentTime= pq.top().first;
            string currentStation=pq.top().second;
            pq.pop();

            if (visited[currentStation]) continue;
            visited[currentStation] = true;

            if (currentStation == dst) {
                string path = dst, current = dst;
                int totalStops = 0;
                while (current != src) {
                    current = parents[current];
                    path = current + " -> " + path;
                    totalStops++;
                }
                int minutes = ceil((double)currentTime / 60);
                return "🚉 Path: " + path +
                       "\n⏱️ Estimated Time: " + to_string(minutes) + " minutes" +
                       "\n🚏 Total Stations: " + to_string(totalStops + 1);
            }

            for (auto& neighbor : stations[currentStation].neighbors) {
                int lineChangePenalty = 0;
                if (stations[neighbor.first].line != stations[currentStation].line)
                    lineChangePenalty = 300; // 5 minutes in seconds

                int travelTime = currentTime + 120 + (40 * neighbor.second) + lineChangePenalty;

                if (travelTime < times[neighbor.first]) {
                    times[neighbor.first] = travelTime;
                    parents[neighbor.first] = currentStation;
                    pq.push({travelTime, neighbor.first});
                }
            }
        }
        return "❌ No path found between " + src + " and " + dst;
    }

    void Create_Metro_Map() {
        // Blue Line
        addVertex("Noida City Centre", "Blue Line");
        addVertex("Botanical Garden", "Blue Line");
        addVertex("Golf Course", "Blue Line");
        addVertex("Noida Sector 18", "Blue Line");
        addVertex("Yamuna Bank", "Blue Line");

        // Yellow Line
        addVertex("Rajiv Chowk", "Yellow Line");
        addVertex("Central Secretariat", "Yellow Line");
        addVertex("Chandni Chowk", "Yellow Line");

        // Add interchange logic
        addVertex("Yamuna Bank", "Yellow Line"); // Now a dual-line station

        // Edges
        addEdge("Noida City Centre", "Botanical Garden", 8);
        addEdge("Botanical Garden", "Golf Course", 4);
        addEdge("Golf Course", "Noida Sector 18", 7);
        addEdge("Noida Sector 18", "Yamuna Bank", 3);
        addEdge("Yamuna Bank", "Rajiv Chowk", 10);
        addEdge("Rajiv Chowk", "Central Secretariat", 2);
        addEdge("Central Secretariat", "Chandni Chowk", 5);
    }
};

int main() {
    Graph_M metroMap;
    metroMap.Create_Metro_Map();

    int choice;
    string source, destination;

    do {
        cout << "\n============== 🧭 Delhi Metro Navigator ==============\n";
        cout << "1. Show Metro Map\n";
        cout << "2. List All Stations\n";
        cout << "3. Find Minimum Distance Path\n";
        cout << "4. Find Fastest Path (Time-based)\n";
        cout << "5. Add New Station\n";
        cout << "6. Add New Connection (Edge)\n";
        cout << "0. Exit\n";
        cout << "======================================================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                metroMap.display_Map();
                break;
            case 2:
                metroMap.display_Stations();
                break;
            case 3:
                cout << "Enter Source Station: ";
                getline(cin, source);
                cout << "Enter Destination Station: ";
                getline(cin, destination);
                cout << "\n" << metroMap.Get_Minimum_Distance(source, destination) << "\n";
                break;
            case 4:
                cout << "Enter Source Station: ";
                getline(cin, source);
                cout << "Enter Destination Station: ";
                getline(cin, destination);
                cout << "\n" << metroMap.Get_Minimum_Time(source, destination) << "\n";
                break;
            case 5: {
                string name, line;
                cout << "Enter new station name: ";
                getline(cin, name);
                cout << "Enter metro line (e.g., Red Line): ";
                getline(cin, line);
                metroMap.addVertex(name, line);
                cout << "✅ Station added successfully.\n";
                break;
            }
            case 6: {
                string from, to;
                int dist;
                cout << "Enter station 1 name: ";
                getline(cin, from);
                cout << "Enter station 2 name: ";
                getline(cin, to);
                cout << "Enter distance in km: ";
                cin >> dist;
                cin.ignore();
                if (!metroMap.stations.count(from) || !metroMap.stations.count(to)) {
                    cout << "❌ Error: One or both stations do not exist. Add them first.\n";
                } else {
                    metroMap.addEdge(from, to, dist);
                    cout << "✅ Connection added successfully.\n";
                }
                break;
            }
            case 0:
                cout << "Thank you for using the Delhi Metro Navigator!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
