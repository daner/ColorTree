#pragma once

namespace ColorTree
{
    class ColorNode
    {
    public:
        ColorNode();

    private:
        ColorNode* parent;
        ColorNode* children[4];


    };
}