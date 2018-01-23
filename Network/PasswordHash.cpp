#include "PasswordHash.h"

std::string PasswordHash::EncodeHash(std::string text) {
	
	byte digest[CryptoPP::SHA256::DIGESTSIZE];
	std::string message = "abcdefghijklmnopqrstuvwxyz";

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
	const std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"£$%^&*()";
	std::string salt = "";
	for (int c = 0; c < rand() % 10 + 1; c++) {
		salt += alphabet[rand() % strlen(alphabet.c_str()) + 0];
	}
	return salt;
}