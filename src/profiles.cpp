#include "definitions.h"
#include "profiles.h"
#define MONITOR

std::pair<Nodes,Edges> create_edges_and_nodes_from_profiles(Profiles & profiles, Companies & companies)
    {
        using namespace std::literals;

        Nodes nodes;
        Edges edges;
        nodes.reserve(40'000);
        edges.reserve(40'000);

        bool use_profile;


        std::unordered_map<s,float> company_name_median_tenure_map;
        std::unordered_map<s,float> company_name_headcount_growth_map;
        std::unordered_map<s,int> company_name_company_size_map;
        std::unordered_map<s,s> company_name_industry_map;

        float current_duration;
        float t_company_size, t_median_tenure, t_headcount_growth, t_duration, t_salary;
        s t_name, t_position_title, t_location, t_institution_name, t_industry;

        

        #ifdef MONITOR
            auto before_map_createion = std::chrono::high_resolution_clock::now();
        #endif  

        for (Company & company : companies)
            {
                
                company_name_median_tenure_map[company.name] = company.median_tenure;
                company_name_headcount_growth_map[company.name] = company.headcount_growth;
                company_name_company_size_map[company.name] = company.company_size;
                company_name_industry_map[company.name] = company.industry;
            }
        
        #ifdef MONITOR
            auto after_map_creation = std::chrono::high_resolution_clock::now();

            auto temp = std::chrono::duration_cast<std::chrono::milliseconds>(after_map_creation-before_map_createion).count();

            std::cout << "after_map_creation (msecs) " <<temp<<std::endl;
        #endif

        for (Profile & profile : profiles)
            {
                Nodes nodes_temp;
                nodes_temp.reserve(profile.experiences.size());
                current_duration = 0.0;
                use_profile = false;


                for (Experience & experience : profile.experiences)
                    {
                        
                        stv location = stv(experience.location);
                        
                        if (location.compare(""sv)!=0)
                            {
                                
                                //if (location.find("United Kingdom"sv)!=stv::npos)
                                    
                                t_name = profile.name;
                                t_position_title = experience.position_title;
                                t_location = experience.location;

                                
                                t_duration = experience.duration;
                                
                                
                                t_institution_name = experience.institution_name;
                                
                                t_company_size = company_name_company_size_map[t_institution_name];
                                t_median_tenure = company_name_median_tenure_map[t_institution_name];
                                t_headcount_growth = company_name_headcount_growth_map[t_institution_name];

                                
                                t_salary = experience.salary;


                                t_industry = company_name_industry_map[t_institution_name];
                                
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
                
                for (Node & node : nodes_temp)
                    {
                        if (node.location.compare(""sv)!=0)
                        {
                            use_profile = true;
                            break;
                        }
                            
                    }
                
                if (!use_profile)
                    continue;
                
                current_duration = 0.0;

                for (Nodes::reverse_iterator rit=nodes_temp.rbegin();rit!=nodes_temp.rend();++rit)
                    {
                        rit->current_experience_duration = current_duration;
                        current_duration += rit->duration;
                    }
                
                if (nodes_temp.size()>1)
                    {
                        for (int i=0;i<nodes_temp.size()-1;i++)
                            {
                                //Edge edge = Edge(&nodes_temp[i+1],&nodes_temp[i]);
                                edges.emplace_back(std::move(nodes_temp[i+1]),std::move(nodes_temp[i]));

                            }
                    }
                
                for (auto & node : nodes_temp)
                    {
                        nodes.push_back(std::move(node));
                    }
            }

        return std::make_pair(std::move(nodes),std::move(edges));
    }