#pragma once
#include <memory>
#include <glm/glm.hpp>

namespace ColorTree
{
    struct OrderedColor
    {
        int colorId;
        glm::vec3 color;
    };

    enum class NodeStatus
    {
        Unassigned,
        Assigned,
    };

    class ColorNode
    {
    public:
        ColorNode();
        ColorNode(glm::ivec2 offset, glm::ivec2 size);
        ~ColorNode();

        ColorNode* Parent() const;
        ColorNode* Child(int index) const;

        int ColorId() const;
        glm::ivec2 Offset() const;
        glm::ivec2 Size() const;
        glm::vec3 Color() const;
        void Color(int colorId, glm::vec3 color);
        NodeStatus Status() const;

        void Split();

    private:
        ColorNode* parent;
        std::unique_ptr<ColorNode> children[4];

        NodeStatus status;
        glm::ivec2 offset;
        glm::ivec2 size;
        glm::vec3 color;
        int colorId;
    };
}