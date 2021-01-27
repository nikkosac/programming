#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>
#define push push_back
#include <algorithm>
#include <iomanip>

std::string hexToBin(char c)
{
    // TODO handle default / error
    switch(toupper(c))
    {
        case '0': return "0000"; // hex 0 is 0000 in binary
        case '1': return "0001"; // hex 1 is 0001 in binary
        case '2': return "0010"; // hex 2 is 0010 in binary
        case '3': return "0011"; // hex 3 is 0011 in binary
        case '4': return "0100"; // hex 4 is 0100 in binary
        case '5': return "0101"; // hex 5 is 0101 in binary
        case '6': return "0110"; // hex 6 is 0110 in binary
        case '7': return "0111"; // hex 7 is 0111 in binary
        case '8': return "1000"; // hex 8 is 1000 in binary
        case '9': return "1001"; // hex 9 is 1001 in binary
        case 'A': return "1010"; // hex 10 is 1010 in binary
        case 'B': return "1011"; // hex 11 is 1011 in binary
        case 'C': return "1100"; // hex 12 is 1100 in binary
        case 'D': return "1101"; // hex 13 is 1101 in binary
        case 'E': return "1110"; // hex 14 is 1110 in binary
        case 'F': return "1111"; // hex 15 is 1111 in binary
    }
}

int vecFind(int key, std::vector<int> v){ //finding the key within a vector 
	if (std::find(v.begin(), v.end(), key) != v.end())
        return 1;
    else
        return 0;
 
}

int parseSym(std::vector<std::string> sym, std::unordered_map<int,std::string> &asym, std::unordered_map<int,std::string> &lit, std::vector<int> &adds,std::unordered_map<std::string,int> &bsym, std::vector<int> &addsb,std::unordered_map<std::string,std::string> &blit){
  bool f = true;
  for(int i=0;i<sym.size();i++){
    if(sym.at(i) == "Literal:"){
	  f=!f;
	  continue;
	}
	if(f){
	  std::string temp;
	  std::string val;
	  int addr;
	  for(int j=0;j<sym.at(i).size();j++){
	    while(sym.at(i).at(j) != ' '){ //looks through indexes of the string and if the index isnt a space push into string temp 
		  temp.push(sym.at(i).at(j));
		  j++;
		}
		while(sym.at(i).at(j)==' '){ //looks through indexes of the string and if the index is a space move to next index 
		  j++;
		}
		while(sym.at(i).at(j) != ' '){ //looks through indexes of the string and if the index isn't a space push into string val
		  val.push(sym.at(i).at(j));
		  j++;
		}
		break;
	  }
	  addr = std::stoi(val, 0, 16);
	  asym.emplace(addr,temp); //asym emplaces the address with the corresponding symbol in the unordered map
	  bsym.emplace(temp,addr); //bsym emplaces the symbol with the corresponding address in the unordered map
	  addsb.push(addr);
	}
	if(!f){
	  std::string temp;
	  std::string addy;
	  std::string name;
	  int j = 0;
	  while(sym.at(i).at(j)==' '){ //looks through indexes of the string and if the index is a space move to next index
		j++;
	  }
	  while(sym.at(i).at(j)!=' '){ //looks through indexes of the string and if the index isnt a space push into string temp 
	    name.push(sym.at(i).at(j));
		j++;
	  }
	  while(sym.at(i).at(j)==' '){ // looks through indexes of the string and if the index is a space move to next index 
		j++;
	  }
	  while(sym.at(i).at(j)!=' '){
		temp.push(sym.at(i).at(j));		  // looks through indexes of the string and if the index isnt a space move to next index
		j++;
	  }
	  while(sym.at(i).at(j)==' '){ // looks through indexes of the string and if the index is a space move to next index
		j++;
	  }
	  while(sym.at(i).at(j)!=' '){ // looks through indexes of the string and if the index isnt a space push into addy 
		j++;
	  }
	  while(sym.at(i).at(j)==' '){ // looks through indexes of the string and if the index is a space move to next index
		j++;
	  }
	  while(sym.at(i).at(j)!=' '){ // looks through indexes of the string and if the index isnt a space push into addy 
	    addy.push(sym.at(i).at(j));
		j++;
	  }
	  int val = std::stoi(addy,0,16);
	  asym.emplace(val,temp);
	  bsym.emplace(temp,val);
	  lit.emplace(val,temp);
	  blit.emplace(temp,name);
	  adds.push(val);
	  addsb.push(val);
	}
  }
  return 1;
}

std::string binToHex(std::string c){ 
  if(c == "00"){ //the binary number 00(00) is 0 in hex
    return "0";
  }
  if(c == "01"){ //the binary number of 01(00) is 4 in hex
   return "4";
  }
  if(c == "10"){ // the binary number of 10(00) is 8 in hex
   return "8";
  }
  if(c == "11"){ // the binary number of 11(00) is C in hex 
    return "C";
  }
  return "false";
}

int parse(std::string filename, std::vector<std::string> &file, std::vector<std::string> &sym){
  std::fstream input;
  std::string name;
  name = filename + ".obj";
  input.open(name); //open <filename>.obj 
    if (!input.is_open()) { //output error message
        std::cout << "Could not open file\n";
        return 0;
    }else {
      std::cout << "Using input file \"" << name<< "\" for the program" << "\n\n";
      std::string tp;
        while (getline(input, tp)) { //pushes line to file
          file.push(tp);
        }
      input.close();
    }
	name = filename + ".sym"; 
	input.open(name); //open <filename>.sym
	if (!input.is_open()) { //output error message 
        std::cout << "Could not open file\n";
        return 0;
    }else {
      std::cout << "Using input file \"" << name<< "\" for the symtable for the program" << "\n\n";
      std::string tp;
	  getline(input, tp);
	  getline(input, tp);
        while (getline(input, tp)) {
          if(tp!=""){ //if line is not empty push into sym
            sym.push(tp);
          }else{
			getline(input, tp);
			getline(input, tp);
			sym.push("Literal:");
		  }
        }
      input.close();
    }
    std::cout << "\nFinished using file \"" << name << "\" for the program" << "\n";
  return 1;
}

int parseHash(std::unordered_map<int,std::string> &instr, std::unordered_map<int,int> &type){
  std::fstream input;
  std::string in;
  std::string op;
  int sict;
  char temp;
  bool f = true;
  bool g = false;
  int value;
  input.open("instructions.txt"); //open instructions.txt file with op code mnemonic, op code, and format
    if (!input.is_open()) { //output error message
        std::cout << "Could not open file\n";
        return 0;
    }else {
      std::cout << "Using input file \"" << "instructions.txt"<< "\" for the program" << "\n\n";
      std::string tp;
        while (input.get(temp)) { //input grabs chars
          if(temp == ','){
            if(!f){
              value = std::stoi(op, 0, 16);
              instr.emplace(value,in); //emplace the value with the corresponding instruction
              input.get(temp);
              in="";
              in.push(temp);
              sict=std::stoi(in, 0, 10);
              type.emplace(value,sict);
              if(!input.get(temp)){
                break;
              }
              in="";
              op="";
            }
            f=!f;
            continue;
          }
          if(f){
            in.push(temp);
          }else{
            op.push(temp);
          }
        }
      input.close();
      std::cout << "\nFinished using file \"" << "instructions.txt" << "\" for the program" << "\n";
    }
  return 1;
}

int getLength(int type,std::string flags,std::string next,int &PC){
  if(type == 1 || type == 0){ //format 3/4
	if(next.at(3) == '0'){
	  PC+=3; //3 bytes
	  return 4;
	}
	PC += 4; //4 bytes
	return 6;
  }
  if(type == 2){ //format 2
	PC += 2; //2 bytes
	return 1;
  }
  if(type == 3){ //format 1
	PC += 1; //1 byte
	return 0;
  }
  return -1;
}


//deciphers which addressing style the opcode uses
int flagHandler(std::string &fin,std::string opcode,int loc, std::unordered_map<int,std::string> asym,std::unordered_map<int,std::string> lit,std::string flags,std::string next,int PC,int type,std::string &out,std::unordered_map<std::string,int> bsym,int &BASE,std::unordered_map<int,std::string> instr){
  int i = loc + 1;
  std::string hold;
  bool hash = false;
  while(i<(type + loc)){
	hold.push(opcode.at(i));
    i++;
  }
  int TA = std::stoi(hold,0,16);
  if(flags == "00" || flags == "11"){ //if n and i flags are 00 or 11 simple addressing 
    if(next.at(1) == '0' && next.at(2) == '0'){ //if b and p flags are 00 direct addressing
	  out = asym[TA];
	}
    if(next.at(1) == '0' && next.at(2) == '1'){ //if b and p flags are 01 PC relative addressing
	  out = asym[PC + TA];
	  if(out == ""){
		int b = 4095;
		b = b - TA + 1;
		out = asym[PC -b];
	  }
    }
    if(next.at(1) == '1' && next.at(2) == '0'){ // if b and p flags are 10 base relative addressing
	  out = asym[BASE + TA];
	  if(out == ""){
		int b = 4095;
		b = b - TA + 1;
		out = asym[BASE -b];
	  }
    }
  }
  if(flags == "01"){ //if n and i flags are 01 immediate addressing
	hash = true;
    if(next.at(1) == '0' && next.at(2) == '0'){ //if b and p flags are 00 direct addressing
	  out = hold;
	}
    if(next.at(1) == '0' && next.at(2) == '1'){ //if b and p flags are 01 PC relative addressing
	  out = std::to_string(PC + TA);
    }
    if(next.at(1) == '1' && next.at(2) == '0'){ // if b and p flags are 10 base relative addressing
	  out = std::to_string(BASE + TA);
    }
  }
  if(flags == "10"){ // if n and i flags are 10 indirect addressing 
    if(next.at(1) == '0' && next.at(2) == '0'){ //if b and p flags are 00 direct addressing
	  out = std::to_string(bsym[asym[TA]]);
	}
    if(next.at(1) == '0' && next.at(2) == '1'){ //if b and p flags are 01 PC relative addressing
       out = std::to_string(bsym[asym[TA+PC]]);
	  if(out == ""){
		int b = 4095;
		b = b - TA + 1;
		out = std::to_string(bsym[asym[PC-b]]);
	  }
    }
    if(next.at(1) == '1' && next.at(2) == '0'){ // if b and p flags are 10 base relative addressing
	    out = std::to_string(bsym[asym[BASE+TA]]);
	  if(out == ""){
		int b = 4095;
		b = b - TA + 1;
		out = std::to_string(bsym[asym[BASE-b]]);
	  }
    }
  }
  if(fin == "LDB"){
	BASE = stoi(out,0,16);
  }
  if(next.at(3)=='1'){ //if e flag is 1
	if(flags == "01"){
	  out = asym[std::stoi(out,0,16)];
	}
    fin = "+" + fin;
  }else{
	out.erase(0, out.find_first_not_of('0'));
	if(out == ""){
	  out ="0";
	}
  }
  if(next.at(0)=='1'){ // if x flag is 1 indexed addressing
    out = out + ",X";
  }
  if(hash){
	out = "#"+ out;
  }
  if(fin == "RSUB"){
	out = "";
  }
  return 1;
}


std::vector<int> convertToASCII(std::string letter) //conversion to ASCII 
{
	std::vector<int> out;
    for (int i = 0; i < letter.length(); i++)
    {
		char x = letter.at(i);
        int b = int(x);
		out.push(b);
    }
	return out;
}

int decipher(std::string filename,std::vector<std::string> file,std::unordered_map<int,std::string> instr, std::unordered_map<int,int> type,std::unordered_map<int,std::string> asym,std::unordered_map<int,std::string> lit,std::vector<int>adds,std::unordered_map<std::string,int> bsym,std::vector<int>addsb,std::unordered_map<std::string,std::string> &blit){
  std::ofstream output;
  std::ofstream sickout;
  std::string name; //name of file
  std::string name1; //name of file
  int skip = 0; //number of bytes to skip at the end in the case of literal usage
  int PC = 0;
  std::string length; //length of the file
  name = filename + ".lis"; 
  name1 = filename + ".sic";
  output.open(name); //open <filename>.lis
  sickout.open(name1); //open <filename>.sic
  if (!output.is_open()) { //output error message
        std::cout << "Could not open out file\n";
        return 0;
  }
  if (!sickout.is_open()) { //output error message
	std::cout << "could not open sic file\n";
	return 0;
  }
  else {
  std::cout << "output files launched"; 
  int hold;
  std::string name; //name of program
  int BASE = 0;//base location
  char temp;
  int i = 1;
  std::string opcode;

  //handles Object file until Text records are reached
  while(file.at(0).at(i) != ' '){ //if file at index isnt a space push into name
	name.push(file.at(0).at(i));
	i++;
  }
  while(file.at(0).at(i) == ' '){ //if file at index is a space move to next index
	i++;
  }
  while(file.at(0).at(i)=='0'){ //if file at index is a 0 move to next index
	i++;
  }
  while(i < file.at(0).size()){ //gets the length of file
	length.push(file.at(0).at(i));
	i++;
  }
  i = 1;
  output<< std::right << std::setfill('0') << std::setw(4) << "0"<< std::setfill(' ') << std::setw(2) << " " << name << std::right<< std::setw(11) << "START" << std::setw(4) << "0" << "\n"; //output to lis file with format
  sickout<< name << std::right<< std::setw(11) << "START" << std::setw(4) << "0" << "\n"; //output to sic file with format
  
  //handles text records portion of opcode
  while(file.at(i).at(0) == 'T'){
	std::string var;
	bool f = true;
	std::string address = "0";
	std::string tLength = "0";
	bool start = false;
	for(int j = 1; j < 7; j++){
	  if(file.at(i).at(j) != '0'){ //if file at index is not 0 
		start = true;
	  }
	  if(start){
		address.push(file.at(i).at(j));
	  }
	}
	tLength.push(file.at(i).at(7)); //length of the text row
	tLength.push(file.at(i).at(8));
	int j=9;//current location in TextRow
	int _length;//length of current opcode
	int holdd;
	std::string fin; //the assembler command
	std::string done;
	bool LTORG = true;
	while(j < file.at(i).size()){
	  if(file.at(i+1).at(0) != 'T' && (file.at(i).size() - j) < skip){
		break;
	  }
	  if(!f){
		std::string holder;
		holder = lit[PC - (_length/2) -1]; //holds the literal
		output <<std::right << std::setfill('0') << std::setw(4) << std::hex << holdd <<std::right<<std::setfill(' ') << std::setw(11) << " " <<fin<< std::setw(10) <<holder<< std::setw(11) <<done<<"\n"; //output to lis file with format
		output <<std::right << std::setfill('0') << std::setw(4) << PC << std::right << std::setfill(' ') << std::setw(11) << " " << "*" << std::setw(12)<< holder << std::setw(6); //output to lis file with format
		if(holder.at(1) == 'C'){
			j+=(holder.length() -4)*2;
			PC += (holder.length() -4);
		}
		std::cout<<holder;
		output << file.at(i).at(j); //output to lis file with format
		sickout <<std::right << std::setfill(' ') << std::setw(12) << fin<< std::setw(11) <<holder<< "\n"; //output to sic file with format
		output << file.at(i).at(j)<<"\n"; //output to lis file with format
		j+=(holder.length() -4);
		f=!f;
		PC += (holder.length() -4)/2; //literal line adds one to address 
		continue;
	  }
	  if(vecFind(PC,adds)){
		output <<std::right << std::setfill('0') << std::setw(4) << std::hex << PC << std::right<< std::setfill(' ') << std::setw(11) << " " << "LTORG\n"; //output to lis file with format
		if(LTORG){
		  sickout << std::right<< std::setfill(' ') << std::setw(9) << " " << "LTORG\n"; //output to sic file with format
		  LTORG = false;
		}
		f = false;
	  }
	  std::string flags; //n and i bits
	  std::string _command; //second part of opcode
	  std::string command; //first part of opcode
	  std::string test;
	  int hold;
	  command.push(file.at(i).at(j));
	  test.push(file.at(i).at(j));
	  j++;
	  test.push(file.at(i).at(j));
	  flags = hexToBin(file.at(i).at(j)); //convert flags from hex to bin
	  _command = flags;
	  flags = flags.substr(2,2);  //grab substring
	  _command.pop_back();
	  _command.pop_back();
	  command = command + binToHex(_command);

	  //seperates the command from the flags
	  hold = std::stoi(command, 0, 16); //int value of the command
	  holdd = PC; //holdd has value of PC
	  var = "";
	  if(asym[PC]!=""){
	    //if this location in the program uses a symbol from the symbol table then it sets the variable for output
	    var = asym[PC]; //gets symbol by using PC address
	  }
	  j++;
	  std::string next= hexToBin(file.at(i).at(j));
	  int format = type[hold];
	  _length = getLength(format,flags,next,PC);
	  std::string out;
	  fin = instr[hold];
	  if(_length == 6 || _length == 4){
		flagHandler(fin,file.at(i),j,asym,lit,flags,next,PC,_length,out,bsym,BASE,instr); //handles the object code based on the flags
	  }
	  if(_length == 0){
		out = "";
	  }
	  test = test + file.at(i).substr(j,_length); //the full operation code

	  //seperate output if LDB is the command
	  if(fin == "LDB"||fin=="+LDB"){
		  output << std::setfill('0') << std::setw(4) << std::hex << holdd << std::setfill(' ') << std::setw(2) << " " <<var<<std::setw(8) << std::right <<fin<<std::setw(6)<< std::right <<out<<std::right << std::setw(14) <<test<<"\n"; //output to lis file with format
		  sickout << var<<std::setw(7) << std::right <<fin<<std::setfill(' ') << std::setw(6)<< std::right <<out<<"\n"; //output to sic file with format
		  if(out.at(0) == '#') {
			  out = out.substr(1,out.length());
		  }
		  output << std::setfill('0') << std::setw(4) << std::hex << PC << std::setfill(' ') << std::setw(2) << " " <<' '<<std::setw(8) << std::right <<"BASE"<<std::setw(6)<< std::right <<out<<std::right << std::setw(14) <<' '<<"\n"; //output to lis file with format

		  sickout <<std::setw(8) << std::right <<"BASE"<<std::setw(6)<< std::right <<out<<std::right << std::setw(14) <<' '<<"\n";
	  }else{
		if(f){
		  //if there is a literal used it logs how many bits to skip at the end
		  if(var == "" && out != ""){
			var = blit[out];
				if(out.at(1)=='C'){
					int mad = out.length();
					skip += (2 * (mad - 3));
				}else{
					int mad = out.length();
					skip += (mad - 3);
				}
		  }
		  output << std::setfill('0') << std::setw(4) << std::hex << holdd << std::setfill(' ') << std::setw(2) << " " <<var<<std::setw(8) << std::right <<fin<<std::setw(6)<< std::right <<out<<std::right << std::setw(14) <<test<<"\n"; //output to lis file with format
		  sickout << var<<std::setw(7) << std::right <<fin<<std::setfill(' ') << std::setw(6)<< std::right <<out<<"\n"; //output to sic file with format
		}
	  }
	  done = test;
	  j+=_length;
	}
	i++; 
  }
  }
  bool go = false;
  int i;
  for(i=0; i<addsb.size();i++){
	if(addsb.at(i) >= PC){
	  go = true;
	  break;
	}
  }
  if(go){
	int temp;
	for(i; i<(addsb.size()-1 - adds.size());i++){
	  temp = addsb.at(i+1) - addsb.at(i);
	  if(temp % 3 == 0){ //checks to see if divisible by 3 for w or b
		  output << std::right<< std::setfill('0') << std::setw(4) << std::hex << addsb.at(i) << std::setfill(' ') << std::setw(2) << " " <<asym[addsb.at(i)]<< std::setw(8) <<std::right <<"RESW"<<std::left << std::setfill(' ') << std::setw(10) << std::dec<<temp/3<<"\n"; //output to lis file with format
	  	  sickout << std::left << asym[addsb.at(i)]<< std::setw(8) <<std::right <<"RESW"<< std::setfill(' ') << std::setw(6) << std::dec<<temp/3<<"\n"; //output to sic file with format

	  }else{
		  output << std::right<< std::setfill('0') << std::setw(4) << std::hex << addsb.at(i) << std::setfill(' ') << std::setw(2) << " " <<asym[addsb.at(i)]<< std::setw(8) <<"RESB"<<" "<<std::setw(4) << std::dec<<temp<<"\n"; //output to lis file with format
	  	  sickout << asym[addsb.at(i)]<< std::setw(8) <<"RESB"<<" "<<std::setw(4) << std::dec<<temp<<"\n"; //output to sic file with format
	  }
	}
	if(PC < adds.at(0)){
	  temp = adds.at(0) - addsb.at(i);
	}else{
	  temp = std::stoi(length,0,16) - addsb.at(i);
	}
	if(temp % 3 == 0){ //checks to see if divisible by 3 for w or b
		output << std::right<< std::setfill('0') << std::setw(4) << std::hex << addsb.at(i) << std::setfill(' ') << std::setw(2) << " " <<asym[addsb.at(i)]<< std::setw(8) <<std::right <<"RESW"<<std::left << std::setfill(' ') << std::setw(10) << std::dec<<temp/3<<"\n"; //output to lis file with format
	   	sickout << std::left << asym[addsb.at(i)]<< std::setw(8) << std::right <<"RESW" << std::setfill(' ') << std::setw(6) << std::dec<<temp/3<<"\n"; //output to sic file with format

	}else{
		output << std::right<< std::setfill('0') << std::setw(4) << std::hex << addsb.at(i) << std::setfill(' ') << std::setw(2) << " " <<asym[addsb.at(i)]<< std::setw(8) <<"RESB"<<" "<<std::setw(4) << std::dec<<temp<<"\n"; //output to lis file with format
		sickout << asym[addsb.at(i)]<< std::setw(8) <<"RESB"<<" "<<std::setw(4) << std::dec<<temp<<"\n"; //output to sic file with format
	}
  }
  for(int j = 0; j< adds.size();j++){
	  if(PC < adds.at(j)){
		  std::string temp;
		  std::string here = lit[adds.at(j)];
		  for(int f = 3; f < here.length() -1;f++){
			temp.push(here.at(f));
		  }
		  if(here.at(1) == 'X'){
			  sickout<< here<<std::setw(6)<< std::right <<' '<<std::right << std::setw(14) <<temp<<"\n"; 
			  output << std::right<< std::setfill('0') << std::setw(4) << std::hex << adds.at(j) << std::setfill(' ') << std::setw(2) << " " <<'*'<<std::setw(8) << std::right <<here<<std::setw(6)<< std::right <<' '<<std::right << std::setw(14) <<temp<<"\n"; //output to lis file with format
		  }else{
			std::vector<int> hold;
			hold = convertToASCII(temp);
			output << std::right<< std::setfill('0') << std::setw(4) << std::hex << adds.at(j) << std::setfill(' ') << std::setw(2) << " " <<'*'<<std::setw(8) << std::right <<here; //output to lis file with format
			sickout<< std::setfill(' ') << std::setw(8) << "*" << std::setw(10)<< std::right << here<< "\n"; 
			for(int l = 0; l < hold.size(); l++){
			  output<< std::hex << hold.at(l); //output to lis file with format
			}
			output<<'\n';
		  }
	  }
  }
  output << std::right<< std::setfill('0') << std::setw(4) << std::hex << length << std::setfill(' ') << std::setw(14) << "END" << std::setw(9) << asym[addsb.at(0)]<<"\n"; //output to lis file with format
  sickout << std::right << std::setw(12) << "END"<< std::setw(9) << asym[addsb.at(0)]<<"\n"; //output to sic file with format
  //output for end files
  sickout.close();
  output.close();
  return 1;
}

int main(int argc, char* argv[])
{
  std::fstream input;
  std::ofstream output;
  std::vector<std::string> file;
  std::vector<std::string> sym;//vector of the symbol table
  std::vector<int> adds;//addresses of the symbol table
  std::vector<int> addsb;//addresses of the literals
  std::unordered_map<int,std::string> instr;//the opcodes and threir assembler directive counterparts
  std::unordered_map<int,int> type;//the opcode and the format the opcode can be in
  std::unordered_map<int,std::string> asym;//the address and the symbol table variable
  std::unordered_map<std::string,int> bsym;//teh symbol table variable and its address
  std::unordered_map<std::string,std::string> blit;//the literal value an dliteral name
  std::unordered_map<int,std::string> lit;//the literal address and literal value
  if(argc > 1){
    if(!parse(argv[1],file,sym)){ //parses the input file
      return 0;
    }
    if(!parseHash(instr,type)){//parses the instruction file made by my group
      return 0;
    }
	if(!parseSym(sym,asym,lit,adds,bsym,addsb,blit)){ //parses the symbol table vector and makes it into hashmaps
	  return 0;
	}
    if(decipher(argv[1],file,instr,type,asym,lit,adds,bsym,addsb,blit)){//deciphers every line of the object
          std::cout <<"\nSuccess\n";					// code and translates into sic/lis file
	}
  }else{
    std::cout <<"\nNo file provided\n";
  }
  return 0;
}
