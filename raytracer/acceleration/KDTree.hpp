#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../world/World.hpp"
#include "Acceleration.hpp"
#include "KDNode.hpp"

/**
 Reference:
http://www.flipcode.com/archives/Raytracing_Topics_Techniques-Part_7_Kd-Trees_and_More_Speed.shtml
*/
class KDTree : public Acceleration
{

protected:
    World *world_ptr;
    KDNode *root_node;

public:
    // Constructor
    KDTree(World *world);
    KDTree() = delete;

    // Copy constructor
    KDTree(const KDTree &rhs) = delete;

    // Destructor
    virtual ~KDTree();

    // Calculates which object a ray hits
    virtual ShadeInfo hit_objects(const Ray &ray) const override;
};