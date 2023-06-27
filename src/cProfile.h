class cProfile
{
    std::string linkedin_url;
    std::string name;
    const vExperiences_t myExperiences;
    std::vector<std::string> skills;

public:
    cProfile(
        const std::string &linkedin_url,
        const std::string &name,
        const std::vector<std::string> &skills,
        const vExperiences_t &experiences)
        : myExperiences(std::move(experiences))
        {}

    cProfile( bool ftest = false )
    : myExperiences(10 )
    {}

        /** @brief Check if the profile is to be used
     *
     * Profile is used if 1 or more experiences have a defined location
     */
    bool isUsed() const;

    const vExperiences_t& experiences() const
    {
        return myExperiences;
    }

    std::string text() const;

};
typedef std::vector<cProfile> vProfile_t;