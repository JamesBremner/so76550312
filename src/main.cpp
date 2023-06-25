#include "definitions.h"
#include "profiles.h"
#include "cRunWatch.h"
#define MONITOR



Profiles get_profiles(int count)
{
    Profiles ret(count);

    return ret;
}

Companies get_companies(int count)
{
    Companies ret(count);

    return ret;
}

int main()
{
    #ifdef MONITOR
    raven::set::cRunWatch::Start();
    #endif

    int testCount = 10000;
    Profiles profiles = get_profiles(testCount);
    Companies companies = get_companies(testCount);


    // Create nodes and edges from profiles and companies
    auto [nodes, edges] = create_edges_and_nodes_from_profiles(profiles, companies);

    raven::set::cRunWatch::Report();


    // lots of functions using Nodes and Edges
    //...
    //...
    
    return 0;
}
