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
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
    }
}

int vecFind(int key, std::vector<int> v){
	if (std::find(v.begin(), v.end(), key) != v.end())
        return 1;
    else
        return 0;
 
}

int parseSym(std::vector<std::string> sym, std::unordered_map<int,std::string> &asym, std::unordered_map<int,std::string> &lit, std::vector<int> &adds,std::unordered_map<std::string,int> &bsym, std::vector<int> &addsb){
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
	    while(sym.at(i).at(j) != ' '){
		  temp.push(sym.at(i).at(j));
		  j++;
		}
		while(sym.at(i).at(j)==' '){
		  j++;
		}
		while(sym.at(i).at(j) != ' '){
		  val.push(sym.at(i).at(j));
		  j++;
		}
		break;
	  }
	  addr = std::stoi(val, 0, 16);
	  asym.emplace(addr,temp);
	  bsym.emplace(temp,addr);
	  addsb.push(addr);
	  std::cout<<addr<<' '<<temp<<'\n';
	}
	if(!f){
	  std::string temp;
	  std::string addy;
	  int j = 0;
	  while(sym.at(i).at(j)==' '){
		j++;
	  }
	  while(sym.at(i).at(j)!=' '){
	    temp.push(sym.at(i).at(j));
		j++;
	  }
	  while(sym.at(i).at(j)==' '){
		j++;
	  }
	  while(sym.at(i).at(j)!=' '){
		j++;
	  }
	  while(sym.at(i).at(j)==' '){
		j++;
	  }
	  while(sym.at(i).at(j)!=' '){
	    addy.push(sym.at(i).at(j));
		j++;
	  }
	  int val = std::stoi(addy,0,16);
	  lit.emplace(val,temp);
	  adds.push(val);
	  std::cout<<val<<' '<<temp<<'\n';
	}
  }
  return 1;
}

std::string binToHex(std::string c){
  if(c == "00"){
    return "0";
  }
  if(c == "01"){
   return "4";
  }
  if(c == "10"){
   return "8";
  }
  if(c == "11"){
    return "C";
  }
  return "false";
}

int parse(std::string filename, std::vector<std::string> &file, std::vector<std::string> &sym){
  std::fstream input;
  std::string name;
  name = filename + ".obj";
  input.open(name);
    if (!input.is_open()) {
        std::cout << "Could not open file\n";
        return 0;
    }else {
      std::cout << "Using input file \"" << name<< "\" for the program" << "\n\n";
      std::string tp;
        while (getline(input, tp)) {
          file.push(tp);
		  std::cout<<tp;
        }
      input.close();
    }
	name = filename + ".sym";
	input.open(name);
	if (!input.is_open()) {
        std::cout << "Could not open file\n";
        return 0;
    }else {
      std::cout << "Using input file \"" << name<< "\" for the symtable for the program" << "\n\n";
      std::string tp;
	  getline(input, tp);
	  getline(input, tp);
        while (getline(input, tp)) {
          if(tp!=""){
            sym.push(tp);
			std::cout<<tp;
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
  input.open("instructions.txt");
    if (!input.is_open()) {
        std::cout << "Could not open file\n";
        return 0;
    }else {
      std::cout << "Using input file \"" << "instructions.txt"<< "\" for the program" << "\n\n";
      std::string tp;
        while (input.get(temp)) {
          if(temp == ','){
            if(!f){
              value = std::stoi(op, 0, 16);
              instr.emplace(value,in);
              std::cout<<value<<in<<'\n';
              input.get(temp);
              in="";
              in.push(temp);
              sict=std::stoi(in, 0, 10);
              type.emplace(value,sict);
              std::cout<<sict;
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
  if(type == 1 || type == 0){
	if(next.at(3) == '0'){
	  PC+=3;
	  return 4;
	}
	PC += 4;
	return 6;
  }
  if(type == 2){
	PC += 2;
	return 1;
  }
  if(type == 3){
	PC += 1;
	return 0;
  }
  return -1;
}

int flagHandler(std::string &fin,std::string opcode,int loc, std::unordered_map<int,std::string> asym,std::unordered_map<int,std::string> lit,std::string flags,std::string next,int PC,int type,std::string &out,std::unordered_map<std::string,int> bsym,int &BASE,std::unordered_map<int,std::string> instr){
  int i = loc + 1;
  std::string hold;
  bool hash = false;
  while(i<(type + loc)){
	hold.push(opcode.at(i));
    i++;
  }
  int TA = std::stoi(hold,0,16);
  if(flags == "00" || flags == "11"){
    if(next.at(1) == '0' && next.at(2) == '0'){
	  out = asym[TA];
	}
    if(next.at(1) == '0' && next.at(2) == '1'){
	  out = asym[PC + TA];
	  if(out == ""){
		int b = 4095;
		b = b - TA + 1;
		out = asym[PC -b];
	  }
    }
    if(next.at(1) == '1' && next.at(2) == '0'){
	  out = asym[BASE + TA];
	  if(out == ""){
		int b = 4095;
		b = b - TA + 1;
		out = asym[BASE -b];
	  }
    }
  }
  if(flags == "01"){
	hash = true;
    if(next.at(1) == '0' && next.at(2) == '0'){
	  out = hold;
	}
    if(next.at(1) == '0' && next.at(2) == '1'){
	  out = std::to_string(PC + TA);
    }
    if(next.at(1) == '1' && next.at(2) == '0'){
	  out = std::to_string(BASE + TA);
    }
  }
  if(flags == "10"){
    if(next.at(1) == '0' && next.at(2) == '0'){
	  out = std::to_string(bsym[asym[TA]]);
	}
    if(next.at(1) == '0' && next.at(2) == '1'){
       out = std::to_string(bsym[asym[TA+PC]]);
	  if(out == ""){
		int b = 4095;
		b = b - TA + 1;
		out = std::to_string(bsym[asym[PC-b]]);
	  }
    }
    if(next.at(1) == '1' && next.at(2) == '0'){
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
  if(next.at(3)=='1'){
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
  if(next.at(0)=='1'){
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

int decipher(std::string filename,std::vector<std::string> file,std::unordered_map<int,std::string> instr, std::unordered_map<int,int> type,std::unordered_map<int,std::string> asym,std::unordered_map<int,std::string> lit,std::vector<int>adds,std::unordered_map<std::string,int> bsym,std::vector<int>addsb){
  std::ofstream output;
  std::string name; 
  int PC = 0;
  std::string length;
  name = filename + ".lis";
  output.open(name);
  if (!output.is_open()) {
        std::cout << "Could not open out file\n";
        return 0;
  }
  else {
  std::cout << "output file launched"; 
  int hold;
  std::string name;
  int BASE = 0;
  char temp;
  int i = 1;
  std::string opcode;
  while(file.at(0).at(i) != ' '){
	name.push(file.at(0).at(i));
	i++;
  }
  while(file.at(0).at(i) == ' '){
	i++;
  }
  while(file.at(0).at(i)=='0'){
	i++;
  }
  while(i < file.at(0).size()){
	length.push(file.at(0).at(i));
	i++;
  }
  std::cout<<name<<' '<<length<<'\n';
  i = 1;
  output<<"0 "<<name<<" START 0\n";
  while(file.at(i).at(0) == 'T'){
	std::string var;
	bool f = true;
	std::cout<<file.at(i)<<'\n';
	std::string address = "0";
	std::string tLength = "0";
	bool start = false;
	for(int j = 1; j < 7; j++){
	  if(file.at(i).at(j) != '0'){
		start = true;
	  }
	  if(start){
		address.push(file.at(i).at(j));
	  }
	}
	tLength.push(file.at(i).at(7));
	tLength.push(file.at(i).at(8));
	int j=9;
	int _length;
	int holdd;
	std::string fin;
	std::string done;
	while(j < file.at(i).size()){
	  if(!f){
		std::string holder;
		holder = lit[PC - (_length/2) -1];
		output <<std::hex << holdd <<" "<<fin<<" "<<holder<<" "<<done<<"\n";
		output <<PC<<" * "<<holder << " ";
		output <<file.at(i).at(j);
		j++;
		output <<file.at(i).at(j)<<'\n';
		j++;
		f=!f;
		PC += 1;
		continue;
	  }
	  if(vecFind(PC,adds)){
		output << std::hex << PC << " LTORG\n";
		f = false;
	  }
	  std::string flags;
	  std::string _command;
	  std::string command;
	  std::string test;
	  int hold;
	  command.push(file.at(i).at(j));
	  test.push(file.at(i).at(j));
	  j++;
	  test.push(file.at(i).at(j));
	  flags = hexToBin(file.at(i).at(j));
	  _command = flags;
	  flags = flags.substr(2,2);
	  _command.pop_back();
	  _command.pop_back();
	  command = command + binToHex(_command);
	  hold = std::stoi(command, 0, 16);
	  holdd = PC;
	  var = "";
	  if(asym[PC]!=""){
	    var = asym[PC];
	    std::cout<<var<<"herherherh" << PC<<"\n";
	  }
	  j++;
	  std::string next= hexToBin(file.at(i).at(j));
	  int format = type[hold];
	  _length = getLength(format,flags,next,PC);
	  std::string out;
	  fin = instr[hold];
	  if(_length == 6 || _length == 4){
		flagHandler(fin,file.at(i),j,asym,lit,flags,next,PC,_length,out,bsym,BASE,instr);
	  }
	  if(_length == 0){
		out = "";
	  }
	  test = test + file.at(i).substr(j,_length);
	  if(next.at(1) == '1'){
		  output <<std::hex << holdd <<" BASE\n";
		  output <<std::hex << holdd <<" "<<var<<" "<<fin<<" "<<out<<" "<<test<<"\n";
		  output <<std::hex << PC <<" NOBASE\n";
		  
	  }else{
		if(f){
		  output <<std::hex << holdd <<" "<<var<<" "<<fin<<" "<<out<<" "<<test<<"\n";
		}
	  }
	  std::cout<<test<<'\n';
	  done = test;
	  j+=_length;
	}
	i++; 
  }
  }
  std::cout<<"help\n";
  bool go = false;
  int i;
  for(i=0; i<addsb.size();i++){
	std::cout<<addsb.at(i)<<" "<<PC;
	if(addsb.at(i) >= PC){
	  go = true;
	  break;
	}
  }
  if(go){
	int temp;
	for(i; i<(addsb.size()-1);i++){
	  temp = addsb.at(i+1) - addsb.at(i);
	  if(temp % 3 == 0){
		  output <<std::hex << addsb.at(i) <<" "<<asym[addsb.at(i)]<<" "<<"RESW"<<" "<<std::dec<<temp/3<<"\n";
	  }else{
		  output <<std::hex << addsb.at(i) <<" "<<asym[addsb.at(i)]<<" "<<"RESB"<<" "<<std::dec<<temp<<"\n";
	  }
	}
	temp = std::stoi(length,0,16) - addsb.at(i);
	if(temp % 3 == 0){
		output <<std::hex << addsb.at(i) <<" "<<asym[addsb.at(i)]<<" "<<"RESW"<<" "<<std::dec<<temp/3<<"\n";
	}else{
		output <<std::hex << addsb.at(i) <<" "<<asym[addsb.at(i)]<<" "<<"RESB"<<" "<<std::dec<<temp<<"\n";
	}
  }
  output << "end "<<asym[addsb.at(0)]<<"\n";
  output.close();
  return 1;
}

int main(int argc, char* argv[])
{
  std::fstream input;
  std::ofstream output;
  std::vector<std::string> file;
  std::vector<std::string> sym;
  std::vector<int> adds;
  std::vector<int> addsb;
  std::unordered_map<int,std::string> instr;
  std::unordered_map<int,int> type;
  std::unordered_map<int,std::string> asym;
  std::unordered_map<std::string,int> bsym;
  std::unordered_map<int,std::string> lit;
  if(argc > 1){
    if(!parse(argv[1],file,sym)){
      return 0;
    }
    if(!parseHash(instr,type)){
      return 0;
    }
	if(!parseSym(sym,asym,lit,adds,bsym,addsb)){
	  return 0;
	}
    if(decipher(argv[1],file,instr,type,asym,lit,adds,bsym,addsb)){
	  std::cout <<"Success\n";
	}
  }else{
    std::cout <<"No file provided\n";
  }
  return 0;
}
