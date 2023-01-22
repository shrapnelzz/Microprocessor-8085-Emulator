import re
with open('/Users/shreyasharinambiar/Desktop/gitgud/8085-Emulator-master/test/tests.cpp', 'r') as f:
    code = f.read()

old_streq = """	strcpy(map_mem,mem["2000"].c_str());
	strcpy(map_mem1,mem["2001"].c_str());
	strcpy(reg,registers[6].c_str());
	strcpy(reg1,registers[5].c_str());
	
	ASSERT_STREQ(map_mem,reg);
	ASSERT_STREQ(map_mem1,reg1);"""
new_streq = """	ASSERT_EQ(mem["2000"], registers[6]);
	ASSERT_EQ(mem["2001"], registers[5]);"""

old_strne = """	strcpy(map_mem,mem["2000"].c_str());
	strcpy(map_mem1,mem["2001"].c_str());
	strcpy(reg,registers[6].c_str());
	strcpy(reg1,registers[5].c_str());
	
	ASSERT_STRNE(map_mem,reg);
	ASSERT_STRNE(map_mem1,reg1);"""
new_strne = """	ASSERT_NE(mem["2000"], registers[6]);
	ASSERT_NE(mem["2001"], registers[5]);"""

code = code.replace(old_streq, new_streq)
code = code.replace(old_strne, new_strne)

code = code.replace("char map_mem[100],map_mem1[100],reg[100],reg1[100];\\n", "")

with open('/Users/shreyasharinambiar/Desktop/gitgud/8085-Emulator-master/test/tests.cpp', 'w') as f:
    f.write(code)
