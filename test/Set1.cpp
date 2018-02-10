#include<hex.hpp>
#include<catch.hpp>

TEST_CASE( "Challenge 1", "[hex]" ) {
  
  SECTION( "HexString object creation works" ) {
    std::string valid_hex_string { "49276d2" };
    encoding::HexString valid_hex_object { valid_hex_string };
    REQUIRE( valid_hex_object.print() == valid_hex_string );
  }

  SECTION( "encoding to base64 works" ) {
    encoding::HexString valid_hex { "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d" };
    std::string valid_64 { "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t" };
    REQUIRE( valid_hex.to_base64() == valid_64 );
    
    encoding::HexString valid_uneven_hex { "49276d2" };
    std::string valid_uneven_64 { "SSdtyQ==" };
    REQUIRE( valid_uneven_hex.to_base64() == valid_uneven_64 );
  }
  
}
