#include "KDTree.hpp"
#include <stack>
#include "../utilities/BBox.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../world/World.hpp"

KDTree::KDTree(World *world)
    : world_ptr{world}, root_node{new KDNode(world->geometry)}
{
    KDNode::build_kd_tree(root_node);
}

KDTree::~KDTree() { delete root_node; }

ShadeInfo KDTree::hit_objects(const Ray &ray) const
{
    ShadeInfo sinfomin(*this->world_ptr);
    ShadeInfo sinfocur(*this->world_ptr);

    std::stack<KDNode *> frontier;
    frontier.push(root_node);

    KDNode *current = frontier.top();
    float t;
    float tmin = kHugeValue;

    while (!frontier.empty())
    {
        if (current->left == NULL || current->right == NULL)
        {
            // we are at leaf node, this is where we intersect with geometry
            for (Geometry *geom : current->primitives)
            {
                if (geom->hit(ray, t, sinfocur) && (t < tmin))
                {
                    tmin = t;
                    sinfomin = sinfocur;
                    sinfomin.hit = true;
                    sinfomin.material_ptr = geom->get_material();
                    sinfomin.ray = ray;
                    sinfomin.t = t;
                }
            }
        }
        else
        {
            if (current->left->bb.hit(ray))
            {
                // if the ray hits the left bounding box, add child to frontier
                frontier.push(current->left);
            }

            if (current->right->bb.hit(ray))
            {
                // if the ray hits the right bounding box, add child to frontier
                frontier.push(current->right);
            }
        }
        // move on to next item
        current = frontier.top();
        frontier.pop();
    }
    return sinfomin;
}