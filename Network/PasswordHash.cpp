#include "PasswordHash.h"

std::string PasswordHash::GeneratePassword(std::string text, std::string salt) {
	//Sha256 hashes are always 64 characters long (256 bits)
	std::string passwordHash = EncodeHash(text);
	passwordHash += salt;
	int hashCycle = rand() % 25 + 10;
	for (int c = 0; c < hashCycle; c++) {
		passwordHash = EncodeHash(passwordHash);
		passwordHash += salt;
	}
	//Represent the hash cycle by the alphabet value or numerical value
	std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	if (rand() % 1 + 0 == 0) {//Random chance
		passwordHash += alphabet[hashCycle - 1];
	}
	else {
		passwordHash += hashCycle;
	}
	return passwordHash;
}
int PasswordHash::AlphabetValue(char letter) {
	std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (int c = 0; c < strlen(alphabet.c_str()); c++) {
		if (alphabet[c] == letter)
			return c+1;
	}
}
bool PasswordHash::ComparePasswords(std::string password, std::string passwordHash) {
	std::string salt;
	int saltSize=strlen(passwordHash.c_str())-65;
	int hashCycle = 0;
	for (int c = 0; c < saltSize; c++) {
		salt += passwordHash[64 + c];
	}
	bool letter=false;
	if (isdigit(passwordHash[strlen(passwordHash.c_str()) - 1])) {
		hashCycle = (int)(passwordHash[strlen(passwordHash.c_str()) - 1]);
	}
	else {
		hashCycle = AlphabetValue(passwordHash[strlen(passwordHash.c_str()) - 1]);
		letter = true;
	}
	password = EncodeHash(password);
	password += salt;
	for (int c = 0; c < hashCycle; c++) {
		password = EncodeHash(password);
		password += salt;
	}
	if(!letter)
		password += hashCycle;
	else {
		std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		password += alphabet[hashCycle - 1];
	}
	if (password == passwordHash)
		return true;
	return false;
}
std::string PasswordHash::EncodeHash(std::string text) {
	byte digest[CryptoPP::SHA256::DIGESTSIZE];
	std::string message = text;

	CryptoPP::SHA256 hash;
	hash.CalculateDigest(digest, (const byte*)message.c_str(), message.length());

	CryptoPP::HexEncoder encoder;
	std::string output;

	encoder.Attach(new CryptoPP::StringSink(output));
	encoder.Put(digest, sizeof(digest));
	encoder.MessageEnd();
	return output;
}
std::string PasswordHash::GenerateSalt() {
	const std::string alphabet = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string salt = "";
	for (int c = 0; c < rand() % 20 + 10; c++) {
		salt += alphabet[rand() % strlen(alphabet.c_str()) + 0];
	}
	return salt;
}