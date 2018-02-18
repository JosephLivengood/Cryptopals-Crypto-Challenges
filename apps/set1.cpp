#include <iostream>
#include <cxxopts.hpp>
#include <hex.hpp>

int main(int argc, char** argv){
  try {
    cxxopts::Options options(argv[0]);

    options.add_options("")
      ("h,help", "prints the help message")
    ;
    
    options.add_options("params")
      ("e,hexencode", "hex string to encode in base64", cxxopts::value<std::string>()) // ->default_value("49276d"))
    ;

    options.add_options("params")
      ("x,xoreven", "xor 2 even hex strings", cxxopts::value<std::string>())
    ;
    
    options.parse(argc, argv);

    if(options.count("help") > 0) {
      std::cout << options.help({"", "params"}) << std::endl;
      return 0;
    }
    
    if(options.count("hexencode") > 0) {
      try {
        auto hex_input = options["hexencode"].as<std::string>();
        encoding::HexString input { hex_input };
        std::cout << "Hex: " << input.print() << '\n' << "Base64: " << input.to_base64() << std::endl;
      } catch(...) {
        std::cout << "Error" << std::endl;
      }
    }
    
    if(options.count("xoreven") > 0) {
      try {
        auto hex_input = options["xoreven"].as<std::string>();
        encoding::HexString input1 { hex_input };
        std::string hex_input2;
        std::cout << "Enter an even hex string to xor against inital input: ";
        std::cin >> hex_input2;
        encoding::HexString input2 { hex_input2 };
        encoding::HexString result = input1.even_xor(input2);
        
        std::cout << input1.print() << " XOR'd against" << std::endl;
        std::cout << input2.print() << " results in" << std::endl;
        std::cout << result.print() << std::endl;
      } catch(...) {
        std::cout << "Error" << std::endl;
      }
    }
  } catch (const cxxopts::OptionException& e) {
    std::cout << "error parsing options: " << e.what() << std::endl;
    exit(1);
  }
  
  return 0;
}
