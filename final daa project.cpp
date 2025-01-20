//REGISTER LOGIN MODULE
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <iomanip>

// A simple SHA-256 implementation for demonstration purposes

// This is not a complete or secure implementation of SHA-256.
std::string simpleSHA256(const std::string& input)
{
    // This is a placeholder for a real SHA-256 implementation.

    // For simplicity, we'll just return a dummy hash.

    std::string hash = "dummyhash";

    return hash;
}

// User database simulation
std::unordered_map<std::string, std::string> userDatabase;

bool registerUser(const std::string& username, const std::string& password, const std::string& confirmPassword)
{

    if (username.empty() || password.empty())
    {
        std::cout << "Username and password cannot be empty!" << std::endl;
        return false;
    }
    if (password != confirmPassword)
        {
        std::cout << "Passwords do not match!" << std::endl;

        return false;
    }
    if (userDatabase.find(username) != userDatabase.end())
        {
        std::cout << "Username already exists!" << std::endl;

        return false;
    }

    std::string hashedPassword = simpleSHA256(password);
    userDatabase[username] = hashedPassword;

    std::cout << "Registration successful!" << std::endl;

    return true;
}

bool loginUser(const std::string& username, const std::string& password)
{
    auto it = userDatabase.find(username);

    if (it == userDatabase.end())
    {
        std::cout << "Username does not exist!" << std::endl;

        return false;
    }

    std::string hashedPassword = simpleSHA256(password);

    if (it->second == hashedPassword)
        {
        std::cout << "Login successful! Welcome, " << username << "!" << std::endl;

        return true;
    }
    else
    {
        std::cout << "Invalid password!" << std::endl;

        return false;
    }
}

int module1()
{
    int choice;

    std::string username, password, confirmPassword;

    while (true)
    {
        std::cout << "\nUser Authentication System" << std::endl;

        std::cout << "1. Register" << std::endl;

        std::cout << "2. Login" << std::endl;

        std::cout << "3. Exit" << std::endl;

        std::cout << "Choose an option: ";

        std::cin >> choice;

        std::cin.ignore(); // Clear the newline character from the input buffer

        switch (choice)
        {
            case 1:
                // Registration

                std::cout << "Enter Username: ";

                std::getline(std::cin, username);

                std::cout << "Enter Password: ";

                std::getline(std::cin, password);

                std::cout << "Confirm Password: ";

                std::getline(std::cin, confirmPassword);

                registerUser(username, password, confirmPassword);

                break;

            case 2:
                // Login

                std::cout << "Enter Username: ";

                std::getline(std::cin, username);

                std::cout << "Enter Password: ";

                std::getline(std::cin, password);

                loginUser(username, password);

                break;

            case 3:
                 // Exit

                std::cout << "Exiting the program." << std::endl;

                return 0;

            default:

                std::cout << "Invalid option! Please try again." << std::endl;
        }
    }

    return 0;
}



//NAVIGAION MODULE

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <unordered_map> // Needed for the unordered_map

using namespace std;

typedef pair<int, double> Node;

typedef vector<vector<Node>> Graph;

vector<int> dijkstra(const Graph& graph, int start, int end, double& totalDistance)
{
    int n = graph.size();

    priority_queue<Node, vector<Node>, greater<Node>> pq;

    vector<double> distances(n, 1e9);

    vector<int> previous(n, -1);

    vector<int> path;

    distances[start] = 0.0;
    pq.push({start, 0.0});

    while (!pq.empty())
    {
        int current = pq.top().first;

        double currentDist = pq.top().second;

        pq.pop();

        if (current == end)
        {
            totalDistance = currentDist;
            while (current != start)
            {
                path.push_back(current);

                current = previous[current];
            }
            path.push_back(start);

            reverse(path.begin(), path.end());

            return path;
        }

        for (const auto& neighbor : graph[current])
        {
            int next = neighbor.first;

            double edgeWeight = neighbor.second;

            double newDist = currentDist + edgeWeight;

            if (newDist < distances[next])
            {
                distances[next] = newDist;

                previous[next] = current;

                pq.push({next, newDist});
            }
        }
    }

    totalDistance = 1e9;

    return path;
}

double heuristic(int current, int goal)
{
    return abs(current - goal);
}

vector<int> aStar(const Graph& graph, int start, int end, const vector<double>& congestionData, double& totalTime)
{
    int n = graph.size();

    priority_queue<Node, vector<Node>, greater<Node>> pq;

    vector<double> gScores(n, 1e9);

    vector<double> fScores(n, 1e9);

    vector<int> previous(n, -1);

    vector<int> path;

    gScores[start] = 0.0;

    fScores[start] = heuristic(start, end);

    pq.push({start, fScores[start]});

    while (!pq.empty())
    {
        int current = pq.top().first;

        pq.pop();

        if (current == end)
        {
            totalTime = gScores[end];

            while (current != start)
            {
                path.push_back(current);

                current = previous[current];
            }
            path.push_back(start);

            reverse(path.begin(), path.end());

            return path;
        }

        for (const auto& neighbor : graph[current])
        {
            int next = neighbor.first;

            double edgeWeight = neighbor.second + congestionData[next];

            double tentativeGScore = gScores[current] + edgeWeight;

            if (tentativeGScore < gScores[next])
            {
                previous[next] = current;
                gScores[next] = tentativeGScore;

                fScores[next] = gScores[next] + heuristic(next, end);

                pq.push({next, fScores[next]});
            }
        }
    }

    totalTime = 1e9;

    return path;
}

vector<int> preprocessBoyerMoore(const string& pattern)
{
    const int ALPHABET_SIZE = 256;

    vector<int> badCharShift(ALPHABET_SIZE, -1);

    for (int i = 0; i < pattern.size(); ++i)
    {
        badCharShift[pattern[i]] = i;
    }

    return badCharShift;
}

vector<int> boyerMooreSearch(const string& text, const string& pattern)
{
    vector<int> badCharShift = preprocessBoyerMoore(pattern);

    vector<int> matches;
    int m = pattern.size();

    int n = text.size();

    int s = 0;
    while (s <= (n - m))
    {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[s + j])
        {
            --j;
        }

        if (j < 0)
        {
            matches.push_back(s);
            s += (s + m < n) ? m - badCharShift[text[s + m]] : 1;
        }
        else
        {
            s += max(1, j - badCharShift[text[s + j]]);
        }
    }

    return matches;
}

struct TouristInfo
{
    string name;

    string location;

    string description;
};

void searchTouristInfo(const string& query, const vector<TouristInfo>& database)
{
    for (const auto& info : database)
    {
        if (!boyerMooreSearch(info.name, query).empty() ||
            !boyerMooreSearch(info.location, query).empty() ||
            !boyerMooreSearch(info.description, query).empty())
        {
            cout << "Name: " << info.name << "\nLocation: " << info.location << "\nDescription: " << info.description << "\n\n";
        }
    }
}

vector<int> bellmanFord(const Graph& graph, int start, int end, double& totalDistance)
{
    int n = graph.size();
    vector<double> distances(n, 1e9);

    vector<int> previous(n, -1);

    vector<int> path;

    distances[start] = 0.0;

    for (int i = 0; i < n - 1; ++i)
    {
        for (int u = 0; u < n; ++u)
        {
            for (const auto& neighbor : graph[u])
            {
                int v = neighbor.first;

                double weight = neighbor.second;

                if (distances[u] != 1e9 && distances[u] + weight < distances[v])
                {
                    distances[v] = distances[u] + weight;
                    previous[v] = u;
                }
            }
        }
    }

    for (int u = 0; u < n; ++u)
    {
        for (const auto& neighbor : graph[u])
        {
            int v = neighbor.first;

            double weight = neighbor.second;

            if (distances[u] != 1e9 && distances[u] + weight < distances[v])
            {
                cout << "Graph contains a negative-weight cycle\n";
                totalDistance = 1e9;

                return {};
            }
        }
    }

    if (distances[end] != 1e9)
    {
        totalDistance = distances[end];

        int current = end;

        while (current != start)
        {
            path.push_back(current);
            current = previous[current];
        }
        path.push_back(start);
        reverse(path.begin(), path.end());

        return path;
    }

    totalDistance = 1e9;

    return path;
}

void displayGraph(const Graph& graph)
{
    for (int i = 0; i < graph.size(); ++i)
    {
        cout << "Node " << i << " has edges to:\n";

        for (const auto& neighbor : graph[i])
        {
            cout << "  Node " << neighbor.first << " with weight " << neighbor.second << "\n";
        }
    }
}

void addEdge(Graph& graph, int from, int to, double weight)
{
    graph[from].push_back({to, weight});

    cout << "Edge added from Node " << from << " to Node " << to << " with weight " << weight << "\n";
}

void removeEdge(Graph& graph, int from, int to)
{
    auto& neighbors = graph[from];
    neighbors.erase(remove_if(neighbors.begin(), neighbors.end(), [to](const Node& neighbor)
                              {

        return neighbor.first == to;
    }), neighbors.end());
    cout << "Edge removed from Node " << from << " to Node " << to << "\n";
}

void updateCongestionData(vector<double>& congestionData, int node, double newCongestion)
{
    congestionData[node] = newCongestion;

    cout << "Congestion data updated for Node " << node << " to " << newCongestion << "\n";
}

void displayTouristInfo(const vector<TouristInfo>& database)
{
    cout << "Tourist Information Database:\n";

    for (const auto& info : database)
    {
        cout << "Name: " << info.name << "\nLocation: " << info.location << "\nDescription: " << info.description << "\n\n";
    }
}

int module2()
{
    unordered_map<string, int> locationMap =
    {
        {"Central Park", 0},

        {"Statue of Liberty", 1},

        {"Eiffel Tower", 2},

        {"Louvre Museum", 3},

        {"Notre Dame Cathedral", 4}
    };

    Graph cityGraph(5);

    cityGraph[1] = {{2, 1.0}, {3, 4.0}};

    cityGraph[2] = {{1, 1.0}, {3, 2.0}, {4, 5.0}};

    cityGraph[3] = {{1, 4.0}, {2, 2.0}, {4, 1.0}};

    cityGraph[4] = {{2, 5.0}, {3, 1.0}};

    vector<double> congestionData(5, 0.0);

    congestionData[2] = 1.0;

    congestionData[3] = 1.5;

    congestionData[4] = 0.5;

    vector<TouristInfo> database =
    {
        {"Central Park", "NYC", "A large public park in New York City."},

        {"Statue of Liberty", "NYC", "A colossal neoclassical sculpture on Liberty Island."},

        {"Eiffel Tower", "Paris", "A wrought-iron lattice tower on the Champ de Mars in Paris, France."}
    };

    string startLocation, endLocation, query;

    cout << "Graph representation of the city:\n";
    displayGraph(cityGraph);

    cout << "Enter start location for Dijkstra: ";
    getline(cin, startLocation);

    cout << "Enter end location for Dijkstra: ";
    getline(cin, endLocation);

    double totalDistance;

    vector<int> shortestPath = dijkstra(cityGraph, locationMap[startLocation], locationMap[endLocation], totalDistance);

    cout << "Shortest path using Dijkstra: ";

    for (int node : shortestPath)
    {
        for (auto& loc : locationMap)
        {
            if (loc.second == node)
            {
                cout << loc.first << " ";
                break;
            }
        }
    }
    cout << "\nTotal distance: " << totalDistance << endl;

    cout << "Enter current location for A*: ";

    getline(cin, startLocation);

    cout << "Enter destination for A*: ";
    getline(cin, endLocation);

    double totalTime;

    vector<int> optimalPath = aStar(cityGraph, locationMap[startLocation], locationMap[endLocation], congestionData, totalTime);

    cout << "Optimal path using A*: ";

    for (int node : optimalPath)
    {
        for (auto& loc : locationMap)
        {
            if (loc.second == node)
            {
                cout << loc.first << " ";
                break;
            }
        }
    }
    cout << "\nEstimated time: " << totalTime << endl;

    cout << "Enter start location for Bellman-Ford: ";

    getline(cin, startLocation);

    cout << "Enter end location for Bellman-Ford: ";

    getline(cin, endLocation);

    vector<int> bfPath = bellmanFord(cityGraph, locationMap[startLocation], locationMap[endLocation], totalDistance);

    cout << "Shortest path using Bellman-Ford: ";

    for (int node : bfPath)
    {
        for (auto& loc : locationMap)
        {
            if (loc.second == node)
            {
                cout << loc.first << " ";
                break;
            }
        }
    }
    cout << "\nTotal distance: " << totalDistance << endl;

    cout << "Enter query for tourist information: ";

    getline(cin, query);

    cout << "Search results for \"" << query << "\":\n";
    searchTouristInfo(query, database);

    cout << "\nTourist Information Database:\n";
    displayTouristInfo(database);

    addEdge(cityGraph, locationMap["Central Park"], locationMap["Statue of Liberty"], 2.0);

    removeEdge(cityGraph, locationMap["Statue of Liberty"], locationMap["Eiffel Tower"]);
    updateCongestionData(congestionData, locationMap["Eiffel Tower"], 0.8);

    return 0;
}





//RESOURCE DISTRIBUTION FOR BICYCLE MODULE


#include <iostream> // Include input-output stream library
#include <queue> // Include queue library for priority queue
#include <vector> // Include vector library for dynamic arrays
#include <string> // Include string library
#include <algorithm> // Include algorithm library

using namespace std; // Use the standard namespace

// Define a structure for the resource request
struct ResourceRequest
{
    int priority; // Priority of the request
    string location; // Location of the request
    string resourceType; // Type of resource requested
    int count; // Number of resources requested

    // Overload the < operator for priority queue
    bool operator<(const ResourceRequest& other) const
    {
        return priority > other.priority; // Min-heap based on priority
    }
};

// Define a structure for the resources at a location
struct LocationResources
{
    string location; // Location name

    int bicycles; // Number of bicycles at the location

    int shuttles; // Number of shuttles at the location
};

// Define a structure for an edge in the graph
struct Edge
{
    int weight; // Weight of the edge

    int from; // Starting node of the edge

    int to; // Ending node of the edge

    // Overload the < operator for priority queue
    bool operator<(const Edge& other) const
    {
        return weight > other.weight; // Min-heap based on weight
    }
};

class ResourceManagement
{
public:
    // Priority queue for resource requests (min-heap)

    priority_queue<ResourceRequest> resourceRequests;
    // Vector to track resources at each location

    vector<LocationResources> resources;

    // Add a resource request to the priority queue
    void addResourceRequest(const string& location,
                            const string& resourceType,
                            int priority,
                            int count)
    {
        resourceRequests.push({priority, location, resourceType, count});

        cout << "Added request for " << count << " " << resourceType << "(s) at "
             << location << " with priority " << priority << endl; // Debugging statement
    }

    // Remove a specific resource request
    void removeResourceRequest(const string& location,
                               const string& resourceType)
                               {
        priority_queue<ResourceRequest> tempQueue; // Temporary queue to hold remaining requests

        while (!resourceRequests.empty())
            {
            ResourceRequest request = resourceRequests.top(); // Get the top request
            resourceRequests.pop(); // Remove the top request

            if (!(request.location == location && request.resourceType == resourceType))
                {
                tempQueue.push(request); // Keep the request if it doesn't match
            }
        }
        resourceRequests = tempQueue; // Update the main queue

        cout << "Removed request for " << resourceType << " at " << location << endl;
    }

    // Update the priority of an existing resource request
    void updateResourceRequestPriority(const string& location,
                                       const string& resourceType,
                                       int newPriority)
                                        {
        removeResourceRequest(location, resourceType);
        // Assuming the count remains the same for simplicity
        int count = 1;

        addResourceRequest(location, resourceType, newPriority, count);

        cout << "Updated priority for " << resourceType << " at " << location
             << " to " << newPriority << endl;
    }

    // List all the resource requests
    void listAllRequests()
     {

        if (resourceRequests.empty())
            {
            cout << "No resource requests present" << endl;

            return;
        }
        priority_queue<ResourceRequest> tempQueue = resourceRequests; // Copy the queue

        cout << "Listing all resource requests:" << endl;

        while (!tempQueue.empty())
            {
            ResourceRequest request = tempQueue.top(); // Get the top request
            tempQueue.pop(); // Remove the top request

            cout << "Location: " << request.location
                 << ", Resource: " << request.resourceType
                 << ", Priority: " << request.priority
                 << ", Count: " << request.count << endl;
        }
    }

    // Add resources to a specific location
    void addResources(const string& location,
                      const string& resourceType,
                      int count)
                      {

        for (auto& res : resources)
            {

            if (res.location == location)
            {

                if (resourceType == "bicycle")
                {
                    res.bicycles += count;
                }
                else if (resourceType == "shuttle")
                {
                    res.shuttles += count;
                }
                cout << "Added " << count << " " << resourceType << "(s) to " << location << endl; // Debugging statement

                return;
            }
        }
        // If location not found, add a new location
        if (resourceType == "bicycle")
            {
            resources.push_back({location, count, 0});
        }
        else if (resourceType == "shuttle")
        {
            resources.push_back({location, 0, count});
        }
        cout << "Created new location " << location
             << " and added " << count << " " << resourceType << "(s)" << endl; // Debugging statement
    }

    // Remove resources from a specific location
    void removeResources(const string& location,
                         const string& resourceType,
                         int count)
                         {
        for (auto& res : resources)
            {

            if (res.location == location)
            {

                if (resourceType == "bicycle" && res.bicycles >= count)
                {
                    res.bicycles -= count;

                    cout << "Removed " << count << " bicycle(s) from " << location << endl;
                }
                else if (resourceType == "shuttle" && res.shuttles >= count)
                    {
                    res.shuttles -= count;

                    cout << "Removed " << count << " shuttle(s) from " << location << endl;
                } else
                {
                    cout << "Not enough " << resourceType
                         << "s to remove from " << location << endl;
                }

                return;
            }
        }

        cout << "Location " << location << " not found" << endl;
    }

    // Check availability of resources at a specific location
    bool checkAvailability(const string& location,
                           const string& resourceType)
                            {
        for (const auto& res : resources)
            {

            if (res.location == location)
             {
                if (resourceType == "bicycle" && res.bicycles > 0)
                {

                    return true;
                }
                else if (resourceType == "shuttle" && res.shuttles > 0)
                 {

                    return true;
                }

                return false;
            }
        }

        return false;
    }

    // List all resources at a specific location
    void listResourcesAtLocation(const string& location)
    {

        for (const auto& res : resources)
            {
            if (res.location == location)
            {
                cout << "Location: " << res.location << endl;

                cout << "  Bicycles: " << res.bicycles << endl;

                cout << "  Shuttles: " << res.shuttles << endl;

                return;
            }
        }
        cout << "Location " << location << " not found" << endl;
    }

    // Allocate resources based on the requests' priority using a greedy algorithm
    void allocateResources()
     {
        if (resourceRequests.empty())
            {
            cout << "No resource requests present" << endl;

            return;
        }
        while (!resourceRequests.empty())
        {
            ResourceRequest request = resourceRequests.top(); // Get the top request

            resourceRequests.pop(); // Remove the top request

            bool allocated = false;

            for (auto& res : resources)
                {

                if (res.location == request.location)
                 {

                    if (request.resourceType == "bicycle" && res.bicycles >= request.count)
                     {
                        res.bicycles -= request.count;

                        cout << "Allocated " << request.count << " bicycle(s) to "
                             << request.location << " (Priority: " << request.priority << ")" << endl;
                        allocated = true;

                        break;
                    }

                    else if (request.resourceType == "shuttle" && res.shuttles >= request.count)
                    {
                        res.shuttles -= request.count;

                        cout << "Allocated " << request.count << " shuttle(s) to "
                             << request.location << " (Priority: " << request.priority << ")" << endl;
                        allocated = true;

                        break;
                    }
                }
            }

            if (!allocated)
            {
                cout << "No available " << request.resourceType << "s at "

                     << request.location << " for request with priority " << request.priority << endl;
            }
        }
    }

    // Track resources at each location

    void trackResources()
    {
        if (resources.empty())
            {

            cout << "No resources present" << endl;

            return;
        }

        cout << "Current Resource Status:" << endl;

        for (const auto& res : resources)
            {

            cout << "Location: " << res.location << endl;

            cout << "  Bicycles: " << res.bicycles << endl;

            cout << "  Shuttles: " << res.shuttles << endl;
        }
    }

    // Get total available resources of a specific type

    int getTotalAvailableResources(const string& resourceType)
    {
        int total = 0;
        for (const auto& res : resources)
            {
            if (resourceType == "bicycle")
            {
                total += res.bicycles;
            }
            else if (resourceType == "shuttle")
            {
                total += res.shuttles;
            }
        }
        return total;
    }

    // Get resource availability at a specific location
    int getResourceAvailability(const string& location,
                                const string& resourceType)
                                 {
        for (const auto& res : resources)
            {

            if (res.location == location)
            {

                if (resourceType == "bicycle")
                {

                    return res.bicycles;
                }

                else if (resourceType == "shuttle")
                {

                    return res.shuttles;
                }
            }
        }
        return 0; // Location not found
    }

    // Find location with maximum available resources of a specific type

    string findLocationWithMaxResources(const string& resourceType)
    {

        if (resources.empty())
            {
            return ""; // No locations
        }
        int maxCount = 0; // Variable to track the maximum count

        string maxLocation = resources[0].location; // Variable to track the location with maximum resources

        for (const auto& res : resources)
        {
            if (resourceType == "bicycle" && res.bicycles > maxCount)
            {
                maxCount = res.bicycles;
                maxLocation = res.location;
            }

            else if (resourceType == "shuttle" && res.shuttles > maxCount)
             {
                maxCount = res.shuttles;
                maxLocation = res.location;
            }
        }

        return maxLocation;
    }

    // Rebalance resources between locations to ensure even distribution

    void rebalanceResources(const string& resourceType,
                            int target)
                            {
        int totalResources = getTotalAvailableResources(resourceType);

        int targetPerLocation = totalResources / resources.size(); // Calculate target per location

        for (auto& res : resources)
            {
            if (resourceType == "bicycle")
            {
                int diff = targetPerLocation - res.bicycles;
                if (diff > 0)
                {
                    // This location needs more bicycles

                    cout << "Need to transfer " << diff << " bicycles to " << res.location << endl;
                }
                else if (diff < 0)
                {
                    // This location has excess bicycles

                    cout << "Need to transfer " << -diff << " bicycles from " << res.location << endl;
                }
            }
            else if (resourceType == "shuttle")
                {
                int diff = targetPerLocation - res.shuttles;

                if (diff > 0)
                {
                    // This location needs more shuttles

                    cout << "Need to transfer " << diff << " shuttles to " << res.location << endl;
                }
                else if (diff < 0)
                {
                    // This location has excess shuttles

                    cout << "Need to transfer " << -diff << " shuttles from " << res.location << endl;
                }
            }
        }
    }
};

// Main function to handle user interaction
int module3() {
    ResourceManagement rms; // Create an instance of ResourceManagement

    int choice; // Variable to store user's choice

    bool exit = false; // Variable to control the exit condition

    while (!exit) {
        // Display menu options

        cout << "\nMenu:\n";

        cout << "1. Add Resources to Locations\n";

        cout << "2. Add Resource Requests\n";

        cout << "3. Check Availability of Resources\n";

        cout << "4. Track Resources\n";

        cout << "5. Allocate Resources\n";

        cout << "6. List All Resource Requests\n"; // New menu option

        cout << "7. List Resources at a Location\n"; // New menu option

        cout << "8. Remove Resource Request\n"; // New menu option

        cout << "9. Remove Resources from Locations\n"; // New menu option

        cout << "10. Update Resource Request Priority\n"; // New menu option

        cout << "11. Rebalance Resources\n"; // New menu option

        cout << "12. Exit\n";

        cout << "Enter your choice: ";

        cin >> choice; // Read user choice

        switch (choice)
        {
            case 1:
                {
                // Add resources to locations

                int numLocations;

                cout << "Enter number of locations: ";

                cin >> numLocations;

                for (int i = 0; i < numLocations; ++i)
                    {

                    string location;

                    cout << "Enter location name: ";

                    cin >> location;

                    int bicycles, shuttles;

                    cout << "Enter number of bicycles: ";

                    cin >> bicycles;

                    cout << "Enter number of shuttles: ";

                    cin >> shuttles;

                    rms.addResources(location, "bicycle", bicycles);

                    rms.addResources(location, "shuttle", shuttles);
                }
                break;
            }

            case 2:
                {
                // Add resource requests
                int numRequests;

                cout << "Enter number of resource requests: ";

                cin >> numRequests;

                for (int i = 0; i < numRequests; ++i)
                    {
                    string location;

                    int priority, bicycleCount, shuttleCount;

                    cout << "Enter location name: ";

                    cin >> location;

                    cout << "Enter priority: ";

                    cin >> priority;

                    cout << "Enter number of bicycles needed: ";

                    cin >> bicycleCount;

                    cout << "Enter number of shuttles needed: ";

                    cin >> shuttleCount;

                    if (bicycleCount > 0)
                        {
                        rms.addResourceRequest(location, "bicycle", priority, bicycleCount);
                    }
                    if (shuttleCount > 0)
                    {
                        rms.addResourceRequest(location, "shuttle", priority, shuttleCount);
                    }
                }

                break;
            }
            case 3:
                {
                // Check availability of resources
                string location, resourceType;

                cout << "Enter location to check availability: ";

                cin >> location;

                cout << "Enter resource type to check availability (B/b for bicycle, S/s for shuttle): ";

                cin >> resourceType;

                if (resourceType == "B" || resourceType == "b")
                    {
                    resourceType = "bicycle";
                }
                else if (resourceType == "S" || resourceType == "s")
                {
                    resourceType = "shuttle";
                }
                cout << (rms.checkAvailability(location, resourceType) ? "Yes" : "No") << " available" << endl;
                break;
            }
            case 4:
                 {
                // Track resources
                rms.trackResources();

                break;
            }
            case 5:
                 {
                // Allocate resources based on requests
                rms.allocateResources();

                break;
            }
            case 6:
                {
                // List all resource requests
                rms.listAllRequests();

                break;
            }
            case 7:
                {
                // List resources at a location
                string location;
                cout << "Enter location name: ";
                cin >> location;
                rms.listResourcesAtLocation(location);

                break;
            }
            case 8:
                {
                // Remove a resource request
                string location, resourceType;

                cout << "Enter location name: ";

                cin >> location;

                cout << "Enter resource type (B/b for bicycle, S/s for shuttle): ";

                cin >> resourceType;

                if (resourceType == "B" || resourceType == "b")
                    {
                    resourceType = "bicycle";
                }
                else if (resourceType == "S" || resourceType == "s")
                {
                    resourceType = "shuttle";
                }
                rms.removeResourceRequest(location, resourceType);

                break;
            }
            case 9:
                {
                // Remove resources from locations
                string location, resourceType;

                int count;

                cout << "Enter location name: ";

                cin >> location;

                cout << "Enter resource type (B/b for bicycle, S/s for shuttle): ";

                cin >> resourceType;

                if (resourceType == "B" || resourceType == "b")
                    {
                    resourceType = "bicycle";
                }
                else if (resourceType == "S" || resourceType == "s")
                {
                    resourceType = "shuttle";
                }
                cout << "Enter number of resources to remove: ";

                cin >> count;
                rms.removeResources(location, resourceType, count);

                break;
            }
            case 10:
                {
                // Update resource request priority
                string location, resourceType;
                int newPriority;
                cout << "Enter location name: ";

                cin >> location;

                cout << "Enter resource type (B/b for bicycle, S/s for shuttle): ";

                cin >> resourceType;

                if (resourceType == "B" || resourceType == "b")
                    {
                    resourceType = "bicycle";
                }
                else if (resourceType == "S" || resourceType == "s")
                    {
                    resourceType = "shuttle";
                }
                cout << "Enter new priority: ";

                cin >> newPriority;
                rms.updateResourceRequestPriority(location, resourceType, newPriority);

                break;
            }
            case 11:
                 {
                // Rebalance resources
                string resourceType;
                int target;
                cout << "Enter resource type to rebalance (B/b for bicycle, S/s for shuttle): ";

                cin >> resourceType;

                if (resourceType == "B" || resourceType == "b")
                    {
                    resourceType = "bicycle";
                }
                else if (resourceType == "S" || resourceType == "s")
                    {
                    resourceType = "shuttle";
                }
                cout << "Enter target number of resources per location: ";

                cin >> target;

                rms.rebalanceResources(resourceType, target);

                break;
            }
            case 12:
                {
                // Exit the program
                exit = true;

                break;
            }
            default:
                {
                cout << "Invalid choice. Please try again.\n";

                break;
            }
        }
    }

    return 0; // Exit the program
}





//RESOURCE DIStRIBUTION FOR EV MODULE

#include <iostream> // Include the iostream library for input and output
#include <vector> // Include the vector library for using dynamic arrays
#include <string> // Include the string library for string manipulation
#include <sstream> // Include the sstream library for string stream operations
#include <ctime> // Include the ctime library for time manipulation
#include <algorithm> // Include the algorithm library for various algorithms
#include <unordered_map> // Include the unordered_map library for hash tables

using namespace std; // Use the standard namespace

// Structure to represent a booking
struct Booking
{
    string vehicleID; // Vehicle ID for the booking

    time_t start; // Start time of the booking

    time_t end; // End time of the booking
};

// Structure to represent maintenance records
struct Maintenance
{
    string vehicleID; // Vehicle ID for the maintenance record

    time_t date; // Date of the maintenance

    string description; // Description of the maintenance
};

// Structure to represent feedback
struct Feedback
{
    string vehicleID; // Vehicle ID for the feedback

    string username; // Username of the person giving feedback

    int rating; // Rating given (1 to 5)

    string comment; // Comment provided in the feedback
};

// Function prototypes for various functionalities
bool addBooking(const string& vehicleID, time_t start, time_t end, vector<Booking>& bookings, vector<string>& conflictReports);

bool checkAvailability(const string& vehicleID, time_t start, time_t end, const vector<Booking>& bookings);

void updateBooking(const string& vehicleID, time_t oldStart, time_t newStart, time_t newEnd, vector<Booking>& bookings);

void analyzeBookings(const vector<Booking>& bookings);

double calculatePenalty(time_t actualReturn, time_t scheduledReturn, double rate);

void manageMultipleBookings(const vector<Booking>& requests, vector<Booking>& bookings, vector<string>& conflictReports);

void sendNotifications(const vector<Booking>& bookings);

void generateReport(const vector<Booking>& bookings, const vector<string>& conflictReports);

void bookingsWithinDateRange(const vector<Booking>& bookings, time_t startDate, time_t endDate);

void addMaintenance(const string& vehicleID, time_t date, const string& description, vector<Maintenance>& maintenanceRecords);

void viewMaintenance(const string& vehicleID, const vector<Maintenance>& maintenanceRecords);

void submitFeedback(const string& vehicleID, const string& username, int rating, const string& comment, vector<Feedback>& feedbacks);

void viewFeedback(const string& vehicleID, const vector<Feedback>& feedbacks);

// Helper function to convert date string to time_t
time_t convertToDate(const string& dateStr)
 {
    struct tm tm = {0}; // Initialize a tm structure to hold the date components
    sscanf(dateStr.c_str(), "%d-%d-%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday); // Parse the date string
    tm.tm_year -= 1900; // Adjust year to be years since 1900
    tm.tm_mon -= 1; // Adjust month to be 0-based

    return mktime(&tm); // Convert tm structure to time_t
}

// Helper function to format time_t to string
string formatDate(time_t date)
{

    char buffer[11]; // Buffer to hold the formatted date string
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localtime(&date)); // Format the date

    return string(buffer); // Return the formatted date as a string
}

int module4()
{
    vector<Booking> bookings; // Vector to hold all bookings

    vector<string> conflictReports; // Vector to hold conflict reports

    vector<Maintenance> maintenanceRecords; // Vector to hold maintenance records

    vector<Feedback> feedbacks; // Vector to hold feedback records


    int choice; // Variable to hold user choice

    while (true) { // Infinite loop for the menu
        cout << "Vehicle Booking and Management System" << endl; // Display system title

        cout << "1. Add Booking" << endl; // Option to add a booking

        cout << "2. Check Availability" << endl; // Option to check vehicle availability

        cout << "3. Update Booking" << endl; // Option to update a booking

        cout << "4. Analyze Bookings" << endl; // Option to analyze bookings

        cout << "5. Calculate Late Return Penalty" << endl; // Option to calculate penalty

        cout << "6. Manage Multiple Bookings" << endl; // Option to manage multiple bookings

        cout << "7. Send Notifications" << endl; // Option to send notifications


        cout << "8. Generate Report" << endl; // Option to generate a report

        cout << "9. Bookings Within Date Range" << endl; // Option to view bookings within a date range

        cout << "10. Add Maintenance Record" << endl; // Option to add a maintenance record

        cout << "11. View Maintenance Records" << endl; // Option to view maintenance records

        cout << "12. Submit Feedback" << endl; // Option to submit feedback

        cout << "13. View Feedback" << endl; // Option to view feedback

        cout << "14. Exit" << endl; // Option to exit the system

        cout << "Enter your choice: "; // Prompt for user choice

        cin >> choice; // Read user choice

        switch (choice)
        { // Switch statement to handle user choice

            case 1:
                {
                    // Case for adding a booking

                string vehicleID; // Variable to hold vehicle ID

                time_t start, end; // Variables to hold start and end times

                cout << "Enter vehicle ID: "; // Prompt for vehicle ID

                cin >> vehicleID; // Read vehicle ID

                cout << "Enter start time (YYYY-MM-DD): "; // Prompt for start time

                string startDateStr; // Variable to hold start date string

                cin >> startDateStr; // Read start date string

                start = convertToDate(startDateStr); // Convert start date string to time_t

                cout << "Enter end time (YYYY-MM-DD): "; // Prompt for end time

                string endDateStr; // Variable to hold end date string

                cin >> endDateStr; // Read end date string

                end = convertToDate(endDateStr); // Convert end date string to time_t

                if (addBooking(vehicleID, start, end, bookings, conflictReports)) { // Attempt to add booking

                    cout << "Booking added successfully." << endl; // Success message
                }
                else
                    {
                    cout << "Booking conflict detected." << endl; // Conflict message
                }

                break; // Break from case
            }

            case 2:
                {
                    // Case for checking availability
                string vehicleID; // Variable to hold vehicle ID

                time_t start, end; // Variables to hold start and end times

                cout << "Enter vehicle ID: "; // Prompt for vehicle ID

                cin >> vehicleID; // Read vehicle ID

                cout << "Enter start time (YYYY-MM-DD): "; // Prompt for start time

                string startDateStr; // Variable to hold start date string

                cin >> startDateStr; // Read start date string

                start = convertToDate(startDateStr); // Convert start date string to time_t

                cout << "Enter end time (YYYY-MM-DD): "; // Prompt for end time

                string endDateStr; // Variable to hold end date string

                cin >> endDateStr; // Read end date string

                end = convertToDate(endDateStr); // Convert end date string to time_t


                if (checkAvailability(vehicleID, start, end, bookings))
                    { // Check availability

                    cout << "Vehicle is available." << endl; // Availability message
                }
                else
                    {

                    cout << "No availability." << endl; // Unavailability message
                }

                break; // Break from case
            }

            case 3:
                {
                    // Case for updating a booking
                string vehicleID; // Variable to hold vehicle ID

                time_t oldStart, newStart, newEnd; // Variables for old and new booking times

                cout << "Enter vehicle ID: "; // Prompt for vehicle ID

                cin >> vehicleID; // Read vehicle ID

                cout << "Enter old start time (YYYY-MM-DD): "; // Prompt for old start time

                string oldStartDateStr; // Variable to hold old start date string

                cin >> oldStartDateStr; // Read old start date string

                oldStart = convertToDate(oldStartDateStr); // Convert old start date string to time_t

                cout << "Enter new start time (YYYY-MM-DD): "; // Prompt for new start time

                string newStartDateStr; // Variable to hold new start date string

                cin >> newStartDateStr; // Read new start date string

                newStart = convertToDate(newStartDateStr); // Convert new start date string to time_t

                cout << "Enter new end time (YYYY-MM-DD): "; // Prompt for new end time

                string newEndDateStr; // Variable to hold new end date string

                cin >> newEndDateStr; // Read new end date string

                newEnd = convertToDate(newEndDateStr); // Convert new end date string to time_t

                updateBooking(vehicleID, oldStart, newStart, newEnd, bookings); // Update the booking with new times

                cout << "Booking updated successfully." << endl; // Success message

                break; // Break from case
            }

            case 4:
                { // Case for analyzing bookings

                if (bookings.empty())
                    { // Check if there are no bookings

                    cout << "No bookings done." << endl; // Message for no bookings
                }
                else
                    {

                    analyzeBookings(bookings); // Analyze the bookings
                }

                break; // Break from case
            }

            case 5:
                {
                     // Case for calculating late return penalty

                time_t actualReturn, scheduledReturn; // Variables for actual and scheduled return times

                double rate; // Variable for daily rate

                cout << "Enter actual return time (YYYY-MM-DD): "; // Prompt for actual return time

                string actualReturnDateStr; // Variable to hold actual return date string

                cin >> actualReturnDateStr; // Read actual return date string

                actualReturn = convertToDate(actualReturnDateStr); // Convert actual return date string to time_t

                cout << "Enter scheduled return time (YYYY-MM-DD): "; // Prompt for scheduled return time

                string scheduledReturnDateStr; // Variable to hold scheduled return date string

                cin >> scheduledReturnDateStr; // Read scheduled return date string

                scheduledReturn = convertToDate(scheduledReturnDateStr); // Convert scheduled return date string to time_t

                cout << "Enter daily rate: "; // Prompt for daily rate

                cin >> rate; // Read daily rate


                double penalty = calculatePenalty(actualReturn, scheduledReturn, rate); // Calculate penalty

                cout << "Late return penalty: $" << penalty << endl; // Display penalty

                break; // Break from case
            }

            case 6:
                {
                    // Case for managing multiple bookings

                vector<Booking> requests; // Vector to hold multiple booking requests

                string vehicleID; // Variable to hold vehicle ID

                time_t start, end; // Variables to hold start and end times

                int numRequests; // Variable to hold number of requests

                cout << "Enter the number of booking requests: "; // Prompt for number of requests

                cin >> numRequests; // Read number of requests

                for (int i = 0; i < numRequests; ++i)
                    { // Loop through each request

                    cout << "Enter vehicle ID: "; // Prompt for vehicle ID

                    cin >> vehicleID; // Read vehicle ID

                    cout << "Enter start time (YYYY-MM-DD): "; // Prompt for start time

                    string startDateStr; // Variable to hold start date string

                    cin >> startDateStr; // Read start date string

                    start = convertToDate(startDateStr); // Convert start date string to time_t

                    cout << "Enter end time (YYYY-MM-DD): "; // Prompt for end time

                    string endDateStr; // Variable to hold end date string

                    cin >> endDateStr; // Read end date string

                    end = convertToDate(endDateStr); // Convert end date string to time_t

                    requests.push_back({vehicleID, start, end}); // Add request to the vector
                }
                manageMultipleBookings(requests, bookings, conflictReports); // Manage the multiple bookings

                break; // Break from case
            }

            case 7:
                { // Case for sending notifications
                sendNotifications(bookings); // Send notifications for all bookings

                break; // Break from case
            }

            case 8:
                {
                     // Case for generating a report
                generateReport(bookings, conflictReports); // Generate a report of bookings and conflicts

                break; // Break from case
            }

            case 9:
                { // Case for viewing bookings within a date range
                time_t startDate, endDate; // Variables for start and end dates

                cout << "Enter start date (YYYY-MM-DD): "; // Prompt for start date

                string startDateStr; // Variable to hold start date string

                cin >> startDateStr; // Read start date string

                startDate = convertToDate(startDateStr); // Convert start date string to time_t

                cout << "Enter end date (YYYY-MM-DD): "; // Prompt for end date

                string endDateStr; // Variable to hold end date string

                cin >> endDateStr; // Read end date string

                endDate = convertToDate(endDateStr); // Convert end date string to time_t

                bookingsWithinDateRange(bookings, startDate, endDate); // View bookings within the specified date range

                break; // Break from case
            }

            case 10:
                { // Case for adding a maintenance record

                string vehicleID, description; // Variables to hold vehicle ID and maintenance description

                time_t date; // Variable to hold maintenance date

                cout << "Enter vehicle ID: "; // Prompt for vehicle ID

                cin >> vehicleID; // Read vehicle ID

                cout << "Enter maintenance date (YYYY-MM-DD): "; // Prompt for maintenance date

                string dateStr; // Variable to hold date string

                cin >> dateStr; // Read date string

                date = convertToDate(dateStr); // Convert date string to time_t

                cout << "Enter maintenance description: "; // Prompt for maintenance description

                cin.ignore(); // Clear the input buffer

                getline(cin, description); // Read the entire line for description

                addMaintenance(vehicleID, date, description, maintenanceRecords); // Add maintenance record

                cout << "Maintenance record added." << endl; // Success message

                break; // Break from case
            }

            case 11:
                {
                    // Case for viewing maintenance records
                string vehicleID; // Variable to hold vehicle ID

                cout << "Enter vehicle ID: "; // Prompt for vehicle ID

                cin >> vehicleID; // Read vehicle ID

                viewMaintenance(vehicleID, maintenanceRecords); // View maintenance records for the vehicle

                break; // Break from case
            }

            case 12:
                { // Case for submitting feedback

                string vehicleID, comment; // Variables to hold vehicle ID and feedback comment

                int rating; // Variable to hold rating

                cout << "Enter vehicle ID: "; // Prompt for vehicle ID

                cin >> vehicleID; // Read vehicle ID

                cout << "Enter rating (1-5): "; // Prompt for rating

                cin >> rating; // Read rating

                cout << "Enter comment: "; // Prompt for feedback comment

                cin.ignore(); // Clear the input buffer

                getline(cin, comment); // Read the entire line for comment

                submitFeedback(vehicleID, "Anonymous", rating, comment, feedbacks); // Submit feedback

                cout << "Feedback submitted." << endl; // Success message

                break; // Break from case
            }

            case 13:
                {
                     // Case for viewing feedback

                string vehicleID; // Variable to hold vehicle ID

                cout << "Enter vehicle ID: "; // Prompt for vehicle ID

                cin >> vehicleID; // Read vehicle ID

                viewFeedback(vehicleID, feedbacks); // View feedback for the vehicle

                break; // Break from case
            }

            case 14:
                { // Case for exiting the system

                cout << "Exiting the system." << endl; // Exit message

                return 0; // Exit the program
            }

            default: // Default case for invalid choice

                cout << "Invalid choice. Please try again." << endl; // Error message
        }
    }
    return 0; // Return from main function
}

// Function implementations
void addMaintenance(const string& vehicleID, time_t date, const string& description, vector<Maintenance>& maintenanceRecords)
{
    maintenanceRecords.push_back({vehicleID, date, description}); // Add maintenance record to the vector
}

void viewMaintenance(const string& vehicleID, const vector<Maintenance>& maintenanceRecords)
{
    cout << "Maintenance records for vehicle " << vehicleID << ":" << endl; // Display vehicle ID


    bool found = false; // Flag to check if records are found

    for (const Maintenance& record : maintenanceRecords)
        { // Loop through maintenance records

        if (record.vehicleID == vehicleID)
            { // Check if vehicle ID matches
            cout << "Date: " << formatDate(record.date) << " Description: " << record.description << endl; // Display record
            found = true; // Set found flag to true
        }
    }
    if (!found)
        { // If no records found
        cout << "No maintenance records found for vehicle " << vehicleID << "." << endl; // Message for no records
    }
}

void submitFeedback(const string& vehicleID, const string& username, int rating, const string& comment, vector<Feedback>& feedbacks) {
    feedbacks.push_back({vehicleID, username, rating, comment}); // Add feedback to the vector
}

void viewFeedback(const string& vehicleID, const vector<Feedback>& feedbacks)
{
    cout << "Feedback for vehicle " << vehicleID << ":" << endl; // Display vehicle ID
    bool found = false; // Flag to check if feedback is found
    for (const Feedback& feedback : feedbacks)
        { // Loop through feedback records

        if (feedback.vehicleID == vehicleID)
        { // Check if vehicle ID matches

            cout << ":User  " << feedback.username << ", Rating: " << feedback.rating << ", Comment: " << feedback.comment << endl ; // Display feedback details
            found = true; // Set found flag to true
        }
    }

    if (!found)
    {
            // If no feedback found

        cout << "No feedback found for vehicle " << vehicleID << "." << endl; // Message for no feedback
    }
}

bool addBooking(const string& vehicleID, time_t start, time_t end, vector<Booking>& bookings, vector<string>& conflictReports)
{
    if (!checkAvailability(vehicleID, start, end, bookings))
        {
            // Check for booking conflicts
        conflictReports.push_back("Conflict for vehicle " + vehicleID); // Add conflict report

        return false;
        // Booking conflict detected
    }
    bookings.push_back({vehicleID, start, end}); // Add booking to the vector

    return true;
     // Booking added successfully
}

bool checkAvailability(const string& vehicleID, time_t start, time_t end, const vector<Booking>& bookings) {

    for (const Booking& booking : bookings)
        {
            // Loop through existing bookings

        if (booking.vehicleID == vehicleID && // Check if vehicle ID matches
            ((start >= booking.start && start < booking.end) || // Check if start time conflicts
             (end > booking.start && end <= booking.end) || // Check if end time conflicts
             (start <= booking.start && end >= booking.end)))
             {
                 // Check if booking completely overlaps

            return false; // Vehicle is not available
        }
    }

    return true; // Vehicle is available
}

void updateBooking(const string& vehicleID, time_t oldStart, time_t newStart, time_t newEnd, vector<Booking>& bookings)
 {

    for (Booking& booking : bookings)
        { // Loop through bookings
        if (booking.vehicleID == vehicleID && booking.start == oldStart)
         { // Find the booking to update
            booking.start = newStart; // Update start time

            booking.end = newEnd; // Update end time

            break; // Exit loop after updating
        }
    }
}

void analyzeBookings(const vector<Booking>& bookings)
 {

    cout << "Total bookings: " << bookings.size() << endl; // Display total number of bookings
    // Additional analysis can be added here
}

double calculatePenalty(time_t actualReturn, time_t scheduledReturn, double rate)
{
    double penalty = 0.0; // Initialize penalty

    if (actualReturn > scheduledReturn)
        { // Check if return is late

        double daysLate = difftime(actualReturn, scheduledReturn) / (60 * 60 * 24); // Calculate days late
        penalty = daysLate * rate; // Calculate penalty based on daily rate
    }

    return penalty; // Return calculated penalty
}

void manageMultipleBookings(const vector<Booking>& requests, vector<Booking>& bookings, vector<string>& conflictReports)
{
    for (const Booking& request : requests)
        {
            // Loop through each booking request

        if (!addBooking(request.vehicleID, request.start, request.end, bookings, conflictReports))
        {
            // Attempt to add booking

            cout << "Conflict for vehicle " << request.vehicleID << endl; // Display conflict message
        }
    }
}

void sendNotifications(const vector<Booking>& bookings)
{

    for (const Booking& booking : bookings)
        {
            // Loop through bookings

        cout << "Notification: Vehicle " << booking.vehicleID << " is booked from " // Display notification
             << formatDate(booking.start) << " to " << formatDate(booking.end) << endl; // Show booking dates
    }
}

void generateReport(const vector<Booking>& bookings, const vector<string>& conflictReports)
{
    cout << "Booking Report:" << endl;
     // Display report title
    for (const Booking& booking : bookings)
        {
            // Loop through bookings
        cout << "Vehicle ID: " << booking.vehicleID << ", Start: " << formatDate(booking.start) // Display booking details

             << ", End: " << formatDate(booking.end) << endl; // Show end date
    }
    if (bookings.empty())
    {
        // Check if there are no bookings

        cout << "No bookings done." << endl; // Message for no bookings
    }
    if (conflictReports.empty())
    {
         // Check if there are no conflict reports

        cout << "No conflict reports." << endl; // Message for no conflicts
    }
    else
        {
        cout << "Conflict Reports:" << endl; // Display conflict report title

        for (const string& report : conflictReports)
        {
             // Loop through conflict reports

            cout << report << endl; // Display each conflict report
        }
    }
}

void bookingsWithinDateRange(const vector<Booking>& bookings, time_t startDate, time_t endDate)
{
    cout << "Bookings within the specified date range:" << endl; // Display title for bookings within date range

    bool found = false; // Flag to check if any bookings are found

    for (const Booking& booking : bookings)
        {
            // Loop through all bookings

        if ((booking.start >= startDate && booking.start <= endDate) || // Check if booking starts within the range
            (booking.end >= startDate && booking.end <= endDate))
            {
                // Check if booking ends within the range
            cout << "Vehicle ID: " << booking.vehicleID << ", Start: " << formatDate(booking.start) // Display booking details
                 << ", End: " << formatDate(booking.end) << endl; // Show end date
            found = true; // Set found flag to true
        }
    }
    if (!found)
    {
        // If no bookings found
        cout << "No bookings done within the specified date range." << endl; // Message for no bookings
    }
}






//ENVIRONMENTAL MODULE
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>  // For iota
#include <limits>   // For numeric_limits
#include <functional> // For lambda functions
#include <queue>    // For Dijkstra's Algorithm
#include <iomanip>  // For formatting output
#include <random>   // For generating random numbers

using namespace std;

const int INF = 1e9;

// Structure to represent a road (edge) with properties
struct Road {
    int from;
    int to;
    int length;
    int cost;
};

// Utility function for input validation
int getValidatedInput(const string& prompt, int minValue = 0) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < minValue) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid non-negative integer.\n";
        } else {
            return value;
        }
    }
}

// Utility function to provide input help
void displayInputHelp() {
    cout << "\n=== Input Help ===\n";
    cout << "1. For intersections: Enter a non-negative integer representing the number of intersections.\n";
    cout << "2. For roads: Enter the details in the format 'from to length cost'.\n";
    cout << "   - 'from' and 'to' are the intersection indices (0-based).\n";
    cout << "   - 'length' is the distance between the intersections.\n";
    cout << "   - 'cost' is the construction cost of the road.\n";
    cout << "3. For source intersection: Enter the index of the starting intersection (0-based).\n";
    cout << "====================\n\n";
}

// Utility function to display roads
void displayRoads(const vector<Road>& roads) {
    cout << "\n================= Roads in the Network =================\n";
    cout << left << setw(10) << "From" << setw(10) << "To" << setw(10) << "Length" << setw(10) << "Cost" << endl;
    for (const auto& road : roads) {
        cout << setw(10) << road.from << setw(10) << road.to << setw(10) << road.length << setw(10) << road.cost << endl;
    }
    cout << "=======================================================\n\n";
}

// Class for City Graph (Bellman-Ford Algorithm)
class CityGraph {
private:
    int intersections;
    vector<Road> roads;

public:
    CityGraph(int intersections) : intersections(intersections) {}

    void addEdge(int from, int to, int length, int cost) {
        roads.push_back({from, to, length, cost});
    }

    void bellmanFord(int source) {
        if (source < 0 || source >= intersections) {
            cout << "Error: Invalid source intersection.\n";
            return;
        }

        vector<int> distance(intersections, INF);
        distance[source] = 0;

        // Relax edges repeatedly
        for (int i = 1; i < intersections; ++i) {
            for (const auto& road : roads) {
                if (distance[road.from] != INF &&
                    distance[road.from] + road.length < distance[road.to]) {
                    distance[road.to] = distance[road.from] + road.length;
                }
            }
        }

        // Check for negative weight cycles
        for (const auto& road : roads) {
            if (distance[road.from] != INF &&
                distance[road.from] + road.length < distance[road.to]) {
                cout << "Error: Negative weight cycle detected.\n";
                return;
            }
        }

        // Print results
        cout << "\n=============== Shortest Distances from Intersection " << source << " ===============\n";
        for (int i = 0; i < intersections; ++i) {
            if (distance[i] == INF) {
                cout << "Intersection " << i << ": Unreachable\n";
            } else {
                cout << "Intersection " << i << ": " << distance[i] << " km\n";
            }
        }
        cout << "===================================================================\n";
    }

    void displayGraphInfo() {
        cout << "\n=============== Graph Information ===============\n";
        cout << "Number of intersections: " << intersections << "\n";
        displayRoads(roads);
        cout << "================================================\n";
    }

    int getIntersections() const {
        return intersections;
    }

    vector<Road> getRoads() const {
        return roads;
    }
};

// Class for City Road Network (Kruskal's Algorithm)
class CityRoadNetwork {
private:
    int intersections;
    vector<Road> roads;

public:
    CityRoadNetwork(int intersections) : intersections(intersections) {}

    void addEdge(int from, int to, int length, int cost) {
        roads.push_back({from, to, length, cost});
    }

    void kruskal() {
        // Sort roads by cost
        sort(roads.begin(), roads.end(), [](Road a, Road b) {
            return a.cost < b.cost;
        });

        // Initialize union-find structure
        vector<int> parent(intersections);
        iota(parent.begin(), parent.end(), 0); // Set parent[i] = i for all i

        function<int(int)> find = [&](int x) {
            if (parent[x] != x) parent[x] = find(parent[x]); // Path compression
            return parent[x];
        };

        auto unionSets = [&](int x, int y) {
            parent[find(x)] = find(y);
        };

        int totalCost = 0;    // Total cost of MST
        vector<Road> mst;     // List of edges in the MST

        for (const auto& road : roads) {
            int rootFrom = find(road.from);
            int rootTo = find(road.to);

            // If not in the same set, add to MST
            if (rootFrom != rootTo) {
                unionSets(rootFrom, rootTo);
                mst.push_back(road);
                totalCost += road.cost;
            }
        }

        // Display the MST
        cout << "\n=============== Minimal Spanning Tree (MST) ===============\n";
        for (const auto& road : mst) {
            cout << "Road between intersection " << road.from
                 << " and intersection " << road.to
                 << " with cost " << road.cost << "\n";
        }
        cout << "Total cost of MST: " << totalCost << "\n";
        cout << "============================================================\n";
    }

    void displayNetworkInfo() {
        cout << "\n=============== Road Network Information ===============\n";
        cout << "Number of intersections: " << intersections << "\n";
        displayRoads(roads);
        cout << "========================================================\n";
    }
};

// Class for City Map (Dijkstra's Algorithm)
class CityMap {
private:
    int intersections;
    vector<vector<pair<int, int>>> adjList; // Pair: <destination, length>

public:
    CityMap(int intersections) : intersections(intersections) {
        adjList.resize(intersections);
    }

    void addEdge(int from, int to, int length) {
        adjList[from].push_back({to, length});
        adjList[to].push_back({from, length}); // Assuming undirected graph
    }

    void dijkstra(int source) {
        if (source < 0 || source >= intersections) {
            cout << "Error: Invalid source intersection.\n";
            return;
        }

        vector<int> distance(intersections, INF);
        distance[source] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, source});

        while (!pq.empty()) {
            int dist = pq.top().first;
            int current = pq.top().second;
            pq.pop();

            if (dist > distance[current]) continue;

            for (const auto& neighbor : adjList[current]) {
                int next = neighbor.first;
                int weight = neighbor.second;

                if (distance[current] + weight < distance[next]) {
                    distance[next] = distance[current] + weight;
                    pq.push({distance[next], next});
                }
            }
        }

        cout << "\n=============== Shortest Distances from Intersection " << source << " ===============\n";
        for (int i = 0; i < intersections; ++i) {
            if (distance[i] == INF) {
                cout << "Intersection " << i << ": Unreachable\n";
            } else {
                cout << "Intersection " << i << ": " << distance[i] << " km\n";
            }
        }
        cout << "===================================================================\n";
    }
};

// Function to generate a random graph
CityGraph generateRandomGraph(int intersections, int roadsCount) {
    CityGraph cityGraph(intersections);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> disLength(1, 100); // Random length between 1 and 100
    uniform_int_distribution<> disCost(1, 50);   // Random cost between 1 and 50
    uniform_int_distribution<> disRoads(0, intersections - 1);

    for (int i = 0; i < roadsCount; ++i) {
        int from = disRoads(gen);
        int to = disRoads(gen);
        while (to == from) to = disRoads(gen); // Ensure "from" and "to" are different
        int length = disLength(gen);
        int cost = disCost(gen);
        cityGraph.addEdge(from, to, length, cost);
    }

    return cityGraph;
}

// Main Menu Functions
void handleBellmanFord(CityGraph& cityGraph) {
    int source = getValidatedInput("Enter source intersection (0-based index): ");
    cityGraph.bellmanFord(source);
}

void handleKruskal(CityRoadNetwork& cityRoadNetwork) {
    cityRoadNetwork.kruskal();
}

void handleDijkstra(CityMap& cityMap) {
    int source = getValidatedInput("Enter source intersection (0-based index): ");
    cityMap.dijkstra(source);
}
  // KMP Algorithm: Compute the prefix table (also called LPS - Longest Prefix Suffix)
vector<int> computePrefixTable(const string& pattern) {
    int m = pattern.size();         // Length of the pattern
    vector<int> prefix(m, 0);       // Initialize prefix table
    int j = 0;                      // Length of the previous longest prefix suffix

    // Build the prefix table (LPS array)
    for (int i = 1; i < m; i++) {
        // Mismatch after j matches, use the prefix table to find the next possible position
        while (j > 0 && pattern[i] != pattern[j]) {
            j = prefix[j - 1];    // Fall back in the pattern using the prefix table
        }

        // If pattern[i] matches pattern[j], we increase the length of the current prefix suffix
        if (pattern[i] == pattern[j]) {
            j++;
        }

        prefix[i] = j;  // Store the length of the current longest prefix suffix
    }

    return prefix;
}

// KMP Algorithm: Pattern Search
void kmpSearch(const string& text, const string& pattern) {
    int n = text.size();  // Length of the text
    int m = pattern.size();  // Length of the pattern

    if (m == 0) {
        cout << "Pattern is empty.\n";
        return;
    }

    if (n == 0) {
        cout << "Text is empty.\n";
        return;
    }

    // Compute the prefix table (LPS array) for the pattern
    vector<int> prefix = computePrefixTable(pattern);

    int j = 0;  // Index for the pattern

    cout << "\nPattern Matching Results:\n";
    // Traverse the text
    for (int i = 0; i < n; i++) {
        // Mismatch after j matches, use the prefix table to skip unnecessary comparisons
        while (j > 0 && text[i] != pattern[j]) {
            j = prefix[j - 1];  // Fall back using the prefix table
        }

        // If the characters match, increase the match length
        if (text[i] == pattern[j]) {
            j++;
        }

        // If the full pattern is found
        if (j == m) {
            cout << "Pattern found at index " << i - m + 1 << endl;
            j = prefix[j - 1];  // Continue searching for next possible match
        }
    }
}

// Environmental Data Pattern Detection Handler
void handlePatternDetection() {
    string data, pattern;

    // Get user input for the environmental data (e.g., temperature readings as a string)
    cout << "Enter environmental data (e.g., temperature readings as a string): ";
    cin.ignore();  // Clear the input buffer
    getline(cin, data);

    // Get the pattern to search for in the environmental data
    cout << "Enter the pattern to search for: ";
    getline(cin, pattern);

    // Call the KMP search function to find the pattern in the given data
    kmpSearch(data, pattern);
}

// Main Function
int module5() {
    CityGraph cityGraph(0);  // Placeholder, will be reinitialized later
    while (true) {
        cout << "\n=============== City Road Network Management ===============\n";
        cout << "1. Bellman-Ford Algorithm (Shortest Paths)\n";
        cout << "2. Kruskal's Algorithm (Minimal Spanning Tree)\n";
        cout << "3. Dijkstra's Algorithm (Shortest Paths)\n";
        cout << "4. Generate Random Graph and Use It\n";
        cout << "5. Display Input Help\n";
        cout << "6. Exit\n";
        cout << "==========================================================\n";
        int choice = getValidatedInput("Enter your choice: ", 1);

        switch (choice) {
            case 1:
                handleBellmanFord(cityGraph);
                break;
            case 2:
                {
                    int intersections = getValidatedInput("Enter number of intersections: ");
                    CityRoadNetwork cityRoadNetwork(intersections);
                    int numRoads = getValidatedInput("Enter number of roads: ");
                    for (int i = 0; i < numRoads; ++i) {
                        int from, to, length, cost;
                        cout << "Road " << i + 1 << ": ";
                        cin >> from >> to >> length >> cost;
                        cityRoadNetwork.addEdge(from, to, length, cost);
                    }
                    handleKruskal(cityRoadNetwork);
                }
                break;
            case 3:
                {
                    int intersections = getValidatedInput("Enter number of intersections: ");
                    CityMap cityMap(intersections);
                    int numRoads = getValidatedInput("Enter number of roads: ");
                    for (int i = 0; i < numRoads; ++i) {
                        int from, to, length;
                        cout << "Road " << i + 1 << ": ";
                        cin >> from >> to >> length;
                        cityMap.addEdge(from, to, length);
                    }
                    handleDijkstra(cityMap);
                }
                break;
            case 4:
                {
                    cout << "\n=== Generate Random Graph Sub-Menu ===\n";
                    cout << "1. Generate Random Graph\n";
                    cout << "2. Manually Add Roads\n";
                    cout << "3. Back to Main Menu\n";
                    int subChoice = getValidatedInput("Enter your choice: ", 1);

                    switch (subChoice) {
                        case 1:
                            {
                                int intersections = getValidatedInput("Enter number of intersections: ");
                                int roadsCount = getValidatedInput("Enter number of roads: ");
                                cityGraph = generateRandomGraph(intersections, roadsCount);
                                cityGraph.displayGraphInfo();
                                break;
                            }
                        case 2:
                            {
                                int intersections = getValidatedInput("Enter number of intersections: ");
                                cityGraph = CityGraph(intersections);
                                int numRoads = getValidatedInput("Enter number of roads: ");
                                for (int i = 0; i < numRoads; ++i) {
                                    int from, to, length, cost;
                                    cout << "Road " << i + 1 << ": ";
                                    cin >> from >> to >> length >> cost;
                                    cityGraph.addEdge(from, to, length, cost);
                                }
                                cityGraph.displayGraphInfo();
                                break;
                            }
                        case 3:
                            continue;  // Return to the main menu
                        default:
                            cout << "Invalid choice. Returning to the main menu.\n";
                            continue;
                    }

                    // After generating or adding roads, let the user use the graph for algorithms
                    char useAgain;
                    do {
                        cout << "\n=== Use Graph for Algorithm ===\n";
                        cout << "1. Bellman-Ford Algorithm (Shortest Paths)\n";
                        cout << "2. Kruskal's Algorithm (Minimal Spanning Tree)\n";
                        cout << "3. Dijkstra's Algorithm (Shortest Paths)\n";
                        cout << "4. Back to Main Menu\n";
                        int algorithmChoice = getValidatedInput("Enter your choice: ", 1);

                        switch (algorithmChoice) {
                            case 1:
                                {
                                    int source = getValidatedInput("Enter source intersection (0-based index): ");
                                    cityGraph.bellmanFord(source);
                                }
                                break;
                            case 2:
                                {
                                    CityRoadNetwork cityRoadNetwork(cityGraph.getIntersections());
                                    for (const auto& road : cityGraph.getRoads()) {
                                        cityRoadNetwork.addEdge(road.from, road.to, road.length, road.cost);
                                    }
                                    handleKruskal(cityRoadNetwork);
                                }
                                break;
                            case 3:
                                {
                                    CityMap cityMap(cityGraph.getIntersections());
                                    for (const auto& road : cityGraph.getRoads()) {
                                        cityMap.addEdge(road.from, road.to, road.length);
                                    }
                                    handleDijkstra(cityMap);
                                }
                                break;
                            case 4:
                                continue;  // Return to the main menu
                            default:
                                cout << "Invalid choice. Returning to the main menu.\n";
                                continue;
                        }

                        // Ask if they want to use the graph again
                        cout << "Do you want to use the same graph for another algorithm? (y/n): ";
                        cin >> useAgain;
                    } while (useAgain == 'y' || useAgain == 'Y');
                }
                break;
            case 5:
                displayInputHelp();
                break;
            case 6:
                cout << "Exiting the program. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please select a valid option.\n";
                break;
        }
    }
}





//ACCESSIBILITY MODULE
#include <iostream>
#include <queue>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

//const double INF = 1e9;
const int MAX_NODES = 100;

// Graph Representation
int graphTo[MAX_NODES][MAX_NODES];
double graphWeight[MAX_NODES][MAX_NODES];
bool graphAccessible[MAX_NODES][MAX_NODES];

// Requests and Assistants
int requestId[MAX_NODES];
string requestLocation[MAX_NODES];
string requestType[MAX_NODES];
int requestUrgency[MAX_NODES];

int assistantId[MAX_NODES];
string assistantType[MAX_NODES];
bool assistantAvailable[MAX_NODES];

// Function to add an edge to the graph
void addEdge(int from, int to, double weight, bool isAccessible) {
    graphTo[from][to] = to;
    graphWeight[from][to] = weight;
    graphAccessible[from][to] = isAccessible;
}

// Function to update the weight of an edge
void updateEdgeWeight(int from, int to, double newWeight) {
    graphWeight[from][to] = newWeight;
}

// Function to remove an edge from the graph
void removeEdge(int from, int to) {
    graphTo[from][to] = -1;
    graphWeight[from][to] = INF;
    graphAccessible[from][to] = false;
}

// Function to get edge details
void getEdgeDetails(int from, int to, double &weight, bool &isAccessible) {
    weight = graphWeight[from][to];
    isAccessible = graphAccessible[from][to];
}

// Function to print the graph
void printGraph(int numNodes) {
    for (int i = 0; i < numNodes; ++i) {
        cout << "Node " << i << " has edges to:\n";
        for (int j = 0; j < numNodes; ++j) {
            if (graphTo[i][j] != -1) {
                cout << "  Node " << graphTo[i][j] << " with weight " << graphWeight[i][j]
                     << " and accessibility " << (graphAccessible[i][j] ? "true" : "false") << "\n";
            }
        }
    }
}

// Function for Barrier-Free Path Calculation using Dijkstra's Algorithm
void dijkstra(int numNodes, int start, int end, double *distances, int *previous) {
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    fill(distances, distances + numNodes, INF);
    fill(previous, previous + numNodes, -1);

    distances[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int current = pq.top().second;
        pq.pop();

        if (current == end) break;

        for (int i = 0; i < numNodes; ++i) {
            if (graphAccessible[current][i] && graphWeight[current][i] < INF) {
                double newDist = distances[current] + graphWeight[current][i];
                if (newDist < distances[i]) {
                    distances[i] = newDist;
                    previous[i] = current;
                    pq.push({newDist, i});
                }
            }
        }
    }
}

// Function to print the shortest path
void printPath(int end, int *previous) {
    if (previous[end] == -1) {
        cout << "No path found." << endl;
        return;
    }
    int path[MAX_NODES];
    int count = 0;
    for (int at = end; at != -1; at = previous[at]) {
        path[count++] = at;
    }
    for (int i = count - 1; i >= 0; --i) {
        cout << path[i] << " ";
    }
    cout << endl;
}

// Function to read graph input from the user
void readGraphInput(int &numNodes, int &numEdges) {
    cout << "Enter the number of nodes: ";
    cin >> numNodes;

    cout << "Enter the number of edges: ";
    cin >> numEdges;

    for (int i = 0; i < numNodes; ++i) {
        for (int j = 0; j < numNodes; ++j) {
            graphTo[i][j] = -1;
            graphWeight[i][j] = INF;
            graphAccessible[i][j] = false;
        }
    }

    for (int i = 0; i < numEdges; ++i) {
        int from, to;
        double weight;
        bool isAccessible;
        cout << "Enter edge (from to weight isAccessible): ";
        cin >> from >> to >> weight >> isAccessible;
        addEdge(from, to, weight, isAccessible);
    }
}

// Function to read requests input from the user
void readRequestsInput(int &numRequests) {
    cout << "Enter the number of requests: ";
    cin >> numRequests;

    for (int i = 0; i < numRequests; ++i) {
        int id, urgency;
        string location, type;
        cout << "Enter request (id location type urgency): ";
        cin >> id >> location >> type >> urgency;
        requestId[i] = id;
        requestLocation[i] = location;
        requestType[i] = type;
        requestUrgency[i] = urgency;
    }
}

// Function to read assistants input from the user
void readAssistantsInput(int &numAssistants) {
    cout << "Enter the number of assistants: ";
    cin >> numAssistants;

    for (int i = 0; i < numAssistants; ++i) {
        int id;
        string type;
        bool available;
        cout << "Enter assistant (id type available): ";
        cin >> id >> type >> available;
        assistantId[i] = id;
        assistantType[i] = type;
        assistantAvailable[i] = available;
    }
}

// Function to allocate assistants using a greedy algorithm
void allocateAssistants(int numRequests, int numAssistants, pair<int, int> *allocations, int &numAllocations) {
    priority_queue<pair<int, int>> pq;
    for (int i = 0; i < numRequests; ++i) {
        pq.push({requestUrgency[i], i});
    }

    numAllocations = 0;
    while (!pq.empty()) {
        int reqIndex = pq.top().second;
        pq.pop();

        for (int i = 0; i < numAssistants; ++i) {
            if (assistantAvailable[i] && assistantType[i] == requestType[reqIndex]) {
                allocations[numAllocations++] = {requestId[reqIndex], assistantId[i]};
                assistantAvailable[i] = false;
                break;
            }
        }
    }
}

// Function to print allocations and assistants' status
void printAllocationsAndStatus(int numAllocations, pair<int, int> *allocations, int numAssistants) {
    cout << "Allocations (RequestID, AssistantID):" << endl;
    for (int i = 0; i < numAllocations; ++i) {
        cout << "(" << allocations[i].first << ", " << allocations[i].second << ")" << endl;
    }

    cout << "Updated status of assistants:" << endl;
    for (int i = 0; i < numAssistants; ++i) {
        cout << "Assistant " << assistantId[i] << " (Type: " << assistantType[i] << ") - "
             << (assistantAvailable[i] ? "Available" : "In Use") << endl;
    }
}

int module6() {
    // Variables to store user inputs
    int numNodes, numEdges, numRequests, numAssistants, numAllocations;
    pair<int, int> allocations[MAX_NODES];

    // Read user inputs
    readGraphInput(numNodes, numEdges);
    readRequestsInput(numRequests);
    readAssistantsInput(numAssistants);

    // Example usage for Barrier-Free Path Calculation
    int start, end;
    cout << "Enter the start and end nodes for the path calculation: ";
    cin >> start >> end;

    double distances[MAX_NODES];
    int previous[MAX_NODES];
    dijkstra(numNodes, start, end, distances, previous);

    cout << "Shortest barrier-free path: ";
    printPath(end, previous);

    cout << "Total travel distance: " << distances[end] << endl;

    // Example usage for Assistance Resource Allocation
    allocateAssistants(numRequests, numAssistants, allocations, numAllocations);
    printAllocationsAndStatus(numAllocations, allocations, numAssistants);

    return 0;
}




//EV SUPPORT MODULE
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <queue>
#include <cmath>
#include <iomanip>

// Function to calculate fitness of an individual
int calculateFitness(std::vector<int> chromosome, const std::vector<std::vector<int>>& nodes, int budget) {
    int totalDemand = 0, totalCost = 0, numStationsSelected = 0;

    for (size_t i = 0; i < nodes.size(); ++i) {
        if (chromosome[i]) {
            totalDemand += nodes[i][0];
            totalCost += nodes[i][1];
            numStationsSelected++;
        }
    }

    if (totalCost > budget || numStationsSelected < 2) {
        return 0;
    }

    double costEfficiency = (totalCost > 0) ? (double)totalDemand / totalCost : 0;
    int demandReward = totalDemand;
    int efficiencyReward = static_cast<int>(costEfficiency * 100);

    return demandReward + efficiencyReward;
}

// Function to generate a random individual
std::vector<int> generateIndividual(int numNodes) {
    std::vector<int> chromosome(numNodes);
    for (int i = 0; i < numNodes; ++i) {
        chromosome[i] = rand() % 2;
    }
    return chromosome;
}

// Function to perform crossover between two individuals
std::vector<int> crossover(std::vector<int> parent1, std::vector<int> parent2) {
    size_t numNodes = parent1.size();
    std::vector<int> offspring(numNodes);
    int crossoverPoint = rand() % numNodes;
    for (size_t i = 0; i < numNodes; ++i) {
        offspring[i] = (i < crossoverPoint) ? parent1[i] : parent2[i];
    }
    return offspring;
}

// Function to mutate an individual
void mutate(std::vector<int>& chromosome, double mutationRate) {
    for (size_t i = 0; i < chromosome.size(); ++i) {
        if ((rand() % 100) < (mutationRate * 100)) {
            chromosome[i] = !chromosome[i];
        }
    }
}

// Function to evaluate and display the best individual
void displayBestIndividual(const std::vector<int>& bestIndividual, const std::vector<std::vector<int>>& nodes, int budget) {
    int fitness = calculateFitness(bestIndividual, nodes, budget);
    std::cout << "\n========================================\n";
    std::cout << "          BEST INDIVIDUAL         \n";
    std::cout << "========================================\n";
    std::cout << "Best Individual Fitness: " << fitness << "\nSelected Nodes: ";
    for (size_t i = 0; i < bestIndividual.size(); ++i) {
        if (bestIndividual[i]) {
            std::cout << i + 1 << " ";
        }
    }
    std::cout << "\n========================================\n";
}

// Genetic Algorithm for charging station placement
std::vector<int> geneticAlgorithm(const std::vector<std::vector<int>>& nodes, int budget, int populationSize, int generations, double mutationRate) {
    std::vector<std::vector<int>> population;

    for (int i = 0; i < populationSize; ++i) {
        population.push_back(generateIndividual(nodes.size()));
    }

    for (int generation = 0; generation < generations; ++generation) {
        std::vector<std::pair<int, std::vector<int>>> fitnessPopulation;
        for (auto& individual : population) {
            fitnessPopulation.push_back({calculateFitness(individual, nodes, budget), individual});
        }

        std::sort(fitnessPopulation.rbegin(), fitnessPopulation.rend());
        population.clear();


        for (size_t i = 0; i < fitnessPopulation.size() / 2; ++i) {

            auto parent1 = fitnessPopulation[i].second;


            auto parent2 = fitnessPopulation[(i + 1) % (fitnessPopulation.size() / 2)].second;


            auto offspring = crossover(parent1, parent2);
            mutate(offspring, mutationRate);
            population.push_back(offspring);

        }
    }

    auto bestIndividual = population[0];


    for (auto& individual : population) {

        if (calculateFitness(individual, nodes, budget) > calculateFitness(bestIndividual, nodes, budget)) {
            bestIndividual = individual;
        }
    }

    displayBestIndividual(bestIndividual, nodes, budget);

    return bestIndividual;
}

// Function to manage EVs waiting at charging stations
void manageChargingQueue(std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>>& queue, int availableSlots) {
    int servedEVs = 0;

    std::cout << "\n========================================\n";
    std::cout << "     CHARGING QUEUE STATUS     \n";
    std::cout << "========================================\n";

    while (!queue.empty() && servedEVs < availableSlots) {
        auto currentEV = queue.top();
        queue.pop();

        std::cout << "Serving EV with battery level " << currentEV.first << "% at time " << currentEV.second << "\n";
        servedEVs++;
    }

    if (servedEVs == 0) {
        std::cout << "No EVs served. All slots are occupied or no EVs in queue.\n";
    }

    std::cout << "========================================\n";
}

// Power distribution simulation
void optimizePowerDistribution(const std::vector<std::vector<int>>& nodes) {
    int totalDemand = 0;
    for (const auto& node : nodes) {
        totalDemand += node[0];
    }
    std::cout << "\n========================================\n";
    std::cout << "   POWER DISTRIBUTION STATUS   \n";
    std::cout << "========================================\n";
    std::cout << "Total power demand: " << totalDemand << "\n";

    for (size_t i = 0; i < nodes.size(); ++i) {
        int surplus = nodes[i][0] - nodes[i][1];
        if (surplus >= 0) {
            std::cout << "Station " << i + 1 << " has a power surplus of " << surplus << " units.\n";
        } else {
            std::cout << "Station " << i + 1 << " has a power deficit of " << -surplus << " units.\n";
        }
    }
    std::cout << "========================================\n";
}

// EV traffic analysis
void analyzeEVTraffic(const std::vector<std::pair<int, int>>& evs) {
    int totalBattery = 0, totalArrivalTime = 0;
    int minBattery = 100, maxBattery = 0;

    for (const auto& ev : evs) {
        totalBattery += ev.first;
        totalArrivalTime += ev.second;
        minBattery = std::min(minBattery, ev.first);
        maxBattery = std::max(maxBattery, ev.first);
    }

    int numEVs = evs.size();
    std::cout << "\n========================================\n";
    std::cout << "       EV TRAFFIC ANALYSIS     \n";
    std::cout << "========================================\n";
    std::cout << "Average Battery Level: " << totalBattery / numEVs << "%\n";
    std::cout << "Battery Range: " << minBattery << "%-" << maxBattery << "%\n";
    std::cout << "========================================\n";
}

// Function to simulate route tracking
void trackEVRoute(int startNode, int endNode, int currentBattery) {
    std::cout << "\n========================================\n";
    std::cout << "        EV ROUTE TRACKING      \n";
    std::cout << "========================================\n";
    std::cout << "Tracking EV from Location " << startNode << " to " << endNode << "\n";
    if (currentBattery < 20) {
        std::cout << "Low battery! Consider charging.\n";
    } else {
        std::cout << "Sufficient battery to complete route.\n";
    }
    std::cout << "========================================\n";
}

// Function to display EV fleet status
void displayEVFleetStatus(const std::vector<std::pair<int, int>>& evs) {
    std::cout << "\n========================================\n";
    std::cout << "         EV FLEET STATUS       \n";
    std::cout << "========================================\n";
    int totalBattery = 0;
    for (size_t i = 0; i < evs.size(); ++i) {
        totalBattery += evs[i].first;
        std::cout << "EV " << i + 1 << " - Battery: " << evs[i].first << "%, Arrival Time: " << evs[i].second << "\n";
    }
    double averageBattery = evs.empty() ? 0 : (double)totalBattery / evs.size();
    std::cout << "Average Fleet Battery Level: " << averageBattery << "%\n";

    std::cout << "Fleet Details by Arrival Time:\n";
    for (const auto& ev : evs) {


        std::cout << "Arrival Time " << ev.second << " - EV Battery: " << ev.first << "%\n";
    }
    std::cout << "========================================\n";
}

// Function to evaluate system performance
void evaluateSystemPerformance(const std::vector<std::vector<int>>& nodes, int budget) {
    int totalDemand = 0, totalCost = 0;
    for (const auto& node : nodes) {
        totalDemand += node[0];
        totalCost += node[1];
    }
    std::cout << "\n========================================\n";
    std::cout << "  SYSTEM PERFORMANCE EVALUATION\n";
    std::cout << "========================================\n";
    std::cout << "Total Demand: " << totalDemand << "\n";
    std::cout << "Total Cost: " << totalCost << "\n";
    std::cout << "Budget: " << budget << "\n";
    std::cout << "========================================\n";
}

// Main menu function
void mainMenu() {
    std::cout << "\n========================================\n";
    std::cout << "        EV OPTIMIZATION SYSTEM         \n";
    std::cout << "========================================\n";

    std::cout << "1. Run Genetic Algorithm for Charging Stations\n";

    std::cout << "2. Manage Charging Queue\n";

    std::cout << "3. Optimize Power Distribution\n";

    std::cout << "4. Analyze EV Traffic\n";

    std::cout << "5. Track EV Route\n";

    std::cout << "6. Display EV Fleet Status\n";

    std::cout << "7. Evaluate System Performance\n";

    std::cout << "8. Exit\n";

    std::cout << "========================================\n";
}

int module7() {
    srand(time(0));

    int choice;
    while (true) {
        mainMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int numNodes, budget, populationSize = 20, generations = 100;
                double mutationRate = 0.1;
                std::cout << "Enter the number of locations and budget: ";
                std::cin >> numNodes >> budget;

                std::vector<std::vector<int>> nodes(numNodes, std::vector<int>(2));
                for (int i = 0; i < numNodes; ++i) {
                    std::cout << "Enter demand and cost for location " << i + 1 << ": ";
                    std::cin >> nodes[i][0] >> nodes[i][1];
                }

                geneticAlgorithm(nodes, budget, populationSize, generations, mutationRate);
                break;
            }
            case 2: {
                int numEVs, availableSlots;
                std::cout << "Enter the number of EVs and available slots: ";
                std::cin >> numEVs >> availableSlots;

                std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> queue;
                for (int i = 0; i < numEVs; ++i) {
                    int battery, arrivalTime;



                    std::cout << "Enter battery level and arrival time for EV " << i + 1 << ": ";
                    std::cin >> battery >> arrivalTime;
                    queue.push({battery, arrivalTime});
                }

                manageChargingQueue(queue, availableSlots);
                break;
            }
            case 3: {
                int numNodes;
                std::cout << "Enter the number of charging stations: ";
                std::cin >> numNodes;

                std::vector<std::vector<int>> nodes(numNodes, std::vector<int>(2));
                for (int i = 0; i < numNodes; ++i) {
                    std::cout << "Enter power demand and supply for station " << i + 1 << ": ";
                    std::cin >> nodes[i][0] >> nodes[i][1];
                }

                optimizePowerDistribution(nodes);
                break;
            }
            case 4: {
                int numEVs;
                std::cout << "Enter the number of EVs: ";
                std::cin >> numEVs;

                std::vector<std::pair<int, int>> evs(numEVs);


                for (int i = 0; i < numEVs; ++i) {
                    std::cout << "Enter battery level and arrival time for EV " << i + 1 << ": ";
                    std::cin >> evs[i].first >> evs[i].second;
                }

                analyzeEVTraffic(evs);
                break;
            }
            case 5: {
                int startNode, endNode, batteryLevel;
                std::cout << "Enter start node, end node, and current battery level: ";


                std::cin >> startNode >> endNode >> batteryLevel;

                trackEVRoute(startNode, endNode, batteryLevel);
                break;
            }
            case 6: {
                int numEVs;
                std::cout << "Enter the number of EVs: ";
                std::cin >> numEVs;

                std::vector<std::pair<int, int>> evs(numEVs);
                for (int i = 0; i < numEVs; ++i) {
                    std::cout << "Enter battery level and arrival time for EV " << i + 1 << ": ";
                    std::cin >> evs[i].first >> evs[i].second;
                }

                displayEVFleetStatus(evs);
                break;
            }
            case 7: {
                int numNodes, budget;

                std::cout << "Enter the number of locations and budget: ";

                std::cin >> numNodes >> budget;

                std::vector<std::vector<int>> nodes(numNodes, std::vector<int>(2));

                for (int i = 0; i < numNodes; ++i) {
                    std::cout << "Enter demand and cost for location " << i + 1 << ": ";
                    std::cin >> nodes[i][0] >> nodes[i][1];
                }

                evaluateSystemPerformance(nodes, budget);
                break;
            }
            case 8: {
                std::cout << "Exiting the system. Goodbye!\n";
                return 0;
            }
            default: {
                std::cout << "Invalid choice! Please try again.\n";
                break;
            }
        }
    }

    return 0;
}

//CHARGING STATUS DISPLAY MODULE
#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <tuple>
#include <string>

class IntervalTree {
    struct Interval {
        int start, end;
        Interval(int s, int e) : start(s), end(e) {}
    };

    struct Node {
        Interval interval;
        int maxEnd;
        Node* left;
        Node* right;
        Node(Interval iv) : interval(iv), maxEnd(iv.end), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insert(Node* node, Interval interval) {
        if (!node) return new Node(interval);

        if (interval.start < node->interval.start)
            node->left = insert(node->left, interval);
        else
            node->right = insert(node->right, interval);

        node->maxEnd = std::max(node->maxEnd, interval.end);
        return node;
    }

    bool overlap(Interval i1, Interval i2) {
        return (i1.start < i2.end && i2.start < i1.end);
    }

    bool searchOverlap(Node* node, Interval interval) {
        if (!node) return false;
        if (overlap(node->interval, interval)) return true;

        if (node->left && node->left->maxEnd > interval.start)
            return searchOverlap(node->left, interval);

        return searchOverlap(node->right, interval);
    }

public:
    IntervalTree() : root(nullptr) {}

    void insert(int start, int end) {
        root = insert(root, Interval(start, end));
    }

    bool hasOverlap(int start, int end) {
        return searchOverlap(root, Interval(start, end));
    }
};

class BookingSystem {
    std::map<int, IntervalTree> vehicleBookings;
    std::map<int, std::vector<std::pair<int, int>>> sortedBookings;
    std::map<int, double> vehicleRates;
    std::map<int, double> penalties;
    std::priority_queue<std::tuple<int, int, int>> eventQueue;

    class TrieNode {
    public:
        std::unordered_map<char, TrieNode*> children;
        bool isEndOfVehicle;

        TrieNode() : isEndOfVehicle(false) {}
    };

    class Trie {
        TrieNode* root;

    public:
        Trie() {
            root = new TrieNode();
        }

        void insert(const std::string& vehicle) {
            TrieNode* node = root;
            for (char ch : vehicle) {
                if (node->children.find(ch) == node->children.end()) {
                    node->children[ch] = new TrieNode();
                }
                node = node->children[ch];
            }
            node->isEndOfVehicle = true;
        }

        void search(const std::string& prefix, TrieNode* node, std::string current, std::vector<std::string>& results) {
            if (node->isEndOfVehicle) {
                results.push_back(current);
            }
            for (const auto& [ch, child] : node->children) {
                search(prefix, child, current + ch, results);
            }
        }

        std::vector<std::string> autoComplete(const std::string& prefix) {
            TrieNode* node = root;
            std::vector<std::string> results;
            for (char ch : prefix) {
                if (node->children.find(ch) == node->children.end()) {
                    return results;
                }
                node = node->children[ch];
            }
            search(prefix, node, prefix, results);
            return results;
        }
    };

    Trie vehicleTrie;

public:
    bool bookVehicle(int vehicleID, int start, int end) {
        if (vehicleBookings[vehicleID].hasOverlap(start, end)) {
            std::cout << "Booking conflict for vehicle " << vehicleID << " from " << start << " to " << end << std::endl;
            return false;
        }
        vehicleBookings[vehicleID].insert(start, end);
        sortedBookings[vehicleID].emplace_back(start, end);
        std::sort(sortedBookings[vehicleID].begin(), sortedBookings[vehicleID].end());
        eventQueue.emplace(start, vehicleID, 1);
        eventQueue.emplace(end, vehicleID, -1);
        std::cout << "Booking confirmed for vehicle " << vehicleID << " from " << start << " to " << end << std::endl;
        return true;
    }

    bool checkAvailability(int vehicleID, int start, int end) {
        if (sortedBookings.find(vehicleID) == sortedBookings.end()) {
            std::cout << "Vehicle " << vehicleID << " is available from " << start << " to " << end << std::endl;
            return true;
        }

        auto& bookings = sortedBookings[vehicleID];
        for (const auto& booking : bookings) {
            if (std::max(booking.first, start) < std::min(booking.second, end)) {
                std::cout << "Vehicle " << vehicleID << " is unavailable from " << start << " to " << end << std::endl;
                return false;
            }
        }
        std::cout << "Vehicle " << vehicleID << " is available from " << start << " to " << end << std::endl;
        return true;
    }

    void updateBookings() {
        while (!eventQueue.empty()) {
            auto [time, vehicleID, type] = eventQueue.top();
            eventQueue.pop();
            if (type == 1) {
                std::cout << "Booking started for vehicle " << vehicleID << " at time " << time << std::endl;
            } else {
                std::cout << "Booking ended for vehicle " << vehicleID << " at time " << time << std::endl;
            }
        }
    }

    void addVehicleRate(int vehicleID, double rate) {
        vehicleRates[vehicleID] = rate;
    }

    double calculatePenalty(int vehicleID, int scheduledReturn, int actualReturn) {
        double rate = vehicleRates[vehicleID];
        int lateHours = actualReturn - scheduledReturn;
        double penalty = lateHours * rate;
        penalties[vehicleID] += penalty;
        return penalty;
    }

    void analyzeBookings(const std::map<int, int>& bookingCounts) {
        std::cout << "Most frequently booked vehicles:" << std::endl;
        for (const auto& [vehicleID, count] : bookingCounts) {
            std::cout << "Vehicle ID: " << vehicleID << ", Bookings: " << count << std::endl;
        }
    }

    void addVehicleToTrie(const std::string& vehicleName) {
        vehicleTrie.insert(vehicleName);
    }

    std::vector<std::string> getAutoCompleteSuggestions(const std::string& prefix) {
        return vehicleTrie.autoComplete(prefix);
    }

    void addVehicle(int vehicleID) {
        eventQueue.emplace(0, 0, vehicleID);
    }

    void assignBookings(std::vector<std::tuple<int, int, int>>& requests) {
        for (auto& [start, end, vehicleType] : requests) {
            if (!eventQueue.empty()) {
                auto [time, _, vehicleID] = eventQueue.top();
                eventQueue.pop();
                std::cout << "Assigned vehicle " << vehicleID << " for booking from " << start << " to " << end << std::endl;
                eventQueue.emplace(end, end, vehicleID);
            } else {
                std::cout << "No available vehicle for booking from " << start << " to " << end << std::endl;
            }
        }
    }

    void sendReminders() {
        while (!eventQueue.empty()) {
            auto [time, vehicleID, type] = eventQueue.top();
            eventQueue.pop();
            if (type == 1) {
                std::cout << "Reminder: Vehicle " << vehicleID << " booking ending soon." << std::endl;
            }
        }
    }

    bool cancelBooking(int vehicleID, int start, int end) {
        auto& bookings = sortedBookings[vehicleID];
        auto it = std::find(bookings.begin(), bookings.end(), std::make_pair(start, end));
        if (it != bookings.end()) {
            bookings.erase(it);
            std::cout << "Booking for vehicle " << vehicleID << " from " << start << " to " << end << " cancelled." << std::endl;
            return true;
        } else {
            std::cout << "No such booking found for vehicle " << vehicleID << " from " << start << " to " << end << std::endl;
            return false;
        }
    }

    bool extendBooking(int vehicleID, int oldEnd, int newEnd) {
        auto& bookings = sortedBookings[vehicleID];
        for (auto& booking : bookings) {
            if (booking.second == oldEnd) {
                if (checkAvailability(vehicleID, oldEnd, newEnd)) {
                    booking.second = newEnd;
                    std::cout << "Booking for vehicle " << vehicleID << " extended to " << newEnd << std::endl;
                    return true;
                } else {
                    std::cout << "Cannot extend booking due to a conflict." << std::endl;
                    return false;
                }
            }
        }
        std::cout << "No such booking found for vehicle " << vehicleID << " ending at " << oldEnd << std::endl;
        return false;
    }

    void viewAllBookings(int vehicleID) {
        auto& bookings = sortedBookings[vehicleID];
        if (bookings.empty()) {
            std::cout << "No bookings found for vehicle " << vehicleID << std::endl;
            return;
        }
        std::cout << "Bookings for vehicle " << vehicleID << ":" << std::endl;
        for (const auto& booking : bookings) {
            std::cout << "From " << booking.first << " to " << booking.second << std::endl;
        }
    }

    double getTotalEarnings(int vehicleID) {
        double totalEarnings = 0.0;
        auto& bookings = sortedBookings[vehicleID];
        for (const auto& booking : bookings) {
            int duration = booking.second - booking.first;
            totalEarnings += duration * vehicleRates[vehicleID];
        }
        return totalEarnings;
    }

    void viewBookingDetails(int vehicleID, int start, int end) {
        auto& bookings = sortedBookings[vehicleID];
        auto it = std::find(bookings.begin(), bookings.end(), std::make_pair(start, end));
        if (it != bookings.end()) {
            std::cout << "Booking found for vehicle " << vehicleID << " from " << start << " to " << end << std::endl;
        } else {
            std::cout << "No such booking found for vehicle " << vehicleID << " from " << start << " to " << end << std::endl;
        }
    }
};

int module8() {
    BookingSystem bs;
    int command;

    while (true) {
        std::cout << "Enter command:" << std::endl;
        std::cout << "1: Book Vehicle\n2: Check Availability\n3: Cancel Booking\n4: Extend Booking\n5: Add Vehicle Rate\n6: Calculate Penalty\n7: Historical Analysis\n8: Auto-complete\n9: Assign Bookings\n10: Send Reminders\n11: View All Bookings\n12: Get Total Earnings\n13: View Booking Details\n14: Exit" << std::endl;
        std::cin >> command;

        switch (command) {
            case 1: {
                int vehicleID, start, end;
                std::cout << "Enter Vehicle ID, Start Time, End Time: ";
                std::cin >> vehicleID >> start >> end;
                bs.bookVehicle(vehicleID, start, end);
                break;
            }
            case 2: {
                int vehicleID, start, end;
                std::cout << "Enter Vehicle ID, Start Time, End Time: ";
                std::cin >> vehicleID >> start >> end;
                bs.checkAvailability(vehicleID, start, end);
                break;
            }
            case 3: {
                int vehicleID, start, end;
                std::cout << "Enter Vehicle ID, Start Time, End Time: ";
                std::cin >> vehicleID >> start >> end;
                bs.cancelBooking(vehicleID, start, end);
                break;
            }
            case 4: {
                int vehicleID, oldEnd, newEnd;
                std::cout << "Enter Vehicle ID, Old End Time, New End Time: ";
                std::cin >> vehicleID >> oldEnd >> newEnd;
                bs.extendBooking(vehicleID, oldEnd, newEnd);
                break;
            }
            case 5: {
                int vehicleID;
                double rate;
                std::cout << "Enter Vehicle ID, Rate: ";
                std::cin >> vehicleID >> rate;
                bs.addVehicleRate(vehicleID, rate);
                break;
            }
            case 6: {
                int vehicleID, scheduledReturn, actualReturn;
                std::cout << "Enter Vehicle ID, Scheduled Return Time, Actual Return Time: ";
                std::cin >> vehicleID >> scheduledReturn >> actualReturn;
                double penalty = bs.calculatePenalty(vehicleID, scheduledReturn, actualReturn);
                std::cout << "Penalty: $" << penalty << std::endl;
                break;
            }
            case 7: {
                std::map<int, int> bookingCounts;
                int vehicleID, count;
                std::cout << "Enter Vehicle ID and Booking Count (enter -1 to stop): ";
                while (std::cin >> vehicleID && vehicleID != -1) {
                    std::cin >> count;
                    bookingCounts[vehicleID] = count;
                }
                bs.analyzeBookings(bookingCounts);
                break;
            }
            case 8: {
                std::string prefix;
                std::cout << "Enter prefix for auto-complete: ";
                std::cin >> prefix;
                std::vector<std::string> results = bs.getAutoCompleteSuggestions(prefix);
                for (const std::string& result : results) {
                    std::cout << result << std::endl;
                }
                break;
            }
            case 9: {
                std::vector<std::tuple<int, int, int>> requests;
                int start, end, vehicleType;
                std::cout << "Enter Start Time, End Time, Vehicle Type (enter -1 to stop): ";
                while (std::cin >> start && start != -1) {
                    std::cin >> end >> vehicleType;
                    requests.emplace_back(start, end, vehicleType);
                }
                bs.assignBookings(requests);
                break;
            }
            case 10: {
                bs.sendReminders();
                break;
            }
            case 11: {
                int vehicleID;
                std::cout << "Enter Vehicle ID: ";
                std::cin >> vehicleID;
                bs.viewAllBookings(vehicleID);
                break;
            }
            case 12: {
                int vehicleID;
                std::cout << "Enter Vehicle ID: ";
                std::cin >> vehicleID;
                double earnings = bs.getTotalEarnings(vehicleID);
                std::cout << "Total earnings for vehicle " << vehicleID << ": $" << earnings << std::endl;
                break;
            }
            case 13: {
                int vehicleID, start, end;
                std::cout << "Enter Vehicle ID, Start Time, End Time: ";
                std::cin >> vehicleID >> start >> end;
                bs.viewBookingDetails(vehicleID, start, end);
                break;
            }
            case 14:
                return 0;
            default:
                std::cout << "Invalid command!" << std::endl;
        }
    }

    return 0;
}





//CHARGING COST CALCULATION MODULE
#include <iostream>
#include <string> // For string
using namespace std;

// Function for Basic Charging Cost Calculation
void basicChargingCost()
 {
    double rate, duration;
    cout << "\n--- Basic Charging Cost Calculation ---\n";
    cout << "This module calculates the cost of a single charging session based on the rate per hour and duration.\n";

    cout << "Enter charging rate per hour: ";
    cin >> rate;
    cout << "You entered a rate of: " << rate << " per hour.\n";

    cout << "Enter duration of charging session (in hours): ";
    cin >> duration;
    cout << "You entered a duration of: " << duration << " hours.\n";

    double cost = rate * duration;
    cout << "Performing calculation: Cost = Rate (" << rate << ") * Duration (" << duration << ")\n";
    cout << "Estimated charging cost: $" << cost << "\n\n";
}

// Function for Cost Breakdown by Time of Day
void costBreakdownByTime()
{
    double peakRate, offPeakRate, duration;
    int startTime;

    cout << "\n--- Cost Breakdown by Time of Day ---\n";
    cout << "This module calculates the charging cost by considering peak and off-peak rates based on the session's timing.\n";

    cout << "Enter peak rate per hour: ";
    cin >> peakRate;
    cout << "You entered a peak rate of: " << peakRate << " per hour.\n";

    cout << "Enter off-peak rate per hour: ";
    cin >> offPeakRate;
    cout << "You entered an off-peak rate of: " << offPeakRate << " per hour.\n";

    cout << "Enter start time of charging session (24-hour format, e.g., 13 for 1 PM): ";
    cin >> startTime;
    cout << "You entered a start time of: " << startTime << ":00.\n";

    cout << "Enter duration of charging session (in hours): ";
    cin >> duration;
    cout << "You entered a duration of: " << duration << " hours.\n";

    double cost = 0.0;
    cout << "Calculating cost for each hour of the session...\n";
    for (int i = 0; i < duration; ++i)
        {
        int currentTime = (startTime + i) % 24;
        cout << "Hour " << (i + 1) << " (Time: " << (currentTime < 10 ? "0" : "") << currentTime << ":00) - ";
        if (currentTime >= 8 && currentTime <= 20)
        { // Peak hours (8 AM to 8 PM)
            cout << "Peak rate applied ($" << peakRate << ")\n";
            cost += peakRate;
        } else
         {
            cout << "Off-peak rate applied ($" << offPeakRate << ")\n";
            cost += offPeakRate;
        }
    }
    cout << "Total estimated cost with breakdown: $" << cost << "\n\n";
}

// Function for Total Monthly Charging Cost
void totalMonthlyChargingCost()
{
    int n;
    cout << "\n--- Total Monthly Charging Cost ---\n";
    cout << "This module calculates the total cost of multiple charging sessions over a month.\n";

    cout << "Enter number of charging sessions: ";
    cin >> n;
    cout << "You entered the number of sessions: " << n << ".\n";

    double totalCost = 0.0;
    for (int i = 0; i < n; ++i)
        {
        double sessionCost;
        cout << "Enter cost of session " << (i + 1) << ": ";
        cin >> sessionCost;
        cout << "Session " << (i + 1) << " cost: " << sessionCost << "\n";
        totalCost += sessionCost;
    }
    cout << "Summing up the costs for " << n << " sessions...\n";
    cout << "Total monthly charging cost: $" << totalCost << "\n\n";
}

// Function for Cost Comparison with Different Rates
void costComparisonWithRates()
 {
    int n;
    double duration;
    cout << "\n--- Cost Comparison with Different Rates ---\n";
    cout << "This module compares costs for a charging session with multiple rate options.\n";

    cout << "Enter duration of charging session (in hours): ";
    cin >> duration;
    cout << "You entered a duration of: " << duration << " hours.\n";

    cout << "Enter number of different rates to compare: ";
    cin >> n;
    cout << "You entered " << n << " rates to compare.\n";

    for (int i = 0; i < n; ++i)
        {
        double rate;
        cout << "Enter rate " << (i + 1) << ": ";
        cin >> rate;
        cout << "Rate " << (i + 1) << " entered: " << rate << " per hour.\n";

        double cost = rate * duration;
        cout << "Calculating cost for rate " << rate << "... Cost = " << rate << " * " << duration << "\n";
        cout << "Cost with rate " << rate << ": $" << cost << "\n";
    }
    cout << "All rate comparisons completed.\n\n";
}

// Function for Cost Savings Estimation with Membership Discounts
void costSavingsWithDiscount()
{
    double rate, duration, discount;
    cout << "\n--- Cost Savings Estimation with Membership Discounts ---\n";
    cout << "This module calculates the cost and savings for a charging session with membership discounts applied.\n";

    cout << "Enter charging rate per hour: ";
    cin >> rate;
    cout << "You entered a rate of: " << rate << " per hour.\n";

    cout << "Enter duration of charging session (in hours): ";
    cin >> duration;
    cout << "You entered a duration of: " << duration << " hours.\n";

    cout << "Enter membership discount percentage: ";
    cin >> discount;
    cout << "You entered a discount of: " << discount << "%.\n";

    double originalCost = rate * duration;
    cout << "Calculating original cost: " << rate << " * " << duration << " = " << originalCost << "\n";

    double discountedCost = originalCost * (1 - discount / 100);
    cout << "Calculating discounted cost: " << originalCost << " * (1 - " << discount << "/100) = " << discountedCost << "\n";

    double savings = originalCost - discountedCost;
    cout << "Calculating savings: " << originalCost << " - " << discountedCost << " = " << savings << "\n";

    cout << "Cost with discount: $" << discountedCost << "\n";
    cout << "Savings compared to standard rate: $" << savings << "\n\n";
}

// Function for Charging Cost Estimation with Tax
void chargingCostWithTax()
{
    double rate, duration, taxRate;
    cout << "\n--- Charging Cost Estimation with Tax ---\n";
    cout << "This module calculates the total cost of a charging session with tax included.\n";

    cout << "Enter charging rate per hour: ";
    cin >> rate;
    cout << "You entered a rate of: " << rate << " per hour.\n";

    cout << "Enter duration of charging session (in hours): ";
    cin >> duration;
    cout << "You entered a duration of: " << duration << " hours.\n";

    cout << "Enter tax rate percentage: ";
    cin >> taxRate;
    cout << "You entered a tax rate of: " << taxRate << "%.\n";

    double cost = rate * duration;
    double tax = cost * (taxRate / 100);
    double totalCost = cost + tax;

    cout << "Calculating total cost: Base cost = " << cost << ", Tax = " << tax << ", Total = " << totalCost << "\n";
    cout << "Estimated cost including tax: $" << totalCost << "\n\n";
}

// Function for Charging Cost for Multiple EVs
void chargingCostForMultipleEVs()
 {
    int n;
    cout << "\n--- Charging Cost for Multiple EVs ---\n";
    cout << "This module calculates the total cost of charging multiple EVs with different rates and durations.\n";

    cout << "Enter number of EVs: ";
    cin >> n;
    cout << "You entered " << n << " EVs.\n";

    double totalCost = 0.0;
    for (int i = 0; i < n; ++i)
        {
        double rate, duration;
        cout << "Enter rate per hour for EV " << (i + 1) << ": ";
        cin >> rate;
        cout << "Rate for EV " << (i + 1) << ": " << rate << " per hour.\n";

        cout << "Enter duration for EV " << (i + 1) << " (in hours): ";
        cin >> duration;
        cout << "Duration for EV " << (i + 1) << ": " << duration << " hours.\n";

        double cost = rate * duration;
        cout << "Calculating cost for EV " << (i + 1) << ": " << rate << " * " << duration << " = " << cost << "\n";
        totalCost += cost;
    }
    cout << "Total cost for all EVs: $" << totalCost << "\n\n";
}

// New Function for Charging Cost with Renewable Energy Discount
void chargingCostWithRenewableDiscount()
{
    double rate, duration, renewableDiscount;
    cout << "\n--- Charging Cost with Renewable Energy Discount ---\n";
    cout << "This module calculates the cost for a charging session with a renewable energy discount applied.\n";

    cout << "Enter charging rate per hour: ";
    cin >> rate;
    cout << "You entered a rate of: " << rate << " per hour.\n";

    cout << "Enter duration of charging session (in hours): ";
    cin >> duration;
    cout << "You entered a duration of: " << duration << " hours.\n";

    cout << "Enter renewable energy discount percentage: ";
    cin >> renewableDiscount;
    cout << "You entered a discount of: " << renewableDiscount << "%.\n";

    double originalCost = rate * duration;
    cout << "Calculating original cost: " << rate << " * " << duration << " = " << originalCost << "\n";

    double discountedCost = originalCost * (1 - renewableDiscount / 100);
    cout << "Calculating discounted cost: " << originalCost << " * (1 - " << renewableDiscount << "/100) = " << discountedCost << "\n";

    cout << "Cost with renewable energy discount: $" << discountedCost << "\n\n";
}

// New Function for Charging Cost Prediction for Future Months
void futureChargingCostPrediction()
 {
    double currentMonthlyCost, growthRate;
    int months;
    cout << "\n--- Future Charging Cost Prediction ---\n";
    cout << "This module predicts the future charging costs for upcoming months based on a growth rate.\n";

    cout << "Enter current monthly charging cost: ";
    cin >> currentMonthlyCost;
    cout << "You entered a current monthly cost of: " << currentMonthlyCost << "\n";

    cout << "Enter monthly growth rate percentage: ";
    cin >> growthRate;
    cout << "You entered a growth rate of: " << growthRate << "%\n";

    cout << "Enter number of months for prediction: ";
    cin >> months;
    cout << "You entered a duration of " << months << " months for prediction.\n";

    for (int i = 1; i <= months; ++i)
        {
        currentMonthlyCost *= (1 + growthRate / 100);
        cout << "Predicted cost for month " << i << ": $" << currentMonthlyCost << "\n";
    }
    cout << "Future charging cost prediction completed.\n\n";
}

// New Function for Charging Cost with Seasonal Rates
void chargingCostWithSeasonalRates()
{
    double summerRate, winterRate, duration;
    string season;
    cout << "\n--- Charging Cost with Seasonal Rates ---\n";
    cout << "This module calculates the charging cost based on seasonal rates.\n";

    cout << "Enter summer rate per hour: ";
    cin >> summerRate;
    cout << "You entered a summer rate of: " << summerRate << " per hour.\n";

    cout << "Enter winter rate per hour: ";
    cin >> winterRate;
    cout << "You entered a winter rate of: " << winterRate << " per hour.\n";

    cout << "Enter current season (summer/winter): ";
    cin >> season;
    cout << "You entered the current season as: " << season << ".\n";

    cout << "Enter duration of charging session (in hours): ";
    cin >> duration;
    cout << "You entered a duration of: " << duration << " hours.\n";

    double cost = 0.0;
    if (season == "summer")
        {
        cout << "Applying summer rate...\n";
        cost = summerRate * duration;
    } else if (season == "winter")
    {
        cout << "Applying winter rate...\n";
        cost = winterRate * duration;
    } else {
        cout << "Invalid season entered. Please enter either 'summer' or 'winter'.\n";
        return;
    }
    cout << "Total estimated cost for the session: $" << cost << "\n\n";
}

// New Function for Charging Cost with Holiday Rates
void chargingCostWithHolidayRates()
 {
    double regularRate, holidayRate, duration;
    string isHoliday;
    cout << "\n--- Charging Cost with Holiday Rates ---\n";
    cout << "This module calculates the charging cost based on whether it is a holiday or not.\n";

    cout << "Enter regular rate per hour: ";
    cin >> regularRate;
    cout << "You entered a regular rate of: " << regularRate << " per hour.\n";

    cout << "Enter holiday rate per hour: ";
    cin >> holidayRate;
    cout << "You entered a holiday rate of: " << holidayRate << " per hour.\n";

    cout << "Is it a holiday today? (yes/no): ";
    cin >> isHoliday;
    cout << "You entered: " << isHoliday << ".\n";

    cout << "Enter duration of charging session (in hours): ";
    cin >> duration;
    cout << "You entered a duration of: " << duration << " hours.\n";

    double cost = 0.0;
    if (isHoliday == "yes")
        {
        cout << "Applying holiday rate...\n";
        cost = holidayRate * duration;
    } else if (isHoliday == "no")
    {
        cout << "Applying regular rate...\n";
        cost = regularRate * duration;
    } else
     {
        cout << "Invalid input. Please enter 'yes' or 'no'.\n";
        return;
    }
    cout << "Total estimated cost for the session: $" << cost << "\n\n";
}

// New Function for Charging Cost with Peak Hour Surcharge
void chargingCostWithPeakSurcharge()
 {
    double baseRate, peakRate, duration;
    int startTime;
    cout << "\n--- Charging Cost with Peak Hour Surcharge ---\n";
    cout << "This module calculates the cost of a charging session with an additional surcharge during peak hours.\n";

    cout << "Enter base rate per hour: ";
    cin >> baseRate;
    cout << "You entered a base rate of: " << baseRate << " per hour.\n";

    cout << "Enter peak hour surcharge rate per hour: ";
    cin >> peakRate;
    cout << "You entered a peak hour surcharge rate of: " << peakRate << " per hour.\n";

    cout << "Enter start time of charging session (24-hour format, e.g., 13 for 1 PM): ";
    cin >> startTime;
    cout << "You entered a start time of: " << startTime << ":00.\n";

    cout << "Enter duration of charging session (in hours): ";
    cin >> duration;
    cout << "You entered a duration of: " << duration << " hours.\n";

    double cost = 0.0;
    cout << "Calculating cost for each hour of the session...\n";
    for (int i = 0; i < duration; ++i)
        {
        int currentTime = (startTime + i) % 24;
        cout << "Hour " << (i + 1) << " (Time: " << (currentTime < 10 ? "0" : "") << currentTime << ":00) - ";
        if (currentTime >= 17 && currentTime <= 19)
        { // Peak hours (5 PM to 7 PM)
            cout << "Peak hour surcharge applied ($" << peakRate << ")\n";
            cost += (baseRate + peakRate);
        } else
        {
            cout << "Base rate applied ($" << baseRate << ")\n";
            cost += baseRate;
        }
    }
    cout << "Total estimated cost with peak hour surcharge: $" << cost << "\n\n";
}

// Main Function
int module9()
{
    int choice;
    cout << "Choose an option:\n";
    cout << "1. Basic Charging Cost Calculation\n";
    cout << "2. Cost Breakdown by Time of Day\n";
    cout << "3. Total Monthly Charging Cost\n";
    cout << "4. Cost Comparison with Different Rates\n";
    cout << "5. Cost Savings Estimation with Membership Discounts\n";
    cout << "6. Charging Cost Estimation with Tax\n";
    cout << "7. Charging Cost for Multiple EVs\n";
    cout << "8. Charging Cost with Renewable Energy Discount\n";
    cout << "9. Future Charging Cost Prediction\n";
    cout << "10. Charging Cost with Seasonal Rates\n";
    cout << "11. Charging Cost with Holiday Rates\n";
    cout << "12. Charging Cost with Peak Hour Surcharge\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
        case 1: basicChargingCost(); break;
        case 2: costBreakdownByTime(); break;
        case 3: totalMonthlyChargingCost(); break;
        case 4: costComparisonWithRates(); break;
        case 5: costSavingsWithDiscount(); break;
        case 6: chargingCostWithTax(); break;
        case 7: chargingCostForMultipleEVs(); break;
        case 8: chargingCostWithRenewableDiscount(); break;
        case 9: futureChargingCostPrediction(); break;
        case 10: chargingCostWithSeasonalRates(); break;
        case 11: chargingCostWithHolidayRates(); break;
        case 12: chargingCostWithPeakSurcharge(); break;
        default: cout << "Invalid choice! Please try again.\n"; break;
    }

    return 0;
}






//MAIN FUNCTION
int main()
{
    int choice=0;
    do
    {
    std::cout << "-----POLLUTION-FREE CITY----" << std::endl;

    std::cout << "1. MODULE 1 -- LOGIN/REGISTER " << std::endl;

    std::cout << "2. MODULE 2 -- NAVIGATION MODULE" << std::endl;

    std::cout << "3. MODULE 3 -- RESOURCE DISTRIBUTION MODULE FOR BICYCLE " << std::endl;

    std::cout << "4. MODULE 4 -- RESOURCE DISTRIBUTION MODULE FOR EV " << std::endl;

    std::cout << "5. MODULE 5 -- ENVIRONMENTAL MODULE " << std::endl;

    std::cout << "6. MODULE 6 -- ACCESIBILITY SUPPORT MODULE " << std::endl;

    std::cout << "7. MODULE 7 -- EV SUPPORT MODULE " << std::endl;

    std::cout << "8. MODULE 8 -- CHARGING STATION STATUS DISPLAY MODULE " << std::endl;

    std::cout << "9. MODULE 9 -- CHARGING COST CALCULATION MODULE  " << std::endl;

    std::cout << "10. EXIT " << std::endl;

     cout<<"\nEnter your choice:\t";

     cin>>choice;

     switch(choice)
     {
         case 1:module1();

                break;

         case 2:module2();

                break;

         case 3:module3();

                break;

         case 4:module4();

                break;

         case 5:module5();

                break;

         case 6:module6();

                break;

         case 7:module7();

                break;

         case 8:module8();

                break;

         case 9:module9();

                break;


         default:cout<<"ENTER VALID CHOICE";

                break;


     }

    }

    while(choice!=11);

    return 0;
}

