class cExperience
{
    std::string myfrom_date;
    std::string to_date;
    std::string position_title;
    float myDuration;
    std::string myLocation;
    std::string institution_name;
    float mySalary;

public:
    cExperience(
        const std::string &from_date,
        const std::string &to_date,
        const std::string &position_title,
        float duration,
        const std::string &location,
        const std::string &institution_name,
        float salary)
        : myfrom_date( from_date ),
        myLocation( location ),
        myDuration( duration ),
        mySalary( salary )
    {
    }
    cExperience(bool ftest = false)
    {
        myLocation = "4334";
    }

    std::string location() const
    {
        return myLocation;
    }
    std::string text() const
    {
        std::stringstream os;
        os << "from_date: " << myfrom_date << ", ";
        os << "to_date: " << to_date << ", ";
        os << "position_title: " << position_title << ", ";
        os << "duration: " << myDuration << ", ";
        os << "location: " << myLocation << ", ";
        os << "institution_name: " << institution_name << ", ";
        os << "salary: " << mySalary << std::endl;
        return os.str();
    }
};
typedef std::vector<cExperience> vExperiences_t;

