#pragma once
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <algorithm>
// some mathematical formula and constants for this project
const float DEGTORAD = 0.017453f; // converter constant from degrees to radians
const float RADTODEG = 57.295779f; // converter constant friom radians to degree
const float PI = 3.141592f; // Ratio of circumference to its diameter


float dot(sf::Vector2f& a, sf::Vector2f& b); //dot product


float length(sf::Vector2f& a); // vector's length
    

float length2(sf::Vector2f& a); // vector's length squared 
 

sf::Vector2f normalize(sf::Vector2f& a); // returns vector with length of 1;
    

int clamp(int value, int min, int max);
  

float clamp(float value, float min, float max);

