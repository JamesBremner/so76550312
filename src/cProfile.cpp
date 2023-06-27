#include "declarations.h"

/** @brief Check if the profile is to be used
 *
 * Profile is used if 1 or more experiences have a defined location
 */
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
    os << "linkedin_url: " << linkedin_url << std::endl;
    os << "name: " << name << std::endl;
    os << "experiences: " << std::endl;
    for (auto &e : myExperiences)
    {
        os << '\t' << e.text() << std::endl;
    }
    return os.str();
}