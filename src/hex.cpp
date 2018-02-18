#include <hex.hpp>
#include <iostream>
#include <functional>
#include <stdexcept>

encoding::HexString::HexString(std::string hex) {
  hex_ = hex;
  for (size_t i = 0; i < hex.size(); i += 2) {
    hex_bytes_.push_back(pair_to_byte(hex[i], hex[i + 1]));
  }
}

std::string encoding::HexString::to_base64() {
  std::string result;
  result.reserve(hex_bytes_.size() / 3 * 4 + 4);
  
  /* 3 octets as each octet stores 2 hex characters(4 bit) and 6 are needed for even encoding */
  uint8_t octets[3];
  
  for (decltype(hex_bytes_.size()) i = 0; i + 2 < hex_bytes_.size(); i += 3) {
    octets[0] = hex_bytes_.at(i);
    octets[1] = hex_bytes_.at(i+1);
    octets[2] = hex_bytes_.at(i+2);
    
    /*
     *  Hex characters are 4 bits while base64 encoded character are 6 bits
     *  For every 6 hex there are 4 base64 encoded:
     *
     *  aaaa bbbb cccc  dddd eeee ffff
     *  aaaabb  bbcccc  ddddee  eeffff
     */
    result.push_back( base64_chars[ octets[0] >> 2 ] );
    result.push_back( base64_chars[ ((octets[0] & 0x3) << 4) + (octets[1] >> 4) ] );
    result.push_back( base64_chars[ ((octets[1] & 0xf) << 2) + (octets[2] >> 6) ] );
    result.push_back( base64_chars[ octets[2] & 0x3f ] );
  }
  
  auto remainder = hex_bytes_.size() % 3;
  
  if (remainder > 0) {
    octets[0] = octets[1] = octets[2] = 0;
    
    auto last = hex_bytes_.end();
    for (auto i = remainder; i > 0; --i) {
      octets[i - 1] = *(--last);
    }
    
    result.push_back( base64_chars[ octets[0] >> 2 ] );
    result.push_back( base64_chars[ ((octets[0] & 0x3) << 4) + (octets[1] >> 4) ] );
    if (remainder == 2) {
      result.push_back( base64_chars[ ((octets[1] & 0xf) << 2) + (octets[2] >> 6) ] );
    }
    
    std::string padding(3 - remainder, '=');
    result.append(padding);
  }
  
  return result;
}

std::string encoding::HexString::print() {
  return hex_;
}

std::vector<uint8_t> encoding::HexString::print_bytes() {
  return hex_bytes_;
}

encoding::HexString encoding::HexString::even_xor(encoding::HexString against) {
  if (hex_bytes_.size() != against.print_bytes().size()) {
    std::cout << "uneven inputs" << std::endl;
    throw std::invalid_argument("uneven inputs");
  }
  
  std::vector<uint8_t> result_bytes;
  for (int i = 0; i < hex_bytes_.size(); i++) {
    uint8_t temp = hex_bytes_[i] ^ against.print_bytes()[i];
    result_bytes.push_back(temp);
  }
  
  std::string result_string;
  for (int i = 0; i < result_bytes.size(); i++) {
    auto t1 = result_bytes[i] >> 4;
    auto t2 = result_bytes[i] & 0xf;
    result_string.push_back(hex_chars[t1 % 16]);
    result_string.push_back(hex_chars[t2 % 16]);
  }
  
  encoding::HexString result { result_string };
  return result;
}

uint8_t pair_to_byte(const char a, const char b) {
  return (hex_to_number(a) << 4) + hex_to_number(b);
}

uint8_t hex_to_number(const char c) {
  if ('0' <= c && c <= '9') {
    return c - '0';
  }
  if ('A' <= c && c <= 'Z') {
    return c - 'A' + 10;
  }
  return c - 'a' + 10;
}
