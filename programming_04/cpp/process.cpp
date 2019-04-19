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
    
    bool eof_flag = 0;

    while ((c != EOF) && !(eof_flag)) {

        //get new line
        while (c != '\n') {
            line += c;
            c = fgetc(rfp);
            if (c == EOF) {
                eof_flag = 1;
                break;
            }
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
        bool label_flag = 0;
        int colon_loc = line.find(":");
        std::string cur_label = "";
        if (!(isspace(line.at(0)))) {
            if (colon_loc == line.npos) 
                return get_error(7);

            char label_char = line.at(0);

            //check first character for letter
            if (!(isalpha(label_char)))
                return get_error(7);

            //check for invalid label chars
            for (int i = 1; i < colon_loc; i++) {
                label_char = line.at(i);
                if (!(isalpha(label_char) || isdigit(label_char) || (label_char == 95)))
                    return get_error(7);
            }

            //check for duplicate labels
            cur_label = line.substr(0,colon_loc);
            if (label_dict.find(cur_label) != label_dict.end())
                return get_error(7);

            //update line and save label
            if ((colon_loc + 1) >= line.length()) {
                line = "";
            } else {
                line = line.substr(colon_loc + 1);
            }
            label_dict.insert(std::pair<std::string, unsigned char>(cur_label,mem_counter));
            label_flag = 1;

            //handle blank labels
            bool blank_label = 1;
            for (int i = 0; i < line.length(); i++) {
                if (!(isspace(line.at(i)))) {
                    blank_label = 0;
                    break;
                }
            }
            if (blank_label) {
                if (mem_counter > 255)
                    return get_error(4);
                mem[mem_counter] = 0;
                mem_counter++;
                line = "";
                c = fgetc(rfp);
                continue;
            }
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
            else
                break;
        } 

        if (!(line.length() <= 1)) {
            while (isspace(line.at(0))) {
                line = line.substr(1);
            }
        }

        //check for invalid argument
        char arg_char;
        for (int i = 0; i < line.length(); i++) {
            arg_char = line.at(i);
            if (!(isalpha(arg_char) || isdigit(arg_char) || (arg_char == 95) || (arg_char == 43) || (arg_char == 45)))
                return get_error(6);
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
            if (label_flag)
                return get_error(7);
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
        if (it->first > 255)
            return get_error(4);
        mem[it->first] += label_dict.find(it->second)->second;
    }

    int write_ret = write(mem, ofp); 
    if (write_ret != 0) 
        return write_ret;


    //need to learn how to actually change the memory of something in non local function

    return 0;

}
