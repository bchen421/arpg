//
//  TexturePacker.cpp
//  arpg
//
//  Created by Benjamin Chen on 6/12/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#include <fstream>
#include <iostream>

#include "TexturePacker.h"

#pragma mark - Spritesheet Data Utilities

bool TexturePacker::parseSpritesheetData(std::string filename, std::map<std::string,TexturePacker::spriteData>& map)
{
    std::string jsonString;
    
    if (!getFileContents(filename, &jsonString))
    {
        printf("Unable to parse file: %s", filename.c_str());
        return false;
    }
    
    rapidjson::Document document;
    
    document.Parse(jsonString.c_str());
    
    if (!validateSpritesheetJSON(&document))
    {
        printf("%s if not in the expected format!\n", filename.c_str());
        return false;
    }
    
    for (rapidjson::Value::ConstMemberIterator itr = document["frames"].MemberBegin(); itr != document["frames"].MemberEnd(); itr++)
    {
        std::string spriteKey = itr->name.GetString();
        TexturePacker::spriteData spriteData;
        
        // Builds frame SDL_Rect
        spriteData.frame.x = document["frames"][itr->name.GetString()]["frame"]["x"].GetInt();
        spriteData.frame.y = document["frames"][itr->name.GetString()]["frame"]["y"].GetInt();
        spriteData.frame.w = document["frames"][itr->name.GetString()]["frame"]["w"].GetInt();
        spriteData.frame.h = document["frames"][itr->name.GetString()]["frame"]["h"].GetInt();
        
        // Grabs original sprite width and height
        spriteData.spriteWidth = document["frames"][itr->name.GetString()]["sourceSize"]["w"].GetInt();
        spriteData.spriteHeight = document["frames"][itr->name.GetString()]["sourceSize"]["h"].GetInt();
        
        // Grab rotated and trimmed bools
        // Unsupported right now
        spriteData.rotated = document["frames"][itr->name.GetString()]["rotated"].GetBool();
        spriteData.trimmed = document["frames"][itr->name.GetString()]["trimmed"].GetBool();
        
        map[spriteKey] = spriteData;
    }
    
    
    return true;
}

bool TexturePacker::validateSpritesheetJSON(rapidjson::Document* document)
{
    if (!document->IsObject())
    {
        printf("JSON document is not an object as expected.\n");
        return false;
    }
    
    if (!document->HasMember("frames"))
    {
        printf("Cannot find frames key!\n");
        return false;
    }

    
    return true;
}

bool TexturePacker::getFileContents(std::string filename, std::string* contents)
{
    // Opens a RO stream of the file
    std::ifstream jsonFile;
    jsonFile.open(filename);
    
    // Tests if stream is openable for IO operations
    if (jsonFile.fail())
    {
        printf("Unable to open file: %s\n", filename.c_str());
        return false;
    }
    
    // Moves input position to the EOF
    jsonFile.seekg(0, std::ifstream::end);
    
    // Tests for iostream failbit
    if (jsonFile.fail())
    {
        printf("Unable to find EOF for file: %s\n", filename.c_str());
        return false;
    }
    
    // Resize String Variable to same size as data
    contents->resize(jsonFile.tellg());
    
    // Moves input position back to file beginning
    jsonFile.seekg(0, std::ifstream::beg);
    
    // Tests for iostream failbit
    if (jsonFile.fail())
    {
        printf("Unable to find EOF for file: %s\n", filename.c_str());
        return false;
    }
    
    // Extracts from iostream
    // First parameter is pointer to char array
    // Second parameter is count, which is the same size as the target string
    jsonFile.read(&((*contents)[0]), contents->size());
    
    // Tidy up after yourself
    jsonFile.close();
    
    return true;
}