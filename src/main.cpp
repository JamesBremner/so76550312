#include "declarations.h"
#include "cRunWatch.h"
#define MONITOR



vProfile_t get_profiles(int count)
{
    vProfile_t ret(count);

    return ret;
}

vCompany_t get_companies(int count)
{
    vCompany_t ret(count);

    return ret;
}

void testSanity()
{
    vExperiences_t vexp {
        cExperience("","","",1,"London","",1),
        cExperience("","","",1,"HongKong","",1),
    };
    vProfile_t vProfile;
    vProfile.push_back( cProfile("","",{""},vexp));

    vCompany_t vCompany;
    vCompany.push_back( cCompany("testCompany") );

    cProjectGraph g( vProfile, vCompany );

    std::cout << g.text();
}

int main()
{
    testSanity();

    #ifdef MONITOR
    raven::set::cRunWatch::Start();
    #endif

    int testCount = 10000;
    auto vProfile  = get_profiles(testCount);
    auto vCompany  = get_companies(testCount);


    // Create nodes and edges from profiles and companies
    cProjectGraph g2( vProfile, vCompany );

    raven::set::cRunWatch::Report();

    
    return 0;
}
