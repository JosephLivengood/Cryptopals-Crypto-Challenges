#include <hex.hpp>
#include <catch.hpp>

TEST_CASE( "Challenge 1", "[set1]" ) {
  
  SECTION( "HexString object creation" ) {
    std::string valid_hex_string { "49276d2" };
    encoding::HexString valid_hex_object { valid_hex_string };
    REQUIRE( valid_hex_object.print() == valid_hex_string );
  }

  SECTION( "Encoding to base64" ) {
    encoding::HexString valid_hex { "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d" };
    std::string valid_64 { "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t" };
    REQUIRE( valid_hex.to_base64() == valid_64 );
    
    encoding::HexString valid_uneven_hex { "49276d2" };
    std::string valid_uneven_64 { "SSdtyQ==" };
    REQUIRE( valid_uneven_hex.to_base64() == valid_uneven_64 );
  }
  
}

TEST_CASE( "Challenge 2", "[set1]" ) {
  SECTION( "Xor'ing 2 hex inputs" ) {
    encoding::HexString hex1 { "1c0111001f010100061a024b53535009181c" };
    encoding::HexString hex2 { "686974207468652062756c6c277320657965" };
    encoding::HexString hex_uneven { "123456789" };
    std::string xor_result { "746865206b696420646f6e277420706c6179" };
    
    REQUIRE_THROWS( hex1.even_xor(hex_uneven) );
    REQUIRE( hex1.even_xor(hex2).print() == xor_result );
    REQUIRE( hex2.even_xor(hex1).print() == xor_result );
  }
}
