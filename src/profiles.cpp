#include "definitions.h"
#include "profiles.h"
#include "cRunWatch.h"

std::pair<Nodes, Edges> create_edges_and_nodes_from_profiles(Profiles &profiles, Companies &companies)
{
    raven::set::cRunWatch aWatcher("create_edges_and_nodes_from_profiles");

    using namespace std::literals;

    Nodes nodes;
    Edges edges;
    nodes.reserve(40'000);
    edges.reserve(40'000);

    bool use_profile;

    struct company_data
    {
        float tenure;
        float growth;
        int size;
        std::string industry; // this should be an index into a table of industry names
    };

    std::unordered_map<std::string, company_data> company_map;

    float current_duration;
    float t_company_size, t_median_tenure, t_headcount_growth, t_duration, t_salary;
    s t_name, t_position_title, t_location, t_institution_name, t_industry;

    for (Company &company : companies)
    {
        raven::set::cRunWatch aWatcher("populate company map");
        company_data scd;
        scd.tenure = company.median_tenure;
        scd.growth = company.headcount_growth;
        scd.size = company.company_size;
        scd.industry = company.industry;

        company_map[company.name] = scd;
    }

    Nodes nodes_temp;
    for (Profile &profile : profiles)
    {
        raven::set::cRunWatch aWatcher("loop over profiles");

        nodes_temp.clear();
        current_duration = 0.0;
        use_profile = false;

        for (Experience &experience : profile.experiences)
        {
            raven::set::cRunWatch aWatcher("loop over experiences");
            stv location = stv(experience.location);

            if (location.compare(""sv) != 0)
            {

                // if (location.find("United Kingdom"sv)!=stv::npos)

                t_name = profile.name;
                t_position_title = experience.position_title;
                t_location = experience.location;

                t_duration = experience.duration;

                t_institution_name = experience.institution_name;

                company_data scd = company_map[t_institution_name];
                t_company_size = scd.size;
                t_median_tenure = scd.tenure;
                t_headcount_growth = scd.growth;

                t_salary = experience.salary;

                t_industry = scd.industry;

                Node node_obj = Node(std::move(t_name),
                                     std::move(t_position_title),
                                     std::move(t_institution_name),
                                     std::move(t_location),
                                     std::move(t_industry),
                                     profile.linkedin_url,
                                     t_duration,
                                     current_duration,
                                     t_company_size,
                                     t_median_tenure,
                                     t_salary,
                                     t_headcount_growth);

                nodes_temp.push_back(std::move(node_obj));

                current_duration += t_duration;
            }
        }

        {
            raven::set::cRunWatch aWatcher("rest of profile loop");
            for (Node &node : nodes_temp)
            {
                if (node.location.compare(""sv) != 0)
                {
                    use_profile = true;
                    break;
                }
            }

            if (!use_profile)
                continue;

           {
                raven::set::cRunWatch aWatcher("populate nodes");

                // loop over nodes constructed by this profile
                for (auto &node : nodes_temp)
                {
                    // add to the nodes vector
                    nodes.push_back(std::move(node));

                    // assign index into node vector
                    nodes.back().index = nodes.size() - 1;
                }
            }
            {
                raven::set::cRunWatch aWatcher("populate edges");
                for (int i = 0; i < nodes_temp.size() - 1; i++)
                {
                    // Edge edge = Edge(&nodes_temp[i+1],&nodes_temp[i]);
                    edges.emplace_back(std::move(nodes_temp[i + 1]), std::move(nodes_temp[i]));
                }
            }
        }
    }

    return std::make_pair(std::move(nodes), std::move(edges));
}