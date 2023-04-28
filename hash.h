#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
 static const unsigned long long pow_36[6] = {1ull, 36ull, 1296ull, 46656ull, 1679616ull, 60466176ull};
        unsigned long long w[5] = {0};
        int len = k.length();
				if (len == 0){
					return 0;
				}
        int offset = len % 6;
				// Get the number of substrings
				int numSub = ceil(len / 6.0001 );
				// std::cout << "offset: "<< offset << std::endl;
				// std::cout << "len: "<< len << std::endl;
				// std::cout << "numsub:" << numSub << std::endl;
				if (offset == 0){
					offset = 6;
				}
				std::string begining_sub = k.substr(0, offset);// get the first 6 - mod 6 characters and append 0s (a's)
				begining_sub.insert(0, 6 - offset, 'a');
				//std::cout << std::endl << "begining_sub: " <<begining_sub << std::endl;
				for (int i = 0; i < 6; i++){
					int val = letterDigitToNumber(begining_sub[i]);
					//std::cout << begining_sub[i] << " num: "  << val << "\n";
					w[5 - numSub] += val * pow_36[5 - i];// makes first char multiplied by 36^5
				}
				if (numSub > 1){
						for (int j = 0; j <= numSub - 2; j++){
							//std::string substr = k.substr(len - ((j * 6) - (6 - offset) - 1), 6);
							std::string substr = k.substr(6*j + offset, 6);
							for (int i = 0; i < 6; i++){
								int val = letterDigitToNumber(substr[i]);
								//std::cout << substr[i] << " num: "  << val << "\n";
								w[5 - numSub + j + 1] += val * pow_36[5 - i];// makes first char multiplied by 36^5
							}
						}
				}
        unsigned long long hash_val = 0;
        for (int i = 0; i < 5; i++) {
            hash_val += rValues[i] * w[i];
						//std::cout<< w[i] << std::endl;
        }
        return hash_val;
    }

    // convert a-z,0-9 to a value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
    if (letter >= 'a' && letter <= 'z') {
        return static_cast<HASH_INDEX_T>(letter - 'a');
    } else if (letter >= 'A' && letter <= 'Z') {
        return static_cast<HASH_INDEX_T>(letter - 'A');
    } else if (letter >= '0' && letter <= '9') {
        return static_cast<HASH_INDEX_T>(letter - '0') + 26;
    } else {
        return static_cast<HASH_INDEX_T>(-1);
    }
    }

    // Code to generate the random R values
    void generateRValues()
    {
            srand(time(0));
            for (int i = 0; i < 5; i++) {
                rValues[i] = rand();
            }
    }
};



#endif
