#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
using namespace std;
using namespace boost::algorithm;
using namespace boost;
ifstream myfile;
bool secondpass = false;
int module_length, module_number=1;
map<int, int> base_addr_map;
map<string, int> sym_map;
int instruction_counter;
int readDefList(){
    string line;
    int count, sym_addr;
    string sym;
    getline(myfile,line);
    trim(line);
    boost::tokenizer<> tok(line);
    vector<string> tokens(tok.begin(), tok.end());
    
    if(tokens.empty()) return 0;

    base_addr_map[module_number]= module_length;

    istringstream iss(tokens[0]);
    iss >> count;


    for(int i = 1; i <= count; i++) {
        sym = tokens[i*2 -1];
        sym_addr = atoi(tokens[i*2].c_str());
        sym_map[sym] = module_length + sym_addr;
      //  cout << sym <<  "  "  << sym_addr << endl; 
    }

    for( vector<string>::iterator it=tokens.begin(); it!= tokens.end(); it++) {
     //  cout << (*it)<< endl;
    }

}

int readUseList(vector<string> &used_symbols){
    string line;
    int count;
    string used_sym;
    getline(myfile,line);
    trim(line);
    boost::tokenizer<> tok(line);
    vector<string> tokens(tok.begin(), tok.end());
    
    if(tokens.empty()) return 0;
    istringstream iss(tokens[0]);
    iss >> count;


    for(int i = 1; i <= count; i++) {
        used_sym = tokens[i];
        used_symbols.push_back(used_sym);
       // cout << used_sym  << endl;
    }


}

int readInstList(vector<string> &used_symbols) {
    string line;
    int count, inst_addr;
    string inst;
    getline(myfile,line);
    trim(line);
    boost::tokenizer<> tok(line);
    vector<string> tokens(tok.begin(), tok.end());

    if(tokens.empty()) return 0;
    istringstream iss(tokens[0]);
    iss >> count;


    for(int i = 1; i <= count; i++) {
        inst = tokens[i*2 -1];
        inst_addr = atoi(tokens[i*2].c_str());
        
	if(secondpass) {
		if(inst == "R") {
			cout << setfill('0') << setw(3) << instruction_counter;
                        cout << " :   " << base_addr_map[module_number] + inst_addr << endl;
		}
		
		else if(inst == "E") {
			cout << setfill('0') << setw(3) << instruction_counter;
  			cout << "  :  " << (inst_addr - inst_addr%1000) + sym_map[used_symbols[inst_addr%1000]]<< endl;
		}
                else {
 			 cout << setfill('0') << setw(3) << instruction_counter;
                	cout << "  :  " <<  inst_addr << endl;
		}
	instruction_counter++;
	}

        module_length++;
     //   cout << inst <<  "  "  << inst_addr << endl;
    }


}

int create_module(){
    vector<string> used_symbols;
    readDefList();
    readUseList(used_symbols);
    readInstList(used_symbols);		
    module_number++;

    

    return 0;
}

int resolve_address() {
    vector<string> used_symbols;
    readDefList();
    readUseList(used_symbols);
    readInstList(used_symbols);
    module_number++;



    return 0;

}

int first_pass() {
   myfile.open("input-1", ios::in);
  if (myfile.is_open())
  {
    while(!myfile.eof()){
        create_module();
    }

     for( map<int, int>::iterator it=base_addr_map.begin(); it!= base_addr_map.end(); it++) {
     //  cout << (it)->first<< "  "<< (it)->second  <<endl;
       }
     cout << "SYMBOL TABLE"<<endl;

     for( map<string, int>::iterator it=sym_map.begin(); it!= sym_map.end(); it++) {
       cout << (it)->first<< "  "<< (it)->second  <<endl;
    }
    cout<<endl<<endl;

  }

  else cout << "Unable to open file";
  myfile.close();

}

int second_pass() {
     secondpass = true;
     module_number = 0;
     module_length = 0;
     myfile.open("input-1", ios::in);
  if (myfile.is_open())
  {
    while(!myfile.eof()){
        resolve_address();
    }
  }
  else cout << "Unable to open file";
  myfile.close();

}

int main () {

 first_pass();
 second_pass();
  return 0;
}



