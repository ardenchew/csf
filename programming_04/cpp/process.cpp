#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include <string>
#include <map>
#include <iostream>

#include "error.h"
#include "write.h"
#include "operate.h"

int process(FILE * rfp, FILE * ofp) {

    unsigned char mem[256];
    for (int i = 0; i < 256; i++)
        mem[i] = 0;

    std::map<std::string, unsigned char> label_dict;
    std::map<int, std::string> label_args;

    int mem_counter = 0;

    std::string line = "";
    char c = fgetc(rfp);

    if (c == EOF) 
        return write(mem, ofp);
    
    while (c != EOF) {

        //get new line
        while (c != '\n') {
            line += c;
            c = fgetc(rfp);
        }

        //remove comments
        int semi_loc = line.find(";");
        if (semi_loc != line.npos) 
            line = line.substr(0,semi_loc);


        //skip empty line
        if (line.length() < 4) {
            line = "";
            c = fgetc(rfp);
            continue;
        }
       
        //get label
        int colon_loc = line.find(":");
        std::string cur_label = "";
        if (colon_loc != line.npos) {
            char label_char = line.at(0);
            if (!(isalpha(label_char)))
                return get_error(7);
            for (int i = 1; i < colon_loc; i++) {
                label_char = line.at(i);
                if (!(isalpha(label_char) || isdigit(label_char) || (label_char == 95)))
                    return get_error(7);
            }
            cur_label = line.substr(0,colon_loc);
            if (label_dict.find(cur_label) != label_dict.end())
                return get_error(7);
            line = line.substr(colon_loc + 1);
            label_dict.insert(std::pair<std::string, unsigned char>(cur_label,mem_counter));
        }

        //get opcode
        while (isspace(line.at(0))) {
            line = line.substr(1);
        }
        std::string cur_opcode = line.substr(0,3);
        line = line.substr(3);
        for (int i = line.length() - 1; i >= 0; i--) {
            if (isspace(line.at(i)))
                line.erase(i,1);
        }

        //get argument
        std::string cur_arg = line;
        char * arg_check;
        long int arg_int;
        arg_int = strtol(cur_arg.c_str(), &arg_check, 0);

        //if argument is label
        if ((arg_check == cur_arg) && !(cur_arg.empty())) 
            label_args.insert(std::pair<int,std::string>(mem_counter,cur_arg));
        
        int mem_byte = get_byte(cur_opcode, arg_int, cur_arg.empty());

        //error case
        if (mem_byte > 255) 
            return (mem_byte - 255);

        //ORG directive
        if (mem_byte < 0) {
            mem_counter = (mem_byte * -1) - 1;
            line = "";
            c = fgetc(rfp);
            continue;
        }

        //process byte
        unsigned char mem_char = mem_byte;
        if (mem_counter > 255)
            return get_error(4);
        mem[mem_counter] = mem_char;
        mem_counter++;
        
        line = "";
        c = fgetc(rfp);
    }

    //handle argument labels
    std::map<int, std::string>::iterator it;  
    for (it = label_args.begin(); it != label_args.end(); it++) {
        if (label_dict.find(it->second) == label_dict.end())
            return get_error(8);
        mem[it->first] += label_dict.find(it->second)->second;
    }

    int write_ret = write(mem, ofp); 
    if (write_ret != 0) 
        return write_ret;


    //need to learn how to actually change the memory of something in non local function

    return 0;

}
