// tests.cpp
#include "../src/header/MASTER.h"
#include "../src/header/tools.h"
#include "../src/utils/validityFile.cpp"
#include "../src/utils/validityRegisters.cpp"
#include "../src/utils/validityData.cpp"
#include "../src/utils/validityAddress.cpp"
#include "../src/utils/validityHexadecimal.cpp"
#include "../src/instructions/SHLD.cpp"
#include "../src/utils/increaseAddress.cpp"
#include <gtest/gtest.h>


map<string,string> mem;
string registers[7];
bool flag[7];


// Logic based CACC criteria for validityFile
TEST(validityFile, MajorClause1){
	ASSERT_TRUE(validityFile("MOV A,B"));
	ASSERT_FALSE(validityFile("MOVE A,B"));
}
TEST(validityFile, MajorClause2){
	ASSERT_TRUE(validityFile("SET 0004,00"));
	ASSERT_FALSE(validityFile("INX H,10"));
}
TEST(validityFile, MajorClause3){
	ASSERT_TRUE(validityFile("LXI H,0000"));
	ASSERT_FALSE(validityFile("DCR a"));
}
// Logic based CACC criteria for validityHexadecimal
TEST(validityHexadecimal, MajorClause1){
	ASSERT_TRUE(validityHexadecimal("1E"));
	ASSERT_FALSE(validityHexadecimal("01D"));
}
TEST(validityHexadecimal, MajorClause2){
	ASSERT_TRUE(validityHexadecimal("0046"));
	ASSERT_FALSE(validityHexadecimal("A"));
}
TEST(validityHexadecimal, MajorClause3){
	ASSERT_TRUE(validityHexadecimal("0130"));
	ASSERT_FALSE(validityHexadecimal("01H3"));
}
TEST(validityHexadecimal, MajorClause4){
	ASSERT_TRUE(validityHexadecimal("1D"));
	ASSERT_FALSE(validityHexadecimal("0G"));
}
// Logic based CACC criteria for SHLD command
TEST(SHLD, MajorClause1){
	registers[5] = "01";
	registers[6] = "AB";
	mem["2000"]="DUMMY";
	mem["2001"]="DUMMY";	
	SHLD("2000",registers,flag,mem);
	
	ASSERT_EQ(mem["2000"], registers[6]);
	ASSERT_EQ(mem["2001"], registers[5]);
	
	mem["2000"]="DUMMY";
	mem["2001"]="DUMMY";
	
	std::stringstream buffer;
	// Save cout's buffer here
	std::streambuf *sbuf = std::cout.rdbuf();

	// Redirect cout to our stringstream buffer or any other ostream
	std::cout.rdbuf(buffer.rdbuf());

	SHLD("400",registers,flag,mem);
	
	// When done redirect cout to its old self
	std::cout.rdbuf(sbuf);	
	
	ASSERT_NE(mem["2000"], registers[6]);
	ASSERT_NE(mem["2001"], registers[5]);
}
TEST(SHLD, MajorClause2){
	mem["2000"]="DUMMY";
	mem["2001"]="DUMMY";
	registers[5] = "01";
	registers[6] = "AB";
	SHLD("2000",registers,flag,mem);
	
	ASSERT_EQ(mem["2000"], registers[6]);
	ASSERT_EQ(mem["2001"], registers[5]);
	
	mem["2000"]="DUMMY";
	mem["2001"]="DUMMY";
	
	std::stringstream buffer;
	std::streambuf *sbuf = std::cout.rdbuf();
	std::cout.rdbuf(buffer.rdbuf());
	
	SHLD("AAZA",registers,flag,mem);
	
	std::cout.rdbuf(sbuf);
	
	ASSERT_NE(mem["2000"], registers[6]);
	ASSERT_NE(mem["2001"], registers[5]);
}
TEST(SHLD, MajorClause3){
	
	mem["2000"]="DUMMY";
	mem["2001"]="DUMMY";
	registers[5] = "01";
	registers[6] = "AB";
	SHLD("2000",registers,flag,mem);
	
	ASSERT_EQ(mem["2000"], registers[6]);
	ASSERT_EQ(mem["2001"], registers[5]);
	
	mem["2000"]="DUMMY";
	mem["2001"]="DUMMY";
	registers[5] = "";
	std::stringstream buffer;
	std::streambuf *sbuf = std::cout.rdbuf();
	std::cout.rdbuf(buffer.rdbuf());
	SHLD("2000",registers,flag,mem);
	
	std::cout.rdbuf(sbuf);
	
	ASSERT_NE(mem["2000"], registers[6]);
	ASSERT_NE(mem["2001"], registers[5]);
}
TEST(SHLD, MajorClause4){
	mem["2000"]="DUMMY";
	mem["2001"]="DUMMY";
	registers[5] = "01";
	registers[6] = "AB";
	SHLD("2000",registers,flag,mem);
	
	ASSERT_EQ(mem["2000"], registers[6]);
	ASSERT_EQ(mem["2001"], registers[5]);
	
	registers[6] = "";
	mem["2000"]="DUMMY";
	mem["2001"]="DUMMY";
	std::stringstream buffer;
	std::streambuf *sbuf = std::cout.rdbuf();
	std::cout.rdbuf(buffer.rdbuf());
	SHLD("2000",registers,flag,mem);
	std::cout.rdbuf(sbuf);
	
	ASSERT_NE(mem["2000"], registers[6]);
	ASSERT_NE(mem["2001"], registers[5]);
}
TEST(SHLD, MajorClause5){
	mem["2000"]="DUMMY";
	mem["2001"]="DUMMY";
	registers[5] = "01";
	registers[6] = "AB";
	SHLD("2000",registers,flag,mem);
	
	ASSERT_EQ(mem["2000"], registers[6]);
	ASSERT_EQ(mem["2001"], registers[5]);
	
	mem.clear();
	std::stringstream buffer;
	std::streambuf *sbuf = std::cout.rdbuf();
	std::cout.rdbuf(buffer.rdbuf());
	SHLD("2000",registers,flag,mem);
	std::cout.rdbuf(sbuf);
	
	ASSERT_NE(mem["2000"], registers[6]);
	ASSERT_NE(mem["2001"], registers[5]);
}

// Logic based CACC criteria for validityData
TEST(validityData, MajorClause1){
	ASSERT_TRUE(validityData("AB"));
	ASSERT_FALSE(validityData("100"));
}
TEST(validityData, MajorClause2){
	ASSERT_TRUE(validityData("FF"));
	ASSERT_FALSE(validityData("Z1"));
}
TEST(validityData, MajorClause3){
	ASSERT_TRUE(validityData("1A"));
	ASSERT_FALSE(validityData("1Z"));
}
int main(int argc, char **argv) {
	
	//Dummy data
	for(int i=0;i<7;i++)	registers[i]="";
	memset(flag,sizeof(flag),false);
	mem["1000"]="MOV A,B";
	
    	testing::InitGoogleTest(&argc, argv);
    	return RUN_ALL_TESTS();
}
