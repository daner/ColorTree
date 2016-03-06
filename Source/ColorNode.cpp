#include "ColorNode.h"
#include  <memory>
#include <iostream>

namespace ColorTree
{
    using namespace std;
    using namespace glm;

    ColorNode::ColorNode() :
        parent{ nullptr },
        status{ NodeStatus::Unassigned },
        offset{ 0, 0 },
        size{ 0, 0 }
    {
    }

    ColorNode::ColorNode(ivec2 offset, ivec2 size) :
        parent{ nullptr },
        status{ NodeStatus::Unassigned },
        offset{ offset },
        size{ size }
    {
    }

    ColorNode::~ColorNode()
    {
    }

    ColorNode* ColorNode::Parent() const
    {
        return parent;
    }

    ColorNode* ColorNode::Child(int index) const
    {
        if (index >= 0 && index < 4)
        {
            return children[index].get();
        }
        return nullptr;
    }

    ivec2 ColorNode::Offset() const
    {
        return offset;
    }

    ivec2 ColorNode::Size() const
    {
        return size;
    }

    vec3 ColorNode::Color() const
    {
        return color;
    }

    void ColorNode::Color(vec3 newColor)
    {
        color = newColor;
        status = NodeStatus::Assigned;
    }

    NodeStatus ColorNode::Status() const
    {
        return status;
    }

    void ColorNode::Split()
    {
        auto halfWidth = size.x / 2;
        auto halfHeight = size.y / 2;

        auto widthCorrection = 0;
        auto heightCorrection = 0;

        if(halfWidth * 2 != size.x)
        {
            widthCorrection = 1;
        }

        if(halfHeight * 2 != size.y)
        {
            heightCorrection = 1;
        }

        children[0] = make_unique<ColorNode>(ivec2{ offset.x, offset.y }, ivec2{ halfWidth, halfHeight });       
        children[1] = make_unique<ColorNode>(ivec2{ offset.x + halfWidth, offset.y }, ivec2{ halfWidth + widthCorrection, halfHeight });
        children[2] = make_unique<ColorNode>(ivec2{ offset.x, offset.y + halfHeight }, ivec2{ halfWidth, halfHeight + heightCorrection });
        children[3] = make_unique<ColorNode>(ivec2{ offset.x + halfWidth, offset.y + halfHeight }, ivec2{ halfWidth + widthCorrection, halfHeight + heightCorrection });

        for (auto i = 0; i < 4; i++)
        {
            children[i]->parent = this;
        }
    }
}
