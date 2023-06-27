#include "declarations.h"




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
        cExperience("2001","2005","",1,"London","",1),
        cExperience("2005","2010","",1,"HongKong","",1),
    };
    vProfile_t vProfile;
    vProfile.push_back( cProfile("","",{""},vexp));

    vCompany_t vCompany;
    vCompany.push_back( cCompany("testCompany") );

    cProjectGraph g( vProfile, vCompany );

    std::cout << g.text();
}

void testTiming()
{
    raven::set::cRunWatch::Start();

    int testCount = 10000;
    auto vProfile  = get_profiles(testCount);
    auto vCompany  = get_companies(testCount);


    // Create nodes and edges from profiles and companies
    cProjectGraph g2( vProfile, vCompany );

    std::cout <<"\n" << g2.nodeCount() 
        << " nodes and " << g2.edgeCount() 
        << " edges constructed\n";

    raven::set::cRunWatch::Report();    
}

int main()
{
    testSanity();

    testTiming();
 
    return 0;
}
