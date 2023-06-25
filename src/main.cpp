#include "definitions.h"
#include "profiles.h"
#define MONITOR

Profiles get_profiles(int count)
{
    Profiles ret(count);

    /// ...stub ...

    return ret;
}

Companies get_companies(int count)
{
    Companies ret(count);

    /// ...stub ...

    return ret;
}

int main()
{
    int testCount = 10000;
    Profiles profiles = get_profiles(testCount);
    Companies companies = get_companies(testCount);

#ifdef MONITOR

    auto before_creating_edges_and_nodes = std::chrono::high_resolution_clock::now();

#endif

    // Create nodes and edges from profiles and companies
    auto [nodes, edges] = create_edges_and_nodes_from_profiles(profiles, companies);

#ifdef MONITOR
    auto after_creating_edges_and_nodes = std::chrono::high_resolution_clock::now();
    auto time_creating_edges_and_nodes = std::chrono::duration_cast<std::chrono::milliseconds>(after_creating_edges_and_nodes - before_creating_edges_and_nodes).count();
    std::cout << "time_creating_edges_and_nodes  (msecs) " << time_creating_edges_and_nodes 
    <<" for count of "<< testCount<< "\n";

#endif
    // lots of functions using Nodes and Edges
    //...
    //...
    return 0;
}
