#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
using namespace std;
using namespace boost::algorithm;
using namespace boost;

typedef boost::tokenizer<boost::char_separator<char> > my_tokenizer;
ifstream myfile;
bool secondpass = false, module_end = true;
int module_length, module_number=1;
map<int, int> base_addr_map; // To store the base address of each module
map<int, int> module_length_map; // To store the length of each module
map<string, int> sym_map; // The main symbol table
int instruction_counter;
list<string> tokens; // The tokens that is passed around the methods for processing
list<string> used_symbols; // The symbols that are used in the current module
list<string> def_symbols; // The symbols that are defined in the current module
vector<string> mod_def_symbols;
vector<string> sym_list; // used to maintain order of symbols as map sorts the key
vector<string> w_list; // Warnings list
int MACHINE_SIZE = 512;
int linenumber, lineoffset; // line number and the offset
const char* FILE_NAME = "";
string line;
int current_list;
bool flip = true;
char i_addr[4] = {'A', 'E', 'I', 'R'}; // Four different types of addresses possible

/* Prints the Instruction set errors */
void _printInstErrors(string type, string err_code, string sym) {
	static map<string, string> R_errstr;
	static map<string, string> E_errstr;
	static map<string, string> A_errstr;
	R_errstr["EXCEEDS_MOD_SIZE"] =  "Error: Relative address exceeds module size; zero used";
	E_errstr["EXCEEDS_USELIST_LENGTH"] = "Error: External address exceeds length of uselist; treated as immediate";
	E_errstr["SYM_NOT_DEFINED"] = "Error: " + sym + " is not defined; zero used";
	A_errstr["EXCEEDS_MACHINE_SIZE"] = "Error: Absolute address exceeds machine size; zero used";
	
	cout << " ";
	if(type == "R")
		cout << R_errstr[err_code];
	else if(type == "E")
		cout << E_errstr[err_code];
	else if(type == "A")
		cout << A_errstr[err_code];
}

/* Registers the warnings to be printed at the end of the module/first pass */
void _registerWarnings(vector<string> &w_list, string w_code, int module_number, string sym) {
	if(w_code == "DEF_NOT_USED")
		w_list.push_back("Warning: Module " + boost::lexical_cast<string>(module_number) + ": " + sym + " was defined but never used");
	else if(w_code == "USELIST_NOT_USED")
		 w_list.push_back("Warning: Module " + boost::lexical_cast<string>(module_number) + ": " + sym + " appeared in the uselist but was not actually used");

}

/* Prints the warnigns that are registered by the first pass handler */
void _printWarnings(vector<string> &w_list) {
	for( vector<string>::iterator it=w_list.begin(); it!= w_list.end(); it++) {
       cout << (*it) << endl;
    }
	w_list.clear();
}

/* Prints the parse errors */
void __parseerror(int errcode, int linenum, int lineoffset) {
	static const string errstr[] = {
	"NUM_EXPECTED", // Number expect
	"SYM_EXPECTED", // Symbol Expected
	"ADDR_EXPECTED", // Addressing Expected
	"SYM_TOLONG", // Symbol Name is to long
	"TO_MANY_DEF_IN_MODULE", // > 16
	"TO_MANY_USE_IN_MODULE", // > 16
	"TO_MANY_INSTR" // total num_instr exceeds memory size (512)
	};
	cout << "Parse Error line " + boost::lexical_cast<string>(linenum) + " offset " + boost::lexical_cast<string>(lineoffset) + ": " + errstr[errcode] << endl;
	exit(0);
}

/* Prints the memory map in the second pass handler */
void __printMemoryMap(int address, string err_msg) {
	cout << setfill('0') << setw(3) << instruction_counter;
	
	cout << ": " << setw(4) << address;
	if(!err_msg.empty())
		cout << " " << err_msg; 
}

bool isInteger(string s)
{
    if(s.empty() || (s.c_str()[0] == '-') || (!isdigit(s.c_str()[0]))) return false ;
    char * p ;
    strtol(s.c_str(), &p, 10) ;
    return (*p == 0) ;
}

/* Gets the next set of tokens from the next valid line that is not empty
	If the line is empty, it increments the line counter until it reaches eof or a valid line.
	If tokens are not empty, do not parse the next line
*/
void getNextTokens(list<string> &t) {
    string curr_line;
    if(!myfile.eof() && t.empty()) { // parse next line only if tokens are empty
        lineoffset = strlen(line.c_str()) + 1;
        getline(myfile,line);
        if(!line.empty() || (!myfile.eof() && line.empty())) {
            linenumber++;
            lineoffset = 1;
        }
        curr_line = line; 
        trim(curr_line);
        
		while(!myfile.eof() && curr_line.empty()) {
            lineoffset = strlen(line.c_str()) + 1;
	        getline(myfile, line);
            curr_line = line;
            trim(curr_line);
            if(!myfile.eof()) {
                linenumber++;
                lineoffset = 1;
            } 
		}
        if(!line.empty()){
            curr_line = line;
            trim(curr_line);
            boost::char_separator<char> sep(" \t\n\0");
            my_tokenizer tok(curr_line, sep);
            t.insert(t.end(), tok.begin(), tok.end());
            lineoffset = 1;
        }
    }
}

/* Returns the count of the current instruction set */
int getCount() {
     int count;
     if(!tokens.empty()) {
        lineoffset = line.find(tokens.front(), lineoffset-1) + 1;
	    if(!isInteger(tokens.front())) {
		     __parseerror(0, linenumber, lineoffset);
	    }
        istringstream iss(tokens.front());
        iss >> count;
        if( count < 0 ) {
             __parseerror(0, linenumber, lineoffset);
        }
        lineoffset = line.find(tokens.front(), lineoffset-1) + 1;

       if(current_list == 1) { // if def list
            if(count > 16) {
                __parseerror(4, linenumber, lineoffset);
            }
       } else if(current_list == 2) { // if use list
             if(count > 16) {
                 __parseerror(5, linenumber, lineoffset);
             }
       } else if(current_list == 3) { // if instruction list
             if((instruction_counter + count) > (MACHINE_SIZE)) {
                 __parseerror(6, linenumber, lineoffset);
             }
       }
		tokens.pop_front();
        return count;
     } else { // if tokens are empty, return -1
         if(!myfile.eof() || !module_end)
            __parseerror(0, linenumber, lineoffset);
	    return -1;
     }
}

/* Validation of the definition list */
void verifyDefList(int count, list<string> &curr_tokens) {
    int number;
    string token;
	if (count > 0) {
        if(tokens.empty()) {
            if(!myfile.eof() && line.empty())
                lineoffset = 1;
            else if(!line.empty())
                lineoffset = strlen(line.c_str()) + 1;

            if(flip)
                __parseerror(1, linenumber, lineoffset);
            else
                __parseerror(0, linenumber, lineoffset);
        }

        token = tokens.front();
        lineoffset  = line.find(token, lineoffset - 1) + 1;
        if(flip) {
            if(isalpha(token.at(0)) == 0) {
                __parseerror(1, linenumber, lineoffset);
            } else if(strlen(token.c_str()) > 16) {
                __parseerror(3, linenumber, lineoffset);
            }
        } else {
             if(!isInteger(tokens.front())) {
                 __parseerror(0, linenumber, lineoffset);
             }
        }
        lineoffset += strlen(token.c_str());
        flip = !flip;
    }
}

/* validation of the use list */
void verifyUseList(int count, list<string> &curr_tokens) {
    string token;
    if(count > 0) {
         if(tokens.empty()) {
             if(!myfile.eof() && line.empty())
                 lineoffset = 1;
             else if(!line.empty())
                 lineoffset = strlen(line.c_str()) + 1;

             __parseerror(1, linenumber, lineoffset);
         }

        token = tokens.front();
        lineoffset  = line.find(token, lineoffset - 1) + 1;
        if(isalpha(token.at(0)) == 0) {
            __parseerror(1, linenumber, lineoffset);
        } else if(strlen(token.c_str()) > 16) {
            __parseerror(3, linenumber, lineoffset);
        }
        lineoffset += strlen(token.c_str());
    }
}

/* validation of the instruction list */
void verifyInstList(int count, list<string> &curr_tokens) {
     string token;
     int number;
     if (count > 0) {
        if(tokens.empty()) {
            if(!myfile.eof() && line.empty()) lineoffset = 1;
            else if(!line.empty()) lineoffset = strlen(line.c_str()) + 1;
            if(flip) __parseerror(2, linenumber, lineoffset);
            else __parseerror(0, linenumber, lineoffset);
        }        
        token = tokens.front();
        char current_token = token.at(0);
        lineoffset  = line.find(token, lineoffset -1 ) + 1;
        if(flip) {            
            if(isalpha(token.at(0)) == 0 || strlen(token.c_str()) > 1 || ( current_token != i_addr[0] && current_token != i_addr[1]  && current_token != i_addr[2] && current_token != i_addr[3])) {
                __parseerror(2, linenumber, lineoffset);
            }
        } else {
            if(!isInteger(tokens.front())) {
                __parseerror(0, linenumber, lineoffset);
            }
        }
        lineoffset += strlen(token.c_str());
        flip = !flip;
    }
}

/* Parse the tokens and validate if it fits the definition list syntax*/
int readDefList(vector<string> &duplicates){
    string line;
    int count, sym_addr;
    string sym;
    current_list = 1;
    getNextTokens(tokens); 
    
    map<string, int>::iterator it;
    base_addr_map[module_number]= module_length;
    
    count = getCount();
        for(int i = 0; i < count; i++) {
            if(!secondpass) { // first pass.
				getNextTokens(tokens);
				verifyDefList(count, tokens);
				sym = tokens.front();
				tokens.pop_front();
				
				it = sym_map.find(sym);
				if(it != sym_map.end()) { // Dulicate definition
					getNextTokens(tokens);
					verifyDefList(count, tokens);
					duplicates.push_back(sym);
				} else { // first occurence
					getNextTokens(tokens);
					verifyDefList(count, tokens);
					sym_addr = atoi(tokens.front().c_str());
					sym_map[sym] = module_length + sym_addr;
					sym_list.push_back(sym);
					mod_def_symbols.push_back(sym);
					def_symbols.insert(def_symbols.end(), boost::lexical_cast<string>(module_number));
					def_symbols.insert(def_symbols.end(), sym);					
				}			   
				tokens.pop_front();
            } else { // second pass. Just skip the tokens
                getNextTokens(tokens);
                verifyDefList(count, tokens);
                tokens.pop_front();
                getNextTokens(tokens);
                verifyDefList(count, tokens);
                tokens.pop_front();
            }
        }
    if( count > -1 ) // Edge case where it is the end of the file. 
        module_end = false;
}

/* Parses the tokens and validates if its the use list syntax*/
int readUseList(vector<string> &uselist_symbols){
    string line;
    int count;
    string used_sym;
    current_list = 2;
    getNextTokens(tokens); 
    count = getCount();

    for(int i = 0; i < count; i++) {
        getNextTokens(tokens);
        verifyUseList(count, tokens);
        used_sym = tokens.front();
        tokens.pop_front();
        uselist_symbols.push_back(used_sym);
    }
}

/* Utility function for the Instruction list parser to remove elements that are used */
void removeFromUsedList(vector<string> &uselist_symbols, int inst_addr) {
	list<string>::iterator pos;
	pos = find(used_symbols.begin(), used_symbols.end(), uselist_symbols[inst_addr%1000] );
	if(pos != used_symbols.end()) {
		used_symbols.erase(pos);
	}

	pos = find(def_symbols.begin(), def_symbols.end(), uselist_symbols[inst_addr%1000] );
	if(pos != def_symbols.end()) {
		def_symbols.erase(pos--);
		def_symbols.erase(pos);
	}
}

/* Parses the tokens and validates if its the instruction list syntax*/
int readInstList(vector<string> &uselist_symbols) {
    int count, inst_addr;
    string inst;
    current_list = 3;
    used_symbols.insert(used_symbols.end(), uselist_symbols.begin(), uselist_symbols.end());
    list<string>::iterator pos;
    getNextTokens(tokens);
    count = getCount();	

    for(int i = 0; i < count; i++) {
        getNextTokens(tokens);
        verifyInstList(count, tokens);
        inst = tokens.front();
        tokens.pop_front();
        getNextTokens(tokens);
        verifyInstList(count, tokens);
        inst_addr = atoi(tokens.front().c_str());
        tokens.pop_front();
		if(secondpass) {
				
			if(inst == "R") {			
				if(inst_addr > 9999) {
					__printMemoryMap(9999, "Error: Illegal opcode; treated as 9999");
				} else if((inst_addr%1000) > module_length_map[module_number]) {
					__printMemoryMap(((inst_addr/1000)*1000) + base_addr_map[module_number], "");
					_printInstErrors("R", "EXCEEDS_MOD_SIZE", "");
				} else if(inst_addr < 10000) {		
						__printMemoryMap(base_addr_map[module_number] + inst_addr, "");					
				}
				cout << endl;
			}
			
			else if(inst == "E") {
				if(inst_addr > 9999) {
						__printMemoryMap(9999, "Error: Illegal opcode; treated as 9999");
				} else if( ((inst_addr%1000)+1) > uselist_symbols.size() ) {
					 __printMemoryMap(inst_addr, "");
					 _printInstErrors("E", "EXCEEDS_USELIST_LENGTH", "");
				} else {
					if ((sym_map.find(uselist_symbols[inst_addr%1000])) != sym_map.end()) {
						__printMemoryMap((inst_addr - inst_addr%1000) + sym_map[uselist_symbols[inst_addr%1000]], "");
						removeFromUsedList(uselist_symbols, inst_addr);
						
					} else {
						__printMemoryMap((inst_addr/1000)*1000, "");
						_printInstErrors("E", "SYM_NOT_DEFINED", uselist_symbols[inst_addr%1000]);
						removeFromUsedList(uselist_symbols, inst_addr);
					}
				}
				cout << endl;
			}
			else if(inst == "A") {
				if(inst_addr > 9999) {
					__printMemoryMap(9999, "Error: Illegal opcode; treated as 9999");
				} else if ((inst_addr%1000 + 1) > MACHINE_SIZE) {
					__printMemoryMap((inst_addr/1000) * 1000 , "");
					_printInstErrors("A", "EXCEEDS_MACHINE_SIZE", "");
				} else {
					if(inst_addr < 10000)
						__printMemoryMap(inst_addr, "");					
				}
				cout << endl;
			} 
			else if(inst == "I"){
				if(inst_addr < 10000) {
					__printMemoryMap(inst_addr, "");
				} else {
					 __printMemoryMap(9999, "Error: Illegal immediate value; treated as 9999");
				}
				cout << endl;
			}			
		} // second pass
		instruction_counter++;
		module_length++;
    }// forloop
	module_end = true;
}

/* Create module is called by the first pass. */
int create_module(vector<string> &duplicates){
    vector<string> uselist_symbols; // Symbols used in the use list
    readDefList(duplicates);
    readUseList(uselist_symbols);
    readInstList(uselist_symbols);		
    module_length_map[module_number] = module_length - base_addr_map[module_number];

	int old_value;
	for( vector<string>::iterator it=mod_def_symbols.begin(); it!= mod_def_symbols.end(); it++) {
		if(module_number > 0 && (sym_map[*(it)] - base_addr_map[module_number]) >  module_length_map[module_number] - 1){
			old_value = sym_map[*(it)] - base_addr_map[module_number];	
			sym_map[*(it)] = 0 +  base_addr_map[module_number]; // rule 5
			cout << "Warning: Module " + boost::lexical_cast<string>(module_number) + ": " + (*it) + " to big " + boost::lexical_cast<string>(old_value) + " (max=" +  boost::lexical_cast<string>(module_length_map[module_number]-1) + ") assume zero relative" << endl;
		}
	}
	mod_def_symbols.clear();
    module_number++;
    return 0;
}

/* Resolve_address is called by the second pass */
int resolve_address() {
    vector<string> uselist_symbols;
    vector<string> duplicates;
    readDefList(duplicates);
    readUseList(uselist_symbols);
    readInstList(uselist_symbols);
	if(used_symbols.size() > 0) {
		for( list<string>::iterator it=used_symbols.begin(); it!= used_symbols.end(); it++) {
			_registerWarnings(w_list, "USELIST_NOT_USED", module_number, (*it));
		}
	}
    _printWarnings(w_list);
    used_symbols.clear();
    module_number++;

    return 0;
}

int first_pass() {
	myfile.open(FILE_NAME, ios::in);
	
	if (myfile.is_open()){
	vector<string> duplicates; // Duplicate symbol definitions
	while(!myfile.eof()){
		create_module(duplicates);
	}
	
	/* Print symbol table */
	cout << "Symbol Table"<<endl;
	for( vector<string>::iterator it=sym_list.begin(); it!= sym_list.end(); it++) {
		cout << (*it) << "=" << sym_map[(*it)];
		if( find(duplicates.begin(), duplicates.end(), (*it))!= duplicates.end() ) {
			cout << " Error: This variable is multiple times defined; first value used" << endl;
		} else {
			cout << endl;
		}
	} 
	cout << endl;
  }

  else cout << "Not a valid inputfile <" << FILE_NAME << ">";
  myfile.close();
}

int second_pass() {
    secondpass = true;
    tokens.clear();
    used_symbols.clear();
    module_number = 1;
    module_length = 0;
    linenumber = 0;
    flip = true;
    instruction_counter = 0;
    myfile.open(FILE_NAME, ios::in);    
	if (myfile.is_open()) {
		cout << "Memory Map" << endl;
		while(!myfile.eof()){
			resolve_address();
		}
		cout << endl;
		for( list<string>::iterator it=def_symbols.begin(); it!= def_symbols.end();it++) {
			cout << "Warning: Module " + (*it) + ": ";
			it++;
			cout << (*it) + " was defined but never used" << endl;
		}
		cout << endl;
	}
	else { cout << "Not a valid inputfile <" << FILE_NAME << ">"; }
	myfile.close();
}

/* MAIN */
int main (int argc, char* argv[]) {
	FILE_NAME = argv[1];
	if(argc < 1 || FILE_NAME == "") {
		cout << "Expected argument after options";
		return 0;
	}
	first_pass();
	second_pass();
	return 0;
}
