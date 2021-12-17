#include "KDNode.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/BBox.hpp"

KDNode::KDNode()
    : left{NULL}, right{NULL}, primitives{std::vector<Geometry *>()}
{
}

KDNode::KDNode(std::vector<Geometry *> _primitives)
    : primitives{_primitives}, bb{BBox()}
{
    // compute bounding box containing all primitives
    for (Geometry *primitive : primitives)
    {
        bb.extend(primitive->getBBox());
    }
}

KDNode::KDNode(std::vector<Geometry *> _primitives, BBox _bb)
    : primitives{_primitives}, bb{_bb}
{
}
void KDNode::add_primitive(Geometry *primitive, BBox new_bb)
{
    primitives.push_back(primitive);
    bb = new_bb;
}
void KDNode::add_primitive(Geometry *primitive)
{
    bb.extend(primitive->getBBox());
    add_primitive(primitive, bb);
}

void KDNode::build_kd_tree(KDNode *node)
{

    BBox current_bb = node->bb;

    int splitaxis = current_bb.maximum_axis(); // split along longest axis
    Vector3D lengths = current_bb.pmax - current_bb.pmin;

    // save length of longest axis
    double axislength;
    if (splitaxis == X_AXIS)
    {
        axislength = lengths.x;
    }
    else if (splitaxis == Y_AXIS)
    {
        axislength = lengths.y;
    }
    else
    {
        axislength = lengths.z;
    }

    //  stoping condition
    if (node->primitives.size() < 3 || axislength < 0.01)
    {
        return;
    }

    // offset from smallest value of BBo along splitaxis
    double split_offset = axislength / 2;

    // compute midpoints for bounding box, where each half will be a new node

    Point3D midpoint_1 = current_bb.pmin;
    Point3D midpoint_2 = current_bb.pmax;

    if (splitaxis == X_AXIS)
    {
        midpoint_1.x += split_offset;
        midpoint_2.x -= split_offset;
    }
    else if (splitaxis == Y_AXIS)
    {
        midpoint_1.y += split_offset;
        midpoint_2.y -= split_offset;
    }
    else if (splitaxis == Z_AXIS)
    {
        midpoint_1.z += split_offset;
        midpoint_2.z -= split_offset;
    }

    BBox splitboxleft = current_bb;
    splitboxleft.pmax = midpoint_2;

    BBox splitboxright = current_bb;
    splitboxright.pmin = midpoint_1;

    node->left = new KDNode();
    node->right = new KDNode();

    // put primitives into their bounding box/es

    for (Geometry *primitive : node->primitives)
    {
        if (splitboxleft.overlaps(primitive->getBBox()))
        {
            node->left->add_primitive(primitive, splitboxleft);
        }
        if (splitboxright.overlaps(primitive->getBBox()))
        {
            node->right->add_primitive(primitive, splitboxright);
        }
    }

    // deallocate space of primitives as they now belong to the children
    node->primitives.clear();
    node->primitives.shrink_to_fit();

    build_kd_tree(node->left);
    build_kd_tree(node->right);
}

KDNode::~KDNode()
{
    if (left != NULL)
    {
        delete left;
    }
    if (right != NULL)
    {
        delete right;
    }
}