class cCompany
{
    std::string myName;
    std::string industry;
    float headcount_growth;
    float median_tenure;
    int company_size;

public:
    cCompany()
    : myName("n/a")
    , industry("n/a")
    {}
    cCompany( const std::string& name )
    : myName( std::move(name))
    {}
    bool operator==(const cCompany &other) const
    {
        return (this->myName == other.myName);
    }

    friend std::ostream &operator<<(std::ostream &os, const cCompany &company)
    {
        os << "Name: " << company.myName << std::endl;
        os << "Industry: " << company.industry << std::endl;
        os << "Headcount Growth: " << company.headcount_growth << std::endl;
        os << "Median Tenure: " << company.median_tenure << std::endl;
        os << "Company Size: " << company.company_size << std::endl;
        return os;
    }
};
typedef std::vector<cCompany> vCompany_t;

