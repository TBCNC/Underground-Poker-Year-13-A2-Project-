//#include "CryptLib\sha3.h"

#include <iostream>
#include <string>
#include "../Crypto++/sha.h"
#include "../Crypto++/hex.h"
#pragma once


//This class is responsible for converting between SHA3 salts + hash and strings; and vice versa.
class PasswordHash {
public:
	static std::string EncodeHash(std::string text);
private:
	static std::string GenerateSalt();
};
