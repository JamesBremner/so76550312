#include "declarations.h"

cProjectGraph::cProjectGraph(
    const vProfile_t &profiles,
    const vCompany_t &companies)
    : myCompany(std::move(companies)),
      myProfile(std::move(profiles))
{
    raven::set::cRunWatch aWatcher("cProjectGraph constructor");

    // loop over profiles
    int profileIndex = -1;
    for (const cProfile &profile : profiles)
    {
        profileIndex++;

        // check that profile will be used
        if (!profile.isUsed())
            continue;

        // loop over experiences
        int experienceIndex = -1;
        for (const auto &experience : profile.experiences())
        {
            experienceIndex++;

            // construct node for experience
            myNode.emplace_back(
                myNode.size(),
                profileIndex,
                experienceIndex);

            // check for previous node
            if (myNode.size() == 1)
                continue;

            // construct edge from previous node
            myEdge.emplace_back(
                myNode[myNode.size() - 2].index(),
                myNode[myNode.size() - 1].index());
        }
    }
}

std::string cProjectGraph::text() const
{
    std::stringstream ss;
    ss << "Project Graph:\n"
       << myProfile.size() << " Profiles, "
       << myNode.size() << " Nodes, "
       << myEdge.size() << " Edges"
       << "\n\n";

    for (auto &p : myProfile)
        ss << p.text();

    for (auto &n : myNode)
        ss << "\nNode:\n"
           << experience(n).text();

    for (auto &e : myEdge)
        ss << "\nEdge:\n"
           << experience(myNode[e.source()]).text()
           << " TO\n"
           << experience(myNode[e.target()]).text();

    return ss.str();
}

const cExperience &cProjectGraph::experience(
    const cNode &n) const
{
    return myProfile[n.profileIndex()].experiences()[n.experienceIndex()];
}