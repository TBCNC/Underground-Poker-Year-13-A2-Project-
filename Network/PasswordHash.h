//#include "CryptLib\sha3.h"

#include <ctime>
#include <iostream>
#include <string>
#include "../Crypto++/sha.h"
#include "../Crypto++/hex.h"
#pragma once


//This class is responsible for converting between SHA3 salts + hash and strings; and vice versa.
class PasswordHash {
public:
	static std::string GeneratePassword(std::string text, std::string salt = GenerateSalt());
	static bool ComparePasswords(std::string password, std::string passwordHash);
private:
	static int AlphabetValue(char letter);
	static std::string EncodeHash(std::string text);
	static std::string GenerateSalt();
};
