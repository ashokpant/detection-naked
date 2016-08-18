//
// Created by Ashok K. Pant on 8/10/16.
//
#include "iostream"
#ifndef CONFIG_HPP
#define CONFIG_HPP
class Config{
public:
    static std::string DETECTOR;
    static bool NAKED;
    static bool DRAW_HAAR_FEATURES;
    static bool RUN_DETECTOR_IN_PARALLEL;
};
#endif //CONFIG_HPP
