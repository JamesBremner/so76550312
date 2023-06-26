#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <string>
#include <vector>
#include <string_view>

#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <utility>
#include <immintrin.h>
#include <chrono>

typedef std::string s;
typedef std::string_view stv;

struct Experience
{
    s from_date;
    s to_date;
    s position_title;
    float duration;
    s location;
    s institution_name;
    float salary;

    Experience(s from_date, s to_date, s position_title, float duration, s location, s institution_name, float salary)
    {
        this->from_date = from_date;
        this->to_date = to_date;
        this->position_title = position_title;
        this->duration = duration;
        this->location = location;
        this->institution_name = institution_name;
        this->salary = salary;
    }

    Experience()
    {
        this->from_date = "";
        this->to_date = "";
        this->position_title = "";
        this->duration = 0;
        this->location = "4334";
        this->institution_name = "";
        this->salary = 0;
    }

    friend std::ostream &operator<<(std::ostream &os, const Experience &e)
    {
        os << "from_date: " << e.from_date << std::endl;
        os << "to_date: " << e.to_date << std::endl;
        os << "position_title: " << e.position_title << std::endl;
        os << "duration: " << e.duration << std::endl;
        os << "location: " << e.location << std::endl;
        os << "institution_name: " << e.institution_name << std::endl;
        os << "salary: " << e.salary << std::endl;
        return os;
    }
};
typedef std::vector<Experience> Experiences;

struct Profile
{
    s linkedin_url;
    s name;
    Experiences experiences;
    std::vector<s> skills;

    Profile(s linkedin_url, s name, std::vector<s> skills, Experiences experiences)
    {
        this->linkedin_url = linkedin_url;
        this->name = name;
        this->skills = skills;
        this->experiences = experiences;
    }

    /** @brief Default Ctor.
     *
     * Creates 10 default experiences
     */
    Profile()
        : experiences(10)
    {
    }

    /** @brief Check if the profile is to be used
     *
     * Profile is used if 1 or emre exoperiences have a defined location
     */
    bool isUsed() const
    {
        for (const auto &exp : experiences)
            if (!exp.location.empty())
                return true;
        return false;
    }

        friend std::ostream &operator<<(std::ostream &os, const Profile &p)
        {
            os << "linkedin_url: " << p.linkedin_url << std::endl;
            os << "name: " << p.name << std::endl;
            os << "experiences: " << std::endl;
            for (auto e : p.experiences)
            {
                os << '\t' << e << std::endl;
            }
            return os;
        }
    };

    typedef std::vector<Profile> Profiles;

    struct Node
    {
        int index;
        s name;
        s position_title;
        s institution_name;
        s location;
        s industry;
        s linkedin_url;
        float duration;
        int company_size;
        float median_tenure;
        float salary;
        float headcount_growth;
        float current_experience_duration;

        Node(s t_name, s t_position_title, s t_institution_name, s t_location, s t_industry, s linkedin_url, float t_duration, float t_current_experience_duration, int t_company_size, float t_median_tenure, float t_salary, float t_headcount_growth)
        {
            this->name = t_name;
            this->position_title = t_position_title;
            this->institution_name = t_institution_name;
            this->location = t_location;
            this->industry = t_industry;
            this->linkedin_url = linkedin_url;
            this->duration = t_duration;
            this->current_experience_duration = t_current_experience_duration;
            this->company_size = t_company_size;
            this->median_tenure = t_median_tenure;
            this->salary = t_salary;
            this->headcount_growth = t_headcount_growth;
        }

        Node()
        {
            this->name = "";
            this->position_title = "";
            this->institution_name = "";
            this->location = "";
            this->industry = "";
            this->linkedin_url = "";
            this->duration = 0;
            this->current_experience_duration = 0;
            this->company_size = 0;
            this->median_tenure = 0;
            this->salary = 0;
            this->headcount_growth = 0;
        }

        bool operator==(const Node &other) const
        {
            if (this->name == other.name && this->position_title == other.position_title && this->institution_name == other.institution_name && this->location == other.location)
                return true;
            else
                return false;
        }

        friend std::ostream &operator<<(std::ostream &os, const Node &node)
        {
            os << "Name: " << node.name << std::endl;
            os << "Position Title: " << node.position_title << std::endl;
            os << "Institution Name: " << node.institution_name << std::endl;
            os << "Location: " << node.location << std::endl;
            os << "Industry: " << node.industry << std::endl;
            os << "Linkedin URL: " << node.linkedin_url << std::endl;
            os << "Duration: " << node.duration << std::endl;
            os << "Current Experience Duration " << node.current_experience_duration << std::endl;
            os << "Company Size: " << node.company_size << std::endl;
            os << "Median Tenure: " << node.median_tenure << std::endl;
            os << "Salary: " << node.salary << std::endl;
            os << "Headcount Growth: " << node.headcount_growth << std::endl;
            return os;
        }
    };

    typedef std::vector<Node> Nodes;

    struct Edge
    {
        int source;
        int target;
        s linkedin_url;
        float duration;
        int company_size;
        float median_tenure;
        float salary;
        float headcount_growth;

        Edge(const Node &t_source, const Node &t_target)
        {

            this->source = t_source.index;
            this->target = t_target.index;
            this->linkedin_url = t_target.linkedin_url;
            this->duration = t_target.duration;
            this->company_size = t_target.company_size;
            this->median_tenure = t_target.median_tenure;
            this->salary = t_target.salary;
            this->headcount_growth = t_target.headcount_growth;
        }

        Edge()
        {
            this->source = -1;
            this->target = -1;
            this->linkedin_url = "";
            this->duration = 0;
            this->company_size = 0;
            this->median_tenure = 0;
            this->salary = 0;
            this->headcount_growth = 0;
        }

        bool operator==(const Edge &other) const
        {
            return (source == other.source && target == other.target);
        }

        friend std::ostream &operator<<(std::ostream &os, const Edge &edge)
        {
            os << "Source: " << edge.source << std::endl;
            os << "Target: " << edge.target << std::endl;
            os << "Linkedin URL: " << edge.linkedin_url << std::endl;
            os << "Duration: " << edge.duration << std::endl;
            os << "Company Size: " << edge.company_size << std::endl;
            os << "Median Tenure: " << edge.median_tenure << std::endl;
            os << "Salary: " << edge.salary << std::endl;
            os << "Headcount Growth: " << edge.headcount_growth << std::endl;
            return os;
        }
    };

    typedef std::vector<Edge> Edges;

    struct Company
    {
        s name;
        s industry;
        float headcount_growth;
        float median_tenure;
        int company_size;

        Company(s name, s industry, float headcount_growth, float median_tenure, int company_size)
        {
            this->name = name;
            this->industry = industry;
            this->headcount_growth = headcount_growth;
            this->median_tenure = median_tenure;
            this->company_size = company_size;
        }

        Company()
        {
            this->name = "";
            this->industry = "";
            this->headcount_growth = 0;
            this->median_tenure = 0;
            this->company_size = 0;
        }

        bool operator==(const Company &other) const
        {
            if (this->name == other.name)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        friend std::ostream &operator<<(std::ostream &os, const Company &company)
        {
            os << "Name: " << company.name << std::endl;
            os << "Industry: " << company.industry << std::endl;
            os << "Headcount Growth: " << company.headcount_growth << std::endl;
            os << "Median Tenure: " << company.median_tenure << std::endl;
            os << "Company Size: " << company.company_size << std::endl;
            return os;
        }
    };

    typedef std::vector<Company> Companies;

#endif // DEFINITIONS_H
