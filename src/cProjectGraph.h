#include <vector>

class cProjectGraph
{
public:

    /// @brief construct graph
    /// @param profiles 
    /// @param companies 
    cProjectGraph(
        const vProfile_t &profiles,
        const vCompany_t &companies);
    
    /// @brief get text describing graph
    std::string text() const;

    /// @brief get experience that generated a node
    /// @param n the node
    /// @return const reference to experience
    const cExperience& experience( 
        const cNode& n ) const;

    int nodeCount() const
    {
        return myNode.size();
    }
    int edgeCount() const
    {
        return myEdge.size();
    }

private:
    vCompany_t myCompany;
    const vProfile_t myProfile;
    vNode_t myNode;
    vEdge_t myEdge;
};