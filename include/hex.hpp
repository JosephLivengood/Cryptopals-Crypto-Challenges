#include <string>
#include <vector>
#pragma once

namespace encoding {
  
  const std::string base64_chars { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/" };
  const std::string hex_chars { "0123456789abcdef" };
  
  class HexString {
    private:
      std::string hex_;
      std::vector<uint8_t> hex_bytes_;
    public:
      HexString (std::string);
      std::string to_base64();
      std::string print();
  };
  
}

uint8_t pair_to_byte(const char a, const char b);
uint8_t hex_to_number(const char c);
