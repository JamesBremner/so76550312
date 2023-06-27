#include "declarations.h"


    cProfile::cProfile(
        const std::string &linkedin_url,
        const std::string &name,
        const std::vector<std::string> &skills,
        const vExperiences_t &experiences)
        : mylinkedin_url( std::move( linkedin_url)),
        myName( std::move(name )),
        mySkills( std::move( skills )),
        myExperiences(std::move(experiences))
        {}

bool cProfile::isUsed() const
{
    for (const auto &exp : myExperiences)
        if (!exp.location().empty())
            return true;
    return false;
}

std::string cProfile::text() const
{
    std::stringstream os;
    os << "linkedin_url: " << mylinkedin_url << std::endl;
    os << "name: " << myName << std::endl;
    os << "experiences: " << std::endl;
    for (auto &e : myExperiences)
    {
        os << '\t' << e.text() << std::endl;
    }
    return os.str();
}