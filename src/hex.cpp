#include <hex.hpp>
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
  
  uint8_t octets[3];
  
  for (decltype(hex_bytes_.size()) i = 0; i + 2 < hex_bytes_.size(); i += 3) {
    octets[0] = hex_bytes_.at(i);
    octets[1] = hex_bytes_.at(i+1);
    octets[2] = hex_bytes_.at(i+2);
    
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
