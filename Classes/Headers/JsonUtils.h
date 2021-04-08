#pragma once

#include "libjson.h"

class JsonUtils
{
public:
    static int getInt(const std::string& key, const JSONNode& node, int defaultData = 0)
    {
        JSONNode::const_iterator iter = node.find(key);
        if(node.end() == iter)
            return defaultData;
        
        int data = (int)iter->as_int();
        return data;
    }
};
