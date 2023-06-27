class cNode
{
    int myIndex;
    int myProfileIndex;
    int myExperienceIndex;

public:
    cNode(
        int index,
        int profileIndex,
        int experienceIndex)
        : myIndex(index),
          myProfileIndex(profileIndex),
          myExperienceIndex(experienceIndex)
    {
    }
    int index() const
    {
        return myIndex;
    }
    int profileIndex() const
    {
        return myProfileIndex;
    }
    int experienceIndex() const
    {
        return myExperienceIndex;
    }
};

class cEdge
{
    int mySource;
    int myTarget;

public:
    cEdge(int source, int target)
        : mySource(source), myTarget(target)
    {
    }
    int source() const
    {
        return mySource;
    }
    int target() const
    {
        return myTarget;
    }
};

typedef std::vector<cNode> vNode_t;
typedef std::vector<cEdge> vEdge_t;