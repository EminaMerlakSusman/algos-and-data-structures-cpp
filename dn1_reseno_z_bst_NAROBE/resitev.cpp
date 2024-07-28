#include "resitev.h"
#ifndef RESITEV_H
#define RESITEV_H


#include <string>
#include "bst.h" // include the binary search tree header file
#include <iostream>
using std::cout;
using std::endl;
BinarySearchTree bst;
int Resitev::obdelaj(const string & ukaz){
    if (ukaz[0] == 'v'){
        // vstavim v strukturo (TODO)
        // in vrnem nekaj
        
        std::string time_str = ukaz.substr(2, ukaz.find(' ', 2) - 2); // extract the time string from the command
        std::string num_str = ukaz.substr(ukaz.find(' ', 2) + 1); // extract the number string from the command
        int time = std::stoi(time_str); // convert the time string to an integer
        int num = std::stoi(num_str); // convert the number string to an integer
        bst.insert(num, time); // insert the time and number into the binary search tree
        cout << "vstavljam vozlišče (" << time << "," << num << ")" << endl;
        return 0;
    } else{
        // izracunam (TODO)
        
        std::string time_str = ukaz.substr(2, ukaz.find(' ', 2) - 2); // extract the time string from the command
        std::string num_str = ukaz.substr(ukaz.find(' ', 2) + 1); // extract the number string from the command
        int time = std::stoi(time_str); // convert the time string to an integer
        int num = std::stoi(num_str); // convert the number string to an integer
        cout << "poizvedba:" << time << ", " << num <<endl;
        std::vector<int> closest_nums = bst.findClosestNums(time, num, 4); // find the 4 closest numbers to 'num' among all the inserted pairs before 'time'
        int sum_diff = 0;
        for (int i = 0; i < closest_nums.size(); i++) {
            cout << closest_nums[i] << " " << endl;
            sum_diff += abs(closest_nums[i] - num); // compute the sum of differences between the closest numbers and 'num'
        }
        return sum_diff;
    }
}

#endif // RESITEV_H