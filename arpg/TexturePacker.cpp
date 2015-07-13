//
//  TexturePacker.cpp
//  arpg
//
//  Created by Benjamin Chen on 6/12/15.
//  Copyright (c) 2015 chenjamin. All rights reserved.
//

#include <fstream>
#include <iostream>

#include "Constants.h"
#include "GameUtilities.h"
#include "TexturePacker.h"

#pragma mark - Spritesheet Data Utilities
bool TexturePacker::parseSpriteMetaData(std::string filename, std::map<std::string, TexturePacker::spriteData>& map)
{
    std::string jsonString;
    
    if (!getFileContents(filename, &jsonString))
    {
        printf("Unable to parse metadata file: %s", filename.c_str());
        return false;
    }
    
    rapidjson::Document document;
    
    document.Parse(jsonString.c_str());
    
    assert(document.HasMember("metadata"));
    const rapidjson::Value& metadata = document["metadata"];
    
    for (rapidjson::Value::ConstMemberIterator itr = metadata.MemberBegin(); itr != metadata.MemberEnd(); itr++)
    {
        std::string spriteKey = itr->name.GetString();
        
        if (metadata[spriteKey.c_str()].HasMember("hurtboxes"))
        {
            debug_print("%s has hurtbox data.\n", itr->name.GetString());
            const rapidjson::Value& hurtboxes = metadata[spriteKey.c_str()]["hurtboxes"];
            assert(hurtboxes.IsArray());
            
            for (rapidjson::SizeType i = 0; i < hurtboxes.Size(); i++)
            {
                int x = hurtboxes[i]["x"].GetInt();
                int y = hurtboxes[i]["y"].GetInt();
                int w = hurtboxes[i]["w"].GetInt();
                int h = hurtboxes[i]["h"].GetInt();
                
                debug_print("Creating SDL_Rect X: %d Y: %d W: %d H: %d", x, y, w, h);
                
                SDL_Rect hurtbox = {x,y,w,h};
                
                map[spriteKey].hurtboxes.push_back(hurtbox);
                
            }
        }
        
        if (document["metadata"][spriteKey.c_str()].HasMember("hitboxes"))
        {
            debug_print("%s has hitbox data.\n", itr->name.GetString());
            const rapidjson::Value& hitboxes = document["metadata"][spriteKey.c_str()]["hitboxes"];
        }
    }
    
    return true;
}

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
        printf("%s is not in the expected format!\n", filename.c_str());
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